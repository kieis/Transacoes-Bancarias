#include "..\includes\includes.h"

void menuGlobal::iniciar(BOOL &resetar)
{
	arquivoIO* arquivo = new arquivoIO(obterDiretorio(), FILE_GLOBAL, FILE_ALTERACAO);
	if (arquivo)
	{
		dthGlobal->Atualizar();

		vector<string> linhasL;
		arquivo->lerArquivo(linhasL, 1000);
		int iProcura = -1;

		for (int i = 0; i < linhasL.size(); i++)
		{
			vector<string> colunasL;
			arquivo->lerColunas(colunasL, linhasL[i], ';');

			if (atoi(colunasL[0].c_str()) == dthGlobal->dia && atoi(colunasL[1].c_str()) == dthGlobal->mes && atoi(colunasL[2].c_str()) == dthGlobal->ano)
				iProcura = i;
		}

		vector<string> wColunas;
		wColunas.push_back(tostr(dthGlobal->dia));
		wColunas.push_back(tostr(dthGlobal->mes));
		wColunas.push_back(tostr(dthGlobal->ano));

		if (iProcura != -1) {
			arquivo->reescreverLinha(wColunas, iProcura, ';');
			resetar = FALSE;
		}
		else {
			arquivo->escreverColunas(wColunas, ';');
			resetar = TRUE;
		}

		if (resetar)
			printf("-> Iniciando com reset no banco de dados.\n");
		else {
			
			printf("-> Iniciando com banco de dados do dia %s.\n", dthGlobal->paraChar(DATAHORA::DIA_MES_ANO));
		}

		free(arquivo);
	}
}

void menuAgencia::iniciar(Agencia* agenciasLista[])
{
	/*Fila duplamente encadeada*/
	arquivoIO* arquivo = new arquivoIO(obterDiretorio(), FILE_AGENCIA, FILE_ALTERACAO);
	if (arquivo)
	{
		int contador = 0;
		vector<string> linhas;
		arquivo->lerArquivo(linhas, 1000);

		for (int i = 0; i < linhas.size(); i++)
		{
			vector<string> colunas;
			arquivo->lerColunas(colunas, linhas[i], ';');

			Agencia* anterior = agenciasLista[FIM];
			agenciasLista[FIM] = criarAgencia(agenciasLista[FIM], atoi(colunas[0].c_str()), colunas[1].c_str(), colunas[2].c_str());
			if (agenciasLista[FIM] != anterior)
				contador++;
		}

		printf("-> Agências inicializadas: %.2i\n", contador);
		free(arquivo);
	}
}

void menuConta::iniciar(ContaCorrente* contasLista[], Agencia* agenciasLista[])
{
	/*Fila duplamente encadeada*/
	arquivoIO* arquivo = new arquivoIO(obterDiretorio(), FILE_CONTA, FILE_ALTERACAO);
	if (arquivo)
	{
		int contador = 0;
		vector<string> linhas;
		arquivo->lerArquivo(linhas, 1000);

		for (int i = 0; i < linhas.size(); i++)
		{
			vector<string> colunas;
			arquivo->lerColunas(colunas, linhas[i], ';');

			ContaCorrente* anterior = contasLista[FIM];
			contasLista[FIM] = criarConta(contasLista[FIM], agenciasLista, atoi(colunas[0].c_str()), atoi(colunas[1].c_str()), colunas[2].c_str(), atoi(colunas[3].c_str()), colunas[4].c_str(), atof(colunas[5].c_str()));
			if (contasLista[FIM] != anterior)
				contador++;
		}

		printf("-> Contas inicializadas: %.2i\n", contador);
		free(arquivo);
	}
}

void menuCaixa::iniciar(Caixa* caixasLista[])
{
	/*Fila duplamente encadeada*/
	arquivoIO* arquivo = new arquivoIO(obterDiretorio(), FILE_CAIXA, FILE_ALTERACAO);
	if (arquivo)
	{
		int contador = 0;
		vector<string> linhas;
		arquivo->lerArquivo(linhas, 1000);

		for (int i = 0; i < linhas.size(); i++)
		{
			vector<string> colunas;
			arquivo->lerColunas(colunas, linhas[i], ';');

			DataHora* dtAbertura = new DataHora();
			dtAbertura->dia = atoi(colunas[8].c_str());
			dtAbertura->mes = atoi(colunas[9].c_str());
			dtAbertura->ano = atoi(colunas[10].c_str());
			dtAbertura->hora = atoi(colunas[11].c_str());
			dtAbertura->min = atoi(colunas[12].c_str());
			dtAbertura->seg = atoi(colunas[13].c_str());

			if (dtAbertura->dia == 0 || dtAbertura->mes == 0 || dtAbertura->ano == 0) {
				free(dtAbertura);
				dtAbertura = NULL;
			}
				
			DataHora* dtFechamento = new DataHora();
			dtFechamento->dia = atoi(colunas[14].c_str());
			dtFechamento->mes = atoi(colunas[15].c_str());
			dtFechamento->ano = atoi(colunas[16].c_str());
			dtFechamento->hora = atoi(colunas[17].c_str());
			dtFechamento->min = atoi(colunas[18].c_str());
			dtFechamento->seg = atoi(colunas[19].c_str());

			if (dtFechamento->dia == 0 || dtFechamento->mes == 0 || dtFechamento->ano == 0) {
				free(dtFechamento);
				dtFechamento = NULL;
			}

			if (bresetarCaixas) {
				colunas[8] = colunas[9] = colunas[10] = colunas[11] = colunas[12] = colunas[13] = tostr(0);
				colunas[14] = colunas[15] = colunas[16] = colunas[17] = colunas[18] = colunas[19] = tostr(0);
				colunas[2] = colunas[7] = colunas[6] = tostr(0);
				colunas[5] = colunas[4];
			}

			arquivo->reescreverLinha(colunas, i, ';');

			float lSaldo[3] = { atof(colunas[4].c_str()), atof(colunas[5].c_str()), atof(colunas[6].c_str()) };

			Caixa* anterior = caixasLista[FIM];
			caixasLista[FIM] = carregarCaixa(caixasLista[FIM], atoi(colunas[0].c_str()), atoi(colunas[1].c_str()), atoi(colunas[2].c_str()), atoi(colunas[7].c_str()), colunas[3].c_str(), lSaldo, (bresetarCaixas) ? NULL : dtAbertura, (bresetarCaixas) ? NULL : dtFechamento);
			if (caixasLista[FIM] != anterior)
				contador++;
		}

		printf("-> Caixas inicializados: %.2i\n", contador);
		free(arquivo);
	}
}

void menuTransacoes::iniciar(TransacoesBancarias* transacoesLista[], Caixa* caixasLista[], ContaCorrente* contasLista[])
{
	/*Fila duplamente encadeada*/
	arquivoIO* arquivo = new arquivoIO(obterDiretorio(), FILE_TRANSACOES, FILE_ALTERACAO);
	if (arquivo)
	{
		int contador = 0;
		vector<string> linhas;
		arquivo->lerArquivo(linhas, 1000);

		for (int i = 0; i < linhas.size(); i++)
		{
			vector<string> colunas;
			arquivo->lerColunas(colunas, linhas[i], ';');

			Caixa* caixaProcura = procurarCaixa(caixasLista, atoi(colunas[6].c_str()));
			if (vP(caixaProcura))
			{
				ContaCorrente* contaOrigem = procurarConta(contasLista, atoi(colunas[19].c_str()), atoi(colunas[20].c_str()), atoi(colunas[21].c_str()));
				if (vP(contaOrigem))
				{
					DataHora* dthTransacao = new DataHora();
					dthTransacao->dia = atoi(colunas[0].c_str());
					dthTransacao->mes = atoi(colunas[1].c_str());
					dthTransacao->ano = atoi(colunas[2].c_str());
					dthTransacao->hora = atoi(colunas[3].c_str());
					dthTransacao->min = atoi(colunas[4].c_str());
					dthTransacao->seg = atoi(colunas[5].c_str());

					SenhaAtendimento senhaInfo;
					senhaInfo.dtH = new DataHora();
					senhaInfo.dtH->dia = atoi(colunas[7].c_str());
					senhaInfo.dtH->mes = atoi(colunas[8].c_str());
					senhaInfo.dtH->ano = atoi(colunas[9].c_str());
					senhaInfo.dtH->hora = atoi(colunas[10].c_str());
					senhaInfo.dtH->min = atoi(colunas[11].c_str());
					senhaInfo.dtH->seg = atoi(colunas[12].c_str());
					senhaInfo.numero = atoi(colunas[13].c_str());
					senhaInfo.status = SENHASTATUS(atoi(colunas[14].c_str()));

					ContaCorrente* contaDestino = procurarConta(contasLista, atoi(colunas[22].c_str()), atoi(colunas[23].c_str()), atoi(colunas[24].c_str()));

					TransacoesBancarias* anterior = transacoesLista[FIM];
					transacoesLista[FIM] = carregarTransacao(transacoesLista[FIM], dthTransacao, caixaProcura, senhaInfo, colunas[15].c_str(), contaOrigem, contaDestino, atof(colunas[17].c_str()), atof(colunas[18].c_str()), atof(colunas[16].c_str()));
						if (transacoesLista[FIM] != anterior)
							contador++;
				}
				else
					printf("-> Conta não encontrado para a transação da linha[%d]", linhas[i]);
			}
			else
				printf("-> Caixa não encontrado para a transação da linha[%d]", linhas[i]);
		}

		printf("-> Transações inicializadas: %.2i\n", contador);
		free(arquivo);
	}
}

int main()
{
	setlocale(0, "Portuguese");
	setConsoleSize(100, 100, 1400, 600);

	//Fila de atendimento
	const int FilaMax = 10;
	FilaAtendimento filaAtendimento[FilaMax];

	int Fila[2] = { -1, -1 };
	int Senha = gerarSenha(100, 899, true);
	int atendimentoAtual = 0;

	vector<SenhaAtendimento> senhaInfo;

	//Caixas Ativos
	vector<Caixa*> caixasAtivos;
	int caixaAtual = 0;

	//Filas
	Agencia* agenciasLista[2] = { NULL, NULL };
	agenciasLista[INICIO] = agenciasLista[FIM] = criarAgencia();

	ContaCorrente* contasLista[2] = { NULL, NULL };
	contasLista[INICIO] = contasLista[FIM] = criarConta();

	Caixa* caixasLista[2] = { NULL, NULL };
	caixasLista[INICIO] = caixasLista[FIM] = criarCaixa();

	TransacoesBancarias* transacoesLista[2] = { NULL, NULL };
	transacoesLista[INICIO] = transacoesLista[FIM] = criarTransacao();
		
	//Inicialização
	printf("-> Inicialização do banco de dados:\n");
	menuGlobal::iniciar(bresetarCaixas);
	printf("-> Inicialização das agências:\n");
	menuAgencia::iniciar(agenciasLista);
	printf("-> Inicialização das contas:\n");
	menuConta::iniciar(contasLista, agenciasLista);
	printf("-> Inicialização dos caixas:\n");
	menuCaixa::iniciar(caixasLista);
	printf("-> Inicialização das transações:\n");
	menuTransacoes::iniciar(transacoesLista, caixasLista, contasLista);

	system("pause");
	system("cls");

	//Menu global
	int optGlobal = -1;
	while (optGlobal != 0)
	{
#ifdef BUILD_ADMIN
		optGlobal = menuGlobal::menu_admin();
		system("cls");

		switch (optGlobal)
		{
		case 1:
		{
			int optAgencia = -1;
			while (optAgencia != 0)
			{
				optAgencia = menuAgencia::menu();
				system("cls");

				switch (optAgencia)
				{
				case 1:
					menuAgencia::criar(agenciasLista);
					break;
				case 2:
					menuAgencia::remover(agenciasLista);
					break;
				case 3:
					menuAgencia::consultar(agenciasLista);
					break;
				case 4:
					menuAgencia::listar(agenciasLista);
					break;
				}
			}
		}break;

		case 2:
		{
			int optConta = -1;
			while (optConta != 0)
			{
				optConta = menuConta::menu();
				system("cls");

				switch (optConta)
				{
				case 1:
					menuConta::criar(contasLista, agenciasLista);
					break;
				case 2:
					menuConta::remover(contasLista);
					break;
				case 3:
					menuConta::consultar(contasLista, agenciasLista);
					break;
				case 4:
					menuConta::listar(contasLista);
					break;
				}
			}
		}break;

		case 3:
		{
			int optCaixa = -1;
			while (optCaixa != 0)
			{
				optCaixa = menuCaixa::menu();
				system("cls");

				switch (optCaixa)
				{
				case 1:
					menuCaixa::criar(caixasLista);
					break;
				case 2:
					menuCaixa::remover(caixasLista);
					break;
				case 3:
					menuCaixa::consultar(caixasLista);
					break;
				case 4:
					menuCaixa::abrir(caixasLista);
					break;
				case 5:
					menuCaixa::fechar(caixasLista);
					break;
				case 6:
					menuCaixa::listar(caixasLista);
					break;
				case 7:
					menuCaixa::repor(caixasLista);
					break;
				}
			}
		}break;

		case 4:
		{
			int optTransacoes = -1;
			while (optTransacoes != 0)
			{
				optTransacoes = menuTransacoes::menu();
				system("cls");

				switch (optTransacoes)
				{
				case 1:
					menuTransacoes::consultar(transacoesLista, contasLista);
					break;
				case 2:
					menuTransacoes::listar(transacoesLista);
					break;
				}
			}
		}break;

		case 5:
		{
			int optAvulsa = -1;
			while (optAvulsa != 0)
			{
				optAvulsa = menuAvulso::menu();
				system("cls");

				switch (optAvulsa)
				{
				case 1:
					menuAvulso::reposicao(caixasLista);
					break;
				case 2:
					menuAvulso::cancelarSenha(filaAtendimento, Fila, atendimentoAtual, senhaInfo);
					break;
				case 3:
					menuAvulso::relacaoCorrentistas(agenciasLista, contasLista);
					break;
				case 4:
					menuAvulso::saldo(contasLista, agenciasLista);
					break;
				case 5:
					menuAvulso::extrato(transacoesLista, contasLista);
					break;
				case 6:
					menuAvulso::listarSenhas(senhaInfo);
					break;
				case 7:
					menuAvulso::gerarDigito();
					break;
				}
			}
		}break;

		case 6:
		{
			int optAtendimento = -1;
			while (optAtendimento != 0)
			{
				optAtendimento = menuAtendimento::menu();
				system("cls");

				switch (optAtendimento)
				{
				case 1:
					menuAtendimento::novo(contasLista, caixasLista, senhaInfo, caixasAtivos, caixaAtual, filaAtendimento, Fila, FilaMax, Senha);
					break;
				}
			}
		}break;

		case 7:
		{
			int optAtendimentoAoCliente = -1;
			while (optAtendimentoAoCliente != 0)
			{
				menuAtendimento::aoCliente::filaCircular(optAtendimentoAoCliente, Fila, filaAtendimento, atendimentoAtual, senhaInfo, transacoesLista, contasLista);
			}
		}break;
		}
#else
		optGlobal = menuGlobal::menu_user();
		system("cls");

		switch (optGlobal)
		{
		case 1:
		{
			int optAtendimento = -1;
			while (optAtendimento != 0)
			{
				optAtendimento = menuAtendimento::menu();
				system("cls");

				switch (optAtendimento)
				{
				case 1:
					menuAtendimento::novo(contasLista, caixasLista, senhaInfo, caixasAtivos, caixaAtual, filaAtendimento, Fila, FilaMax, Senha);
					break;
				}
			}
		}break;

		case 2:
		{
			int optAtendimentoAoCliente = -1;
			while (optAtendimentoAoCliente != 0)
			{
				menuAtendimento::aoCliente::filaCircular(optAtendimentoAoCliente, Fila, filaAtendimento, atendimentoAtual, senhaInfo, transacoesLista, contasLista);
			}
		}break;
		}
#endif
	}

	free(dthGlobal);

	system("pause");
	system("cls");

	return 0;
}