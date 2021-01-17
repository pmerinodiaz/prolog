/*---------------------------------------------------------------------------*\
 | Archivo       : Editor.cpp                                                |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - H�ctor D�az - Paul Leger.               |
 | Descripci�n   : Este es el editor de texto que tiene el interprete Prolog.|
 |                 En este editor se pueden realizar las funciones t�picas de|
 |                 un editor de texto b�sico, m�s todas las funcionalidades  |
 |                 ue permiten al usuario interpretar un programa Prolog.    |
 | Uso           : En la Form principal del proyecto.                        |
\*---------------------------------------------------------------------------*/

#include <vcl.h>
#include <stdlib.h>
#include <stdio.h>
#include <printers.hpp>
#pragma hdrstop
#include "Editor.h"
#include "Reporte.h"
#include "Meta.h"
#include "Grafica.h"
#include "Interprete.h"
#include "SQL.h"
#include "AcercaDe.h"
#include "Contenidos.h"
#include "TamanioPila.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

// Puntero a la TForm1.
TForm1 *Form1;

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall TForm1(TComponent* Owner)                      |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero a TComponent.                                  |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo constructor en el cual se llama al m�todo <nuevo()>|
 |                 para inicializar variables que ser�n usadas m�s adelante  |
 |                 en el programa.                                           |
\*---------------------------------------------------------------------------*/
__fastcall TForm1::TForm1(TComponent* Owner):TForm(Owner)
{
    // Font por defecto.
    fuente = new TFont();
    fuente->Assign(Memo1->Font);

    nuevo();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall acomodaMemo(TObject *Sender)              |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que permite cambiar las propiedades de tama�o del  |
 |                 <Memo1> cuando el usuario cambia el tama�o de la <Form1>. |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::acomodaMemo(TObject *Sender)
{
    Memo1->Width  = Form1->Width - 10;
    Memo1->Height = Form1->Height - 100;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall cierraForm(TObject *Sender,               |
 |                                            TCloseAction &Action)          |
 | Programado por: Patricio Merino - H�ctor D�az - Paul Leger.               |
 | Entradas      : Un puntero al TObject y un puntero al TCloseAction.       |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario cierra la <Form1>. |
 |                 Se llama al m�todo <salirArchivo()> para verificar si se  |
 |                 efectuaron cambios en el programa.                        |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::cierraForm(TObject *Sender, TCloseAction &Action)
{
    salirArchivo();

    if (TerminoPrograma == IDCANCEL)
      Action = caNone;
    else Action = caFree;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Nuevo1Click(TObject *Sender)              |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario elige la opci�n    |
 |                 Nuevo del Men� Archivo. Se llama al m�todo                |
 |                 <nuevoArchivo()> para efectuar el proceso de generar un   |
 |                 nuevo archivo.                                            |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Nuevo1Click(TObject *Sender)
{
    nuevoArchivo();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Abrir1Click(TObject *Sender)              |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario elige la opci�n    |
 |                 Abrir del Menu Archivo. Se llama al m�todo                |
 |                 <abrirArchivo()> para efectuar el proceso de cargar un    |
 |                 archivo en el <Memo1>.                                    |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Abrir1Click(TObject *Sender)
{
    abrirArchivo();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Guardar1Click(TObject *Sender)            |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que activa cuando el usuario elige la opci�n       |
 |                 Guardar del Menu Archivo. Se llama al m�todo              |
 |                 <guardarArchivo()> para efectuar el proceso de guardar en |
 |                 un archivo el programa contenido en el <Memo1>.           |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Guardar1Click(TObject *Sender)
{
    guardarArchivo();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall GuardarComo1Click(TObject *Sender)        |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que activa cuando el usuario elige la opci�n       |
 |                 Guardar Como del Menu Archivo. Se llama al m�todo         |
 |                 <guardarComoArchivo()> para efectuar el proceso de guardar|
 |                 en un archivo el programa contenido en el <Memo1>.        |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::GuardarComo1Click(TObject *Sender)
{
    guardarComoArchivo();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Imprimir1Click(TObject *Sender)           |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que activa cuando el usuario elige la opci�n       |
 |                 Imprimir del Menu Archivo. Se llama al m�todo <imprime()> |
 |                 para efectuar el proceso de imprimir el programa.         |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Imprimir1Click(TObject *Sender)
{
    imprime();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Salir1Click(TObject *Sender)              |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que activa cuando el usuario elige la opci�n       |
 |                 Salir del Menu Archivo. Se llama al m�todo                |
 |                 <salirArchivo()> para efectuar el proceso de salir del    |
 |                 programa.                                                 |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Salir1Click(TObject *Sender)
{
    salirArchivo();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Deshacer1Click(TObject *Sender)           |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que activa cuando el usuario elige la opci�n       |
 |                 Deshacer del Menu Edici�n.                                |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Deshacer1Click(TObject *Sender)
{
    if (Memo1->HandleAllocated())
      SendMessage(Memo1->Handle, EM_UNDO, 0, 0);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Cortar1Click(TObject *Sender)             |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que activa cuando el usuario elige la opci�n       |
 |                 Cortar del Menu Edici�n.                                  |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Cortar1Click(TObject *Sender)
{
    Memo1->CutToClipboard();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Copiar1Click(TObject *Sender)             |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que activa cuando el usuario elige la opci�n       |
 |                 Copiar del Menu Edici�n.                                  |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Copiar1Click(TObject *Sender)
{
    Memo1->CopyToClipboard();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Pegar1Click(TObject *Sender)              |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que activa cuando el usuario elige la opci�n       |
 |                 Pegar del Menu Edici�n.                                   |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Pegar1Click(TObject *Sender)
{
    Memo1->PasteFromClipboard();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Interpretar1Click(TObject *Sender)        |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario elige la opci�n    |
 |                 Interpretar del Menu Principal. Se llama al m�todo        |
 |                 <interpretar()> para que realiza la operaci�n de          |
 |                 interpretar el programa Prolog contenido en el <Memo1>.   |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Interpretar1Click(TObject *Sender)
{
    interpretar();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Interpretar1Click(TObject *Sender)        |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario lige la opci�n     |
 |                 Reporte del Menu Pincipal. Se llama al m�todo <reporte()> |
 |                 para que realize la operaci�n de mostrar u ocultar el     |
 |                 Reporte.                                                  |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Reporte1Click(TObject *Sender)
{
    reporte();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Interpretar1Click(TObject *Sender)        |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario lige la opci�n     |
 |                 Metas del Menu Pincipal. Se llama al m�todo <metas()>     |
 |                 para que realize la operaci�n de mostrar u ocultar las    |
 |                 Metas.                                                    |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Metas1Click(TObject *Sender)
{
    metas();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Interpretar1Click(TObject *Sender)        |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario lige la opci�n     |
 |                 Gr�ficas del Menu Pincipal. Se llama al m�todo            |
 |                 <graficas()> para que realize la operaci�n de mostrar u   |
 |                 las Gr�ficas.                                             |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Graficas1Click(TObject *Sender)
{
    graficas();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Editor1Click(TObject *Sender)             |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario lige la opci�n     |
 |                 Configurar Fuente del Editor.                             |
 |                 Se setea la fuente del Editor.                            |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Editor1Click(TObject *Sender)
{
    FontDialog1->Font->Assign(Memo1->Font);

    if (FontDialog1->Execute())
      Memo1->Font = FontDialog1->Font;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Reporte2Click(TObject *Sender)            |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario lige la opci�n     |
 |                 Configurar Fuente del Reporte.                            |
 |                 Se setea la fuente del Reporte.                           |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Reporte2Click(TObject *Sender)
{
    FontDialog1->Font->Assign(Form2->Memo1->Font);

    if (FontDialog1->Execute())
    {
      Form2->Edit1->Font = FontDialog1->Font;
      Form2->Memo1->Font = FontDialog1->Font;
    }
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Consulta1Click(TObject *Sender)           |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario lige la opci�n     |
 |                 Configurar Fuente de la Consulta.                         |
 |                 Se setea la fuente de la Consulta.                        |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Consulta1Click(TObject *Sender)
{
    FontDialog1->Font->Assign(Form3->Memo1->Font);

    if (FontDialog1->Execute())
      Form3->Memo1->Font = FontDialog1->Font;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Solucin1Click(TObject *Sender)           |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario lige la opci�n     |
 |                 Configurar Fuente de la Soluci�n.                         |
 |                 Se setea la fuente de la Soluci�n.                        |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Solucin1Click(TObject *Sender)
{
    FontDialog1->Font->Assign(Form3->Memo2->Font);

    if (FontDialog1->Execute())
      Form3->Memo2->Font = FontDialog1->Font;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Grficas1Click(TObject *Sender)            |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario lige la opci�n     |
 |                 Configurar Fuente de la Gr�ficas.                         |
 |                 Se setea la fuente de la Gr�ficas.                        |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Grficas1Click(TObject *Sender)
{
    FontDialog1->Font->Assign(Form5->Memo1->Font);

    if (FontDialog1->Execute())
      Form5->Memo1->Font = FontDialog1->Font;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Editor2Click(TObject *Sender)             |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario lige la opci�n     |
 |                 Configurar Color del Editor.                              |
 |                 Se setea el color de fondo del Editor.                    |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Editor2Click(TObject *Sender)
{
    ColorDialog1->Color = Memo1->Color;

    if (ColorDialog1->Execute())
      Memo1->Color = ColorDialog1->Color;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Reporte3Click(TObject *Sender)            |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario lige la opci�n     |
 |                 Configurar Color del Reporte.                             |
 |                 Se setea el color de fondo del Reporte.                   |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Reporte3Click(TObject *Sender)
{
    ColorDialog1->Color = Form2->Memo1->Color;

    if (ColorDialog1->Execute())
    {
      Form2->Edit1->Color = ColorDialog1->Color;
      Form2->Memo1->Color = ColorDialog1->Color;
    }
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Consulta2Click(TObject *Sender)           |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario lige la opci�n     |
 |                 Configurar Color de la Consulta.                          |
 |                 Se setea el color de fondo de la Consulta.                |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Consulta2Click(TObject *Sender)
{
    ColorDialog1->Color = Form3->Memo1->Color;

    if (ColorDialog1->Execute())
      Form3->Memo1->Color = ColorDialog1->Color;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Solucin2Click(TObject *Sender)            |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario lige la opci�n     |
 |                 Configurar Color de la Soluci�n.                          |
 |                 Se setea el color de fondo de la Soluci�n.                |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Solucin2Click(TObject *Sender)
{
    ColorDialog1->Color = Form3->Memo2->Color;

    if (ColorDialog1->Execute())
      Form3->Memo2->Color = ColorDialog1->Color;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Grficas2Click(TObject *Sender)            |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario lige la opci�n     |
 |                 Configurar Color de la Gr�fica.                           |
 |                 Se setea el color de fondo de la Gr�fica.                 |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Grficas2Click(TObject *Sender)
{
    ColorDialog1->Color = Form5->Memo1->Color;

    if (ColorDialog1->Execute())
      Form5->Memo1->Color = ColorDialog1->Color;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall TamaoPilaClick(TObject *Sender)           |
 | Programado por: Patricio Merino - H�ctor D�az - Paul Leger.               |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario lige la opci�n     |
 |                 Tama�o de Pila del Menu Pincipal.                         |
 |                 Se muestra la <Form7>.                                    |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::TamaoPila1Click(TObject *Sender)
{
    Form7->ShowModal();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void Predeterminado1Click()                               |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que setea la fuente y el color por defecto del     |
 |                 <Memo1> y llama a los m�todos que setean los valores por  |
 |                 defecto de las otras formas.                              |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Predeterminado1Click(TObject *Sender)
{
    // Valores por defecto del Editor.
    Memo1->Font->Assign(fuente);
    Memo1->Color = clWindow;

    // Valores por defecto del Reporte.
    Form2->porDefecto();

    // Valores por defecto de las Metas.
    Form3->porDefecto();
    Form3->Max_Nodos = 10;
    Form7->porDefecto();

    // Valores por defecto de la Gr�fica.
    Form5->porDefecto();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall Contenidos1Click(TObject *Sender)         |
 | Programado por: Patricio Merino - H�ctor D�az - Paul Leger.               |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario lige la opci�n     |
 |                 Contenidos de la Ayuda.                                   |
 |                 Se muestra la <Form8>.                                    |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::Contenidos1Click(TObject *Sender)
{
    Form8->Visible = true;
    Form8->SetFocus();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall AcercaDe1Click(TObject *Sender)           |
 | Programado por: Patricio Merino - H�ctor D�az - Paul Leger.               |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario lige la opci�n     |
 |                 Acerca De del Menu Pincipal.                              |
 |                 Se muestra la <Form6>.                                    |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::AcercaDe1Click(TObject *Sender)
{
    Form6->ShowModal();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall SpeedButton1Click(TObject *Sender)        |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario pulsa sobre el     |
 |                 bot�n Nuevo Archivo. Se llama al m�todo <nuevoArchivo()>  |
 |                 para efectuar el proceso de generar un nuevo archivo.     |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
    nuevoArchivo();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall SpeedButton2Click(TObject *Sender)        |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario pulsa sobre el     |
 |                 bot�n Abrir Archivo. Se llama al m�todo <abrirArchivo()>  |
 |                 para efectuar el proceso de cargar un archivo en el       |
 |                 <Memo1>.                                                  |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
    abrirArchivo();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall SpeedButton3Click(TObject *Sender)        |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario pulsa sobre el     |
 |                 bot�n Guardar Archivo. Se llama al m�todo                 |
 |                 <guardarArchivo()>  para efectuar el proceso de guardar el|
 |                 archivo contenido en el <Memo1>.                          |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
    if (ruta == "Sin Titulo")
      guardarComoArchivo();
    else guardarArchivo();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall SpeedButton13Click(TObject *Sender)       |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario pulsa sobre el     |
 |                 bot�n Imprimir.                                           |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::SpeedButton13Click(TObject *Sender)
{
    imprime();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall SpeedButton8Click(TObject *Sender)        |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario pulsa sobre el     |
 |                 bot�n Deshacer.                                           |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::SpeedButton8Click(TObject *Sender)
{
    if (Memo1->HandleAllocated())
      SendMessage(Memo1->Handle, EM_UNDO, 0, 0);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall SpeedButton10Click(TObject *Sender)       |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario pulsa sobre el     |
 |                 bot�n Cortar.                                             |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::SpeedButton10Click(TObject *Sender)
{
    Memo1->CutToClipboard();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall SpeedButton11Click(TObject *Sender)       |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario pulsa sobre el     |
 |                 bot�n Copiar.                                             |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::SpeedButton11Click(TObject *Sender)
{
    Memo1->CopyToClipboard();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall SpeedButton12Click(TObject *Sender)       |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario pulsa sobre el     |
 |                 bot�n Pegar.                                              |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::SpeedButton12Click(TObject *Sender)
{
    Memo1->PasteFromClipboard();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall SpeedButton4Click(TObject *Sender)        |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario pulsa sobre el     |
 |                 bot�n Interpretar. Se llama al m�todo <interpretar()>     |
 |                 para que realiza la operaci�n de interpretar el programa  |
 |                 Prolog contenido en el <Memo1>.                           |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
    interpretar();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall SpeedButton5Click(TObject *Sender)        |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario pulsa sobre el     |
 |                 bot�n Reporte. Se llama al m�todo <reporte()> para que    |
 |                 realize la operaci�n de mostrar u ocultar el Reporte.     |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::SpeedButton5Click(TObject *Sender)
{
    reporte();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall SpeedButton6Click(TObject *Sender)        |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario pulsa sobre el     |
 |                 bot�n Metas. Se llama al m�todo <metas()> para que        |
 |                 realize la operaci�n de mostrar u ocultar la Metas.       |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::SpeedButton6Click(TObject *Sender)
{
    metas();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall SpeedButton7Click(TObject *Sender)        |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario pulsa sobre el     |
 |                 bot�n Gr�ficas. Se llama al m�todo <graficas()> para que  |
 |                 realize la operaci�n de mostrar u ocultar las Gr�ficas.   |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::SpeedButton7Click(TObject *Sender)
{
    graficas();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall SpeedButton8Click(TObject *Sender)        |
 | Programado por: Patricio Merino - H�ctor D�az - Paul Leger.               |
 | Entradas      : Un puntero al TObject.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que se activa cuando el usuario pulsa sobre el     |
 |                 bot�n Ayuda. Se llama al m�todo <graficas()> para que     |
 |                 realize la operaci�n de mostrar u ocultar las Gr�ficas.   |
\*---------------------------------------------------------------------------*/
void __fastcall TForm1::SpeedButton9Click(TObject *Sender)
{
    Form8->ShowModal();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void nuevoArchivo()                                       |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que realiza la operaci�n de generar un nuevo       |
 |                 archivo.                                                  |
 |                 Primero se verifican si hay cambios en el contenido del   |
 |                 <Memo1>. Si los hay, entonces se pregunta al usuario si   |
 |                 quiere guardar los cambios efectudados.                   |
 |                 Posteriormente se llama al m�todo <nuevo()> para que setee|
 |                 las variables y componentes correspondientes.             |
\*---------------------------------------------------------------------------*/
void TForm1::nuevoArchivo()
{
    if (!verificaCambios())
      switch (confirmaGuardar())
      {
        case IDYES:
        {
          if (ruta == "Sin Titulo")
          {
            if (SaveDialog1->Execute())
            {
              ruta = SaveDialog1->FileName;
              guarda();
              nuevo();
              Form2->limpia(ruta);
              Form2->deshabilita();
              Form3->deshabilita();
              Form5->limpia();
              Form5->deshabilita();
            }
          }
          else
          {
            guarda();
            nuevo();
            Form2->limpia(ruta);
            Form2->deshabilita();
            Form3->deshabilita();
            Form5->limpia();
            Form5->deshabilita();
          }
          break;
        }
        case IDNO:
        {
          nuevo();
          Form2->limpia(ruta);
          Form2->deshabilita();
          Form3->deshabilita();
          Form5->limpia();
          Form5->deshabilita();
          break;
        }
        case IDCANCEL:
          break;
      }
    else
    {
      nuevo();
      Form2->limpia(ruta);
      Form2->deshabilita();
      Form3->deshabilita();
      Form5->limpia();
      Form5->deshabilita();
    }
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void abrirArchivo()                                       |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que realiza la operaci�n de abrir un archivo.      |
 |                 Primero se verifican si hay cambios en el contenido del   |
 |                 <Memo1>. Si los hay, entonces se pregunta al usuario si   |
 |                 quiere guardar los cambios efectudados.                   |
 |                 Posteriormente se llama al m�todo <abre()> para que setee |
 |                 las variables y componentes correspondientes.             |
\*---------------------------------------------------------------------------*/
void TForm1::abrirArchivo()
{
    if (!verificaCambios())
      switch (confirmaGuardar())
      {
        case IDYES:
        {
          if (ruta == "Sin Titulo")
          {
            if (SaveDialog1->Execute())
            {
              ruta = SaveDialog1->FileName;
              guarda();
              abre();
            }
          }
          else
          {
            guarda();
            abre();
          }
          break;
        }
        case IDNO:
          abre();
          break;
        case IDCANCEL:
          break;
      }
    else abre();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void guardarArchivo()                                     |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que realiza la operaci�n de guardar un archivo.    |
 |                 Primero se verifica que existe una ruta para el archivo.  |
 |                 Si no la hay, entonces se debe especificar esa ruta. En   |
 |                 caso contrario, se debe guardar el archivo.               |
 |                 Se llama al m�todo <guarda()> para que setee las          |
 |                 variables y componentes correspondientes.                 |
\*---------------------------------------------------------------------------*/
void TForm1::guardarArchivo()
{
    if (ruta == "Sin Titulo")
      guardarComoArchivo();
    else guarda();
}


/*---------------------------------------------------------------------------*\
 | Nombre        : void guardarComoArchivo()                                 |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que realiza la operaci�n de guardar un archivo que |
 |                 no tiene ruta o bien en el cual se quiere cambiar la ruta.|
 |                 Se llama al m�todo <guarda()> para que setee las          |
 |                 variables y componentes correspondientes.                 |
\*---------------------------------------------------------------------------*/
void TForm1::guardarComoArchivo()
{
    if (SaveDialog1->Execute())
    {
      ruta = SaveDialog1->FileName;
      Form1->Caption = "Prolog - " +ruta;
      guarda();
    }
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void imprime()                                            |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que realiza la operaci�n de imprimir el programa   |
 |                 que est� en el <Memo1>.                                   |
\*---------------------------------------------------------------------------*/
void TForm1::imprime()
{
    TPrinter * impresora;
    TStringList * pagina;
    FILE * test_impresora;
    int intervalo, copias;
    int primera_pg, ultima_pg;
    bool nueva_pg = false;

    pagina = new TStringList();
    pagina->Text = Memo1->Text;

    test_impresora = fopen("PRN", "wt");
    if (test_impresora != NULL)
    {
      if (!PrintDialog1->Execute())
        return;

      // Intervalo - Copias.
      if (!PrintDialog1->Collate)
      {
        intervalo = 1;
        copias = PrintDialog1->Copies;
      }
      else
      {
        intervalo = PrintDialog1->Copies;
        copias = 1;
      }

      // Rango - Todas.
      if (PrintDialog1->PrintRange == prAllPages)
      {
        primera_pg = PrintDialog1->MinPage;
        ultima_pg  = PrintDialog1->MaxPage;
      }
      else
      {
        primera_pg = PrintDialog1->FromPage;
        ultima_pg  = PrintDialog1->ToPage;
      }

      impresora = new TPrinter();
      impresora->BeginDoc();
      impresora->Title = Form1->Caption;

      for (int x = 0; x < intervalo; x++)
        for (int y = primera_pg - 1; y < ultima_pg; y++)
          for (int z = 0; z < copias; z++)
          {
            if (nueva_pg)
              impresora->NewPage();

            for (int linea = 0; linea < pagina->Count; linea++)
              impresora->Canvas->TextOut(20, (10 + impresora->Canvas->TextHeight("PMD"))*linea, pagina->Strings[linea].c_str());

            nueva_pg = true;
          }

      impresora->EndDoc();
    }
    fclose(test_impresora);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void salirArchivo()                                       |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que realiza la operaci�n de salir del programa.    |
 |                 Primero se verifican si hay cambios en el contenido del   |
 |                 <Memo1>. Si los hay, entonces se pregunta al usuario si   |
 |                 quiere guardar los cambios efectudados.                   |
 |                 Posteriormente se llama al m�todo <sale()> para que       |
 |                 limpie la Base de Hechos y Conocimiento y para que cierre |
 |                 la aplicaci�n.                                            |
\*---------------------------------------------------------------------------*/
void TForm1::salirArchivo()
{
    if (!verificaCambios())
    {
      TerminoPrograma = confirmaGuardar();
      switch (TerminoPrograma)
      {
        case IDYES:
        {
          if (ruta == "Sin Titulo")
          {
            if (SaveDialog1->Execute())
            {
              ruta = SaveDialog1->FileName;
              guarda();
              sale();
            }
          }
          else
          {
            guarda();
            sale();
          }
          break;
        }
        case IDNO:
          sale();
          break;
        case IDCANCEL:
          break;
      }
    }
    else sale();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void reporte()                                            |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que realiza la operaci�n de ocultar o visualizar el|
 |                 reporte del programa.                                     |
\*---------------------------------------------------------------------------*/
void TForm1::reporte()
{
    if (Form2->Visible)
    {
      Form2->Visible    = false;
      Reporte1->Checked = false;
    }
    else
    {
      Form2->Visible    = true;
      Reporte1->Checked = true;
      Form2->SetFocus();
    }
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void metas()                                              |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que realiza la operaci�n de ocultar o visualizar   |
 |                 las metas del programa.                                   |
\*---------------------------------------------------------------------------*/
void TForm1::metas()
{
    if (Form3->Visible)
    {
      Form3->Visible  = false;
      Metas1->Checked = false;
    }
    else
    {
      Form3->Visible  = true;
      Metas1->Checked = true;
      Form3->SetFocus();
    }
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void graficas()                                           |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que realiza la operaci�n de ocultar o visualizar   |
 |                 las gr�ficas del programa.                                |
\*---------------------------------------------------------------------------*/
void TForm1::graficas()
{
    if (Form5->Visible)
    {
      Form5->Visible  = false;
      Graficas1->Checked = false;
    }
    else
    {
      Form5->Visible  = true;
      Graficas1->Checked = true;
      Form5->SetFocus();
    }
}

/*---------------------------------------------------------------------------*\
 | Nombre        : bool verificaCambios()                                    |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : Si hay cambios en el programa cargado en el <Memo1>,      |
 |                 entonces retorna false. En caso contrario, retorna true.  |
 | Descripci�n   : M�todo que compara el texto que est� en el <Memo1> y el   |
 |                 que se ten�a del programa abierto. Retorna el valor de    |
 |                 esta comparaci�n.                                         |
\*---------------------------------------------------------------------------*/
bool TForm1::verificaCambios()
{
    return (Memo1->Text == programa);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int confirmaGuardar()                                     |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : La opci�n del <MessageBox>.                               |
 | Descripci�n   : M�todo que despliega el <MessageBox> en el cual se        |
 |                 pregunta si se quiere guardar los cambios o no. Se captura|
 |                 esta opci�n y se retorna el valor.                        |
\*---------------------------------------------------------------------------*/
int TForm1::confirmaGuardar()
{
    return (Application->MessageBox("El texto en el archivo ha cambiado.\n\n�Desea guardar los cambios?", "Prolog", MB_YESNOCANCEL + MB_DEFBUTTON1));
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void nuevo()                                              |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que inicializa los valores de las variables ruta y |
 |                 programa. Limpia el <Memo1> y muestra en el <Caption> de  |
 |                 la <Form1> el t�tulo "Sin T�tulo".                        |
\*---------------------------------------------------------------------------*/
void TForm1::nuevo()
{
    ruta = "Sin Titulo";
    programa = "";
    Memo1->Lines->Clear();
    Form1->Caption = "Prolog - " +ruta;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void abre()                                               |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que abre el archivo especificado por ruta y lo     |
 |                 carga en el <Memo1>.                                      |
\*---------------------------------------------------------------------------*/
void TForm1::abre()
{
    if (OpenDialog1->Execute())
    {
      ruta = OpenDialog1->FileName;
      Memo1->Lines->LoadFromFile(ruta);
      programa = Memo1->Text;
      Form1->Caption = "Prolog - " +ruta;
      Form2->limpia(ruta);
      Form2->deshabilita();
      Form3->deshabilita();
      Form5->limpia();
      Form5->deshabilita();
    }
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void guarda()                                             |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que guarda el texto que est� en el <Memo1> en el   |
 |                 archivo especificado por la variable ruta.                |
\*---------------------------------------------------------------------------*/
void TForm1::guarda()
{
    Memo1->Lines->SaveToFile(ruta);
    programa = Memo1->Text;
    Form2->limpia(ruta);
    Form2->deshabilita();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void sale()                                               |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que cierra la aplicaci�n.                          |
\*---------------------------------------------------------------------------*/
void TForm1::sale()
{
    Form4->limpiaBaseDatos();
    exit(0);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void interpretar()                                        |
 | Programado por: Patricio Merino - H�ctor D�az - Paul Leger.               |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que efect�a la operaci�n de interpretar el programa|
 |                 Prolog contenido en el <Memo1>.                           |
 |                 Se crea el objeto <interprete> de la Clase Interprete para|
 |                 que este se encargue de la revisi�n sint�xica y l�gica    |
 |                 del programa le�do del <Memo1>.                           |
 |                 Se transforma el String del <Memo1> a un arreglo de       |
 |                 caracteres, los cuales son ingresados al interprete uno a |
 |                 uno mediante un ciclo <for>.                              |
 |                 Si existe alg�n tipo de error en el programa, el          |
 |                 interprete informa de tal suceso y el <for> se quiebra    |
 |                 enseguida. En caso contrario, se contin�a interpretando el|
 |                 siguiente caracter del arreglo obtenido del <Memo1> hasta |
 |                 que se llegue al final del arreglo.                       |
 |                 Si hubo un tipo de error, entonces se muestra la l�nea y  |
 |                 el mensaje de error en el Reporte. En caso contrario, se  |
 |                 muestra un mesaje de revisi�n sin errores.                |
\*---------------------------------------------------------------------------*/
void TForm1::interpretar()
{
    Interprete interprete;
    String programa;
    int i, j, longitud, linea, error;
    double deltaBar;
    char *cadena, *auxiliar;

    interprete = Interprete();
    programa   = Memo1->Text;
    cadena     = programa.c_str();
    longitud   = strlen(cadena);
    auxiliar   = new char[longitud];
    error      = 0;
    deltaBar   = 0.01*longitud;

    // Limpiamos todas las formas y limpiamos la Base de Datos.
    Form2->limpia(ruta);
    Form2->habilita();
    Form3->deshabilita();
    Form4->limpiaBaseDatos();
    Form5->limpia();
    Form5->deshabilita();

    // Ciclo en el cual se transforma la cadena a una auxiliar.
    // Se ingresa al interprete caracter a caracter el programa Prolog.
    int contadorBar=0;
    //unidad de contador de una unidad bar
    for (i = 0, j = 0, linea = 1, Form2->ProgressBar1->Position = 0;
         i < longitud; i++, j++)
    {
      // Transformaci�n de la cadena a auxiliar.
      if (cadena[i] == 13)
      {
        auxiliar[j] = '\n';
        i++;
        contadorBar++;
      }
      else auxiliar[j] = cadena[i];
      contadorBar++;

      // Ingresa al interprete el caracter.
      interprete.interpreta(auxiliar[j]);

      // Avance del ProgressBar1 en el Form2.
      if (deltaBar <= contadorBar)
      {
        contadorBar = 0;
        Form2->ProgressBar1->Position++;
      }

      // Muestra el avance.
      Form2->Label4->Caption = String(Form2->ProgressBar1->Position) + "%";
      Application->ProcessMessages();

      error = interprete.obtieneTipoError();

      // Si existe un error se quebra el ciclo. (Es un interprete).
      if (error != 0)
        break;

      // Cuenta las l�neas de c�digo.
      if (auxiliar[j] == '\n')
        linea++;
    }

    // Seteamos el ProgressBar y el Texto de conteo (en %).
    Form2->ProgressBar1->Position = 0;
    Form2->Label4->Caption = "";

    // Si hay errores.
    if (error != 0)
    {
      Form2->Memo1->Text = Form2->Memo1->Text + "Error en la l�nea " +
                           IntToStr(linea)+ "." + char(13) + char(10);
      Form2->Memo1->Text = Form2->Memo1->Text +
                           interprete.obtieneMensajeError();
      apuntaError(linea);
    }
    else
    {
      // Si no es reconocido.
      if (!interprete.reconoce())
      {
        Form2->Memo1->Text = Form2->Memo1->Text + "Error en la l�nea " +
                             IntToStr(linea)+ "." + char(13) + char(10);
        Form2->Memo1->Text = Form2->Memo1->Text + "Error de sintaxis.";
        apuntaError(linea);
      }
      else
      {
        // Revisi�n del Error Tipo 13.
        interprete.revisaError(13);

        if (interprete.obtieneTipoError() != 0)
        {
          Form2->Memo1->Text = Form2->Memo1->Text + "Error en la l�nea " +
                               IntToStr(linea)+ "." + char(13) + char(10);
          Form2->Memo1->Text = Form2->Memo1->Text +
                               interprete.obtieneMensajeError();
          apuntaError(linea);
        }
        else
        {
          // Revisi�n sin errores.
          Form2->Memo1->Text = Form2->Memo1->Text + "Sin errores.";
          Form3->habilita();
        }
      }
    }
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void apuntaError()                                        |
 | Programado por: Patricio Merino.                                          |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que realiza la operaci�n de recorrer el <Memo1>    |
 |                 buscando donde ocurri� el error. Adem�s se marca en donde |
 |                 ocurri� dicho error.                                      |
\*---------------------------------------------------------------------------*/
void TForm1::apuntaError(int linea)
{
    FindDialog1->FindText = Memo1->Lines->Strings[linea - 1];

    for (int i = 0; i < Memo1->Lines->Count; i++)
    {
      int posicion = Memo1->Lines->Strings[i].Pos(FindDialog1->FindText);

      if ((posicion) && ((i + 1) == linea))
      {
        int salta_char = 0;

        for (int j = 0; j < i; j++)
          salta_char += Memo1->Lines->Strings[j].Length();

        salta_char += i*2;
        salta_char += posicion - 1;
        Memo1->SetFocus();
        Memo1->SelStart = salta_char;
        Memo1->SelLength = FindDialog1->FindText.Length();

        break;
      }
    }
}
