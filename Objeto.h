/*---------------------------------------------------------------------------*\
 | Archivo       : Objeto.h                                                  |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Descripción   : Esta librería encapsula los datos y métodos para la clase |
 |                 Objeto, para luego ser usada en otros archivos.           |
 |                 La clase Objeto se deriva de la clase Cadena. El atributo |
 |                 que se incorpora es el <tipo> que nos permite identificar |
 |                 si un Objeto es Variable o Atomo.                         |
 | Usada por     : Interprete.cpp, Objeto.cpp, Predicado.cpp                 |
\*---------------------------------------------------------------------------*/

#ifndef ObjetoH
#define ObjetoH
#include "Cadena.h"

class Objeto : public Cadena
{
    private:
    int tipo;

    public:
    Objeto();
    int obtieneTipo();
};

#endif
