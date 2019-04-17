/*
** listener.c -- a datagram sockets "server" demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include "funcoes.h"

#define MYPORT "4950"	// the port users will be connecting to

#define MAXBUFLEN 100
#define MAXPERFIL 10  // quantos perfis o DB aguenta

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;
	struct sockaddr_storage their_addr;
	char buf[MAXBUFLEN];
	socklen_t addr_len;
	char s[INET6_ADDRSTRLEN];
    clock_t start_time, end_time;
    perfil* database = malloc(MAXPERFIL * sizeof(perfil));
    memset(database, '\0', MAXPERFIL*sizeof(perfil));
    
    preencheDB(database);
    writeToFile(database);
    
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("listener: socket");
			continue;
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("listener: bind");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "listener: failed to bind socket\n");
		return 2;
	}

	freeaddrinfo(servinfo);

	printf("listener: waiting to recvfrom...\n");

	addr_len = sizeof their_addr;
	while(1) {
		if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
			(struct sockaddr *)&their_addr, &addr_len)) == -1) {
			perror("recvfrom");
			exit(1);
		}
		start_time = clock();
		
		char enderecocartola[100];
		strcpy(enderecocartola, inet_ntop(their_addr.ss_family, 
										   get_in_addr((struct sockaddr *)&their_addr),
										   s, sizeof s));	
		printf("listener: got packet from %s\n", enderecocartola);
		printf("listener: packet is %d bytes long\n", numbytes);
		buf[numbytes] = '\0';
		
		printf("listener: message is %s\n", buf);
        char message[5000];
        memset(message, '\0', 5000);
		retorna_perfil(database, 10, message, buf);
        
		end_time = clock();
        printf("Time is %lf", ((double)end_time-(double)start_time)/(double)CLOCKS_PER_SEC);
        //printf("Sending message:\n%sto my boy cartolano...", message);
        if ((numbytes = sendto(sockfd, message, strlen(message), 0,
			 (struct sockaddr *)&their_addr, addr_len)) == -1) {
			perror("talker: sendto");
			exit(1);
		}
		printf("sent ;)\n");
        
        
	}

	close(sockfd);

	return 0;
}
