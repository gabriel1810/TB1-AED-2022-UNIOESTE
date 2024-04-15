#ifndef BURGERTI_H_INCLUDED
#define BURGERTI_H_INCLUDED
#include "ListaEncadeada.h"
#include "BurgerTI.h"
#include "Utilidades.h"


/* Realiza operações para tratar uma linha recebida do arquivo de dados caso a opçao "Ler arquivo" seja selecionada no menu principal
*  Pré-Condição: String contendo uma linha com informações de pedidos ou itens
*  Pós-Condição: Retorna um objeto do tipo no_item_cardapio com as informações que tinham na string
*/
no_item_cardapio trataLinhaArquivo(char str[]);


/* Exibe as informações de pedidos passados e faz o passo a passo de registrar um novo pedido, auxiliar de {void exibirMenuCadastroItem(FILE* arqItens)}
*  Pré-Condição: Arquivos de Pedidos e de Itens abertos e do tipo lista
*  Pós-Condição: Registra o novo pedido no arquivo de Pedidos
*/
void exibirMenuRegistrarNovoPedido(FILE* arqPedidos, FILE* arqItens);


/* Função que imprime os itens cadastrados no arquivo de Itens
*  Pré-Condição: Arquivo de Itens aberto e do tipo lista
*  Pós-Condição: Exibe as informações que o usuário escolher da lista de itens
*/
void exibirMenuImprimeItem(FILE* arqItens);


/* Menu principal de cadastro de itens, aqui o usuário escolhe qual o tipo de item que deseja cadastrar 
*  Pré-Condição: Arquivo de Itens deve estar aberto e ser do tipo Lista
*  Pós-Condição: Redireciona para função de adicionar itens na Lista e mostra o que foi adicionado na tela
*/
void exibirMenuCadastroItem(FILE* arqItens);


/* Menu principal do programa, caso não tenha nada cadastrado nos arquivos só mostra a opção de Inserir, caso seja a primeira inserção cria o cabeçalho no arquivo
*  Pré-Condição: Ponteiro para flag que informará para a função se ela deve ou não criar o cabeçalho nos arquivos, arquivos de Itens e Pedidos do tipo lista
*  Pós-Condição: Retorna a opção escolhida pelo usuário (Cadastrar, visualizar ou remover)
*/
int exibirMenuPrincipal(int *cria_cab,FILE* arqItens, FILE* arqPedidos);


/* Irá ler o arquivo informado pelo usuário, irá redirecionar para a função de tratamento de linha e fará as inserções nos respectivos arquivos
*  Pré-Condição: Arquivos de itens e pedidos abertos e do tipo lista
*  Pós-Condição: Caso encontre o arquivo especificado pelo usuário, fará as inserções nas listas
*/
void lerArquivoUsuario(FILE *arqItens, FILE* arqPedidos, int *cria_cab);


/* Menu que exibirá para o usuário as informações sobre os pedidos cadastrados
*  Pré-Condição: Arquivo de pedidos aberto e do tipo lista
*  Pós-Condição: Exibe na tela as informações requisitadas pelo usuário
*/
void exibirMenuImprimirPedido(FILE* arqPedidos);


/* Muda a flag atendido para 'S' do primeiro pedido da lista que ainda não foi atendido
*  Pré-Condição: Arquivo de pedidos aberto e do tipo lista
*  Pós-Condição: Muda o status do pedido que é o proximo na fila para atendido
*/
void atenderPedido(FILE* arqPedidos);


/* Faz a remoção lógica do ultimo pedido do cliente cujo cpf seja o mesmo do especificado
*  Pré-Condição: Arquivo de pedidos aberto e do tipo lista
*  Pós-Condição: Realiza a remoção lógica
*/
void removerPedido(FILE* arqPedidos);

#endif // BURGERTI_H_INCLUDED
