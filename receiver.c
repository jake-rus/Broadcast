/*
 * receiver.c
 * sender Broadcast udp-packets
 *  Created on: 28 февр. 2018 г.
 *      Author: jake
 */
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h> //для close()
#include <stdlib.h> // для exit()

int main(void)
{
	char buf[BUFSIZ];
	const int optval=1;
	struct sockaddr_in local;
	struct sockaddr_in from;
	int fromlen = sizeof(from);
	int sock = socket(AF_INET,SOCK_DGRAM,0);
	if (sock < 0)
			{
			perror("socket error");
			exit(1);
			}
	bzero(&local, sizeof(local));
	bzero(&from, fromlen);
	inet_aton("127.255.255.255",&local.sin_addr);
	local.sin_port = htons(55555);
	local.sin_family = AF_INET;
	if (bind(sock, (struct sockaddr*) &local, sizeof(local)) < 0)
			{
			perror("binding error");
			exit(2);
			}
	if (recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr*)&from,&fromlen) <0)
			{
			perror("recvfrom error");
			exit(3);
			}
		printf("%s	from %s-%d\n",buf,inet_ntoa(from.sin_addr),from.sin_port);

}
