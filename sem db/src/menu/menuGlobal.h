#ifndef GLOBAL_H
#define GLOBAL_H

namespace menuGlobal
{
	int menu()
	{
		int opcao = 0;
		printf("Menu global:\n");
		printf("0 - Finalizar programa.\n");
		printf("1 - Ir at� o menu de Ag�ncias.\n");
		printf("2 - Ir at� o menu de Contas Correntes.\n");
		printf("3 - Ir at� o menu de Caixas.\n");
		printf("4 - Ir at� o menu de Transa��es.\n");
		printf("5 - Ir at� o menu de Consultas Avulsas.\n");
		printf("6 - Ir at� o menu de Novo Atendimento.\n");
		printf("7 - Ir at� o menu de Atendimento ao Cliente.\n");
		printf("R: ");

		scanf("%i", &opcao);

		return opcao;
	}
};

#endif