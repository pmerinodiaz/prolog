/*---------------------------------------------------------------------------*\
 | Archivo       : Cadena.cpp                                                |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Descripci�n   : Esta clase representa a una palabra (cadena) que se forma |
 |                 mientras se est�n ingresando los caracteres al interprete.|
 |                 La cadena es usada para almacenar nombres de predicados.  |
 |                 Tambi�n es usada por la clase Objeto para formar nombres  |
 |                 �tomos y variables.                                       |
 |                 La Estructura de datos que representa es un arreglo.      |
 | Usado por     : Interprete.cpp                                            |
\*---------------------------------------------------------------------------*/

#include <vcl.h>
#pragma hdrstop
#include "Cadena.h"
#pragma package(smart_init)

/*---------------------------------------------------------------------------*\
 | Nombre        : Cadena()                                                  |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo constructor en el cual se inicializa el <indice>   |
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
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : Un String que corresponde al valor de la <cadena>.        |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo en el cual se inicializa el <indice> como 0 y la   |
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
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : El caracter que se quiere ingresar a la cadena.           |
 | Salidas       : Si se pudo ingresar con exito, entonces <true>.           |
 |                 En caso contrario, <false>.                               |
 | Descripci�n   : M�todo en el cual se ingresa un caracter a la cadena (Si  |
 |                 es que la cadena no est� llena).                          |
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
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : La cadena entera con sus elementos.                       |
 | Descripci�n   : M�todo en el cual se retorna la cadena (palabra generada).|
\*---------------------------------------------------------------------------*/
String Cadena::obtiene()
{
    return (LowerCase(String(cadena)));
}

/*---------------------------------------------------------------------------*\
 | Nombre        : char obtiene(int i)                                       |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : El indice <i>.                                            |
 | Salidas       : El caracter de la cadena que est� en la posici�n <i>.     |
 | Descripci�n   : M�todo en el cual se retorna el elemento de la cadena que |
 |                 est� en la posici�n (o �ndice) <i>.                       |
\*---------------------------------------------------------------------------*/
char Cadena::obtiene(int i)
{
    return (cadena[i]);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void limpia()                                             |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : M�todo que setea a todos los elementos de la cadena en    |
 |                 valor NULL.                                               |
 |                 Adem�s el indice se hace 0.                               |
\*---------------------------------------------------------------------------*/
void Cadena::limpia()
{
    for (int i = 0; i < indice; i++)
      cadena[i] = NULL;
    indice = 0;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : bool llena()                                              |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : Si la cadena est� llena, entonces se retorna <true>.      |
 |                 En caso contrario, se retorna <false>.                    |
 | Descripci�n   : En este m�todo se realiza la pregunta de si la cadena est�|
 |                 llena o no. Y se devuelve la respuesta.                   |
\*---------------------------------------------------------------------------*/
bool Cadena::llena()
{
    return (indice == MAXSIZE);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void cambiaPrimerCaracter()                               |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripci�n   : En este m�todo se cambia el primer caracter de la cadena  |
 |                 a un caracter may�sculo.                                  |
\*---------------------------------------------------------------------------*/
void Cadena::cambiaPrimerCaracter()
{
    cadena[0] = toupper(cadena[0]);
}
