/*---------------------------------------------------------------------------*\
 | Archivo       : Contenidos.h                                              |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Descripción   : Esta librería empaqueta la clase TForm8 para ser usada en |
 |                 otros archivos.                                           |
 | Usada por     : Editor.cpp.                                               |
\*---------------------------------------------------------------------------*/

#ifndef ContenidosH
#define ContenidosH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#define MAXITEM 250

class TForm8 : public TForm
{
    __published:
    TGroupBox *GroupBox1;
    TEdit *Edit1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TListBox *ListBox1;
    TButton *Button1;
    TButton *Button2;
    TGroupBox *GroupBox2;
    TLabel *Label5;
    TLabel *Label4;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall changeEdit1(TObject *Sender);
    void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
    void __fastcall ListBox1Click(TObject *Sender);
    void __fastcall ListBox1DbClick(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);

    private:

    public:
    __fastcall TForm8(TComponent* Owner);
    void muestraInformacion();
};

extern PACKAGE TForm8 *Form8;
#endif
