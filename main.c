#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_NOME 5
#define MAX_PRODUTO 100
#define MAX_CATEGORIA 50

//Definindo as listas

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


//Funcoes
void inicializarLista(LISTA* l);
int tamanho(LISTA* l);
bool cadastrarProduto(LISTA *l, int idCategoria, REGISTRO_PRODUTO reg);
bool cadastrarCategoria(LISTA *l, REGISTRO_CATEGORIA reg, int i);
void Titulo();
bool voltarOuRepetir(); 
int confereIDCategoria(LISTA *l);
void sair(); 

//Menu Principal
int main(){
  LISTA l;
  REGISTRO_PRODUTO regProduto;
  REGISTRO_CATEGORIA regCategoria;

  int cat, op;
  int idTemporarioProduto, idTemporarioCategoria;
  int opcao;

  inicializarLista(&l);
  system("clear");

  setlocale(LC_ALL, "");

  do{
    Titulo();
    printf("OPERACOES:\n");
    printf(" 1 - Cadastrar um produto\n");
    printf(" 2 - Cadastrar categoria\n");
    printf(" 3 - Deletar produto\n");
    printf(" 4 - Deletar categoria\n");
    printf(" 0 - Sair\n");
    printf("Digite uma opcao: ");
    scanf("%d", &opcao);
    switch(opcao){
      case 1:
        //Loop que permite o cadastro de varios produtos
        while(true){
          /*Confere se existem categorias para cadastrar produtos. Caso não existe
          ele nao permite cadastrar o produto*/
          if(tamanho(&l) == 0){
            printf("Ainda não foram cadastradas categorias! Crie uma categoria antes\n\n");

            if(!(voltarOuRepetir())){
              system("clear");
              break;
            }
          }
          else{
            //Leitura de dados e aloca em "regProduto"
            system("clear");
            Titulo();
            printf("- CADASTRAR PRODUTO\n");
            getchar();

            printf("Digite o nome do novo produto: ");
            scanf("%[^\n]s", regProduto.nomeProduto);

            printf("Digite o valor do produto: ");
            scanf("%f", &regProduto.valor);

            printf("Digite a quantidade de unidades desse produto: ");
            scanf("%d", &regProduto.quantidade);

            printf("Digite o id de identifição da categoria que quer vincular o produto(0 para cancelar operação): ");
            scanf("%d", &idTemporarioCategoria);

            //Verificação de cancelamento da operação
            if(idTemporarioCategoria == -1){
              regProduto.nomeProduto[0] = '\0';

              if(!(voltarOuRepetir())){
                system("clear");
                break;
              }
            }
            else{
              //Chamando a função para cadastro do produto
              cadastrarProduto(&l, idTemporarioCategoria, regProduto);

              if(!(voltarOuRepetir())){
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

          if(!(voltarOuRepetir())){
            system("clear");
            break;
          }
        }
        break;

      case 0:
        sair();
        break;
      
      default:
        printf("Opção inválida!");
        if(!(voltarOuRepetir())){
            system("clear");
            break;
        }
    }
  } while(true);
}

int tamanho(LISTA* l) {
	return l->tamanhoListaCategoria;
}

void inicializarLista(LISTA* l) {
	l->tamanhoListaCategoria = 0;
}

void Titulo() {
	printf("\n***************************************");
	printf("\n*      GERENCIADOR DE ESTOQUE         *\n");
 	printf("***************************************\n\n");
}

bool voltarOuRepetir() {
  setlocale(LC_ALL, "");
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
    printf("O id da categoria não existe. Tente novamente.\n\n");
    return false;
  }

  tamanho = l->registroCategoria[pos].tamanhoListaProduto;

  if(tamanho == MAX_PRODUTO){
    printf("Lista cheia. Delete alguns produtos.\n\n");
    return false;
  }

  while(var2){
    if(var2 == true){
      var2 = false;
    }
    printf("Digite o id do novo produto (0 para cancelar operação): ");
    scanf("%d", &reg.chaveProduto);
    if(reg.chaveProduto == 0){
      return false;
    }

    for(j = 0; j < l->tamanhoListaCategoria; j++){
      for(i = 0; i < l->registroCategoria[j].tamanhoListaProduto; j++){
        if(l->registroCategoria[j].registroProduto[i].chaveProduto == reg.chaveProduto){
          printf("Id desse produto já existe. Tente novamente.\n\n");
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
  printf("Nome: %s\nid: %d\n", l->registroCategoria[pos].registroProduto[tamanho].nomeProduto, l->registroCategoria[pos].registroProduto[tamanho].chaveProduto);
  printf("Valor: %.2f\nQuantidade: %d\n\n", l->registroCategoria[pos].registroProduto[tamanho].valor, l->registroCategoria[pos].registroProduto[tamanho].quantidade);

  return true;
}

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
	
	printf("\nCategoria cadastrada com sucesso!\n");
	printf("Nome: %s, id: %d\n\n", l->registroCategoria[i].nomeCategoria,l->registroCategoria[i].chaveCategoria);
	
	return true;
}

int confereIDCategoria(LISTA *l) {
  setlocale(LC_ALL, "");
	int i;
  bool aux = true;
	TIPOCHAVE temporario;
	
  //Verificar se já existe o mesmo ID na lista
	while(true) {
		scanf("%d", &temporario);
		for(i = 0; i < l->tamanhoListaCategoria; i++) {
			if (l->registroCategoria[i].chaveCategoria == temporario) {
				printf("O id ja existe! Digite outro: ");
				aux = false;
				break;
			}
		}
		if (aux) break;		
		aux = true;
	}
	return temporario;
}

// --- Sair ---
void sair() {
	system("clear");;
	Titulo();
	printf("Obrigado, até a próxima!\n\n");
	exit(0);
}
