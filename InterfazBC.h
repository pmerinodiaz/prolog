/*---------------------------------------------------------------------------*\
 | Archivo       : InterfazBC.h                                              |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Descripci�n   : Esta librer�a encapsula datos y m�todos para una interzaz |
 |                 en la cual el Motor de Inferencia se comunica con las     |
 |                 sentencias SQL.                                           |
 |                 La conexi�n se realiza entre el Motor de Inferencia y la  |
 |                 Base de Conocimientos generada en la etapa de             |
 |                 intrepretaci�n.                                           |
 | Usada por     : Motor.cpp                                                 |
\*---------------------------------------------------------------------------*/

#ifndef InterfazBCH
#define InterfazBCH
#include "Regla.h"
#include "SQL.h"

class InterfazBC
{
    public:
    InterfazBC();
    bool Existe_regla(String nombre_predicado);
    Regla * Entregar_regla(String nombre_predicado, int indice_regla);
};

#endif
