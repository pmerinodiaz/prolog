//---------------------------------------------------------------------------
#ifndef ListaSolucionH
#define ListaSolucionH
//---------------------------------------------------------------------------

/*-------------------------------------------------------------------------*/
//                        CLASE UNASOLUCION
/*-------------------------------------------------------------------------*/
class UnaSolucion
{
 private:
 int IDVA;        // Identificador de la variable solucion
 String IDVAX;    // Identifcador con X + mas identificador
 String Valor;    // Valor de la variable

 public:

 UnaSolucion()
 {
 IDVA=0;
 IDVAX="";
 Valor="";
 }

 UnaSolucion(int ID,String Val)
 {
  IDVA=ID;
  IDVAX="X"+IntToStr(IDVA);
  Valor=Val;
 }

 ~UnaSolucion() {}
/*-------------------------------------------------------------------------*/
//   Constructor y desctructor de la UNASOLUCION
/*-------------------------------------------------------------------------*/
 String getIdvax() { return IDVAX;}
 // devuelve in identifcador(variable) en forma de String (Ej: "X1","X3")

 String getValor() { return Valor;}
 // devuelve el valor de la variable

 int getIDVA() { return IDVA;}
// devuelve el identicador en int (Ej: 1,2,4)

 bool setValor(String valor)  {Valor=valor;return true;}
 // setea el valor de la solucion

 // deuvelve el identicador en int (Ej: 1,2,4)
 bool getAlmacenavalor()
 {
  if (IDVA==0) return false;
  return true;
 }
 /* Funcion que sirve para saber si acaso la variable es valida como solucion
    si es valida es true, sino es false*/


};
/*-------------------------------------------------------------------------*/
//                           FIN CLASE UNASOLUCION
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
//                        CLASE ElEMENTOSOLUCIONES
/*-------------------------------------------------------------------------*/
class ElementoSoluciones
{
    private:
    UnaSolucion Primera;
    UnaSolucion Segunda;
    UnaSolucion Tercera;
    /* Como la solucion puede tener 3 valores ( es decir , X=? Y=? Z=?)*/


    public:
    ElementoSoluciones *Siguiente;
    //apuntador usado para formar una lista enlazada

    ElementoSoluciones()
     {
      Primera = UnaSolucion();
      Segunda = UnaSolucion();
      Tercera = UnaSolucion();
      Siguiente=NULL;
     }

    ElementoSoluciones(UnaSolucion P1,UnaSolucion P2,UnaSolucion P3)
     {
      Primera=P1;
      Segunda=P2;
      Tercera=P3;
      Siguiente=NULL;
      }

    ~ElementoSoluciones() {}
/*-------------------------------------------------------------------------*/
//   Constructor y desctructor de la ELEMENTOSOLUCIONES
/*-------------------------------------------------------------------------*/
    UnaSolucion getPrimera() {return Primera;}
    UnaSolucion getSegunda() {return Segunda;}
    UnaSolucion getTercera() {return Tercera;}
    // Retorna cada una soluciones Pedidas
};
/*-------------------------------------------------------------------------*/
//                        FIN CLASE ElEMENTOSOLUCIONES
/*-------------------------------------------------------------------------*/






/*-------------------------------------------------------------------------*/
//                        CLASE LISTASOLUCION
/*-------------------------------------------------------------------------*/
class ListaSolucion
  {
    private:
    ElementoSoluciones *Primera;
    ElementoSoluciones *Ultima;
    //apuntador al primero y al último elemento de la lista
    int Total;
    //indica el numero de soluciones en la lista

    public:
    ListaSolucion()
      {
       Primera=Ultima=NULL;
       Total=0;
      }
   ~ListaSolucion();
/*-------------------------------------------------------------------------*/
//   Constructor y desctructor de la LISTASOLUCION
/*-------------------------------------------------------------------------*/
    bool Agregasoluciones(ElementoSoluciones*);
    /* Agrega una solucion ( que puede ser un elemento 3 soluciones )
       si agrega con satisfacion devuelve TRUE,sino FALSE
       (NOTA: la grega al final de la lista)  */
    int getNumerosdeSoluciones() { return Total;}
    /* devuelve el numero total de grupo de soluciones encontradas
       Por Ejejmplo (X=TOM Y=JUAN Z=PEDRO
                     X=HUMBERTO Y=JUAN Z=PEPE)
                     devolveria 2 */
    ElementoSoluciones *getSolucion(int indice);
    /* devuelve un grupo de soluciones dadando el indice a encontrar
      en la fila. Sino la encuntra devuelve NULL
      Ej:           (X=TOM Y=JUAN Z=PEDRO
                     X=HUMBERTO Y=JUAN Z=PEPE)
                     devolveria 2
     Si pregunto con inidice 2 devuelve (X=HUMBERTO Y=JUAN Z=PEPE)*/

     bool Busca_solucion(ElementoSoluciones *);
     /* devuelve true si la solucion esta ya almacenada
        devuelve false sino esta la solucion*/

};
/*-------------------------------------------------------------------------*/
//                        FIN CLASE LISTASOLUCION
/*-------------------------------------------------------------------------*/




#endif
