/*---------------------------------------------------------------------------*\
 | Archivo       : Interprete.h                                              |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Descripción   : Esta librería empaqueta la clase Interprete, la cual      |
 |                 representa al interprete de comandos del Prolog.          |
 | Uso           : En Editor.cpp                                             |
\*---------------------------------------------------------------------------*/

#ifndef InterpreteH
#define InterpreteH
#include "Cadena.h"
#include "Objeto.h"
#include "Predicado.h"
#include "Regla.h"

class Interprete
{
    private:
    int estado;
    int tipo_error;
    int argumentos;
    int antecedentes;
    Cadena cadena;
    Objeto objeto;
    Predicado predicado;
    Predicado hecho;
    Regla regla;

    public:
    Interprete();
    void interpreta(char c);
    void revisaDominio();
    void revisaPredicado();
    void revisaHecho(int id_tipo_hecho);
    void revisaRegla();
    void revisaError(int tipo);
    int obtieneTipoError();
    String obtieneMensajeError();
    bool reconoce();
    void guardaObjeto();
    void guardaPredicado();
    void guardaHecho(int id_tipo_hecho);
    void guardaRegla();
};

#endif
