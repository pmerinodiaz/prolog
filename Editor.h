/*---------------------------------------------------------------------------*\
 | Archivo       : Editor.h                                                  |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Héctor Díaz - Paul Leger.               |
 | Descripción   : Esta librería empaqueta la clase TForm1 para ser usada en |
 |                 otros archivos.                                           |
 | Uso           : En la Form principal del proyecto.                        |
\*---------------------------------------------------------------------------*/

#ifndef EditorH
#define EditorH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>

class TForm1 : public TForm
{
    __published:
    TMainMenu *MainMenu1;
    TToolBar *ToolBar1;
    TMemo *Memo1;
    TStatusBar *StatusBar1;
    TMenuItem *Archivo1;
    TMenuItem *Nuevo1;
    TMenuItem *Abrir1;
    TMenuItem *Guardar1;
    TMenuItem *GuardarComo1;
    TMenuItem *Salir1;
    TMenuItem *Interpretar1;
    TMenuItem *Ver1;
    TMenuItem *Reporte1;
    TMenuItem *Metas1;
    TMenuItem *Graficas1;
    TMenuItem *Ayuda1;
    TMenuItem *Contenidos1;
    TMenuItem *AcercaDe0;
    TMenuItem *AcercaDe1;
    TMenuItem *Configuracion1;
    TMenuItem *Fuente1;
    TMenuItem *Color1;
    TMenuItem *n2;
    TMenuItem *TamaoPila1;
    TMenuItem *Predeterminado1;
    TMenuItem *Editor1;
    TMenuItem *Reporte2;
    TMenuItem *Consulta1;
    TMenuItem *Grficas1;
    TMenuItem *Editor2;
    TMenuItem *Reporte3;
    TMenuItem *Consulta2;
    TMenuItem *Grficas2;
    TMenuItem *Solucin1;
    TMenuItem *Solucin2;
    TMenuItem *Edicin1;
    TMenuItem *Deshacer1;
    TMenuItem *N3;
    TMenuItem *Cortar1;
    TMenuItem *Copiar1;
    TMenuItem *Pegar1;
    TMenuItem *N4;
    TMenuItem *Imprimir1;
    TMenuItem *N1;
    TSpeedButton *SpeedButton8;
    TSpeedButton *SpeedButton10;
    TSpeedButton *SpeedButton11;
    TSpeedButton *SpeedButton12;
    TSpeedButton *SpeedButton13;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TSpeedButton *SpeedButton3;
    TSpeedButton *SpeedButton4;
    TSpeedButton *SpeedButton5;
    TSpeedButton *SpeedButton6;
    TSpeedButton *SpeedButton7;
    TSpeedButton *SpeedButton9;
    TOpenDialog *OpenDialog1;
    TSaveDialog *SaveDialog1;
    TFontDialog *FontDialog1;
    TColorDialog *ColorDialog1;
    TPrintDialog *PrintDialog1;
    TFindDialog *FindDialog1;
    void __fastcall acomodaMemo(TObject *Sender);
    void __fastcall cierraForm(TObject *Sender, TCloseAction &Action);
    void __fastcall Nuevo1Click(TObject *Sender);
    void __fastcall Abrir1Click(TObject *Sender);
    void __fastcall Guardar1Click(TObject *Sender);
    void __fastcall GuardarComo1Click(TObject *Sender);
    void __fastcall Salir1Click(TObject *Sender);
    void __fastcall Deshacer1Click(TObject *Sender);
    void __fastcall Cortar1Click(TObject *Sender);
    void __fastcall Copiar1Click(TObject *Sender);
    void __fastcall Pegar1Click(TObject *Sender);
    void __fastcall Reporte1Click(TObject *Sender);
    void __fastcall Metas1Click(TObject *Sender);
    void __fastcall Graficas1Click(TObject *Sender);
    void __fastcall Interpretar1Click(TObject *Sender);
    void __fastcall Contenidos1Click(TObject *Sender);
    void __fastcall AcercaDe1Click(TObject *Sender);
    void __fastcall Editor1Click(TObject *Sender);
    void __fastcall Reporte2Click(TObject *Sender);
    void __fastcall Consulta1Click(TObject *Sender);
    void __fastcall Solucin1Click(TObject *Sender);
    void __fastcall Grficas1Click(TObject *Sender);
    void __fastcall Editor2Click(TObject *Sender);
    void __fastcall Reporte3Click(TObject *Sender);
    void __fastcall Consulta2Click(TObject *Sender);
    void __fastcall Solucin2Click(TObject *Sender);
    void __fastcall Grficas2Click(TObject *Sender);
    void __fastcall TamaoPila1Click(TObject *Sender);
    void __fastcall Predeterminado1Click(TObject *Sender);
    void __fastcall Imprimir1Click(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
    void __fastcall SpeedButton3Click(TObject *Sender);
    void __fastcall SpeedButton4Click(TObject *Sender);
    void __fastcall SpeedButton5Click(TObject *Sender);
    void __fastcall SpeedButton6Click(TObject *Sender);
    void __fastcall SpeedButton7Click(TObject *Sender);
    void __fastcall SpeedButton9Click(TObject *Sender);
    void __fastcall SpeedButton8Click(TObject *Sender);
    void __fastcall SpeedButton10Click(TObject *Sender);
    void __fastcall SpeedButton11Click(TObject *Sender);
    void __fastcall SpeedButton12Click(TObject *Sender);
    void __fastcall SpeedButton13Click(TObject *Sender);

    private:
    AnsiString FFileName;
    int TerminoPrograma;
    String ruta;
    String programa;
    TFont *fuente;

    public:
    __fastcall TForm1(TComponent* Owner);
    void nuevoArchivo();
    void abrirArchivo();
    void guardarArchivo();
    void guardarComoArchivo();
    void imprime();
    void salirArchivo();
    void reporte();
    void metas();
    void graficas();
    void nuevo();
    void abre();
    void guarda();
    void sale();
    bool verificaCambios();
    int confirmaGuardar();
    void interpretar();
    void apuntaError(int linea);
};

extern PACKAGE TForm1 *Form1;
#endif
