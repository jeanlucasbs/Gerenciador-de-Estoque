#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_PRODUTO 100
#define MAX_CATEGORIA 50
#define MAX_NOME 40

typedef int TIPOCHAVE;

//Registro para os produtos
typedef struct {
	TIPOCHAVE chaveProduto;
	char nomeProduto[MAX_NOME];
	int quantidade;
	float valor;
} REGISTRO_PRODUTO;

// Registro para as categorias
typedef struct {
	TIPOCHAVE chaveCategoria;
	char nomeCategoria[MAX_NOME];
	
	REGISTRO_PRODUTO registroProduto[MAX_PRODUTO];
	int tamanhoListaProduto;
} REGISTRO_CATEGORIA;

// Definindo a lista
typedef struct {
	REGISTRO_CATEGORIA registroCategoria[MAX_CATEGORIA];
	int tamanhoListaCategoria;
} LISTA;


//Funções
void Titulo();
bool voltarOuRepetirOP(); 
int tamanho(LISTA* l);
void inicializarLista(LISTA* l);
bool cadastrarCategoria(LISTA *l, REGISTRO_CATEGORIA reg, int i);
bool cadastrarProduto(LISTA *l, int idCategoria, REGISTRO_PRODUTO reg);
int confereIDCategoria(LISTA *l);
bool excluirCategoria(LISTA *l, int idCategoria);
bool excluirProduto(LISTA* l, int idProduto);
void exibirCategorias(LISTA *l);
bool exibirTodosProdutos(LISTA *l);
bool buscarProduto(LISTA *l, TIPOCHAVE idProduto);
bool atualizarProduto(LISTA *l, int idTemPro); 


int main(){
  LISTA l;
  REGISTRO_PRODUTO regProduto;
  REGISTRO_CATEGORIA regCategoria;

  int delProd, delCat;
  int idTemCat, idTemPro, idBusca;
  int opcao;

  inicializarLista(&l);
  system("clear");

  setlocale(LC_ALL, "");

  //MENU PRINCIPAL
  do{
    Titulo();
    printf("OPERACOES:\n");
    printf(" 1 - Cadastrar produto\n");//ok
    printf(" 2 - Cadastrar categoria\n");//ok
    printf(" 3 - Deletar categoria\n");//ok
    printf(" 4 - Deletar produto\n");//ok
    printf(" 5 - Exibir categorias\n");//ok
    printf(" 6 - Exibir todos os produtos\n");//ok
    printf(" 7 - Buscar produto\n");//ok
    printf(" 8 - Atualizar produto\n");//ok
    printf(" 0 - Sair\n");//ok
    
    printf("Digite uma opcao: ");
    scanf("%d", &opcao);
    
    while(opcao < 0 || opcao > 8){
      printf("Opção inválida, digite novamente: ");
      scanf("%d", &opcao);
    }
    switch(opcao){
      case 1: //Cadastro de produtos
        while(true){
          /*Confere se existem categorias para cadastrar produtos. Caso não existe
          ele nao permite cadastrar o produto*/
          if(tamanho(&l) == 0){
            printf("Ainda não foram cadastradas categorias! Crie uma categoria antes\n\n");
            if(!(voltarOuRepetirOP())){
              system("clear");
              break;
            }
          }
          else{
            system("clear");
            Titulo();
            printf("- CADASTRAR PRODUTO -\n\n");
            getchar();

            printf("Digite o nome do produto: ");
            scanf("%[^\n]s", regProduto.nomeProduto);

            printf("Digite o valor do produto: ");
            scanf("%f", &regProduto.valor);

            printf("Digite a quantidade de unidades desse produto: ");
            scanf("%d", &regProduto.quantidade);

            printf("Digite o id de identifição da categoria que quer vincular o produto: ");
            scanf("%d", &idTemCat);

            //Verificação de cancelamento da operação
            if(idTemCat == -1){
              regProduto.nomeProduto[0] = '\0';

              if(!(voltarOuRepetirOP())){
                break;
              }
            }
            else{
              cadastrarProduto(&l, idTemCat, regProduto);

              if(!(voltarOuRepetirOP())){
                system("clear");
                break;
              }
            }
          }
        }
        break;
      case 2: //Cadastrar categoria
        while(true){
          system("clear");
          Titulo();

          printf("- CADASTRAR CATEGORIA -\n\n");
          getchar();

          printf("Digite o nome da nova categoria: ");
          scanf("%[^\n]s", regCategoria.nomeCategoria);

          printf("Digite o id de identificação da nova categoria: ");
          regCategoria.chaveCategoria = confereIDCategoria(&l);

          cadastrarCategoria(&l, regCategoria, tamanho(&l));
          regCategoria.nomeCategoria[0] = '\0';

          if(!(voltarOuRepetirOP())){
            system("clear");
            break;
          }
        }
        break;
      case 3: //Deletar Categoria
        while(true){
          system("clear");
          Titulo();
          printf("Digite o ID da categoria que deseja excluir: ");
          scanf("%d", &delCat);
          excluirCategoria(&l, delCat);
          
          if(!(voltarOuRepetirOP())){
            break;
          }
        }
        system("clear");
        break;
      case 4: //Deletar Produto
        while(true){
          system("clear");
          Titulo();
          printf("Digite o ID do produto para ser excluido: ");
          scanf("%d", &delProd);
          excluirProduto(&l, delProd);
          if(!(voltarOuRepetirOP())){
            break;
          }
        }
        system("clear");
        break;
      case 5: //Exibir Categorias
        system("clear");
        Titulo();
        printf("CATEGORIAS DISPONIVEIS:\n\n");
        exibirCategorias(&l);
        break;
      case 6: //Exibir todos os produtos
        system("clear");
        while(true){
          exibirTodosProdutos(&l);
          if(!(voltarOuRepetirOP())){
              system("clear");
              break;
            }
        }
        break;
      case 7: // Buscar produto
        while(true){
          system("clear");
          Titulo();
          printf("- BUSCA DE PRODUTO- \n\n");
          printf("Digite o ID do produto: ");
          scanf("%d", &idBusca);
          buscarProduto(&l, idBusca);
          if(!(voltarOuRepetirOP())){
            system("clear");
            break;
          }
        }
        break;
      case 8: // Atualizar produto
        system("clear");
        Titulo();
        printf("Informe o ID do produto a ser atualizado: ");
        scanf("%d", &idTemPro);
        atualizarProduto(&l, idTemPro);
        system("pause");
        break;
      case 0:
        system("clear");
	      Titulo();
	      printf("Obrigado, até a próxima!\n\n");
	      exit(0);
      }
    }
    while(true);
}


/* --- Titulo do sistema --- */
void Titulo() {
	printf("\n***************************************");
	printf("\n*       GERENCIADOR DE ESTOQUE        *\n");
 	printf("***************************************\n\n");
}

/* --- Função para repetir operação ---*/
bool voltarOuRepetirOP(){
	int op;
	while(true) {
    printf("\n1 - Repetir operação");
    printf("\n2 - Voltar");
    printf("\nDigite um opção: ");
		scanf("%d", &op);
		if (op == 1 || op == 2) {
			if (op == 2) {
				return false;	
			}
			else{
        return true;
      }
		} 
    else {
			printf("\nOpção inválida!\n");
		}
	}
}

/* ---Funções de manipulação da lista --- */


int tamanho(LISTA* l) {
	return l->tamanhoListaCategoria;
}

void inicializarLista(LISTA* l) {
	l->tamanhoListaCategoria = 0;
}

//Cadastro de Produtos
bool cadastrarProduto(LISTA* l, int idCategoria, REGISTRO_PRODUTO reg){
  bool var1 = false, var2 = true;
  int i, j, pos;
  int tamanho;
  
  for(i = 0; i < l->tamanhoListaCategoria; i++){
    if(l->registroCategoria[i].chaveCategoria == idCategoria){
      pos = i;
      var1 = true;
      break;
    }
  }
  if(var1 == false){
    printf("O ID da categoria não existe. Tente novamente.\n\n");
    return false;
  }

  tamanho = l->registroCategoria[pos].tamanhoListaProduto;

  if(tamanho == MAX_PRODUTO){
    printf("Estoque cheio. Delete alguns produtos.\n\n");
    return false;
  }

  while(var2){
    if(var2 == true){
      var2 = false;
    }
    printf("Digite o ID do novo produto (0 para cancelar operação): ");
    scanf("%d", &reg.chaveProduto);
    if(reg.chaveProduto == 0){
      return false;
    }

    for(j = 0; j < l->tamanhoListaCategoria; j++){
      for(i = 0; i < l->registroCategoria[j].tamanhoListaProduto; j++){
        if(l->registroCategoria[j].registroProduto[i].chaveProduto == reg.chaveProduto){
          printf("Este ID já existe! Registe um outro ID.\n\n");
          var2 = true;
          break;
        }
      }
      if(var2 == true) break;
    }
  }

  l->registroCategoria[pos].registroProduto[tamanho] = reg;
  l->registroCategoria[pos].tamanhoListaProduto++;

  printf("\nProduto cadastrado com sucesso!\n");
  printf("ID: %d\n",l->registroCategoria[pos].registroProduto[tamanho].chaveProduto);
  printf("Nome: %s\n", l->registroCategoria[pos].registroProduto[tamanho].nomeProduto);
  printf("Valor: %.2f\n", l->registroCategoria[pos].registroProduto[tamanho].valor);
  printf("Quantidade: %d\n\n", l->registroCategoria[pos].registroProduto[tamanho].quantidade);
  return true;
}

//Cadastro de Categoria
bool cadastrarCategoria(LISTA *l, REGISTRO_CATEGORIA reg, int i){
	int j;
	
	if ((l->tamanhoListaCategoria == MAX_CATEGORIA) || (i < 0) || (i > l->tamanhoListaCategoria)) {
		return false;	
	}
	
	for (j = l->tamanhoListaCategoria; j > i; j--) {
		l->registroCategoria[j] = l->registroCategoria[j-1];
	}
	
	l->registroCategoria[i] = reg;
	l->registroCategoria[i].tamanhoListaProduto = 0;
	l->tamanhoListaCategoria++;
	
	printf("\nCategoria cadastrada com sucesso!\n\n");
	printf("ID: %d\n", l->registroCategoria[i].chaveCategoria);
  printf("Nome: %s\n\n", l->registroCategoria[i].nomeCategoria);
	
	return true;
}


//Função para conferir a existencia de ID
int confereIDCategoria(LISTA *l) {
	int i;
  bool j = true;
	TIPOCHAVE aux;
	
  //Verificar se já existe o mesmo ID na lista
	while(true) {
		scanf("%d", &aux);
		for(i = 0; i < l->tamanhoListaCategoria; i++) {
			if (l->registroCategoria[i].chaveCategoria == aux) {
				printf("Esse ID ja existe! Digite outro: ");
				j = false;
				break;
			}
		}
		if(j){
      break;
    }		
		j = true;
	}
	return aux;
}

//Excluir categoria
bool excluirCategoria(LISTA *l, int idCategoria){
  int i, j;
  bool k = false;

  if(idCategoria <= 0 || l->tamanhoListaCategoria == 0){
    return false;
  }

  //Verificar se existe a categoria na lista
  for(i = 0; i < l->tamanhoListaCategoria; i++){
    if(l->registroCategoria[i].chaveCategoria == idCategoria){
      k = true;
      break; 
    }
  }

  if(k == true){
    for(j = 0; j < l->registroCategoria[i].tamanhoListaProduto; j++){
      l->registroCategoria[i].registroProduto[j].nomeProduto[0] = '\0';
    }

    l->registroCategoria[i].nomeCategoria[0] = '\0';
    l->registroCategoria[i].tamanhoListaProduto = 0;

    for(j = i; i < l->tamanhoListaCategoria - 1; j++){
      l->registroCategoria[i] = l->registroCategoria[i+1];
    }

    l->tamanhoListaCategoria--;
    printf("\nCategoria deletada com sucesso!\n");
    return true;
  }
  else{
    printf("\nID da categoria não foi encontrado.\n");
    return false;
  }  
}

//Excluir produto
bool excluirProduto(LISTA* l, int idProduto){
  int aux1, aux2, k;
  bool tp;

  tp = false;

  for(aux1 = 0; aux1 < l->tamanhoListaCategoria; aux1++){
    for(aux2 = 0; aux2 < l->registroCategoria[aux1].tamanhoListaProduto; aux2++){
      if(l->registroCategoria[aux1].registroProduto[aux2].chaveProduto == idProduto){
        tp = true;
        break;
      }
    }
    if(tp == true){
      break;
    }
  }
  if(tp == true){
    for(k = aux2; k < l->registroCategoria[aux1].tamanhoListaProduto -1; k++){
      l->registroCategoria[aux1].registroProduto[k] = l->registroCategoria[aux1].registroProduto[k+1];
    }

    l->registroCategoria[aux1].tamanhoListaProduto--;
    printf("Produto deletado com sucesso!\n");
    return true;
  }
  printf("\nProduto não existe!\n") ;
  return false;

}

//Exibir Categorias
void exibirCategorias(LISTA *l){
  int i;
  if(tamanho(l) > 0){
    for(i = 0; i < l->tamanhoListaCategoria; i++){
      printf("Nome: %s\nID Categoria: %d\n\n", l->registroCategoria[i].nomeCategoria, l->registroCategoria[i].chaveCategoria);
    }
  }
  else{
    printf("Ainda não foram cadastradas categorias! Crie uma categoria antes\n\n");
  }
}

//Exibir todos os produtos do estoque
bool exibirTodosProdutos(LISTA *l){
  int tamanhoProdutos;
  int i, j;

  Titulo();
  printf("- LISTA DE PRODUTOS CADASTRADOS -\n\n");
  if(l->tamanhoListaCategoria == 0){
    printf("Sem cadastro de produtos e categorias.\n\n");
    return false;
  }
  else{
    for(i = 0; i < l->tamanhoListaCategoria; i++){
      tamanhoProdutos = l->registroCategoria[i].tamanhoListaProduto;
      if(tamanhoProdutos == 0){
        printf("Nome da categoria: %s - ID: %d\n", l->registroCategoria[i].nomeCategoria, l->registroCategoria[i].chaveCategoria);
        printf("Sem produtos cadastrados nessa categoria.\n\n");
      }
      else{
        printf("Nome da categoria: %s - ID: %d\n", l->registroCategoria[i].nomeCategoria, l->registroCategoria[i].chaveCategoria);
        for(j = 0; j < tamanhoProdutos; j++){
          printf("Nome do produto: %s\nID: %d\n", l->registroCategoria[i].registroProduto[j].nomeProduto,l->registroCategoria[i].registroProduto[j].chaveProduto);
          printf("Preço: %.2f\nQuantidade em estoque: %d\n\n", l->registroCategoria[i].registroProduto[j].valor,l->registroCategoria[i].registroProduto[j].quantidade);
        }
      }
    }
    printf("-----------------------------------\n");
  }
  return true;
}

//Buscar por produto especifico
bool buscarProduto(LISTA *l, TIPOCHAVE idProduto){
  int i, j;
  bool k = false;

  for(i = 0; i < l->tamanhoListaCategoria; i++){
    for(j = 0; j < l->registroCategoria[i].tamanhoListaProduto; j++){
      if(l->registroCategoria[i].registroProduto[j].chaveProduto == idProduto){
        k = true;
        break;
      }
    }
    if(k == true){
      break;
    }
  }

  if(k == true){
    printf("\nNome do produto: %s\nID: %d\n", l->registroCategoria[i].registroProduto[j].nomeProduto, l->registroCategoria[i].registroProduto[j].chaveProduto);
    printf("Preço: %.2f\nQuantidade em estoque: %d\n\n", l->registroCategoria[i].registroProduto[j].valor,l->registroCategoria[i].registroProduto[j].quantidade);
    return true;
  }
  else{
    printf("Produto não foi encontrado.\n\n");
    return false;
  }
}

//Atualização de produtos
bool atualizarProduto(LISTA *l, int idProduto){
  int i, j, qntdNova, opcao2;
  bool m = false;
  char novoNome[MAX_NOME];
  float novoValor;

  //Verifica se a lista não esta vazia
  if(l->tamanhoListaCategoria == 0){
    printf("Sem cadastro de produtos e categorias.\n\n");
    return false;
  }

  for(i = 0; i < l->tamanhoListaCategoria; i++){
    for(j = 0; j < l->registroCategoria[i].tamanhoListaProduto; j++){
      if(l->registroCategoria[i].registroProduto[j].chaveProduto == idProduto){
        m = true;
        break;
      }
    }
    if(m == true) break;
  }
  
  if(m == false){
    printf("Este produto não foi encontrado no estoque!\n\n");
    return 0;
  }
  else{
    do{ // SUBMENU
      Titulo();
      printf("OPERACOES:\n");
      printf(" 1 - Alterar nome do produto\n");
      printf(" 2 - Alterar quantidade do produto\n");
      printf(" 3 - Alterar valor do produto\n");
      printf(" 0 - Voltar ao menu principal\n");
      printf("Digite uma opcao: ");
      scanf("%d", &opcao2);

      while(opcao2 < 0 || opcao2 > 3){
        printf("Opção inválida, digite novamente: ");
        scanf("%d", &opcao2);
      }
      switch(opcao2){
        case 1: // Alterar nome do produto
          l->registroCategoria[i].registroProduto[j].nomeProduto[0] = '\0';
          printf("Digite o novo nome para o produto: ");
          getchar();
          scanf("%[^\n]s", novoNome);
          strcpy(l->registroCategoria[i].registroProduto[j].nomeProduto, novoNome);


          printf("\nNome alterado com sucesso!\n\n");
          printf("ID: %d\n", l->registroCategoria[i].registroProduto[j].chaveProduto);
          printf("Nome do produto: %s\n", l->registroCategoria[i].registroProduto[j].nomeProduto);
          printf("Preço: %.2f\n", l->registroCategoria[i].registroProduto[j].valor);
          printf("Quantidade em estoque: %d\n\n", l->registroCategoria[i].registroProduto[j].quantidade);
          if(!(voltarOuRepetirOP())){
            system("clear");
            break;
          }
          break;
        
        case 2: //Alterar quantidade do produto
          printf("Digite a nova quantidade do produto: ");
          scanf("%d", &qntdNova);

          l->registroCategoria[i].registroProduto[j].quantidade = qntdNova;

          printf("\nQuantidade de produtos alterado com sucesso!\n\n");
          printf("ID: %d\n", l->registroCategoria[i].registroProduto[j].chaveProduto);
          printf("Nome do produto: %s\n", l->registroCategoria[i].registroProduto[j].nomeProduto);
          printf("Preço: %.2f\n", l->registroCategoria[i].registroProduto[j].valor);
          printf("Quantidade em estoque: %d\n\n", l->registroCategoria[i].registroProduto[j].quantidade);
          if(!(voltarOuRepetirOP())){
            system("clear");
            break;
          }
          break;
        
        case 3: //Alterar valor do produto
          printf("Digite um novo valor para o produto: ");
          scanf("%f", &novoValor);

          l->registroCategoria[i].registroProduto[j].valor = novoValor;
          printf("\nValor do produto alterado com sucesso!\n\n");
          printf("ID: %d\n", l->registroCategoria[i].registroProduto[j].chaveProduto);
          printf("Nome do produto: %s\n", l->registroCategoria[i].registroProduto[j].nomeProduto);
          printf("Preço: %.2f\n", l->registroCategoria[i].registroProduto[j].valor);
          printf("Quantidade em estoque: %d\n\n", l->registroCategoria[i].registroProduto[j].quantidade);
          if(!(voltarOuRepetirOP())){
            system("clear");
            break;
          }
          break;

        case 0: //Voltar ao menu principal
          return true;
          break;
      }
    }
    while(true);
  }
}
