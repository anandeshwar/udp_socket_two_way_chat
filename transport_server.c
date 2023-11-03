#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include "udp_transport.h"

#define BUF_LEN 256

struct trans_fds *server_trfds;

void sigfun(int sig)
{
        printf("You have pressed Ctrl-C , please press again to exit");
        udp_transport_close(server_trfds->m_server_fd, server_trfds->m_client_fd);
	sleep(3);
        (void) signal(SIGINT, SIG_DFL);
}

void tansport_recv(char *data, int len)
{
	printf("Received: %s\n", data);
}

void get_input(char *buf, char *msg) {
    	printf("%s", msg);
    	fgets(buf, BUF_LEN, stdin);
    	buf[strcspn(buf, "\n")] = '\0'; // Remove the newline
}

int main()
{
	char buf[BUF_LEN] = {0};

	(void) signal(SIGINT, sigfun);

	udp_transport_init();

	server_trfds = udp_transport_create("127.0.0.1", 1234, 5678);

	udp_transport_register(tansport_recv);

	while(1)
	{
		get_input(buf, "\nPlease type a message to send\n");
		udp_transport_send(buf, BUF_LEN);
	}
}

