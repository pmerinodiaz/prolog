/*---------------------------------------------------------------------------*\
 | Archivo       : Objeto.h                                                  |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - H�ctor D�az.                            |
 | Descripci�n   : Esta librer�a encapsula los datos y m�todos para la clase |
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
