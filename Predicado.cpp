/*---------------------------------------------------------------------------*\
 | Archivo       : Predicado.cpp                                             |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Descripción   : Clase que representa a un predicado del Prolog. Se        |
 |                 constituye de una Cadena nombre y de dos Objetos que son  |
 |                 los argumentos.                                           |
 | Usado por     : Interprete.cpp, Regla.cpp                                 |
\*---------------------------------------------------------------------------*/

#include <vcl.h>
#pragma hdrstop
#include "Predicado.h"
#pragma package(smart_init)
#define SINTIPO -1
#define SINARGU  0
#define UNITARIO 1
#define BINARIO  2

/*---------------------------------------------------------------------------*\
 | Nombre        : Predicado()                                               |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método constructor en el cual se inicializan los valores  |
 |                 de las variables.                                         |
 |                 Se asigna memoria a los objeto y se inicializa.           |
\*---------------------------------------------------------------------------*/
Predicado::Predicado()
{
    nombre     = Cadena();
    argumento1 = Objeto();
    argumento2 = Objeto();
    tipo       = SINTIPO;
    argumentos = 0;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void ingresaNombre(Cadena cadena)                         |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : La cadena del nombre del predicado.                       |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método en el cual se setea la cedena <nombre>.            |
\*---------------------------------------------------------------------------*/
void Predicado::ingresaNombre(Cadena cadena)
{
    nombre = cadena;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void ingresaArgumento1(Objeto objeto)                     |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El objeto que representa el argumento1.                   |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método en el cual se setea el objeto <argumento1>.        |
\*---------------------------------------------------------------------------*/
void Predicado::ingresaArgumento1(Objeto objeto)
{
    argumento1 = objeto;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void ingresaArgumento2(Objeto objeto)                     |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El objeto que representa el argumento2.                   |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método en el cual se setea el objeto <argumento2>.        |
\*---------------------------------------------------------------------------*/
void Predicado::ingresaArgumento2(Objeto objeto)
{
    argumento2 = objeto;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : String obtieneNombre()                                    |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El nombre del predicado.                                  |
 | Descripción   : Método en el cual se retorna el String que tiene el nombre|
 |                 del predicado.                                            |
\*---------------------------------------------------------------------------*/
String Predicado::obtieneNombre()
{
    return (nombre.obtiene());
}

/*---------------------------------------------------------------------------*\
 | Nombre        : String obtieneArgumento1()                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El argumento1 del predicado.                              |
 | Descripción   : Método en el cual se retorna el String que tiene el       |
 |                 argumento1 del predicado.                                 |
\*---------------------------------------------------------------------------*/
String Predicado::obtieneArgumento1()
{
    return (argumento1.obtiene());
}

/*---------------------------------------------------------------------------*\
 | Nombre        : String obtieneArgumento2()                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El argumento2 del predicado.                              |
 | Descripción   : Método en el cual se retorna el String que tiene el       |
 |                 argumento2 del predicado.                                 |
\*---------------------------------------------------------------------------*/
String Predicado::obtieneArgumento2()
{
    return (argumento2.obtiene());
}

/*---------------------------------------------------------------------------*\
 | Nombre        : Cadena capturaNombre()                                    |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El nombre del predicado como objeto de la clase <Cadena>. |
 | Descripción   : Método en el cual se retorna la Cadena que tiene el       |
 |                 nombre del predicado.                                     |
\*---------------------------------------------------------------------------*/
Cadena Predicado::capturaNombre()
{
    return (nombre);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : Objeto capturaArgumento1()                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El argumento1 del predicado como objeto de clase <Objeto>.|
 | Descripción   : Método en el cual se retorna el Objeto que tiene el       |
 |                 argumento1 del predicado.                                 |
\*---------------------------------------------------------------------------*/
Objeto Predicado::capturaArgumento1()
{
    return (argumento1);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : Objeto capturaArgumento2()                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El argumento2 del predicado como objeto de clase <Objeto>.|
 | Descripción   : Método en el cual se retorna el Objeto que tiene el       |
 |                 argumento2 del predicado.                                 |
\*---------------------------------------------------------------------------*/
Objeto Predicado::capturaArgumento2()
{
    return (argumento2);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int obtieneTipo()                                         |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El tipo de predicado.                                     |
 |                 -1. Sin tipo                                              |
 |                  0. Sin argumentos                                        |
 |                  1. Unitario                                              |
 |                  2. Binario                                               |
 | Descripción   : En este método se setea el valor de <tipo>. Se preguntan  |
 |                 por los casos posibles de existencia y no existencia de   |
 |                 los argumentos que tiene el predicado.                    |
\*---------------------------------------------------------------------------*/
int Predicado::obtieneTipo()
{
    tipo = SINTIPO;

    int tipo_argumento1 = argumento1.obtieneTipo();
    int tipo_argumento2 = argumento2.obtieneTipo();

    if ((tipo_argumento1 == 0) && (tipo_argumento2 == 0))
      tipo = SINARGU;
    else if ((tipo_argumento1 != 0) && (tipo_argumento2 == 0))
           tipo = UNITARIO;
         else if ((tipo_argumento1 != 0) && (tipo_argumento2 != 0))
                tipo = BINARIO;

    return (tipo);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int obtieneTipoArgumento1()                               |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El tipo de objeto del argumento1.                         |
 |                 0. Sin tipo.                                              |
 |                 1. Atomo.                                                 |
 |                 2. Variable.                                              |
 | Descripción   : En este método se retorna el tipo de objeto que tiene el  |
 |                 <argumento1>. Se llama al método <obtieneTipo()>.         |
\*---------------------------------------------------------------------------*/
int Predicado::obtieneTipoArgumento1()
{
    return (argumento1.obtieneTipo());
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int obtieneTipoArgumento2()                               |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El tipo de objeto del argumento2.                         |
 |                 0. Sin tipo.                                              |
 |                 1. Atomo.                                                 |
 |                 2. Variable.                                              |
 | Descripción   : En este método se retorna el tipo de objeto que tiene el  |
 |                 <argumento2>. Se llama al método <obtieneTipo()>.         |
\*---------------------------------------------------------------------------*/
int Predicado::obtieneTipoArgumento2()
{
    return (argumento2.obtieneTipo());
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void limpia()                                             |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : En este método se llama a los metodos de los objetos que  |
 |                 limpian la cadena <nombre> y los objetos <argumento1> y   |
 |                 <argumento2>.                                             |
\*---------------------------------------------------------------------------*/
void Predicado::limpia()
{
    nombre.limpia();
    argumento1.limpia();
    argumento2.limpia();
    argumentos = 0;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void incrementaArgumentos()                               |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : En este método se suma 1 a la variable <argumentos>.      |
\*---------------------------------------------------------------------------*/
void Predicado::incrementaArgumentos()
{
    argumentos++;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void obtieneArgumentos()                                  |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El número de argumentos que fueron ingresados.            |
 | Descripción   : En este método se obtiene el número de argumentos que     |
 |                 fueron ingresados al predicado.                           |
\*---------------------------------------------------------------------------*/
int Predicado::obtieneArgumentos()
{
    return (argumentos);
}
