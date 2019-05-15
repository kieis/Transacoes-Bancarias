#ifndef DATAHORA_H
#define DATAHORA_H

enum DATAHORA
{
	HORA_MIN,			 //Hora e minuto
	HORA_MIN_SEG,		 //Hora, minuto e segundo
	DIA_MES_ANO,		 //Dia, mês e ano
	DIA_MES_ANO_HORA_MIN //Data e horário
};

struct DataHora
{
	int dia, mes, ano,
		hora, min, seg;

	DataHora()
	{
		time_t ptr = time(0);
		tm* time = localtime(&ptr);

		hora = time->tm_hour;
		min = time->tm_min;
		seg = time->tm_sec;

		dia = time->tm_mday;
		mes = time->tm_mon + 1;
		ano = time->tm_year + 1900;
	}

	void Update()
	{
		time_t ptr = time(0);
		tm* time = localtime(&ptr);

		hora = time->tm_hour;
		min = time->tm_min;
		seg = time->tm_sec;

		dia = time->tm_mday;
		mes = time->tm_mon + 1;
		ano = time->tm_year + 1900;
	}

	char* paraChar(DATAHORA Tipo)
	{
		char buffer[256];

		switch (Tipo) {
		case DATAHORA::HORA_MIN: sprintf(buffer, "[%.2i:%.2i]", hora, min); break;
		case DATAHORA::HORA_MIN_SEG: sprintf(buffer, "[%.2i:%.2i:%.2i]", hora, min, seg); break;
		case DATAHORA::DIA_MES_ANO: sprintf(buffer, "[%.2i/%.2i/%i]", dia, mes, ano); break;
		case DATAHORA::DIA_MES_ANO_HORA_MIN: sprintf(buffer, "[%.2i/%.2i/%i %.2i:%.2i]", dia, mes, ano, hora, min); break;
		default:sprintf(buffer, "[%.2i:%.2i %.2i/%.2i/%i]", hora, min, dia, mes, ano); break;
		}

		return buffer;
	}
};

extern DataHora* dthGlobal = new DataHora();

#endif