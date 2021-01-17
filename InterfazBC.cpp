/*---------------------------------------------------------------------------*\
 | Archivo       : InterfazBC.cpp                                            |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Descripción   : Esta es la clase que comunica el Motor de Inferencia con  |
 |                 la Base de Concocimientos generada en la etapa de         |
 |                 interpretación.                                           |
 | Usada por     : Motor.cpp.                                                |
\*---------------------------------------------------------------------------*/

#include <vcl.h>
#pragma hdrstop
#include "InterfazBC.h"
#pragma package(smart_init)

/*---------------------------------------------------------------------------*\
 | Nombre        : InterfazBC()                                              |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método constructor en el cual no se implementa nada.      |
\*---------------------------------------------------------------------------*/
InterfazBC::InterfazBC()
{
}

/*---------------------------------------------------------------------------*\
 | Nombre        : bool Existe_regla(String nombre_predicado)                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El nombre del predicado consecuente en la regla.          |
 | Salidas       : Si se encuentra una regla que use el predicado consecuente|
 |                 especificado, entonces se retorna <true>. En caso         |
 |                 contrario, se retorna <false>.                            |
 | Descripción   : Este método hace la consulta SQL necesaria para buscar una|
 |                 regla que tenga el nombre del predicado consecuente       |
 |                 ingresado.                                                |
\*---------------------------------------------------------------------------*/
bool InterfazBC::Existe_regla(String nombre_predicado)
{
    String subconsulta1, consulta;
    bool respuesta = false;

    // Convertimos los String a minúsculas.
    nombre_predicado = LowerCase(nombre_predicado);

    subconsulta1 = "Select ID_Predicado From Predicado Where Nombre_Predicado = '" +nombre_predicado+ "'";
    consulta     = "Select Count(*) As Total From Hecho Where ID_Predicado = (" +subconsulta1+ ") And ID_Tipo_Hecho = 2";

    // Si se encontraron.
    if (Form4->obtieneInteger(consulta, "Total") > 0)
      respuesta = true;

    return (respuesta);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : Regla * Entregar_regla(String nombre_predicado,           |
 |                                        int indice_regla)                  |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El nombre del predicado consecuente en la regla y el      |
 |                 indice de la regla.                                       |
 | Salidas       : Si se encuentra una regla que use el predicado consecuente|
 |                 especificado, y que tenga el indice especificado, entonces|
 |                 se retorna <true>. En caso contrario, se retorna <false>. |
 | Descripción   : Este método hace la consulta SQL necesaria para buscar una|
 |                 regla que tenga el nombre del predicado consecuente       |
 |                 ingresado y con indice indicado.                          |
\*---------------------------------------------------------------------------*/
Regla * InterfazBC::Entregar_regla(String nombre_predicado, int indice_regla)
{
    Regla * regla;
    Cadena nombre;
    Objeto argumento1, argumento2;
    Predicado consecuente, antecedente1, antecedente2;
    String subconsulta1, subconsulta2, subconsulta3, consulta;
    int id_regla, id_tipo_regla, id_predicado, id_tipo_predicado, id_hecho, contador;

    // Convertimos los String a minúsculas.
    nombre_predicado = LowerCase(nombre_predicado);

    subconsulta1 = "Select ID_Predicado From Predicado Where Nombre_Predicado = '" +nombre_predicado+ "'";
    subconsulta2 = "Select ID_Hecho From Hecho Where ID_Predicado = (" +subconsulta1+ ") And Indice_Hecho = " +IntToStr(indice_regla)+ " And ID_Tipo_Hecho = 2";
    subconsulta3 = "Select ID_Regla From Orden_Hecho Where ID_Hecho = (" +subconsulta2+ ") And Orden_Hecho = 1";
    consulta     = "Select ID_Regla, ID_Tipo_Regla From Regla Where ID_Regla = (" +subconsulta3+ ")";
    Form4->ejecuta(consulta);

    id_regla      = Form4->Query1->FieldByName("ID_Regla")->AsInteger;
    id_tipo_regla = Form4->Query1->FieldByName("ID_Tipo_Regla")->AsInteger;

    // Fue encontrada la regla.
    if (id_regla > 0)
    {
      // Creamos la regla.
      regla = new Regla();

      // Este será el nombre de predicado que usa el hecho consecuente.
      nombre = Cadena();
      nombre.ingresa(nombre_predicado);

      // Creamos e ingresamos el nombre del hecho consecuente.
      consecuente = Predicado();
      consecuente.ingresaNombre(nombre);

      // Veamos el número de argumentos que tiene el hecho consecuente.
      consulta = "Select ID_Predicado, ID_Tipo_Predicado From Predicado Where Nombre_Predicado = '" +nombre_predicado+ "'";
      Form4->ejecuta(consulta);
      id_predicado      = Form4->Query1->FieldByName("ID_Predicado")->AsInteger;
      id_tipo_predicado = Form4->Query1->FieldByName("ID_Tipo_Predicado")->AsInteger;

      // El hecho consecuente puede ser unitario o binario.
      if (id_tipo_predicado > 0)
      {
        subconsulta1 = "Select ID_Hecho From Hecho Where ID_Predicado = " +IntToStr(id_predicado)+ " And Indice_Hecho = " +IntToStr(indice_regla)+ " And ID_Tipo_Hecho = 2";
        subconsulta2 = "Select ID_Objeto From Argumento_Hecho Where ID_Hecho = (" +subconsulta1+ ") And Orden_Argumento_Hecho = 1";
        consulta     = "Select Nombre_Objeto, ID_Tipo_Objeto From Objeto Where ID_Objeto = (" +subconsulta2+ ")";
        Form4->ejecuta(consulta);

        // Creamos e ingresamos el argumento1.
        argumento1 = Objeto();
        argumento1.ingresa(Form4->Query1->FieldByName("Nombre_Objeto")->AsString);

        // Si el argumento1 es una variable.
        if (Form4->Query1->FieldByName("ID_Tipo_Objeto")->AsInteger == 2)
          argumento1.cambiaPrimerCaracter();

        // Ingresamos el argumento1 al consecuente.
        consecuente.ingresaArgumento1(argumento1);

        // Si el hecho consecuente es binario.
        if (id_tipo_predicado == 2)
        {
          subconsulta1 = "Select ID_Hecho From Hecho Where ID_Predicado = " +IntToStr(id_predicado)+ " And Indice_Hecho = " +IntToStr(indice_regla)+ " And ID_Tipo_Hecho = 2";
          subconsulta2 = "Select ID_Objeto From Argumento_Hecho Where ID_Hecho = (" +subconsulta1+ ") And Orden_Argumento_Hecho = 2";
          consulta     = "Select Nombre_Objeto, ID_Tipo_Objeto From Objeto Where ID_Objeto = (" +subconsulta2+ ")";
          Form4->ejecuta(consulta);

          // Creamos e ingresamos el argumento2.
          argumento2 = Objeto();
          argumento2.ingresa(Form4->Query1->FieldByName("Nombre_Objeto")->AsString);

          // Si el argumento2 es una variable.
          if (Form4->Query1->FieldByName("ID_Tipo_Objeto")->AsInteger == 2)
            argumento2.cambiaPrimerCaracter();

          // Ingresamos el argumento2 al consecuente.
          consecuente.ingresaArgumento2(argumento2);
        }
      }// Fin hecho consecuente.

      // Ingresamos el hecho consecuente a la regla.
      regla->ingresaConsecuente(consecuente);

      // Regla con uno o dos hechos en el cuerpo.
      if (id_tipo_regla >= 1)
      {
        consulta = "Select ID_Hecho From Orden_Hecho Where ID_Regla = " +IntToStr(id_regla)+ " And Orden_Hecho = 2";
        id_hecho = Form4->obtieneInteger(consulta, "ID_hecho");

        subconsulta1 = "Select ID_Predicado From Hecho Where ID_Hecho = " +IntToStr(id_hecho)+ "";
        consulta     = "Select Nombre_Predicado, ID_Tipo_Predicado From Predicado Where ID_Predicado = (" +subconsulta1+ ")";
        Form4->ejecuta(consulta);

        // Este será el nombre de predicado que usa el hecho antecedente1.
        nombre = Cadena();
        nombre.ingresa(Form4->Query1->FieldByName("Nombre_Predicado")->AsString);

        // Creamos e ingresamos el nombre del hecho antecedente1.
        antecedente1 = Predicado();
        antecedente1.ingresaNombre(nombre);

        id_tipo_predicado = Form4->Query1->FieldByName("ID_Tipo_Predicado")->AsInteger;

        // El hecho antecedente1 puede ser unitario o binario.
        if (id_tipo_predicado >= 1)
        {
          subconsulta1 = "Select ID_Objeto From Argumento_Hecho Where ID_Hecho = " +IntToStr(id_hecho)+ " And Orden_Argumento_Hecho = 1";
          consulta     = "Select Nombre_Objeto, ID_Tipo_Objeto From Objeto Where ID_Objeto = (" +subconsulta1+ ")";
          Form4->ejecuta(consulta);

          // Creamos e ingresamos el argumento1.
          argumento1 = Objeto();
          argumento1.ingresa(Form4->Query1->FieldByName("Nombre_Objeto")->AsString);

          // Si el argumento1 es una variable.
          if (Form4->Query1->FieldByName("ID_Tipo_Objeto")->AsInteger == 2)
            argumento1.cambiaPrimerCaracter();

          // Ingresamos el argumento1 al antecedente1.
          antecedente1.ingresaArgumento1(argumento1);

          // Si el hecho antecedente1 es binario.
          if (id_tipo_predicado == 2)
          {
            subconsulta1 = "Select ID_Objeto From Argumento_Hecho Where ID_Hecho = " +IntToStr(id_hecho)+ " And Orden_Argumento_Hecho = 2";
            consulta     = "Select Nombre_Objeto, ID_Tipo_Objeto From Objeto Where ID_Objeto = (" +subconsulta1+ ")";
            Form4->ejecuta(consulta);

            // Creamos e ingresamos el argumento2.
            argumento2 = Objeto();
            argumento2.ingresa(Form4->Query1->FieldByName("Nombre_Objeto")->AsString);

            // Si el argumento2 es una variable.
            if (Form4->Query1->FieldByName("ID_Tipo_Objeto")->AsInteger == 2)
              argumento2.cambiaPrimerCaracter();

            // Ingresamos el argumento2 al antecedente1.
            antecedente1.ingresaArgumento2(argumento2);
          }
        }// Fin antecedente1.

        // Ingresamos el hecho antecedente1 a la regla.
        regla->ingresaAntecedente1(antecedente1);

        // Si la regla tiene dos hechos en el cuerpo.
        if (id_tipo_regla == 2)
        {
          consulta = "Select ID_Hecho From Orden_Hecho Where ID_Regla = " +IntToStr(id_regla)+ " And Orden_Hecho = 3";
          id_hecho = Form4->obtieneInteger(consulta, "ID_hecho");

          subconsulta1 = "Select ID_Predicado From Hecho Where ID_Hecho = " +IntToStr(id_hecho)+ "";
          consulta     = "Select Nombre_Predicado, ID_Tipo_Predicado From Predicado Where ID_Predicado = (" +subconsulta1+ ")";
          Form4->ejecuta(consulta);

          // Este será el nombre de predicado que usa el hecho antecedente2.
          nombre = Cadena();
          nombre.ingresa(Form4->Query1->FieldByName("Nombre_Predicado")->AsString);

          // Creamos e ingresamos el nombre del hecho antecedente2.
          antecedente2 = Predicado();
          antecedente2.ingresaNombre(nombre);

          id_tipo_predicado = Form4->Query1->FieldByName("ID_Tipo_Predicado")->AsInteger;

          // El hecho antecedente2 puede ser unitario o binario.
          if (id_tipo_predicado >= 1)
          {
            subconsulta1 = "Select ID_Objeto From Argumento_Hecho Where ID_Hecho = " +IntToStr(id_hecho)+ " And Orden_Argumento_Hecho = 1";
            consulta     = "Select Nombre_Objeto, ID_Tipo_Objeto From Objeto Where ID_Objeto = (" +subconsulta1+ ")";
            Form4->ejecuta(consulta);

            // Creamos e ingresamos el argumento1.
            argumento1 = Objeto();
            argumento1.ingresa(Form4->Query1->FieldByName("Nombre_Objeto")->AsString);

            // Si el argumento1 es una variable.
            if (Form4->Query1->FieldByName("ID_Tipo_Objeto")->AsInteger == 2)
              argumento1.cambiaPrimerCaracter();

            // Ingresamos el argumento1 al antecedente2.
            antecedente2.ingresaArgumento1(argumento1);

            // Si el hecho antecedente2 es binario.
            if (id_tipo_predicado == 2)
            {
              subconsulta1 = "Select ID_Objeto From Argumento_Hecho Where ID_Hecho = " +IntToStr(id_hecho)+ " And Orden_Argumento_Hecho = 2";
              consulta     = "Select Nombre_Objeto, ID_Tipo_Objeto From Objeto Where ID_Objeto = (" +subconsulta1+ ")";
              Form4->ejecuta(consulta);

              // Creamos e ingresamos el argumento2.
              argumento2 = Objeto();
              argumento2.ingresa(Form4->Query1->FieldByName("Nombre_Objeto")->AsString);

              // Si el argumento2 es una variable.
              if (Form4->Query1->FieldByName("ID_Tipo_Objeto")->AsInteger == 2)
                argumento2.cambiaPrimerCaracter();

              // Ingresamos el argumento2 al antecedente1.
              antecedente2.ingresaArgumento2(argumento2);
            }
          }// Fin antecedente2.

          // Ingresamos el hecho antecedente2 a la regla.
          regla->ingresaAntecedente2(antecedente2);
        }
      }

      // Seteamos el conflicto de la regla.
      subconsulta1 = "Select ID_Predicado From Predicado Where Nombre_Predicado = '" +nombre_predicado+ "'";
      consulta     = "Select Count(*) As Total From Hecho Where ID_Predicado = (" +subconsulta1+ ") And ID_Tipo_Hecho = 2";
      contador     = Form4->obtieneInteger(consulta, "Total");

      // Si se encontraron conflictos.
      if (contador > 1)
        regla->ingresaConflicto(contador);

        
    }

    // No fue encontrada la regla.
    else regla = NULL;

    return (regla);
}
