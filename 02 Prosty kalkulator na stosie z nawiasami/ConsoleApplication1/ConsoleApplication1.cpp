// ConsoleApplication2.cpp: Definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;
#include "Stos.h"
#include "cStos.h"

//konsultacje wt 12.30-14.00
//w pon byc moze miedzy 14.00-16.00
//i w pon po wykladzie

//---------------------------------------------
#define DOT '.'

void SkipSpaces(); //pomin spacje
double ONP(); //program
double GetNum(); //pobierz liczbe
int isOper(char c); //sprawdz czy jest operatorem
char GetOper(); //wez operator
int isDigit(char c); //sprawdz czy jest liczba
int prior(char c); //ustalenie priorytetu
double Calcul(char c, double arg1, double arg2); //obliczenie pojedynczego wyrazenia

//=============================================
int main(int argc, char* argv[])
{
	cout << "Podaj wyrazenie: ";
	cout << "Wartosc wyrazenia: " << ONP();

	cout << "\n\n";
	return 0;
}
//=============================================
void SkipSpaces()
{
	char c;
	while( (c = getchar()) == ' ' );
	ungetc(c, stdin);
}
//---------------------------------------------
double ONP()
{
	char c;
	Stack* pStack = NULL;		//stos znakowy
	dStack* dpStack = NULL;		//stos liczbowy
	while ((c = GetOper()) == '(')		//jesli sa najpierw nawiasy to wloz na stos
		push(&pStack, c);
	ungetc(c, stdin);
	dpush(&dpStack, GetNum());
	while( isOper( c=GetOper() ) )
	{
		/*if (c == '(')
		{
			push(&pStack, c);
			while ((c = GetOper()) == '(')		//jesli jest wiecej niz jeden nawias to wloz na stos
				push(&pStack, c);
			ungetc(c, stdin);
			dpush(&dpStack, GetNum());
		}*/
		if (c == ')')
		{
			while ((c = pop(&pStack)) != '(')
			{
				double x = dpop(&dpStack);
				dpush(&dpStack, Calcul(c, dpop(&dpStack), x));
			}
		}
		else
		{
				while (prior(c) <= prior(top(pStack)))
				{
					double x = dpop(&dpStack);
					dpush(&dpStack, Calcul(pop(&pStack), dpop(&dpStack), x));
				}
				push(&pStack, c);
				while ((c = GetOper()) == '(')
					push(&pStack, c);
				ungetc(c, stdin);
				dpush(&dpStack, GetNum());
				/*char x = (c = GetOper());
				ungetc(c, stdin);
				if (!isOper(x))					//wloz liczbe na stos
					dpush(&dpStack, GetNum());*/
		}
	}
	while (!isEmpty(pStack))				//oproznij stos
	{
		double x = dpop(&dpStack);
		dpush(&dpStack, Calcul(pop(&pStack), dpop(&dpStack), x));
	}

	return dpop(&dpStack);
}
//---------------------------------------------
double GetNum()
{
	char c;
	SkipSpaces();
	double res = 0;
	while (isDigit(c = getchar()))
	{
		res = res * 10 + (c - '0');
	}
	if (c == DOT)
	{
		double coef = 0.1;
		while (isDigit(c = getchar()))
		{
			res += (c - '0') * coef;
		}
	}
	ungetc(c, stdin);

	return res;
}
//---------------------------------------------
char GetOper()
{
	SkipSpaces();
	return getchar();
}
//---------------------------------------------
int isOper(char c)
{
	switch (c)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '^': 
	case '(': 
	case ')': return 1;
	}
	return 0;
}
//---------------------------------------------
int prior(char c)
{
	switch (c)
	{
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	case '^': return 3;
	}
	return 0;
}
//---------------------------------------------
int isDigit(char c)
{
	return (c >= '0') && (c <= '9');
}
//---------------------------------------------
double Calcul(char c, double arg1, double arg2)
{
	switch (c)
	{
	case '+': return arg1 + arg2;
	case '-': return arg1 - arg2;
	case '*': return arg1 * arg2;
	case '/': {
		if (fabs(arg2) < 1e-15)
		{
			printf("Dzielenie przez 0\n");
			break;
		}
		else
			return arg1 / arg2;
	};
	case '^': return pow(arg1, arg2);
	}
	return 0;
}