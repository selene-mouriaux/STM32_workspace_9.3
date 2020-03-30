/*
 * client.h
 *
 *  Created on: Mar 17, 2020
 *      Author: s_il_vanas
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#define SRV_IP "127.0.0.1"
#define SRV_PORT 5001
int create_client_socket(void);
int establish_client_connection(void);
int send_client_message(int socket_desc, char* message);
#endif /* CLIENT_H_ */
