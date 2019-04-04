#ifndef _INCLUDE_LISTH_ //zabezpieczenie preprocesora
#define _INCLUDE_LISTH_

typedef struct 
{
	int nKey;
} ListInfo;

#define LISTINFO ListInfo									//LISTINFO bedzie sie wszedzie uzywac, dlatego to wyzej mozna modyfikowac dowolnie

int compare( const void*, const void* );					//tak jakby inty sie porownywalo //w main ja napisac

#endif