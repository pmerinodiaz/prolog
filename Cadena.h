/*---------------------------------------------------------------------------*\
 | Archivo       : Cadena.h                                                  |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Descripción   : Esta librería encapsula los datos y métodos para la clase |
 |                 Cadena, para luego ser usada en otros archivos.           |
 |                 La clase Cadena se compone de un arreglo de caracteres    |
 |                 <cadena> y de un <indice> del arreglo.                    |
 | Usada por     : Interprete.cpp, Cadena.cpp, Objeto.cpp, Predicado.cpp     |
\*---------------------------------------------------------------------------*/

#ifndef CadenaH
#define CadenaH
#define MAXSIZE 255

class Cadena
{
    private:
    char cadena[MAXSIZE];
    int indice;

    public:
    Cadena();
    bool ingresa(char c);
    void ingresa(String string);
    String obtiene();
    char obtiene(int i);
    void limpia();
    bool llena();
    void cambiaPrimerCaracter();
};

#endif
