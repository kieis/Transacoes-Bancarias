#ifndef CAIXA_H
#define CAIXA_H

enum SALDOCAIXA
{
	INICIAL,
	ATUAL,
	REPOSICAO
};

struct Caixa
{
	int numero,    //2 dig 0-9
		matricula,
		senhasAtendidas; //5 dig

	char operador[100]; //25

	float saldo[3]; //0 - saldoInicial, 1 - saldo, 2 - reposi��o
	bool caixaAtivo;

	DataHora* dtAbertura,
		    * dtFechamento;
	 
	Caixa* proximo,
		 * anterior;
};

Caixa* criarCaixa(void)
{
	Caixa* novoCaixa = (Caixa*)malloc(sizeof(Caixa));
	if (!vP(novoCaixa))
		return NULL;

	novoCaixa->matricula = novoCaixa->numero = -1;
	novoCaixa->senhasAtendidas = 0;
	novoCaixa->saldo[SALDOCAIXA::INICIAL] = novoCaixa->saldo[SALDOCAIXA::ATUAL] = novoCaixa->saldo[SALDOCAIXA::REPOSICAO] = 0.0f;
	novoCaixa->proximo = NULL;
	novoCaixa->caixaAtivo = FALSE;
	novoCaixa->dtAbertura = novoCaixa->dtFechamento = NULL;

	return novoCaixa;
}

Caixa* criarCaixa(Caixa* caixaAtual, int numero, int matricula, const char* operador, float saldoInicial, bool caixaAberto)
{
	if (!vP(caixaAtual))
		return NULL;

	Caixa* novoCaixa = (Caixa*)malloc(sizeof(Caixa));
	if (!vP(novoCaixa))
		return caixaAtual;

	if (numero > 9 || numero < 0)
	{
		printf("\n-> N�mero do caixa inv�lido, [0...9]");
		return caixaAtual;
	}

	if (intTamanho(matricula) != 5)
	{
		printf("\n-> N�mero da matr�cula inv�lida, necess�rio 5 digitos.");
		return caixaAtual;
	}

	novoCaixa->numero = numero;
	novoCaixa->matricula = matricula;
	novoCaixa->senhasAtendidas = 0;
	sprintf(novoCaixa->operador, "%s", operador);
	bancoSaldo -= saldoInicial;
	novoCaixa->saldo[SALDOCAIXA::INICIAL] = novoCaixa->saldo[SALDOCAIXA::ATUAL] = saldoInicial;
	novoCaixa->saldo[SALDOCAIXA::REPOSICAO] = 0.0f;
	novoCaixa->caixaAtivo = caixaAberto;
	if (caixaAberto) {
		novoCaixa->dtAbertura = new DataHora();
		novoCaixa->dtFechamento = NULL;
	}
	else
		novoCaixa->dtAbertura = novoCaixa->dtFechamento = NULL;

	Caixa* atual = caixaAtual;

	caixaAtual->proximo = novoCaixa;
	caixaAtual = novoCaixa;
	caixaAtual->anterior = atual;
	caixaAtual->proximo = atual = NULL;

	return novoCaixa;
}

Caixa* procurarCaixa(Caixa* caixasLista[], int numero)
{
	if (vP(caixasLista[INICIO]) && vP(caixasLista[FIM]))
	{
		Caixa* caixaLoop = caixasLista[INICIO];

		while (caixaLoop && caixaLoop->proximo || caixaLoop && caixaLoop == caixasLista[FIM])
		{
			if (caixaLoop != caixasLista[INICIO])
				if (caixaLoop->numero == numero)
					return caixaLoop;

			caixaLoop = caixaLoop->proximo;
		}
	}

	return NULL;
}

bool deletarCaixa(Caixa* caixasLista[], int numero)
{
	if (vP(caixasLista[INICIO]) && vP(caixasLista[FIM]))
	{
		Caixa* caixaLoop = caixasLista[INICIO];

		while (caixaLoop && caixaLoop->proximo || caixaLoop && caixaLoop == caixasLista[FIM])
		{
			if (caixaLoop != caixasLista[INICIO])
			{
				if (caixaLoop->numero == numero)
				{
					Caixa* link = caixaLoop->proximo;
					Caixa* anlink = caixaLoop->anterior;

					if (caixaLoop == caixasLista[INICIO]->proximo && caixaLoop == caixasLista[FIM])//inicio == fim
					{
						caixasLista[INICIO]->proximo = NULL;
						caixasLista[FIM] = caixasLista[INICIO];
						free(caixaLoop);
					}
					else if (caixaLoop == caixasLista[INICIO]->proximo) //inicio da fila
					{
						if (link)
						{
							link->anterior = NULL;
							caixasLista[INICIO]->proximo = link;
							free(caixaLoop);
						}
					}
					else if (caixaLoop == caixasLista[FIM]) //fim da fila
					{
						if (anlink)
						{
							anlink->proximo = NULL;
							caixasLista[FIM] = anlink;
							free(caixaLoop);
						}
					}
					else
					{
						if (anlink)
						{
							anlink->proximo = caixaLoop->proximo;
							if (link)
							{
								link->anterior = anlink;
								free(caixaLoop);
							}
						}
					}

					return true;
				}
			}

			caixaLoop = caixaLoop->proximo;
		}
	}

	return false;
}

namespace menuCaixa
{
	void iniciar(Caixa* caixasLista[]);

	void criar(Caixa* caixasLista[])
	{
		Caixa leitura;

		printf("Novo Caixa:\n");
		printf("N�mero do caixa:\n");
		scanf("%i", &leitura.numero);
		printf("Matr�cula do operador:\n");
		scanf("%i", &leitura.matricula);
		printf("Nome do operador:\n");
		getchar();
		scanf("%[^\n]", &leitura.operador);
		printf("Status do caixa(1 - Ativo, 0 - Inativo):\n");
		scanf("%d", &leitura.caixaAtivo);
		printf("Saldo do caixa:\n");
		scanf("%f", &leitura.saldo[SALDOCAIXA::INICIAL]);

		Caixa* procurar = procurarCaixa(caixasLista, leitura.numero);
		if (!vP(procurar)) {
			Caixa* Anterior = caixasLista[FIM];
			caixasLista[FIM] = criarCaixa(caixasLista[FIM], leitura.numero, leitura.matricula, leitura.operador, leitura.saldo[SALDOCAIXA::INICIAL], leitura.caixaAtivo);

			if (vP(caixasLista[FIM]) && caixasLista[FIM] != Anterior)
				printf("\n-> Caixa criado com sucesso.\n");
			else
				printf("-> Falha ao criar caixa.\n");
		}
		else
			printf("\n-> O caixa digitado j� existe.\n");


		system("pause");
		system("cls");
	}

	void remover(Caixa* caixasLista[])
	{
		Caixa leitura;

		printf("Digite o n� do caixa que deseja remover:\n");
		scanf("%i", &leitura.numero);

		if (deletarCaixa(caixasLista, leitura.numero))
			printf("\n-> Caixa deletado com sucesso.\n");
		else
			printf("\n-> Caixa n�o encontrada.\n");

		system("pause");
		system("cls");
	}

	void consultar(Caixa* caixasLista[])
	{
		Caixa leitura;
		
		printf("Digite o n� do caixa para realizar a consulta:\n");
		scanf("%i", &leitura.numero);

		TextTable table('\0', '\0', '\0');
		Caixa* consulta = procurarCaixa(caixasLista, leitura.numero);
		if (vP(consulta)) {
			printf("\nCaixa encontrado:");
			
			table.add("N�mero:     ");
			table.add("Matr�cula:     ");
			table.add("Operador:                  ");
			table.add("Status:     ");
			table.add("Saldo Inicial:     ");
			table.add("Saldo Atual:     ");
			table.add("Reposi��es:     ");
			table.add("Senhas Atendidas:   ");
			table.add("Abriu �s:        ");
			table.add("Fechou �s:     ");
			table.endOfRow();

			char caixaNum[100];
			sprintf(caixaNum, "%.2i", consulta->numero);
			char matricNum[100];
			sprintf(matricNum, "%i", consulta->matricula);
			char saldoIniNum[100];
			sprintf(saldoIniNum, "%.2f R$", consulta->saldo[SALDOCAIXA::INICIAL]);
			char saldoFimNum[100];
			sprintf(saldoFimNum, "%.2f R$", consulta->saldo[SALDOCAIXA::ATUAL]);
			char repoNum[100];
			sprintf(repoNum, "%.2f R$", consulta->saldo[SALDOCAIXA::REPOSICAO]);
			char senhasAten[100];
			sprintf(senhasAten, "%.2i", consulta->senhasAtendidas);

			table.add(caixaNum);
			table.add(matricNum);
			table.add(consulta->operador);
			table.add((consulta->caixaAtivo) ? "Ativo" : "Inativo");
			table.add(saldoIniNum);
			table.add(saldoFimNum);
			table.add(repoNum);
			table.add(senhasAten);
			table.add((consulta->dtAbertura) ? consulta->dtAbertura->paraChar(DATAHORA::DIA_MES_ANO_HORA_MIN) : "N�o foi aberto");
			table.add((consulta->dtFechamento) ? consulta->dtFechamento->paraChar(DATAHORA::DIA_MES_ANO_HORA_MIN) : "N�o foi fechado");
			table.endOfRow();

			std::cout << table;
		}
		else
			printf("\n-> Caixa n�o encontrado.\n");

		system("pause");
		system("cls");
	}

	void abrir(Caixa* caixasLista[])
	{
		Caixa leitura;

		printf("Digite o n� do caixa que deseja abrir:\n");
		scanf("%i", &leitura.numero);

		Caixa* consulta = procurarCaixa(caixasLista, leitura.numero);
		if (vP(consulta)) {
			printf("\nCaixa encontrado:\n");

			if (consulta->caixaAtivo)
				printf("-> O caixa j� est� aberto.\n");
			else
			{
				consulta->caixaAtivo = TRUE;
				if (!vP(consulta->dtAbertura)) {
					consulta->dtAbertura = new DataHora();
					printf("-> O caixa foi aberto com sucesso no dia: %s �s %s.\n", consulta->dtAbertura->paraChar(DATAHORA::DIA_MES_ANO), consulta->dtAbertura->paraChar(DATAHORA::HORA_MIN));
				}
				else {
					printf("-> O caixa foi re-aberto com sucesso\n");
				}
			}
		}
		else
			printf("\n-> Caixa n�o encontrado.\n");

		system("pause");
		system("cls");
	}

	void fechar(Caixa* caixasLista[])
	{
		Caixa leitura;

		printf("Digite o n� do caixa que deseja fechar:\n");
		scanf("%i", &leitura.numero);

		TextTable table('\0', '\0', '\0');
		Caixa* consulta = procurarCaixa(caixasLista, leitura.numero);
		if (vP(consulta)) {
			printf("\nCaixa encontrado:\n");

			table.add("N�mero:     ");
			table.add("Matr�cula:     ");
			table.add("Operador:      ");
			table.add("Saldo Inicial:     ");
			table.add("Saldo Final:       ");
			table.add("Reposi��es:     ");
			table.add("Senhas Atendidas:   ");
			table.add("Abriu �s:        ");
			table.add("Fechou �s:     ");
			table.endOfRow();

			if (!consulta->caixaAtivo)
				printf("-> O caixa j� est� fechado.\n");
			else
			{
				char caixaNum[100];
				sprintf(caixaNum, "%.2i", consulta->numero);
				char matricNum[100];
				sprintf(matricNum, "%i", consulta->matricula);
				char saldoIniNum[100];
				sprintf(saldoIniNum, "%.2f R$", consulta->saldo[SALDOCAIXA::INICIAL]);
				char saldoFimNum[100];
				sprintf(saldoFimNum, "%.2f R$", consulta->saldo[SALDOCAIXA::ATUAL]);
				char repoNum[100];
				sprintf(repoNum, "%.2f R$", consulta->saldo[SALDOCAIXA::REPOSICAO]);
				char senhasAten[100];
				sprintf(senhasAten, "%.2i", consulta->senhasAtendidas);

				consulta->caixaAtivo = FALSE;
				consulta->dtFechamento = new DataHora();

				table.add(caixaNum);
				table.add(matricNum);
				table.add(consulta->operador);
				table.add(saldoIniNum);
				table.add(saldoFimNum);
				table.add(repoNum);
				table.add(senhasAten);
				table.add((consulta->dtAbertura) ? consulta->dtAbertura->paraChar(DATAHORA::DIA_MES_ANO_HORA_MIN) : "N�o foi aberto");
				table.add((consulta->dtFechamento) ? consulta->dtFechamento->paraChar(DATAHORA::DIA_MES_ANO_HORA_MIN) : "N�o foi fechado");
				table.endOfRow();

				std::cout << table;
			}
		}
		else
			printf("\n-> Caixa n�o encontrado.\n");

		system("pause");
		system("cls");
	}

	void listar(Caixa* caixasLista[])
	{
		BOOL bEncontrou = FALSE;
		TextTable table('\0', '\0', '\0');

		if (vP(caixasLista[INICIO]) && vP(caixasLista[FIM]))
		{
			Caixa* caixaLoop = caixasLista[INICIO];

			while (caixaLoop && caixaLoop->proximo || caixaLoop && caixaLoop == caixasLista[FIM])
			{
				if (caixaLoop != caixasLista[INICIO])
				{
					if (!bEncontrou) {
						table.add("N�mero:          ");
						table.add("Operador:                    ");
						table.add("Status:          ");
						table.endOfRow();

						bEncontrou = TRUE;
					}

					char caixaNum[10];
					sprintf(caixaNum, "%.2i", caixaLoop->numero);

					table.add(caixaNum);
					table.add(caixaLoop->operador);
					table.add((caixaLoop->caixaAtivo) ? "Ativo" : "Inativo");
					table.endOfRow();
				}
				else if (caixasLista[INICIO] == caixasLista[FIM] && caixaLoop->proximo == NULL)
					printf("\n-> Lista vazia.\n");

				caixaLoop = caixaLoop->proximo;
			}
		}

		if (bEncontrou)
			std::cout << table;

		system("pause");
		system("cls");
	}

	void repor(Caixa* caixasLista[])
	{
		Caixa leitura;

		printf("Digite o n� do caixa que deseja repor, quantia:\n");
		scanf("%i", &leitura.numero);
		scanf("%f", &leitura.saldo[SALDOCAIXA::REPOSICAO]);

		Caixa* consulta = procurarCaixa(caixasLista, leitura.numero);
		if (vP(consulta)) {
			printf("\nCaixa encontrado:\n");

			if (consulta->caixaAtivo) {
				if (leitura.saldo[SALDOCAIXA::ATUAL] <= bancoSaldo)
				{
					bancoSaldo -= leitura.saldo[SALDOCAIXA::REPOSICAO];
					consulta->saldo[SALDOCAIXA::ATUAL] += leitura.saldo[SALDOCAIXA::REPOSICAO];
					consulta->saldo[SALDOCAIXA::REPOSICAO] += leitura.saldo[SALDOCAIXA::REPOSICAO];

					printf("\n-> Reposi��o efetuada com sucesso:\n");
					printf("-> Saldo Inicial: %.2f R$.\n", consulta->saldo[SALDOCAIXA::INICIAL]);
					printf("-> Somat�rio de Reposi��es: %.2f R$.\n", consulta->saldo[SALDOCAIXA::REPOSICAO]);
					printf("-> Saldo Atual: %.2f R$.\n", consulta->saldo[SALDOCAIXA::ATUAL]);
				}
				else
					printf("\n-> N�o � poss�vel fazer a reposi��o.\n");
			}
			else
				printf("-> O caixa est� Inativo.\n");
		}
		else
			printf("\n-> Caixa n�o encontrado.\n");

		system("pause");
		system("cls");
	}

	int menu()
	{
		int opcao = 0;
		printf("Menu para controle dos caixas:\n");
		printf("0 - Sair.\n");
		printf("1 - Criar.\n");
		printf("2 - Remover.\n");
		printf("3 - Consultar.\n");
		printf("4 - Abrir Caixa.\n");
		printf("5 - Fechar Caixa.\n");
		printf("6 - Listar Caixas.\n");
		printf("7 - Reposi��o.\n");
		printf("R: ");

		scanf("%i", &opcao);

		return opcao;
	}
}

#endif