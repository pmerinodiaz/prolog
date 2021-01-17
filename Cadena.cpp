/*---------------------------------------------------------------------------*\
 | Archivo       : Cadena.cpp                                                |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Descripción   : Esta clase representa a una palabra (cadena) que se forma |
 |                 mientras se están ingresando los caracteres al interprete.|
 |                 La cadena es usada para almacenar nombres de predicados.  |
 |                 También es usada por la clase Objeto para formar nombres  |
 |                 átomos y variables.                                       |
 |                 La Estructura de datos que representa es un arreglo.      |
 | Usado por     : Interprete.cpp                                            |
\*---------------------------------------------------------------------------*/

#include <vcl.h>
#pragma hdrstop
#include "Cadena.h"
#pragma package(smart_init)

/*---------------------------------------------------------------------------*\
 | Nombre        : Cadena()                                                  |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método constructor en el cual se inicializa el <indice>   |
 |                 como 0 y los todos los elementos de la cadena se setean   |
 |                 con valor NULL.                                           |
\*---------------------------------------------------------------------------*/
Cadena::Cadena()
{
    indice = 0;
    for (int i = 0; i < MAXSIZE; i++)
      cadena[i] = NULL;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : ingresa(String string)                                    |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : Un String que corresponde al valor de la <cadena>.        |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método en el cual se inicializa el <indice> como 0 y la   |
 |                 cadena se iguala al <string>.                             |
\*---------------------------------------------------------------------------*/
void Cadena::ingresa(String string)
{
    char *auxiliar;
    int i;

    auxiliar = string.c_str();
    indice   = strlen(auxiliar);

    for (i = 0; i < indice; i++)
      cadena[i] = auxiliar[i];
}

/*---------------------------------------------------------------------------*\
 | Nombre        : bool ingresa(char c)                                      |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El caracter que se quiere ingresar a la cadena.           |
 | Salidas       : Si se pudo ingresar con exito, entonces <true>.           |
 |                 En caso contrario, <false>.                               |
 | Descripción   : Método en el cual se ingresa un caracter a la cadena (Si  |
 |                 es que la cadena no está llena).                          |
\*---------------------------------------------------------------------------*/
bool Cadena::ingresa(char c)
{
    if (!llena())
    {
      cadena[indice] = c;
      indice++;
      return (true);
    }

    return (false);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : String obtiene()                                          |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : La cadena entera con sus elementos.                       |
 | Descripción   : Método en el cual se retorna la cadena (palabra generada).|
\*---------------------------------------------------------------------------*/
String Cadena::obtiene()
{
    return (LowerCase(String(cadena)));
}

/*---------------------------------------------------------------------------*\
 | Nombre        : char obtiene(int i)                                       |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El indice <i>.                                            |
 | Salidas       : El caracter de la cadena que está en la posición <i>.     |
 | Descripción   : Método en el cual se retorna el elemento de la cadena que |
 |                 está en la posición (o índice) <i>.                       |
\*---------------------------------------------------------------------------*/
char Cadena::obtiene(int i)
{
    return (cadena[i]);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void limpia()                                             |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que setea a todos los elementos de la cadena en    |
 |                 valor NULL.                                               |
 |                 Además el indice se hace 0.                               |
\*---------------------------------------------------------------------------*/
void Cadena::limpia()
{
    for (int i = 0; i < indice; i++)
      cadena[i] = NULL;
    indice = 0;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : bool llena()                                              |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : Si la cadena está llena, entonces se retorna <true>.      |
 |                 En caso contrario, se retorna <false>.                    |
 | Descripción   : En este método se realiza la pregunta de si la cadena está|
 |                 llena o no. Y se devuelve la respuesta.                   |
\*---------------------------------------------------------------------------*/
bool Cadena::llena()
{
    return (indice == MAXSIZE);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void cambiaPrimerCaracter()                               |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : En este método se cambia el primer caracter de la cadena  |
 |                 a un caracter mayúsculo.                                  |
\*---------------------------------------------------------------------------*/
void Cadena::cambiaPrimerCaracter()
{
    cadena[0] = toupper(cadena[0]);
}
