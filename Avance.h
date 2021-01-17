/*---------------------------------------------------------------------------*\
 | Archivo       : Avance.h                                                  |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino.                                          |
 | Descripción   : Esta librería empaqueta la clase TForm9 para ser usada en |
 |                 otros archivos.                                           |
 | Usada por     : Avance.cpp, Meta.cpp.                                     |
\*---------------------------------------------------------------------------*/

#ifndef AvanceH
#define AvanceH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>

class TForm9 : public TForm
{
    __published:
    TGroupBox *GroupBox1;
    TLabel *Label1;
    TLabel *Label2;
    TAnimate *Animate1;
    private:

    public:
    __fastcall TForm9(TComponent* Owner);
    void activa();
    void desactiva();
};

extern PACKAGE TForm9 *Form9;
#endif
