#include "Utilidades.h"

/* Mostra as informações de um determinado item do cardápio
*  Pré-Condição: x deve ser um ponteiro válido e do tipo no_item_cardapio
*  Pós-Condição: As informações contidas em x são mostradas na tela
*/
void showInfo(no_item_cardapio* x){
  printf("Tipo: %s | ",x->tipo);
  printf("Codigo: %d | ",x->codigo);
  printf("Nome: %s\n",x->nome);
  if(strcmp(x->tipo,"SD") == 0) printf("Descricao: %s\n",x->descricao);
  printf("Disponivel: %c\n",x->disponivel);
  if(strcmp(x->tipo,"SD") == 0 || strcmp(x->tipo,"BB") == 0)printf("Precos| P:%0.2f, M:%0.2f, G:%0.2f\n\n",x->precos[0],x->precos[1],x->precos[2]);
  else printf("Precos| P:%0.2f\n\n",x->precos[0]);
}

/* Passo a passo para cadastrar qualquer item do cardápio, 1->SD, 2->BB, 3->SM, 4->EX
*  Pré-Condição: x deve ser do tipo no_item_cardapio, opt deve ser um valor entre 1 e 4
*  Pós-Condição: Retorna um nó do tipo no_item_cardápio populado para ser inserido
*/
no_item_cardapio CadastroNovoItem(no_item_cardapio x, int opt){
    if(opt == 1) strcpy(x.tipo,"SD");
    if(opt == 2) strcpy(x.tipo,"BB");
    if(opt == 3) strcpy(x.tipo,"SM");
    if(opt == 4) strcpy(x.tipo,"EX");

    printf("Codigo: ");
    scanf("%d%*c",&x.codigo);
    printf("\nNome: ");
    scanf("%[^\n]%*c", x.nome);

    if(opt == 1){
      printf("\nDescricao: ");
      scanf("%[^\n]%*c", x.descricao);
    }

    printf("\nDisponivel: ");
    scanf("%c%*c",&x.disponivel);

    printf("\nPreco P: ");
    scanf("%lf%*c",&x.precos[0]);

    if(opt == 1 || opt == 2){
      printf("\nPreco M: ");
      scanf("%lf%*c",&x.precos[1]);
      printf("\nPreco G: ");
      scanf("%lf%*c",&x.precos[2]);
    }
  return x;
}

/* Caso o valor opt seja 1 mostra os pedidos atendidos, caso seja 0 mostra os pedidos não atendidos
*  Pré-Condição: Arquivo de pedidos deve estar aberto, opt deve ter valor 0 ou 1
*  Pós-Condição: Exibe os pedidos na tela, conforme especificado por opt
*/
void exibirPedidosAtendidos(FILE* arqPedidos, int opt){
    setlocale(LC_ALL, "Portuguese");        //Para trabalhar com numeros com virgula
    printf("Lista de pedidos");
    if(opt == 0) printf(" nao");
    printf(" atendidos\n");
    char at = 'N';
    if(opt == 1) at = 'S';

    cabecalho* cab = le_cabecalho(arqPedidos);
    pedido_cliente* x;
    for(int i = 0; i < cab->pos_topo;i++){
        x = le_no_Pedido(arqPedidos,i);
        if(x->atendido == at && x->excluido == 'N'){
            printf("_________________\nCodigo: %d\n",x->codigo);
            printf("CPF: %s\n",x->cpf);
            printf("Total do Pedido: R$ %0.2lf\n",x->total_pedido);
            printf("Itens do pedido:\n");
            printf("NOME DO ITEM    |    QUANTIDADE    | TAMANHO\n");
            for(int j = 0; j < x->numItens;j++){
                printf("%-25s  %-10d",x->itens[j].nomeItem,x->itens[j].quantidadeItem);
                if(x->itens[j].tamanhoItem != 'z') printf("  %c",x->itens[j].tamanhoItem);
                printf("\n");
            }
            printf("\n_________________\n");
        }
    }
    system("pause");
}

/* Testa o tamanho do arquivo fp
*  Pré-Condição: Arquivo deve existir e estar aberto
*  Pós-Condição: Retorna 0 caso o tamanho do arquivo é 0, senão retorna 1
*/
int testa_tam_arquivo(FILE* fp){
 if(fp){
    fseek (fp, 0, SEEK_END);      //Vai ate o final do arquivo
    if(ftell(fp) == 0) return 0;  //Verifica o tamanho
    return 1;
  }
  return 0;
}
