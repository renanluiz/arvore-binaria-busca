/******************************************************************************************************
 
ESTRUTURA DE DADOS II | Turma: 1INF35A
Mat.: 20181105683 | Renan Luiz Souza de Oliveira 

******************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estrutura Funcionario
typedef struct funcionario{
	int matric; 		/* número de matrícula */
	char nome [120]; 	/* nome do funcionário */
	char fones[80]; 	/* telefone(s) do funcionário */
	char depto[5]; 		/* departamento em que trabalha */
	float salario; 		/* salário do funcionário */
}Funcionario;

// Estrutura
typedef struct arv {
	Funcionario* info;
	struct arv* esq;
	struct arv* dir;
}Arv;


Arv *inicializaArvore(Arv *no) {
    no = NULL;
    return no;
}

Arv *inserirNo(Arv *no, Funcionario* info) {
    if(no == NULL) { // se a arvore estiver vazia, entao insere como no raiz
        no = (Arv *) malloc(sizeof(Arv));
        no->info = info;
        no->esq = NULL;
        no->dir = NULL;
    }
    
    int resultNome;
    resultNome = strcmp(info->nome, no->info->nome);
    
    if(resultNome > 0 ) { // Valor do nó atual é menor que o inserido (str2 < str1)
        no->esq = inserirNo(no->esq, info); // entao caminha para a esquerda
    }
    
    if(resultNome < 0){ // Valor do nó atual é maior que o inserido (str2 > str1)
        no->dir = inserirNo(no->dir, info); // entao caminha para a direita
    }
    return no;
}

void imprimirArvorePreOrdem(Arv *no) {

    if(no != NULL) {
        printf("%s %d %s %s %.2f\n", no->info->nome, no->info->matric, no->info->fones, no->info->depto, no->info->salario);
//        printf("%i ", no->info->matric);
        imprimirArvorePreOrdem(no->esq);
        imprimirArvorePreOrdem(no->dir);
    }
}

// realiza a impressao da arvore Em ordem
void imprimirArvoreEmOrdem(Arv *no) {

    if(no != NULL) {
        imprimirArvoreEmOrdem(no->esq);
        printf("%s %d %s %s %.2f\n", no->info->nome, no->info->matric, no->info->fones, no->info->depto, no->info->salario);
        imprimirArvoreEmOrdem(no->dir);
    }
}

void imprimirArvorePosOrdem(Arv *no) {

    if(no != NULL) {
        imprimirArvorePosOrdem(no->esq);
        imprimirArvorePosOrdem(no->dir);
        printf("%s %d %s %s %.2f\n", no->info->nome, no->info->matric, no->info->fones, no->info->depto, no->info->salario);

    }
}
  

Arv* retira(Arv* t, Funcionario* info){
	if(!t) return t;
	
    int result;
    result = strcmp(t->info->nome, info->nome);
		
 		if((!t->esq)&&(!t->dir)){ //Caso 1
 			printf("\nRemocao - caso 1 = %s\n",t->info->nome);
			free(t);
			t = NULL;	
		}else if((!t->esq)||(!t->dir)){ //Caso 2
			printf("\nRemocao - caso 2 = %s\n",t->info->nome);
			Arv* a = t;
			if(t->esq)
				t = t->esq;
			else
				t = t->dir;
				free(a);
		}else{ //Caso 3 - vá a esquerda e pegue o filho mais à direita
			printf("\nRemocao - caso 3 = %s\n",t->info->nome);
			Arv* f = t->esq;
			while(f->dir)
				f = f->dir;
			Arv* temp;
			temp = t;
			t->info = f->info; // o nó a ser removido recebe o valor que está no nó mais à direira do seu filho esquerdo  
			f->info = temp->info; //Na verdade, há uma troca entre esses dois nós - o valor a ser revomido passa para a folha
			//printf("\nNo da esquerda do noh a ser removido = %d\n",t->sae->num);
			t->esq = retira(t->esq,info); //remover o nó folha que contém agora o valor a ser removido.
		}

    return t;
}

Arv *valorMinimo(Arv *no) {
    while(no->esq != NULL) {
        no = no->esq;
    }
    return no;
}

void remover_pares(Arv *no) {

    if(no != NULL) {
        remover_pares(no->esq);
        if(no->info->matric%2 == 0){
		retira(no,no->info);
		}
        remover_pares(no->dir);
    }
}


Funcionario *maior_salario(Arv *no, float aux) {

    if(no != NULL) {

            if(no->info->salario >= aux){
            aux = no->info->salario;
            return no->info;
            }
            
        	maior_salario(no->esq, aux);
            maior_salario(no->dir, aux);
    }
}

Arv* busca(Arv *no, char* s) {

    while(no != NULL) {
    	
	    int result;
	    result = strcmp(no->info->nome, s);
	    printf("%i \n", result);
	    
        if (result == 0){
		
    	printf("Nome: %s \n", no->info->nome);
    	printf("Depto: %s \n", no->info->depto);
    	printf("Fones: %s \n", no->info->fones);
    	printf("Salario: %.2f \n", no->info->salario);
            return no; // Retorna o No caso ele seja encontrado
    	}
        else if (result < 0)
            no = no->esq;
        else
            no = no->dir;
    }
    return no; // Retorna NULL caso o No nao exista
}


// Obtém o tamanho da árvore
int tamanhoDicionario(Arv *no) { 

    if (no == NULL)
        return 0;
    else {          
        int contEsq = tamanhoDicionario(no->esq);         
        int contDir = tamanhoDicionario(no->dir);
        int contagem = contEsq + contDir + 1;
        return contEsq + contDir + 1;   
    }
}



int main() {
    
    Arv *arvore;
    arvore = inicializaArvore(arvore);
    
    int resp;
    char valor[50];
    float aux;
    
    Funcionario paulo;
    Funcionario renan;
    Funcionario carlos;
    Funcionario mariana;

    paulo.matric = 1;
    strcpy(paulo.nome, "PAULO");
    strcpy(paulo.fones, "40028922");
    strcpy(paulo.depto, "TI");
    paulo.salario = 1200;
    
    renan.matric = 2;
    strcpy(renan.nome, "RENAN");
    strcpy(renan.fones, "351182911");
    strcpy(renan.depto, "TI");
    renan.salario = 2300;
    
    carlos.matric = 3;
    strcpy(carlos.nome, "CARLOS");
    strcpy(carlos.fones, "219946565");
    strcpy(carlos.depto, "RH");
    carlos.salario = 1500;
    
    mariana.matric = 4;
    strcpy(mariana.nome, "MARIANA");
    strcpy(mariana.fones, "219943423");
    strcpy(mariana.depto, "RH");
    mariana.salario = 1600;

	arvore = inserirNo(arvore, &renan);
	arvore = inserirNo(arvore, &carlos);
    arvore = inserirNo(arvore, &paulo);
    arvore = inserirNo(arvore, &mariana);
	fflush(stdin);
	

        while(true){
        	
        printf( // Exibe o menu na tela
        "\n============== Sub-Menu =================\n"
        "1) Inserir um novo funcionario\n"
        "2) Buscar por um funcionario\n"
        "3) Imprimir arvore em Pre-ordem\n"
        "4) Imprimir arvore em Pos-ordem\n"
        "5) Imprimir arvore Em-Ordem\n"
        "6) Encerrar o programa\n"
        "\n"
        "Digite a opcao desejada: "
        );
		
		// Captura a resposta do usuario
        scanf(" %d", &resp);
		
        switch (resp) {
        case 1: // Inserir um valor na árvore
			Funcionario novo;
			
			printf("Digite o nome do funcionario\n");
            scanf("%s", &novo.nome);
            
			printf("Digite a matricula do funcionario\n");
            scanf("%d", &novo.matric);
            
			printf("Digite o telefone do funcionario\n");
            scanf("%s", &novo.fones);
            
			printf("Digite o departamento do funcionario\n");
            scanf("%s", &novo.depto);
            
			printf("Digite o salario do funcionario\n");
            scanf("%f", &novo.salario);
            
            	arvore = inserirNo(arvore, &novo);
            
            break;
            
	        case 2: //Caso o usuário tenha desejado buscar por um valor
	        
	        	printf("\nDigite um valor para busca: "); // Se usuario escolheu digitar os dados
	            scanf("%s", &valor);
	
		            if (busca(arvore, valor) == NULL)
			            printf("\nO valor nao foi encontrado!\n");
	            break;
	            
	        case 3:
				imprimirArvorePreOrdem(arvore); 
	            break;
	            
	        case 4:
				imprimirArvorePosOrdem(arvore);
	            break;
	            
	        case 5:
	        	imprimirArvoreEmOrdem(arvore);
	            break;
	            
	        case 6: //Encerrar o programa
	        	return 0;
	        	
	        default:
	            printf("\nOpcao nao identificada!"); // Se usuario digitou uma opcao invalida
	            return 0;
	            break;
        }
	} 

}
