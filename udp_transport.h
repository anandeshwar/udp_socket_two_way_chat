#ifndef _UDP_TRANSPORT_
#define _UDP_TRANSPORT_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

#include "udp_server.h"
#include "udp_client.h"
#include "queue.h"

#define MAX_LEN 320
#define MAX_THREADS 100

typedef void (*trans_cb) (char *buf, int len);

struct trans_fds
{
	int m_client_fd;
	int m_server_fd;
};

int udp_transport_init();
int udp_transport_close(int m_server_sock, int m_client_sock);
struct trans_fds *udp_transport_create(char *ip, int port_send, int port_recv);
void udp_transport_register(trans_cb callback);
int udp_transport_send(char *send, int len);

void *server_handler(void *);
void *client_handler(void *);

#endif //_UDP_TRANSPORT_
