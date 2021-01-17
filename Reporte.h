/*---------------------------------------------------------------------------*\
 | Archivo       : Reporte.h                                                 |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Héctor Díaz - Paul Leger.               |
 | Descripción   : Esta librería empaqueta la clase TForm2 para ser usada en |
 |                 otros archivos.                                           |
 | Usada por     : Reporte.cpp, Editor.cpp.                                  |
\*---------------------------------------------------------------------------*/

#ifndef ReporteH
#define ReporteH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>

class TForm2 : public TForm
{
    __published:
    TPanel *Panel1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TEdit *Edit1;
    TProgressBar *ProgressBar1;
    TMemo *Memo1;
    void __fastcall cierraForm(TObject *Sender, TCloseAction &Action);

    private:
    TFont *fuente;

    public:
    __fastcall TForm2(TComponent* Owner);
    void limpia(String ruta);
    void habilita();
    void deshabilita();
    void porDefecto();
};

extern PACKAGE TForm2 *Form2;
#endif
