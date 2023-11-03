#ifndef _UDP_SOCKET_
#define _UDP_SOCKET_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

// Server initialization
void udp_socket_init(); 
int udp_socket_create();
bool udp_socket_bind(int m_sock, const int port, bool server);

// Client initialization
bool udp_socket_connect(int m_sock, const char *host, const int port, bool server);

// Data Transimission
int udp_socket_send(int m_sock, char *, int, bool server);
int udp_socket_recv(int m_sock, char *, int, bool server);
void udp_socket_close(int m_sock);

void udp_socket_set_non_blocking (int m_sock, const bool );
void udp_socket_set_rcv_timeout(int m_sock, int sec);
void udp_socket_set_snd_timeout(int m_sock, int sec);

bool is_valid(int m_sock);

#endif //_UDP_SOCKET_
