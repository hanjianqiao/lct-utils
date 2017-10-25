# Makefile

default:
	@echo 'Usage: make all or make all_clean'

all: tcp_server tcp_client udp_server udp_client

all_clean:
	rm *.out

tcp_server: tcp_server.c
	gcc tcp_server.c -o tcp_server.out

tcp_client: tcp_client.c
	gcc tcp_client.c -o tcp_client.out

udp_server: udp_server.c
	gcc udp_server.c -o udp_server.out

udp_client: udp_client.c
	gcc udp_client.c -o udp_client.out
