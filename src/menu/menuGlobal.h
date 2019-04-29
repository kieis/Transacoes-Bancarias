#ifndef GLOBAL_H
#define GLOBAL_H

namespace menuGlobal
{
	int menu()
	{
		int opcao = 0;
		printf("Menu global:\n");
		printf("0 - Finalizar programa.\n");
		printf("1 - Ir até o menu de Agências.\n");
		printf("2 - Ir até o menu de Contas Correntes.\n");
		printf("3 - Ir até o menu de Caixas.\n");
		printf("4 - Ir até o menu de Transações.\n");
		printf("5 - Ir até o menu de Consultas Avulsas.\n");
		printf("6 - Ir até o menu de Novo Atendimento.\n");
		printf("7 - Ir até o menu de Atendimento ao Cliente.\n");
		printf("R: ");

		scanf("%i", &opcao);

		return opcao;
	}
};

#endif