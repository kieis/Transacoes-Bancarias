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

#pragma warning(disable: 4996 4477 4244 4018)
using namespace std;

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

template<typename T>
bool vP(T* ponteiro) //Validar ponteiro
{
	return (ponteiro == NULL) ? false : true;
}

#include "textTable.h"
#include "dataHora.h"
#include "menuAgencia.h"
#include "menuCaixa.h"
#include "menuConta.h"
#include "menuTransacoes.h"
#include "menuAtendimento.h"
#include "menuAvulso.h"
#include "menuGlobal.h"