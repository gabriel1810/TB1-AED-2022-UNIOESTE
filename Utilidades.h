#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED
#include "ListaEncadeada.h"

/* Mostra as informações de um determinado item do cardápio
*  Pré-Condição: x deve ser um ponteiro válido e do tipo no_item_cardapio
*  Pós-Condição: As informações contidas em x são mostradas na tela
*/
void showInfo(no_item_cardapio* x);


/* Passo a passo para cadastrar qualquer item do cardápio, 1->SD, 2->BB, 3->SM, 4->EX
*  Pré-Condição: x deve ser do tipo no_item_cardapio, opt deve ser um valor entre 1 e 4
*  Pós-Condição: Retorna um nó do tipo no_item_cardápio populado para ser inserido
*/
no_item_cardapio CadastroNovoItem(no_item_cardapio x, int opt);


/* Caso o valor opt seja 1 mostra os pedidos atendidos, caso seja 0 mostra os pedidos não atendidos
*  Pré-Condição: Arquivo de pedidos deve estar aberto, opt deve ter valor 0 ou 1
*  Pós-Condição: Exibe os pedidos na tela, conforme especificado por opt
*/
void exibirPedidosAtendidos(FILE* arqPedidos, int opt);


/* Testa o tamanho do arquivo fp
*  Pré-Condição: Arquivo deve existir e estar aberto
*  Pós-Condição: Retorna 0 caso o tamanho do arquivo é 0, senão retorna 1
*/
int testa_tam_arquivo(FILE* fp);

#endif // UTILIDADES_H_INCLUDED
