/*---------------------------------------------------------------------------*\
 | Archivo       : SQL.h                                                     |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Descripción   : Esta librería empaqueta la clase TForm4 para ser usada en |
 |                 otros archivos.                                           |
 | Usada por     : Interprete.cpp, Editor.cpp                                |
\*---------------------------------------------------------------------------*/

#ifndef SQLH
#define SQLH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBTables.hpp>

class TForm4 : public TForm
{
    __published:
    TTable *Table1;
    TQuery *Query1;

    private:

    public:
    __fastcall TForm4(TComponent* Owner);
    String obtieneString(String consulta, String campo);
    int obtieneInteger(String consulta, String campo);
    int nuevoIDObjeto();
    int nuevoIDPredicado();
    int nuevoIDArgumentoPredicado();
    int nuevoIDHecho();
    int nuevoIDArgumentoHecho();
    int nuevoIDRegla();
    int nuevoIndiceHecho(int id_predicado, int id_tipo_hecho);
    int nuevoIDOrdenHecho();
    int ultimoIDHecho(int id_predicado);
    int ultimoHechoConsecuente();
    int ultimoHecho();
    void ejecuta(String consulta);
    void insertaObjeto(int id_objeto, int id_tipo_dato, int id_tipo_objeto, String nombre_objeto);
    void insertaPredicado(int id_predicado, int id_tipo_predicado, String nombre_predicado);
    void insertaArgumentoPredicado(int id_argumento_predicado, int id_predicado, int id_objeto, int orden_argumento_predicado);
    void insertaArgumentoHecho(int id_argumento_hecho, int id_objeto, int id_hecho, int orden_argumento_hecho);
    void insertaHecho(int id_hecho, int indice_hecho, int id_predicado, int id_tipo_hecho);
    void insertaRegla(int id_regla, int id_tipo_regla);
    void insertaOrdenHecho(int id_orden_hecho, int id_regla, int id_hecho, int orden_hecho);
    void limpiaBaseDatos();
    void buscaRegla(String predicado, int indice);
};

extern PACKAGE TForm4 *Form4;
#endif
