#pragma once
#ifndef STACK_TWO
#define STACK_TWO

//parametry przekazane do funkcij sa zawsze kopiowane, dziala sie na kopiach
//zeby dzialac na oryginalach trzeba dzialac na wskaznikach
//przyklad poprawny:
//void funckja(int* x, int* y)
//{ int tmp = *x; //w srodku dziala sie na wyluskaniu komorki
//*x = *y
//*y = tmp; }
//int main()
//funkcja(&x, &y);  //przekazuje sie adresy zmiennych
//return 0;

typedef struct tagStack
{
	char Key; //informacja o stosie
	struct tagStack* pNext; //wskaznik na nastepny element na stosie
} Stack;


//typedef Stack* StackType; //<-tak mozna
//teraz dla wielu stosow
void push(Stack** pStack, char c); //2* bo modyfikuja wejscie
char top(Stack* pStack);
int isEmpty(Stack* pStack);
char pop(Stack** pStack);
void del(Stack** pStack);

#endif