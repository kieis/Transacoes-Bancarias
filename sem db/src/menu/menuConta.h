#ifndef CONTACORRENTE_H
#define CONTACORRENTE_H

struct ContaCorrente
{
	int conta,   //5 digitos
		digito;  //1 digito
	char cpf[15];//11 digitos
	int	agencia; //4 digitos   

	char nome[100]; //25

	float saldo; //10 digitos, 2 decimais

	ContaCorrente* anterior,
				 * proximo;
};

ContaCorrente* criarConta(void)
{
	ContaCorrente* novaConta = (ContaCorrente*)malloc(sizeof(ContaCorrente));
	if (!vP(novaConta))
		return NULL;

	novaConta->conta = novaConta->digito = novaConta->agencia = 0;
	novaConta->saldo = 0.0f;
	novaConta->anterior = novaConta->proximo = NULL;

	return novaConta;
}

ContaCorrente* criarConta(ContaCorrente* contaAtual, Agencia* agenciaLista[], int conta, int digito, const char* cpf, int agencia, const char* nome, float saldo)
{
	if (!vP(contaAtual))
		return NULL;

	ContaCorrente* novaConta = (ContaCorrente*)malloc(sizeof(ContaCorrente));
	if (!vP(novaConta))
		return contaAtual;

	if (intTamanho(conta) != 5)
	{
		printf("\n-> Não foi possível criar a conta, necessário 5 digitos.\n");
		return contaAtual;
	}

	if (!verificarDigito(conta, digito))
	{
		printf("\n-> Não foi possível criar a conta, digito invalido.\n");
		return contaAtual;
	}

	Agencia* procura = procurarAgencia(agenciaLista, agencia);
	if (!vP(procura))
	{
		printf("\n-> Não foi possível criar a conta, agência invalida.\n");
		return contaAtual;
	}

	novaConta->conta = conta;
	novaConta->digito = digito;
	sprintf(novaConta->cpf, "%s", cpf);
	novaConta->agencia = agencia;
	novaConta->saldo = saldo;
	sprintf(novaConta->nome, "%s", nome);

	ContaCorrente* atual = contaAtual;

	contaAtual->proximo = novaConta;
	contaAtual = novaConta;
	contaAtual->anterior = atual;
	contaAtual->proximo = atual = NULL;

	return novaConta;
}

ContaCorrente* procurarConta(ContaCorrente* contasLista[], int conta, int digito, int agencia)
{
	if (vP(contasLista[INICIO]) && vP(contasLista[FIM]))
	{
		ContaCorrente* contaLoop = contasLista[INICIO];

		while (contaLoop && contaLoop->proximo || contaLoop && contaLoop == contasLista[FIM])
		{
			if (contaLoop != contasLista[INICIO])
				if (contaLoop->conta == conta && contaLoop->digito == digito && contaLoop->agencia == agencia)
					return contaLoop;

			contaLoop = contaLoop->proximo;
		}
	}

	return NULL;
}

bool deletarConta(ContaCorrente* contasLista[], int conta, int digito, int agencia)
{
	if (vP(contasLista[INICIO]) && vP(contasLista[FIM]))
	{
		ContaCorrente* contasLoop = contasLista[INICIO];

		while (contasLoop && contasLoop->proximo || contasLoop && contasLoop == contasLista[FIM])
		{
			if (contasLoop != contasLista[INICIO])
			{
				if (contasLoop->conta == conta && contasLoop->digito == digito && contasLoop->agencia == agencia)
				{
					ContaCorrente* link = contasLoop->proximo;
					ContaCorrente* anlink = contasLoop->anterior;

					if (contasLoop == contasLista[INICIO]->proximo && contasLoop == contasLista[FIM])//inicio == fim
					{
						contasLista[INICIO]->proximo = NULL;
						contasLista[FIM] = contasLista[INICIO];
						free(contasLoop);
					}
					else if (contasLoop == contasLista[INICIO]->proximo) //inicio da fila
					{
						if (link)
						{
							link->anterior = NULL;
							contasLista[INICIO]->proximo = link;
							free(contasLoop);
						}
					}
					else if (contasLoop == contasLista[FIM]) //fim da fila
					{
						if (anlink)
						{
							anlink->proximo = NULL;
							contasLista[FIM] = anlink;
							free(contasLoop);
						}
					}
					else 
					{
						if (anlink)
						{
							anlink->proximo = contasLoop->proximo;
							if (link)
							{
								link->anterior = anlink;
								free(contasLoop);
							}
						}
					}

					return true;
				}
			}

			contasLoop = contasLoop->proximo;
		}
	}

	return false;
}

namespace menuConta
{
	void iniciar(ContaCorrente* contasLista[], Agencia* agenciaLista[]);

	void criar(ContaCorrente* contasLista[], Agencia* agenciaLista[])
	{
		ContaCorrente leitura;

		printf("Nova Conta:\n");
		printf("Número da conta:\n");
		scanf("%i", &leitura.conta);
		
		printf("Digito Verificador:\n");
		scanf("%i", &leitura.digito);

		printf("CPF:\n");
		scanf("%s", &leitura.cpf);

		printf("Agência:\n");
		scanf("%i", &leitura.agencia);

		printf("Nome do Correntista:\n");
		getchar();
		scanf("%[^\n]", &leitura.nome);

		printf("Saldo:\n");
		scanf("%f", &leitura.saldo);

		ContaCorrente* procurar = procurarConta(contasLista, leitura.conta, leitura.digito, leitura.agencia);
		if (!vP(procurar)) {
			ContaCorrente* Anterior = contasLista[FIM];
			contasLista[FIM] = criarConta(contasLista[FIM], agenciaLista, leitura.conta, leitura.digito, leitura.cpf,
				leitura.agencia, leitura.nome, leitura.saldo);

			if (vP(contasLista[FIM]) && Anterior != contasLista[FIM])
				printf("\n-> Conta criada com sucesso.\n");
			else
				printf("-> Falha ao criar conta.\n");
		}
		else {
			printf("\n-> A conta digitada já existe.\n");
		}

		system("pause");
		system("cls");
	}

	void remover(ContaCorrente* contasLista[])
	{
		ContaCorrente leitura;

		printf("Remover conta:\n");
		printf("Número da conta:\n");
		scanf("%i", &leitura.conta);
		printf("Digito:\n");
		scanf("%i", &leitura.digito);
		printf("Agência:\n");
		scanf("%i", &leitura.agencia);

		if (deletarConta(contasLista, leitura.conta, leitura.digito, leitura.agencia))
			printf("-> Conta deletada com sucesso.\n");
		else
			printf("-> Conta não encontrada.\n");

		system("pause");
		system("cls");
	}

	void consultar(ContaCorrente* contasLista[], Agencia* agenciasLista[])
	{
		ContaCorrente leitura;

		printf("Consultar conta:\n");
		printf("Número da conta:\n");
		scanf("%i", &leitura.conta);
		printf("Digito:\n");
		scanf("%i", &leitura.digito);
		printf("Agência:\n");
		scanf("%i", &leitura.agencia);

		TextTable table('\0', '\0', '\0');
		ContaCorrente* consulta = procurarConta(contasLista, leitura.conta, leitura.digito, leitura.agencia);
		if (vP(consulta)) {
			printf("\nConta encontrada:\n");

			table.add("Conta:    ");
			table.add("Digito:    ");
			table.add("Agência:       ");
			table.add("Nome:                     ");
			table.add("Saldo:       ");
			table.add("CPF:       ");
			table.endOfRow();
			
			Agencia* consultaAgencia = procurarAgencia(agenciasLista, consulta->agencia);

			char contaNum[100];
			sprintf(contaNum, "%i", consulta->conta);
			char digitoNum[100];
			sprintf(digitoNum, "%i", consulta->digito);

			char agenciaNum[100];
			if (vP(consultaAgencia))
				sprintf(agenciaNum, "%s [%i]", consultaAgencia->nome, consulta->agencia);

			char saldoNum[100];
			sprintf(saldoNum, "%.2f R$", consulta->saldo);

			table.add(contaNum);
			table.add(digitoNum);
			table.add(agenciaNum);
			table.add(consulta->nome);
			table.add(saldoNum);
			table.add(consulta->cpf);
			table.endOfRow();

			std::cout << table;
		}
		else
			printf("\n-> Conta não encontrada.\n");

		system("pause");
		system("cls");
	}

	void listar(ContaCorrente* contasLista[])
	{
		BOOL bEncontrou = false;

		TextTable table('\0', '\0', '\0');
		if (vP(contasLista[INICIO]) && vP(contasLista[FIM]))
		{
			ContaCorrente* contasLoop = contasLista[INICIO];

			while (contasLoop && contasLoop->proximo || contasLoop && contasLoop == contasLista[FIM])
			{
				if (contasLoop != contasLista[INICIO])
				{
					if (!bEncontrou)
					{
						table.add("Conta:    ");
						table.add("Digito:    ");
						table.add("Agência:       ");
						table.add("Nome:              ");
						table.endOfRow();

						bEncontrou = true;
					}

					char contaNum[100];
					sprintf(contaNum, "%i", contasLoop->conta);
					char digitoNum[100];
					sprintf(digitoNum, "%i", contasLoop->digito);
					char agenciaNum[100];
					sprintf(agenciaNum, "%i", contasLoop->agencia);

					table.add(contaNum);
					table.add(digitoNum);
					table.add(agenciaNum);
					table.add(contasLoop->nome);
					table.endOfRow();

				}
				else if (contasLista[INICIO] == contasLista[FIM] && contasLoop->proximo == NULL)
					printf("-> Lista vazia.\n");

				contasLoop = contasLoop->proximo;
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
		printf("Menu para controle de contas correntes:\n");
		printf("0 - Sair.\n");
		printf("1 - Criar.\n");
		printf("2 - Remover.\n");
		printf("3 - Consultar.\n");
		printf("4 - Listar Contas.\n");
		printf("R: ");

		scanf("%i", &opcao);

		return opcao;
	}
}

#endif