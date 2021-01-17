//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Lista.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
/*------------------------------------------------------------------------*/
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
 //                     Lista

 Lista::~Lista()
    {
    ElementoLista *aux=Primera;
     while(aux!=NULL)
       {
        Primera=Primera->Siguiente;
        delete(aux);
        aux=Primera;
       }
     }
/*------------------------------------------------------------------------*/
 int Lista::Agrega_variable(String valor)
     {
      ElementoLista *agregado = new ElementoLista(Indice_variable+1,valor);
      if (Primera==NULL)
        {
         Primera=Ultima=agregado;
        }
       else
        {
         Ultima->Siguiente=agregado;
         Ultima=Ultima->Siguiente;
        }

     return ++Indice_variable;
    }
/*------------------------------------------------------------------------*/

 String Lista::Busca_valor(int IDVA)
  {
   ElementoLista *aux=Primera;
   String Valor=NULL;

     while(aux!=NULL)
       {
        if (aux->IDVA==IDVA) {Valor=aux->Valor;break;}
        aux=aux->Siguiente;
       }
     return Valor;
  }

/*------------------------------------------------------------------------*/
bool Lista::Cambia_valor_elemento_lista(int IDVA,String valor)
   {
   ElementoLista *aux=Primera;
   bool Res=false;

     while(aux!=NULL)
       {
        if (aux->IDVA==IDVA) {aux->Valor=valor;Res=true;break;}
        aux=aux->Siguiente;
       }
     return Res;
  }
/*------------------------------------------------------------------------*/

bool Lista::Existe_variable_Lista(int IDVA)
   {
   ElementoLista *aux=Primera;
   bool Res=false;

     while(aux!=NULL)
       {
        if (aux->IDVA==IDVA) {Res=true;break;}
        aux=aux->Siguiente;
       }
     return Res;
  }
/*------------------------------------------------------------------------*/

bool Lista::Borra_elemento_lista(int idva)
   {
   ElementoLista *aux=Primera;
   ElementoLista *aux2;
   bool Res=false;

    if(Primera->IDVA==idva)
     {
      aux=Primera->Siguiente;
      delete(Primera);
      Primera=aux;
      Res=true;
     }

   if(Ultima->IDVA==idva)
     {
      while (aux->Siguiente!=Ultima) aux=aux->Siguiente;
      delete(Ultima);
      Ultima=aux;
      Ultima->Siguiente=NULL;
      Res=true;
     }

  if (Res==false)
   {
     while(aux->Siguiente!=NULL)
       {
           if (aux->Siguiente->IDVA==idva)
           {
           aux2=aux->Siguiente;
           aux->Siguiente=aux->Siguiente->Siguiente;
           delete(aux2);
           Res=true;
           break;
           }
       aux=aux->Siguiente;
      }
    }
     return Res;
  }
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

