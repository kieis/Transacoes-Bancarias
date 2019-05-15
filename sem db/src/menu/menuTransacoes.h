#ifndef MENUTRANSACOES_H
#define MENUTRANSACOES_H

enum SENHASTATUS
{
	EMITIDA,
	ATENDIDA,
	CANCELADA
};

struct SenhaAtendimento
{
	int numero;
	DataHora* dtH;
	SENHASTATUS status;
};

struct TransacoesBancarias
{
	DataHora* dataHora;
	Caixa* caixa; //numero do caixa
	SenhaAtendimento senhaInfo; //numero da senha

	char tipo[2]; //SQ – saque, DP – depósito e TV – transferência de valor

	float valor; //valor da transação
	float origemSaldo, destinoSaldo;

	int origem[3], destino[3]; //conta, digito, agencia

	TransacoesBancarias* proximo,
		*anterior;
};

TransacoesBancarias* criarTransacao(void)
{
	TransacoesBancarias* novaTransacao = (TransacoesBancarias*)malloc(sizeof(TransacoesBancarias));
	if (!vP(novaTransacao))
		return NULL;

	novaTransacao->dataHora = NULL;
	novaTransacao->caixa = NULL;
	novaTransacao->tipo[0] = novaTransacao->tipo[1] ='\0';
	novaTransacao->valor = 0.0f;
	for (int i = 0; i < 4; i++)
		novaTransacao->origem[i] = novaTransacao->destino[i] = 0;
	novaTransacao->proximo = novaTransacao->anterior = NULL;

	return novaTransacao;
}

TransacoesBancarias* criarTransacao(TransacoesBancarias* transacaoAtual, Caixa* caixa, SenhaAtendimento senhaInfo, const char* tipoTransacao, ContaCorrente* contaOrigem, ContaCorrente* contaDestino, float valor)
{
	char transacoes[3][3] = { "SQ", "DP", "TV" };

	if (!vP(transacaoAtual))
		return NULL;

	if (!vP(caixa))
	{
		printf("\n-> Caixa Inválido.");
		return transacaoAtual;
	}

	int contador = 0;
	for (int i = 0; i < 3; i++) {
		if (!strstr(tipoTransacao, transacoes[i])) {
			contador += 1;
		}
	}

	if (contador == 3)
	{
		printf("\n-> Tipo de transação inválida: %s.", tipoTransacao);
		return transacaoAtual;
	}

	TransacoesBancarias* novaTransacao = (TransacoesBancarias*)malloc(sizeof(TransacoesBancarias));
	if (!vP(novaTransacao))
		return transacaoAtual;

	novaTransacao->dataHora = new DataHora();
	novaTransacao->caixa = caixa;
	novaTransacao->senhaInfo = senhaInfo;
	novaTransacao->valor = valor;
	sprintf(novaTransacao->tipo, "%s", tipoTransacao);

	if (strstr(tipoTransacao, transacoes[0])) //SQ
	{
		if (!vP(contaOrigem))
		{
			free(novaTransacao);
			printf("\n-> Conta de Origem inválida.");
			return transacaoAtual;
		}

		if (valor > caixa->saldo[SALDOCAIXA::ATUAL])
		{
			free(novaTransacao);
			printf("\n-> Valor inserido indiponível para saque, o saque máximo atual é de: %.2f R$.", caixa->saldo[SALDOCAIXA::ATUAL]);
			return transacaoAtual;
		}

		if (valor > contaOrigem->saldo)
		{
			free(novaTransacao);
			printf("\n-> Valor solicitado excede o saldo da conta, transação cancelada.");
			return transacaoAtual;
		}

		novaTransacao->origem[0/*conta*/] = contaOrigem->conta;
		novaTransacao->origem[1/*digito*/] = contaOrigem->digito;
		novaTransacao->origem[2/*agencia*/] = contaOrigem->agencia;
		novaTransacao->origemSaldo = contaOrigem->saldo;

		contaOrigem->saldo -= valor;
		caixa->saldo[SALDOCAIXA::ATUAL] -= valor;

		printf("\nSaque de %.2f R$ realizado com sucesso, seu saldo agora é de: %.2f R$.\n", valor, contaOrigem->saldo);
	}
	else if (strstr(tipoTransacao, transacoes[1])) //DP
	{
		if (!vP(contaOrigem))
		{
			free(novaTransacao);
			printf("\n-> Conta de Origem inválida.");
			return transacaoAtual;
		}

		novaTransacao->origem[0/*conta*/] = contaOrigem->conta;
		novaTransacao->origem[1/*digito*/] = contaOrigem->digito;
		novaTransacao->origem[2/*agencia*/] = contaOrigem->agencia;
		novaTransacao->origemSaldo = contaOrigem->saldo;

		contaOrigem->saldo += valor;
		caixa->saldo[SALDOCAIXA::ATUAL] += valor;

		printf("\nDeposito de %.2f R$ realizado com sucesso, seu saldo agora é de: %.2f R$.\n", valor, contaOrigem->saldo);
	}
	else if (strstr(tipoTransacao, transacoes[2])) //TV
	{
		if (!vP(contaOrigem))
		{
			free(novaTransacao);
			printf("\n-> Conta de Origem inválida.");
			return transacaoAtual;
		}

		if (!vP(contaDestino))
		{
			free(novaTransacao);
			printf("\n-> Conta de Destino inválida.");
			return transacaoAtual;
		}

		if (valor > contaOrigem->saldo)
		{
			free(novaTransacao);
			printf("\n-> Valor solicitado excede o saldo da conta, transação cancelada.");
			return transacaoAtual;
		}

		novaTransacao->origem[0/*conta*/] = contaOrigem->conta;
		novaTransacao->origem[1/*digito*/] = contaOrigem->digito;
		novaTransacao->origem[2/*agencia*/] = contaOrigem->agencia;
		novaTransacao->origemSaldo = contaOrigem->saldo;

		contaOrigem->saldo -= valor;

		novaTransacao->destino[0/*conta*/] = contaDestino->conta;
		novaTransacao->destino[1/*digito*/] = contaDestino->digito;
		novaTransacao->destino[2/*agencia*/] = contaDestino->agencia;
		novaTransacao->destinoSaldo = contaDestino->saldo;

		contaDestino->saldo += valor;

		printf("\nTranferência de %.2f R$ realizado com sucesso, seu saldo agora é de: %.2f R$.\n", valor, contaOrigem->saldo);
	}

	TransacoesBancarias* atual = transacaoAtual;

	transacaoAtual->proximo = novaTransacao;
	transacaoAtual = novaTransacao;
	transacaoAtual->anterior = atual;
	transacaoAtual->proximo = atual = NULL;

	return novaTransacao;
}

void consultarExtrato(TransacoesBancarias* transacoesLista[], ContaCorrente* conta, int dataInicio[], int dataFim[])
{
	BOOL bEncontrou = FALSE;

	if (vP(transacoesLista[INICIO]) && vP(transacoesLista[FIM]))
	{
		TransacoesBancarias* transacoesLoop = transacoesLista[INICIO];
		TextTable table('\0', '\0', '\0');

		while (transacoesLoop && transacoesLoop->proximo || transacoesLoop && transacoesLoop == transacoesLista[FIM])
		{
			if (transacoesLoop != transacoesLista[INICIO])
			{
				BOOL bDestino = false, bOrigem = false;

				if ((transacoesLoop->origem[0] == conta->conta && 
					 transacoesLoop->origem[1] == conta->digito && 
					 transacoesLoop->origem[2] == conta->agencia))
					bOrigem = true;
				else if ((transacoesLoop->destino[0] == conta->conta && 
					transacoesLoop->destino[1] == conta->digito && 
					transacoesLoop->destino[2] == conta->agencia))
					bDestino = true;

				if (bDestino || bOrigem)
				{
					if (
						(
						 (transacoesLoop->dataHora->hora >= dataInicio[0] &&
						  transacoesLoop->dataHora->min >= dataInicio[1] &&
						  transacoesLoop->dataHora->seg >= dataInicio[2]
						 ) 
						 &&
						 (transacoesLoop->dataHora->hora <= dataFim[0] &&
						  transacoesLoop->dataHora->min <= dataFim[1] &&
						  transacoesLoop->dataHora->seg <= dataFim[2]
						 )
						) 
						|| 
						(checarVetor(dataInicio, 0, 3) && checarVetor(dataFim, 0, 3))
					   )
					{
						if (!bEncontrou) {
							table.add("Agência:      ");
							table.add("Conta:      ");
							table.add("Digito:      ");
							table.add("Saldo Inicial:      ");
							table.add("Data:      ");
							table.add("Tipo:      ");
							table.add("Valor:      ");
							table.add("Saldo Final:      ");
							table.endOfRow();

							bEncontrou = TRUE;
						}

						char sinal = '-';
						if (strstr(transacoesLoop->tipo, "SQ"))
							sinal = '-';
						else if (strstr(transacoesLoop->tipo, "DP"))
							sinal = '+';
						else if (bOrigem && strstr(transacoesLoop->tipo, "TV"))
							sinal = '-';
						else if (bDestino && strstr(transacoesLoop->tipo, "TV"))
							sinal = '+';
						else
							sinal = '?';

						char contaNum[100];
						sprintf(contaNum, "%i", conta->conta);
						char digitoNum[100];
						sprintf(digitoNum, "%i", conta->digito);
						char agenciaNum[100];
						sprintf(agenciaNum, "%i", conta->agencia);

						char saldoInicialNum[100];
						if (bOrigem)
							sprintf(saldoInicialNum, "%.2f R$", transacoesLoop->origemSaldo);
						else
							sprintf(saldoInicialNum, "%.2f R$", transacoesLoop->destinoSaldo);

						char valorNum[100];
						sprintf(valorNum, "%c %.2f R$", sinal, transacoesLoop->valor);

						char saldoFinalNum[100];
						float saldoFinal = 0.0f;

						if (bOrigem && sinal == '-')
							saldoFinal = transacoesLoop->origemSaldo - transacoesLoop->valor;
						else if (bOrigem && sinal == '+')
							saldoFinal = transacoesLoop->origemSaldo + transacoesLoop->valor;
						else if (bDestino && sinal == '-')
							saldoFinal = transacoesLoop->destinoSaldo - transacoesLoop->valor;
						else if (bDestino && sinal == '+')
							saldoFinal = transacoesLoop->destinoSaldo + transacoesLoop->valor;

						sprintf(saldoFinalNum, "%.2f R$", saldoFinal);

						table.add(agenciaNum);
						table.add(contaNum);
						table.add(digitoNum);
						table.add(saldoInicialNum);
						table.add(transacoesLoop->dataHora->paraChar(DATAHORA::HORA_MIN_SEG)); //DIA_MES_ANO_HORA_MIN
						table.add(transacoesLoop->tipo);
						table.add(valorNum);
						table.add(saldoFinalNum);
						table.endOfRow();
					}
				}
				else if (transacoesLista[INICIO] == transacoesLista[FIM] && transacoesLoop->proximo == NULL)
					printf("\n-> Lista vazia.\n");
			}

			transacoesLoop = transacoesLoop->proximo;
		}

		if (!bEncontrou)
			printf("-> Transação não encontrada.\n");
		else
			std::cout << table;
	}
}

void listarExtratos(TransacoesBancarias* transacoesLista[])
{
	BOOL bEncontrou = FALSE;

	if (vP(transacoesLista[INICIO]) && vP(transacoesLista[FIM]))
	{
		TransacoesBancarias* transacoesLoop = transacoesLista[INICIO];
		TextTable table('\0', '\0', '\0');

		while (transacoesLoop && transacoesLoop->proximo || transacoesLoop && transacoesLoop == transacoesLista[FIM])
		{
			if (transacoesLoop != transacoesLista[INICIO])
			{
				if (!bEncontrou) {
					table.add("Agência:      ");
					table.add("Conta:      ");
					table.add("Digito:      ");
					table.add("Data:      ");
					table.add("Tipo:      ");
					table.endOfRow();

					bEncontrou = true;
				}

				char contaNum[100];
				sprintf(contaNum, "%i", transacoesLoop->origem[0]);
				char digitoNum[100];
				sprintf(digitoNum, "%i", transacoesLoop->origem[1]);
				char agenciaNum[100];
				sprintf(agenciaNum, "%i", transacoesLoop->origem[2]);

				table.add(agenciaNum);
				table.add(contaNum);
				table.add(digitoNum);
				table.add(transacoesLoop->dataHora->paraChar(DATAHORA::HORA_MIN_SEG)); //DIA_MES_ANO_HORA_MIN
				table.add(transacoesLoop->tipo);
				table.endOfRow();
			}
			else if (transacoesLista[INICIO] == transacoesLista[FIM] && transacoesLoop->proximo == NULL)
				printf("\n-> Lista vazia.\n");

			transacoesLoop = transacoesLoop->proximo;
		}

		if (bEncontrou)
			std::cout << table;
	}
}

namespace menuTransacoes
{
	void consultar(TransacoesBancarias* transacoesLista[], ContaCorrente* contasLista[])
	{
		TransacoesBancarias leitura;
		int dataInicio[3];
		int dataFim[3];

		printf("Consultar transações:\n");
		printf("Conta Corrente:\n");
		scanf("%i", &leitura.origem[0]);
		printf("Digito:\n");
		scanf("%i", &leitura.origem[1]);
		printf("Agência:\n");
		scanf("%i", &leitura.origem[2]);
		printf("Data Inicial:\n");
		scanf("%d %d %d", &dataInicio[0], &dataInicio[1], &dataInicio[2]);
		printf("Data Final:\n");
		scanf("%d %d %d", &dataFim[0], &dataFim[1], &dataFim[2]);

		ContaCorrente* contaConsulta = procurarConta(contasLista, leitura.origem[0], leitura.origem[1], leitura.origem[2]);
		if (vP(contaConsulta))
		{
			consultarExtrato(transacoesLista, contaConsulta, dataInicio, dataFim);
		}
		else
			printf("\n-> Conta não encontrada.\n");

		system("pause");
		system("cls");
	}

	void listar(TransacoesBancarias* transacoesLista[])
	{
		printf("Listar Extratos: \n");
		listarExtratos(transacoesLista);

		system("pause");
		system("cls");
	}

	int menu()
	{
		int opcao = 0;
		printf("Menu para controle das transações:\n");
		printf("0 - Sair.\n");
		printf("1 - Consultar extratos.\n");
		printf("2 - Listar extratos.\n");
		printf("R: ");

		scanf("%i", &opcao);

		return opcao;
	}
}

#endif