#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

enum modoIO
{
	LER,         //Ler arquivo
	ESCREVER,    //Caso o arquivo exista, escreve um novo.
	ACRESCENTAR  //Caso o arquivo exista, escreve no final do mesmo.
};

class arquivoIO
{
private:
	FILE* arquivo;
	char arquivoDir[1000];
	char alteracaoDir[1000];
public:
	arquivoIO(string Dir, string arquivo, string alteracao)
	{
		sprintf(arquivoDir, "%s", string(Dir + arquivo).c_str());
		sprintf(alteracaoDir, "%s", string(Dir + alteracao).c_str());
	}

	const char* obterModo(modoIO modo)
	{
		switch (modo)
		{
		case modoIO::LER:
			return "r"; break;
		case modoIO::ESCREVER:
			return "w"; break;
		case modoIO::ACRESCENTAR:
			return "a"; break;
		default:
			return "a";
		}
	}

	void escreverArquivo(string conteudo, modoIO modo = modoIO::ACRESCENTAR)
	{
		arquivo = fopen(arquivoDir, obterModo(modo));
		if (arquivo == NULL)
		{
			printf("-> Falha ao gravar o arquivo: [%s]\n", arquivoDir);
			return;
		}

		fprintf(arquivo, conteudo.c_str());
		fclose(arquivo);
	}

	void lerArquivo(vector<string>& linhas, int quantidadeLinhas, modoIO modo = modoIO::LER)
	{
		arquivo = fopen(arquivoDir, obterModo(modo));
		if (arquivo == NULL)
		{
			printf("-> Falha ao ler o arquivo: [%s]\n", arquivoDir);
			return;
		}

		char buffer[1000];
		while (fgets(buffer, 1000, arquivo))
			linhas.push_back(buffer);

		fclose(arquivo);
	}

	void escreverColunas(vector<string> colunas, char separador)
	{
		string sbuffer;

		for (int i = 0; i < colunas.size(); i++)
		{
			char buffer[256];
			sprintf(buffer, "%s%c", colunas[i].c_str(), separador);
			sbuffer += buffer;
		}

		sbuffer += '\n';
		escreverArquivo(sbuffer.c_str(), modoIO::ACRESCENTAR);
	}

	void lerColunas(vector<string> &colunas, string linha, char separador)
	{
		int pontos[100];
		pontos[0] = -1;
		int contador = 0;

		for (int i = 0; i < linha.length(); i++)
		{
			if (linha[i] == separador)
			{
				contador += 1;
				pontos[contador] = i;
			}
		}

		for (int i = 0; i < contador; i++)
			colunas.push_back(linha.substr(pontos[i] + 1, (pontos[i + 1] - pontos[i]) - 1));
	}

	void reescreverLinha(vector<string> colunas, int linha, char separador)
	{
		FILE *alterado;
		arquivo = fopen(arquivoDir, obterModo(modoIO::LER));
		alterado = fopen(alteracaoDir, obterModo(modoIO::ESCREVER));

		if (arquivo == NULL)
		{
			printf("-> Falha ao ler arquivo. [%s]\n", arquivoDir);
			return;
		}

		if (alterado == NULL)
		{
			printf("-> Falha ao ler arquivo. [%s]\n", alteracaoDir);
			return;
		}

		string sbuffer;
		for (int i = 0; i < colunas.size(); i++)
		{
			char buffer[256];
			sprintf(buffer, "%s%c", colunas[i].c_str(), separador);
			sbuffer += buffer;
		}
		sbuffer += '\n';

		int contador = 0;
		vector<string> linhas;

		char buffer[1000];
		while (fgets(buffer, 1000, arquivo))
		{
			if (contador == linha)
				linhas.push_back(sbuffer.c_str());
			else
				linhas.push_back(buffer);

			contador += 1;
		}

		for (int i = 0; i < linhas.size(); i++)
			fprintf(alterado, "%s", linhas[i].c_str());

		fclose(arquivo);
		fclose(alterado);
		remove(arquivoDir); //unlink
		rename(alteracaoDir, arquivoDir);
	}
};

#endif