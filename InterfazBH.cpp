/*---------------------------------------------------------------------------*\
 | Archivo       : InterfazBH.cpp                                            |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Descripción   : Esta es la clase que comunica el Motor de Inferencia con  |
 |                 la Base de Hechos generada en la etapa de interpretación. |
 | Usada por     : Motor.cpp.                                                |
\*---------------------------------------------------------------------------*/

#include <vcl.h>
#pragma hdrstop
#include "InterfazBH.h"
#pragma package(smart_init)

/*---------------------------------------------------------------------------*\
 | Nombre        : InterfazBH()                                              |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método constructor en el cual no se implementa nada.      |
\*---------------------------------------------------------------------------*/
InterfazBH::InterfazBH()
{
}

/*---------------------------------------------------------------------------*\
 | Nombre        : bool Verdad_hecho(String nombre_predicado,                |
 |                                   String nombre_argumento1,               |
 |                                   String nombre_argumento2)               |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El nombre del predicado, el nombre del argumento1 y del   |
 |                 argumento2 del hecho.                                     |
 | Salidas       : Si se encuentra el hecho especificado por los parámetros  |
 |                 del método, entonces se retorna <true>. En caso contrario,|
 |                 se retorna <false>.                                       |
 | Descripción   : Este método hace la consulta SQL necesaria para buscar el |
 |                 hecho que tenga el nombre del predicado ingresado, con    |
 |                 argumentos <nombre_argumento1> y <nombre_argumento2>.     |
 |                 Observación: El hecho puede no tener argumentos o bien    |
 |                 puede ser unitario o binario. Esto lo detectamos,         |
 |                 preguntando si los valores de los String                  |
 |                 <nombre_argumento1> y <nombre_argumento2> son NULL o no.  |
 | Validación    : Se asume que es predicado que se ingresa viene con la     |
 |                 cantidad de argumentos que tiene ese tipo de predicado.   |
 |                 Es decir, si el predicado es binario, entonces los dos    |
 |                 argumentos son distintos de NULL. Si es unitario,         |
 |                 entonces el primer argumento es distinto de NULL y el     |
 |                 segundo igual a NULL. Cuando el predicado es sin          |
 |                 argumentos, entonces los argumentos deben venir iguales a |
 |                 NULL.                                                     |
\*---------------------------------------------------------------------------*/
bool InterfazBH::Verdad_hecho(String nombre_predicado, String nombre_argumento1, String nombre_argumento2)
{
    String subconsulta1, subconsulta2, subconsulta3, subconsulta4;
    String subconsulta5, subconsulta6, consulta;
    int id_objeto1, id_objeto2, id_hecho;
    bool respuesta = false;

    // Convertimos los String a minúsculas.
    nombre_predicado  = LowerCase(nombre_predicado);
    nombre_argumento1 = LowerCase(nombre_argumento1);
    nombre_argumento2 = LowerCase(nombre_argumento2);

    // Puede ser un hecho unitario o binario.
    if (nombre_argumento1 != NULL)
    {
      consulta   = "Select ID_Objeto From Objeto Where Nombre_Objeto = '" +nombre_argumento1+ "'";
      id_objeto1 = Form4->obtieneInteger(consulta, "ID_Objeto");

      // Se encontró el objeto1.
      if (id_objeto1 > 0)
      {
        subconsulta1 = "Select ID_Predicado From Predicado Where Nombre_Predicado = '" +nombre_predicado+ "'";
        subconsulta2 = "Select ID_Hecho From Hecho Where ID_Predicado = (" +subconsulta1+ ") And ID_Tipo_Hecho = 1";
        consulta     = "Select ID_Hecho From Argumento_Hecho Where ID_Hecho In (" +subconsulta2+ ") And ID_Objeto = " +IntToStr(id_objeto1)+ " And Orden_Argumento_Hecho = 1";
        id_hecho     = Form4->obtieneInteger(consulta, "ID_Hecho");

        // Si el primer argumento está en la tabla Argumento_Hecho,
        // entonces se continúa con el segundo argumento.
        if (id_hecho > 0)
        {
          // Es un hecho binario.
          if (nombre_argumento2 != NULL)
          {
            consulta   = "Select ID_Objeto From Objeto Where Nombre_Objeto = '" +nombre_argumento2+ "'";
            id_objeto2 = Form4->obtieneInteger(consulta, "ID_Objeto");

            // Se encontró el objeto2.
            if (id_objeto2 > 0)
            {
              subconsulta1 = "Select ID_Predicado From Predicado Where Nombre_Predicado = '" +nombre_predicado+ "'";
              subconsulta2 = "Select ID_Hecho From Hecho Where ID_Predicado = (" +subconsulta1+ ") And ID_Tipo_Hecho = 1";
              subconsulta3 = "Select ID_Hecho From Argumento_Hecho Where ID_Objeto = " +IntToStr(id_objeto1)+ " And ID_Hecho In (" +subconsulta2+ ") And Orden_Argumento_Hecho = 1";

              subconsulta4 = "Select ID_Predicado From Predicado Where Nombre_Predicado = '" +nombre_predicado+ "'";
              subconsulta5 = "Select ID_Hecho From Hecho Where ID_Predicado = (" +subconsulta4+ ") And ID_Tipo_Hecho = 1";
              subconsulta6 = "Select ID_Hecho From Argumento_Hecho Where ID_Objeto = " +IntToStr(id_objeto2)+ " And ID_Hecho In (" +subconsulta5+ ") And Orden_Argumento_Hecho = 2";

              consulta     = "Select ID_Hecho From Hecho Where ID_Hecho In (" +subconsulta3+ ") And ID_Hecho In (" +subconsulta6+ ")";

              id_hecho = Form4->obtieneInteger(consulta, "ID_Hecho");

              // Si el segundo argumento se encontró en la tabla Argumento_hecho,
              // entonces si se encontró el hecho binario solicitado.
              if (id_hecho > 0)
                respuesta = true;

              // Cuando el segundo argumento no está en la tabla Argumento_hecho.
              else respuesta = false;
            }
            else respuesta = false;
          }
          // Para un hecho unitario, donde el argumento1 ya ha sido encontrado.
          else respuesta = true;
        }
        else respuesta = false;
      }
      // Cuando no se encontró, entonces no existe en la tabla Argumento_Hecho.
      else respuesta = false;
    }
    else respuesta = Hecho_asociado(nombre_predicado);

    return (respuesta);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : bool Hecho_asociado(String nombre_predicado)              |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El nombre del predicado.                                  |
 | Salidas       : Si se encuentra un hecho que use el predicado especificado|
 |                 entonces se retorna <true>. En caso contrario, se retorna |
 |                 <false>.                                                  |
 | Descripción   : Este método hace la consulta SQL necesaria para buscar un |
 |                 hecho que tenga el nombre del predicado ingresado.        |
\*---------------------------------------------------------------------------*/
bool InterfazBH::Hecho_asociado(String nombre_predicado)
{
    String subconsulta1, consulta;
    bool respuesta = false;

    // Convertimos los String a minúsculas.
    nombre_predicado = LowerCase(nombre_predicado);

    subconsulta1 = "Select ID_Predicado From Predicado Where Nombre_Predicado = '" +nombre_predicado+ "'";
    consulta     = "Select Count(*) As Total From Hecho Where ID_Predicado = (" +subconsulta1+ ") And ID_Tipo_Hecho = 1";

    // Si se encontraron.
    if (Form4->obtieneInteger(consulta, "Total") > 0)
      respuesta = true;

    return (respuesta);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : Predicado * Iniciar_variable_hecho_unario(String predicado|
 |                                                           , int indice)   |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El nombre del predicado y el indice del hecho.            |
 | Salidas       : Retorna un puntero a predicado que corresponde al hecho   |
 |                 que usa el predicado <predicado> y que tiene indice       |
 |                 <indice>. Si no es encontrado, entonces se retorna NULL.  |
 | Descripción   : En este método se busca el hecho que usa <predicado> y    |
 |                 que tiene <indice>. Esto se realiza mediante una consulta |
 |                 SQL. Si no se encuentra este hecho, entonces se devuelve  |
 |                 NULL.                                                     |
 | Validación    : Se asume que el hecho que se ingresa como argumento es    |
 |                 unitario.                                                 |
\*---------------------------------------------------------------------------*/
Predicado * InterfazBH::Iniciar_variable_hecho_unario(String nombre_predicado, int indice_hecho)
{
    Predicado * hecho;
    Cadena nombre;
    Objeto argumento;

    String nombre_objeto, subconsulta1, subconsulta2, subconsulta3, consulta;
    int id_tipo_objeto;

    // Convertimos los String a minúsculas.
    nombre_predicado = LowerCase(nombre_predicado);

    subconsulta1 = "Select ID_Predicado From Predicado Where Nombre_Predicado = '" +nombre_predicado+ "' And ID_Tipo_Predicado = 1";
    subconsulta2 = "Select ID_Hecho From Hecho Where ID_Predicado = (" +subconsulta1+ ") And Indice_Hecho = "+ IntToStr(indice_hecho) +" And ID_Tipo_Hecho = 1";
    subconsulta3 = "Select ID_Objeto From Argumento_Hecho Where ID_Hecho = (" +subconsulta2+ ")";
    consulta     = "Select Nombre_Objeto, ID_Tipo_Objeto From Objeto Where ID_Objeto In (" +subconsulta3+ ")";
    Form4->ejecuta(consulta);

    nombre_objeto  = Form4->Query1->FieldByName("Nombre_Objeto")->AsString;
    id_tipo_objeto = Form4->Query1->FieldByName("ID_Tipo_Objeto")->AsInteger;

    // Si fue encontrado.
    if (id_tipo_objeto != 0)
    {
      nombre = Cadena();
      nombre.ingresa(nombre_predicado);

      argumento = Objeto();
      argumento.ingresa(nombre_objeto);

      if (id_tipo_objeto == 2)
        argumento.cambiaPrimerCaracter();

      hecho = new Predicado();
      hecho->ingresaNombre(nombre);
      hecho->ingresaArgumento1(argumento);

    }
    // Cuando no fue encontrado.
    else hecho = NULL;

    return (hecho);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : Predicado * Iniciar_variable_en_hecho(                    |
 |                 String nombre_predicado, String nombre_argumento1,        |
 |                 String nombre_argumento2, int indice)                     |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El nombre del predicado, el nombre del argumento1, el     |
 |                 nombre del argumento2 y el indice del hecho.              |
 | Salidas       : Retorna un puntero a predicado que corresponde al hecho   |
 |                 que usa el predicado <predicado> , con argumentos         |
 |                 <nombre_argumento1> y <nombre_argumento2> y que además    |
 |                 tiene indice <indice>. Si no es encontrado, entonces se   |
 |                 retorna NULL.                                             |
 | Descripción   : En este método se busca el hecho que usa <predicado> y    |
 |                 que tiene <indice>. Esto se realiza mediante una consulta |
 |                 SQL. Si no se encuentra este hecho, entonces se devuelve  |
 |                 NULL.                                                     |
 | Validación    : Se asume que el predicado que se está ingresando es       |
 |                 binario.                                                  |
\*---------------------------------------------------------------------------*/
Predicado * InterfazBH::Iniciar_variable_en_hecho(String nombre_predicado, String nombre_argumento1, String nombre_argumento2, int indice)
{
    Predicado * hecho;
    Cadena nombre;
    Objeto argumento1, argumento2;
    String subconsulta1, subconsulta2, subconsulta3, subconsulta4;
    String subconsulta5, subconsulta6, subconsulta7, subconsulta8, consulta;
    String nombre_objeto1, nombre_objeto2;
    int id_hecho, id_tipo_objeto1, id_tipo_objeto2;
    bool fin = false;

    // Convertimos los String a minúsculas.
    nombre_predicado  = LowerCase(nombre_predicado);
    nombre_argumento1 = LowerCase(nombre_argumento1);
    nombre_argumento2 = LowerCase(nombre_argumento2);

    if (nombre_argumento1 != NULL)
    {
      // Caso de que el hecho tenga como primer argumento un atomo y como
      // segundo argumento un atomo. Ejemplo: gusta(patricio, soccer).
      if (nombre_argumento2 != NULL)
      {
        subconsulta1 = "Select ID_Predicado From Predicado Where Nombre_Predicado = '" +nombre_predicado+ "'";
        subconsulta2 = "Select ID_Objeto From Objeto Where Nombre_Objeto = '" +nombre_argumento1+ "'";
        subconsulta3 = "Select ID_Hecho From Hecho Where ID_Predicado = (" +subconsulta1+ ") And ID_Tipo_Hecho = 1";
        subconsulta4 = "Select ID_Hecho From Argumento_Hecho Where ID_Objeto = (" +subconsulta2+ ") And ID_Hecho In (" +subconsulta3+ ") And Orden_Argumento_Hecho = 1";
        subconsulta5 = "Select ID_Predicado From Predicado Where Nombre_Predicado = '" +nombre_predicado+ "'";
        subconsulta6 = "Select ID_Objeto From Objeto Where Nombre_Objeto = '" +nombre_argumento2+ "'";
        subconsulta7 = "Select ID_Hecho From Hecho Where ID_Predicado = (" +subconsulta5+ ") And ID_Tipo_Hecho = 1";
        subconsulta8 = "Select ID_Hecho From Argumento_Hecho Where ID_Objeto = (" +subconsulta6+ ") And ID_Hecho In (" +subconsulta7+ ") And Orden_Argumento_Hecho = 2";
        consulta     = "Select ID_Hecho From Hecho Where ID_Hecho In (" +subconsulta4+ ") And ID_Hecho In (" +subconsulta8+ ")";

        id_hecho = Form4->obtieneInteger(consulta, "ID_Hecho");

        // Si existe el hecho.
        if (id_hecho > 0)
        {
          // Iteramos "indice-veces" en los resultados.
          for (int i = 0; i < indice - 1; i++)
          {
            Form4->Query1->Next();

            if (Form4->Query1->Eof)
            {
              fin = true;
              break;
            }
          }

          // Si existe el hecho con el indice ingresado.
          if (!fin)
          {
            id_hecho = Form4->Query1->FieldByName("ID_Hecho")->AsInteger;

            subconsulta1 = "Select ID_Objeto From Argumento_Hecho Where ID_Hecho = " +IntToStr(id_hecho)+ " And Orden_Argumento_Hecho = 1";
            consulta     = "Select Nombre_Objeto, ID_Tipo_Objeto From Objeto Where ID_Objeto = (" +subconsulta1+ ")";

            Form4->ejecuta(consulta);
            nombre_objeto1  = Form4->Query1->FieldByName("Nombre_Objeto")->AsString;
            id_tipo_objeto1 = Form4->Query1->FieldByName("ID_Tipo_Objeto")->AsInteger;

            subconsulta1 = "Select ID_Objeto From Argumento_Hecho Where ID_Hecho = " +IntToStr(id_hecho)+ " And Orden_Argumento_Hecho = 2";
            consulta     = "Select Nombre_Objeto, ID_Tipo_Objeto From Objeto Where ID_Objeto = (" +subconsulta1+ ")";

            Form4->ejecuta(consulta);
            nombre_objeto2  = Form4->Query1->FieldByName("Nombre_Objeto")->AsString;
            id_tipo_objeto2 = Form4->Query1->FieldByName("ID_Tipo_Objeto")->AsInteger;

            nombre = Cadena();
            nombre.ingresa(nombre_predicado);

            argumento1 = Objeto();
            argumento1.ingresa(nombre_objeto1);

            if (id_tipo_objeto1 == 2)
              argumento1.cambiaPrimerCaracter();

            argumento2 = Objeto();
            argumento2.ingresa(nombre_objeto2);

            if (id_tipo_objeto2 == 2)
              argumento2.cambiaPrimerCaracter();

            hecho = new Predicado();
            hecho->ingresaNombre(nombre);
            hecho->ingresaArgumento1(argumento1);
            hecho->ingresaArgumento2(argumento2);
          }

          // No existe el hecho con el indice ingresado.
          else hecho = NULL;
        }

        // No existe el hecho.
        else hecho = NULL;
      }

      // Caso de que el hecho tenga como primer argumento un atomo y como
      // segundo argumento una variable. Ejemplo: gusta(patricio, X).
      else
      {
        subconsulta1 = "Select ID_Predicado From Predicado Where Nombre_Predicado = '" +nombre_predicado+ "'";
        subconsulta2 = "Select ID_Objeto From Objeto Where Nombre_Objeto = '" +nombre_argumento1+ "'";
        subconsulta3 = "Select ID_Hecho From Hecho Where ID_Predicado = (" +subconsulta1+ ") And ID_Tipo_Hecho = 1";
        consulta     = "Select ID_Hecho From Argumento_Hecho Where ID_Objeto = (" +subconsulta2+ ") And ID_Hecho In (" +subconsulta3+ ") And Orden_Argumento_Hecho = 1";

        id_hecho = Form4->obtieneInteger(consulta, "ID_Hecho");

        // Si existe el hecho.
        if (id_hecho > 0)
        {
          // Iteramos "indice-veces" en los resultados.
          for (int i = 0; i < indice - 1; i++)
          {
            Form4->Query1->Next();

            if (Form4->Query1->Eof)
            {
              fin = true;
              break;
            }
          }

          // Si existe el hecho con el indice ingresado.
          if (!fin)
          {
            id_hecho = Form4->Query1->FieldByName("ID_Hecho")->AsInteger;

            subconsulta1 = "Select ID_Objeto From Argumento_Hecho Where ID_Hecho = " +IntToStr(id_hecho)+ " And Orden_Argumento_Hecho = 2";
            consulta     = "Select Nombre_Objeto, ID_Tipo_Objeto From Objeto Where ID_Objeto = (" +subconsulta1+ ")";

            Form4->ejecuta(consulta);
            nombre_objeto2  = Form4->Query1->FieldByName("Nombre_Objeto")->AsString;
            id_tipo_objeto2 = Form4->Query1->FieldByName("ID_Tipo_Objeto")->AsInteger;

            nombre = Cadena();
            nombre.ingresa(nombre_predicado);

            argumento1 = Objeto();
            argumento1.ingresa(nombre_argumento1);

            argumento2 = Objeto();
            argumento2.ingresa(nombre_objeto2);

            if (id_tipo_objeto2 == 2)
              argumento2.cambiaPrimerCaracter();

            hecho = new Predicado();
            hecho->ingresaNombre(nombre);
            hecho->ingresaArgumento1(argumento1);
            hecho->ingresaArgumento2(argumento2);
          }

          // No existe el hecho con el indice ingresado.
          else hecho = NULL;
        }

        // No existe el hecho.
        else hecho = NULL;
      }
    }
    else
    {
      // Caso de que el hecho tenga como primer argumento una variable y como
      // segundo argumento un atomo. Ejemplo: gusta(X, soccer).
      if (nombre_argumento2 != NULL)
      {
        subconsulta1 = "Select ID_Predicado From Predicado Where Nombre_Predicado = '" +nombre_predicado+ "'";
        subconsulta2 = "Select ID_Objeto From Objeto Where Nombre_Objeto = '" +nombre_argumento2+ "'";
        subconsulta3 = "Select ID_Hecho From Hecho Where ID_Predicado = (" +subconsulta1+ ") And ID_Tipo_Hecho = 1";
        consulta     = "Select ID_Hecho From Argumento_Hecho Where ID_Objeto = (" +subconsulta2+ ") And ID_Hecho In (" +subconsulta3+ ") And Orden_Argumento_Hecho = 2";

        id_hecho = Form4->obtieneInteger(consulta, "ID_Hecho");

        // Si existe el hecho.
        if (id_hecho > 0)
        {
          // Iteramos "indice-veces" en los resultados.
          for (int i = 0; i < indice - 1; i++)
          {
            Form4->Query1->Next();

            if (Form4->Query1->Eof)
            {
              fin = true;
              break;
            }
          }

          // Si existe el hecho con el indice ingresado.
          if (!fin)
          {
            id_hecho = Form4->Query1->FieldByName("ID_Hecho")->AsInteger;

            subconsulta1 = "Select ID_Objeto From Argumento_Hecho Where ID_Hecho = " +IntToStr(id_hecho)+ " And Orden_Argumento_Hecho = 1";
            consulta     = "Select Nombre_Objeto, ID_Tipo_Objeto From Objeto Where ID_Objeto = (" +subconsulta1+ ")";

            Form4->ejecuta(consulta);
            nombre_objeto1  = Form4->Query1->FieldByName("Nombre_Objeto")->AsString;
            id_tipo_objeto1 = Form4->Query1->FieldByName("ID_Tipo_Objeto")->AsInteger;

            nombre = Cadena();
            nombre.ingresa(nombre_predicado);

            argumento1 = Objeto();
            argumento1.ingresa(nombre_objeto1);

            if (id_tipo_objeto1 == 2)
              argumento1.cambiaPrimerCaracter();

            argumento2 = Objeto();
            argumento2.ingresa(nombre_argumento2);

            hecho = new Predicado();
            hecho->ingresaNombre(nombre);
            hecho->ingresaArgumento1(argumento1);
            hecho->ingresaArgumento2(argumento2);
          }

          // No existe el hecho con el indice ingresado.
          else hecho = NULL;
        }

        // No existe el hecho.
        else hecho = NULL;
      }

      // Caso de que el hecho tenga como primer argumento una variable y como
      // segundo argumento una variable. Ejemplo: gusta(X, Y).
      else
      {
        subconsulta1 = "Select ID_Predicado From Predicado Where Nombre_Predicado = '" +nombre_predicado+ "' And ID_Tipo_Predicado = 2";
        subconsulta2 = "Select ID_Hecho From Hecho Where ID_Predicado = (" +subconsulta1+ ") And Indice_Hecho = "+ IntToStr(indice) +" And ID_Tipo_Hecho = 1";
        subconsulta3 = "Select ID_Objeto From Argumento_Hecho Where ID_Hecho = (" +subconsulta2+ ") And Orden_Argumento_Hecho = 1";
        consulta     = "Select Nombre_Objeto, ID_Tipo_Objeto From Objeto Where ID_Objeto = (" +subconsulta3+ ")";
        Form4->ejecuta(consulta);

        nombre_objeto1  = Form4->Query1->FieldByName("Nombre_Objeto")->AsString;
        id_tipo_objeto1 = Form4->Query1->FieldByName("ID_Tipo_Objeto")->AsInteger;

        subconsulta1 = "Select ID_Predicado From Predicado Where Nombre_Predicado = '" +nombre_predicado+ "' And ID_Tipo_Predicado = 2";
        subconsulta2 = "Select ID_Hecho From Hecho Where ID_Predicado = (" +subconsulta1+ ") And Indice_Hecho = "+ IntToStr(indice) +" And ID_Tipo_Hecho = 1";
        subconsulta3 = "Select ID_Objeto From Argumento_Hecho Where ID_Hecho = (" +subconsulta2+ ") And Orden_Argumento_Hecho = 2";
        consulta     = "Select Nombre_Objeto, ID_Tipo_Objeto From Objeto Where ID_Objeto = (" +subconsulta3+ ")";
        Form4->ejecuta(consulta);

        nombre_objeto2  = Form4->Query1->FieldByName("Nombre_Objeto")->AsString;
        id_tipo_objeto2 = Form4->Query1->FieldByName("ID_Tipo_Objeto")->AsInteger;

        // Si fue encontrado.
        if ((id_tipo_objeto1 != 0) && (id_tipo_objeto2 != 0))
        {
          nombre = Cadena();
          nombre.ingresa(nombre_predicado);

          argumento1 = Objeto();
          argumento1.ingresa(nombre_objeto1);

          if (id_tipo_objeto1 == 2)
            argumento1.cambiaPrimerCaracter();

          argumento2 = Objeto();
          argumento2.ingresa(nombre_objeto2);

          if (id_tipo_objeto2 == 2)
            argumento2.cambiaPrimerCaracter();

          hecho = new Predicado();
          hecho->ingresaNombre(nombre);
          hecho->ingresaArgumento1(argumento1);
          hecho->ingresaArgumento2(argumento2);
        }
        // Cuando no fue encontrado.
        else hecho = NULL;
      }
    }

    return (hecho);
}
