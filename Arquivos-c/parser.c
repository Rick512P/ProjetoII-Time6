#include "../Arquivos-h/parser.h"

//RESPONSAVEL POR ABRIR O ARQUIVO E ENCHER A MEMORIA DE INSTRUÇÕES
int parser(Memorias *memoria, int *tamanho_linhas){
    char linha[100], nome_arquivo[200], *token;
    int contador_de_linhas = 0, opcao, contadorAux = 0;
    FILE *arq;
    printf("Digite 1 para utilizar o diretorio padrao ou 2 para entrar com o diretorio do arquivo: ");
    scanf("%d", &opcao);
    if(opcao == 1)
        //arq = fopen("./memoria/testaTodas.mem", "r");
        arq = fopen("./memoria/ExemploAsmBinario.mem", "r");
    else if(opcao == 2){
        printf("Entre com o caminho/nome do arquivo incluindo a extenção .mem\n");
        scanf(" %[^\n]", nome_arquivo);
        arq = fopen(nome_arquivo, "r");
    }
    else{
        printf("Opcao inexistente. Utilizando o diretorio padrao.");
        arq = fopen("./memoria/instrucoes.mem", "r");
    }

    if(arq){

        //primeiro, conto quantas linhas de instruçoes terei no arquivo
        while(fgets(linha, sizeof(linha), arq) != NULL){
            if (strlen(linha) > 19){
                fprintf(stderr, "OVERFLOW. Numero de bits maior que 16."); //FLAG OVERFLOW
                return -1;
            }           
            contador_de_linhas++; 
        }

        //alocaçao de memoria que minha variavel memoria terá será = ao tanto de linhas do arquivo lido
        //*memoria = malloc(contador_de_linhas * sizeof(Memorias));

        if (!memoria) { //se memoria nao ter nada alocado, dará erro.
            fprintf(stderr, "Falha na alocação de memória para instruções.\n"); //stderr envia mensagem de erro
            //separadamente do fluxo principal de saída de um programa
            return 1;
        }

        // Reinicia o arquivo para ler desde a 1° linha
        rewind(arq);
        int i = 0;
        
        while((i<contador_de_linhas) && (i<=255)){ //coloca as instrucoes na memoria (area das instrucoes)
            if (fgets(linha, sizeof(linha), arq) == NULL){
                remove_newline(linha);
                break;
            }        

            if(linha[0] == '\n'){
                i++;
            }

            // Copia a linha para a estrutura memoria

            else{
                if(((memoria)[i].uso != -1))
                    fprintf(stderr, "Instrucao sobrescreveu em endereço ja utilizado por um dado.\n"); //se o uso for terminador nulo, entao esta diponivel
                
                token = strtok(linha,";");
                strncpy((memoria)[i].mem, token, 17);
                
                token = strtok(NULL,";");
                (memoria)[i].uso = atoi(token);
                if (atoi(token) == 0)
                    contadorAux++;
                
                (memoria)[i].mem[sizeof((memoria)[i].mem) - 1] = '\0'; // certifica-se de que a string termina com null terminator
            }

            i++;                
        }     
            fclose(arq);
            printf("Arquivo lido com sucesso!");
    }
    else
        fprintf(stderr, "Erro ao abrir arquivo de instrucoes.");
    *tamanho_linhas = contadorAux;
    return 0; // Retorna 0 indicando sucesso
}