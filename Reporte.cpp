/*---------------------------------------------------------------------------*\
 | Archivo       : Reporte.cpp                                               |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Héctor Díaz - Paul Leger.               |
 | Descripción   : Esta es la Form donde se muestra el Reporte de los        |
 |                 resultados al interpretar un programa Prolog.             |
 |                 Se muestra el nombre del archivo, una barra de progreso   |
 |                 de revisión y los resultados obtenidos de la              |
 |                 interpretación.                                           |
 | Usado por     : Editor.cpp.                                               |
\*---------------------------------------------------------------------------*/

#include <vcl.h>
#pragma hdrstop
#include "Reporte.h"
#include "Editor.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

// Puntero a la TForm2.
TForm2 *Form2;

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall TForm2(TComponent* Owner)                      |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : Un puntero a TComponent.                                  |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método constructor en el cual se limpia el reporte.       |
\*---------------------------------------------------------------------------*/
__fastcall TForm2::TForm2(TComponent* Owner):TForm(Owner)
{
     // Font por defecto.
    fuente = new TFont();
    fuente->Assign(Memo1->Font);

    limpia("Sin Título");
    deshabilita();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall cierraForm(TObject *Sender,               |
 |                                            TCloseAction &Action)          |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : Un puntero a TObject y un puntero a TCloseAction.         |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que se activa cuando el usuario cierra la Form del |
 |                 Reporte.                                                  |
\*---------------------------------------------------------------------------*/
void __fastcall TForm2::cierraForm(TObject *Sender, TCloseAction &Action)
{
    Form2->Visible = false;
    Form1->Reporte1->Checked = false;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void limpia()                                             |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : La ruta del archivo que se está interpretando.            |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que limpia el reporte.                             |
\*---------------------------------------------------------------------------*/
void TForm2::limpia(String ruta)
{
    Edit1->Text = ruta;
    ProgressBar1->Position = 0;
    Label4->Caption = "";
    Memo1->Clear();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void deshabilita()                                        |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que deshabilita la escritura en el <Edit1> y en el |
 |                 <Memo1>.                                                  |
\*---------------------------------------------------------------------------*/
void TForm2::deshabilita()
{
    Edit1->Enabled = false;
    Memo1->Enabled = false;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void habilita()                                           |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que habilita la escritura en el <Edit1> y en el    |
 |                 <Memo1>.                                                  |
\*---------------------------------------------------------------------------*/
void TForm2::habilita()
{
    Edit1->Enabled = true;
    Memo1->Enabled = true;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void porDefecto()                                         |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que setea la fuente y el color por defecto del     |
 |                 <Edit1> y del <Memo1>.                                    |
\*---------------------------------------------------------------------------*/
void TForm2::porDefecto()
{
    // Valores por defecto del Editor.
    Edit1->Font->Assign(fuente);
    Memo1->Font->Assign(fuente);
    Edit1->Color = clWindow;
    Memo1->Color = clWindow;
}
