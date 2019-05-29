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
		int menu();

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

		void filaCircular(int& optAtendimentoAoCliente, int Fila[], FilaAtendimento filaAtendimento[], int atendimentoAtual, vector<SenhaAtendimento> senhaInfo, TransacoesBancarias* transacoesLista[], ContaCorrente* contasLista[])
		{
			if (Fila[INICIO] != Fila[FIM])
			{
				if (filaAtendimento[atendimentoAtual].senhaInfo.status == SENHASTATUS::EMITIDA)
				{
					filaAtendimento[atendimentoAtual].Chamada += 1;

					if (filaAtendimento[atendimentoAtual].Chamada <= limiteChamadas)
					{
						printf("Chamada %.2i: Senha[%i].\n", filaAtendimento[atendimentoAtual].Chamada, filaAtendimento[atendimentoAtual].senhaInfo.numero);
						printf("Correntista: %s, comparecer ao caixa %.2i.\n", filaAtendimento[atendimentoAtual].contaCorrentista->nome, filaAtendimento[atendimentoAtual].caixaDesignado->numero);

						system("pause");
						system("cls");

						ContaCorrente leitura;
						printf("Confirme seu atendimento com conta, digito e agência:\n");
						scanf("%i", &leitura.conta);
						scanf("%i", &leitura.digito);
						scanf("%i", &leitura.agencia);

						if (filaAtendimento[atendimentoAtual].contaCorrentista->conta == leitura.conta &&
							filaAtendimento[atendimentoAtual].contaCorrentista->digito == leitura.digito &&
							filaAtendimento[atendimentoAtual].contaCorrentista->agencia == leitura.agencia)
						{
							system("cls");

							while (optAtendimentoAoCliente != 0)
							{
								optAtendimentoAoCliente = menuAtendimento::aoCliente::menu();
								system("cls");

								switch (optAtendimentoAoCliente)
								{
								case 0:
								{
									BOOL bEncontrou = false;
									filaAtendimento[atendimentoAtual].senhaInfo.status = SENHASTATUS::ATENDIDA;
									for (int i = 0; i < senhaInfo.size(); i++) {
										if (senhaInfo[i].numero == filaAtendimento[atendimentoAtual].senhaInfo.numero) {
											bEncontrou = true;
											senhaInfo[i].status = filaAtendimento[atendimentoAtual].senhaInfo.status;
										}
									}
									if (!bEncontrou)
										senhaInfo.push_back(filaAtendimento[atendimentoAtual].senhaInfo);

									filaAtendimento[atendimentoAtual].caixaDesignado->senhasAtendidas += 1;

									if ((atendimentoAtual + 1) % (Fila[FIM] + 1) == 0)
										atendimentoAtual = (Fila[FIM] == 9) ? 0 : Fila[FIM] + 1;
									else
										atendimentoAtual = (atendimentoAtual + 1) % (Fila[FIM] + 1);
								}break;
								case 1:
									menuAtendimento::aoCliente::saque(transacoesLista, filaAtendimento[atendimentoAtual].contaCorrentista, filaAtendimento[atendimentoAtual].caixaDesignado, filaAtendimento[atendimentoAtual].senhaInfo);
									break;
								case 2:
									menuAtendimento::aoCliente::deposito(transacoesLista, filaAtendimento[atendimentoAtual].contaCorrentista, filaAtendimento[atendimentoAtual].caixaDesignado, filaAtendimento[atendimentoAtual].senhaInfo);
									break;
								case 3:
									menuAtendimento::aoCliente::transferencia(transacoesLista, contasLista, filaAtendimento[atendimentoAtual].contaCorrentista, filaAtendimento[atendimentoAtual].caixaDesignado, filaAtendimento[atendimentoAtual].senhaInfo);
									break;
								}
							}
						}
						else {
							printf("\n-> Problema ao confirmar atendimento, conta inválida.\n");
							optAtendimentoAoCliente = 0;

							system("pause");
							system("cls");
						}

						if (filaAtendimento[atendimentoAtual].Chamada == limiteChamadas) {
							BOOL bEncontrou = false;
							filaAtendimento[atendimentoAtual].senhaInfo.status = SENHASTATUS::CANCELADA;
							for (int i = 0; i < senhaInfo.size(); i++) {
								if (senhaInfo[i].numero == filaAtendimento[atendimentoAtual].senhaInfo.numero) {
									bEncontrou = true;
									senhaInfo[i].status = filaAtendimento[atendimentoAtual].senhaInfo.status;
								}
							}
							if (!bEncontrou)
								senhaInfo.push_back(filaAtendimento[atendimentoAtual].senhaInfo);

							if ((atendimentoAtual + 1) % (Fila[FIM] + 1) == 0)
								atendimentoAtual = (Fila[FIM] == 9) ? 0 : Fila[FIM] + 1;
							else
								atendimentoAtual = (atendimentoAtual + 1) % (Fila[FIM] + 1);
						}
					}
				}
				else {
					printf("\n-> Todas as senhas já foram atendidas.\n");
					optAtendimentoAoCliente = 0;

					system("pause");
					system("cls");
				}
			}
			else {
				printf("-> Nenhum atendimento foi solicitado.\n");
				system("pause");
				system("cls");

				optAtendimentoAoCliente = 0;
			}
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