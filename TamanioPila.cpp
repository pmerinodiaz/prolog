/*---------------------------------------------------------------------------*\
 | Archivo       : TamanioPila.cpp                                           |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Descripci�n   : Esta es la forma en donde se puede elegir el n�mero de    |
 |                 elementos que se quiere usar en la pila.                  |
 | Usada por     : Editor.cpp.                                               |
\*---------------------------------------------------------------------------*/

#include <vcl.h>
#pragma hdrstop
#include "TamanioPila.h"
#include "Meta.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

// Puntero a la TForm7.
TForm7 *Form7;

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall TForm7(TComponent* Owner)                      |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : Un puntero a TComponent.                                  |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo constructor en el cual se posiciona el <ScrollBar1>|
 |                 en el n�mero actual de nodos que tiene la pila.           |
\*---------------------------------------------------------------------------*/
__fastcall TForm7::TForm7(TComponent* Owner):TForm(Owner)
{
    ScrollBar1->Position = Form3->Max_Nodos;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall muestraTamanio(TObject *Sender)                |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : Un puntero a TObject.                                     |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario mueve el           |
 |                 <ScrollBar1>. Se va mostrando el valor que toma el tama�o |
 |                 de la pila en el <Label2>.                                |
\*---------------------------------------------------------------------------*/
void __fastcall TForm7::muestraTamanio(TObject *Sender)
{
    Label2->Caption = IntToStr(ScrollBar1->Position);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall Button5Click(TObject *Sender)                  |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : Un puntero a TObject.                                     |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario pulsa el bot�n     |
 |                 Aceptar. Se setea el valor del tama�o de la pila en el    |
 |                 valor ingresado.                                          |
\*---------------------------------------------------------------------------*/
void __fastcall TForm7::Button5Click(TObject *Sender)
{
    Form3->Max_Nodos = ScrollBar1->Position;
    Close();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall Button1Click(TObject *Sender)                  |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : Un puntero a TObject.                                     |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario pulsa el bot�n     |
 |                 Cancelar. Se cierra la forma.                             |
\*---------------------------------------------------------------------------*/
void __fastcall TForm7::Button1Click(TObject *Sender)
{
    ScrollBar1->Position = Form3->Max_Nodos;
    Close();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void porDefecto()                                         |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : Un puntero a TComponent.                                  |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que setea la posici�n del <ScrollBar1> en 10.      |
\*---------------------------------------------------------------------------*/
void TForm7::porDefecto()
{
    ScrollBar1->Position = 10;
}

