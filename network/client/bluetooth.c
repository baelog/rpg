// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/socket.h>
// #include <bluetooth/bluetooth.h>
// #include <bluetooth/hci.h>
// #include <bluetooth/hci_lib.h>

// int main(int argc, char **argv)
// {
//     inquiry_info *ii = NULL;
//     int max_rsp, num_rsp;
//     int dev_id, sock, len, flags;
//     int i;
//     char addr[19] = "98:D3:21:F8:31:76";
//     char name[248] = { 0 };

//     dev_id = hci_get_route(NULL);
//     sock = hci_open_dev( dev_id );
//     if (dev_id < 0 || sock < 0) {
//         perror("opening socket");
//         exit(1);
//     }

//     len  = 8;
//     max_rsp = 255;
//     flags = IREQ_CACHE_FLUSH;
//     ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));
    
//     num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
//     if( num_rsp < 0 ) perror("hci_inquiry");

//     for (i = 0; i < num_rsp; i++) {
//         ba2str(&(ii+i)->bdaddr, addr);
//         memset(name, 0, sizeof(name));
//         if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name), 
//             name, 0) < 0)
//         strcpy(name, "[unknown]");
//         printf("%s  %s\n", addr, name);
//     }

//     free( ii );
//     close( sock );
//     return 0;
// }

// /* 
//  * RFCOMM Server for Linux by using BlueZ
//  * Copyright (C) 2015 by Tony Cho
//  * This program is free software: you can redistribute it and/or modify
//  * it under the terms of the GNU General Public License as published by
//  * the Free Software Foundation, either version 3 of the License, or
//  * (at your option) any later version.
//  *
//  * This program is distributed in the hope that it will be useful,
//  * but WITHOUT ANY WARRANTY; without even the implied warranty of
//  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  * GNU General Public License for more details.
//  *
//  * You should have received a copy of the GNU General Public License
//  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
//  */

// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <sys/socket.h>
// #include <bluetooth/bluetooth.h>
// #include <bluetooth/rfcomm.h>
// #include "bluetooth.h"

// int main(int argc, char **argv)
// {
// 	struct sockaddr_rc loc_addr = { 0 };	/* local bluetooth adapter's info */
// 	struct sockaddr_rc client_addr = { 0 };	/* filled in with remote (client) bluetooth device's info */
// 	char buf[1024] = { 0 };
// 	int server_sock, client_sock, bytes_read;
// 	unsigned int opt = sizeof(client_addr);

// 	printf("Start Bluetooth RFCOMM server...\n");

// 	/* allocate socket */
// 	server_sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

// 	loc_addr.rc_family = AF_BLUETOOTH;		/* Addressing family, always AF_BLUETOOTH */
// 	bacpy(&loc_addr.rc_bdaddr, BDADDR_ANY);		/* Bluetooth address of local bluetooth adapter */
// 	loc_addr.rc_channel = RFCOMM_SERVER_PORT_NUM;	/* port number of local bluetooth adapter */

// 	printf("binding\n");
// 	if(bind(server_sock, (struct sockaddr *)&loc_addr, sizeof(loc_addr)) < 0) {
// 		perror("failed to bind");
// 		exit(1);
// 	}

// 	printf("listening\n");
// 	/* put socket into listening mode */
// 	listen(server_sock, 1);		/* backlog is one */

// 	/* accept one connection */
// 	client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &opt);	/* return new socket for connection with a client */

// 	ba2str( &client_addr.rc_bdaddr, buf );
// 	printf("connected from %s\n", buf);

// 	/* read data from the client */
// 	memset(buf, 0, sizeof(buf));
// 	bytes_read = recv(client_sock, buf, sizeof(buf), 0);
// 	if( bytes_read > 0 ) {
// 		printf("received [%s]\n", buf);
// 	}

// 	/* close connection */
// 	close(client_sock);
// 	close(server_sock);
// 	return 0;
// }

/* 
 * RFCOMM Client for Linux by using BlueZ
 * Copyright (C) 2015 by Tony Cho
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include "bluetooth.h"

int main(int argc, char **argv)
{
	struct sockaddr_rc addr = { 0 };
	int sock;
	const char *sample_text = "RFCOMM Simple Example Done";

	printf("Start Bluetooth RFCOMM client, server addr %s\n", RFCOMM_SERVER_BLUETOOTH_ADDR);
	/* allocate a socket */
	sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

	/* set the outgoing connection parameters, server's address and port number */
	addr.rc_family = AF_BLUETOOTH;								/* Addressing family, always AF_BLUETOOTH */
	addr.rc_channel = RFCOMM_SERVER_PORT_NUM;						/* server's port number */
	str2ba(RFCOMM_SERVER_BLUETOOTH_ADDR, &addr.rc_bdaddr); 					/* server's Bluetooth Address */

	/* connect to server with destination address and port */
	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("failed to connect");
		exit(1);
	}

	/* send a message */
	printf("connected...\n");
	send(sock, sample_text, strlen(sample_text), 0);

	close(sock);
	return 0;
}
