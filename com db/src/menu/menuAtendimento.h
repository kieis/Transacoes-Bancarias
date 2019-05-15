#ifndef MENUATENDIMENTO_H
#define MENUATENDIMENTO_H

int limiteChamadas = 2;

struct FilaAtendimento
{
	Caixa* caixaDesignado;
	ContaCorrente* contaCorrentista;
	SenhaAtendimento senhaInfo;
	int Chamada;
};

int gerarSenha(int min, int max, bool rnd)
{
	if (rnd)
		srand(time(NULL));

	return rand() % max + min;
}

bool gerarSenha(FilaAtendimento filaAtendimento[], int Fila[], int max, int &senha)
{
	int cFila = (Fila[FIM] + 1) % max;
	
	if (filaAtendimento[cFila].senhaInfo.status != SENHASTATUS::EMITIDA)
	{
		Fila[FIM] = cFila;
		senha += 1;
		filaAtendimento[Fila[FIM]].senhaInfo.status = SENHASTATUS::EMITIDA;
		filaAtendimento[Fila[FIM]].senhaInfo.dtH = new DataHora();
		filaAtendimento[Fila[FIM]].senhaInfo.numero = senha;

		return TRUE;
	}

	return FALSE;
}

namespace menuAtendimento
{
	void novo(ContaCorrente* contasLista[], Caixa* caixasLista[], vector<SenhaAtendimento>& senhaInfo, vector<Caixa*> caixasAtivos, int& caixaAtual, FilaAtendimento filaAtendimento[], int Fila[], int maxFila, int& Senha)
	{
		vector<Caixa*> checarCaixas;

		for (int i = 0; i < 10; i++)
		{
			Caixa* procura = procurarCaixa(caixasLista, i);
			if (vP(procura))
			{
				if (procura->caixaAtivo) {
					checarCaixas.push_back(procura);
				}
			}
		}

		caixasAtivos = checarCaixas;

		if (caixasAtivos.size() > 0)
		{
			ContaCorrente leitura;
			printf("Informe seus dados:\n");
			printf("Número da conta:\n");
			scanf("%i", &leitura.conta);
			printf("Digito:\n");
			scanf("%i", &leitura.digito);
			printf("Agência:\n");
			scanf("%i", &leitura.agencia);

			ContaCorrente* procura = procurarConta(contasLista, leitura.conta, leitura.digito, leitura.agencia);
			if (vP(procura))
			{
				if (gerarSenha(filaAtendimento, Fila, maxFila, Senha))
				{
					filaAtendimento[Fila[FIM]].contaCorrentista = procura;
					filaAtendimento[Fila[FIM]].caixaDesignado = caixasAtivos[caixaAtual];
					filaAtendimento[Fila[FIM]].Chamada = 0;
					senhaInfo.push_back(filaAtendimento[Fila[FIM]].senhaInfo);

					printf("\n%s\nSua senha de atendimento é: %i.\n", filaAtendimento[Fila[FIM]].senhaInfo.dtH->paraChar(DATAHORA::DIA_MES_ANO_HORA_MIN), Senha);
					caixaAtual = (caixaAtual + 1) % caixasAtivos.size();
				}
				else
					printf("\nSem senhas de atendimento disponíveis.\n");
			}
			else
				printf("\n-> Conta digitada inválida.\n");
		}
		else {
			printf("\n-> Não há caixas disponíveis.\n");
		}

		system("pause");
		system("cls");
	}

	int menu()
	{
		int opcao = 0;
		printf("Novo Atendimento:\n");
		printf("0 - Sair.\n");
		printf("1 - Nova Senha.\n");
		printf("R: ");

		scanf("%i", &opcao);

		return opcao;
	}

	namespace aoCliente
	{
		void saque(TransacoesBancarias* transacoesLista[], ContaCorrente* contaAtual, Caixa* caixaDesignado, SenhaAtendimento senhaAtual)
		{
			float valor;
			printf("Atendimento ao cliente:\n");
			printf("Insira o valor para saque:\n");
			scanf("%f", &valor);

			TransacoesBancarias* anterior = transacoesLista[FIM];
			transacoesLista[FIM] = criarTransacao(transacoesLista[FIM], caixaDesignado, senhaAtual, "SQ", contaAtual, NULL, valor);
			
			if (vP(transacoesLista[FIM]) && transacoesLista[FIM] != anterior)
				printf("");
			else
				printf("\n-> Falha ao realizar o saque.\n");
				
			system("pause");
			system("cls");
		}

		void deposito(TransacoesBancarias* transacoesLista[], ContaCorrente* contaAtual, Caixa* caixaDesignado, SenhaAtendimento senhaAtual)
		{
			float valor;
			printf("Atendimento ao cliente:\n");
			printf("Insira o valor para deposito:\n");
			scanf("%f", &valor);

			TransacoesBancarias* anterior = transacoesLista[FIM];
			transacoesLista[FIM] = criarTransacao(transacoesLista[FIM], caixaDesignado, senhaAtual, "DP", contaAtual, NULL, valor);

			if (vP(transacoesLista[FIM]) && transacoesLista[FIM] != anterior)
				printf("");
			else
				printf("\n-> Falha ao realizar o deposito.\n");

			system("pause");
			system("cls");
		}

		void transferencia(TransacoesBancarias* transacoesLista[], ContaCorrente* contasLista[], ContaCorrente* contaAtual, Caixa* caixaDesignado, SenhaAtendimento senhaAtual)
		{
			float valor;
			ContaCorrente leitura;

			printf("Atendimento ao cliente:\n");
			printf("Insira o valor para transferência:\n");
			scanf("%f", &valor);
			printf("Insira a conta de destino:\n");
			scanf("%i", &leitura.conta);
			printf("Insira o digito da conta de destino:\n");
			scanf("%i", &leitura.digito);
			printf("Insira a agencia da conta de destino:\n");
			scanf("%i", &leitura.agencia);

			ContaCorrente* destino = procurarConta(contasLista, leitura.conta, leitura.digito, leitura.agencia);
			if (vP(destino) && destino != contaAtual)
			{
				TransacoesBancarias* anterior = transacoesLista[FIM];
				transacoesLista[FIM] = criarTransacao(transacoesLista[FIM], caixaDesignado, senhaAtual, "TV", contaAtual, destino, valor);

				if (vP(transacoesLista[FIM]) && transacoesLista[FIM] != anterior)
					printf("");
				else
					printf("\n-> Falha ao realizar o transferência.\n");
			}
			else {
				printf("\n-> Falha ao realizar o transferência, conta de destino inválida.\n");
			}

			system("pause");
			system("cls");
		}

		int menu()
		{
			int opcao = 0;
			printf("Atendimento ao cliente:\n");
			printf("0 - Sair.\n");
			printf("1 - Saque.\n");
			printf("2 - Deposito.\n");
			printf("3 - Transferência.\n");
			printf("R: ");

			scanf("%i", &opcao);

			return opcao;
		}
	}
}

#endif