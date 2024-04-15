#include <locale.h>
#include "BurgerTI.h"
#include "ListaEncadeada.h"
#include "Utilidades.h"

int main() {
  setlocale(LC_ALL, "Portuguese");    //Para trabalhar com numeros com virgula 
  int opcaoMenuPrincipal = 0;
  int cria_cab = 0;       //Flag que define se será preciso criar o cabeçalho no arquivo
  FILE *arqItens;
  FILE *arqPedidos;

  //Tenta abrir em modo leitura, caso já existam
  arqItens = fopen("arqDadosItens.bin","rb+");
  arqPedidos = fopen("arqDadosPedidos.bin","rb+");

  //Senão abre em modo escrita e seta a flag para criar cabeçalho
  if(arqItens == NULL){
    arqItens = fopen("arqDadosItens.bin","wb+");
    cria_cab = 1;
  }

  if(arqPedidos == NULL){
    arqPedidos = fopen("arqDadosPedidos.bin","wb+");
    cria_cab = 1;
  }

  //Caso o arquivo seja vazio 
  if(testa_tam_arquivo(arqItens) == 0) cria_cab = 1;
  if(testa_tam_arquivo(arqPedidos) == 0) cria_cab = 1;

  do{
    opcaoMenuPrincipal = exibirMenuPrincipal(&cria_cab,arqItens,arqPedidos);

    switch (opcaoMenuPrincipal)
    {
        case 1: {
            int opt;
            system("cls");
            printf("[1] - Cadastrar Item do cardapio\n");
            printf("[2] - Cadastrar Pedido (Somente se existirem itens cadastrados)\n");
            printf("[3] - Ler arquivo\n");
            printf("\n[0] - Voltar");
            printf("\n\nOpcao: ");
            scanf("%d", &opt);
            if(opt == 1) exibirMenuCadastroItem(arqItens);
            else if(opt == 2) exibirMenuRegistrarNovoPedido(arqPedidos,arqItens);
            else if(opt == 3) lerArquivoUsuario(arqItens,arqPedidos,&cria_cab);
            else break;
        }break;

        case 2: {
            int opt;
            system("cls");
            printf("[1] - Exibir itens do cardapio\n");
            printf("[2] - Exibir pedidos\n");
            printf("[3] - Exibir pedidos atendidos\n");
            printf("[4] - Exibir pedidos nao atendidos\n");
            printf("\n[0] - Voltar");
            printf("\n\nOpcao: ");
            scanf("%d", &opt);
            if(opt == 1) exibirMenuImprimeItem(arqItens);
            else if(opt == 2) exibirMenuImprimirPedido(arqPedidos);
            else if(opt == 3) exibirPedidosAtendidos(arqPedidos,1);
            else if(opt == 4) exibirPedidosAtendidos(arqPedidos,0);
            else break;
        }break;

        case 3: {
            int opt;
            system("cls");
            printf("[1] - Atender primeiro pedido da fila\n");
            printf("[2] - Desistir do pedido\n");
            printf("\n[0] - Voltar");
            printf("\n\nOpcao: ");
            scanf("%d", &opt);
            if(opt == 1) atenderPedido(arqPedidos);
            else if(opt == 2) removerPedido(arqPedidos);
            else break;
        }break;

        case 0: break;

        default: printf("Opcao invalida\n"); break;
    }

  }while (opcaoMenuPrincipal != 0);

  fclose(arqItens);
  return 0;
}