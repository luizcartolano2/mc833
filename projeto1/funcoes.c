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

void writeToFile(perfil* database)
{
    FILE *fp = fopen("db", "w");
    if (fp == NULL)
    {
        perror("Erro ao tentar abrir db\n");
        exit(1);
    }
    char *filestring = malloc(MAXPERFIL*sizeof(perfil));
    memset(filestring, '\0', MAXPERFIL*sizeof(perfil));
    for (int i = 0; i < 5; i++)
    {
        strcat(filestring, database[i].email);
        strcat(filestring, database[i].nome);
        strcat(filestring, database[i].sobrenome);
        strcat(filestring, database[i].foto);
        strcat(filestring, database[i].residencia);
        strcat(filestring, database[i].formacaoacad);
        strcat(filestring, database[i].habilidades);
        char aux[3];
        aux[0] = database[i].n_experienciaprof + '0';
        aux[1] = '\n';
        aux[2] = '\0';
        strcat(filestring, aux);
        strcat(filestring, database[i].experienciaprof);
    }
    fputs(filestring, fp);
    fclose(fp);
}

void readFromDB(perfil* database) {
    FILE *fp = fopen("db", "r");
    if (fp == NULL)
    {
        perror("Erro ao tentar abrir db\n");
        exit(1);
    }
    memset(database, '\0', 10*sizeof(perfil));
    for (int i = 0; i < 5; i++)
    {
        fgets(database[i].email, 100, fp);
        fgets(database[i].nome, 50, fp);
        fgets(database[i].sobrenome, 50, fp);
        fgets(database[i].foto, 30, fp);
        fgets(database[i].residencia, 30, fp);
        fgets(database[i].formacaoacad, 50, fp);
        fgets(database[i].habilidades, 300, fp);
        char aux[3];
        fgets(aux, 100, fp);
        database[i].n_experienciaprof = aux[0]-'0';
        for (int j = 0; j < database[i].n_experienciaprof; j++)
        {
            char aux[400];
            fgets(aux, 400, fp);
            strcat(database[i].experienciaprof, aux);
        }
    }
    fclose(fp);
}
//char email[100];
//char nome[50];
//char sobrenome[50];
//char foto[50];
//char residencia[30];
//char formacaoacad[50];
//char habilidades[300];
//int n_experienciaprof;
//char experienciaprof[400];

void preencheDB(perfil* database) {

    strcpy(database[0].email, "maria_silva@gmail.com\n");
    strcpy(database[0].nome, "Maria\n");
    strcpy(database[0].sobrenome, "Silva\n");
    strcpy(database[0].foto, "/usr/semfoto\n");
    strcpy(database[0].residencia, "Campinas\n");
    strcpy(database[0].formacaoacad, "Ciência da Computação\n");
    strcpy(database[0].habilidades, "Análise de Dados, Internet das Coisas, Computação em Nuvem\n");
    database[0].n_experienciaprof = 2;
    strcpy(database[0].experienciaprof, "Estágio de 1 ano na Empresa X, onde trabalhei como analista de dados\nTrabalhei com IoT e Computação em Nuvem por 5 anos na Empresa Y\n");

    strcpy(database[1].email, "luiz_cartolano@gmail.com\n");
    strcpy(database[1].nome, "Luiz\n");
    strcpy(database[1].sobrenome, "Cartolano\n");
    strcpy(database[1].foto, "/usr/semfoto\n");
    strcpy(database[1].residencia, "Campinas\n");
    strcpy(database[1].formacaoacad, "Engenharia de Computação\n");
    strcpy(database[1].habilidades, "Parecer o Dorinha, Salva animais exceto patos, Superacademico\n");
    database[1].n_experienciaprof = 2;
    strcpy(database[1].experienciaprof, "Conpec empresa júnior na area de qualidade salvando o dia\nEstágio no Itaú juntando dinheiro pro Amoedo 30\n");

    strcpy(database[2].email, "gabrielaffonso32@hotmail.com\n");
    strcpy(database[2].nome, "Gabriel\n");
    strcpy(database[2].sobrenome, "Feitosa\n");
    strcpy(database[2].foto, "/usr/semfoto\n");
    strcpy(database[2].residencia, "Fortaleza\n");
    strcpy(database[2].formacaoacad, "Engenharia de Computação\n");
    strcpy(database[2].habilidades, "Caprinocultura, joga LoL muito bem, manja de animes\n");
    database[2].n_experienciaprof = 1;
    strcpy(database[2].experienciaprof, "Conpec empresa júnior como gerente de projetos desviando de balas que deixaram pra mim\n");

    strcpy(database[3].email, "victor_henrique@gmail.com\n");
    strcpy(database[3].nome, "Victor\n");
    strcpy(database[3].sobrenome, "Henrique\n");
    strcpy(database[3].foto, "/usr/semfoto\n");
    strcpy(database[3].residencia, "Campinas\n");
    strcpy(database[3].formacaoacad, "Física\n");
    strcpy(database[3].habilidades, "Capaz de acelerar partículas com as proprias maos\n");
    database[3].n_experienciaprof = 3;
    strcpy(database[3].experienciaprof, "Quarteto fantástico\nIncríveis\nVingadores\n");

    strcpy(database[4].email, "flavia.brtlt@gmail.com\n");
    strcpy(database[4].nome, "Flávia\n");
    strcpy(database[4].sobrenome, "Bertoletti\n");
    strcpy(database[4].foto, "/usr/semfoto\n");
    strcpy(database[4].residencia, "Socorro\n");
    strcpy(database[4].formacaoacad, "Turismo\n");
    strcpy(database[4].habilidades, "Sabe todas as trilhas de socorro, rafting, skydiving\n");
    database[4].n_experienciaprof = 2;
    strcpy(database[4].experienciaprof, "Full time como guia turistica de esportes radicais\nCEO da empresa `RotaryClub Radical`\n");

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
