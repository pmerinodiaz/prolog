/*---------------------------------------------------------------------------*\
 | Archivo       : Predicado.h                                               |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Descripción   : Esta librería empaqueta la clase Predicado para ser usada |
 |                 en otros ficheros.                                        |
 |                 La clase Predicado se compone de una Cadena <nombre> que  |
 |                 es el nombre del predicado, además de dos Objetos         |
 |                 <argumento1> y <argumento2> que representan a los         |
 |                 argumentos dentro del predicado.                          |
 | Usada por     : Interprete.cpp, Regla.cpp, Predicado.cpp                  |
\*---------------------------------------------------------------------------*/

#ifndef PredicadoH
#define PredicadoH
#include "Cadena.h";
#include "Objeto.h"

class Predicado
{
    private:
    Cadena nombre;
    Objeto argumento1;
    Objeto argumento2;
    int tipo;
    int argumentos;

    public:
    Predicado();
    void ingresaNombre(Cadena cadena);
    void ingresaArgumento1(Objeto objeto);
    void ingresaArgumento2(Objeto objeto);
    String obtieneNombre();
    String obtieneArgumento1();
    String obtieneArgumento2();
    Cadena capturaNombre();
    Objeto capturaArgumento1();
    Objeto capturaArgumento2();
    int obtieneTipo();
    void limpia();
    int obtieneTipoArgumento1();
    int obtieneTipoArgumento2();
    void incrementaArgumentos();
    int obtieneArgumentos();
};

#endif
