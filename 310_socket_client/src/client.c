/*
 * client.c
 *
 *  Created on: Mar 17, 2020
 *      Author: s_il_vanas
 */

#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>
#include"debug.h"
#include<errno.h>
#include"client.h"
int create_client_socket(void) {
	int socket_desc;
	int myerror;
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1) {
		myerror = errno;
		error_printf("Could not create socket. Error = %d (%s)\n", myerror,
				strerror(myerror));
		return -1;
	}
	debug_printf(-1, "Socket created.\n");
	return socket_desc;
}
int establish_client_connection(void) {
	while (1) {
		int socket_desc = create_client_socket();

		struct sockaddr_in server;
		server.sin_addr.s_addr = inet_addr(SRV_IP);
		server.sin_family = AF_INET;
		server.sin_port = htons(SRV_PORT);
		int connection_status = connect(socket_desc,
				(struct sockaddr *) &server, sizeof(server));
		debug_printf(-1, "Connection established.\n");
		return socket_desc;

	}
}

int send_client_message(int socket_desc, char* message) {
	int message_status = send(socket_desc, message, strlen(message), 0);
	int myerror;
	if (message_status < 0) {
		myerror = errno;
		error_printf("Message sending failed. Error = %d (%s)\n", myerror,
				strerror(myerror));
		return -1;
	}
	debug_printf(-1, "Data sent.\n");
	return 0;
}