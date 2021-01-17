/*---------------------------------------------------------------------------*\
 | Archivo       : AcercaDe.cpp                                              |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Descripción   : Esta es la forma en donde se muestra el "Acerca de..." del|
 |                 software Prolog.                                          |
 | Usado por     : Editor.cpp.                                               |
\*---------------------------------------------------------------------------*/

#include <vcl.h>
#pragma hdrstop
#include "AcercaDe.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

// Puntero a la TForm6.
TForm6 *Form6;

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall TForm6(TComponent* Owner)                      |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : Un puntero a TComponent.                                  |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método constructor.                                       |
\*---------------------------------------------------------------------------*/
__fastcall TForm6::TForm6(TComponent* Owner):TForm(Owner)
{
}

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall Button1Click(TObject *Sender)                  |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : Un puntero a TObject.                                     |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que se activa cuando el usuario presiona el botón  |
 |                 Aceptar de la forma. Se cierra la forma.                  |
\*---------------------------------------------------------------------------*/
void __fastcall TForm6::Button1Click(TObject *Sender)
{
    Form6->Visible = false;
    Form6->Close();
}
