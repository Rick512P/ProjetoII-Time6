#include "../Arquivos-h/memorias.h"


type_instruc Memoria(RegistradoresAux *aux){
        type_instruc traduzido; //DECOMPOE A INSTRUÇÃO EM OPCODE, RS, RT, RD, FUNCT, IMM OU ADDR

        traduzido = decoder(aux); //DECODER IRA DECOMPOR A INSTRUÇÃO
        return traduzido; //retorna para o controller
}

void escreveDado(Memorias *mem, int immediate, char *valor) { //ESCREVE O DADO DA POSICAO DE MEMORIA 128 -> 256
    if (immediate >= 0 && immediate < 256) {
		if((mem)[immediate].uso != -1) //se o uso foi \0, entao sera usado para dados (1)
			printf("Escrita de dado sobrescreveu uma instrucao.\n");
		strcpy((mem)[immediate].mem, "00000000");
        strcat((mem)[immediate].mem, valor);
		(mem)[immediate].uso = 1;
	}
	else {
        fprintf(stderr, "Tentativa de escrita fora dos limites da memória no endereço %d\n", immediate);
    }
}

void imprimeMemoria(Memorias *memoria){
	for (int i = 0; i < 256; i++) {
		if (i < 10)
			printf("Instrucao/Dado armazenada(o) no endereco 00%d da memoria: [%s]\n", i, memoria[i].mem);
		else if (i<100)
			printf("Instrucao/Dado armazenada(o) no endereco 0%d da memoria: [%s]\n", i, memoria[i].mem);
		else
			printf("Instrucao/Dado armazenada(o) no endereco %d da memoria: [%s]\n", i, memoria[i].mem);
	}
}

void escreverArquivoMemoria(Memorias *memoria) {
	FILE *arquivo;
	char nome[256];

	puts("Entre com o nome do arquivo");
	scanf(" %[^\n]", nome);
	strcat(nome,".mem");
	arquivo = fopen(nome, "w");
	
	if(arquivo==NULL){
		fprintf(stderr, "Erro ao abrir o arquivo DATA.dat\n");
	}
	
	for (int i=0; i<256; i++){
		if(memoria[i].uso == 1)
			fprintf(arquivo, "%s;1\n", memoria[i].mem);
		
		else if (memoria[i].uso == 0)
			fprintf(arquivo, "%s;0\n", memoria[i].mem);
		
		else
			fprintf(arquivo, "\n");
	}
	
	fclose(arquivo);
	printf("\nArquivo criado com sucesso!\n\n");
}

void remove_newline(char *line) { //remove a quebra de linha
    size_t len = strcspn(line, "\n");
    if (line[len] == '\n') {
        line[len] = '\0';
    }
}
    

