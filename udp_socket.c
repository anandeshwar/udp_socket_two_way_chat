#include "udp_socket.h"

struct sockaddr_in m_server_addr;
struct sockaddr_in m_client_addr;

bool is_valid(int m_sock) 
{ 
	return m_sock != -1; 
}

void udp_socket_init()
{
	memset(&m_server_addr, 0, sizeof(m_server_addr));
	memset(&m_client_addr, 0, sizeof(m_client_addr));
}


int udp_socket_create()
{
	int m_sock = socket(AF_INET,SOCK_DGRAM,0);

  	if (!is_valid(m_sock))
    		return -1;

  	return m_sock;
}

bool udp_socket_bind(int m_sock, const int port, bool server)
{
	int on = 1;
	int bind_return;
	if (!is_valid(m_sock)){
      		return false;
    	}


	if(server){
  		m_server_addr.sin_family = AF_INET;
  		m_server_addr.sin_addr.s_addr = INADDR_ANY;
  		m_server_addr.sin_port = htons(port);

		setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on));

        	bind_return = bind(m_sock,(struct sockaddr *)&m_server_addr,sizeof(m_server_addr));
	}else {
		m_client_addr.sin_family = AF_INET;
                m_client_addr.sin_addr.s_addr = INADDR_ANY;
                m_client_addr.sin_port = htons(port);

		setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on));

        	bind_return = bind(m_sock,(struct sockaddr *)&m_client_addr,sizeof(m_client_addr));
	}

    	if(bind_return == -1){
		printf("bind to port %d failed......\n", port);
      		return false;
    	}else{
		printf("bind to port %d success......\n", port);
	}
  	return true;
}


int udp_socket_send(int m_sock, char *s, int len, bool server) 
{
	int status;

	if(server){
		status = sendto(m_sock, s, len, 0,(struct sockaddr *) &m_server_addr, sizeof(struct sockaddr_in));
	}else{
		status = sendto(m_sock, s, len, 0,(struct sockaddr *) &m_client_addr, sizeof(struct sockaddr_in));
	}

    	if(status == -1){
      		return 0;
    	}else if(status == 0){
      		return 0;
    	}else{
      		return status;
    	}
}

int udp_socket_recv(int m_sock, char *buf, int buf_len, bool server) 
{
	int status;
  	socklen_t sin_size = sizeof(struct sockaddr_in);

	if(server){
  		status = recvfrom (m_sock, buf, buf_len, 0, (struct sockaddr *)&m_server_addr, &sin_size);
	}else{
		status = recvfrom (m_sock, buf, buf_len, 0, (struct sockaddr *)&m_client_addr, &sin_size);
	}	
  	if(status == -1){
      		return 0;
    	}else if(status == 0){
      		return 0;
    	}else{
      		return status;
    	}
}


bool udp_socket_connect(int m_sock, const char *host, const int port, bool server)
{
	int status;
	if(!is_valid(m_sock)) 
		return false;

	if(server){
  		m_server_addr.sin_family = AF_INET;
  		m_server_addr.sin_port = htons (port);
		status = inet_pton(AF_INET, host, &m_server_addr.sin_addr);
		if(errno == EAFNOSUPPORT)
                	return false;

        	status = connect(m_sock, (struct sockaddr *) &m_server_addr, sizeof(m_server_addr));

	}else{
		m_client_addr.sin_family = AF_INET;
                m_client_addr.sin_port = htons (port);
		status = inet_pton(AF_INET, host, &m_client_addr.sin_addr);
		if(errno == EAFNOSUPPORT)
                	return false;

        	status = connect(m_sock, (struct sockaddr *) &m_client_addr, sizeof(m_client_addr));
	}

  	if (status == 0)
    		return true;
  	else
    		return false;
}

void udp_socket_set_non_blocking(int m_sock,  const bool b)
{
  	int opts;

  	opts = fcntl(m_sock, F_GETFL);

  	if(opts < 0){
      		return;
    	}

  	if(b){
    		printf("Setting Socket to NONBLOCK mode\n");
    		opts = (opts | O_NONBLOCK);
  	}else{
    		opts = (opts & ~O_NONBLOCK);
  	}
  	fcntl(m_sock, F_SETFL,opts);
}

void udp_socket_set_rcv_timeout(int m_sock, int sec)
{
	struct timeval tv;

	tv.tv_sec = sec;
	tv.tv_usec = 0;  // Not init'ing this can cause strange errors

	setsockopt(m_sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));
}

void udp_scocket_set_snd_timeout(int m_sock, int sec)
{
	struct timeval tv;

    	tv.tv_sec = sec;
    	tv.tv_usec = 0;  // Not init'ing this can cause strange errors

    	setsockopt(m_sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv,sizeof(struct timeval));
}

void udp_socket_close(int m_sock)
{
	if (is_valid(m_sock))
		close(m_sock);
}


