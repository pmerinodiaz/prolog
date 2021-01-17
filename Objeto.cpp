/*---------------------------------------------------------------------------*\
 | Archivo       : Objeto.cpp                                                |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Descripci�n   : Esta clase representa lo que es en Prolog un Objeto. Esto |
 |                 puede ser un Atomo o una Variable. Ambos son una cadena de|
 |                 caracteres, pero difieren en que una Variable debe        |
 |                 con una letra May�scula, en cambio el Atomo puede comenzar|
 |                 con una letra Min�scula o May�scula.                      |
 | Usada por     : Predicado.cpp, Interprete.cpp                             |
\*---------------------------------------------------------------------------*/

#include <vcl.h>
#pragma hdrstop
#include "Objeto.h"
#define SINTIPO  0
#define ATOMO    1
#define VARIABLE 2
#pragma package(smart_init)

/*---------------------------------------------------------------------------*\
 | Nombre        : Objeto()                                                  |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo constructor en el cual se llama al constructor de  |
 |                 la clase madre y el <tipo> de Objeto se deja en valor 0.  |
\*---------------------------------------------------------------------------*/
Objeto::Objeto()
{
    Cadena();
    tipo = SINTIPO;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int obtieneTipo()                                         |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El <tipo> del Objeto.                                     |
 |                 0. Sin tipo.                                              |
 |                 1. Atomo.                                                 |
 |                 2. Variable.                                              |
 | Descripci�n   : Este m�todo determina si un Objeto es Variable o Atomo.   |
 |                 Para esto, se toma el primer caracter de la cadena y se ve|
 |                 si es may�scula o no. Si lo es, entonces es Variable, en  |
 |                 caso contrario es Atomo. Posteriormente se retorna el     |
 |                 valor de <tipo>.                                          |
\*---------------------------------------------------------------------------*/
int Objeto::obtieneTipo()
{
    tipo = SINTIPO;

    char c = obtiene(0);

    if ((c >= 97) && (c <= 122))
      tipo = ATOMO;
    else if ((c >= 65) && (c <= 90 ))
           tipo = VARIABLE;

    return (tipo);
}
