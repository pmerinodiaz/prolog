/*---------------------------------------------------------------------------*\
 | Archivo       : Regla.cpp                                                 |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Descripción   : Clase que representa a una regla en Prolog. Se constituye |
 |                 de un predicado consecuente y de dos o un predicado       |
 |                 antecedente.                                              |
 | Usado por     : Interprete.cpp, Regla.cpp                                 |
\*---------------------------------------------------------------------------*/

#include <vcl.h>
#pragma hdrstop
#include "Regla.h"
#pragma package(smart_init)
#define SINTIPO 0
#define UNANTEC 1
#define DOSANTE 2

/*---------------------------------------------------------------------------*\
 | Nombre        : Regla()                                                   |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método constructor en el cual se inicializan los valores  |
 |                 de las variables.                                         |
 |                 Se asigna memoria a los objeto y se inicializan.          |
\*---------------------------------------------------------------------------*/
Regla::Regla()
{
    consecuente = Predicado();
    antecedente1 = Predicado();
    antecedente2 = Predicado();
    tipo = SINTIPO;
    conflicto = 0;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void ingresaConsecuente(Predicado predicado)              |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El predicado consecuente de la regla.                     |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método en el cual se setea el predicado <consecuente>.    |
\*---------------------------------------------------------------------------*/
void Regla::ingresaConsecuente(Predicado predicado)
{
    consecuente = predicado;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void ingresaAntecedente1(Predicado predicado)             |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El predicado antecedente1 de la regla.                    |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método en el cual se setea el predicado <antecedente1>.   |
\*---------------------------------------------------------------------------*/
void Regla::ingresaAntecedente1(Predicado predicado)
{
    antecedente1 = predicado;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void ingresaAntecedente2(Predicado predicado)             |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El predicado antecedente2 de la regla.                    |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método en el cual se setea el predicado <antecedente2>.   |
\*---------------------------------------------------------------------------*/
void Regla::ingresaAntecedente2(Predicado predicado)
{
    antecedente2 = predicado;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : Predicado obtieneConsecuente()                            |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El predicado consecuente de la regla.                     |
 | Descripción   : Método en el cual se retorna el predicado consecuente de  |
 |                 la regla.                                                 |
\*---------------------------------------------------------------------------*/
Predicado Regla::obtieneConsecuente()
{
    return (consecuente);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : Predicado obtieneAntecedente1()                           |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El predicado antecedente1 de la regla.                    |
 | Descripción   : Método en el cual se retorna el predicado antecedente1 de |
 |                 la regla.                                                 |
\*---------------------------------------------------------------------------*/
Predicado Regla::obtieneAntecedente1()
{
    return (antecedente1);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : Predicado obtieneAntecedente2()                           |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El predicado antecedente1 de la regla.                    |
 | Descripción   : Método en el cual se retorna el predicado antecedente2 de |
 |                 la regla.                                                 |
\*---------------------------------------------------------------------------*/
Predicado Regla::obtieneAntecedente2()
{
    return (antecedente2);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int obtieneTipo()                                         |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El tipo de regla.                                         |
 |                  0. Sin tipo.                                             |
 |                  1. Un antecedente.                                       |
 |                  2. Dos antecedentes.                                     |
 | Descripción   : En este método se setea el valor de <tipo>. Se preguntan  |
 |                 por los casos posibles de existencia y no existencia de   |
 |                 los antecedentes que tiene la regla.                      |
\*---------------------------------------------------------------------------*/
int Regla::obtieneTipo()
{
    char c1 = antecedente1.capturaNombre().obtiene(0);
    char c2 = antecedente2.capturaNombre().obtiene(0);
    tipo = SINTIPO;

    if ((c1 != NULL) && (c2 == NULL))
      tipo = UNANTEC;
    else if ((c1 != NULL) && (c2 != NULL))
           tipo = DOSANTE;

    return (tipo);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void limpia()                                             |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : En este método se llama a los metodos de los objetos que  |
 |                 limpian los predicados <consecuente>, <antecedente1> y    |
 |                 <antecedente2>.                                           |
\*---------------------------------------------------------------------------*/
void Regla::limpia()
{
    consecuente.limpia();
    antecedente1.limpia();
    antecedente2.limpia();
}

int Regla::obtieneConflicto()
{
    return (conflicto);
}

void Regla::ingresaConflicto(int cantidad)
{
    conflicto = cantidad;
}    
