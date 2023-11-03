#include "udp_transport.h"

struct thread_args {
	int m_sock;
	//bool server;
};

static pthread_mutex_t g_client_buf_mutex;
static pthread_mutex_t g_server_buf_mutex;

int thread_no = 0;
bool run_server_thread = false;
bool run_client_thread = false;

pthread_t server_tid[MAX_THREADS];
pthread_t client_tid[MAX_THREADS];

trans_cb transport_callback;
struct trans_fds fds;

int udp_transport_init()
{
	pthread_mutex_init(&g_server_buf_mutex, NULL);
	pthread_mutex_init(&g_client_buf_mutex, NULL);

	init_send_queue();

	run_server_thread = false;
	run_client_thread = false;
}

int udp_transport_close(int m_server_sock, int m_client_sock)
{
	run_client_thread = false;
	run_server_thread = false;

	udp_close_server_socket(m_server_sock);
	udp_close_client_socket(m_client_sock);

	delete_send_queue();

	return 0;
}

void udp_transport_register(trans_cb callback)
{
	transport_callback = callback;
}

int udp_transport_send(char *send, int len)
{
	int status = len;

	pthread_mutex_lock(&g_client_buf_mutex);
	node n;
	memcpy(&n.m_str, send, len);
	send_queue_enqueue(n);		
	pthread_mutex_unlock(&g_client_buf_mutex);

	return status;
}


struct trans_fds *udp_transport_create(char *ip, int port_send, int port_recv)
{
	struct thread_args *server_th_arg;
	struct thread_args *client_th_arg;

	int rc_server = 0;
	int rc_client = 0;

	int *status1;
	int *status2;
	int m_server_sock = udp_server_init(port_recv);
	int m_client_sock = udp_client_init(ip, port_send);
	
		
	run_server_thread = true;
        run_client_thread = true;

	server_th_arg = (struct thread_args *)malloc(sizeof(struct thread_args));
	client_th_arg = (struct thread_args *)malloc(sizeof(struct thread_args));

	server_th_arg->m_sock = m_server_sock;
	client_th_arg->m_sock = m_client_sock;

	rc_server = pthread_create(&server_tid[thread_no], 0, server_handler, (void *)server_th_arg);
	rc_client = pthread_create(&client_tid[thread_no], 0, client_handler, (void *)client_th_arg);

	//pthread_join(server_tid[thread_no], (void **) &status1);
	//pthread_join(client_tid[thread_no], (void **) &status2);

	if(rc_server && rc_client){
                printf("A request could not be processed\n");
		udp_transport_close(m_server_sock, m_client_sock);
		return NULL;
	}else{
        	thread_no++;
        }

	fds.m_server_fd = m_server_sock;
	fds.m_client_fd = m_client_sock;
	
	return &fds;
}


void *server_handler(void *m_server_sock)
{
	int status = 0;
	char buf[MAX_LEN];
	int len=MAX_LEN;

	struct thread_args *arg = m_server_sock;

	while(run_server_thread)
	{
		memset(buf, 0, MAX_LEN);

		status = udp_server_receive(arg->m_sock, (char *)&buf, len);

		if(status)
		{
			pthread_mutex_lock(&g_server_buf_mutex);
			transport_callback(buf, status);
			pthread_mutex_unlock(&g_server_buf_mutex);
		}
		usleep(5000);
	}

	if(arg)
		free(arg);
	pthread_exit(NULL);
}

void *client_handler(void *m_client_sock)
{
 	int status;
	char temp_buf[MAX_LEN];

	struct thread_args *arg = m_client_sock;

	while(run_client_thread)
	{
		if(!send_queue_empty())
		{
			pthread_mutex_lock(&g_client_buf_mutex);
			node *temp = send_queue_front();
			if(temp != NULL)
			{
				status = udp_client_send(arg->m_sock, (char *)temp->m_str, MAX_LEN);
            			send_queue_dequeue();
			}
			pthread_mutex_unlock(&g_client_buf_mutex);
		}
		
		usleep(5000);
	}
	if(arg)
		free(arg);
	pthread_exit(NULL);
}

