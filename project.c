#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data {

    int dia,mes,ano;
};

struct Faxineiro { //registro de faxineiros

    char cpf[15],rg[15],nome[40],sexo[3],telefone[15],telefone2[15];
    struct Data data;
};

struct Cliente { //registro de clientes

    char cpf[15],nome[40],endereco[100],cep[10],cidade[50],email[45],email2[45],telefone[15],telefone2[15];
    struct Data data;
};

struct Servico {
	
	char cpf_cliente[15],cpf_faxineiro[15];
	struct Data data;
	float valor;
};

struct Faxineiro *alocar_vetor_faxineiro(FILE *arquivo, int *posicao,int *tamanho) { //funcao que aloca memoria para o tipo Faxineiro

    fseek(arquivo, 0, SEEK_END); //posiciona o cursor no final do arquivo
    
    long tamanho_arquivo = ftell(arquivo); //calcula o tamanho total da leitura

    *posicao = tamanho_arquivo / sizeof(struct Faxineiro); //calcula a quantidade de registros Faxineiro
    rewind(arquivo); //volta o cursor no comeco do arquivo

    struct Faxineiro *vetor = (struct Faxineiro*) malloc(((*posicao) + 10) * sizeof(struct Faxineiro));
    fread(vetor, sizeof(struct Faxineiro), *posicao, arquivo);
    *tamanho = *posicao;

    return vetor;
}

FILE *abrir_arquivo(FILE *arquivo,char *nome) { //funcao que  abre arquivos

    arquivo = fopen(nome,"rb+"); //abrir ou criar arquivo de faxineiros

    if(arquivo == NULL) { //verificar se a abertura ou criacao de arquivo de faxineiros pode ser efetuada

        arquivo = fopen(nome,"wb+");

        if(arquivo == NULL) {

            printf("\nErro ao localizar / criar o arquivo\n");
            exit(1);
        }             
    }        
    return arquivo;
}
 
void menu_principal(int *opcao) { //imprime menu principal

        system("cls");

        printf("\tMENU DE OPCOES:\n\n"); //menu principal
        printf("1.\tSubmenu de faxineiros\n");
        printf("2.\tSubmenu  de clientes\n");
        printf("3.\tSubmenu de servicos\n");
        printf("4.\tSubmenu de relatorios\n");
        printf("5.\tSair\n");
        printf("\nSelecione uma opcao: ");
        scanf("%d%*c",opcao);
}

void submenus(int *opcao,char *tipo) { //imprime os submenus

    system("cls");

    printf("\tMENU DE %s\n\n",tipo); 

    strlwr(tipo);
    int tamanho = strlen(tipo);

    tipo[tamanho - 1] = '\0';

    printf("1.\tCadastrar %s\n",tipo);
    printf("2.\tConsultar %s\n",tipo);
    printf("3.\tAlterar %s\n",tipo);
    printf("4.\tRemover %s\n",tipo);
    printf("5.\tSair\n");
    printf("\nSelecione uma opcao: ");
    scanf("%d%*c",opcao);
}

void submenu_consulta(int *opcao) { //imprime submenu de consulta de faxineiros

    system("cls");
    printf("SUBMENU DE CONSULTA\n\n"); 
    printf("1.\tConsultar cadastro individual\n");
    printf("2.\tConsulta geral\n\n");
    printf("Selecione uma opcao: ");
    scanf("%d%*c",opcao);
}

int buscar_faxineiro(char *cpf,struct Faxineiro *vetor,int qtd) { // funcao que verifica se o cadastro já existe

    int i;

    for(i = 0;i < qtd;i++) {

        if(strcmp(cpf,(vetor + i)->cpf) == 0) {

            return i;
        }
    }
    return -1;
}

int verifica_memoria(int *posicao,int *tamanho) {

    if(*posicao < *tamanho) {

        return 0;
    }
    else {

        return 1;
    }
}

struct Faxineiro *cadastrar_faxineiro(struct Faxineiro *vetor, int *posicao, int *tamanho,int *existe) { //funcao para cadastrar novos faxineiros

    if (verifica_memoria(posicao,tamanho) == 0) { //verifica se ha espaço para adicionar um novo cadastro
        
        char cpf[15], telefone2[15];

        printf("\nInsira o CPF a ser cadastrado: ");
        fgets(cpf, sizeof(cpf), stdin);

        if (buscar_faxineiro(cpf, vetor, *posicao) >= 0) {
        
            *existe = 1;
        } 
        else {
        
            strcpy((vetor + *posicao)->cpf, cpf);
            printf("\nInsira o RG: ");
            fgets((vetor + *posicao)->rg,sizeof((vetor + *posicao)->rg),stdin);
            printf("\nInsira o nome: ");
            fgets((vetor + *posicao)->nome,sizeof((vetor + *posicao)->nome),stdin);
            printf("\nInsira o sexo (M ou F): ");
            fgets((vetor + *posicao)->sexo,sizeof((vetor + *posicao)->sexo),stdin);
            printf("\nInsira o telefone 1: ");
            fgets((vetor + *posicao)->telefone,sizeof((vetor + *posicao)->telefone),stdin);
            printf("\nInsira o telefone 2 (ou tecle Enter para pular): ");
            fgets(telefone2,sizeof(telefone2),stdin);

            if(telefone2[0] == '\n') {

                printf("\nInsira o dia de nascimento (dd): ");
                scanf("%d%*c",&(vetor + *posicao)->data.dia);
                printf("Insira o mes de nascimento (mm): ");
                scanf("%d%*c",&(vetor + *posicao)->data.mes);
                printf("Insira o ano de nascimento (aaaa): ");
                scanf("%d%*c",&(vetor + *posicao)->data.ano); 
            }
            else {

                strcpy((vetor + *posicao)->telefone2,telefone2);
                printf("\nInsira o dia de nascimento (dd): ");
                scanf("%d%*c",&(vetor + *posicao)->data.dia);
                printf("Insira o mes de nascimento (mm): ");
                scanf("%d%*c",&(vetor + *posicao)->data.mes);
                printf("Insira o ano de nascimento (aaaa): ");
                scanf("%d%*c",&(vetor + *posicao)->data.ano);
            }
            (*posicao)++;
        }
    } 
    else {
      
        (*tamanho) += 10; //se nao houver espaco, realoca memoria para um tamanho maior
        vetor = realloc(vetor, (*tamanho) * sizeof(struct Faxineiro));
      
        if (vetor == NULL) {
      
            printf("\nErro ao realocar memoria!\n");
        }
        return cadastrar_faxineiro(vetor, posicao, tamanho,existe);  //continua o processo de cadastro como antes
    }
    
    return vetor;
}


int consultar_faxineiro(struct Faxineiro *vetor,int posicao) { //funcao para consultar o cadastro de um faxineiro

    char cpf[15];
    int indice;

    printf("\nInsira o CPF para consulta: ");
    fgets(cpf, sizeof(cpf), stdin);

    indice = buscar_faxineiro(cpf,vetor,posicao);

    if(indice >= 0) {

        printf("\nCPF:\t\t\t%s",(vetor + indice)->cpf);
        printf("RG:\t\t\t%s",(vetor + indice)->rg);
        printf("Nome:\t\t\t%s",(vetor + indice)->nome);
        printf("Sexo:\t\t\t%s",(vetor + indice)->sexo);
        printf("Telefone 1:\t\t%s",(vetor + indice)->telefone);
        
        if (((vetor + indice)->telefone2[0] == '\n')) { 

            printf("\nData de nascimento:\t%d/%d/%d",(vetor + indice)->data.dia,(vetor + indice)->data.mes,(vetor + indice)->data.ano);
        }
        else {

            printf("Telefone 2:\t\t%s",(vetor + indice)->telefone2);
            printf("\nData de nascimento:\t%d/%d/%d\n",(vetor + indice)->data.dia,(vetor + indice)->data.mes,(vetor + indice)->data.ano);
        }
        return 0;
    }
    else {

        return 1;
    }
}

void consulta_geral_faxineiro(struct Faxineiro *vetor, int posicao) { //imprime todos os faxineiros cadastrados

    int i;

    for (i = 0; i < posicao; i++) {

        printf("\nCPF:\t\t\t%s", (vetor + i)->cpf);
        printf("RG:\t\t\t%s", (vetor + i)->rg);
        printf("Nome:\t\t\t%s", (vetor + i)->nome);
        printf("Sexo:\t\t\t%s", (vetor + i)->sexo);
        printf("Telefone 1:\t\t%s", (vetor + i)->telefone);

        if (((vetor + i)->telefone2[0] == '\n')) { 
            
            printf("\nData de nascimento:\t%d/%d/%d\n", (vetor + i)->data.dia, (vetor + i)->data.mes, (vetor + i)->data.ano);
        } 
        else {
            
            printf("Telefone 2:\t\t%s", (vetor + i)->telefone2);
            printf("\nData de nascimento:\t%d/%d/%d", (vetor + i)->data.dia, (vetor + i)->data.mes, (vetor + i)->data.ano);
        }
        printf("\n---------------------------------------\n\n"); 
    }
}

int alterar_faxineiro(struct Faxineiro *vetor,int posicao) { //funcao para alterar o cadastro de um faxineiro
	
    char cpf[15];
    
	printf("\nInsira o CPF do faxineiro: ");
    fgets(cpf,sizeof(cpf),stdin);

	int indice = buscar_faxineiro(cpf,vetor,posicao);

    if(indice >= 0) {
		
        int op_alterar;
        
        do {

        	system("cls");

	        printf("\tSUBMENU DE ALTERACAO\n\n");
	
	        printf("1.\tAlterar o RG\n");
	        printf("2.\tAlterar o nome\n");
	        printf("3.\tAlterar o telefone 1\n");
	        printf("4.\tAlterar o telefone 2\n");
	        printf("5.\tAlterar a data de nascimento\n");
	        printf("6.\tSair\n");
	        printf("\nEscolha uma opcao: ");
	        scanf("%d%*c",&op_alterar);

            switch(op_alterar) {

                case 1:

                    printf("\nInsira o novo RG: ");
                    fgets((vetor + indice)->rg,sizeof((vetor + indice)->rg),stdin);
                    printf("\nAlteracao concluida!\n\n");
                    system("pause");

                    break;
                case 2:

                    printf("\nInsira o novo nome: ");
                    fgets((vetor + indice)->nome,sizeof((vetor + indice)->nome),stdin);
                    printf("\nAlteracao concluida!\n\n");
                    system("pause");
                    
                    break;
                case 3:

                    printf("\nInsira o novo telefone 1: ");
                    fgets((vetor + indice)->telefone,sizeof((vetor + indice)->telefone),stdin);
                    printf("\nAlteracao concluida!\n\n");
                    system("pause");

                    break;
                case 4:

                    printf("\nInsira o novo telefone 2: ");
                    fgets((vetor + indice)->telefone2,sizeof((vetor + indice)->telefone2),stdin);
                    printf("\nAlteracao concluida!\n\n");
                    system("pause");

                    break;
                case 5:

                    printf("\nInsira o dia de nascimento (dd): ");
                    scanf("%d%*c",&(vetor + indice)->data.dia);
                    printf("Insira o mes de nascimento (mm): ");
                    scanf("%d%*c",&(vetor + indice)->data.mes);
                    printf("Insira o ano de nascimento (aaaa): ");
                    scanf("%d%*c",&(vetor + indice)->data.ano);
       
                    printf("\nAlteracao concluida!\n\n");
                    system("pause");

                    break;
                case 6:

                    printf("\nSaindo...\n");
                    break;
                default:

                    printf("\nOpcao invalida!\n\n");
                    system("pause");

                    break;
            }
        } while(op_alterar != 6);
        return 0;
    }
    else {

        return 1;
    }
}

int excluir_faxineiro(struct Faxineiro *vetor,int *posicao,int qtd) { //funcao que remove o cadastro de um faxineiro

    char cpf[15];

    printf("\nInsira o CPF: ");
    fgets(cpf,sizeof(cpf),stdin);

    int indice = buscar_faxineiro(cpf,vetor,*posicao);

    if(indice >= 0) {

        int i;

        for(i = indice;i < (qtd -1);i++) {

            *(vetor + indice) = *(vetor + (indice + 1));
        }
        (*posicao)--;
        return 0;
    }
    else {

        return 1;
    }
}

struct Cliente *alocar_vetor_cliente(FILE *arquivo,int *posicao,int *tamanho) { //funcao que aloca memoria para o tipo cliente

    fseek(arquivo,0,SEEK_END);

    long tamanho_arquivo = ftell(arquivo);

    *posicao = tamanho_arquivo / sizeof(struct Cliente);
    rewind(arquivo);

    struct Cliente *vetor = (struct Cliente*) malloc(((*posicao) + 10) * (sizeof(struct Cliente)));
    fread(vetor,sizeof(struct Cliente),*posicao,arquivo);
    *tamanho = *posicao;

    return vetor;
}

int buscar_cliente(char *cpf,struct Cliente *vetor,int qtd) { // funcao que verifica se o cadastro de cliente já existe

    int i;

    for(i = 0;i < qtd;i++) {

        if(strcmp(cpf,(vetor + i)->cpf) == 0) {

            return i;
        }
    }
    return -1;
}


struct Cliente *cadastrar_cliente(struct Cliente *vetor,int *posicao,int *tamanho,int *existe) { //função que cadastra novos clientes

    if(verifica_memoria(posicao,tamanho) == 0) { //verifica se ha espaco para adicionar um novo cadastro

        char cpf[15],email2[45],telefone2[15];

        printf("\nInsira o CPF a ser cadastrado: ");
        fgets(cpf,sizeof(cpf),stdin);

        if(buscar_cliente(cpf,vetor,*posicao) >= 0) {

            *existe = 1;
        }
        else {

            strcpy((vetor + *posicao)->cpf,cpf);
            printf("\nInsira o nome: ");
            fgets((vetor + *posicao)->nome,sizeof((vetor + *posicao)->nome),stdin);
            printf("\nInsira o endererco: ");
            fgets((vetor + *posicao)->endereco,sizeof((vetor + *posicao)->endereco),stdin);
            printf("\nInsira o CEP: ");
            fgets((vetor + *posicao)->cep,sizeof((vetor + *posicao)->cep),stdin);
            printf("\nInsira a cidade: ");
            fgets((vetor + *posicao)->cidade,sizeof((vetor + *posicao)->cidade),stdin);
            printf("\nInsira o e-mail 1: ");
            fgets((vetor + *posicao)->email,sizeof((vetor + *posicao)->email),stdin);
            printf("\nInsira o e-mail 2 (ou tecle Enter para pular): ");
            fgets(email2,sizeof(email2),stdin);
            
            if((email2[0] == '\n')) {

                printf("\nInsira o telefone 1: ");
                fgets((vetor + *posicao)->telefone,sizeof((vetor + *posicao)->telefone),stdin);
                printf("\nInsira o telefone 2 (ou tecle Enter para pular): ");
                fgets(telefone2,sizeof(telefone2),stdin);

                if((telefone2[0] == '\n')) {

                    printf("\nInsira o dia de nascimento: ");
                    scanf("%d%*c",&(vetor + *posicao)->data.dia);
                    printf("Insira o mes de nascimento: ");
                    scanf("%d%*c",&(vetor + *posicao)->data.mes);
                    printf("Insira o ano de nascimento: ");
                    scanf("%d%*c",&(vetor + *posicao)->data.ano);
                }
                else {

                    strcpy((vetor + *posicao)->telefone2,telefone2);
                    printf("\nInsira o dia de nascimento: ");
                    scanf("%d%*c",&(vetor + *posicao)->data.dia);
                    printf("Insira o mes de nascimento: ");
                    scanf("%d%*c",&(vetor + *posicao)->data.mes);
                    printf("Insira o ano de nascimento: ");
                    scanf("%d%*c",&(vetor + *posicao)->data.ano);
                }
            }
            else {

                strcpy((vetor + *posicao)->email2,email2);
                printf("\nInsira o telefone 1: ");
                fgets((vetor + *posicao)->telefone,sizeof((vetor + *posicao)->telefone),stdin);
                printf("\nInsira o telefone 2 (ou tecle Enter para pular): ");
                fgets(telefone2,sizeof(telefone2),stdin);

                if((telefone2[0] == '\n')) {

                    printf("\nInsira o dia de nascimento: ");
                    scanf("%d%*c",&(vetor + *posicao)->data.dia);
                    printf("Insira o mes de nascimento: ");
                    scanf("%d%*c",&(vetor + *posicao)->data.mes);
                    printf("Insira o ano de nascimento: ");
                    scanf("%d%*c",&(vetor + *posicao)->data.ano);
                }
                else {

                    strcpy((vetor + *posicao)->telefone2,telefone2);
                    printf("\nInsira o dia de nascimento: ");
                    scanf("%d%*c",&(vetor + *posicao)->data.dia);
                    printf("Insira o mes de nascimento: ");
                    scanf("%d%*c",&(vetor + *posicao)->data.mes);
                    printf("Insira o ano de nascimento: ");
                    scanf("%d%*c",&(vetor + *posicao)->data.ano);

                }
            }
        }
    }
    else {

        (*tamanho) += 10; //se nao houver espaco, realoca memoria para um tamanho maior
        vetor = realloc(vetor, (*tamanho) * sizeof(struct Cliente));

        if (vetor == NULL) {
      
            printf("\nErro ao realocar memoria!\n");
        }
        return cadastrar_cliente(vetor, posicao, tamanho,existe);  //continua o processo de cadastro como antes
    }

    (*posicao)++;
    
    return vetor;
}

int consultar_cliente(struct Cliente *vetor,int posicao) {

    char cpf[15];
    int indice,tamanho;

    printf("\nInsira o CPF para consulta: ");
    fgets(cpf,sizeof(cpf),stdin);

    indice = buscar_cliente(cpf,vetor,posicao);

    if(indice >= 0) {

        printf("\nCPF:\t\t\t%s",(vetor + indice)->cpf);
        printf("Nome:\t\t\t%s",(vetor + indice)->nome);
        printf("Endereco:\t\t%s",(vetor + indice)->endereco);
        printf("CEP:\t\t\t%s",(vetor + indice)->cep);
        printf("Cidade:\t\t\t%s",(vetor + indice)->cidade);
        printf("E-mail:\t\t\t%s",(vetor + indice)->email);

        if(((vetor + indice)->email2[0] == '\n')) {

            printf("\nTelefone:\t\t%s",(vetor + indice)->telefone);

            if(((vetor + indice)->telefone2[0] == '\n')) {

                printf("\nData de nascimento:\t%d/%d/%d",(vetor + indice)->data.dia,(vetor + indice)->data.mes,(vetor + indice)->data.ano);
            }
            else {

                printf("\nTelefone 2:\t\t%s",(vetor + indice)->telefone2);
                printf("\nData de nascimento:\t%d/%d/%d",(vetor + indice)->data.dia,(vetor + indice)->data.mes,(vetor + indice)->data.ano);
            }
        }
        else {

            printf("E-mail 2:\t\t\t%s",(vetor + indice)->email2);
            printf("\nTelefone:\t\t%s",(vetor + indice)->telefone);

            if(((vetor + indice)->telefone2[0] == '\n')) {

                printf("\nData de nascimento:\t%d/%d/%d",(vetor + indice)->data.dia,(vetor + indice)->data.mes,(vetor + indice)->data.ano);
            }
            else {

                printf("Telefone 2:\t\t%s",(vetor + indice)->telefone2);
                printf("\nData de nascimento:\t%d/%d/%d",(vetor + indice)->data.dia,(vetor + indice)->data.mes,(vetor + indice)->data.ano);
            }
        }
        return 0;
    }
    else {

        return 1;
    }
}

void consulta_geral_cliente(struct Cliente *vetor,int posicao) {
    
    system("cls");

    int i;

    for(i = 0;i < posicao;i++) {

        printf("\nCPF:\t\t\t%s",(vetor + i)->cpf);
        printf("Nome:\t\t\t%s",(vetor + i)->nome);
        printf("Endereco:\t\t%s",(vetor + i)->endereco);
        printf("CEP:\t\t\t%s",(vetor + i)->cep);
        printf("Cidade:\t\t\t%s",(vetor + i)->cidade);
        printf("E-mail:\t\t\t%s",(vetor + i)->email);

        if(((vetor + i)->email2[0] == '\n')) {
            
            printf("\nTelefone:\t\t%s",(vetor + i)->telefone);

            if(((vetor + i)->telefone2[0] == '\n')) {

                printf("\nData de nascimento:\t\t\t%d/%d/%d",(vetor + i)->data.dia,(vetor + i)->data.mes,(vetor + i)->data.ano);
            }
            else {

                printf("Telefone 2:\t\t%s",(vetor + i)->telefone2);
                printf("\nData de nascimento:\t%d/%d/%d",(vetor + i)->data.dia,(vetor + i)->data.mes,(vetor + i)->data.ano);
            }
        }
        else {

            printf("E-mail 2:\t\t\t%s",(vetor + i)->email2);
            printf("\nTelefone:\t\t%s",(vetor + i)->telefone);

            if(((vetor + i)->telefone2[0] == '\n')) {

                printf("\nData de nascimento:\t%d/%d/%d",(vetor + i)->data.dia,(vetor + i)->data.mes,(vetor + i)->data.ano);
            }
            else {

                printf("Telefone 2:\t\t%s",(vetor + i)->telefone2);
                printf("\nData de nascimento:\t%d/%d/%d",(vetor + i)->data.dia,(vetor + i)->data.mes,(vetor + i)->data.ano);
            }
        }
        printf("\n---------------------------------------\n\n"); 
    }
}

int alterar_cliente(struct Cliente *vetor,int posicao) { //funcao para alterar o cadastro de um cliente
	
    char cpf[15];
    
	printf("\nInsira o CPF do cliente: ");
    fgets(cpf,sizeof(cpf),stdin);

	int indice = buscar_cliente(cpf,vetor,posicao);

    if(indice >= 0) {
		
        int op_alterar;
        
        do {

        	system("cls");

	        printf("\tSUBMENU DE ALTERACAO\n\n");
	
	        printf("1.\tAlterar o nome\n");
	        printf("2.\tAlterar o endereco\n");
	        printf("3.\tAlterar o CEP\n");
	        printf("4.\tAlterar a cidade\n");
            printf("5.\tAlterar e-mail 1\n");
            printf("6.\tAlterar o e-mail 2\n");
            printf("7.\tAlterar o telefone 1\n");
            printf("8.\tAlterar o telefone 2\n");
	        printf("9.\tAlterar a data de nascimento\n");
	        printf("10.\tSair\n");
	        printf("\nEscolha uma opcao: ");
	        scanf("%d%*c",&op_alterar);

            switch(op_alterar) {

                case 1:

                    printf("\nInsira o novo nome: ");
                    fgets((vetor + indice)->nome,sizeof((vetor + indice)->nome),stdin);
                    printf("\nAlteracao concluida!\n\n");
                    system("pause");

                    break;
                case 2:

                    printf("\nInsira o novo endereco: ");
                    fgets((vetor + indice)->endereco,sizeof((vetor + indice)->endereco),stdin);
                    printf("\nAlteracao concluida!\n\n");
                    system("pause");
                    
                    break;
                case 3:

                    printf("\nInsira o novo CEP: ");
                    fgets((vetor + indice)->cep,sizeof((vetor + indice)->cep),stdin);
                    printf("\nAlteracao concluida!\n\n");
                    system("pause");

                    break;
                case 4:

                    printf("\nInsira a nova cidade: ");
                    fgets((vetor + indice)->cidade,sizeof((vetor + indice)->cidade),stdin);
                    printf("\nAlteracao concluida!\n\n");
                    system("pause");

                    break;
                case 5: 

                    printf("\nInsira o novo e-mail 1: ");
                    fgets((vetor + indice)->email,sizeof((vetor + indice)->email),stdin);
                    printf("\nAlteracao concluida!\n\n");
                    system("pause");
                    
                    break;
                case 6:

                    printf("\nInsira o novo e-mail 2: ");
                    fgets((vetor + indice)->email2,sizeof((vetor + indice)->email2),stdin);
                    printf("\nAlteracao concluida!\n\n");
                    system("pause");
                    
                    break;
                case 7:

                    printf("\nInsira o novo telefone 1: ");
                    fgets((vetor + indice)->telefone,sizeof((vetor + indice)->telefone),stdin);
                    printf("\nAlteracao concluida!\n\n");
                    system("pause");
                    
                    break;
                case 8:

                    printf("\nInsira o novo telefone 2: ");
                    fgets((vetor + indice)->telefone2,sizeof((vetor + indice)->telefone2),stdin);
                    printf("\nAlteracao concluida!\n\n");
                    system("pause");
                    
                    break;
                case 9:

                    printf("\nInsira o dia de nascimento (dd): ");
                    scanf("%d%*c",&(vetor + indice)->data.dia);
                    printf("Insira o mes de nascimento (mm): ");
                    scanf("%d%*c",&(vetor + indice)->data.mes);
                    printf("Insira o ano de nascimento (aaaa): ");
                    scanf("%d%*c",&(vetor + indice)->data.ano);
       
                    printf("\nAlteracao concluida!\n\n");
                    system("pause");

                    break;
                case 10:

                    printf("\nSaindo...\n");
                    break;
                default:

                    printf("\nOpcao invalida!\n\n");
                    system("pause");

                    break;
            }
        } while(op_alterar != 10);

        return 0;
    }
    else {

        return 1;
    }
}

int excluir_cliente(struct Cliente *vetor,int *posicao,int qtd) {

    char cpf[15];

    printf("\nInsira o CPF: ");
    fgets(cpf,sizeof(cpf),stdin);

    int indice = buscar_cliente(cpf,vetor,*posicao);

    if(indice >= 0) {

        int i;

        for(i = indice;i < (qtd -1);i++) {

            *(vetor + indice) = *(vetor + (indice + 1));
        }
        (*posicao)--;
        return 0;
    }
    else {

        return 1;
    }
}

struct Servico *alocar_vetor_servico(FILE *arquivo,int *posicao,int *tamanho) {
	
	fseek(arquivo,0,SEEK_END);
	
	long tamanho_arquivo = ftell(arquivo);
	
	*posicao = tamanho_arquivo / sizeof(struct Servico);
	rewind(arquivo);
	
	struct Servico *vetor = (struct Servico*) malloc(((*posicao) + 10) * sizeof(struct Servico));
	fread(vetor,sizeof(struct Servico),*posicao,arquivo);
	*tamanho = *posicao;
	
	return vetor;
}

int verifica_servico(struct Servico *vetor,int posicao,char *cpf,int dia,int mes,int ano) { //verifica se o faxineiro tera disponibilidade

    int i;

    for(i = 0;i < posicao;i++) {

        if((vetor + i)->cpf_faxineiro == cpf) {

            if((vetor + i)->data.dia == dia && (vetor + i)->data.mes == mes && (vetor + i)->data.ano == ano) {
    
                return 1;
            }
        }

    }
    return 0;
}

struct Servico *cadastrar_servico(struct Servico *vetor,int *posicao,int *tamanho) { //função que cadastra novos servicos

    if(verifica_memoria(posicao,tamanho) == 0) {
        
        system("cls");

        int dia,mes,ano;
        char cpf[15];

        printf("DATA DO SERVICO\n\n");
        printf("Insira o dia: ");
        scanf("%d%*c",&dia);
        printf("Insira o mes: ");
        scanf("%d%*c",&mes);
        printf("Insira o ano: ");
        scanf("%d%*c",&ano);
        printf("\nInsira o CPF do faxineiro: ");
        fgets(cpf,sizeof(cpf),stdin);

        if(verifica_servico(vetor,*posicao,cpf,dia,mes,ano) == 0) {
            
            (vetor + *posicao)->data.dia = dia;
            (vetor + *posicao)->data.mes = mes;
            (vetor + *posicao)->data.ano = ano;
            strcpy((vetor + *posicao)->cpf_faxineiro,cpf);

            printf("\nInsira o CPF do cliente: ");
            fgets((vetor + *posicao)->cpf_cliente,sizeof((vetor + *posicao)->cpf_cliente),stdin);
            printf("\nInsira o valor do servico: ");
            scanf("%f%*c",&(vetor + *posicao)->valor);
        }
        else {

            printf("\nData invalida, faxineiro indisponivel!\n");
        }
    }   
    else {

        (*tamanho) += 10;
        vetor = realloc(vetor,(*tamanho) * sizeof(struct Servico));

        if (vetor == NULL) {
      
            printf("\nErro ao realocar memoria!\n");
        }
        return cadastrar_servico(vetor, posicao, tamanho);  //continua o processo de cadastro como antes
    }
    (*posicao)++;

    return vetor;
}

int buscar_servico_cliente(char *cpf, struct Servico *vetor, int qtd, int pos_inicio) {
    
	int i;

    	for (i = pos_inicio; i < qtd; i++) {
        	
		    if (strcmp(cpf, (vetor + i)->cpf_cliente) == 0) {
            	
			    return i;
        	}
    }
    return -1;
}

int buscar_servico_faxineiro(char *cpf,struct Servico *vetor,int qtd) { 

    int i;

    for(i = 0;i < qtd;i++) {

        if(strcmp(cpf,(vetor + i)->cpf_faxineiro) == 0) {

            return i;
        }
    }
    return -1;
}

void submenu_consulta_servico(int *opcao) {

    system("cls");

    printf("SUBMENU DE CONSULTA\n\n");
    printf("1.\tConsultar pelo CPF do faxineiro\n");
    printf("2.\tConsultar pelo CPF do clente\n");
    printf("3.\tListar todos\n\n");
    printf("Selecione uma opcao: ");
    scanf("%d%*c",opcao);
}

int consultar_servico_faxineiro(struct Servico *vetor,int posicao) {

    system("cls");

    int i,indice;
    char cpf[15];
    
    printf("Insira o CPF do faxineiro: ");
    fgets(cpf,sizeof(cpf),stdin);

    for(i = 0;i < posicao;i++) {

        indice = buscar_servico_faxineiro(cpf,vetor,posicao);
        
        if(indice >= 0) {
            
            if(strcmp((vetor + i)->cpf_faxineiro,cpf) == 0) {

                printf("\nCPF do cliente:\t\t%s",(vetor + i)->cpf_cliente);
                printf("Data do servico:\t%d/%d/%d\n",(vetor + i)->data.dia,(vetor + i)->data.mes,(vetor + i)->data.ano);
                printf("Valor:\t\t\tR$ %.2f",(vetor + i)->valor);
                printf("\n---------------------------------------\n\n");
            }
        }
    }
    return 0;
}

int consultar_servico_cliente(struct Servico *vetor,int posicao) {

    system("cls");

    int i,indice;
    char cpf[15];
    
    printf("Insira o CPF do cliente: ");
    fgets(cpf,sizeof(cpf),stdin);

    for(i = 0;i < posicao;i++) {

        indice = buscar_servico_cliente(cpf,vetor,posicao,0);
        
        if(indice >= 0) {
            
            if(strcmp((vetor + i)->cpf_cliente,cpf) == 0) {

                printf("\nCPF do faxineiro:\t%s",(vetor + i)->cpf_faxineiro);
                printf("Data do servico:\t%d/%d/%d\n",(vetor + i)->data.dia,(vetor + i)->data.mes,(vetor + i)->data.ano);
                printf("Valor:\t\t\tR$ %.2f",(vetor + i)->valor);
                printf("\n---------------------------------------\n\n");
            }
        }   
    }
    return 0;
}

void consulta_geral_servico(struct Servico *vetor,int posicao) {

    system("cls");
    
    int i;

    for(i = 0;i < posicao;i++) {

        printf("CPF do faxineiro:\t%s",(vetor + i)->cpf_faxineiro);
        printf("CPF do cliente:\t\t%s",(vetor + i)->cpf_cliente);
        printf("Data do servico:\t%d/%d/%d\n",(vetor + i)->data.dia,(vetor + i)->data.mes,(vetor + i)->data.ano);
        printf("Valor:\t\t\tR$ %.2f",(vetor + i)->valor);
        printf("\n---------------------------------------\n\n");
    }
}

int alterar_servico(struct Servico *vetor, int qtd) {

    char cpf[15];
    int op = 0,dia,mes,ano;

    printf("\nInsira o CPF do cliente: ");
    fgets(cpf, sizeof(cpf), stdin);
    printf("\nInsira a data do servico a ser alterado:\n\n");
    printf("Dia: ");
    scanf("%d%*c", &dia);
    printf("Mes: ");
    scanf("%d%*c", &mes);
    printf("Ano: ");
    scanf("%d%*c", &ano);

    int pos_inicio = 0,var = 0;

    while (op != 3) {

        system("cls");

        int indice = buscar_servico_cliente(cpf, vetor, qtd, pos_inicio);

        if (indice >= 0) {

            if (dia == (vetor + indice)->data.dia && mes == (vetor + indice)->data.mes && ano == (vetor + indice)->data.ano) {
            
                printf("CPF do faxieniro:\t%s", (vetor + indice)->cpf_faxineiro);
                printf("CPF do cliente:\t\t%s", (vetor + indice)->cpf_cliente);
                printf("Data do servico:\t%d/%d/%d\n", (vetor + indice)->data.dia, (vetor + indice)->data.mes, (vetor + indice)->data.ano);
                printf("Valor:\t\t\tR$ %.2f\n", (vetor + indice)->valor);
                printf("\n---------------------------------------\n\n");

                printf("\tSUBMENU DE ALTERACAO\n\n");
                printf("1.\tAlterar o valor\n");
                printf("2.\tProximo servico\n");
                printf("3.\tSair\n");
                printf("\nEscolha uma opcao: ");
                scanf("%d%*c", &op);

                switch (op) {
            
                    case 1:

                        printf("\n\nInsira o novo valor: ");
                        scanf("%f%*c", &((vetor + indice)->valor));
                        printf("\n\nAlteracao concluida!\n\n");
            
                        system("pause");
            
                        break;
                    case 2:
            
                        pos_inicio = indice + 1; //avanca para o proximo servico
                        
                        if (pos_inicio >= qtd) {
                        
                            printf("\nNao ha mais servicos para esse cliente.\n\n");
                        
                            system("pause");
                        
                            return 1;
                        }
                        break;
                    case 3:
                        
                        printf("\n\nSaindo...\n\n");
                        
                        system("pause");
            
                        break;
                    default:
                        printf("\n\nOpcao invalida!\n\n");
                        
                        system("pause");
                        
                        break;
                }
                return 0;
            } 
            else {
                
                pos_inicio = indice + 1; //continua a busca

                if (pos_inicio >= qtd) {
                
                    printf("\nServico nao encontrado\n\n");
                
                    system("pause");
            
                    return 1;
                }
            }
        } 
        else {

            return 1;
        }
    }
    return 0;
}

int excluir_servico(struct Servico *vetor, int *posicao, int qtd) {
    
    char cpf[15];
    int i, op = 0, pos_inicio = 0;

    printf("\nInsira o CPF: ");
    fgets(cpf, sizeof(cpf), stdin);

    while (1) {
    
        int indice = buscar_servico_cliente(cpf, vetor, *posicao, pos_inicio);

        if (indice >= 0) {
    
            printf("CPF do faxineiro:\t%s", (vetor + indice)->cpf_faxineiro);
            printf("CPF do cliente:\t\t%s", (vetor + indice)->cpf_cliente);
            printf("Data do servico:\t%d/%d/%d\n", (vetor + indice)->data.dia, (vetor + indice)->data.mes, (vetor + indice)->data.ano);
            printf("Valor:\t\t\tR$ %.2f\n", (vetor + indice)->valor);
            printf("\n---------------------------------------\n\n");

            printf("\nOPCOES\n\n");
            printf("1.\tExcluir este servico\n");
            printf("2.\tAvancar para o proximo servico\n");
            printf("3.\tSair\n");
            printf("Selecione uma opcao: ");
            scanf("%d%*c", &op);

            switch (op) {
    
                case 1:
    
                    for (i = indice; i < (*posicao - 1); i++) {
    
                        *(vetor + i) = *(vetor + (i + 1));
                    }
                    (*posicao)--;
    
                    printf("\nServico excluido com sucesso!\n");
    
                    return 0;
                case 2:
    
                    pos_inicio = indice + 1;
    
                    if (pos_inicio >= *posicao) {
    
                        printf("\nNao ha mais servicos para este cliente.\n");
    
                        return 0;
                    }
                    break;
                case 3:
    
                    printf("\nSaindo...\n");
                    return 0;
                default:
    
                    printf("\nOpcao invalida!\n");
                    break;
            }
        } 
        else {
        
            printf("\nServico nao encontrado.\n");
            return 1;
        }
    }
}

void submenu_relatorio(int *opcao) {

    system("cls");

    printf("SUBMENU DE RELATORIOS\n\n");
    printf("1.\tClientes contratantes em um periodo\n");
    printf("2.\tTodos os servicos em uma data\n");
    printf("3.\tTodos os servicos de um faxineiro\n\n");
    printf("Selecione uma opcao: ");
    scanf("%d%*c",opcao);
}

FILE *abrir_arquivo_txt(FILE *arquivo,char *nome) {

    arquivo = fopen(nome,"w+");

    if(arquivo == NULL) {

        printf("\nErro ao localizar / criar o arquivo\n");
        exit(1);
    }
    return arquivo;
}

int verifica_data(struct Servico *vet_servico,int dia,int mes,int ano,int dia_fim,int mes_fim,int ano_fim,int i) {

    if(((vet_servico + i)->data.ano >= ano) && ((vet_servico + i)->data.ano <= ano_fim)) {
        
        if(((vet_servico + i)->data.mes >= mes) && ((vet_servico + i)->data.mes <= mes_fim)) {

            if(((vet_servico + i)->data.dia >= dia) && ((vet_servico + i)->data.dia <= dia_fim)) {

                return 0;
            }
        }
    }
    return 1;
}

/*struct Data *filtra_data() {

    struct Data *vetor = (struct Data *)malloc(sizeof(struct Data));

    printf("\nInsira a data do servico: \n\n");
    printf("Dia: ");
    scanf("%d%*c",&vetor->dia);
    printf("Mes: ");
    scanf("%d%*c", &vetor->mes);
    printf("Ano: ");
    scanf("%d%*c", &vetor->ano);
    
    return vetor;
}*/

int gravar_relatorio_1(struct Cliente *vet_cliente, int posicao_cliente, struct Servico *vet_servico, int posicao_servico, FILE *arquivo) {

    char nome_relatorio_1[20];

    strcpy(nome_relatorio_1,"arq_relatorio_1.txt");
    arquivo = abrir_arquivo_txt(arquivo,nome_relatorio_1);
    
    int i,j,cont = 0;
    int dia,mes,ano,dia_fim,mes_fim,ano_fim;
    char cpf_faxineiro[15], cpf_cliente[15];

    printf("\nInsira o CPF do faxineiro: ");
    fgets(cpf_faxineiro, sizeof(cpf_faxineiro), stdin);

    printf("\nInsira a data inicial do servico: \n\n");
    printf("Dia: ");
    scanf("%d%*c", &dia);
    printf("Mes: ");
    scanf("%d%*c", &mes);
    printf("Ano: ");
    scanf("%d%*c", &ano);

    printf("\n\n\nInsira a data final do servico: \n\n");
    printf("Dia: ");
    scanf("%d%*c", &dia_fim);
    printf("Mes: ");
    scanf("%d%*c", &mes_fim);
    printf("Ano: ");
    scanf("%d%*c", &ano_fim);

    for (i = 0; i < posicao_servico; i++) { 
        
        if (verifica_data(vet_servico,dia,mes,ano,dia_fim,mes_fim,ano_fim,i) == 0) {
            
            if(strcmp((vet_servico + i)->cpf_faxineiro, cpf_faxineiro) == 0) {
                        
                strcpy(cpf_cliente, (vet_servico + i)->cpf_cliente);

                fprintf(arquivo, "CPF do faxineiro:\t%s\n", (vet_servico + i)->cpf_faxineiro); //grava cpf faxineiro no arquivo
                printf("\nCPF do faxineiro:\t%s", (vet_servico + i)->cpf_faxineiro);

                for (j = 0; j < posicao_cliente; j++) { //verifica o cpf do cliente e agrupa as informacoes dele
                        
                    if (strcmp(cpf_cliente,(vet_cliente + j)->cpf) == 0) {
                        
                        fprintf(arquivo, "Nome do cliente:\t%s\n", (vet_cliente + j)->nome);
                        printf("Nome do cliente:\t%s", (vet_cliente + j)->nome);
                        fprintf(arquivo, "E-mail 1:\t%s\n", (vet_cliente + j)->email);
                        printf("E-mail 1:\t%s\n", (vet_cliente + j)->email);
                        fprintf(arquivo,"E-mail 2:\t%s\n", (vet_cliente + j)->email2);
                        printf("\nE-mail 2:\t%s", (vet_cliente + j)->email2);
                        fprintf(arquivo, "Telefone 1:\t%s\n", (vet_cliente + j)->telefone);
                        printf("\nTelefone 1:\t%s", (vet_cliente + j)->telefone);
                        fprintf(arquivo, "Telefone 2:\t%s\n", (vet_cliente + j)->telefone2);
                        printf("\nTelefone 2:\t%s", (vet_cliente + j)->telefone2);
                        fprintf(arquivo, "\n---------------------------------------\n\n");
                        printf("\n---------------------------------------\n\n");
                    }
                }
            }
            cont++;
        }
    }
    printf("\n");
    system("pause");
    fclose(arquivo);
    
    if(cont > 0) {
        
        return 0;
    }
    else {

        return 1;
    }
}

int gravar_relatorio_2(struct Servico *vet_servico,int posicao_servico,struct Cliente *vet_cliente,int posicao_cliente,struct Faxineiro *vet_faxineiro,int posicao_faxineiro,FILE *arquivo) {

    char nome_relatorio_2[20];

    strcpy(nome_relatorio_2,"arq_relatorio_2.txt");
    arquivo = abrir_arquivo_txt(arquivo,nome_relatorio_2);

    int i,j,cont = 0;
    int dia,mes,ano;

    printf("\nInsira a data do servico: \n\n");
    printf("Dia: ");
    scanf("%d%*c", &dia);
    printf("Mes: ");
    scanf("%d%*c", &mes);
    printf("Ano: ");
    scanf("%d%*c", &ano);

    for(i = 0;i < posicao_servico;i++) {

        if(dia == (vet_servico)->data.dia && mes == (vet_servico)->data.mes && ano == (vet_servico)->data.ano) {

            fprintf(arquivo,"CPF do cliente:\t%s\n",(vet_servico + i)->cpf_cliente);
            printf("\nCPF do cliente:\t%s\n",(vet_servico + i)->cpf_cliente);
            fprintf(arquivo,"CPF do faxineiro:\t%s",(vet_servico + i)->cpf_faxineiro);
            printf("CPF do faxineiro:\t%s",(vet_servico + i)->cpf_faxineiro);
            fprintf(arquivo,"Data:\t%d/%d/%d\n",(vet_servico + i)->data.dia,(vet_servico + i)->data.mes,(vet_servico + i)->data.ano);
            printf("Data:\t%d/%d/%d\n",(vet_servico + i)->data.dia,(vet_servico + i)->data.mes,(vet_servico + i)->data.ano);
            fprintf(arquivo,"Valor:\tR$\t%.2f\n",(vet_servico + i)->valor);
            printf("Valor:\tR$\t%.2f\n",(vet_servico + i)->valor);
            
            for(j = 0;j < posicao_cliente;j++) {

                if(strcmp((vet_servico + i)->cpf_cliente,(vet_cliente + j)->cpf) == 0) {

                    fprintf(arquivo,"Nome do cliente:\t%s\n",(vet_cliente + j)->nome);
                    printf("Nome do cliente:\t%s\n",(vet_cliente + j)->nome);
                }
            }
            for(j = 0;j < posicao_faxineiro;j++) {

                if(strcmp((vet_servico + i)->cpf_faxineiro,(vet_faxineiro + j)->cpf) == 0) {

                    fprintf(arquivo,"Nome do faxineiro:\t%s",(vet_faxineiro + j)->nome);
                    printf("Nome do faxineiro:\t%s",(vet_faxineiro + j)->nome);
                }
            }
            cont++;
        }
    }
    printf("\n");
    system("pause");
    fclose(arquivo);

    if(cont > 0) {

        return 0;
    }
    else {

        return 1;
    }
}

int gravar_relatorio_3(struct Servico *vetor,int posicao_servico,FILE *arquivo) {

    system("cls");

    int i,j,cont = 0;
    char cpf[15],nome_relatorio_2[20];

    strcpy(nome_relatorio_2,"arq_relatorio_2.txt");
    arquivo = abrir_arquivo_txt(arquivo,nome_relatorio_2);
    
    printf("Insira o CPF do faxineiro: ");
    fgets(cpf,sizeof(cpf),stdin);

    for(i = 0;i < posicao_servico;i++) {

        if(strcmp(cpf,(vetor + i)->cpf_faxineiro) == 0) {

            fprintf(arquivo,"CPF do cliente:\t%s\n",(vetor + i)->cpf_cliente);
            printf("CPF do cliente:\t%s\n",(vetor + i)->cpf_cliente);
            fprintf(arquivo,"Data:\t%d/%d/%d\n",(vetor + i)->data.dia,(vetor + i)->data.mes,(vetor + i)->data.ano);
            printf("Data:\t%d/%d/%d\n",(vetor + i)->data.dia,(vetor + i)->data.mes,(vetor + i)->data.ano);
            fprintf(arquivo,"Valor:\tR$\t%.2f\n",(vetor + i)->valor);
            printf("Valor:\tR$\t%.2f\n",(vetor + i)->valor);

            cont++;
        }
    }
    printf("\n");
    system("pause");
    fclose(arquivo);

    if(cont > 0) {
        
        return 0;
    }
    else {

        return 1;
    }
}

int main() {

    //variaveis de opcao para cada submenu
    int op,op_faxineiro,op_faxineiro2,op_servico_op_relatorio,op_cliente,op_cliente2,op_servico,op_servico2,op_relatorio;

	//variaveis para controle de cada submenu
    int posicao_faxineiro = 0,tamanho_faxineiro = 0,existe_faxineiro = 0,posicao_cliente = 0,tamanho_cliente = 0,existe_cliente = 0;
	int posicao_servico = 0,tamanho_servico = 0,existe_servico = 0; 
    
	char tipo[15],nome_arq_faxineiro[20],nome_arq_cliente[20],nome_arq_servico[20],nome_relatorio_3[20];
    
    //tipos de registro de cada vetor
    struct Faxineiro *vet_faxineiro;
    struct Cliente *vet_cliente;
    struct Servico *vet_servico;

    //arquivos
    FILE *arquivo_faxineiro,*arquivo_cliente,*arquivo_servico; 
    FILE *arq_relatorio_1,*arq_relatorio_2,*arq_relatorio_3; 

    do { 
    
        menu_principal(&op);

        switch(op) {

            case 1:

                strcpy(nome_arq_faxineiro,"arq_faxineiro.bin"); //nomeia o arquivo com os dados de faxineiros
                arquivo_faxineiro = abrir_arquivo(arquivo_faxineiro,nome_arq_faxineiro); //alocar vetor de faxineiros
                vet_faxineiro = alocar_vetor_faxineiro(arquivo_faxineiro,&posicao_faxineiro,&tamanho_faxineiro); //aloca dinamicamente um vetor com os dados do arquivo
                                
                do { 

                    strcpy(tipo,"FAXINEIROS"); //tipo recebe FAXINEIROS
                    submenus(&op_faxineiro,tipo); //chama o submenu com o tipo atribuido na linha acima
                    existe_faxineiro = 0; 

                    switch(op_faxineiro) {

                        case 1:  

                            system("cls");
                            printf("\nCadastrando novo faxineiro...\n");

                            vet_faxineiro = cadastrar_faxineiro(vet_faxineiro,&posicao_faxineiro,&tamanho_faxineiro,&existe_faxineiro);

                            if(existe_faxineiro == 0) { //verificar se o cadastro pode ser efetuado
                                        
                                printf("\nCadastro efetuado com sucesso!\n\n");   
                            }
                            else {
                                printf("\nFaxineiro ja cadastrado!\n\n");
                            }
                            system("pause");

                            break;
                        case 2: 

                            system("cls");                   
                            submenu_consulta(&op_faxineiro2);

                            switch(op_faxineiro2) {

                                case 1:

                                    printf("\nConsultando faxineiro...\n");

                                    if(consultar_faxineiro(vet_faxineiro,posicao_faxineiro) != 0) { //verificar se o cadastro de faxineiro existe
                                                
                                        printf("\nFaxineiro nao encontrado!");
                                    }
                                    printf("\n\n");
                                    system("pause");
                                    break;
                                case 2:

                                    printf("\nConsultando faxineiros...\n");
                
                                    consulta_geral_faxineiro(vet_faxineiro,posicao_faxineiro); //mostra todos os faxineiros cadastrados
                                    printf("\n\n");
                                    system("pause");

                                    break;
                            }
                            break;
                        case 3: 
                        
                            system("cls");
                            printf("\nAlterando faxineiro...\n");
                            
                            if(alterar_faxineiro(vet_faxineiro,posicao_faxineiro) == 0) {

                                printf("\nCadastro alterado com sucesso!\n\n");
                            }
                            else {

                                printf("\nErro  na alteracao!\n\n");
                            }
                            system("pause");

                            break;
                        case 4:

                            system("cls");
                            printf("\nExcluindo faxineiro...\n");

                            if(excluir_faxineiro(vet_faxineiro,&posicao_faxineiro,posicao_faxineiro) == 0) {

                                printf("\nCadastro removido com sucesso!\n\n");
                            }
                            else {

                                printf("\nErro na remocao!\n\n");
                            }
                            system("pause");

                            break;
                        case 5:

                            printf("\nSaindo...\n\n");
                            
                            break;
                        default:

                            printf("\nOpcao invalida!\n\n");
                            system("pause");

                            break;
                        }       
                } while(op_faxineiro != 5);
                
                rewind(arquivo_faxineiro); //posiciona o cursor no inicio de vet_faxineiro
                fwrite(vet_faxineiro,sizeof(struct Faxineiro),posicao_faxineiro,arquivo_faxineiro); //grava os dados de vet_faxineiro para arquivo_faxineiro
                free(vet_faxineiro); //libera a memoria alocada dinamicamente
                fclose(arquivo_faxineiro); //fecha arquivo_faxineiro
                
                break;
            case 2: 

                strcpy(nome_arq_cliente,"arq.cliente.bin"); //nomeia o arquivo com os dados de clientes
                arquivo_cliente = abrir_arquivo(arquivo_cliente,nome_arq_cliente); //alocar vetor de clientes
                vet_cliente = alocar_vetor_cliente(arquivo_cliente,&posicao_cliente,&tamanho_cliente); //aloca dinamicamente um vetor com os dados do arquivo
                
                do {
                    
                    existe_cliente = 0;
                    strcpy(tipo,"CLIENTES"); //tipo recebe CLIENTES
                    submenus(&op_cliente,tipo); //chama o submenu com o tipo atribuido acima

                    switch(op_cliente) {

                        case 1:

                            system("cls");
                            printf("Cadastrando novo cliente...\n");

                            vet_cliente = cadastrar_cliente(vet_cliente,&posicao_cliente,&tamanho_cliente,&existe_cliente);

                            if(existe_cliente == 0) {

                                printf("\nCadastro efetuado com sucesso!\n\n");   
                            }
                            else {

                                printf("\nCliente ja cadastrado!\n\n");
                            }
                            system("pause");

                            break;
                        case 2:

                            system("cls");
                            submenu_consulta(&op_cliente2);

                            switch(op_cliente2) {

                                case 1:

                                    printf("\nConsultando cliente...\n");

                                    if(consultar_cliente(vet_cliente,posicao_cliente) != 0) { //verificar se o cadastro de cliente existe
                                                
                                        printf("\nCliente nao encontrado!\n\n");
                                    }
                                    printf("\n\n");
                                    system("pause");

                                    break;
                                case 2:

                                    printf("\nConsultando clientes...\n");
                
                                    consulta_geral_cliente(vet_cliente,posicao_cliente); //mostra todos os clientes cadastrados
                                    printf("\n\n");
                                    system("pause");
                                    
                                    break;
                            }
                            break;
                        case 3:

                            system("cls");
                            printf("\nAlterando cliente...\n");
                            
                            if(alterar_cliente(vet_cliente,posicao_cliente) == 0) {

                                printf("\nCadastro alterado com sucesso!\n\n");
                            }
                            else {

                                printf("\nErro  na alteracao!\n\n");
                            }
                            system("pause");

                            break;
                        case 4:

                            system("cls");
                            printf("\nExcluindo cliente...\n");

                            if(excluir_cliente(vet_cliente,&posicao_cliente,posicao_cliente) == 0) {

                                printf("\nCadastro removido com sucesso!\n\n");
                            }
                            else {

                                printf("\nErro na remocao!\n\n");
                            }
                            system("pause");

                            break;
                        case 5:

                            printf("\nSaindo...\n\n");

                            break;
                        default:

                            printf("\nOpcao invalida!\n\n");
                            system("pause");

                            break;
                    }
                } while(op_cliente != 5);  

                rewind(arquivo_cliente); //posiciona o cursor no inicio de vet_cliente
                fwrite(vet_cliente,sizeof(struct Cliente),posicao_cliente,arquivo_cliente); //grava os dados de vet_cliente para arquivo_cliente
                free(vet_cliente); //libera memoria alocada dinamicamente
                fclose(arquivo_cliente); //fecha arquivo_cliente

                break;
            case 3:
            	
            	strcpy(nome_arq_servico,"arq_servico.bin");
            	arquivo_servico = abrir_arquivo(arquivo_servico,nome_arq_servico);
            	vet_servico = alocar_vetor_servico(arquivo_servico,&posicao_servico,&tamanho_servico);
            	
            	do {
            		
            		existe_servico = 0;
            		strcpy(tipo,"SERVICOS");
            		submenus(&op_servico,tipo);

                    switch(op_servico) {

                        case 1:

                            system("cls");
                            printf("Cadastrando novo servico...\n");

                            vet_servico = cadastrar_servico(vet_servico,&posicao_servico,&tamanho_servico);

                            if(existe_servico == 0) {

                                printf("\nCadastro efetuado com sucesso!\n\n");   
                            }
                            else {

                                printf("\nServico ja cadastrado!\n\n");
                            }
                            system("pause");

                            break;
                        case 2: 

                            system("cls");
                            printf("\nConsultando servico...\n\n");
                            submenu_consulta_servico(&op_servico2);

                            switch(op_servico2) {

                                case 1:


                                    if(consultar_servico_faxineiro(vet_servico,posicao_servico) != 0) { //verificar se o cadastro de servico existe
                                                
                                        printf("\nServico nao encontrado!\n\n");
                                    }
                                    printf("\n\n");
                                    system("pause");

                                    break;  
                                case 2:

                                    if(consultar_servico_cliente(vet_servico,posicao_servico) != 0) {

                                        printf("\nServico nao encontrado!\n\n");
                                    }                                           
                                    printf("\n\n");
                                    system("pause");

                                    break;         
                                case 3:
                
                                    consulta_geral_servico(vet_servico,posicao_servico); //mostra todos os clientes cadastrados
                                    printf("\n\n");
                                    system("pause");
                                    
                                    break;
                            }
                            break;	
                        case 3:

                            system("cls");
                            printf("\nAlterando servico...\n");
                            
                            if(alterar_servico(vet_servico,posicao_servico) == 0) {

                                printf("\nCadastro alterado com sucesso!\n\n");
                            }
                            else {

                                printf("\nErro na alteracao!\n\n");
                            }
                            system("pause");

                            break;
                        case 4:

                            system("cls");
                            printf("\nExcluindo servico...\n");

                            if(excluir_servico(vet_servico,&posicao_servico,posicao_servico) == 0) {

                                printf("\nCadastro removido com sucesso!\n\n");
                            }
                            else {

                                printf("\nErro na remocao!\n\n");
                            }
                            system("pause");

                            break;
                        case 5:

                            printf("\nSaindo...\n\n");

                            break;
                        default:

                            printf("\nOpcao invalida!\n\n");
                            system("pause");

                            break;
                    }
				} while(op_servico != 5);

                rewind(arquivo_servico);
                fwrite(vet_servico,sizeof(struct Servico),posicao_servico,arquivo_servico);
                free(vet_servico);
                fclose(arquivo_servico);
				
				break;
            case 4: 

                system("cls");
                submenu_relatorio(&op_relatorio);

                switch(op_relatorio) {

                    case 1:
                        
                        if(gravar_relatorio_1(vet_cliente,posicao_cliente,vet_servico,posicao_servico,arq_relatorio_1) != 0) {

                            printf("\nNenhum registro encontrado!\n\n");
                            system("pause");
                        }
                        break;
                    case 2:

                        if(gravar_relatorio_2(vet_servico,posicao_servico,vet_cliente,posicao_cliente,vet_faxineiro,posicao_faxineiro,arq_relatorio_2) != 0) {

                            printf("Nenhum registro encontrado!\n\n");
                            system("pause");
                        }
                        break;
                    case 3:

                        if(gravar_relatorio_3(vet_servico,posicao_servico,arq_relatorio_3) != 0) {

                            printf("Nenhum registro encontrado!\n\n");
                            system("pause");
                        }
                        break;
                }
                break;
            case 5:

                printf("\nSaindo...\n\n");
                system("pause");
                
                break;
        }
    } while(op != 5);
}
