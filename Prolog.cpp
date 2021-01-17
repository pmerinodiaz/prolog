//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("Prolog.res");
USEFORM("Editor.cpp", Form1);
USEUNIT("Interprete.cpp");
USEUNIT("Predicado.cpp");
USEUNIT("Regla.cpp");
USEFORM("Reporte.cpp", Form2);
USEFORM("Meta.cpp", Form3);
USEFORM("SQL.cpp", Form4);
USEUNIT("Consulta.cpp");
USEUNIT("Lista.cpp");
USEUNIT("ListaSolucion.cpp");
USEUNIT("Motor.cpp");
USEUNIT("Nodo.cpp");
USEUNIT("InterfazBC.cpp");
USEUNIT("InterfazBH.cpp");
USEUNIT("Cadena.cpp");
USEUNIT("Objeto.cpp");
USEFORM("Grafica.cpp", Form5);
USEFORM("AcercaDe.cpp", Form6);
USEFORM("TamanioPila.cpp", Form7);
USEFORM("Contenidos.cpp", Form8);
USEFORM("Avance.cpp", Form9);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TForm1), &Form1);
        Application->CreateForm(__classid(TForm2), &Form2);
        Application->CreateForm(__classid(TForm3), &Form3);
        Application->CreateForm(__classid(TForm4), &Form4);
        Application->CreateForm(__classid(TForm5), &Form5);
        Application->CreateForm(__classid(TForm6), &Form6);
        Application->CreateForm(__classid(TForm7), &Form7);
        Application->CreateForm(__classid(TForm8), &Form8);
        Application->CreateForm(__classid(TForm9), &Form9);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
