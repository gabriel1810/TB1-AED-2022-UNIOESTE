#ifndef LISTAENCADEADA_H_INCLUDED
#define LISTAENCADEADA_H_INCLUDED
#define MAX_CHAR 254
#define CLEAR_SCREEN system("cls");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//Estrutura para cabeçalho dos arquivos
typedef struct{
    int pos_cabeca; //Posição do inicio da lista
    int pos_topo;   //1a posição não usada no fim do arquivo
    int pos_livre;  //Posição do inicio da lista de nos livres
} cabecalho;

//Estrutura para item de cardapio (Sanduiche, Bebida, Extra ou sobremesa)
typedef struct {
    char tipo[2];               //Tipo do item (SD,BB,EX,SM)
    int codigo;                 //Codigo referente ao item
    char nome[MAX_CHAR];        //Nome do item
    char descricao[MAX_CHAR];   //Descricao caso seja um SD
    char disponivel;            //Flag disponivel 'D' ou 'I'
    double precos[3];           //Vetor com os precos P, M e G
    int prox;                   //Proximo item da lista
}no_item_cardapio;

//Estrura para item do pedido do cliente
typedef struct {
    char nomeItem[MAX_CHAR];   //Nome do item
    int quantidadeItem;        //Quantidade do item
    char tamanhoItem;          //Tamanho do item 'P', 'M' ou 'G'
    double preco;              //Preço do item considerando seu tamanho
}item_do_pedido;


//Estrutura para pedido do cliente
typedef struct {
    char cpf[11];               //CPF do cliente
    int codigo;                 //Codigo do pedido
    int numItens;               //Numero de itens do pedido
    item_do_pedido itens[50];   //Vetor de itens do pedido
    int prox;                   //Proximo pedido da lista
    char atendido;              //Flag de pedido atendido 'S' ou 'N'
    char excluido;              //Flag de pedido excluido 'S' ou 'N'
    double total_pedido;        //Valor total do pedido
} pedido_cliente;

/* Cria uma lista nova em arquivo
*  Pre-Condicao: Arquivo aberto para leitura/escrita
*  Pos-Condicao: Arquivo é inicializado com uma lista vazia
*/
void cria_lista_vazia(FILE* arq);


/* Lê o cabeçalho do arquivo contendo as informações da lista
*  Pre-Condicao: Arquivo deve estar aberto e ser um arquivo de lista
*  Pos-Condicao: Retorna o ponteiro para o cabeçalho lido
*/
cabecalho* le_cabecalho(FILE * arq);


/* Escreve no arquivo o cabeçalho contendo as informações da lista
*  Pre-Condicao: Arquivo deve estar aberto e ser um arquivo de lista
*  Pos-Condicao: Cabeçalho escrito no arquivo
*/
void escreve_cabecalho(FILE* arq, cabecalho* cab);


/* Lê um no da lista de itens do cardápio
*  Pre-Condicao: Arquivo deve estar aberto e ser um arquivo de lista válida, pos deve ser uma posição válida
*  Pos-Condicao: Ponteiro para item do cardápio lido é retornado
*/
no_item_cardapio* le_no(FILE* arq, int pos);


/* Escreve um nó de item do cardápio na posição fornecida
*  Pre-Condicao: Arquivo deve estar aberto e ser um arquivo de lista, pos deve ser uma posição válida
*  Pos-Condicao: Nó é escrito na lista de itens
*/
void escreve_no(FILE* arq, no_item_cardapio* x, int pos);


/* Insere um item na lista de itens do cardápio
*  Pre-Condicao: Arquivo deve estar aberto e ser um arquivo de lista, info deve ser do tipo no_item_cardapio com informações válidas
*  Pos-Condicao: Insere o item na lista de itens do cardápio
*/
void insere(FILE* arq, no_item_cardapio info);


/* Insere um pedido na lista de pedidos
*  Pre-Condicao: Arquivo de pedidos deve estar aberto, info deve ser do tipo pedido_cliente e ter informaçoes válidas
*  Pos-Condicao: O pedido é inserido na lista de pedidos
*/
void insere_pedido(FILE* arq, pedido_cliente info);


/* Escreve um nó de pedido na posição fornecida
*  Pre-Condicao: Arquivo de pedidos deve estar aberto, pos deve ser uma posição válida
*  Pos-Condicao: Nó é escrito na lista de pedidos
*/
void escreve_no_Pedido(FILE* arq, pedido_cliente* x, int pos);


/* Lê um no da lista de pedidos
*  Pre-Condicao: Arquivo de pedidos deve estar aberto, pos deve ser uma posição válida
*  Pos-Condicao: Ponteiro para o pedido é retornado
*/
pedido_cliente* le_no_Pedido(FILE* arq, int pos);

#endif // LISTAENCADEADA_H_INCLUDED
