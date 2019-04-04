#pragma once
#ifndef STACK_ONE
#define STACK_ONE

//inicjacja stosu
typedef struct dtagStack
{
	double dKey; //informacja o stosie
	dtagStack* dpNext; //wskaznik na nastepny element na stosie
} dStack;

void dpush(dStack** dpStack , double x);
double dtop(dStack* dpStack);
int disEmpty(dStack* dpStack);
double dpop(dStack** dpStack);
void ddel(dStack** dpStack);

#endif
