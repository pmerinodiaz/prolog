//---------------------------------------------------------------------------
#ifndef MotorH
#define MotorH
#include "Lista.h"
#include "Nodo.h"
#include "Predicado.h"
#include "Regla.h"
#include "InterfazBH.h"
#include "InterfazBC.h"
#include "ListaSolucion.h"

//---------------------------------------------------------------------------
class Motor
{
    Nodo *Nodo_raiz;
    //raíz del árbol, es decir, la consulta al motor

    Lista *Lista_variable;
    // lista que tiene los valores e identificadores de las variables
    // con un nodo que contengan los identifcadores puede acceder a los
    // valores si es necesario

    ListaSolucion *Soluciones;
    //Lista que contiene las soluciones
    //solamente sirve si hay que encontrar varias soluciones

    InterfazBC BC;
    InterfazBH BH;
    //clase de comunicación entre las bases de datos y el motor

    String Sol1;
    String Sol2;
    String Sol3;

    bool Una_solucion;
    //es verdadera si la respuesta al usuario es sólo
	//una solución (verdadero o falso), es falsa si la
	//respuesta al usuario es un conjunto de soluciones

    int Numeros_de_nodos;
    //cantidades de nodo creadas,debe ser menor condicion de borde
    // MAX_NODOS 100
    int MAX_NODOS;
    //condicion de borde

/*--------------------------------------------------------------------------*/
  void LiberaArbol(Nodo *); //destructor del arbol
/*--------------------------------------------------------------------------*/

    public:

    Motor()
    {
    Una_solucion=false;
    BC = InterfazBC();
    BH = InterfazBH();
    //iniciando interfaces de base dato
    Nodo_raiz=NULL;
    Lista_variable= new Lista();
    Soluciones = new ListaSolucion();
    Numeros_de_nodos=0;
    //sirve de condicion de borde (inicializando)
    MAX_NODOS=10;
    }

    ~Motor()
     {
     Lista_variable->~Lista();
     Soluciones->~ListaSolucion();
     LiberaArbol(Nodo_raiz);
     }
   // constructores y destructores del Motor


/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*-----------------------Funciones para el publico--------------------------*/
  Nodo *getArbol() {return Nodo_raiz;}
    //devuelve la raiz del arbol
    //para que asi pueda tener acceso a todo el arbol

  ListaSolucion *getListasolucion() {return Soluciones;}
    //devuelve una lista enlazada con las soluciones encontradas

  Lista *getLista_variable() {return Lista_variable;}
  // devuelve una lista con los valores de las variables
  // que contiene los nodos

  bool getUna_Solucion(){ return Una_solucion;}
   // devuelve true si al consulta es con atomos, es decir,
   // si hay que devolver verdaddero o falso

 void EntregarStringArbol(Nodo *aux,String *Preorden);
 // Entrega un String que contien el arbol de inferencia en preorden
 // importante que los dato a entrar son (Nodo_raiz , String Preorden=NULL)

 bool setMAX_NODOS(int MAX) {if (MAX>0) {MAX_NODOS=MAX;return true;}else return false;}
 int getMAX_NODOS() {return MAX_NODOS;}
 // setea los valores de condiciones de borde , es decir, la pila de nodos.


/*------------------Fin funciones para el publico---------------------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*-----------------------Metodos del nivel 0--------------------------------*/
  bool Consulta_a_motor(Predicado *,int);
         //Priemra funcion a utlizar del motor
/*------------------Fin del Metodos del nivel 0-----------------------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/


 private:
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*-----------------------Metodos del nivel 1--------------------------------*/
 bool Prepara_consulta(Predicado *,int);
                  //crea el primer nodo y la(s)
				  //primera(s) variable(s)
 bool Analiza_verdad(Nodo *nodo_analizado);
                  //analiza la verdad de un nodo
 bool Cambio_variable();
                //primera prioridad
				//busca la hoja más derecha con variable instanciada
				//y cambia su valor. Si cambia valor, devuelve true
 bool Cambio_conflicto();//segunda prioridad
				//busca el primer nodo con conflicto a través de
				//preorden invertido, borra a sus hijos y crea sus
				//nuevos hijos. Devuelve true si logra la operación
 bool Analiza_solucion(){return Una_solucion;}
    //es true si encuentra una solución, en este
    //caso se detiene y muestra su valor,sino,sigue operando con más valores
 void Almacena_solucion();
    //Almacena los valores del nodo raíz en una lista ( Soluciones )
    // para asi despues mostrarlos a traves de esta lista
/*------------------Fin del Metodos del nivel 1-----------------------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*-----------------------Metodos del nivel 2(Cambia Variable)---------------*/
  bool Buscar_hoja_mas_derecha(Nodo *,Nodo **nodo_hoja);
                 //busca el nodo hoja que se encuentre más a la
				 //derecha y que halla sido instanciado
  bool Verif_existen_vars(Nodo *nodo_hoja);	//verifica si existen más
				//variables para cambiar. Es verdadera cuando existen más
				//variables, y falsa si no hay más
                // Nota para un cietro nodo hoja (HECHO)
  void Cambiar_variables(Nodo *nodo_hoja);
              	//cambia las variables del nodo hoja
				//dado y devuelve el nodo raíz
  void Quitar_valores(Nodo *nodo_hoja);
                //quita la prioridad del nodo hoja y quita
				//los valores de las variables instanciadas
/*------------------Fin del Metodos del nivel 2(Cambia Varible)-------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*-----------------------Metodos del nivel 2(Cambia Conflicto)--------------*/
 void Busca_nodo_interno_mas_derecho(Nodo *,Nodo **);
 //busca el nodo que se encuentre más a la derecha
 //que tenga conflicto de reglas, a través de una búsqueda de
 //pre-orden invertido. Devuelve el nodo que tiene conflicto, si
 //no existe tal nodo, devuelve NULL
 void Elimina_hijos(Nodo *nodo_conflicto);
    //elimina los hijos del nodo y el nodo( se aplica a los hijos
    //del nodo en conflicto) elimina y des-instancian
    //todas las variables que se crearon en él
    //NOTA:cambia el indicador de conflicto a modo temporal, si es necesario
 void Borrar_indicador_conflicto(Nodo *Raiz);
    // borra los indicadores temporales de todo el arbol
    // Ojo: de los que tengan este indicador temporal
  void Pasar_Hecho_a_Regla(Nodo *nodoConflicto,bool *hechoconflicto);
    // un parche que pasa de hecho a regla

/*------------------Fin del Metodos del nivel 2(Cambio Conflicto)-----------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*-----------------------Funciones de Analiza Verdad------------------------*/
 void Crea_hijos(Nodo *padre,int indice_de_regla);
                  //crea los hijos si el padre es una regla.
				  //la a tomar es la segun el indice_de_regla
                  //que varia entre 1, ,n
                  // ( Que Tengan el mismo consecuente)

void Inicializar_variables(Nodo *nodo_a_inicializar);
                 //inicia por primera vez las variables de un nodo hoja
                 // es decir es hecho

/*--------------------------------------------------------------------------*/
int atributosConocidos(Nodo *);
// devuelve los atributos cuntos son atomos o no
// si tiene todos  
/*--------------------------------------------------------------------------*/

/*------------------Fin funciones de Analiza Verdad ------------------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
 
/*--------------------------------------------------------------------------*/



};

#endif
