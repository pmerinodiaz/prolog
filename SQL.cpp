/*---------------------------------------------------------------------------*\
 | Archivo       : SQL.cpp                                                   |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Descripción   : Esta Form es la que contiene la Table y el Query que nos  |
 |                 ayudarán para ingresar los datos a la Base de Hecho y a la|
 |                 Base de Conocimiento. Además el Lenguaje Estructurado de  |
 |                 de Consulta (SQL) lo utilizaremos para obtener respuestas |
 |                 a las consultas realizar por el Interprete y el Motor de  |
 |                 Inferencia.                                               |
 | Usada por     : Editor.cpp, Interprete.cpp                                |
\*---------------------------------------------------------------------------*/

#include <vcl.h>
#include <stdlib.h>
#pragma hdrstop
#include "SQL.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

// Puntero al TForm4.
TForm4 *Form4;

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall TForm4(TComponent* Owner)                      |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : Un puntero a TComponent.                                  |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método constructor de la <Form4>.                         |
\*---------------------------------------------------------------------------*/
__fastcall TForm4::TForm4(TComponent* Owner):TForm(Owner)
{
    try
    {
      Table1->DatabaseName = "C:\\Prolog\\Base Datos\\";
    }
    catch (EDatabaseError &e)
    {
      ShowMessage("RR");
      exit(0);
    }

    try
    {
      Query1->DatabaseName = "C:\\Prolog\\Base Datos\\";
    }
    catch(EDatabaseError &e)
    {
      ShowMessage("RR");
      exit(0);
    }
}

/*---------------------------------------------------------------------------*\
 | Nombre        : String obtieneString(String consulta, String campo)       |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El String correspondiente a la consulta SQL y el String   |
 |                 del nombre del campo a retornar.                          |
 | Salidas       : El valor obtenido de la consulta.                         |
 | Descripción   : Método que devuelve respuestas del tipo String.           |
 |                 En este método se hace un llamado al método <ejecuta()>   |
 |                 con parámetro <consulta>. Posteriormente se devuelve el   |
 |                 valor obtenido de el <campo>.                             |
\*---------------------------------------------------------------------------*/
String TForm4::obtieneString(String consulta, String campo)
{
    ejecuta(consulta);

    return (Query1->FieldByName(campo)->AsString);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : String obtieneInteger(String consulta, String campo)      |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El String correspondiente a la consulta SQL y el String   |
 |                 del nombre del campo a retornar.                          |
 | Salidas       : El valor obtenido de la consulta.                         |
 | Descripción   : Método que devuelve respuestas del tipo int.              |
 |                 En este método se hace un llamado al método <ejecuta()>   |
 |                 con parámetro <consulta>. Posteriormente se devuelve el   |
 |                 valor obtenido de el <campo>.                             |
\*---------------------------------------------------------------------------*/
int TForm4::obtieneInteger(String consulta, String campo)
{
    ejecuta(consulta);

    return (Query1->FieldByName(campo)->AsInteger);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int nuevoIDObjeto()                                       |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El valor obtenido de la consulta incrementado en 1.       |
 | Descripción   : Método en el cual se realiza una consulta SQL que nos     |
 |                 permite obtener el número de objetos que hay en la Tabla  |
 |                 <Objeto.db>. Este contador se incrementa en 1 y se        |
 |                 retorna como un nuevo <ID_Objeto>.                        |
\*---------------------------------------------------------------------------*/
int TForm4::nuevoIDObjeto()
{
    String consulta;

    consulta = "Select Count(ID_Objeto) As Total From Objeto";
    ejecuta(consulta);

    return (Query1->FieldByName("Total")->AsInteger + 1);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int nuevoIDPredicado()                                    |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El valor obtenido de la consulta incrementado en 1.       |
 | Descripción   : Método en el cual se realiza una consulta SQL que nos     |
 |                 permite obtener el número de predicados que hay en la     |
 |                 Tabla <Predicado.db>. Este contador se incrementa en 1 y  |
 |                 se retorna como un nuevo <ID_Predicado>.                  |
\*---------------------------------------------------------------------------*/
int TForm4::nuevoIDPredicado()
{
    String consulta;

    consulta = "Select Count(ID_Predicado) As Total From Predicado";
    ejecuta(consulta);

    return (Query1->FieldByName("Total")->AsInteger + 1);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int nuevoIDArgumentoPredicado()                           |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El valor obtenido de la consulta incrementado en 1.       |
 | Descripción   : Método en el cual se realiza una consulta SQL que nos     |
 |                 permite obtener el número de argumentos de predicado que  |
 |                 hay en la Tabla <Argumento_Predicado.db>. Este contador se|
 |                 incrementa en 1 y se retorna como un nuevo                |
 |                 <ID_Argumento_Predicado>.                                 |
\*---------------------------------------------------------------------------*/
int TForm4::nuevoIDArgumentoPredicado()
{
    String consulta;

    consulta = "Select Count(ID_Argumento_Predicado) As Total From Argumento_Predicado";
    ejecuta(consulta);

    return (Query1->FieldByName("Total")->AsInteger + 1);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int nuevoIDHecho()                                        |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El valor obtenido de la consulta incrementado en 1.       |
 | Descripción   : Método en el cual se realiza una consulta SQL que nos     |
 |                 permite obtener el número de hechos que hay en la Tabla   |
 |                 <Hecho.db>. Este contador se incrementa en 1 y se retorna |
 |                 como un nuevo <ID_Hecho>.                                 |
\*---------------------------------------------------------------------------*/
int TForm4::nuevoIDHecho()
{
    String consulta;

    consulta = "Select Count(ID_Hecho) As Total From Hecho";
    ejecuta(consulta);

    return (Query1->FieldByName("Total")->AsInteger + 1);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int nuevoIDArgumentoHecho()                               |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El valor obtenido de la consulta incrementado en 1.       |
 | Descripción   : Método en el cual se realiza una consulta SQL que nos     |
 |                 permite obtener el número de argumentos de hechos que hay |
 |                 en la Tabla <Argumento_Hecho.db>. Este contador se        |
 |                 incrementa en 1 y se retorna como un nuevo                |
 |                 <ID_Argumento_Hecho>.                                     |
\*---------------------------------------------------------------------------*/
int TForm4::nuevoIDArgumentoHecho()
{
    String consulta;

    consulta = "Select Count(ID_Argumento_Hecho) As Total From Argumento_Hecho";
    ejecuta(consulta);

    return (Query1->FieldByName("Total")->AsInteger + 1);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int nuevoIDRegla()                                        |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El valor obtenido de la consulta incrementado en 1.       |
 | Descripción   : Método en el cual se realiza una consulta SQL que nos     |
 |                 permite obtener el número de reglas que hay en la Tabla   |
 |                 <Regla.db>. Este contador se incrementa en 1 y se retorna |
 |                 como un nuevo <ID_Regla>.                                 |
\*---------------------------------------------------------------------------*/
int TForm4::nuevoIDRegla()
{
    String consulta;

    consulta = "Select Count(ID_Regla) As Total From Regla";
    ejecuta(consulta);

    return (Query1->FieldByName("Total")->AsInteger + 1);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int nuevoIDOrdenHecho()                                   |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El valor obtenido de la consulta incrementado en 1.       |
 | Descripción   : Método en el cual se realiza una consulta SQL que nos     |
 |                 permite obtener el número de ordenes de hechos que hay en |
 |                 la Tabla <Orden_Hecho.db>. Este contador se incrementa en |
 |                 1 y se retorna como un nuevo <ID_Orden_Hecho>.            |
\*---------------------------------------------------------------------------*/
int TForm4::nuevoIDOrdenHecho()
{
    String consulta;

    consulta = "Select Count(ID_Orden_Hecho) As Total From Orden_Hecho";
    ejecuta(consulta);

    return (Query1->FieldByName("Total")->AsInteger + 1);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int nuevoIndiceHecho()                                    |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El id_predicado y el id_tipo_hecho.                       |
 | Salidas       : El valor obtenido de la consulta incrementado en 1.       |
 | Descripción   : Método en el cual se realiza una consulta SQL que nos     |
 |                 permite obtener el número de hechos que hay en la Tabla   |
 |                 <Hechos.db> donde el <ID_Predicado> es <id_predicado> y   |
 |                 el <ID_Tipo_Hecho> es <id_tipo_hecho>. Este contador se   |
 |                 incrementa en 1 y se retorna como un nuevo <Indice_Hecho>.|
\*---------------------------------------------------------------------------*/
int TForm4::nuevoIndiceHecho(int id_predicado, int id_tipo_hecho)
{
    String consulta;

    consulta = "Select Count(*) As Total From Hecho Where ID_Predicado = " +IntToStr(id_predicado)+ " And ID_Tipo_Hecho = " +IntToStr(id_tipo_hecho)+ "";
    ejecuta(consulta);

    return (Query1->FieldByName("Total")->AsInteger + 1);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int ultimoIDHecho()                                       |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El id_predicado.                                          |
 | Salidas       : El valor obtenido de la consulta.                         |
 | Descripción   : Método en el cual se realiza una consulta SQL que nos     |
 |                 permite obtener el valor máximo del <ID_Hecho> de los     |
 |                 hechos que hay en la Tabla <Hechos.db> donde el           |
 |                 <ID_Predicado> es <id_predicado>.                         |
\*---------------------------------------------------------------------------*/
int TForm4::ultimoIDHecho(int id_predicado)
{
    String consulta;

    consulta = "Select Max(ID_Hecho) As Ultimo From Hecho Where Id_Predicado = " +IntToStr(id_predicado)+ "And (ID_Tipo_Hecho = 1 Or ID_Tipo_Hecho = 2)";
    ejecuta(consulta);

    return (Query1->FieldByName("Ultimo")->AsInteger);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int ultimoHechoConsecuente()                              |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El valor obtenido de la consulta.                         |
 | Descripción   : Método en el cual se realiza una consulta SQL que nos     |
 |                 permite obtener el valor máximo del <ID_Hecho> de los     |
 |                 hechos que hay en la Tabla <Hechos.db> donde el           |
 |                 <ID_Tipo_Hecho> es 1 o 2.                                 |
\*---------------------------------------------------------------------------*/
int TForm4::ultimoHechoConsecuente()
{
    String consulta;

    consulta = "Select Max(ID_Hecho) As Ultimo From Hecho Where ID_Tipo_Hecho = 1 Or ID_Tipo_Hecho = 2";
    ejecuta(consulta);

    return (Query1->FieldByName("Ultimo")->AsInteger);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int ultimoHecho()                                         |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El id_predicado.                                          |
 | Salidas       : El valor obtenido de la consulta.                         |
 | Descripción   : Método en el cual se realiza una consulta SQL que nos     |
 |                 permite obtener el valor máximo del <ID_Hecho> de los     |
 |                 hechos que hay en la Tabla <Hechos.db>.                   |
\*---------------------------------------------------------------------------*/
int TForm4::ultimoHecho()
{
    String consulta;

    consulta = "Select Max(ID_Hecho) As Ultimo From Hecho";
    ejecuta(consulta);

    return (Query1->FieldByName("Ultimo")->AsInteger);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void ejecuta(String consulta)                             |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El String de consulta.                                    |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método en el cual se ejecuta la consulta SQL.             |
\*---------------------------------------------------------------------------*/
void TForm4::ejecuta(String consulta)
{
    Query1->SQL->Clear();
    Query1->SQL->Add(consulta);
    Query1->Open();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void insertaObjeto(int id_objeto, int id_tipo_dato,       |
 |                                    int id_tipo_objeto,                    |
 |                                    String nombre_objeto)                  |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : Los valores para todos los campos de un registro de la    |
 |                 Tabla <Objeto.db>.                                        |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método en el cual se inserta una tupla en la tabla        |
 |                 <Objeto.db>.                                              |
\*---------------------------------------------------------------------------*/
void TForm4::insertaObjeto(int id_objeto, int id_tipo_dato, int id_tipo_objeto, String nombre_objeto)
{
    Table1->TableName = "Objeto.db";
    Table1->Open();
    Table1->Insert();
    Table1->FieldByName("ID_Objeto")->AsInteger      = id_objeto;
    Table1->FieldByName("ID_Tipo_Dato")->AsInteger   = id_tipo_dato;
    Table1->FieldByName("ID_Tipo_Objeto")->AsInteger = id_tipo_objeto;
    Table1->FieldByName("Nombre_Objeto")->AsString   = nombre_objeto;
    Table1->Post();
    Table1->Close();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void insertaPredicado(int id_predicado,                   |
 |                                       int id_tipo_predicado,              |
 |                                       String nombre_predicado)            |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : Los valores para todos los campos de un registro de la    |
 |                 Tabla <Predicado.db>.                                     |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método en el cual se inserta una tupla en la tabla        |
 |                 <Predicado.db>.                                              |
\*---------------------------------------------------------------------------*/
void TForm4::insertaPredicado(int id_predicado, int id_tipo_predicado, String nombre_predicado)
{
    Table1->TableName = "Predicado.db";
    Table1->Open();
    Table1->Insert();
    Table1->FieldByName("ID_Predicado")->AsInteger      = id_predicado;
    Table1->FieldByName("ID_Tipo_Predicado")->AsInteger = id_tipo_predicado;
    Table1->FieldByName("Nombre_Predicado")->AsString   = nombre_predicado;
    Table1->Post();
    Table1->Close();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void insertaArgumentoPredicado(int id_argumento_predicado,|
 |                                                int id_predicado,          |
 |                                                int id_objeto,             |
 |                                             int orden_argumento_predicado)|
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : Los valores para todos los campos de un registro de la    |
 |                 Tabla <Argumento_Predicado.db>.                           |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método en el cual se inserta una tupla en la tabla        |
 |                 <Argumento_Predicado.db>.                                 |
\*---------------------------------------------------------------------------*/
void TForm4::insertaArgumentoPredicado(int id_argumento_predicado, int id_predicado, int id_objeto, int orden_argumento_predicado)
{
    Table1->TableName = "Argumento_Predicado.db";
    Table1->Open();
    Table1->Insert();
    Table1->FieldByName("ID_Argumento_Predicado")->AsInteger    = id_argumento_predicado;
    Table1->FieldByName("ID_Predicado")->AsInteger              = id_predicado;
    Table1->FieldByName("ID_Objeto")->AsInteger                 = id_objeto;
    Table1->FieldByName("Orden_Argumento_Predicado")->AsInteger = orden_argumento_predicado;
    Table1->Post();
    Table1->Close();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void insertaHecho(int id_hecho, int indice_hecho,         |
 |                                   int id_predicado, int id_tipo_hecho)    |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : Los valores para todos los campos de un registro de la    |
 |                 Tabla <Hecho.db>.                                         |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método en el cual se inserta una tupla en la tabla        |
 |                 <Hecho.db>.                                               |
\*---------------------------------------------------------------------------*/
void TForm4::insertaHecho(int id_hecho, int indice_hecho, int id_predicado, int id_tipo_hecho)
{
    Table1->TableName = "Hecho.db";
    Table1->Open();
    Table1->Insert();
    Table1->FieldByName("ID_Hecho")->AsInteger      = id_hecho;
    Table1->FieldByName("Indice_Hecho")->AsInteger  = indice_hecho;
    Table1->FieldByName("ID_Predicado")->AsInteger  = id_predicado;
    Table1->FieldByName("ID_Tipo_Hecho")->AsInteger = id_tipo_hecho;
    Table1->Post();
    Table1->Close();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void insertaArgumentoHecho(int id_argumento_hecho,        |
 |                                            int id_objeto, int id_hecho,   |
 |                                            int orden_argumento_hecho)     |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : Los valores para todos los campos de un registro de la    |
 |                 Tabla <Argumento_Hecho.db>.                               |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método en el cual se inserta una tupla en la tabla        |
 |                 <Argumento_Hecho.db>.                                     |
\*---------------------------------------------------------------------------*/
void TForm4::insertaArgumentoHecho(int id_argumento_hecho, int id_objeto, int id_hecho, int orden_argumento_hecho)
{
    Table1->TableName = "Argumento_Hecho.db";
    Table1->Open();
    Table1->Insert();
    Table1->FieldByName("ID_Argumento_Hecho")->AsInteger    = id_argumento_hecho;
    Table1->FieldByName("ID_Objeto")->AsInteger             = id_objeto;
    Table1->FieldByName("ID_Hecho")->AsInteger              = id_hecho;
    Table1->FieldByName("Orden_Argumento_Hecho")->AsInteger = orden_argumento_hecho;
    Table1->Post();
    Table1->Close();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void insertaRegla(int id_regla, int id_tipo_regla)        |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : Los valores para todos los campos de un registro de la    |
 |                 Tabla <Regla.db>.                                         |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método en el cual se inserta una tupla en la tabla        |
 |                 <Regla.db>.                                               |
\*---------------------------------------------------------------------------*/
void TForm4::insertaRegla(int id_regla, int id_tipo_regla)
{
    Table1->TableName = "Regla.db";
    Table1->Open();
    Table1->Insert();
    Table1->FieldByName("ID_Regla")->AsInteger      = id_regla;
    Table1->FieldByName("ID_Tipo_Regla")->AsInteger = id_tipo_regla;
    Table1->Post();
    Table1->Close();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void insertaOrdenHecho(int id_orden_hecho, int id_regla,  |
 |                                        int id_hecho, int orden_hecho)     |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : Los valores para todos los campos de un registro de la    |
 |                 Tabla <Orden_Hecho.db>.                                   |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método en el cual se inserta una tupla en la tabla        |
 |                 <Orden_Hecho.db>.                                         |
\*---------------------------------------------------------------------------*/
void TForm4::insertaOrdenHecho(int id_orden_hecho, int id_regla, int id_hecho, int orden_hecho)
{
    Table1->TableName = "Orden_Hecho.db";
    Table1->Open();
    Table1->Insert();
    Table1->FieldByName("ID_Orden_Hecho")->AsInteger  = id_orden_hecho;
    Table1->FieldByName("ID_Regla")->AsInteger        = id_regla;
    Table1->FieldByName("ID_Hecho")->AsInteger        = id_hecho;
    Table1->FieldByName("Orden_Hecho")->AsInteger     = orden_hecho;
    Table1->Post();
    Table1->Close();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void limpiaBaseDatos()                                    |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método donde se limpian las tablas que corresponden a la  |
 |                 Base de Hechos y a la Base de Conocimiento.               |
\*---------------------------------------------------------------------------*/
void TForm4::limpiaBaseDatos()
{
    String tabla[] = {"Argumento_Predicado.db", "Argumento_Hecho.db", "Orden_Hecho.db", "Regla.db", "Hecho.db", "Predicado.db", "Objeto.db"};

    for (int i = 0; i < 7; i++)
    {
      Table1->TableName = tabla[i];
      Table1->EmptyTable();
    }
}

void TForm4::buscaRegla(String predicado, int indice)
{
    String consulta;

    consulta = "Select * From Hecho Where ID_Predicado = (Select ID_Predicado From Predicado Where Nombre_Predicado = " +predicado+ ") And (ID_Tipo_Hecho = 2) And (Indice_Hecho = " +IntToStr(indice)+ ")";
    ejecuta(consulta);

    //int id_hecho = Query1->FieldByName("ID_Hecho")->AsInteger;
    //ShowMessage(id_hecho);
}
