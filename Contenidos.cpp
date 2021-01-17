/*---------------------------------------------------------------------------*\
 | Archivo       : Contenidos.cpp                                            |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Descripción   : Esta es la forma en donde se muestran los contenidos (FAQ)|
 |                 del software Prolog.                                      |
 | Usada por     : Editor.cpp.                                               |
\*---------------------------------------------------------------------------*/

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop
#include "Contenidos.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

// Puntero a la TForm8.
TForm8 *Form8;

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall TForm8(TComponent* Owner)                      |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : Un puntero a TComponent.                                  |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método constructor.                                       |
\*---------------------------------------------------------------------------*/
__fastcall TForm8::TForm8(TComponent* Owner):TForm(Owner)
{
}

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall FormCreate(TObject* Sender)                    |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : Un puntero a TObject.                                     |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que carga los contenidos del archivo FAQ en el     |
 |                 <ListBox1>.                                               |
\*---------------------------------------------------------------------------*/
void __fastcall TForm8::FormCreate(TObject *Sender)
{
    FILE * archivo;
    char item[MAXITEM];
    int caracter, contador;

    archivo = fopen("C:\\Prolog\\Base Datos\\FAQProlog.txt", "r");

    if (!archivo)
    {
      Edit1->Enabled = false;
      ListBox1->Enabled = false;
      ListBox1->Items->Add("No se encontró el archivo FAQProlog.txt.");
      return;
    }

    while (!feof(archivo))
    {
      caracter = fgetc(archivo);

      if (caracter == '[')
      {
        fscanf(archivo, "%s", item);
        contador = 0;

        while ((item[contador] != NULL) && (contador < MAXITEM))
        {
          if (item[contador] == '_')
            item[contador] = ' ';
          contador++;
        }

        ListBox1->Items->Add(item);
      }
    }

    ListBox1->ItemIndex = 0;
    fclose(archivo);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall changeEdit1(TObject *Sender)                   |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : Un puntero a TObject.                                     |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que se activa cuando el usuario ingresa un caracer |
 |                 al <Edit1>. Se hace la búsqueda en los contenidos y se    |
 |                 despliegua la información en el <Label4>.                 |
\*---------------------------------------------------------------------------*/
void __fastcall TForm8::changeEdit1(TObject *Sender)
{
    char contenidos[MAXITEM], item[MAXITEM];
    int contador1, contador2, coincidencias[500], maxima_coincidencia, indice;

    indice = 0;
    strcpy(contenidos, Edit1->Text.c_str());

    for (contador1 = 0; contador1 < ListBox1->Items->Count; contador1++)
      coincidencias[contador1] = 0;

    for (contador1 = 0 ; contador1 < ListBox1->Items->Count; contador1++)
    {
      strcpy(item, ListBox1->Items->Strings[indice].c_str());
      coincidencias[contador1] = 0;
      contador2 = 0;

      while (contenidos[contador2])
      {
        if (toupper(contenidos[contador2]) != toupper(item[contador2]))
          break;
        else coincidencias[contador1]++;
        contador2++;
      }
      indice++;

      if (contador1 > 0)
      {
        if (coincidencias[contador1 - 1] > coincidencias[contador1])
          break;
      }
    }

    maxima_coincidencia = coincidencias[0];
    indice = 0;

    for (contador1 = 0; contador1 < ListBox1->Items->Count; contador1++)
      if (coincidencias[contador1] > maxima_coincidencia)
      {
        maxima_coincidencia = coincidencias[contador1];
        indice = contador1;
      }

    ListBox1->ItemIndex = indice;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall Edit1KeyPress(TObject *Sender, char &Key)      |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : Un puntero a TObject y el caracter ingresado al <Edit1>.  |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que despliega la información encontrada.           |
\*---------------------------------------------------------------------------*/
void __fastcall TForm8::Edit1KeyPress(TObject *Sender, char &Key)
{
    if (Key == 13)
      muestraInformacion();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall ListBox1Click(TObject *Sender)                 |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : Un puntero a TObject.                                     |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que muestra un tópico en el <Edit1> cuando el      |
 |                 usuario hace click en el <ListBox1>.                      |
\*---------------------------------------------------------------------------*/
void __fastcall TForm8::ListBox1Click(TObject *Sender)
{
    Edit1->Text = ListBox1->Items->Strings[ListBox1->ItemIndex].c_str();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall ListBox1DbClick(TObject *Sender)               |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : Un puntero a TObject.                                     |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que despliega la información encontrada cuando se  |
 |                 hace doble click en el <ListBox1>.                        |
\*---------------------------------------------------------------------------*/
void __fastcall TForm8::ListBox1DbClick(TObject *Sender)
{
    muestraInformacion();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall Button2Click(TObject *Sender)                  |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : Un puntero a TObject.                                     |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que se activa cuando el usuario pulsa el botón     |
 |                 Cerrar. Se cierra la forma.                               |
\*---------------------------------------------------------------------------*/
void __fastcall TForm8::Button2Click(TObject *Sender)
{
    Close();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall Button1Click(TObject *Sender)                  |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : Un puntero a TObject.                                     |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que se ejecuta cuando el usuario pulsa el botón    |
 |                 Muestra. Se llama al método que muestra la información.   |
\*---------------------------------------------------------------------------*/
void __fastcall TForm8::Button1Click(TObject *Sender)
{
    muestraInformacion();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void muestraInformacion()                                 |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Entradas      : Un puntero a TObject.                                     |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que realiza la operación de leer el archivo de     |
 |                 de texto FAQProlog.txt y busca las coincidencias con el   |
 |                 texto ingresado. Posteriormente se despliega la           |
 |                 información encontrada (de haberla).                      |
\*---------------------------------------------------------------------------*/
void TForm8::muestraInformacion()
{
    FILE *archivo;
    char item[MAXITEM];
    int caracter, contador;
    String agregacion;

    Edit1->Text     = ListBox1->Items->Strings[ListBox1->ItemIndex];
    Label4->Caption = ListBox1->Items->Strings[ListBox1->ItemIndex];

    archivo = fopen("C:\\Prolog\\Base Datos\\FAQProlog.txt", "r");

    if (!archivo)
    {
      Edit1->Enabled = false;
      ListBox1->Clear();
      ListBox1->Enabled = false;
      ListBox1->Items->Add("No se encontró el archivo FAQProlog.txt.");
      return;
    }

    while (!feof(archivo))
    {
      caracter = fgetc(archivo);

      if (caracter == '[')
      {
        fscanf(archivo, "%s", item);

        for (contador = 0; contador < int(strlen(item)); contador++)
          if (item[contador] == '_')
            item[contador] = ' ';

        if (strcmp(item,
            ListBox1->Items->Strings[ListBox1->ItemIndex].c_str()) == 0)
        {
          Label5->Caption = "";
          while (!feof(archivo))
          {
            fscanf(archivo, "%s", item);
            contador = 0;

            while (item[contador])
            {
              if (item[contador] == '|')
                item[contador] = 13;

              if (item[contador] == '_' )
                item[contador] = ' ';

              contador++;
            }

            if ((item[0] == ']') || (item[0] == '['))
              break;
            else
            {
              agregacion = item;
              Label5->Caption = Label5->Caption + " " +agregacion;
            }
          }
          break;
        }
      }
      caracter = ' ';
    }
    fclose(archivo);
}


