/*
** talker.c -- a datagram "client" demo
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

#define MAXBUFLEN 499
#define FINALREQUESTSIZE 100
#define SERVERPORT "4950"	// the port users will be connecting to

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	struct sockaddr_storage their_addr;
	char buf[MAXBUFLEN];
	socklen_t addr_len;
	int numbytes;
    clock_t start_time, end_time;

	if (argc != 2) {
		fprintf(stderr,"usage: talker hostname message\n");
		exit(1);
	}

	 //Interface com usuario
    printf("Forneca o email do perfil que voce deseja acessar\n");
    char requestToSend[100];
    scanf("%s", requestToSend);
	
    // Prepara request pro server no formato "(INT DA OPERACAO)stringdaoperacao"
    // Ex: "1Engenharia de Computação"
    // Obs: "3gabrielaffonso32@hotmail.com\nTrader no Bank of America"
    char finalRequest[FINALREQUESTSIZE];
    memset(finalRequest, '\0', FINALREQUESTSIZE*sizeof(char));
    strcat(finalRequest, requestToSend);
    printf("FINAL REQUEST STRING IS: %s\n", finalRequest);


	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ((rv = getaddrinfo(argv[1], SERVERPORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and make a socket
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("talker: socket");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "talker: failed to create socket\n");
		return 2;
	}
	start_time = clock();
	if ((numbytes = sendto(sockfd, finalRequest, strlen(finalRequest), 0,
			 p->ai_addr, p->ai_addrlen)) == -1) {
		perror("talker: sendto");
		exit(1);
	}
	printf("talker: sent %d bytes to %s\n", numbytes, argv[1]);
	
	addr_len = sizeof their_addr;
	if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
		(struct sockaddr *)&their_addr, &addr_len)) == -1) {
		perror("recvfrom");
		exit(1);
	}
	end_time = clock();
	
	char imprime[500];
	memset(imprime, '\0', MAXBUFLEN*sizeof(char));
    strcat(imprime, buf);
	
   	printf("%s\n",buf);
	printf("\nTempo cliente: %lf\n", (((double)end_time - (double)start_time) / (double)CLOCKS_PER_SEC ));

	freeaddrinfo(servinfo);
	close(sockfd);

	return 0;
}
