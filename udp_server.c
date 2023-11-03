#include "udp_server.h"
#include "udp_socket.h"


int udp_server_init(int port_recv)
{
	int m_sock = udp_create_server_socket(port_recv);

	return m_sock;
}

int udp_create_server_socket(int port)
{
	int m_sock;

	if(!(m_sock = udp_socket_create())){
		printf("Could not create server socket\n");

	}

	udp_socket_set_rcv_timeout(m_sock, 3);

	if(!udp_socket_bind(m_sock, port, true)){
		printf("Could not bind to port\n");
	}

	return m_sock;
}

void udp_close_server_socket(int m_sock)
{
	close(m_sock);
}

int udp_server_send(int m_sock, char *s, int len)
{
	int status;
	status = udp_socket_send(m_sock, s, len, true);
	return status;
}

int udp_server_receive(int m_sock, char *s, int len)
{
	int status;
	status = udp_socket_recv(m_sock, s, len, true);
	return status;	
}

