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
//w pon moze siedziec medzy 14.00-16.00
//w pon po wykladzie bedzie

#define DOT '.'

void SkipSpaces(); //pomin spacje
double ONP(); //program
double GetNum(); //pobierz liczbe
int isOper(char c); //sprawdz czy jest operatorem
char GetOper(); //wez operator
int isDigit(char c); //sprawdz czy jest liczba
int prior(char c); //ustalenie priorytetu
double Calcul(char c, double arg1, double arg2);

int main(int argc, char* argv[])
{
	cout << "Podaj wyrazenie: ";
	cout << ONP();

	cout << "\n\n";
	return 0;
}
//------------------------------------------
void SkipSpaces()
{
	char c;
	while ((c = getchar()) == ' ');
	ungetc(c, stdin);
}
//-----------------------------------
double ONP()
{
	char c;
	Stack* pStack = NULL;
	dStack* dpStack = NULL;
	dpush(&dpStack, GetNum());
	while (isOper(c = GetOper()))
	{
		while (prior(c) <= prior(top(pStack)))
		{
			double x = dpop(&dpStack);
			dpush(&dpStack, Calcul(pop(&pStack), dpop(&dpStack), x));  //tu ampersand musi byc
		}
		push(&pStack, c);
		dpush(&dpStack, GetNum());
	}
	while (!(isEmpty(pStack)))
	{
		double x = dpop(&dpStack);
		dpush(&dpStack, Calcul(pop(&pStack), dpop(&dpStack), x));
	}
	return dpop(&dpStack);
}
//-------------------------------------
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
//----------------------------------------
char GetOper()
{
	SkipSpaces();
	return getchar();
}
//------------------------------
int isOper(char c)
{
	switch (c)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '^': return 1;
	}
	return 0;
}
//-------------------
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
//------------------------
int isDigit(char c)
{
	return (c >= '0') && (c <= '9');
}
//------------------------
double Calcul(char c, double arg1, double arg2)
{
	switch (c)
	{
	case '+': return arg1 + arg2;
	case '-': return arg1 - arg2;
	case '*': return arg1 * arg2;
	case '/': return arg1 / arg2;
	case '^': return pow(arg1, arg2);
	}
}