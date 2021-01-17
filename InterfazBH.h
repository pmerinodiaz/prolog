/*---------------------------------------------------------------------------*\
 | Archivo       : InterfazBH.h                                              |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Paul Leger.                             |
 | Descripción   : Esta librería encapsula datos y métodos para una interzaz |
 |                 en la cual el Motor de Inferencia se comunica con las     |
 |                 sentencias SQL.                                           |
 |                 La conexión se realiza entre el Motor de Inferencia y la  |
 |                 Base de Hechos generada en la etapa de intrepretación.    |
 | Usada por     : Motor.cpp                                                 |
\*---------------------------------------------------------------------------*/

#ifndef InterfazBHH
#define InterfazBHH
#include "Predicado.h"
#include "SQL.h"

class InterfazBH
{
    public:
    InterfazBH();
    bool Verdad_hecho(String nombre_predicado, String nombre_argumento1, String nombre_argumento2);
    bool Hecho_asociado(String nombre_predicado);
    Predicado * Iniciar_variable_hecho_unario(String nombre_predicado, int indice_hecho);
    Predicado * Iniciar_variable_en_hecho(String nombre_predicado, String nombre_argumento1, String nombre_argumento2, int indice);
};

#endif
