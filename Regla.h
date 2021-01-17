/*---------------------------------------------------------------------------*\
 | Archivo       : Regla.h                                                   |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Descripción   : Esta librería empaqueta la clase Regla para ser usada en  |
 |                 otros ficheros.                                           |
 |                 La clase Regla se compone de un Predicado <consecuente>   |
 |                 y de dos Predicados <antecedente1> y <antecedente2>.      |
 | Usada por     : Interprete.cpp, Regla.cpp                                 |
\*---------------------------------------------------------------------------*/

#ifndef ReglaH
#define ReglaH
#include "Predicado.h"

class Regla
{
    private:
    Predicado consecuente;
    Predicado antecedente1;
    Predicado antecedente2;
    int tipo;
    int conflicto;

    public:
    Regla();
    void ingresaConsecuente(Predicado predicado);
    void ingresaAntecedente1(Predicado predicado);
    void ingresaAntecedente2(Predicado predicado);
    Predicado obtieneConsecuente();
    Predicado obtieneAntecedente1();
    Predicado obtieneAntecedente2();
    int obtieneTipo();
    void limpia();
    int obtieneConflicto();
    void ingresaConflicto(int cantidad);
};

#endif
