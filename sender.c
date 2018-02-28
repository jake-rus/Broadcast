/*
 * sender.c
 * sender Broadcast udp-packets
 *  Created on: 28 февр. 2018 г.
 *      Author: jake
 */
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h> //для close()
#include <stdlib.h> // для exit()

int main(void)
{
	char msg[]="Broadcast packet";
	const int optval=1;
	struct sockaddr_in local;
	int sock = socket(AF_INET,SOCK_DGRAM,0);
	if (sock < 0)
				{
				perror("socket error");
				exit(1);
				}
	bzero(&local, sizeof(local));
	setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&optval,sizeof(optval));

	inet_aton("127.255.255.255",&local.sin_addr);
	local.sin_port = htons(55555);
	local.sin_family = AF_INET;

	sendto(sock,msg,sizeof(msg),0,(struct sockaddr*)&local,sizeof(local));
	close(sock);
	return 0;
}
