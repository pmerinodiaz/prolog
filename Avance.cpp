/*---------------------------------------------------------------------------*\
 | Archivo       : Avance.cpp                                                |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino .                                         |
 | Descripci�n   : Esta es una forma en la cual se muestra un mensaje de     |
 |                 espera a una respuesta (En nuestro caso las soulciones    |
 |                 para una consulta). Adem�s se muestra una peque�a         |
 |                 animaci�n.                                                |
 | Usada por     : Meta.cpp.                                                 |
\*---------------------------------------------------------------------------*/

#include <vcl.h>
#pragma hdrstop
#include "Avance.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

// Puntero a la TForm9.
TForm9 *Form9;

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall TForm9(TComponent* Owner)                      |
 | Programado por: Patricio Merino.                                          |
 | Entradas      : Un puntero a TComponent.                                  |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo constructor.                                       |
\*---------------------------------------------------------------------------*/
__fastcall TForm9::TForm9(TComponent* Owner):TForm(Owner)
{
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void activa()                                             |
 | Programado por: Patricio Merino.                                          |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo en el cual se hace visible la forma y se comienza  |
 |                 a reproducir la animaci�n.                                |
\*---------------------------------------------------------------------------*/
void TForm9::activa()
{
    Visible = true;
    Animate1->Active = true;
    Refresh();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void desactiva()                                          |
 | Programado por: Patricio Merino.                                          |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo en el cual se hace invisible la forma y se detiene |
 |                 la animaci�n.                                             |
\*---------------------------------------------------------------------------*/
void TForm9::desactiva()
{
    Animate1->Active = false;
    Visible = false;
}
