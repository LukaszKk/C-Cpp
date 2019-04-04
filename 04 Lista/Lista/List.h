#ifndef _LISTA_H
#define _LISTA_H

#include "global.h"

/*
	uzytkownik ma moc podlozyc pod liste dowolny typ
	uzytkownik ma dolozyc dodatkowy plik naglowkowy "global.h"
	ma on zawierac definicje typu, elemetntu jaki bedzie pamietany w liscie, typu T
	definicja preprocesora ktora definiuje stala o nazwie LISTINFO jako typ T
	oraz naglowek funkcji porownujacej czyli taka ktora bedzie dostarczana przez uzytkownika, jej implementacja dostarczana przez uzytkownika
	ma byc ona zefiniowana int comp(const void *, const void *); tak jest zdefiniowany naglowek, cons * oznacza to ze dowolny wskaznik mozna uzyc
	comp - parametr wywolania dwoch funckji w module listy prostej
	w naglowku trzeba zainkludowac global.h
	zawiera pole na wskaznik LISTINFO i pole na kolejny element listy
	//funkcja zwraca -1 kiedy pierwszy parametr mniejszy od drugiego , 0 gdy sa rowne, 1 gdy pierwszy wiekszy od drugiego
*/

//typ elementu listy o nazwie ListItem
typedef struct tagListItem
{
	LISTINFO* m_pInfo;					//wskaznik na informacje ktora bedzie na liscie pamietana
	tagListItem* m_pNext;				//do nastepnego elementu na liscie
} ListItem;

ListItem* MakeEmptyList();													//zwraca wskaznik do zainicjowanej listy //lista z glowa
int isEmpty( ListItem* );													//zwraca 0 gdy lista jest pusta lub 1 //sprawdza czy jest lista pusta czy nie pusta
ListItem* Front( ListItem* pList );											//zwraca wartosc szczytowa elementu //definiuje pusty elment i zwraca wskaznik na ten element //zwraca szczytowy elemnt, ale zwraca caly element listy, zwraca wskaznik na element, nie informacje, sam wskzanik, nie jak w topie
void Insert( ListItem* pAfter, LISTINFO* pInfo );							//wstawia element do listy po wskazniku przekazanym w parametrze (pAfter-po jakim wskazniku, x-)
void InsertFront( ListItem* pList, LISTINFO* pInfo );						//wstawia na poczatek (inaczej push) //nowa informacje tyepu listoinfo
void Remove( ListItem* pAfter );											//usuwa element po parametrze (podobne do Insert) //po elemencie ktory przekazuje wskaznik
void RemoveFront( ListItem* pAfter);										//usuwa pierwszy istotny element (odpowiednik del()) //chlasta ten na ktorym jest
ListItem* Find( ListItem* pList, const void*, ListItem** pPrev, int (__cdecl *comp)( const void*, const void*) );		//, char x, char pPrev); //wyszukuje elementu x //pierwszy parametr to lista, przekazuje wskaznik na poczatek //wskaznik na to czego szukam cont void*, //parametr wyjsciowy pPrev dlatego ** //wskaznik na funkcje porownujaca, ktora find bedzie wywolywac
void FreeList( ListItem* pList );											//czysci liste, calkiem zwalnia liste, nie tylko wszystkie lementy ale rowniez zwalnia ten pusty element pierwszy
void DelList( ListItem** pList );											//usuwa liste, to to niew iem czy jest w ogole
void SortList( ListItem* pList, int (__cdecl *comp)( const void*, const void* ) );				//wskzanik na lsite i wskaznik typu funckyjnego //sortowanie nie moze tworzyc ani usuwac nowych elementow, nma przewiazywac wskaznik, dziala od pierwszego elementu na liscie ktory jesprzekazywany przez elment na liscie pFirst - wskazuje poprzedni, porownuje pFirst i pnext i wybieram, jesli ten jest najmniejszy to jade wskaznikiem do konca i sprawdzam i trzeba ten najmniejszy zapamietac na pudelko wczesniej, 4 albo 5 instrukcij, przpinanie, takie zamienianie, trzeba jechac 3 wskaznikamia, 1 od czego zaczynam, 2 minimalny, 3 ten ktory porownuje

#endif