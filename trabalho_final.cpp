#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//definição fixa do máximo de equipes
#define MAX_EQUIPES 5

//definição fixa do máximo de problemas que podem ser solucionadas
#define MAX_PROBLEMAS 14

//Tamanho máximo de nomes de organizações (equipes e instituições)
#define TAM_MAX_NOME_ORG 51

//Tamanho máximo de nomes próprios
#define TAM_MAX_NOME_PRO 101

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
    char nome[TAM_MAX_NOME_ORG];

    //armazena qual instituição a equipe está vinculada
    char instituicao[TAM_MAX_NOME_ORG];

    //armazena os integrantes da equipe. [3] -> armazena quantos integrantes serão cadastrados. 
    //[TAM_MAX_NOME_PRO] -> armazena uma quantidade de espaço para cada integrante cadastrar seu nome.

    char integrantes[3][TAM_MAX_NOME_PRO];

    //interliga com o struct problema
    // vetor com 14 estruturas do tipo problema, representando as questoes de A ate N.
    // cada posicao armazena as tentativas, o status de resolucao e o tempo de aceite de uma questao especifica para a equipe.
    problema problemas[MAX_PROBLEMAS];
};

//Observação: todas as funções necessitam da struct equipe para pegar os dados necessários, 
//do vetor equipes[] para guardar ou buscar as equipes e quantidades para contar quantas equipes existem


// LIMPEZA DO BUFFER DO CONSOLE
//Função para limpar o buffer do console
void limpa_buffer() {
    int come_lixo;
    while ((come_lixo = getchar()) != '\n' && come_lixo != EOF);
}

// CADASTRO DE EQUIPES

//função para contar quantas equipes já foram cadastradas
int contar_equipes(equipe equipes[]){
    int total = 0;

    //loop que só irá contar a equipe se a quantidade máxima de equipes for menor do que a definida
    // e se o nome for diferente de vazio
    while(total < MAX_EQUIPES && equipes[total].nome[0] != '\0'){
        total++;
    }
    return total;
}

//função para validar se existe alguma equipe de mesmo nome
int validar_nome_equipe(equipe equipes[], int quantidade){
    char sim_nao;  
    //ver se existe algum nome de equipe igual
        for(int i = 0; i < quantidade; i++){
            //strcmp retorna 0 se os dois nomes forem iguais
            if(strcmp(equipes[quantidade].nome, equipes[i].nome )== 0){
                printf("Nome de equipe já existente. Deseja atualizar os dados da equipe?(S ou N)\n");
                scanf(" %c", &sim_nao);

                //loop se o usuário digitar alguma letra ou algo diferente de S ou N
                while(sim_nao != 'S' && sim_nao != 's' && sim_nao != 'N' &&sim_nao != 'n'){
                    printf("Resposta Incorreta. Digite S ou N\n");
                    scanf(" %c", &sim_nao);
                }

                limpa_buffer();

                if(sim_nao == 'S' ||sim_nao == 's'){
                    return i; //retorna aonde é a posição que será alterada
                }else if(sim_nao == 'N' || sim_nao == 'n'){
                    //Obs.: não foi utilizado 0 e 1 por conta das posições do vetor 0 e 1.
                    //Por isso, os returns estão como -1 e -2, mas poderiam ser, por exemplo, -5, -6
                    return -2; //existe, porém não quer atualizar
                }
            }
            
        }
        //nome novo, porque quando se encontra algo e não retorna, retorna -1.  
        //Por isso, nós pensamos em colocar -1 para quando não retornar nada, ser uma opção de nome novo
        return -1; 
    }
    //código que será utilizado, talvez, em breve
    // //ver se existe algum nome de algum integrante repetido
    // for(int i = 0; i < quantidade; i++){
    //     for(int j = i + 1; j < quantidade; j++){
    //         if(strcmp(equipes[i].integrantes, equipes[j].integrantes == 0)){
    //             printf("")
    //         }
    //     }
    // }
    


//função para perguntar se o usuário quer voltar para o menu
int perguntar_voltar(){
    char voltar = 0;

    printf("Deseja voltar ao menu? (S ou N): \n");
        scanf(" %c", &voltar);

    while(voltar != 'S' && voltar != 's' && voltar != 'N' && voltar != 'n'){
        printf("Resposta incorreta. Digite S ou N");
        scanf(" %c", &voltar);
    }
    //serve para quando o usuário colocar S ou s, ele guarda a equipe e vai direto para a main para voltar para a função
    if(voltar == 'S' || voltar == 's'){
        return 1;
    }
    return 0;
}

//função determinada para cadastrar as equipes
int cadastrar_equipe(equipe equipes[], int quantidade){

    //variável que diz que o loop continuará, somente irá parar para ir para a função perguntar_voltar se retornar 1
    int voltar_menu  = 0;

    //indica a posição do vetor aonde os dados serão gravados
    int posicao;
    //diz que enquanto o usuário não der S ou s, o código continua, se apertar essa opção, ele voltará ao menu com as opções
    while(voltar_menu == 0){
        printf("DEBUG: quantidade ao entrar = %d\n", quantidade);
        //Limpa o buffer do console
        limpa_buffer();

        if(quantidade >= MAX_EQUIPES){
            printf("Limite de equipes máximas atingido!");
            //serve para que pare de gravar as equipes no vetor quando o valor é chegado ao limite
            return quantidade;
        }

        //parte para digitar o nome da equipe
        printf("Digite o nome da equipe: ");
        //o vetor equipes guarda as informações dela, quantidades serve para escolher uma posição no vetor e o nome serve para o user
        //escrever o nome da equipe
        fgets(equipes[quantidade].nome, TAM_MAX_NOME_ORG, stdin );
        printf("\n");

        //função para validar corretamente se o nome da equipe está declarado dentro dos termos previstos
        posicao = validar_nome_equipe(equipes, quantidade);
        //condição que colocará vazio se o usuário não quer atualizar o cadastro
        if(posicao == -2){
            equipes[quantidade].nome[0] = '\0';
            printf("Operação cancelada\n");
            voltar_menu = perguntar_voltar();
            continue;
        }else if(posicao == -1){
            //nome novo: grava na posicao livre
            posicao = quantidade;             
        }else{
            //atualizacao: limpa o nome lido na posicao livre
            equipes[quantidade].nome[0] = '\0';  
        }
        

        //parte para escolher a instituição da equipe
        printf("Escolha a instituicao da sua equipe: ");
        //o vetor equipes guarda as informações dela, quantidades serve para escolher uma posição no vetor e a instituição serve para o user
        //escolher qual instituição
        fgets(equipes[quantidade].instituicao, TAM_MAX_NOME_ORG, stdin );
        printf("\n");


        //parte para pegar o nome de cada integrante do grupo
        //o laço é utilizado para delimitar que podem só ser adicionados até 3 integrantes
        for (int integrante = 0; integrante < 3; integrante++) {
            printf("Nome do integrante %d: ", integrante + 1);

            //o vetor equipes guarda as informações dela, quantidades serve para escolher uma posição no vetor e a
            // variável 'integrante' serve para que possa guardar cada integrante do grupo no vetor
            fgets(equipes[quantidade].integrantes[integrante], TAM_MAX_NOME_PRO, stdin);
        }

        //somador que indica que existe mais uma equipe
        quantidade++;
        printf("Dados Cadastrados com sucesso\n");
        voltar_menu = perguntar_voltar();
        
    }
    //serve para retornar um valor definido que a variável está armazenando das equipes, sem ele, não seria armazenado uma equipe
    //para uma consulta de instituição, por exemplo
    return quantidade;
}
// -------------------------------------


//BUSCA DE INSTITUIÇÃO

//função para ordenar a busca de instituições em ordem alfabética
// void ordenar_busca_instituicao(struct equipe equipes[], int quantidade){
    
// }
//função determinada para pesquisar uma instituição
void buscar_instituicao(equipe equipes[], int quantidade){
    //Buscar pelo nome da instituição
    char buscar[TAM_MAX_NOME_ORG];

    //ordenar a posição das equipes 
    int indice[MAX_EQUIPES];

    //quantas equipes foram encontradas
    int total = 0; 
        printf("Teste Git");
}
//----------------------------------------------------

//PARTE DE SUBMISSÃO

//registrar submissões(soluções)feitas pela equipe
void registrar_submissao(equipe equipes[], int quantidade){
        printf("Teste");

}
//----------------------------------------------------

//PARTE EXIBIÇÃO DO PLACAR

//exibição do placar de quantas tentativas e quanto tempo foi resolvido o problema
void exibir_placar(equipe equipes[], int quantidade){
        printf("Teste");

}
//------------------------------------------------

// Exibe o menu para o usuário e coleta a entrada do mesmo, iniciando a função desejada.
int menu(equipe equipes[], int quantidade_equipes) {
    
    int opcao;

    //a variável apresentada irá ser igual a função de contar_equipes que serve para contar 
    // a quantidade de equipes no vetor equipes
    quantidade_equipes = contar_equipes(equipes);

    //Limpa a tela antes de imprimir o menu
    system("cls");

    //Título decorado para a interface
    printf("\n========================================\n");
    printf("       MARATONA DE PROGRAMACAO ABC\n");
    printf("========================================\n");

    //Lista de opções para o usuário
    printf("1 - Cadastrar equipe\n");
    printf("2 - Buscar por instituicao\n");
    printf("3 - Registrar submissao\n");
    printf("4 - Exibir placar\n");
    printf("0 - Sair\n");

    printf("\nEscolha uma opcao: ");
    scanf("%d", &opcao);

        switch (opcao) {
            //opção de cadastrar equipes
            case 1:
                quantidade_equipes += cadastrar_equipe(equipes, quantidade_equipes);
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

                //Fechar o programa
            case 0:
                printf("\nEncerrando o programa...\n");

                //Limpar o \n da última entrada do usuário
                getchar();
                //Espera o \n do usuário, assim tendo tempo para o usuário ler a mensagem de erro
                getchar();
                break;

                //Caso o usuário insira uma opção inválida
            default:
                printf("\nOpcao invalida! Por favor digite uma opcao valida.\n");

                //Limpar o \n da última entrada do usuário
                getchar();
                //Espera o \n do usuário, assim tendo tempo para o usuário ler a mensagem de erro
                getchar();
                break;
        }

    return opcao;
}

//Declaração da main
int main(){
    //Declara a variável(struct) equipes, do tipo equipe.
    equipe equipes[MAX_EQUIPES];

    // variável para ser um contador de quantas equipes foram cadastradas até o momento de execução do código
    int quantidade_equipes = 0;

    //Declara variável continua e atribui 1 pra garantir que o menu será impresso, futuramente ela armazenará
    //a opção do usuário no menu.
    int continua = 1;

    //Continua imprimindo o menu até que o usuário não queira mais
    while (continua != 0)
        continua = menu(equipes, quantidade_equipes); //Muda o valor de continua para a opção selecionada pelo usuário no menu
}