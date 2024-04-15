#include "ListaEncadeada.h"

/* Escreve no arquivo o cabeçalho contendo as informações da lista
*  Pre-Condicao: Arquivo deve estar aberto e ser um arquivo de lista
*  Pos-Condicao: Cabeçalho escrito no arquivo
*/
void escreve_cabecalho(FILE* arq, cabecalho* cab){
    fseek(arq,0,SEEK_SET);
    fwrite(cab,sizeof(cabecalho),1,arq);
}

/* Lê o cabeçalho do arquivo contendo as informações da lista
*  Pre-Condicao: Arquivo deve estar aberto e ser um arquivo de lista
*  Pos-Condicao: Retorna o ponteiro para o cabeçalho lido
*/
cabecalho* le_cabecalho(FILE * arq) {
    cabecalho * cab = (cabecalho*) malloc(sizeof(cabecalho));
    fseek(arq,0,SEEK_SET);
    fread(cab,sizeof(cabecalho),1,arq);
    return cab;
}

/* Lê um no da lista de itens do cardápio
*  Pre-Condicao: Arquivo deve estar aberto e ser um arquivo de lista válida, pos deve ser uma posição válida
*  Pos-Condicao: Ponteiro para item do cardápio lido é retornado
*/
no_item_cardapio* le_no(FILE* arq, int pos) {
    no_item_cardapio* x = malloc(sizeof(no_item_cardapio));
    fseek(arq,sizeof(cabecalho)+ pos*sizeof(no_item_cardapio),SEEK_SET);
    fread(x,sizeof(no_item_cardapio),1,arq);
    return x;
}

/* Escreve um nó de item do cardápio na posição fornecida
*  Pre-Condicao: Arquivo deve estar aberto e ser um arquivo de lista, pos deve ser uma posição válida
*  Pos-Condicao: Nó é escrito na lista de itens
*/
void escreve_no(FILE* arq, no_item_cardapio* x, int pos){
    fseek(arq,sizeof(cabecalho)+ pos*sizeof(no_item_cardapio),SEEK_SET);
    fwrite(x,sizeof(no_item_cardapio),1,arq);
}

/* Cria uma lista nova em arquivo
*  Pre-Condicao: Arquivo aberto para leitura/escrita
*  Pos-Condicao: Arquivo é inicializado com uma lista vazia
*/
void cria_lista_vazia(FILE* arq){
    cabecalho * cab = (cabecalho*) malloc(sizeof(cabecalho));
    cab->pos_cabeca = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;
    escreve_cabecalho(arq,cab);
    free(cab);
}

/* Insere um item na lista de itens do cardápio
*  Pre-Condicao: Arquivo deve estar aberto e ser um arquivo de lista, info deve ser do tipo no_item_cardapio com informações válidas
*  Pos-Condicao: Insere o item na lista de itens do cardápio
*/
void insere(FILE* arq, no_item_cardapio info){
    cabecalho* cab = le_cabecalho(arq);
    no_item_cardapio x;

    x.codigo = info.codigo;
    strcpy(x.tipo,info.tipo);
    strcpy(x.nome,info.nome);
    x.disponivel = info.disponivel;
    x.precos[0] = info.precos[0];

    if(strcmp(info.tipo,"SD") == 0 || strcmp(info.tipo,"BB") == 0){
        x.precos[1] = info.precos[1];
        x.precos[2] = info.precos[2];
    }

    if(strcmp(info.tipo,"SD") == 0)
        strcpy(x.descricao,info.descricao);

    x.prox = cab->pos_cabeca;
    if(cab->pos_livre == -1) {
            escreve_no(arq,&x,cab->pos_topo);
            cab->pos_cabeca = cab->pos_topo;
            cab->pos_topo++;
    }
    else {
        no_item_cardapio* aux = le_no(arq,cab->pos_livre);
        escreve_no(arq,&x,cab->pos_livre);
        cab->pos_cabeca = cab->pos_livre;
        cab->pos_livre = aux->prox;
        free(aux);
        }
    escreve_cabecalho(arq,cab);
    free(cab);
}

/* Lê um no da lista de pedidos
*  Pre-Condicao: Arquivo de pedidos deve estar aberto, pos deve ser uma posição válida
*  Pos-Condicao: Ponteiro para o pedido é retornado
*/
pedido_cliente* le_no_Pedido(FILE* arq, int pos) {
    pedido_cliente* x = malloc(sizeof(pedido_cliente));
    fseek(arq,sizeof(cabecalho)+ pos*sizeof(pedido_cliente),SEEK_SET);
    fread(x,sizeof(pedido_cliente),1,arq);
    return x;
}

/* Escreve um nó de pedido na posição fornecida
*  Pre-Condicao: Arquivo de pedidos deve estar aberto, pos deve ser uma posição válida
*  Pos-Condicao: Nó é escrito na lista de pedidos
*/
void escreve_no_Pedido(FILE* arq, pedido_cliente* x, int pos){
    fseek(arq,sizeof(cabecalho)+ pos*sizeof(pedido_cliente),SEEK_SET);
    fwrite(x,sizeof(pedido_cliente),1,arq);
}

/* Insere um pedido na lista de pedidos
*  Pre-Condicao: Arquivo de pedidos deve estar aberto, info deve ser do tipo pedido_cliente e ter informaçoes válidas
*  Pos-Condicao: O pedido é inserido na lista de pedidos
*/
void insere_pedido(FILE* arq, pedido_cliente info){
    setlocale(LC_ALL, "Portuguese");
    cabecalho* cab = le_cabecalho(arq);
    pedido_cliente x;
    double total_pedido = 0;
    x.codigo = cab->pos_topo;
    //x.codigo = info.codigo;
    strcpy(x.cpf,info.cpf);
    x.numItens = info.numItens;
    x.atendido = 'N';
    x.excluido = 'N';
    for(int i = 0; i < info.numItens; i++){ 
        strcpy(x.itens[i].nomeItem,info.itens[i].nomeItem);
        x.itens[i].tamanhoItem = info.itens[i].tamanhoItem;
        x.itens[i].quantidadeItem = info.itens[i].quantidadeItem;
        total_pedido += (info.itens[i].preco * info.itens[i].quantidadeItem);
    }
    if(total_pedido == 0) x.total_pedido = info.total_pedido;
    else if(total_pedido > 0) x.total_pedido = total_pedido;

    x.prox = cab->pos_cabeca;
    if(cab->pos_livre == -1) {
            escreve_no_Pedido(arq,&x,cab->pos_topo);
            cab->pos_cabeca = cab->pos_topo;
            cab->pos_topo++;
    }
    else {
        pedido_cliente* aux = le_no_Pedido(arq,cab->pos_livre);
        escreve_no_Pedido(arq,&x,cab->pos_livre);
        cab->pos_cabeca = cab->pos_livre;
        cab->pos_livre = aux->prox;
        free(aux);
        }
    escreve_cabecalho(arq,cab);
    free(cab);
}
