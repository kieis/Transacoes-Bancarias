#ifndef AGENCIA_H
#define AGENCIA_H

struct Agencia
{
	int registro; //4 digitos
	char nome[100], //15
		endereco[100]; //30

	Agencia* anterior,
		   * proximo;
};

Agencia* criarAgencia(void)
{
	Agencia* novaAgencia = (Agencia*)malloc(sizeof(Agencia));
	if (!vP(novaAgencia))
		return NULL;

	novaAgencia->registro = 0;
	novaAgencia->proximo = novaAgencia->anterior = NULL;

	return novaAgencia;
}

Agencia* criarAgencia(Agencia* agenciaAtual, int numero, const char* nome, const char* endereco)
{
	if (!vP(agenciaAtual))
		return NULL;

	if (intTamanho(numero) != 4)
	{
		printf("\n-> N�o foi poss�vel criar a agencia, necess�rio 4 digitos.\n");
		return agenciaAtual;
	}

	Agencia* novaAgencia = (Agencia*)malloc(sizeof(Agencia));
	if (!vP(novaAgencia))
		return agenciaAtual;

	novaAgencia->registro = numero;
	sprintf(novaAgencia->nome, "%s", nome);
	sprintf(novaAgencia->endereco, "%s", endereco);

	Agencia* atual = agenciaAtual;

	agenciaAtual->proximo = novaAgencia;
	agenciaAtual = novaAgencia;
	agenciaAtual->anterior = atual;
	agenciaAtual->proximo = atual = NULL;

	return novaAgencia;
}

Agencia* procurarAgencia(Agencia* agenciaLista[], int numero)
{
	if (vP(agenciaLista[INICIO]) && vP(agenciaLista[FIM]))
	{
		Agencia* agenciaLoop = agenciaLista[INICIO];

		while (agenciaLoop && agenciaLoop->proximo || agenciaLoop && agenciaLoop == agenciaLista[FIM])
		{
			if (agenciaLoop != agenciaLista[INICIO])
				if (agenciaLoop->registro == numero)
					return agenciaLoop;

			agenciaLoop = agenciaLoop->proximo;
		}
	}

	return NULL;
}

bool deletarAgencia(Agencia* agenciaLista[], int numero)
{
	if (vP(agenciaLista[INICIO]) && vP(agenciaLista[FIM]))
	{
		Agencia* agenciaLoop = agenciaLista[INICIO];

		while (agenciaLoop && agenciaLoop->proximo || agenciaLoop && agenciaLoop == agenciaLista[FIM])
		{
			if (agenciaLoop != agenciaLista[INICIO])
			{
				if (agenciaLoop->registro == numero)
				{
					Agencia* link = agenciaLoop->proximo;
					Agencia* anlink = agenciaLoop->anterior;

					if (agenciaLoop == agenciaLista[INICIO]->proximo && agenciaLoop == agenciaLista[FIM])//inicio == fim
					{
						agenciaLista[INICIO]->proximo = NULL;
						agenciaLista[FIM] = agenciaLista[INICIO];
						free(agenciaLoop);
					}
					else if (agenciaLoop == agenciaLista[INICIO]->proximo) //inicio da fila
					{
						if (link)
						{ 
							link->anterior = NULL;
							agenciaLista[INICIO]->proximo = link;
							free(agenciaLoop);
						}
					}
					else if (agenciaLoop == agenciaLista[FIM]) //fim da fila
					{
						if (anlink)
						{
							anlink->proximo = NULL;
							agenciaLista[FIM] = anlink;
							free(agenciaLoop);
						}
					}
					else 
					{
						if (anlink)
						{
							anlink->proximo = agenciaLoop->proximo;
							if (link)
							{
								link->anterior = anlink;
								free(agenciaLoop);
							}
						}
					}

					return true;
				}
			}

			agenciaLoop = agenciaLoop->proximo;
		}
	}

	return false;
}

namespace menuAgencia
{
	void iniciar(Agencia* agenciaLista[]);

	void criar(Agencia* agenciaLista[])
	{
		Agencia leitura;

		printf("Nova Ag�ncia:\n");
		printf("N�mero da ag�ncia:\n");
		scanf("%i", &leitura.registro);

		printf("Nome da ag�ncia:\n");
		getchar();
		scanf("%[^\n]", &leitura.nome);

		printf("Endere�o:\n");
		getchar();
		scanf("%[^\n]", &leitura.endereco);

		Agencia* procurar = procurarAgencia(agenciaLista, leitura.registro);
		if (!vP(procurar)) {
			Agencia* Anterior = agenciaLista[FIM];
			agenciaLista[FIM] = criarAgencia(agenciaLista[FIM], leitura.registro, leitura.nome, leitura.endereco);

			if (vP(agenciaLista[FIM]) && agenciaLista[FIM] != Anterior)
				printf("\n-> Ag�ncia criada com sucesso.\n");
			else
				printf("-> Falha ao criar ag�ncia.\n");
		}
		else
			printf("\n-> A ag�ncia digitada j� existe.\n");


		system("pause");
		system("cls");
	}

	void remover(Agencia* agenciaLista[])
	{
		Agencia leitura;

		printf("Digite o n� da ag�ncia que deseja remover:\n");
		scanf("%i", &leitura.registro);

		if (deletarAgencia(agenciaLista, leitura.registro))
			printf("\n-> Ag�ncia deletada com sucesso.\n");
		else
			printf("\n-> Ag�ncia n�o encontrada.\n");

		system("pause");
		system("cls");
	}

	void consultar(Agencia* agenciaLista[])
	{
		Agencia leitura;

		printf("Digite o n� da ag�ncia para realizar a consulta:\n");
		scanf("%i", &leitura.registro);

		TextTable table('\0', '\0', '\0');
		Agencia* consulta = procurarAgencia(agenciaLista, leitura.registro);
		if (vP(consulta)) {
			printf("\nAg�ncia encontrada:\n");

			table.add("N�mero:          ");
			table.add("Nome:          ");
			table.add("Endere�o:          ");
			table.endOfRow();

			char agenciaNum[4];
			sprintf(agenciaNum, "%i", consulta->registro);

			table.add(agenciaNum);
			table.add(consulta->nome);
			table.add(consulta->endereco);
			table.endOfRow();

			std::cout << table;
		}
		else
			printf("\n-> Ag�ncia n�o encontrada.\n");

		system("pause");
		system("cls");
	}

	void listar(Agencia* agenciaLista[])
	{
		BOOL bEncontrou = FALSE;
		TextTable table('\0', '\0', '\0');

		if (vP(agenciaLista[INICIO]) && vP(agenciaLista[FIM]))
		{
			Agencia* agenciaLoop = agenciaLista[INICIO];

			while (agenciaLoop && agenciaLoop->proximo || agenciaLoop && agenciaLoop == agenciaLista[FIM])
			{
				if (agenciaLoop != agenciaLista[INICIO])
				{
					if (!bEncontrou) {
						table.add("N�mero:          ");
						table.add("Nome:          ");
						table.add("Endere�o:          ");
						table.endOfRow();

						bEncontrou = TRUE;
					}

					char agenciaNum[10];
					sprintf(agenciaNum, "%i", agenciaLoop->registro);

					table.add(agenciaNum);
					table.add(agenciaLoop->nome);
					table.add(agenciaLoop->endereco);
					table.endOfRow();
				}
				else if (agenciaLista[INICIO] == agenciaLista[FIM] && agenciaLoop->proximo == NULL)
					printf("\n-> Lista vazia.\n");

				agenciaLoop = agenciaLoop->proximo;
			}
		}

		if (bEncontrou)
			std::cout << table;

		system("pause");
		system("cls");
	}

	int menu()
	{
		int opcao = 0;
		printf("Menu para controle das ag�ncias:\n");
		printf("0 - Sair.\n");
		printf("1 - Criar.\n");
		printf("2 - Remover.\n");
		printf("3 - Consultar.\n");
		printf("4 - Listar Ag�ncias.\n");
		printf("R: ");

		scanf("%i", &opcao);

		return opcao;
	}
}

#endif