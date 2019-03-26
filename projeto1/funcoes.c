#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "funcoes.h"

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}


int retorna_formandos_curso(perfil* perfils_array, int num_perfis, char mensagem[], char* curso) {
    for (int i=0; i<num_perfis; i++){
        if (strcmp(perfils_array[i].formacaoacad, curso) == 0) {

        }
    }
    return -1;
}


int retorna_habilidades_cidade(perfil* perfils_array, int num_perfis, char mensagem[], char* cidade) {
    for (int i=0; i<num_perfis; i++){
        if (strcmp(perfils_array[i].residencia, cidade) == 0) {

        }

    }
    return -1;
}


int acrescenta_experiencia_perfil(perfil* perfils_array, int num_perfis, char* experiencia, char* email) {
    for (int i=0; i<num_perfis; i++){
        if (strcmp(perfils_array[i].email, email) == 0) {

        }

    }
    return -1;
}


int retorna_experiencia_perfil(perfil* perfils_array, int num_perfis, char mensagem[], char* email) {
    for (int i=0; i<num_perfis; i++){
        if (strcmp(perfils_array[i].email, email) == 0) {

        }

    }
    return -1;
}


int retorna_perfis(perfil* perfils_array, int num_perfis, char mensagem[]) {
    for (int i=0; i<num_perfis; i++){

    }
    return -1;
}


int retorna_perfil(perfil* perfils_array, int num_perfis, char mensagem[], char* email) {
    for (int i=0; i<num_perfis; i++){
        if (strcmp(perfils_array[i].email, email) == 0) {

        }

    }
    return -1;
}
