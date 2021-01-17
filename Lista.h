//---------------------------------------------------------------------------
#ifndef ListaH
#define ListaH
//---------------------------------------------------------------------------


/*-------------------------------------------------------------------------*/
//                        CLASE ELEMENTO LISTA
/*-------------------------------------------------------------------------*/
class ElementoLista
{
    public:
    ElementoLista *Siguiente;  //apuntador usado para formar una lista enlazada
    int IDVA;                  //identificador de la variable
    String Valor;              //valor que contiene la variable

    Elemntolista();
    ElementoLista(int IDVAt,String va)//si valor es nulo, es no inicializada
     {
      IDVA=IDVAt;
      Valor=va;
      Siguiente=NULL;
     }
   ~ElementoLista() {}
/*-------------------------------------------------------------------------*/
//   Constructor y desctructor de la lista
/*-------------------------------------------------------------------------*/

    bool quitar_valor(){Valor=NULL;return true;}
   //pasar a no inicializada y quitar valor
    bool cambio_dato(String valor) {Valor=valor;return true;}
    //cambia valor de una variable al valor dado
    String Entregar_dato() {return Valor;}
    //entregar valor de la variable
};

/*-------------------------------------------------------------------------*/
//                        FIN DE CLASE ELEMENTO LISTA
/*-------------------------------------------------------------------------*/






/*-------------------------------------------------------------------------*/
//                        CLASE LISTA
/*-------------------------------------------------------------------------*/

class Lista
{
    ElementoLista *Primera;	//apuntador al primero y al último
    ElementoLista *Ultima;	//elemento de la lista
    int Indice_variable;	//contador de variables creadas

   public:
    Lista()
     {
     Primera=Ultima=NULL;
     Indice_variable=0;
     }
   ~Lista();
/*-------------------------------------------------------------------------*/
//   Constructor y desctructor de la lista
/*-------------------------------------------------------------------------*/

    int Agrega_variable(String valor);
   /* Crea una variable y entrega su identificador
      en caso de crearla no inicializada ( sin valor )
      se ingresa un NULL en el parametro */

    String Busca_valor(int IDVA);
   /*devuelve el valor de la variable a encontrar, es decir,
    pasando un identificador de variable devuelve un String con su valor
    si no tiene valor devuelve NULL*/

    bool Existe_variable_Lista(int IDVA);
    /* Verfica si la variable existe o no
      (NOTA:no si la variable tiene valor)
      Si la encuentra devuelve TRUE, sino FALSE*/

    bool Borra_elemento_lista(int idva);
    /* Elemina una variable de la lista
       (NOTA: Lo Elimina Totalmente,
        no confundir con quitar valor)
        si borra devuelve TRUE, sino FALSE*/

    bool Cambia_valor_elemento_lista(int IDVA,String valor);
     /* Cambia un valor de una variable( es decir, cambiar
        una variable de la lista) , si se quiere quitar el valor
        ingresa el NULL en el String, (Obviamente se le ingresa
        el identificador, si cambia devuelve TRUE, sino FALSE*/
};

/*-------------------------------------------------------------------------*/
//                        FIN DE CLASE LISTA
/*-------------------------------------------------------------------------*/



#endif
