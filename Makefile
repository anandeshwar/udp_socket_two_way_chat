CC      = gcc
CFLAGS  = -g
LDFLAGS = -g -lpthread

.PHONY: all
all: transport_server transport_client

transport_server: transport_server.o queue.o udp_transport.o udp_server.o udp_client.o udp_socket.o 
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

transport_client: transport_client.o queue.o udp_transport.o udp_server.o udp_client.o udp_socket.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^


clean:
	@rm -rf *.o
	@rm transport_client transport_server 	
