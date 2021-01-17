/*---------------------------------------------------------------------------*\
 | Archivo       : Consulta.cpp                                              |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Descripción   : Este es el interprete de comandos para la consulta que    |
 |                 el usuario ingresa al Prolog, el cual utiliza un AFD      |
 |                 (Autómata Finito Determinista) para reconocer la sintaxis |
 |                 del lenguaje Prolog y las instrucciones SQL para verificar|
 |                 otros tipos de errores.                                   |
 | Usado por     : Meta.cpp.                                                 |
\*---------------------------------------------------------------------------*/

#include <vcl.h>
#pragma hdrstop
#include "Consulta.h"
#include "SQL.h"
#pragma package(smart_init)

/*---------------------------------------------------------------------------*\
 | Nombre        : Consulta()                                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método constructor en el cual se inicializan los valores  |
 |                 de las variables que serán usadas más adelante en por la  |
 |                 clase Consulta.                                           |
\*---------------------------------------------------------------------------*/
Consulta::Consulta()
{
    estado     = 1;
    tipo_error = 0;
    num_hechos = 0;
    cadena     = Cadena();
    objeto     = Objeto();
    hecho      = Predicado();
    hecho1     = Predicado();
    hecho2     = Predicado();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void interpreta(char c)                                   |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : Un caracter de entrada.                                   |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método en el cual se implementa el comportamiento del AFD |
 |                 que reconoce la sintaxis Prolog de la consulta. Depende de|
 |                 los valores que tenga el estado y del caracter de entrada.|
 |                 En algunos <case> (sólo los necesarios) se llama a        |
 |                 métodos de esta clase que revisan diversos tipos de       |
 |                 errores.                                                  |
\*---------------------------------------------------------------------------*/
void Consulta::interpreta(char c)
{
    switch (estado)
    {
      // Estado = 1
      case 1:
      {
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
          cadena.limpia();
    	  if (!cadena.ingresa(c))
            revisaError(14);
          estado = 2;
        }
    	else if (c == ' ' || c == '\n')
	           estado = 1;
		     else estado = 9;
        break;
      }

      // Estado = 2
      case 2:
      {
        if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
            (c >= 97 && c <= 122))
    	{
          if (!cadena.ingresa(c))
            revisaError(14);
          estado = 2;
        }
        else if (c == ' ' || c == '\n')
	           estado = 3;
             else if (c == '(')
                  {
                    hecho.ingresaNombre(cadena);
                    estado = 4;
                  }
    		      else estado = 9;
        break;
      }

      // Estado = 3;
      case 3:
      {
        if (c == ' ' || c == '\n')
	      estado = 3;
        else if (c == '(')
	         {
               hecho.ingresaNombre(cadena);
               estado = 4;
             }
		     else estado = 9;
        break;
      }

      // Estado = 4;
      case 4:
      {
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
          if (hecho.obtieneArgumentos() < 2)
            if (!objeto.ingresa(c))
              revisaError(14);
          estado = 5;
        }
        else if (c == ' ' || c == '\n')
	           estado = 4;
             else if (c == ')')
                  {
                    num_hechos++;
                    revisaHecho();
                    estado = 7;
                  }
	              else estado = 9;
        break;
      }

      // Estado = 5
      case 5:
      {
        if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
            (c >= 97 && c <= 122))
        {
          if (hecho.obtieneArgumentos() < 2)
            if (!objeto.ingresa(c))
              revisaError(14);
          estado = 5;
        }
	    else if (c == ' ' || c == '\n')
               estado = 6;
	         else if (c == ')')
                  {
                    if (hecho.obtieneArgumentos() == 0)
                      hecho.ingresaArgumento1(objeto);

                    if (hecho.obtieneArgumentos() == 1)
                      hecho.ingresaArgumento2(objeto);

                    hecho.incrementaArgumentos();
                    num_hechos++;
                    revisaHecho();
                    estado = 7;
                  }
		          else if (c == ',')
		               {
                         if (hecho.obtieneArgumentos() == 0)
                           hecho.ingresaArgumento1(objeto);

                         if (hecho.obtieneArgumentos() == 1)
                           hecho.ingresaArgumento2(objeto);

                         hecho.incrementaArgumentos();
                         objeto.limpia();
                         estado = 4;
                       }
		               else estado = 9;
        break;
      }

      // Estado = 6
      case 6:
      {
        if (c == ' ' || c == '\n')
	      estado = 6;
        else if (c == ')')
		     {
               if (hecho.obtieneArgumentos() == 0)
                 hecho.ingresaArgumento1(objeto);

               if (hecho.obtieneArgumentos() == 1)
                 hecho.ingresaArgumento2(objeto);

               hecho.incrementaArgumentos();
               num_hechos++;
               revisaHecho();
               estado = 7;
             }
	         else if (c == ',')
		          {
                    if (hecho.obtieneArgumentos() == 0)
                      hecho.ingresaArgumento1(objeto);

                    if (hecho.obtieneArgumentos() == 1)
                      hecho.ingresaArgumento2(objeto);

                    hecho.incrementaArgumentos();
                    objeto.limpia();
                    estado = 4;
                  }
		          else estado = 9;
        break;
      }

      // Estado = 7
      case 7:
      {
        if (c == ' ' || c == '\n')
	      estado = 7;
        else if (c == ',')
             {
               objeto.limpia();
               cadena.limpia();
               estado = 8;
             }
             else estado = 9;
        break;
      }

      // Estado = 8
      case 8:
      {
        if (c == ' ' || c == '\n')
	      estado = 8;
        else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
             {
    	       if (!cadena.ingresa(c))
                 revisaError(14);
               estado = 2;
             }
             else estado = 9;
        break;
      }
    }

    if (tipo_error == 0)
      revisaError(1);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void revisaHecho()                                        |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : En este método se revisan varios tipos de errores que se  |
 |                 pueden presentar en los hechos ingresados en la consulta. |
 |                 Si la revisión no tiene errores, entonces se guardar los  |
 |                 hechos en variables temporales.                           |
\*---------------------------------------------------------------------------*/
void Consulta::revisaHecho()
{
    revisaError(9);
    if (tipo_error == 0)
    {
      revisaError(10);
      if (tipo_error == 0)
      {
        revisaError(16);
        if (tipo_error == 0)
        {
          if (num_hechos == 1)
            hecho1 = hecho;
          else if (num_hechos == 2)
                 hecho2 = hecho;
        }
      }
    }
    hecho.limpia();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void revisaError(int tipo)                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El tipo de error que se quiere revisar.                   |
 |                 1. Error de sintaxis.                                     |
 |                 9. Predicado no declarado o mal escrito.                  |
 |                10. Número ilegal de argumentos.                           |
 |                14. Identificador con más de 255 caracteres.               |
 |                16. Consulta con más de dos hechos.                        |
 | Salidas       : No tiene.                                                 |
 | Descripción   : En este método se revisa el tipo de error que se pida.    |
 |                 En casi todas las revisiones, se hacen consultas SQL y    |
 |                 en caso de ocurrir existir algún tipo error, entonces se  |
 |                 le da valor a la varible <tipo_error>.                    |
\*---------------------------------------------------------------------------*/
void Consulta::revisaError(int tipo)
{
    String consulta;

    switch (tipo)
    {
      // 1. Error de sintaxis.
      case 1:
      {
	    if (estado == 9)
          tipo_error = 1;
        break;
      }

      // 9. Predicado no declarado o mal escrito.
      case 9:
      {
        consulta = "Select Count(*) As Total From Predicado Where Nombre_Predicado = '" +hecho.obtieneNombre()+ "'";
        if (Form4->obtieneInteger(consulta, "Total") == 0)
	      tipo_error = 9;
        break;
      }

      // 10. Número ilegal de argumentos.
      case 10:
      {
        consulta = "Select Count(*) As Total From Predicado, Argumento_Predicado Where Predicado.ID_Predicado = Argumento_Predicado.ID_Predicado And Predicado.Nombre_Predicado = '" +hecho.obtieneNombre()+ "'";
        if (Form4->obtieneInteger(consulta, "Total") != hecho.obtieneArgumentos())
	      tipo_error = 10;
        break;
      }

      // 14. Identificador con más de 255 caracteres.
      case 14:
      {
	     tipo_error = 14;
	     break;
      }

      // 16. Consulta con más de dos hechos.
      case 16:
      {
        if (num_hechos > 2)
          tipo_error = 16;
        break;
      }
    }
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int obtieneTipoError()                                    |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El valor del <tipo_error>.                                |
 | Descripción   : Método en el cual se retorna el valor del <tipo_error>.   |
\*---------------------------------------------------------------------------*/
int Consulta::obtieneTipoError()
{
    return (tipo_error);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : String obtieneMensajeError()                              |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El mensaje del tipo de error.                             |
 | Descripción   : Método en el cual se retorna el mensaje del tipo de error.|
 |                 Se hace una consulta SQL a la Tabla Tipo_Error.db.        |
\*---------------------------------------------------------------------------*/
String Consulta::obtieneMensajeError()
{
    String consulta;

    consulta = "Select Mensaje_Error From Tipo_Error Where ID_Tipo_Error = " +
                IntToStr(tipo_error)+ "";
    return (Form4->obtieneString(consulta, "Mensaje_Error"));
}

/*---------------------------------------------------------------------------*\
 | Nombre        : bool reconoce()                                           |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : Si es el AFD recone el programa, entonces retorna <true>. |
 |                 En caso contrario, retorna <false>.                       |
 | Descripción   : Método en el cual se retorna la respuesta de si el AFD    |
 |                 reconoce o no el programa Prolog ingresado.               |
\*---------------------------------------------------------------------------*/
bool Consulta::reconoce()
{
    if (estado == 1  || estado == 7)
      return (true);
    return (false);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int obtieneNumeroHechos()                                 |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : La cantidad de hechos que tiene la consulta.              |
 | Descripción   : Método en el cual se retorna la cantidad de hechos que    |
 |                 fueron ingresados en la consulta.                         |
\*---------------------------------------------------------------------------*/
int Consulta::obtieneNumeroHechos()
{
    return (num_hechos);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : Predicado * obtieneHechos()                               |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : Un puntero con los hechos obtenidos de la consulta.       |
 | Descripción   : Método en el cual se retorna un puntero a los hechos      |
 |                 obtenidos de la consulta.                                 |
\*---------------------------------------------------------------------------*/
Predicado * Consulta::obtieneHechos()
{
    if (num_hechos == 1)
    {
       hechos[0] = Predicado();
       hechos[0] = hecho1;
    }

    else if (num_hechos == 2)
         {
           hechos[0] = Predicado();
           hechos[1] = Predicado();
           hechos[0] = hecho1;
           hechos[1] = hecho2;
         }

    return (hechos);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int obtieneEstado()                                       |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El valor del estado.                                      |
 | Descripción   : Método en el cual se retorna el estado en el cual se      |
 |                 encuentra acutalmente el AFD.                             |
\*---------------------------------------------------------------------------*/
int Consulta::obtieneEstado()
{
    return (estado);
}
