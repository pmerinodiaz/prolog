/*---------------------------------------------------------------------------*\
 | Archivo       : Meta.h                                                    |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Héctor Díaz - Paul Leger.               |
 | Descripción   : Esta librería empaqueta la clase TForm3 para ser usada en |
 |                 otros archivos.                                           |
 | Usada por     : Editor.cpp, Meta.cpp.                                     |
\*---------------------------------------------------------------------------*/

#ifndef MetaH
#define MetaH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "Consulta.h"
#include "Motor.h"
#include "ListaSolucion.h"
#include "Nodo.h"
#include "Lista.h"

class TForm3 : public TForm
{
    __published:
    TGroupBox *GroupBox1;
    TGroupBox *GroupBox2;
    TMemo *Memo1;
    TMemo *Memo2;
    TButton *Button1;
    TButton *Button2;
    void __fastcall cierraForm(TObject *Sender, TCloseAction &Action);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);

    private:
    TFont *fuente1, *fuente2;
    /*----------------------------agregado por paul-------------------------*/
    Motor motorInferencia;
    bool Respuesta_unitaria;
    ListaSolucion *Soluciones;
    ElementoSoluciones *GrupoSolucion;
    UnaSolucion SolucionParticular1;
    UnaSolucion SolucionParticular2;
    UnaSolucion SolucionParticular3;
    String RespuestaTexto;
    String MostrarArbolInferencia;
    int numeroSoluciones;
    /*---------------------fin de agregado por paul-------------------------*/

    public:
    int Max_Nodos;
    __fastcall TForm3(TComponent* Owner);
    void deshabilita();
    void habilita();
    void porDefecto();
};

extern PACKAGE TForm3 *Form3;
#endif
