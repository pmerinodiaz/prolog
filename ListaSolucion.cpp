//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ListaSolucion.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

bool ListaSolucion::Agregasoluciones(ElementoSoluciones *Elemento)
 {
  if (Busca_solucion(Elemento)==true) return false;
  // si ya esta el elemento solucion a insertar

   ElementoSoluciones *agregado = Elemento;
       if (Primera==NULL)
        {
         Primera=Ultima=agregado;
        }
       else
        {
         Ultima->Siguiente=agregado;
         Ultima=Ultima->Siguiente;
        }
     Total++;
     return true;
    }
//---------------------------------------------------------------------------

ElementoSoluciones *ListaSolucion::getSolucion(int indice)
   {
   ElementoSoluciones *aux=Primera;
   int contador=1;


     while(aux!=NULL)
       {
        if (contador==indice) return aux;
        aux=aux->Siguiente;
        contador++;
       }

     return NULL;
  }
//---------------------------------------------------------------------------

ListaSolucion::~ListaSolucion()
    {
    ElementoSoluciones *aux=Primera;
     while(aux!=NULL)
       {
        Primera=Primera->Siguiente;
        delete(aux);
        aux=Primera;
       }
     }
//---------------------------------------------------------------------------
bool ListaSolucion::Busca_solucion(ElementoSoluciones *Solucion_esta)
  {
   bool encontrada = false;
   ElementoSoluciones *aux=Primera;

   while(aux!=NULL)
       {
        if (Solucion_esta->getPrimera().getIDVA()==aux->getPrimera().getIDVA() &&
            Solucion_esta->getPrimera().getValor()==aux->getPrimera().getValor() &&
            Solucion_esta->getSegunda().getIDVA()==aux->getSegunda().getIDVA() &&
            Solucion_esta->getSegunda().getValor()==aux->getSegunda().getValor() &&
            Solucion_esta->getTercera().getIDVA()==aux->getTercera().getIDVA() &&
            Solucion_esta->getTercera().getValor()==aux->getTercera().getValor())
            {encontrada=true;break;}
         aux=aux->Siguiente;
       }

   return encontrada;
  }
//---------------------------------------------------------------------------
