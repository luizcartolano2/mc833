#ifndef FUNCOES_H
#define FUNCOES_H

// struct para armazenar os dados do perfil
typedef struct perfil {
    char email[100];
    char nome[50];
    char sobrenome[50];
    char foto[50];
    char residencia[30];
    char formacaoacad[50];
    char habilidades[300];
    char experienciaprof[400];
} perfil;

// funcoes para manipular as informacoes salvas pelo servidor e enviar o que for pedido pelo cliente
/*
 * Argumentos:
 *  perfils_array: ponteiro para o vetor com todos perfis armazenados
 *  mensagem: mensagem que sera enviada para o cliente com o nome dos formandos do curso solicitado
 * curso: curso que sera usado como parametro de busca dentre os perfis
 * Retorna:
 *  -1 caso haja erro na montagem da mensagem;
 *  0 caso não haja erro.
 */
int retorna_formandos_curso(perfil* perfils_array, int num_perfis, char mensagem[], char* curso);

/*
 * Argumentos:
 *  perfils_array: ponteiro para o vetor com todos perfis armazenados
 *  num_perfis: numero de perfis armazenados no servidor
 *  mensagem: mensagem que sera enviada para o cliente com as habilidades dos perfis de certa cidade
 *  cidade: cidade que sera usado como parametro de busca dentre os perfis
 * Retorna:
 *  -1 caso haja erro na montagem da mensagem;
 *  0 caso não haja erro.
 */
int retorna_habilidades_cidade(perfil* perfils_array, int num_perfis, char mensagem[], char* cidade);

/*
 * Argumentos:
 *  perfils_array: ponteiro para o vetor com todos perfis armazenados
 *  num_perfis: numero de perfis armazenados no servidor
 *  experiencia: experiencia que sera acrescentada ao perfil
 *  email: chave para encontrar o perfil que sera modificado
 * Retorna:
 *  -1 caso haja erro na atualizacao
 *  0 caso não haja erro.
 */
int acrescenta_experiencia_perfil(perfil* perfils_array, int num_perfis, char* experiencia, char* email);

/*
 * Argumentos:
 *  perfils_array: ponteiro para o vetor com todos perfis armazenados
 *  num_perfis: numero de perfis armazenados no servidor
 *  mensagem: mensagem que sera enviada para o cliente com as experiencias de um determinado perfil
 *  email: chave para encontrar o perfil que sera exibido
 * Retorna:
 *  -1 caso haja erro na montagem da mensagem;
 *  0 caso não haja erro.
 */
int retorna_experiencia_perfil(perfil* perfils_array, int num_perfis, char mensagem[], char* email);

/*
 * Argumentos:
 *  perfils_array: ponteiro para o vetor com todos perfis armazenados
 *  num_perfis: numero de perfis armazenados no servidor
 *  mensagem: mensagem que sera enviada para o cliente com todos os perfis
 * Retorna:
 *  -1 caso haja erro na montagem da mensagem;
 *  0 caso não haja erro.
 */
int retorna_perfis(perfil* perfils_array, int num_perfis, char mensagem[]);

/*
 * Argumentos:
 *  perfils_array: ponteiro para o vetor com todos perfis armazenados
 *  num_perfis: numero de perfis armazenados no servidor
 *  mensagem: mensagem que sera enviada para o cliente com o nome dos formandos do curso solicitado
 *  email: chave para encontrar o perfil que sera exibido
 * Retorna:
 *  -1 caso haja erro na montagem da mensagem;
 *  0 caso não haja erro.
 */
int retorna_perfil(perfil* perfils_array, int num_perfis, char mensagem[], char* email);

#endif
