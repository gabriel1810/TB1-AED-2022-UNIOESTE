#include "BurgerTI.h"
#include "Utilidades.h"
#include "ListaEncadeada.h"


/* Realiza operações para tratar uma linha recebida do arquivo de dados caso a opçao "Ler arquivo" seja selecionada no menu principal
*  Pré-Condição: String contendo uma linha com informações de pedidos ou itens
*  Pós-Condição: Retorna um objeto do tipo no_item_cardapio com as informações que tinham na string
*/
no_item_cardapio trataLinhaArquivo(char str[]){
  setlocale(LC_ALL, "Portuguese");
  char * pch;
  int i = 0;
  int bool_BB = 0;
  char dados[8][MAX_CHAR];
  no_item_cardapio x;

  //Separa a string nos ';'
  pch = strtok(str,";");
  while(pch != NULL){
    strcpy(dados[i++],pch);
    pch = strtok (NULL, ";");
  }

  /*Esses 3 são iguais para todos*/
  strcpy(x.tipo,dados[0]);
  x.codigo = atoi(dados[1]);
  strcpy(x.nome, dados[2]);

  //Definição do preço para o sanduiche e bebida, e defini��o da descri��o caso seja Sanduiche
  if(strcmp(x.tipo,"BB") == 0 || strcmp(x.tipo,"SD") == 0){
    if (strcmp(x.tipo,"SD") == 0){
        strcpy(x.descricao,dados[3]);
        x.disponivel = dados[4][0];
    }

    if (strcmp(x.tipo,"BB") == 0) bool_BB = 1;

    //Converte pra float e guarda os dados
    x.precos[0] = atof(dados[5-bool_BB]);
    x.precos[1] = atof(dados[6-bool_BB]);
    x.precos[2] = atof(dados[7-bool_BB]);
  }
    //Caso não seja Sanduiche, a flag disponivel fica na 3a posição
  if (strcmp(x.tipo,"SD") != 0){
     x.disponivel = dados[3][0];
     //Caso não seja Sanduiche ou Bebida só tem 1 preço
     if(strcmp(x.tipo,"BB") != 0){
        dados[4][strlen(dados[4])-3] = '.';
        x.precos[0] = atof(dados[4]);
        x.precos[1] = 0.0;
        x.precos[2] = 0.0;
     }
  }

    return x;
}

/* Exibe as informações de pedidos passados e faz o passo a passo de registrar um novo pedido, auxiliar de {void exibirMenuCadastroItem(FILE* arqItens)}
*  Pré-Condição: Arquivos de Pedidos e de Itens abertos e do tipo lista
*  Pós-Condição: Registra o novo pedido no arquivo de Pedidos
*/
void exibirMenuRegistrarNovoPedido(FILE* arqPedidos, FILE* arqItens){
    setlocale(LC_ALL, "Portuguese");
    CLEAR_SCREEN
    pedido_cliente* x ;
    cabecalho* cab = le_cabecalho(arqPedidos);
    pedido_cliente vet[3];  //Vetor com os 3 ultimos pedidos do cliente
    int opt = 0;
    int numPedidosPassados = 0;
    char cpf[13];
    printf("Informe o CPF: ");
    scanf("%s",cpf);
    printf("\nSeus ultimos 3 pedidos foram: \n");

    //Salva os 3 ultimos pedidos no vetor de pedidos passados
    for(int i = cab->pos_topo; i >= 0; i--){
        x = le_no_Pedido(arqPedidos,i);
        if(strcmp(x->cpf,cpf) == 0){
            vet[numPedidosPassados++] = *x;
        }
        if(numPedidosPassados == 3) break;
    }

    //Exibe o conteudo do vetor de pedidos passados
    for(int i = 0; i < numPedidosPassados;i++){
        printf("\n[%d]\n",i+1);
        printf("NOME DO ITEM    |    QUANTIDADE    | TAMANHO\n");
        for(int j = 0; j < vet[i].numItens; j++){
            printf("%-25s  %-10d",vet[i].itens[j].nomeItem,vet[i].itens[j].quantidadeItem);
            if(vet[i].itens[j].tamanhoItem != 'z') printf("  %c",vet[i].itens[j].tamanhoItem);
            printf("\n");
        }
    }

    //Opções referentes a realizar o mesmo pedido novamente
    if(numPedidosPassados == 0) printf("Nao existem pedidos anteriores para este cpf\n");
    if(numPedidosPassados > 0) printf("[%d] - Realizar pedido %d novamente\n",1,1);
    if(numPedidosPassados > 1) printf("[%d] - Realizar pedido %d novamente\n",2,2);
    if(numPedidosPassados > 2) printf("[%d] - Realizar pedido %d novamente\n",3,3);
    printf("[%d] - Novo pedido\n",4);

    printf("Opcao: ");
    scanf("%d",&opt);

    switch (opt){
        case 1: //Realizar pedido 2 novamente
        {
            if(numPedidosPassados > 0){
                vet[0].codigo = cab->pos_topo;
                insere_pedido(arqPedidos,vet[0]);
            }
            else { printf("Nao existem pedidos anteriores\n"); system("pause");}
        }break;

        case 2: //Realizar pedido 2 novamente
        {
            if(numPedidosPassados > 1){
                vet[1].codigo = cab->pos_topo;
                insere_pedido(arqPedidos,vet[1]);
            }
            else { printf("Nao existe esse pedido\n"); system("pause");}
        }break;

        case 3: //Realizar pedido 3 novamente
        {
            if(numPedidosPassados > 2){
                vet[2].codigo = cab->pos_topo;
                insere_pedido(arqPedidos,vet[2]);
            }
            else { printf("Nao existe esse pedido\n"); system("pause");}
        }break;

        case 4: //Realizar novo pedido
        {
            int escolhaMenu;
            pedido_cliente aux;
            strcpy(aux.cpf,cpf);
            aux.codigo = cab->pos_topo;
            aux.numItens = 0;

            do{
                printf("O que deseja adicionar ao pedido?\n");
                printf("[1] - Sanduiche\n");
                printf("[2] - Bebida\n");
                printf("[3] - Extra\n");
                printf("[4] - Sobremesa\n");
                printf("\n[0] - Finalizar pedido\n");
                printf("[-1] - Cancelar pedido\n");
                printf("\nEscolha: ");
                scanf("%d",&escolhaMenu);

                switch (escolhaMenu){
                    case 1: {
                        aux.numItens++;
                        cabecalho* cab_item = le_cabecalho(arqItens);
                        no_item_cardapio* item;
                        int codigoProduto;
                        printf("Qual sanduiche deseja adicionar ao pedido?\n");
                        printf("Codigo | Nome\n");

                        //Exibe os Sanduiches disponiveis já cadastrados
                        for(int i =0; i < cab_item->pos_topo; i++){
                            item = le_no(arqItens,i);
                            if(item->disponivel == 'D' && strcmp(item->tipo,"SD") == 0)
                                printf("%-10d %s\n",item->codigo,item->nome);
                        }
                        printf("Codigo do produto: ");
                        scanf("%d",&codigoProduto);

                        //Procura pelo item selecionado
                        for(int j =0; j < cab_item->pos_topo;j++){
                            item = le_no(arqItens,j);
                            if(strcmp(item->tipo,"SD") == 0 && item->codigo == codigoProduto) break;
                        }

                        //Salva as informaçoes do pedido em aux
                        strcpy(aux.itens[aux.numItens-1].nomeItem, item->nome);
                        printf("\nQuantidade de %s: ",item->nome);
                        scanf("%d%*c",&aux.itens[aux.numItens-1].quantidadeItem);
                        printf("\nTamanho do %s (P/M/G): ",item->nome);
                        scanf("%c",&aux.itens[aux.numItens-1].tamanhoItem);
                        if(aux.itens[aux.numItens-1].tamanhoItem == 'P' || aux.itens[aux.numItens-1].tamanhoItem == 'p') aux.itens[aux.numItens-1].preco = item->precos[0];
                        else if(aux.itens[aux.numItens-1].tamanhoItem == 'M' || aux.itens[aux.numItens-1].tamanhoItem == 'm') aux.itens[aux.numItens-1].preco = item->precos[1];
                        else if(aux.itens[aux.numItens-1].tamanhoItem == 'G' || aux.itens[aux.numItens-1].tamanhoItem == 'g') aux.itens[aux.numItens-1].preco = item->precos[2];
                    } break;

                    case 2: {
                        aux.numItens++;
                        cabecalho* cab_item = le_cabecalho(arqItens);
                        no_item_cardapio* item;
                        int codigoProduto;
                        printf("Qual Bebida deseja adicionar ao pedido?\n");
                        printf("Codigo | Nome\n");

                        //Exibe as bebidas disponiveis
                        for(int i =0; i < cab_item->pos_topo; i++){
                            item = le_no(arqItens,i);
                            if(item->disponivel == 'D' && strcmp(item->tipo,"BB") == 0)
                                printf("%-10d %s\n",item->codigo,item->nome);
                        }
                        printf("Codigo do produto: ");
                        scanf("%d",&codigoProduto);

                        //Procura pelo item selecionado
                        for(int j =0; j < cab_item->pos_topo;j++){
                            item = le_no(arqItens,j);
                            if(strcmp(item->tipo,"BB") == 0 && item->codigo == codigoProduto) break;
                        }
                        
                        //Salva as informaçoes do pedido em aux
                        strcpy(aux.itens[aux.numItens-1].nomeItem, item->nome);
                        printf("\nQuantidade de %s: ",item->nome);
                        scanf("%d%*c",&aux.itens[aux.numItens-1].quantidadeItem);
                        printf("\nTamanho do %s (P/M/G): ",item->nome);
                        scanf("%c",&aux.itens[aux.numItens-1].tamanhoItem);
                        if(aux.itens[aux.numItens-1].tamanhoItem == 'P' || aux.itens[aux.numItens-1].tamanhoItem == 'p') aux.itens[aux.numItens-1].preco = item->precos[0];
                        else if(aux.itens[aux.numItens-1].tamanhoItem == 'M' || aux.itens[aux.numItens-1].tamanhoItem == 'm') aux.itens[aux.numItens-1].preco = item->precos[1];
                        else if(aux.itens[aux.numItens-1].tamanhoItem == 'G' || aux.itens[aux.numItens-1].tamanhoItem == 'g') aux.itens[aux.numItens-1].preco = item->precos[2];
                    } break;

                    case 3: {
                        aux.numItens++;
                        cabecalho* cab_item = le_cabecalho(arqItens);
                        no_item_cardapio* item;
                        int codigoProduto;
                        printf("Qual Extra deseja adicionar ao pedido?\n");
                        printf("Codigo | Nome\n");

                        //Exibe os Extras disponiveis
                        for(int i =0; i < cab_item->pos_topo; i++){
                            item = le_no(arqItens,i);
                            if(item->disponivel == 'D' && strcmp(item->tipo,"EX") == 0)
                                printf("%-10d %s\n",item->codigo,item->nome);
                        }
                        printf("Codigo do produto: ");
                        scanf("%d",&codigoProduto);

                        //Procura pelo item selecionado
                        for(int j =0; j < cab_item->pos_topo;j++){
                            item = le_no(arqItens,j);
                            if(strcmp(item->tipo,"EX") == 0 && item->codigo == codigoProduto) break;
                        }

                        //Salva as informaçoes do pedido em aux
                        strcpy(aux.itens[aux.numItens-1].nomeItem, item->nome);
                        printf("\nQuantidade de %s: ",item->nome);
                        scanf("%d%*c",&aux.itens[aux.numItens-1].quantidadeItem);
                        aux.itens[aux.numItens-1].tamanhoItem = 'z';
                        aux.itens[aux.numItens-1].preco = item->precos[0];
                    } break;

                    case 4: {
                        aux.numItens++;
                        cabecalho* cab_item = le_cabecalho(arqItens);
                        no_item_cardapio* item;
                        int codigoProduto;
                        printf("Qual sobremesa deseja adicionar ao pedido?\n");
                        printf("Codigo | Nome\n");

                        //Exibe as sobremesas disponiveis
                        for(int i =0; i < cab_item->pos_topo; i++){
                            item = le_no(arqItens,i);
                            if(item->disponivel == 'D' && strcmp(item->tipo,"SM") == 0)
                                printf("%-10d %s\n",item->codigo,item->nome);
                        }
                        printf("Codigo do produto: ");
                        scanf("%d",&codigoProduto);

                        //Procura pelo item selecionado
                        for(int j =0; j < cab_item->pos_topo;j++){
                            item = le_no(arqItens,j);
                            if(strcmp(item->tipo,"SM") == 0 && item->codigo == codigoProduto) break;
                        }

                        //Salva as informaçoes do pedido em aux
                        strcpy(aux.itens[aux.numItens-1].nomeItem, item->nome);
                        printf("\nQuantidade de %s: ",item->nome);
                        scanf("%d%*c",&aux.itens[aux.numItens-1].quantidadeItem);
                        aux.itens[aux.numItens-1].tamanhoItem = 'z';
                        aux.itens[aux.numItens-1].preco = item->precos[0];
                    } break;
                }
            } while(escolhaMenu != 0 && escolhaMenu != -1);
                if( escolhaMenu == 0){
                    //No fim, finaliza e insere o pedido na lista de pedidos
                    insere_pedido(arqPedidos,aux);
                    printf("\nPedido inserido com sucesso!\n");
                }
             if( escolhaMenu == -1) break;
    }
    }
}

/* Função que imprime os itens cadastrados no arquivo de Itens
*  Pré-Condição: Arquivo de Itens aberto e do tipo lista
*  Pós-Condição: Exibe as informações que o usuário escolher da lista de itens
*/
void exibirMenuImprimeItem(FILE * arqItens){
    setlocale(LC_ALL, "Portuguese");
    CLEAR_SCREEN
    no_item_cardapio* x ;
    cabecalho* cab = le_cabecalho(arqItens);
    int tamLista = cab->pos_topo;
    int opt = 0;
    do{
        printf("[1] Imprimir lista de Sanduiches\n");
        printf("[2] Imprimir lista de Bebidas\n");
        printf("[3] Imprimir lista de sobremesas\n");
        printf("[4] Imprimir lista de extras\n");
        printf("[5] Imprimir tudo\n");
        printf("\n[0] Voltar para o menu principal");
        printf("\n\nOpcao: ");
        scanf("%d", &opt);

        switch (opt){
            case 1 :{ //Mostra todos os Sanduiches cadastrados no arquivo de Itens
                for(int i = 0; i < tamLista; i++){
                    x = le_no(arqItens,i);
                    if(strcmp(x->tipo,"SD")==0) showInfo(x);
                }
            } break;

            case 2 :{ //Mostra todas as Bebidas cadastrados no arquivo de Itens
                for(int i = 0; i < tamLista; i++){
                    x = le_no(arqItens,i);
                    if(strcmp(x->tipo,"BB")==0) showInfo(x);
                }
            } break;

             case 3 :{ //Mostra todas as Sobremesas cadastrados no arquivo de Itens
                for(int i = 0; i < tamLista; i++){
                    x = le_no(arqItens,i);
                    if(strcmp(x->tipo,"SM")==0) showInfo(x);
                }
            } break;

             case 4 :{ //Mostra todos os Extras cadastrados no arquivo de Itens
                for(int i = 0; i < tamLista; i++){
                    x = le_no(arqItens,i);
                    if(strcmp(x->tipo,"EX")==0) showInfo(x);
                }
            } break;

            case 5 :{  //Mostra tudo o que está no arquivos de itens
                for(int i = 0; i < tamLista; i++){
                    x = le_no(arqItens,i);
                    showInfo(x);
                }
            } break;

            default: printf("Opcao nao encontrada\n"); break;
        }

    } while (opt != 0);
}

/* Menu principal de cadastro de itens, aqui o usuário escolhe qual o tipo de item que deseja cadastrar 
*  Pré-Condição: Arquivo de Itens deve estar aberto e ser do tipo Lista
*  Pós-Condição: Redireciona para função de adicionar itens na Lista e mostra o que foi adicionado na tela
*/
void exibirMenuCadastroItem(FILE *arqItens){
    setlocale(LC_ALL, "Portuguese");
    CLEAR_SCREEN
    int opt = 0;
    do{
        printf("***\n");
        printf("[1] Cadastrar Sanduiche\n");
        printf("[2] Cadastrar Bebida\n");
        printf("[3] Cadastrar sobremesa\n");
        printf("[4] Cadastrar extra\n");
        printf("***\n");
        printf("\n[0] Voltar para o menu principal");
        printf("\n\nOpcao: ");
        scanf("%d", &opt);

        switch (opt){

        case 1: {
            no_item_cardapio x = CadastroNovoItem(x,1); //Pega os dados do sanduiche passo a passo da função 
            insere(arqItens,x);                         //Insere o novo item
            printf("Sanduiche Cadastrado!\n");
            printf("Dados: %s | %d | %s | %s | %.2lf | %.2lf | %.2lf\n",x.tipo,x.codigo,x.nome,x.descricao,x.precos[0],x.precos[1],x.precos[2]);
        } break;

        case 2: {
            no_item_cardapio x = CadastroNovoItem(x,2); //Pega os dados da bebida passo a passo da função 
            insere(arqItens,x);                         //Insere o novo item
            printf("Bebida Cadastrada!\n");
            printf("Dados: %s | %d | %s | %.2lf | %.2lf | %.2lf\n",x.tipo,x.codigo,x.nome,x.precos[0],x.precos[1],x.precos[2]);
        } break;

        case 3: {
            no_item_cardapio x = CadastroNovoItem(x,3); //Pega os dados da sobremesa passo a passo da função 
            insere(arqItens,x);                         //Insere o novo item
            printf("Sobremesa Cadastrada!\n");
            printf("Dados: %s | %d | %s | %.2lf\n",x.tipo,x.codigo,x.nome,x.precos[0]);
        } break;

        case 4: {
            no_item_cardapio x = CadastroNovoItem(x,4); //Pega os dados do extra passo a passo da função 
            insere(arqItens,x);                         //Insere o novo item
            printf("Extra Cadastrado!\n");
            printf("Dados: %s | %d | %s | %.2lf\n",x.tipo,x.codigo,x.nome,x.precos[0]);
        } break;

        }
    } while (opt != 0);
}

/* Menu que exibirá para o usuário as informações sobre os pedidos cadastrados
*  Pré-Condição: Arquivo de pedidos aberto e do tipo lista
*  Pós-Condição: Exibe na tela as informações requisitadas pelo usuário
*/
void exibirMenuImprimirPedido(FILE* arqPedidos){
    setlocale(LC_ALL, "Portuguese");
    CLEAR_SCREEN
    int opt;
    int codPedido;
    int encontrado = 0;
    pedido_cliente* x ;
    cabecalho* cab = le_cabecalho(arqPedidos);
    int tamLista = cab->pos_topo;
    printf("***\n");
    printf("[1] Por codigo\n");
    printf("[2] Imprimir todos\n");
    printf("\n[0] Voltar ao menu\n");
    printf("\n\nOpcao: ");
    scanf("%d", &opt);
    switch (opt){

    case 0: break;

        case 1: //Caso deseja exibir as informações de um determinado pedido especificado pelo código
            {
                printf("Informe o codigo: ");
                scanf("%d",&codPedido);
                int it=0;
                while(1){
                    x = le_no_Pedido(arqPedidos,it);  //Procura pelo código especifico na lista de Pedidos
                    if(x->codigo == codPedido && x->excluido != 'S'){
                            encontrado = 1;     //Caso seja encontrado
                            break;
                    }
                    if(it == tamLista){ //Caso percorra toda a lista e não encontre o código
                        printf("Codigo nao encontrado\n");
                        encontrado = 0;
                        break;
                    }
                    it++;
                }

                if(encontrado == 1){
                        printf("_________________\nCodigo: %d\n",x->codigo);
                        printf("CPF: %s\n",x->cpf);
                        printf("Atendido: %c\n",x->atendido);
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
                system("pause");
             } break;

        case 2: //Imprime todos os pedidos da lista de pedidos
            {
                for(int i = 0; i < tamLista; i++){
                    x = le_no_Pedido(arqPedidos,i);
                        if(x->excluido == 'N'){
                            printf("_________________\nCodigo: %d\n",x->codigo);
                            printf("CPF: %s\n",x->cpf);
                            printf("Atendido: %c\n",x->atendido);
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
            } break;
        default:{
            printf("Opcao nao encontrada\n");
            system("pause");
        } break;
    }
}

/* Menu principal do programa, caso não tenha nada cadastrado nos arquivos só mostra a opção de Inserir, caso seja a primeira inserção cria o cabeçalho no arquivo
*  Pré-Condição: Ponteiro para flag que informará para a função se ela deve ou não criar o cabeçalho nos arquivos, arquivos de Itens e Pedidos do tipo lista
*  Pós-Condição: Retorna a opção escolhida pelo usuário (Cadastrar, visualizar ou remover)
*/
int exibirMenuPrincipal(int *cria_cab,FILE* arqItens, FILE* arqPedidos){
    setlocale(LC_ALL, "Portuguese");
    CLEAR_SCREEN
    int opt;
    printf("Opcoes disponiveis:\n");
    printf("[1] - Cadastrar\n");
    if(*cria_cab == 0){                 //Só mostra isso se já existir itens cadastrados
        printf("[2] - Visualizar\n");
        printf("[3] - Remover\n");
    }
    printf("\n[0] - Sair");
    printf("\n\nOpcao: ");
    scanf("%d", &opt);
    if(opt == 1){
        if(*cria_cab == 1){             //Caso o usuário tenha o desejo de cadastrar algo seja pedido ou item, deve ser criado os cabeçalhos nos arquivos
            cria_lista_vazia(arqItens);
            cria_lista_vazia(arqPedidos);
            *cria_cab = 0;
        }
    }

    return opt;
}

/* Irá ler o arquivo informado pelo usuário, irá redirecionar para a função de tratamento de linha e fará as inserções nos respectivos arquivos
*  Pré-Condição: Arquivos de itens e pedidos abertos e do tipo lista
*  Pós-Condição: Caso encontre o arquivo especificado pelo usuário, fará as inserções nas listas
*/
void lerArquivoUsuario(FILE *arqItens, FILE* arqPedidos, int *cria_cab){
    setlocale(LC_ALL, "Portuguese");
    char nomeArquivo[MAX_CHAR];         //Caminho do arquivo no sistema
    char linhaArquivo[MAX_CHAR];        //Cada linha do arquivo
    char dados[MAX_CHAR][MAX_CHAR];
    FILE *arq;
    char *pch;
    int tamPedidoLinha = 0;             //Quantidade de itens no pedido
    printf("Informe o nome do arquivo: ");
    scanf("%s",nomeArquivo);
    arq = fopen(nomeArquivo,"r");

    if(arq == NULL){
        printf("Arquivo nao encontrado\n");
        *cria_cab = 1;
    }

    else if(arq != NULL){
        while(fgets(linhaArquivo,MAX_CHAR,arq) != NULL){
            if (linhaArquivo[strlen(linhaArquivo)-1] == '\n')
                linhaArquivo[strlen(linhaArquivo)-1] = '\0';
            if(linhaArquivo[0] != 'P'){
                no_item_cardapio aux = trataLinhaArquivo(linhaArquivo);
                insere(arqItens,aux);
            }
            else if(linhaArquivo[0] == 'P' && linhaArquivo[1] == 'D'){
                tamPedidoLinha = 0;
                int k = 0;
                pch = strtok(linhaArquivo,";");
                while(pch != NULL){
                    strcpy(dados[k++],pch);
                    tamPedidoLinha++;
                    pch = strtok (NULL, ";");
                }

                pedido_cliente aux;
                aux.codigo = atoi(dados[1]);
                strcpy(aux.cpf,dados[2]);
                aux.numItens = tamPedidoLinha-3;

                int pos = 0;
                for(int i = 3; i < tamPedidoLinha; i++){
                    char str[MAX_CHAR];
                    strcpy(str,dados[i]);
                    char *pt;
                    char tamanhoItem[2] = "z";
                    no_item_cardapio* no;
                    if (str[0] == '(') memmove(str, str+1, strlen(str));
                    str[strlen(str)-1] = '\0';

                    pt = strtok(str,",");
                    char tipo[3];
                    strcpy(tipo,pt);

                    pt = strtok (NULL, ",");
                    int codigoItem = atoi(pt);

                    pt = strtok (NULL, ",");
                    int qntItens = atoi(pt);

                    if(strcmp(tipo,"SD") == 0 || strcmp(tipo,"BB") == 0){
                        pt = strtok (NULL, ",");
                        tamanhoItem[0] = pt[0];
                    }
                    int it = 0;
                    while(1){
                        no = le_no(arqItens,it);
                        it++;
                        if(no->codigo == codigoItem && strcmp(no->tipo,tipo) == 0) break;
                    }

                    strcpy(aux.itens[pos].nomeItem,no->nome);
                    aux.itens[pos].quantidadeItem = qntItens;
                    aux.itens[pos].tamanhoItem = tamanhoItem[0];
                    if(aux.itens[pos].tamanhoItem == 'z' || aux.itens[pos].tamanhoItem == 'Z' || aux.itens[pos].tamanhoItem == 'P' || aux.itens[pos].tamanhoItem == 'p'){
                        aux.itens[pos].preco = no->precos[0];
                    }
                    else if (aux.itens[pos].tamanhoItem == 'M' || aux.itens[pos].tamanhoItem == 'm'){
                        aux.itens[pos].preco = no->precos[1];
                    }
                    else if(aux.itens[pos].tamanhoItem == 'G' || aux.itens[pos].tamanhoItem == 'g'){
                        aux.itens[pos].preco = no->precos[2];
                    }
                    pos++;
                }
                insere_pedido(arqPedidos,aux);
            }
        }
     printf("Arquivo lido com sucesso!\n");
    }

    system("pause");
    fclose(arq);
}

/* Muda a flag atendido para 'S' do primeiro pedido da lista que ainda não foi atendido
*  Pré-Condição: Arquivo de pedidos aberto e do tipo lista
*  Pós-Condição: Muda o status do pedido que é o proximo na fila para atendido
*/
void atenderPedido(FILE* arqPedidos){
    setlocale(LC_ALL, "Portuguese");
    cabecalho* cab = le_cabecalho(arqPedidos);
    pedido_cliente* x;
    int achado = 0;
    if(cab != NULL && cab->pos_topo > 0){
        for(int i = 0; i < cab->pos_topo;i++){
            if(i == cab->pos_topo){
                printf("Nao existem pedidos na fila\n");
                break;
            }
            x = le_no_Pedido(arqPedidos,i);
            if(x->atendido == 'N' && x->excluido == 'N'){
                x->atendido = 'S';
                escreve_no_Pedido(arqPedidos,x,i);
                achado = 1;
                break;
            }
    }
    if(achado == 1) printf("Pedido %d atendido com sucesso!\n",x->codigo);
    else if(achado == 0)printf("Nao existem pedidos na fila\n");
    }

    else printf("Nao existem pedidos na fila\n");
    system("pause");
    
}

/* Faz a remoção lógica do ultimo pedido do cliente cujo cpf seja o mesmo do especificado
*  Pré-Condição: Arquivo de pedidos aberto e do tipo lista
*  Pós-Condição: Realiza a remoção lógica
*/
void removerPedido(FILE* arqPedidos){
    setlocale(LC_ALL, "Portuguese");
    cabecalho* cab = le_cabecalho(arqPedidos);
    pedido_cliente* x;
    char cpf[12];
    printf("Informe o cpf cadastrado no pedido: ");
    scanf("%s",cpf);
    for(int i = cab->pos_topo; i >= 0 ;i--){
            x = le_no_Pedido(arqPedidos,i);
            if(strcmp(x->cpf,cpf) == 0){
                x->excluido = 'S';
                escreve_no_Pedido(arqPedidos,x,i);
                break;
            }
        }
    printf("\nPedido numero %d com cpf %s removido com sucesso! \n",x->codigo,x->cpf);
    system("pause");
}
