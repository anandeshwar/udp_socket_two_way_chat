#include "udp_client.h"
#include "udp_socket.h"

int udp_client_init(char *host, int port)
{
	int m_sock;
	printf("Host IP = %s, Port = %d\n", host, port);
	m_sock = udp_create_client_socket(host, port);
	return m_sock;
}

int udp_create_client_socket(char *host, int port)
{
	int m_sock;

	if(!(m_sock = udp_socket_create())){
		printf("Could not create client socket\n");
	}

	udp_socket_set_rcv_timeout(m_sock, 3);

	if(!udp_socket_connect(m_sock, host, port, false)){
		printf("Could not connect to server\n");
	}

	return m_sock;
}

void udp_close_client_socket(int m_sock)
{
	close(m_sock);
}

int udp_client_send(int m_sock, char *s, int len)
{
	int status;

	status = udp_socket_send(m_sock, s, len,false);

	return status;
}

int udp_cleint_receive(int m_sock, char *s, int len)
{
	int status;

	status = udp_socket_recv(m_sock, s, len, false);
	
	return status;	
}
