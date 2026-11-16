#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//definição fixa do máximo de equipes
#define MAX_EQUIPES 5000

//definição fixa do máximo de problemas que podem ser solucionadas
#define MAX_PROBLEMAS 14

// Estrutura que armazena o desempenho de cada problema.
struct problema {
    //número de tentativas que a equipe realizou
    int tentativas;

    //se o problema foi resolvido ou não, pode ser definido que ser foi resolvido será = 1, se não foi, será igual a 0.
    int resolvido;

    //armazenar o tempo, em minutos, de quanto tempo a equipe consegui concluir esse problema
    int tempo_aceito;
};

// Estrutura que armazena os dados de cada equipe.
struct equipe {
    //armazena o nome da equipe
    char nome[51];

    //armazena qual instituição a equipe está vinculada
    char instituicao[51];

    //armazena os integrantes da equipe. [3] -> armazena quantos integrantes serão cadastrados. [101] -> armazena uma quantidade de espaço para cada integrante cadastrar seu nome
    char integrantes[3][101];

    //interliga com o struct problema
    // vetor com 14 estruturas do tipo problema, representando as questoes de A ate N.
    // cada posicao armazena as tentativas, o status de resolucao e o tempo de aceite de uma questao especifica para a equipe.
    struct problema problemas[MAX_PROBLEMAS];
};

//Observação: todas as funções necessitam da struct equipe para pegar os dados necessários, 
//do vetor equipes[] para guardar ou buscar as equipes e quantidades para contar quantas equipes existem

// Exibe as opcoes disponiveis para o usuario.
void menu() {

    printf("\n========================================\n");
    printf("       MARATONA DE PROGRAMACAO ABC\n");
    printf("========================================\n");

    printf("1 - Cadastrar equipe\n");
    printf("2 - Buscar por instituicao\n");
    printf("3 - Registrar submissao\n");
    printf("4 - Exibir placar\n");
    printf("0 - Sair\n");

}

// CADASTRO DE EQUIPES

//função para validar se existe alguma equipe de mesmo nome
void validar_nome_equipe(struct equipe equipes[], int quantidade){
    int nome_rep = 1; // sinaliza que não há nome repetido
    
    while(nome_rep == 1){
        nome_rep = 0;
    //ver se existe algum nome de equipe igual
        for(int i = 0; i < quantidade; i++){
            //strcmp retorna 0 se os dois nomes forem iguais
            if(strcmp(equipes[quantidade].nome, equipes[i].nome )== 0){
                printf("Nome de equipe já existente. Escolha outro nome:");
                scanf("%50s", &equipes[quantidade].nome);
                nome_rep = 1;
                break;
            }
            
        }
    }
    // //ver se existe algum nome de algum integrante repetido
    // for(int i = 0; i < quantidade; i++){
    //     for(int j = i + 1; j < quantidade; j++){
    //         if(strcmp(equipes[i].integrantes, equipes[j].integrantes == 0)){
    //             printf("")
    //         }
    //     }
    // }
    
}


//função determinada para cadastrar as equipes
int cadastrar_equipe(struct equipe equipes[], int quantidade){
    if(quantidade >= MAX_EQUIPES){
        printf("Número máximo de equipes atingido");
    }
    
    //parte para digitar o nome do usuário
    printf("Digite o nome da equipe: ");
    //o vetor equipes guarda as informações dela, quantidades serve para escolher uma posição no vetor e o nome serve para o user
    //escrever o nome da equipe
    scanf(" %50s", equipes[quantidade].nome);
    printf("\n");
    
    validar_nome_equipe(equipes, quantidade);
        
    
    //OBS.: ESSA PARTE É DE TESTES(por enquanto)
    //parte para escolher a instituição da equipe
    printf("Escolha a instituicao da sua equipe: ");
    //o vetor equipes guarda as informações dela, quantidades serve para escolher uma posição no vetor e a instituição serve para o user
    //escolher qual instituição
    scanf(" %50s", equipes[quantidade].instituicao);
    printf("\n");


    //parte para pegar o nome de cada integrante do grupo
    //o laço é utilizado para delimitar que podem só ser adicionados até 3 integrantes
    for (int integrante = 0; integrante < 3; integrante++) {
        printf("Nome do integrante %d: ", integrante + 1);
        //o vetor equipes guarda as informações dela, quantidades serve para escolher uma posição no vetor e a 
        // variável 'integrante' serve para que possa guardar cada integrante do grupo no vetor 
        scanf(" %100[^\n]", equipes[quantidade].integrantes[integrante]);
    }

    //somador que indica que existe mais uma equipe
    quantidade++;
    printf("Equipe cadastrada com sucesso\n");
    
    //adiciona na própria que existe uma equipe nova adicionada
    return quantidade;
    
}
// -------------------------------------


//BUSCA DE INSTITUIÇÃO

//função para ordenar a busca de instituições em ordem alfabética
// void ordenar_busca_instituicao(struct equipe equipes[], int quantidade){
    
// }
//função determinada para pesquisar uma instituição
void buscar_instituicao(struct equipe equipes[], int quantidade){
        printf("Teste Git");
}
//----------------------------------------------------

//PARTE DE SUBMISSÃO

//registrar submissões(soluções)feitas pela equipe
void registrar_submissao(struct equipe equipes[], int quantidade){
        printf("Teste");

}
//----------------------------------------------------

//PARTE EXIBIÇÃO DO PLACAR

//exibição do placar de quantas tentativas e quanto tempo foi resolvido o problema
void exibir_placar(struct equipe equipes[], int quantidade){
        printf("Teste");

}
//------------------------------------------------

int main(){
        //"puxa" a struct equipes para que tenha algum fim de armazenar, registrar 
        struct equipe equipes[MAX_EQUIPES];

        // variável para ser um contador de quantas equipes foram cadastradas até o momento de execução do código
        int quantidade_equipes = 0;
        int opcao;
        
        menu();
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        
        while(opcao != 0){
            
            switch (opcao) {

                //opção de cadastrar equipes
                case 1:
                    cadastrar_equipe(equipes, quantidade_equipes);
                    break;

                //opção de buscar instituição    
                case 2:
                   buscar_instituicao(equipes, quantidade_equipes);
                    break;

                //opção de registrar submissão, ou seja, registrar por uma equipe a resolução de um problema
                case 3:
                    registrar_submissao(equipes, quantidade_equipes);
                    break;

                //opção que exibe o placar da competição em ordem de quem fez com mais AC ou PE, além de, para critério de desempate, que fez em menor tempo
                case 4:
                    exibir_placar(equipes, quantidade_equipes);
                    break;

                case 0:
                    printf("\nEncerrando o programa...\n");
                    break;

                default:
                    printf("\nOpcao invalida! Tente novamente.\n");
                

            }
    }
}
