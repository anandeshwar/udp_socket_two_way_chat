#ifndef _UDP_SERVER_
#define _UDP_SERVER_


int udp_server_init(int port_recv);
int udp_create_server_socket(int port);
void udp_close_server_socket(int m_sock);
int udp_server_send(int m_sock, char *s, int len);
int udp_server_receive(int m_sock, char *s, int len);

#endif //_UDP_SEVRER_
