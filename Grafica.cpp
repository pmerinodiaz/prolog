/*---------------------------------------------------------------------------*\
 | Archivo       : Grafica.cpp                                               |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Descripción   : Esta es la forma en donde se muestra el árbol de          |
 |                 generado por la inferencia efectuada en la consulta       |
 |                 ingresada por el usuario.                                 |
 | Usada por     : Editor.cpp, Meta.cpp.                                     |
\*---------------------------------------------------------------------------*/

#include <vcl.h>
#pragma hdrstop
#include "Grafica.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

// Puntero a la TForm5.
TForm5 *Form5;

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall TForm5(TComponent* Owner)                      |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : Un puntero a TComponent.                                  |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método constructor en el cual se crean e inicializan      |
 |                 las variables y objetos utilizados porteriormente en la   |
 |                 clase.                                                    |
\*---------------------------------------------------------------------------*/
__fastcall TForm5::TForm5(TComponent* Owner):TForm(Owner)
{
    // Font por defecto.
    fuente = new TFont();
    fuente->Assign(Memo1->Font);

    Raiz = NULL;
    Atomos = false;
    limpia();
    deshabilita();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall FormClose(TObject *Sender, TCloseAction &Action)                      |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : Un puntero a TObject y otro puntero a TComponent.         |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que se ejecuta cuando el usuario cierra esta Form. |
 |                 Se modifican las propiedades de esta forma y del menú     |
 |                 principal.                                                |
\*---------------------------------------------------------------------------*/
void __fastcall TForm5::FormClose(TObject *Sender, TCloseAction &Action)
{
    Visible = false;
    Form1->Graficas1->Checked = false;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void recibeNodoRaiz(Nodo *raiz, Lista *Lista_var,         |
 |                                     bool conAtomos)                       |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : La raíz del árbol, La lista de soluciones y si tiene      |
 |                 átomos o no.                                              |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que recibe información generada por la inferecnia  |
 |                 y llama al método que grafica estos datos.                |
\*---------------------------------------------------------------------------*/
void TForm5::recibeNodoRaiz(Nodo *raiz, Lista *Lista_var, bool conAtomos)
{
    Raiz = raiz;
    Atomos = conAtomos;
    Lista_variable = Lista_var;
    limpia();
    GraficandoInferencia(Raiz);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void GraficandoInferencia(Nodo *aux)                      |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : Puntero al Nodo del Arbol.                                |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que va incorporando los nodos del árbol al         |
 |                 <ListBox1>. El recorrido del árbol se hace en Pre-Orden.  |
\*---------------------------------------------------------------------------*/
void TForm5::GraficandoInferencia(Nodo *aux)
{
   if (aux != NULL)
   {
     String StringNodo = CrearString(aux);
     Memo1->Lines->Add(StringNodo);
     GraficandoInferencia(aux->Hijo_izq );
     GraficandoInferencia(aux->Hijo_der );
   }
}

/*---------------------------------------------------------------------------*\
 | Nombre        : String CrearString(Nodo *nodo)                            |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : Puntero al Nodo del Arbol.                                |
 | Salidas       : El String respuesta que contiene la información desplegada|
 |                 para cada nodo.                                           |
 | Descripción   : En este método se forma el String que representa a un     |
 |                 nodo del arbol de inferencia.                             |
\*---------------------------------------------------------------------------*/
String TForm5::CrearString(Nodo *nodo)
{
    String Respuesta;

    if (nodo->Predicado!= NULL)
      Respuesta=nodo->Predicado;
    else Respuesta="Raiz";

    Respuesta+= "(";

    if (Atomos == false)
      Respuesta+= "X" + IntToStr(nodo->IDVA1);
    else Respuesta+= Lista_variable->Busca_valor(nodo->IDVA1);

    if (nodo->IDVA2 != NULL)
    {
      Respuesta+= " , ";
      if (Atomos == false)
        Respuesta+= "X" + IntToStr(nodo->IDVA2);
      else Respuesta+= Lista_variable->Busca_valor(nodo->IDVA2);
    }

    Respuesta+= ")";

   if (nodo->Hijo_izq==NULL)
                Respuesta+=" -- Sin hijos.";
   if (nodo->Hijo_izq != NULL && nodo->Hijo_der == NULL)
                Respuesta+=" -- 1 hijos.";
   if (nodo->Hijo_izq != NULL && nodo->Hijo_der != NULL)
                Respuesta+=" -- 2 hijos.";

    return (Respuesta);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void habilita()                                           |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : En este método se habilita la escritura en el <Memo1>.    |
\*---------------------------------------------------------------------------*/
void TForm5::habilita()
{
    Memo1->Enabled = true;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void deshabilita()                                        |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : En este método se deshabilita la escritura en el <Memo1>. |
\*---------------------------------------------------------------------------*/
void TForm5::deshabilita()
{
    Memo1->Enabled = false;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void limpia()                                             |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : En este método se limpia el <Memo1>.                      |
\*---------------------------------------------------------------------------*/
void TForm5::limpia()
{
    Memo1->Clear();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void porDefecto()                                         |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que setea la fuente y el color por defecto del     |
 |                 <Memo1>.                                                  |
\*---------------------------------------------------------------------------*/
void TForm5::porDefecto()
{
    // Valores por defecto del Editor.
    Memo1->Font->Assign(fuente);
    Memo1->Color = clWindow;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall FormResize(TObject *Sender)                    |
 | Programado por: Paul Leger.                                               |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que setea se activa cuando el usuario cambia el    |
 |                 tamaño de la forma.                                       |
\*---------------------------------------------------------------------------*/
void __fastcall TForm5::FormResize(TObject *Sender)
{
    GroupBox1->Width = Width-17;
    GroupBox1->Height = Height-35;
    Memo1->Width = GroupBox1->Width-20;
    Memo1->Height = GroupBox1->Height-30;
}


