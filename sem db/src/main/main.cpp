#include "includes.h"

void menuAgencia::iniciar(Agencia* agenciasLista[])
{
	/*Fila duplamente encadeada*/
	agenciasLista[FIM] = criarAgencia(agenciasLista[FIM], 5203, "Itau", "Rua Pedro Nolasco de Menezes Filho");
	agenciasLista[FIM] = criarAgencia(agenciasLista[FIM], 7031, "Caixa", "Rua Vereador Joaquim Sales Diniz");
	agenciasLista[FIM] = criarAgencia(agenciasLista[FIM], 2935, "Bradesco", "Rua Túlio Chaves");
	agenciasLista[FIM] = criarAgencia(agenciasLista[FIM], 4633, "Inter", "Rua Ponta Grossa");
}

void menuConta::iniciar(ContaCorrente* contasLista[], Agencia* agenciasLista[])
{
	/*Fila duplamente encadeada*/
	contasLista[FIM] = criarConta(contasLista[FIM], agenciasLista, 18383, 3, "232.823.212-34", 7031, "Thiago Brito Alvaredo", 223.0f);
	contasLista[FIM] = criarConta(contasLista[FIM], agenciasLista, 83939, 2, "341.846.768-71", 4633, "João Sebastião Ruan Galvão", 250.0f);
	contasLista[FIM] = criarConta(contasLista[FIM], agenciasLista, 45324, 8, "443.599.900-57", 5203, "Bruno Daniel da Mota", 700.0f);
	contasLista[FIM] = criarConta(contasLista[FIM], agenciasLista, 23311, 0, "323.823.133-79", 7031, "Jose Pedro Brito", 800.0f);
	contasLista[FIM] = criarConta(contasLista[FIM], agenciasLista, 29393, 6, "939.383.012-01", 7031, "Antonio Jose Brito", 3000.0f);
	contasLista[FIM] = criarConta(contasLista[FIM], agenciasLista, 23833, 9, "883.737.484-93", 7031, "Gustavo Cunha Lorenzo", 3713.0f);
	contasLista[FIM] = criarConta(contasLista[FIM], agenciasLista, 23315, 4, "889.098.527-55", 7031, "Lorenzo Otávio de Paula", 11725.0f);
	contasLista[FIM] = criarConta(contasLista[FIM], agenciasLista, 55314, 8, "993.678.110-47", 7031, "Pietro Antonio Thiago Brito", 14312.0f);
}

void menuCaixa::iniciar(Caixa* caixasLista[])
{
	/*Fila duplamente encadeada*/
	caixasLista[FIM] = criarCaixa(caixasLista[FIM], 0, 21343, "Joaquim Thiago Rodrigues", 4000.0f, FALSE);
	caixasLista[FIM] = criarCaixa(caixasLista[FIM], 1, 21362, "Luiz Antonio Nunes", 2000.0f, TRUE);
	caixasLista[FIM] = criarCaixa(caixasLista[FIM], 2, 21363, "Antonio Levi Galvão", 6000.0f, FALSE);
	caixasLista[FIM] = criarCaixa(caixasLista[FIM], 3, 21364, "Renan Sérgio Santos", 200.0f, TRUE);
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
	menuAgencia::iniciar(agenciasLista);
	menuConta::iniciar(contasLista, agenciasLista);
	menuCaixa::iniciar(caixasLista);

	//Menu global
	int optGlobal = -1;
	while (optGlobal != 0)
	{
		optGlobal = menuGlobal::menu();
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
			}break;
		}
	}

	system("pause");
	system("cls");

	return 0;
}