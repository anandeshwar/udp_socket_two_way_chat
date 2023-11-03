#ifndef _UDP_CLIENT_
#define _UDP_CLIENT_


int udp_client_init(char *host, int port);
int udp_create_client_socket(char *host, int port);
void udp_close_client_socket(int m_sock);
int udp_client_send(int m_sock, char *s, int len);
int udp_cleint_receive(int m_sock, char *s, int len);

#endif //_UDP_CLIENT_
