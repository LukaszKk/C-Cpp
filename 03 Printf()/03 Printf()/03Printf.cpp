// ConsoleApplication1.cpp: Definiuje punkt wejścia dla aplikacji konsolowej.
//

#include <iostream>
#include <stdarg.h>
#include <stdio.h>
using namespace std;

//w domu pisac
//plik naglowkowy z funckja cpp
//modul listy prostej z glowa

//uproszczony printf: %c %d %f %s oraz zamienia `(~) na '(")

int Printf(const char* sFormat, ...);
int PrintfV(const char* sFormat, va_list arg_list);

void outDec(int);		//znakowo wypisuje liczbe alkowita
void outChar(char);		//wypisuje znak
void outStr(char*);		//wypisuje znakowo string
void outDouble(double); //wypisuje znakowo liczbe double
void outNum(int);		//wypisuje znakowo liczbe int > 0

//-------------------------------------------------------------------
//-------------------------------------------------------------------
int main(int argc, char* argv[])
{
	//tu trzebe podelarwac jeszcze te str, x  itd;
	char* str = "to jest napis";
	int n = 657;
	double x = 523.45;
	Printf("%s\n%d\n%f", str, n, x);
	//Printf("%s\n%f%c n=%d \\ /\ny=%f z=%f", str, x, c, n, y, z);

	cout << "\n\n";
	return 0;
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
int Printf(const char* sFormat, ...)	//sFormat jest stringiem
{
	va_list args;						//inicjalizacja listy argumentow
	va_start(args, sFormat);			//ustawienie na poczatku listy argumntow i pobranie pierwszgo argumentu z listy
	int res = PrintfV(sFormat, args);	//wywolanie funkcji przetwarzajacej PritnfV()
	va_end(args);						//reset argumentow
	return res;
}
//-------------------------------------------------------------------
int PrintfV(const char* sFormat, va_list arg_list)
{
	char c;
	while (c = *sFormat++) //wyluskanie, przetwarza od lewej znak po znaku, bo skacze po bajtach
	{
		switch (c)
		{
		case '%':		   //jesli jest procentem to jedziemy dalej
			switch (c = *sFormat++)
			{
			case 'd': outDec(va_arg(arg_list, int)); break;
			case 'f': outDouble(va_arg(arg_list, double)); break;
			case 's': outStr(va_arg(arg_list, char*)); break;
			case 'c': outChar(va_arg(arg_list, char)); break;
			default: outChar(c);
			}
			break;
		case '`': c = '\'';	 //nie ma break wiec przejdzie do default
		default: outChar(c); //jesli nie jest procentem to wypisz znak
		}
	}
	return 0;
}
//-------------------------------------------------------------------
void outDec(int x) 		//znakowo wypisuje liczbe alkowita
{
	if (x < 0)
	{
		x = -x;
		outChar('-');
	}
	else if (!x)
	{
		outChar('0');
		return;
	}
	outNum(x);
}
//-------------------------------------------------------------------
void outChar(char c) 		//wypisuje znak
{
	putchar(c);
}
//-------------------------------------------------------------------
void outStr(char* pStr) 		//wypisuje znakowo string	//wolno modyfikowac bo dostaje kopie tego adresu wiec ta kopie mozna przesuwac
								//zeby modyfikowac trzeba dorzucic jeszcze jedna gwiazdke i adresacje
{
	while (*pStr)
		outChar(*pStr++);
}
//-------------------------------------------------------------------
void outDouble(double x)  //wypisuje znakowo liczbe double
{
	if (x < 0)
	{
		x = -x;
		outChar('-');
	}
	if (x < 1)
		outChar('0');
	outNum((int)x);
	outChar('.');
	x = x - (int)x;
	for (int i = 0; i < 8 && ((x - (int)x) > 1e-10); i++)
		outChar((int)(x *= 10) % 10 + '0');
}
//-------------------------------------------------------------------
void outNum(int x)		//wypisuje znakowo liczbe int > 0, rekurencyjnie!
{
	//trzeba to zrobic zeby wypisywalo od lewej do prawej dlatego trzeba wykorzystac rekurencje ktora odwroci wykonywanie dzialan
	if (x > 0)
	{
		outNum(x / 10);
		outChar(x % 10 + '0');
	}
}