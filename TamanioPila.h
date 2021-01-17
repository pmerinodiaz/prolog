/*---------------------------------------------------------------------------*\
 | Archivo       : TamanioPila.h                                             |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Descripción   : Esta librería empaqueta la clase TForm7 para ser usada en |
 |                 otros archivos.                                           |
 | Usada por     : Editor.cpp, TamanioPila.cpp.                              |
\*---------------------------------------------------------------------------*/

#ifndef ConfiguradorH
#define ConfiguradorH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Meta.h"
#include "Editor.h"
#include <Dialogs.hpp>
#include <ComCtrls.hpp>

class TForm7 : public TForm
{
    __published:
    TGroupBox *GroupBox1;
    TScrollBar *ScrollBar1;
    TLabel *Label1;
    TLabel *Label2;
    TButton *Button5;
    TButton *Button1;
    void __fastcall muestraTamanio(TObject *Sender);
    void __fastcall Button5Click(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);

    private:

    public:
    __fastcall TForm7(TComponent* Owner);
    void porDefecto();
};

extern PACKAGE TForm7 *Form7;
#endif
