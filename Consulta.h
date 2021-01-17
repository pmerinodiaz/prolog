/*---------------------------------------------------------------------------*\
 | Archivo       : Consulta.h                                                |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Descripción   : Esta librería empaqueta la clase Consulta, la cual        |
 |                 representa al pequeño interprete de comandos que el Prolog|
 |                 utiliza para capturar la consulta ingresada.              |
 | Usada por     : Meta.cpp, Consulta.cpp                                    |
\*---------------------------------------------------------------------------*/

#ifndef ConsultaH
#define ConsultaH
#include "Predicado.h"
#include "Objeto.h"
#include "Cadena.h"

class Consulta
{
    private:
    int estado;
    int num_hechos;
    int tipo_error;
    Cadena cadena;
    Objeto objeto;
    Predicado hecho;
    Predicado hecho1;
    Predicado hecho2;
    Predicado hechos[2];

    public:
    Consulta();
    void interpreta(char c);
    void revisaHecho();
    void revisaError(int tipo);
    bool reconoce();
    String obtieneMensajeError();
    int obtieneTipoError();
    int obtieneNumeroHechos();
    Predicado * obtieneHechos();
    int obtieneEstado();
};

#endif
