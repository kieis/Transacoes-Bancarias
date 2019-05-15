#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <locale.h>
#include <time.h>

#define INICIO 0
#define FIM 1

#define FILE_AGENCIA "db\\agencias.txt"
#define FILE_CONTA "db\\contas.txt"
#define FILE_CAIXA "db\\caixas.txt"
#define FILE_TRANSACOES "db\\transacoes.txt"
#define FILE_GLOBAL "db\\global.txt"
#define FILE_ALTERACAO "db\\alteracao.txt"

#pragma warning(disable: 4996 4477 4244 4018)
using namespace std;

BOOL bresetarCaixas = FALSE;
float bancoSaldo = 999999.0f;

bool verificarDigito(int conta, int digito)
{
	int dig = 0, resto = 0;

	while (conta > 0) {
		resto = conta % 10;
		dig += resto;
		conta /= 10;
	}

	return ((dig %= 10) == digito) ? true : false;
}

int intTamanho(int i) {
	int l = 0;
	for (;i;i /= 10) l++;
	return l == 0 ? 1 : l;
}

int charTamanho(const char* a)
{
	return string(a).length();
}

void setConsoleSize(int x, int y, int w, int h)
{
	HWND hwnd = GetConsoleWindow();
	RECT rect = { x, y, w, h };
	MoveWindow(hwnd, rect.top, rect.left, rect.right - rect.left, rect.bottom - rect.top, TRUE);
}

bool checarVetor(int vector[], int value, int size)
{
	int ps = 0;

	for (int i = 0; i < size; i++)
		if (vector[i] == value)
			ps += 1;;

	return (ps == size) ? true : false;
}

int checarData(int dataAtual[], int data[]) //atual > data (1), data > atual (2), data == atual (0)
{
	int data1 = dataAtual[2]* 10000 + dataAtual[1] * 100 + dataAtual[0],
		data2 = data[2] * 10000 + data[1] * 100 + data[0];

	if (data1 > data2)
		return 1;
	else {
		if (data2 > data1)
			return 2;
		else
			return 0;
	}

	return -1;
}

string obterDiretorio()
{
	char buffer[256];
	GetModuleFileNameA(NULL, buffer, 256);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos + 1);
}

template <typename T> 
string tostr(const T& t) {
	ostringstream os;
	os << t;
	return os.str();
}

template<typename T>
bool vP(T* ponteiro) //Validar ponteiro
{
	return (ponteiro == NULL) ? false : true;
}

#include "textTable.h"
#include "arquivoIO.h"
#include "dataHora.h"
#include "menuAgencia.h"
#include "menuCaixa.h"
#include "menuConta.h"
#include "menuTransacoes.h"
#include "menuAtendimento.h"
#include "menuAvulso.h"
#include "menuGlobal.h"