/*Sistema de escola com CRUD e banco de dados local - Jo�o Victor*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

/*Defini��o das constantes dos par�metros usados no c�digo*/
#define tamanho_da_string 100
#define quantidade_de_alunos 50 //Tamanho total do array de structs

typedef struct local{
    char rua[tamanho_da_string];
    int numero_da_casa;
    char cidade[tamanho_da_string];
} local;

typedef struct aluno{
    char nome[tamanho_da_string];
    int idade;
    int matricula;
    int existe;
    local endereco;
} aluno;

//Fun��es de processamento interno
void parada(void);
void cadastrar_aluno(aluno *escola, aluno cadastro);
int verifica_matricula(aluno *escola, int matricula);
int verifica_quantidade_de_alunos(aluno *escola);
void exibir_alunos(aluno *escola);
void exibe_aluno(aluno escola);
void exibe_aluno_por_matricula(aluno *escola, int numero);
void exibe_aluno_por_nome(aluno *escola, char *nome);
void exibe_aluno_por_cidade(aluno *escola, char *cidade);
void remove_aluno_por_matricula(aluno *escola, int matricula);

//Fun��es de manipula��o de arquivos
//O arquivo � salvo na raiz do .exe gerado pelo compilador
int grava_txt(aluno *escola);
aluno* leitura_txt(aluno *escola);

int main(void){
    setlocale(LC_ALL, "Portuguese");
    aluno escola[quantidade_de_alunos] = {0};
    /*Defini��o do ponteiro usado para otimiza��o das fun��es
    desta forma n�o � necess�rio passar o array inteiro como par�metro da fun��o*/
    aluno *aponta_escola = escola;
    aluno cadastro = {0};
    int opcao, escolha_3;
    /*Leitura de texto se existir um arquivo pr�vio*/
    aponta_escola = leitura_txt(escola);

    //Sistema de menu simples em execu��o "infinita"
    do{
        system("cls");
        printf("1 - Cadastrar aluno\n");
        printf("2 - Exibir alunos cadastrados\n");
        printf("3 - Buscar alunos\n");
        printf("4 - Remover aluno por matr�cula\n");
        printf("5 - Finalizar o programa\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                printf("\nDigite o nome do aluno: ");
                fflush(stdin);
                gets(cadastro.nome);
                printf("Digite a idade do aluno: ");
                scanf("%d", &cadastro.idade);
                printf("Digite a matr�cula do aluno: ");
                scanf("%d", &cadastro.matricula);
                if(verifica_matricula(escola, cadastro.matricula) == 0){
                    printf("Digite a rua que o aluno mora: ");
                    fflush(stdin);
                    gets(cadastro.endereco.rua);
                    printf("Digite o n�mero da casa do aluno: ");
                    scanf("%d", &cadastro.endereco.numero_da_casa);
                    printf("Digite a cidade do aluno: ");
                    fflush(stdin);
                    gets(cadastro.endereco.cidade);
                    cadastrar_aluno(aponta_escola, cadastro);
                    aponta_escola++;
                    printf("\nAluno cadastrado com sucesso.");
                    parada();
                } else {
                    printf("J� existe um aluno com essa matr�cula. ");
                    parada();
                }
                break;
            case 2:
                exibir_alunos(escola);
                parada();
                break;
            case 3:
                /*Submenu de execu��o infinita para o caso 3 do menu anterior*/
                do{
                    system("cls");
                    printf("1 - Busca por matr�cula\n");
                    printf("2 - Busca por nome\n");
                    printf("3 - Busca por cidade\n");
                    printf("4 - Voltar para o menu anterior\n");
                    scanf("%d", &escolha_3);
                    switch(escolha_3){
                        case 1:
                            printf("Digite a matr�cula do aluno: ");
                            scanf("%d", &cadastro.matricula);
                            exibe_aluno_por_matricula(escola, cadastro.matricula);
                            parada();
                            break;
                        case 2:
                            printf("Digite o nome do aluno: ");
                            fflush(stdin);
                            gets(cadastro.nome);
                            exibe_aluno_por_nome(escola, cadastro.nome);
                            parada();
                            break;
                        case 3:
                            printf("Digite o nome da cidade: ");
                            fflush(stdin);
                            gets(cadastro.endereco.cidade);
                            exibe_aluno_por_cidade(escola, cadastro.endereco.cidade);
                            parada();
                            break;
                        case 4: break;
                        default:
                            printf("Digite uma op��o v�lida.");
                            parada();
                            break;
                    }
                }while(escolha_3 != 4);
                break;
            case 4:
                printf("Insira a matr�cula: ");
                scanf("%d", &cadastro.matricula);
                remove_aluno_por_matricula(escola, cadastro.matricula);
                parada();
                break;
            default:
                break;
        }
    }while(opcao!=5);
    
    //Grava��o dos dados em um arquivo, se j� existir, � reescrito com os novos dados
    if(grava_txt(escola) == 0) printf("Banco de alunos gravado com sucesso.");
    return 0;
}

//Fun��es de uso interno

//Fun��o de parada, usada em certos momentos do menu
void parada(void)
{
    printf("\n");
    system("pause");
    system("cls");
}

/*Fun��o que recebe um ponteiro do array de struct e uma vari�vel tempor�ria
para gravar dentro do array*/
void cadastrar_aluno(aluno *escola, aluno cadastro)
{
    strcpy(escola->endereco.rua, cadastro.endereco.rua);
    escola->endereco.numero_da_casa = cadastro.endereco.numero_da_casa;
    strcpy(escola->endereco.cidade, cadastro.endereco.cidade);
    strcpy(escola->nome, cadastro.nome);
    escola->idade = cadastro.idade;
    escola->matricula = cadastro.matricula;
    escola->existe = 1;
}

/*Fun��o que recebe o array inteiro, percorre e retorna se existe
um aluno com a matr�cula recebida*/
int verifica_matricula(aluno *escola, int matricula)
{
    for(int i=0; i<quantidade_de_alunos; i++){
        if(escola[i].matricula == matricula) return 1;
    }
    return 0;
}

/*Fun��o que percorre o array inteiro para saber se existem alunos cadastrados,
comparando o elemento interno "existe" do struct*/
int verifica_quantidade_de_alunos(aluno *escola)
{
    int contador = 0;
    for(int i=0;i<quantidade_de_alunos; i++){
        if(escola[i].existe == 1) contador++;
    }
    return contador;
}

/*Fun��o que exibe um �nico aluno, modularizada para as outras fun��es de exibi��o*/
void exibe_aluno(aluno escola)
{
    printf("\nNome: %s, %d anos", escola.nome, escola.idade);
    printf("\nMatr�cula: %d", escola.matricula);
    printf("\nCidade: %s, %s | N: %d\n\n", escola.endereco.cidade, escola.endereco.rua, escola.endereco.numero_da_casa);
}

/*Fun��o que percorre todo o array de alunos e exibe todos*/
void exibir_alunos(aluno *escola)
{   
    int contador = 0;
    for(int i=0; i<quantidade_de_alunos; i++){
        if(escola[i].existe == 1){
            exibe_aluno(escola[i]);
            contador++;
        }
    }
    if(contador == 0) printf("\nN�o existem alunos cadastrados.");
}

/*Fun��o que percorre todo o array e exibe os alunos com a matr�cula fornecida
como � feita uma verifica��o antes de cada cadastro, n�o � poss�vel que tenha
dois alunos com a mesma matr�cula.

OBS: Se a altera��o for feita direta no banco_de_alunos n�o existe verifica��o
de duplicidade de matr�cula. FAZENDO O C�DIGO QUEBRAR!!!*/
void exibe_aluno_por_matricula(aluno *escola, int numero)
{
    int contador=0;
    if(verifica_quantidade_de_alunos(escola) != 0){
        for(int i=0; i<quantidade_de_alunos; i++){
            if(escola[i].matricula == numero){
                exibe_aluno(escola[i]);
                contador++;
            }
        }
        if(contador == 0){
            printf("N�o existe nenhum aluno com essa matr�cula cadastrado.");
        }
    } else printf("N�o existem alunos cadastrados.");
}

/*Fun��o que percorre o array inteiro e exibe os alunos com o nome fornecido*/
void exibe_aluno_por_nome(aluno *escola, char *nome)
{
    int contador=0;
    if(verifica_quantidade_de_alunos(escola) != 0){
        for(int i=0; i<quantidade_de_alunos; i++){
            if(strcmp(escola[i].nome, nome) == 0){
                exibe_aluno(escola[i]);
                contador++;
            }
        }
        if(contador == 0){
            printf("N�o existe nenhum aluno com esse nome cadastrado.");
        }
    } else printf("N�o existem alunos cadastrados.");
}   

/*Fun��o que percorre o array inteiro e exibe os alunos que s�o da
cidade cadastrada*/
void exibe_aluno_por_cidade(aluno *escola, char *cidade)
{
    int contador=0;
    if(verifica_quantidade_de_alunos(escola) != 0){
        for(int i=0; i<quantidade_de_alunos; i++){
            if(strcmp(escola[i].endereco.cidade, cidade) == 0){
                exibe_aluno(escola[i]);
                contador++;
            }
        }
        if(contador == 0){
            printf("N�o existe nenhum aluno dessa cidade cadastrado.");
        }
    } else printf("N�o existem alunos cadastrados.");
}

/*Fun��o que percorre o array inteiro e remove o aluno com a matr�cula
informada.

OBS: A fun��o tamb�m pega os alunos das outras posi��es do array e traz
todos para o �ndice anterior, evitando buracos no array que iriam prejudicar
a fun��o de leitura*/
void remove_aluno_por_matricula(aluno *escola, int matricula)
{
    if(verifica_quantidade_de_alunos(escola) != 0){
        int posicao, contador = 0;
        for(int i=0; i<quantidade_de_alunos; i++){
            if(escola[i].matricula == matricula){
                contador++;
                posicao = i;
                for(int i=posicao; i<quantidade_de_alunos-1; i++){
                    escola[posicao] = escola[i+1];
                }
                printf("O aluno foi removido com sucesso");
                break;
            }
        }
        if(contador == 0) printf("N�o existe aluno com essa matr�cula");
        /*Para zerar o �ltimo elemento a atribui��o deve ser feita dessa forma
        pois dessa forma � poss�vel atribuir diretamente um struct a outro struct, 
        mesmo que ele tenha strings*/
        escola[quantidade_de_alunos-1] = (aluno){0};
    } else printf("N�o existem alunos cadastrados.");
}

//Fun��es de manipula��o de arquivo

//Fun��o de grava��o de arquivo
int grava_txt(aluno *escola)
{
    FILE *banco_de_alunos = fopen("banco_de_alunos.txt", "w");
    if(banco_de_alunos == NULL) {
        printf("N�o foi poss�vel abrir o arquivo");
        return 1;
    }
    for(int i=0; i<quantidade_de_alunos; i++){
        if(escola[i].existe == 1){
            fprintf(banco_de_alunos, "%s\n", escola[i].nome);
            fprintf(banco_de_alunos, "%d\n", escola[i].idade);
            fprintf(banco_de_alunos, "%d\n", escola[i].matricula);
            fprintf(banco_de_alunos, "%d\n", escola[i].existe);
            fprintf(banco_de_alunos, "%s\n", escola[i].endereco.rua);
            fprintf(banco_de_alunos, "%d\n", escola[i].endereco.numero_da_casa);
            fprintf(banco_de_alunos, "%s\n", escola[i].endereco.cidade);
        }
    }
    return 0;
}

/*Essa fun��o tem o tipo do struct para retornar
o �ndice que vai preencher o ponteiro aponta_escola++*/
/*Fun��o de leitura de arquivo*/
aluno* leitura_txt(aluno *escola){
    aluno cadastro = {0};
    FILE *banco_de_alunos = fopen("banco_de_alunos.txt", "r");
    if(banco_de_alunos != NULL){
        for(int i = 0; i < quantidade_de_alunos; i++){
            if(fscanf(banco_de_alunos, "%[^\n]\n", cadastro.nome) != 1) break;
            fscanf(banco_de_alunos, "%d\n", &cadastro.idade);
            fscanf(banco_de_alunos, "%d\n", &cadastro.matricula);
            fscanf(banco_de_alunos, "%d\n", &cadastro.existe);
            fscanf(banco_de_alunos, "%[^\n]\n", cadastro.endereco.rua);
            fscanf(banco_de_alunos, "%d\n", &cadastro.endereco.numero_da_casa);
            fscanf(banco_de_alunos, "%[^\n]\n", cadastro.endereco.cidade);
            cadastrar_aluno(escola, cadastro);
            escola++;
        }
    }
    return escola;
}