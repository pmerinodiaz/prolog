//---------------------------------------------------------------------------
#ifndef NodoH
#define NodoH
//---------------------------------------------------------------------------

class Nodo
{
    public:
    Nodo *Padre;
    Nodo *Hijo_izq;
    Nodo *Hijo_der;
    // apuntadores a los demas nodos del arbol
    int IDVA1;  //identificadores de variables en el objeto lista
    int IDVA2;  //con los que se pueda tener su valor
    String Predicado;   //predicado que representa la cláusula del nodo
    Boolean Hecho;  //verdadera si es hecho, falso si es regla
    int INVA1;  //indicadores de la cantidad de valores que han
    int INVA2;  //instanciado a las variables 1 y 2
    int Conflicto;  //indicador del número de reglas que se han utilizado
    int Max_conflicto;  //número de reglas asociadas al predicado
    int ID_creaVariable; //identificador de la variable en el nodo

    /* si los argumentos del nodo son unitario entonces
        IDVA2=INVA2=0 o IDVA2=INVA2=NULL*/


    Nodo(String pred, int IDVA1t, int IDVA2t)
    {
     Predicado=pred;
     IDVA1=IDVA1t;
     IDVA2=IDVA2t;
     Hecho=false;
     INVA1=0;
     INVA2=0;
     Conflicto=0;
     Max_conflicto=0;
     ID_creaVariable=0;
     Hijo_izq=Hijo_der=Padre=NULL;
    }
  ~Nodo() {}

/*-------------------------------------------------------------------------*/
//   Constructor y desctructor del Nodo
/*-------------------------------------------------------------------------*/
  bool CambiarID_variableCreada(int IDVAC) {ID_creaVariable=IDVAC;return true;}
  bool CambiarID_variable1(int IDVA) {IDVA1=IDVA;return true;}
  bool CambiarID_variable2(int IDVA) {IDVA2=IDVA;return true;}
 /* Cambia el Identificador a una variable de un nodo , en este caso
    segun el indice que corresponda, si quiere quitar el identificador solamenete
    se debe colocar un NULL en el paramtro*/

  //---------------------------------------------------------------------------
  // (0=NULL y 1=INICIALIZADA) o (0=FALSE y 1=TRUE)
  //---------------------------------------------------------------------------
};
#endif
