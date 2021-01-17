/*---------------------------------------------------------------------------*\
 | Archivo       : Grafica.h                                                 |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Descripción   : Esta librería empaqueta la clase TForm5 para ser usada en |
 |                 otros archivos.                                           |
 | Usada por     : Grafica.cpp, Editor.cpp, Meta.cpp.                        |
\*---------------------------------------------------------------------------*/

#ifndef GraficaH
#define GraficaH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Editor.h"
#include "Nodo.h"
#include "Lista.h"

class TForm5 : public TForm
{
    __published:
    TGroupBox *GroupBox1;
    TMemo *Memo1;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormResize(TObject *Sender);

    private:
    TFont *fuente;
    Nodo *Raiz;
    Lista *Lista_variable;
    bool Atomos;

    public:
    __fastcall TForm5(TComponent* Owner);
    void recibeNodoRaiz(Nodo *raiz, Lista *Lista_var,bool ConAtomos);
    void GraficandoInferencia(Nodo *aux);
    String CrearString(Nodo *aux);
    void limpia();
    void habilita();
    void deshabilita();
    void porDefecto();
};

extern PACKAGE TForm5 *Form5;
#endif
