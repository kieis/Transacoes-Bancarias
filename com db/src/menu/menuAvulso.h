#ifndef MENUAVULSO_H
#define MENUAVULSO_H

namespace menuAvulso
{
	void reposicao(Caixa* caixasLista[])
	{
		menuCaixa::repor(caixasLista);
	}

	void cancelarSenha(FilaAtendimento filaAtendimento[], int Fila[], int& atendimentoAtual, vector<SenhaAtendimento>& senhaInfo)
	{
		BOOL bEncontrou = false;
		int senha = 0;
		if (senhaInfo.size() > 0)
		{
			printf("A senha atual na fila de atendimento é %i, para cancelar digite a mesma:\n", filaAtendimento[atendimentoAtual].senhaInfo.numero);
			scanf("%i", &senha);

			if (filaAtendimento[atendimentoAtual].senhaInfo.numero == senha)
			{
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

				printf("\nSenha cancelada com sucesso.\n");
			}
			else
				printf("\n-> A senha não foi cancelada.\n");
		}else
			printf("-> Nenhuma senha foi gerada.\n");

		system("pause");
		system("cls");
	}

	void relacaoCorrentistas(Agencia* agenciasLista[], ContaCorrente* contasLista[])
	{
		vector<ContaCorrente*> contasAchadas;

		int agencia = 0;
		printf("Insira a agência para realizar a relação de contas:\n");
		scanf("%i", &agencia);

		Agencia* agenciaConsulta = procurarAgencia(agenciasLista, agencia);
		if (vP(agenciaConsulta))
		{
			system("cls");
			TextTable table('\0', '\0', '\0');

			if (vP(contasLista[INICIO]) && vP(contasLista[FIM]))
			{
				ContaCorrente* contaLoop = contasLista[INICIO];

				while (contaLoop && contaLoop->proximo || contaLoop && contaLoop == contasLista[FIM])
				{
					if (contaLoop != contasLista[INICIO])
						if (contaLoop->agencia == agenciaConsulta->registro)
							contasAchadas.push_back(contaLoop);

					contaLoop = contaLoop->proximo;
				}
			}

			if (contasAchadas.size() > 0)
			{
				char ordemAlf[100];
				char nm[100][100];
				for (int i = 0; i < contasAchadas.size(); i++)
					sprintf(nm[i], "%s", contasAchadas[i]->nome);

				for (int i = 1; i < contasAchadas.size(); i++) {
					for (int j = 1; j < contasAchadas.size(); j++) {
						if (strcmp(nm[j - 1], nm[j]) > 0) {
							strcpy(ordemAlf, nm[j - 1]);
							strcpy(nm[j - 1], nm[j]);
							strcpy(nm[j], ordemAlf);
						}
					}
				}

				printf("Relação de contas na agência %s(%i):\n", agenciaConsulta->nome, agenciaConsulta->registro);
				table.add("Conta:    ");
				table.add("Digito:    ");
				table.add("Nome:      ");
				table.endOfRow();

				for (int i = 0; i < contasAchadas.size(); i++)
				{
					for (int j = 0; j < contasAchadas.size(); j++)
					{
						if (strstr(nm[i], contasAchadas[j]->nome))
						{
							char contaNum[100];
							sprintf(contaNum, "%i", contasAchadas[j]->conta);
							char digitoNum[100];
							sprintf(digitoNum, "%i", contasAchadas[j]->digito);

							table.add(contaNum);
							table.add(digitoNum);
							table.add(contasAchadas[j]->nome);
							table.endOfRow();
						}
					}
				}

				std::cout << table;
			}
			else {
				printf("\n-> Nenhuma correntista encontrado.\n");
			}
		}
		else
			printf("\n-> Agência não encontrada.\n");

		system("pause");
		system("cls");
	}

	void saldo(ContaCorrente* contaslista[], Agencia* agenciasLista[])
	{
		menuConta::consultar(contaslista, agenciasLista);
	}

	void extrato(TransacoesBancarias* transacoesLista[], ContaCorrente* contaslista[])
	{
		menuTransacoes::consultar(transacoesLista, contaslista);
	}

	int gerarDigito(int conta)
	{
		int dig = 0, resto = 0;

		while (conta > 0) {
			resto = conta % 10;
			dig += resto;
			conta /= 10;
		}

		return dig %= 10;
	}

	void gerarDigito(void)
	{
		int conta = 0;

		printf("Insira a conta para a criação do digito:\n");
		scanf("%i", &conta);
		printf("\nDigito: %i\n", gerarDigito(conta));

		system("pause");
		system("cls");
	}

	void listarSenhas(vector<SenhaAtendimento> senhaInfo)
	{
		if (senhaInfo.size() > 0)
		{
			TextTable table('\0', '\0', '\0');
			printf("Listar Senhas:\n");

			table.add("Data:                      ");
			table.add("Senha:                      ");
			table.add("Status:");
			table.endOfRow();

			for (int i = 0; i < senhaInfo.size(); i++)
			{
				const char* status = "";
				switch (senhaInfo[i].status)
				{
				case SENHASTATUS::EMITIDA:
					status = "Emitida"; break;
				case SENHASTATUS::ATENDIDA:
					status = "Atendida"; break;
				case SENHASTATUS::CANCELADA:
					status = "Cancelada"; break;
				}

				char senhaNum[100];
				sprintf(senhaNum, "%i", senhaInfo[i].numero);

				table.add(senhaInfo[i].dtH->paraChar(DATAHORA::DIA_MES_ANO_HORA_MIN));
				table.add(senhaNum);
				table.add(status);
				table.endOfRow();
			}

			std::cout << table;
		}
		else
			printf("-> Nenhuma senha foi gerada, lista vazia.\n");

		system("pause");
		system("cls");
	}

	int menu()
	{
		int opcao = 0;
		printf("Consultas avulsas:\n");
		printf("0 - Sair.\n");
		printf("1 - Reposição de caixa.\n");
		printf("2 - Cancelamento de Senha.\n");
		printf("3 - Relação de correntistas.\n");
		printf("4 - Saldo do correntista.\n");
		printf("5 - Extrato do correntista.\n");
		printf("6 - Listar senhas geradas.\n");
		printf("7 - Gerar digito verificador.\n");
		printf("R: ");

		scanf("%i", &opcao);

		return opcao;
	}
}

#endif