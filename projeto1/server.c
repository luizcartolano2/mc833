/*
** server.c -- a stream socket server demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include "funcoes.h"

#define PORT "3490"  // the port users will be connecting to
#define CLIENT_COMMAND_SIZE 203
#define BACKLOG 10     // how many pending connections queue will hold
#define MAXPERFIL 10  // quantos perfis o DB aguenta

void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}


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
    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;
    perfil* database = malloc(MAXPERFIL * sizeof(perfil));

    strcpy(database[0].email, "maria_silva@gmail.com");
    strcpy(database[0].nome, "Maria");
    strcpy(database[0].sobrenome, "Silva");
    strcpy(database[0].foto, "/usr/semfoto");
    strcpy(database[0].residencia, "Campinas");
    strcpy(database[0].formacaoacad, "Ciência da Computação");
    strcpy(database[0].habilidades, "Análise de Dados, Internet das Coisas, Computação em Nuvem");
    strcpy(database[0].experienciaprof, "Estágio de 1 ano na Empresa X, onde trabalhei como analista de dados\nTrabalhei com IoT e Computação em Nuvem por 5 anos na Empresa Y");

    strcpy(database[1].email, "luiz_cartolano@gmail.com");
    strcpy(database[1].nome, "Luiz");
    strcpy(database[1].sobrenome, "Cartolano");
    strcpy(database[1].foto, "/usr/semfoto");
    strcpy(database[1].residencia, "Campinas");
    strcpy(database[1].formacaoacad, "Engenharia de Computação");
    strcpy(database[1].habilidades, "Parecer o Dorinha, Salva animais exceto patos, Superacademico");
    strcpy(database[1].experienciaprof, "Conpec empresa júnior na area de qualidade salvando o dia\nEstágio no Itaú juntando dinheiro pro Amoedo 30");

    strcpy(database[2].email, "gabrielaffonso32@hotmail.com");
    strcpy(database[2].nome, "Gabriel");
    strcpy(database[2].sobrenome, "Feitosa");
    strcpy(database[2].foto, "/usr/semfoto");
    strcpy(database[2].residencia, "Fortaleza");
    strcpy(database[2].formacaoacad, "Engenharia de Computação");
    strcpy(database[2].habilidades, "Caprinocultura, joga LoL muito bem, manja de animes");
    strcpy(database[2].experienciaprof, "Conpec empresa júnior como gerente de projetos desviando de balas que deixaram pra mim");

    strcpy(database[3].email, "victor_henrique@gmail.com");
    strcpy(database[3].nome, "Victor");
    strcpy(database[3].sobrenome, "Henrique");
    strcpy(database[3].foto, "/usr/semfoto");
    strcpy(database[3].residencia, "Campinas");
    strcpy(database[3].formacaoacad, "Física");
    strcpy(database[3].habilidades, "Capaz de acelerar partículas com as proprias maos");
    strcpy(database[3].experienciaprof, "Quarteto fantástico\nIncríveis\nVingadores");

    strcpy(database[4].email, "flavia.brtlt@gmail.com");
    strcpy(database[4].nome, "Flávia");
    strcpy(database[4].sobrenome, "Bertoletti");
    strcpy(database[4].foto, "/usr/semfoto");
    strcpy(database[4].residencia, "Socorro");
    strcpy(database[4].formacaoacad, "Turismo");
    strcpy(database[4].habilidades, "Sabe todas as trilhas de socorro, rafting, skydiving");
    strcpy(database[4].experienciaprof, "Full time como guia turistica de esportes radicais\nCEO da empresa `RotaryClub Radical`");

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                       sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
       }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
                  get_in_addr((struct sockaddr *)&their_addr),
                  s, sizeof s);
        printf("server: got connection from %s\n", s);
        if (!fork()) { // this is the child process
            close(sockfd); // child doesn't need the listener

            char client_command[CLIENT_COMMAND_SIZE];
            char message[1200];

            memset(message, '\0', 1200*sizeof(char));

            int numbytes;
            if (numbytes = recv(new_fd, client_command, CLIENT_COMMAND_SIZE-1, 0) == -1) {
              perror("recv");
              exit(1);
            }

            handle_client_option(database, MAXPERFIL, message, client_command);

            if (send(new_fd, message, 1200, 0) == -1)
                perror("send");

            close(new_fd);
            exit(0);
        }
        close(new_fd);  // parent doesn't need this
    }

    return 0;
}
