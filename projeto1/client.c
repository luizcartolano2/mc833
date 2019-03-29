/*
** client.c -- a stream socket client demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "funcoes.h"
#include <arpa/inet.h>
#include <time.h>

#define PORT "3490" // the port client will be connecting to

#define MAXDATASIZE 5000 // max number of bytes we can get at once
#define FINALREQUESTSIZE 203

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa){
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
    int sockfd, numbytes;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    clock_t start_time, end_time;

    /* Get the current time. */


    if (argc != 2) {
        fprintf(stderr,"usage: client hostname\n");
        exit(1);
    }

    //Interface com usuario
    printf("(1) listar todas as pessoas formadas em um determinado curso;\n(2) listar as habilidades dos perfis que moram em uma determinada cidade;\n(3) acrescentar uma nova experiência em um perfil;\n(4) dado o email do perfil, retornar sua experiência;\n(5) listar todas as informações de todos os perfis;\n(6) dado o email de um perfil, retornar suas informações.\n");
    int serverRequest;
    scanf("%d", &serverRequest);
    if ((serverRequest < 1) || (serverRequest > 6)) {
        printf("Request invalido\n");
        exit(1);
    }
    char requestToSend[100];
    if (serverRequest != 5){
        if (serverRequest == 1)
        {
            printf("Qual curso você deseja ver as pessoas formadas?\n");
            scanf("%s", requestToSend);
        }
        else if (serverRequest == 2)
        {
            printf("Qual cidade você deseja ver as habilidades?\n");
            scanf("%s", requestToSend);
        }
        else if (serverRequest == 3)
        {
            printf("Em que perfil iremos acrescentar experiência (email)?\n");
            scanf("%s", requestToSend);
            printf("Qual experiência você deseja acrescentar?\n");
            char requestToSend2[100];
            scanf("%s", requestToSend2);
            strcat(requestToSend, "\n");
            strcat(requestToSend, requestToSend2);
        }
        else if (serverRequest == 4)
        {
            printf("Qual perfil você deseja ver as experiencias (email)?\n");
            scanf("%s", requestToSend);
        }
        else if (serverRequest == 6)
        {
            printf("Qual perfil você deseja ver as informacoes (email)?\n");
            scanf("%s", requestToSend);
        }
    }

    // Prepara request pro server no formato "(INT DA OPERACAO)stringdaoperacao"
    // Ex: "1Engenharia de Computação"
    // Obs: "3gabrielaffonso32@hotmail.com\nTrader no Bank of America"
    char finalRequest[FINALREQUESTSIZE];
    memset(finalRequest, '\0', FINALREQUESTSIZE*sizeof(char));
    finalRequest[0] = serverRequest+'0';
    strcat(finalRequest, requestToSend),
    printf("FINAL REQUEST STRING IS: %s\n", finalRequest);

    //Conection Overhead
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }
    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);
    freeaddrinfo(servinfo); // all done with this structure

    // AQUI INICIA A REQUISICAO
    start_time = clock();
    if (send_all(sockfd, finalRequest, sizeof(finalRequest)) == -1) {
        perror("send");
    }

    //Recebe o request finalmente
    char buf[MAXDATASIZE];
    memset(buf, '\0', MAXDATASIZE*sizeof(char));


    if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
        printf("numbytes: %d\n", numbytes);
        printf("TO AQUI");
        perror("recv");
        exit(1);
    }
    // AQUI TERMINA A REQUISICAO
    end_time = clock();
    buf[numbytes] = '\0';

    printf("client: received '%s'",buf);

    printf("\nTempo cliente: %lf\n", (((double)end_time - (double)start_time) / (double)CLOCKS_PER_SEC ));

    close(sockfd);

    return 0;
}
