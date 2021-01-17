/*---------------------------------------------------------------------------*\
 | Archivo       : AcercaDe.h                                                |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Descripción   : Esta librería empaqueta la clase TForm6 para ser usada en |
 |                 otros archivos.                                           |
 | Usada por     : AcercaDe.cpp, Editor.cpp.                                 |
\*---------------------------------------------------------------------------*/

#ifndef AcercaDeH
#define AcercaDeH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

class TForm6 : public TForm
{
    __published:
    TGroupBox *GroupBox1;
    TGroupBox *GroupBox2;
    TGroupBox *GroupBox3;
    TGroupBox *GroupBox4;
    TGroupBox *GroupBox5;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label14;
    TLabel *Label15;
    TLabel *Label16;
    TLabel *Label17;
    TLabel *Label18;
    TLabel *Label19;
    TLabel *Label20;
    TLabel *Label21;
    TLabel *Label22;
    TLabel *Label23;
    TLabel *Label24;
    TButton *Button1;
    TImage *Image1;
    void __fastcall Button1Click(TObject *Sender);

    private:

    public:
    __fastcall TForm6(TComponent* Owner);
};

extern PACKAGE TForm6 *Form6;
#endif
