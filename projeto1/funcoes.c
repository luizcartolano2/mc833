#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "funcoes.h"
#include <sys/socket.h>

int retorna_formandos_curso(perfil* perfils_array, int num_perfis, char mensagem[], char* curso) {
    int encontrou = 0;

    for (int i=0; i<num_perfis; i++){
        encontrou++;
        if (strcmp(perfils_array[i].formacaoacad, curso) == 0) {
            strcat(mensagem, perfils_array[i].nome);
            strcat(mensagem, " ");
            strcat(mensagem, perfils_array[i].sobrenome);
            strcat(mensagem, "\n");
        }
    }
    if (encontrou == 0) {
        return 0;
    }
    else {
        strcat(mensagem, "Nao foram encontrados formandos para o curso especificado.\n");
        return 1;
    }
}


int retorna_habilidades_cidade(perfil* perfils_array, int num_perfis, char mensagem[], char* cidade) {
    int encontrou = 0;
    for (int i=0; i<num_perfis; i++){
        if (strcmp(perfils_array[i].residencia, cidade) == 0) {
            encontrou++;
            strcat(mensagem, perfils_array[i].habilidades);
            strcat(mensagem, "\n");
        }

    }
    if (encontrou == 0) {
        return 0;
    }
    else {
        strcat(mensagem, "Nao foram encontradas habilidades para a cidade especificada.\n");
        return 1;
    }
}


int acrescenta_experiencia_perfil(perfil* perfils_array, int num_perfis, int k, char* email) {
    printf("%s\n",email);
    for (int i=0; i<num_perfis; i++){
        if (strcmp(perfils_array[i].email, email) == 0) {
            strcat(perfils_array[i].experienciaprof, "\n");
            strcat(perfils_array[i].experienciaprof, email+k+1);
            return 1;
        }
    }
    return 0;
}


int retorna_experiencia_perfil(perfil* perfils_array, int num_perfis, char mensagem[], char* email) {
    for (int i=0; i<num_perfis; i++){
        if (strcmp(perfils_array[i].email, email) == 0) {
            printf("%s\n", perfils_array[i].experienciaprof);
            strcat(mensagem, perfils_array[i].experienciaprof);
            strcat(mensagem, "\n");
            return 1;
        }

    }
    strcat(mensagem, "Perfil nao encontrado.\n");
    return 0;
}


int retorna_perfis(perfil* perfils_array, int num_perfis, char mensagem[]) {
    int tem_perfil = 0;
    for (int i=0; i<num_perfis; i++){
        if (strlen(perfils_array[i].email) > 0) {
            tem_perfil++;
            strcat(mensagem, "Nome: ");
            strcat(mensagem, perfils_array[i].nome);
            strcat(mensagem, " ");
            strcat(mensagem, perfils_array[i].sobrenome);
            strcat(mensagem, "\n");

            strcat(mensagem, "Email: ");
            strcat(mensagem, perfils_array[i].email);
            strcat(mensagem, "\n");

            strcat(mensagem, "Curso: ");
            strcat(mensagem, perfils_array[i].formacaoacad);
            strcat(mensagem, "\n");

            strcat(mensagem, "Foto: ");
            strcat(mensagem, perfils_array[i].foto);
            strcat(mensagem, "\n");

            strcat(mensagem, "Habilidades: ");
            strcat(mensagem, perfils_array[i].habilidades);
            strcat(mensagem, "\n");

            strcat(mensagem, "Experiencia profissional: ");
            strcat(mensagem, perfils_array[i].experienciaprof);
            strcat(mensagem, "\n");

            strcat(mensagem, "Residencia: ");
            strcat(mensagem, perfils_array[i].residencia);
            strcat(mensagem, "\n");
            strcat(mensagem, "\n");
        }
    }
    if (tem_perfil == 0)
        return 0;
    else
        return 1;
}


int retorna_perfil(perfil* perfils_array, int num_perfis, char mensagem[], char* email) {
    for (int i=0; i<num_perfis; i++){
        if (strcmp(perfils_array[i].email, email) == 0) {
            strcat(mensagem, "Nome: ");
            strcat(mensagem, perfils_array[i].nome);
            strcat(mensagem, " ");
            strcat(mensagem, perfils_array[i].sobrenome);
            strcat(mensagem, "\n");

            strcat(mensagem, "Email: ");
            strcat(mensagem, perfils_array[i].email);
            strcat(mensagem, "\n");

            strcat(mensagem, "Curso: ");
            strcat(mensagem, perfils_array[i].formacaoacad);
            strcat(mensagem, "\n");

            strcat(mensagem, "Foto: ");
            strcat(mensagem, perfils_array[i].foto);
            strcat(mensagem, "\n");

            strcat(mensagem, "Habilidades: ");
            strcat(mensagem, perfils_array[i].habilidades);
            strcat(mensagem, "\n");

            strcat(mensagem, "Experiencia profissional: ");
            strcat(mensagem, perfils_array[i].experienciaprof);
            strcat(mensagem, "\n");

            strcat(mensagem, "Residencia: ");
            strcat(mensagem, perfils_array[i].residencia);
            strcat(mensagem, "\n");
            strcat(mensagem, "\n");
            return 1;

        }

    }
    strcat(mensagem, "Perfil nao encontrado.\n");
    return 0;
}


void preencheDB(perfil* database) {

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
}


void handle_client_option(perfil* database, int maxperfil, char message[], char* client_command) {
    if (client_command[0] == '1')
    {
        retorna_formandos_curso(database, maxperfil, message, client_command+1);
    }
    else if(client_command[0] == '2')
    {
        retorna_habilidades_cidade(database, maxperfil, message, client_command+1);
    }
    else if(client_command[0] == '3')
    {
        int k = 0;
        while (client_command[k] != '\n') k++;
        client_command[k] = '\0';
        if (acrescenta_experiencia_perfil(database, maxperfil, k-1 , client_command+1))
            strcpy(message, "OK!");
        else
            strcpy(message, "DEU MERDA!");
    }
    else if(client_command[0] == '4')
    {
        retorna_experiencia_perfil(database, maxperfil, message, client_command+1);
    }
    else if(client_command[0] == '5')
    {
        retorna_perfis(database, maxperfil, message);
    }
    else if(client_command[0] == '6')
    {
        retorna_perfil(database, maxperfil, message, client_command+1);
    }
    else
    {
        strcpy(message, "Nao foi possivel identificar o comando solicitado pelo cliente!");
    }

}


int send_all(int socket, void *buffer, size_t length) {
    char *ptr = (char*) buffer;
    while (length > 0)
    {
        int i = send(socket, ptr, length, 0);
        if (i < 1)
            return -1;
        ptr += i;
        length -= i;
    }
    return 0;
}
