//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Motor.h"

/*NOTA:= Todas las funciona seran revisada y seran evaluadas
  con un porcentaje de riesgo o falla "si es posible una acotacion"
  DENOTACION:

  ESTADO: %(PORCENTAJE)
  ACOTACION:
  RESPONSABLE:

 */


//---------------------------------------------------------------------------
#pragma package(smart_init)
/*------------------------------------------------------------------------*/
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
 //                             MOTOR


/*------------------------------------------------------------------------*/
/* ----------------------     Destructores  especificos ------------------*/
/*------------------------------------------------------------------------*/

// libera el arbol
void Motor::LiberaArbol(Nodo *Raiz)
    {
     if (Raiz!=NULL)
       {
        LiberaArbol(Raiz->Hijo_izq);
        LiberaArbol(Raiz->Hijo_der);
        delete(Raiz);
       }
    }
/*------------------------------------------------------------------------*/
/* ------------- Fin de Destructores especificos--------------------------*/
/*------------------------------------------------------------------------*/


/*------------------------------------------------------------------------*/
/*------------------------------- Nivel 1 --------------------------------*/
/*-------  Aplica la consulta. Pertenece al Nivel 0 (Motor Inferencia) ----*/
bool Motor::Consulta_a_motor(Predicado *predicado,int n)
  {
   Prepara_consulta(predicado,n);
   bool Verdad=false;
   bool CambioVariable=false;
   bool CambioConflicto=false;
   bool Condicion_BORDE=false;

   do
    {
     do
       {
        Verdad=Analiza_verdad(Nodo_raiz);
        //---------------------------------------------------------------//
        if (Numeros_de_nodos>MAX_NODOS) Condicion_BORDE=true;
        if (Condicion_BORDE==true) break;
       // Manejo de una expecion posible
       //---------------------------------------------------------------//
        if (Verdad==true)
           {
            if (Analiza_solucion()==true) break;
            else Almacena_solucion();
           }
        CambioVariable=Cambio_variable();
       }
        while(CambioVariable==true);
       if (Analiza_solucion()==true && Verdad==true) break;
      //---------------------------------------------------------------//
       if (Condicion_BORDE==true) break;
      // Manejo de una expecion posible
      //---------------------------------------------------------------//
       CambioConflicto=Cambio_conflicto();
     }
      while(CambioConflicto==true);
   return Verdad;
  }

/*-------------------- fin Nivel 1 ---------------------------------------*/
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*------------------------- Prepara consulta -----------------------------*/
/*------------------------(pertenece al nivel 1)--------------------------*/
bool Motor::Prepara_consulta(Predicado *hecho,int n)
  {
   bool logro=false;


   // una consulta (n=1)
     if (n==1)
      {
      int IDVA1=0;
      int IDVA2=0;
      if (hecho[0].obtieneTipoArgumento1()==1)
         //si es atomo el argumento =1
          {
           IDVA1=Lista_variable->Agrega_variable(hecho->obtieneArgumento1());
          }
       else
         {
         // si no es atomo
          IDVA1=Lista_variable->Agrega_variable(NULL);
         }

     Nodo_raiz= new Nodo(hecho[0].obtieneNombre(),IDVA1,NULL);

     if (hecho[0].obtieneTipo()==2&&hecho[0].obtieneArgumento1()==hecho[0].obtieneArgumento2())
         Nodo_raiz->CambiarID_variable2(Nodo_raiz->IDVA1);
         // si el hecho tiene el argumento en las 2 partes

     if (hecho[0].obtieneTipo()==2&&Nodo_raiz->IDVA2==NULL) // si es binario
         {
        if (hecho[0].obtieneTipoArgumento2()==1)
           //si es atomo el argumento =2
           {
           IDVA2=Lista_variable->Agrega_variable(hecho[0].obtieneArgumento2());
           }
       else
          {
         // si no es atomo
          IDVA2=Lista_variable->Agrega_variable(NULL);
          }
         Nodo_raiz->CambiarID_variable2(IDVA2);
        }

     if (hecho[0].obtieneTipoArgumento1()==1 && (hecho[0].obtieneTipo()!=2 ||
         hecho[0].obtieneTipoArgumento2()==1))
            Una_solucion=true;
         // si todos eran atomos
     logro=true;
     Numeros_de_nodos=1;
     }
     // fin de una consulta





   if (n==2) //dos consulta (n=2)
    {
     int IDVA1=0;
     int IDVA2=0;
     int IDVA_creada=0;
     Nodo_raiz= new Nodo(NULL,NULL,NULL);
     Nodo *Hijo_izq=NULL;
     Nodo *Hijo_der=NULL;


   if (hecho[0].obtieneTipoArgumento1()==1)
         //si es atomo el Argumento1
          {
           IDVA1=Lista_variable->Agrega_variable(hecho[0].obtieneArgumento1());

          }
       else
         {
         // si no es atomo
          IDVA1=Lista_variable->Agrega_variable(NULL);
         }

    Hijo_izq = new Nodo(hecho[0].obtieneNombre(),IDVA1,NULL);

    if (hecho[0].obtieneTipo()==2&&hecho[0].obtieneArgumento1()==hecho[0].obtieneArgumento2())
         Hijo_izq->CambiarID_variable2(Hijo_izq->IDVA1);

     if (hecho[0].obtieneTipo()==2&&Hijo_izq->IDVA2==NULL) // si es binario el primer antecendente
         {
        if (hecho[0].obtieneTipoArgumento2()==1)
         //si es atomo el argumento2
          {
           IDVA2=Lista_variable->Agrega_variable(hecho[0].obtieneArgumento2());
          }
       else
          {
         // si no es atomo
          IDVA2=Lista_variable->Agrega_variable(NULL);
          }
          Hijo_izq->CambiarID_variable2(IDVA2);
        }
    // final del hijo de izquierdo

   // Hijo derecho comenzado

    Hijo_der= new Nodo(hecho[1].obtieneNombre(),NULL,NULL);

    // Comienzo de variable de hijo de derecho
    // verificando si exite esta variable antes, es decir,
    // si la primera variable del segundo argumento existia antes
    // entoces aplica el mismo identificador, sino crea una variable
    if (hecho[1].obtieneArgumento1()==hecho[0].obtieneArgumento1())
              Hijo_der->CambiarID_variable1(Hijo_izq->IDVA1);
    if (hecho[0].obtieneTipo()==2 &&
        hecho[1].obtieneArgumento1()==hecho[0].obtieneArgumento2())
              Hijo_der->CambiarID_variable1(Hijo_izq->IDVA2);

    // si no existia antes
    if (Hijo_der->IDVA1==NULL)
         {
           if (hecho[1].obtieneTipoArgumento1()==1)
             //si es atomo el argumento1 del segundo hecho
           {
            if(IDVA2!=0) {IDVA_creada=Lista_variable->Agrega_variable(hecho[1].obtieneArgumento1());Hijo_der->CambiarID_variable1(IDVA_creada);}
            else  {IDVA2=Lista_variable->Agrega_variable(hecho[1].obtieneArgumento1());Hijo_der->CambiarID_variable1(IDVA2);}
           }
       else
           {
          if(IDVA2!=0) {IDVA_creada=Lista_variable->Agrega_variable(NULL);Hijo_der->CambiarID_variable1(IDVA_creada);}
          else  {IDVA2=Lista_variable->Agrega_variable(NULL);Hijo_der->CambiarID_variable1(IDVA2);}
           }
        }


   if( hecho[1].obtieneTipo()==2 && hecho[1].obtieneArgumento2()==hecho[1].obtieneArgumento1())
              Hijo_der->CambiarID_variable2(Hijo_der->IDVA1);

    if (hecho[1].obtieneTipo()==2 && Hijo_der->IDVA2==NULL) // si es binario del segundo antecendente
        {
    // Comienzo de la creacion de variable de la binaria variable de hijo de derecho
    // verificando si exite esta variable antes, es decir,
    // si la segunda variable del segundo argumento existia antes
    // entoces aplica el mismo identificador
    if (hecho[1].obtieneArgumento2()==hecho[0].obtieneArgumento1())
              Hijo_der->CambiarID_variable2(Hijo_izq->IDVA1);
    if (hecho[0].obtieneTipo()==2 &&
        hecho[1].obtieneArgumento2()==hecho[0].obtieneArgumento2())
              Hijo_der->CambiarID_variable2(Hijo_izq->IDVA2);




    if (Hijo_der->IDVA2==NULL)
         {
           if (hecho[1].obtieneTipoArgumento2()==1)
             //si es atomo el argumento2 del segundo hecho
           {
            IDVA_creada=Lista_variable->Agrega_variable(hecho[1].obtieneArgumento2());
            Hijo_der->CambiarID_variable2(IDVA_creada);
           }
       else
          {
          IDVA_creada=Lista_variable->Agrega_variable(NULL);
          Hijo_der->CambiarID_variable2(IDVA_creada);
          }
        }
     }

     Nodo_raiz->CambiarID_variable1(IDVA1);
     Nodo_raiz->CambiarID_variable2(IDVA2);
     Nodo_raiz->CambiarID_variableCreada(IDVA_creada);
     Nodo_raiz->Hijo_izq=Hijo_izq;
     Nodo_raiz->Hijo_der=Hijo_der;
     Hijo_izq->Padre=Nodo_raiz;
     Hijo_der->Padre=Nodo_raiz;
     Numeros_de_nodos=3;


     if ( Lista_variable->Busca_valor(IDVA1)!=NULL &&
          Lista_variable->Busca_valor(IDVA2)!=NULL && (IDVA_creada==NULL ||
          Lista_variable->Busca_valor(IDVA_creada)!=NULL) )

          Una_solucion=true;
          // si todos eran atomos

     logro=true;
    }
  //   fin de doble consulta

    return logro;
  }


/*------------------------------------------------------------------------*/
/*--------------------------- Analiza verdad -----------------------------*/
/*----------------------- (Pertenece al nivel 1) -------------------------*/
bool Motor::Analiza_verdad(Nodo *nodo_analizado)
   {
      bool Estado_regla=false;
      bool Verdad_analizada=false;

      // si al llegar la condicion de borde se cumplio
      if (MAX_NODOS < Numeros_de_nodos) return false;
      // Manteniendo bajo informacion esta condicion (OJO) //

      if (nodo_analizado->Hijo_izq==NULL) // no tiene hijos
      {
    //Todos los Argumentos tienen Valores//
       if (Lista_variable->Busca_valor(nodo_analizado->IDVA1)!=NULL &&
           ( nodo_analizado->IDVA2==NULL ||
           Lista_variable->Busca_valor(nodo_analizado->IDVA2)!=NULL ))
               {
              // es un predicado con valores(atomos)
              // si es unario

            if (nodo_analizado->IDVA2==NULL && BH.Verdad_hecho(
            nodo_analizado->Predicado,Lista_variable->Busca_valor
            (nodo_analizado->IDVA1),NULL))
                    Verdad_analizada=true;

                   //si es binario

            if (nodo_analizado->IDVA2!=NULL && BH.Verdad_hecho(
            nodo_analizado->Predicado,Lista_variable->Busca_valor
            (nodo_analizado->IDVA1),Lista_variable->Busca_valor(
            nodo_analizado->IDVA2)))
                    Verdad_analizada=true;

            if (Verdad_analizada==false)
                      Estado_regla=true;
             }
       else //si no son todos tiene valores
             // hay hecho asociado //
          if (BH.Hecho_asociado(nodo_analizado->Predicado))
             {
              bool Inicializar_variable=false;
              // se puede inicializar unario
              if (nodo_analizado->IDVA2==NULL &&
                  BH.Iniciar_variable_hecho_unario(nodo_analizado->Predicado,1)!=NULL)
                  {
                   Inicializar_variable=true;
                   Verdad_analizada=true;
                   Inicializar_variables(nodo_analizado);
                   //inciando  variable unarias
                  }
               // se puede inicializar binario
              if (nodo_analizado->IDVA2!=NULL && BH.Iniciar_variable_en_hecho
              (nodo_analizado->Predicado,Lista_variable->Busca_valor(
              nodo_analizado->IDVA1),Lista_variable->Busca_valor(
              nodo_analizado->IDVA2),1)!=NULL)
               {
                Inicializar_variable=true;
                Verdad_analizada=true;
                Inicializar_variables(nodo_analizado);
             //inciando  variable binarias
   /*-------------------------------------------------------------*/
   // aplicando parche de la consulta X,X
       if  ( nodo_analizado->INVA1==nodo_analizado->INVA2 &&
             BH.Verdad_hecho(
            nodo_analizado->Predicado,Lista_variable->Busca_valor
            (nodo_analizado->IDVA1),Lista_variable->Busca_valor(
             nodo_analizado->IDVA2))==false)
             Verdad_analizada=false;
   /*-------------------------------------------------------------*/
               }
              if (Inicializar_variable==false)
                            Estado_regla=true;
            }
           else
            {
             Estado_regla=true;
             //si no es hecho asociado a regla
             }

       }
      else   Estado_regla=true; // debe ser una regla


   if (Estado_regla==false)
            nodo_analizado->Hecho=true;

  /* si la busqueda a traves de los hechos fue infructuosa =>
    indica que pasara a regla */
         if (Estado_regla==true)
            {
            // tiene regla asociada
             if(BC.Existe_regla(nodo_analizado->Predicado)!=NULL
             || nodo_analizado->Predicado==NULL )
               {
                //no tiene hijos
                if(nodo_analizado->Hijo_izq==NULL)
                      Crea_hijos(nodo_analizado,1);
             ///sss
             int cuantosizq=0;
             int cuantosder=0;
             cuantosizq=atributosConocidos(nodo_analizado->Hijo_izq);
             cuantosder=atributosConocidos(nodo_analizado->Hijo_der);
             ///sss

             bool Verdad_hijo_izq=false;
             bool Verdad_hijo_der=true; //¿porque?
             //valores temporales de la verdad de los hijos




            if (cuantosizq>=cuantosder)
            {
              Verdad_hijo_izq=Analiza_verdad(nodo_analizado->Hijo_izq);
             //fue verdadero
             if (Verdad_hijo_izq==true)
                {
                  if (nodo_analizado->Hijo_der!=NULL)
                    {
                     Verdad_hijo_der=Analiza_verdad(nodo_analizado->Hijo_der);
                     if (Verdad_hijo_der==true)
                         Verdad_analizada=true;
                    }
                  else Verdad_analizada=true;
                }
             } //cuantosizq>cuantosder

            if (cuantosizq<cuantosder)
              {
               Verdad_hijo_der=Analiza_verdad(nodo_analizado->Hijo_der);
                if (Verdad_hijo_der==true)
                    {Verdad_hijo_izq=Analiza_verdad(nodo_analizado->Hijo_izq);
                      if (Verdad_hijo_izq==true)
                        Verdad_analizada=true;
                     }
               } //cuantosizq<cuantosder







         }

       }
         // estado_regla_fin;
       return Verdad_analizada;
  }

/*------------------------------------------------------------------------*/
/*---------------------------Crea Hijos-----------------------------------*/
/*---------------------(Pertence Analiza Verdad)--------------------------*/

void Motor::Crea_hijos(Nodo *Padre, int indice_de_regla)
{
    Regla *Regla_aux;
    Regla_aux = BC.Entregar_regla(Padre->Predicado,indice_de_regla);
    if (Regla_aux==NULL)
        ShowMessage("fue nula");
    int IDVA_creada=0;
    Nodo *hijo_izq=NULL;
    Nodo *hijo_der=NULL;


    if (indice_de_regla==1 && Regla_aux->obtieneConflicto()>0)
    {
        Padre->Conflicto = 1;
        Padre->Max_conflicto = Regla_aux->obtieneConflicto();
    }

       hijo_izq = new Nodo(Regla_aux->obtieneAntecedente1().obtieneNombre(), NULL, NULL);

     //el primer antecedente ,es decir, hijo izquierdo
    if (Regla_aux->obtieneConsecuente().obtieneArgumento1() == Regla_aux->obtieneAntecedente1().obtieneArgumento1())
        hijo_izq->IDVA1 = Padre->IDVA1;
    if (Regla_aux->obtieneAntecedente1().obtieneTipo()==2 && Regla_aux->obtieneConsecuente().obtieneArgumento1() == Regla_aux->obtieneAntecedente1().obtieneArgumento2())
        hijo_izq->IDVA2 = Padre->IDVA1;

   if (Regla_aux->obtieneConsecuente().obtieneTipo()==2) //si es binario el consecuente
    {
    if (Regla_aux->obtieneConsecuente().obtieneArgumento2() == Regla_aux->obtieneAntecedente1().obtieneArgumento1())
        hijo_izq->IDVA1 = Padre->IDVA2;
    if (Regla_aux->obtieneAntecedente1().obtieneTipo()==2 && Regla_aux->obtieneConsecuente().obtieneArgumento2() == Regla_aux->obtieneAntecedente1().obtieneArgumento2())
        hijo_izq->IDVA2 = Padre->IDVA2;
    }

    Padre->Hijo_izq=hijo_izq;
    hijo_izq->Padre=Padre;
    Numeros_de_nodos++; //condicion de Borde


     //si hay otro antecedente ,es decir, un hijo derecho
 if (Regla_aux->obtieneTipo()==2)
    {
       hijo_der = new Nodo(Regla_aux->obtieneAntecedente2().obtieneNombre(), NULL, NULL);
    if (Regla_aux->obtieneConsecuente().obtieneArgumento1() == Regla_aux->obtieneAntecedente2().obtieneArgumento1())
        hijo_der->IDVA1 = Padre->IDVA1;
    if (Regla_aux->obtieneAntecedente2().obtieneTipo()==2 && Regla_aux->obtieneAntecedente2().obtieneTipo()==2 && Regla_aux->obtieneConsecuente().obtieneArgumento1() == Regla_aux->obtieneAntecedente2().obtieneArgumento2())
        hijo_der->IDVA2 = Padre->IDVA1;

       if (Regla_aux->obtieneConsecuente().obtieneTipo()==2) // si es binario es consecuente
       {
    if (Regla_aux->obtieneConsecuente().obtieneArgumento2() == Regla_aux->obtieneAntecedente2().obtieneArgumento1())
        hijo_der->IDVA1 = Padre->IDVA2;
    if (Regla_aux->obtieneAntecedente2().obtieneTipo()==2 && Regla_aux->obtieneConsecuente().obtieneArgumento2() == Regla_aux->obtieneAntecedente2().obtieneArgumento2())
        hijo_der->IDVA2 = Padre->IDVA2;
       }

    Padre->Hijo_der=hijo_der;
    hijo_der->Padre=Padre;
    Numeros_de_nodos++; //condicion de Borde

    }

/*  Creacion de Variable
    Analizar de nuevo este caso para la agregacion de variable por
    lo que no se tien siempre al hijo derecho*/

/*-------------SEGUNDA FORMA DE CREACION DE VARIABLE---------------------------*/
if (Regla_aux->obtieneTipo()==2) // si tiene 2 antecedente
   {
 if (hijo_izq->IDVA1==NULL)
    {
     IDVA_creada=Lista_variable->Agrega_variable(NULL);
     Padre->ID_creaVariable=IDVA_creada;
     hijo_izq->CambiarID_variable1(IDVA_creada);
     if (Regla_aux->obtieneAntecedente1().obtieneTipo()==2 && hijo_izq->IDVA2==NULL)
     hijo_izq->CambiarID_variable2(IDVA_creada);
     if (hijo_der->IDVA1==NULL)
     hijo_der->CambiarID_variable1(IDVA_creada);
     if (Regla_aux->obtieneAntecedente2().obtieneTipo()==2 && hijo_der->IDVA2==NULL)
     hijo_der->CambiarID_variable2(IDVA_creada);
    }
 else
    {
     if (Regla_aux->obtieneAntecedente1().obtieneTipo()==2 && hijo_izq->IDVA2==NULL)
     {
       IDVA_creada=Lista_variable->Agrega_variable(NULL);
       Padre->ID_creaVariable=IDVA_creada;
       hijo_izq->CambiarID_variable2(IDVA_creada);
       if (hijo_der->IDVA1==NULL)
       hijo_der->CambiarID_variable1(IDVA_creada);
       if (Regla_aux->obtieneAntecedente2().obtieneTipo()==2 && hijo_der->IDVA2==NULL)
       hijo_der->CambiarID_variable2(IDVA_creada);
     }
   else
       {
        if(hijo_der->IDVA1==NULL)
         {
          IDVA_creada=Lista_variable->Agrega_variable(NULL);
          Padre->ID_creaVariable=IDVA_creada;
          hijo_der->CambiarID_variable1(IDVA_creada);
          if (Regla_aux->obtieneAntecedente2().obtieneTipo()==2 && hijo_der->IDVA2==NULL)
          hijo_der->CambiarID_variable2(IDVA_creada);
         }
        else
          {
           if(Regla_aux->obtieneAntecedente2().obtieneTipo()==2 && hijo_der->IDVA2==NULL)
            {
            IDVA_creada=Lista_variable->Agrega_variable(NULL);
            Padre->ID_creaVariable=IDVA_creada;
            hijo_der->CambiarID_variable2(IDVA_creada);
            }
          }
       }
    }

 }
/*------------------------------------------------------------------------------------------------------*/
/*---------------------------FIN DE LA de cracion de variable-------------------------------------------*/

 // si la regla tiene 1 ANTECEDNETE(un solo hijo)
 if (Regla_aux->obtieneTipo()==1)
       {
        if(Regla_aux->obtieneAntecedente1().obtieneTipo()==1) // si es unario
          {
           //(X)
            if(hijo_izq->IDVA1==NULL)
             {
              IDVA_creada=Lista_variable->Agrega_variable(NULL);
              Padre->ID_creaVariable=IDVA_creada;
              hijo_izq->IDVA1=IDVA_creada;
             }
          }
       /// fin es unario
       else
          {
           // 3casos
           if (hijo_izq->IDVA1==NULL && hijo_izq->IDVA2==NULL)
            //  (X,X)
           // si creo dos variables en ambos argumentos
             {
              IDVA_creada=Lista_variable->Agrega_variable(NULL);
              Padre->ID_creaVariable=IDVA_creada;
              hijo_izq->IDVA1=IDVA_creada;
              hijo_izq->IDVA2=IDVA_creada;
             }
           if (hijo_izq->IDVA1!=NULL && hijo_izq->IDVA2==NULL)
           //(algo,X)
       // si creo una variable en el segundo argumento
             {
              IDVA_creada=Lista_variable->Agrega_variable(NULL);
              Padre->ID_creaVariable=IDVA_creada;
              hijo_izq->IDVA2=IDVA_creada;
             }
          if (hijo_izq->IDVA1==NULL && hijo_izq->IDVA2!=NULL)
            // (X,algo)
           // si creo una variable en el primer argumento
             {
              IDVA_creada=Lista_variable->Agrega_variable(NULL);
              Padre->ID_creaVariable=IDVA_creada;
              hijo_izq->IDVA1=IDVA_creada;
             }
        }

    }
   // fin de un antecedente ( un solo hijo )

delete(Regla_aux);
}

/*------------------------------------------------------------------------*/
/*----------------------- Inicializa variables ---------------------------*/
/*---------------------(Pertence Analiza Verdad)--------------------------*/

void Motor::Inicializar_variables(Nodo *nodo_a_inicializar)
{
    Predicado *hechoIni=NULL;
    if(nodo_a_inicializar->IDVA2==NULL)//si nodo a inicializar es unario
    {
        if(Lista_variable->Busca_valor(nodo_a_inicializar->IDVA1) == NULL)//si primer argumento
                                                                          // necesita inicializarse
        {
            nodo_a_inicializar->INVA1=1;
            hechoIni=BH.Iniciar_variable_hecho_unario(nodo_a_inicializar->Predicado,1);
            Lista_variable->Cambia_valor_elemento_lista(nodo_a_inicializar->IDVA1,
            hechoIni->obtieneArgumento1());
        }
    }
    else
      // si es binario el hecho
    {
        if ((Lista_variable->Busca_valor(nodo_a_inicializar->IDVA1) == NULL) &&
            (Lista_variable->Busca_valor(nodo_a_inicializar->IDVA2) == NULL) )//si primer y segundo argumento
                                             //es variable
        {   //si ambos fueran átomos no se inicializa ninguna variable
            nodo_a_inicializar->INVA1=1;
            nodo_a_inicializar->INVA2=1;
            hechoIni=BH.Iniciar_variable_en_hecho(nodo_a_inicializar->Predicado,NULL,NULL,1);
            Lista_variable->Cambia_valor_elemento_lista(nodo_a_inicializar->IDVA1,
            hechoIni->obtieneArgumento1());
            Lista_variable->Cambia_valor_elemento_lista(nodo_a_inicializar->IDVA2,
            hechoIni->obtieneArgumento2());


        }
        else
        {
            if((Lista_variable->Busca_valor(nodo_a_inicializar->IDVA1)!= NULL)&&
                (Lista_variable->Busca_valor(nodo_a_inicializar->IDVA2) == NULL))//si primer arg es átomo
                                                 // y segundo arg es variable
            {
                nodo_a_inicializar->INVA2=1;
            hechoIni=BH.Iniciar_variable_en_hecho(nodo_a_inicializar->Predicado,
            Lista_variable->Busca_valor(nodo_a_inicializar->IDVA1),NULL,1);

            Lista_variable->Cambia_valor_elemento_lista(nodo_a_inicializar->IDVA2,
            hechoIni->obtieneArgumento2());
            // y asi cambiar los demas

            }
            else
            {
                if((Lista_variable->Busca_valor(nodo_a_inicializar->IDVA1) == NULL)&&
                    (Lista_variable->Busca_valor(nodo_a_inicializar->IDVA2) != NULL))//si primer arg es
                                            //variable y segundo arg es átomo
                {
                    nodo_a_inicializar->INVA1=1;
                    hechoIni=BH.Iniciar_variable_en_hecho(nodo_a_inicializar->Predicado,NULL,
                    Lista_variable->Busca_valor(nodo_a_inicializar->IDVA2),1);
                    Lista_variable->Cambia_valor_elemento_lista(nodo_a_inicializar->IDVA1,
                    hechoIni->obtieneArgumento1());
                }
            }
        }
    }
  delete(hechoIni);
}

/*------------------------------------------------------------------------*/
/*-------------------- Contenedor de soluciones --------------------------*/
/*------------------- (Pertenece al Nivel 1) -----------------------------*/
void Motor::Almacena_solucion()
 {
  UnaSolucion X1(Nodo_raiz->IDVA1,Lista_variable->Busca_valor(Nodo_raiz->IDVA1));
  UnaSolucion X2(Nodo_raiz->IDVA2,Lista_variable->Busca_valor(Nodo_raiz->IDVA2));
  UnaSolucion X3;
  if (Nodo_raiz->Predicado==NULL)
       X3=UnaSolucion(Nodo_raiz->ID_creaVariable,Lista_variable->Busca_valor(Nodo_raiz->ID_creaVariable));
  else X3=UnaSolucion();
  // tal ves estas lineas queden
  ElementoSoluciones *Solucion = new ElementoSoluciones(X1,X2,X3);
  Soluciones->Agregasoluciones(Solucion);
/*  ShowMessage("Numero:"+IntToStr(Numeros_de_nodos)+" "+Nodo_raiz->Predicado+" "+X1.getIdvax()+"="+Lista_variable->Busca_valor(Nodo_raiz->IDVA1)+
              " "+X2.getIdvax()+"="+Lista_variable->Busca_valor(Nodo_raiz->IDVA2));*/
 }

/*------------------------------------------------------------------------*/
/*-------------------------- (primera prioridad) -------------------------*/
/*-------------------- (Nivel 2. Cambio de variables) --------------------*/
bool Motor::Cambio_variable()
{
    bool existen;
    bool respuesta = true;
    Nodo *nodo_hoja=NULL;
    do
    {
        respuesta = true;
        nodo_hoja=NULL;
        if (Buscar_hoja_mas_derecha(Nodo_raiz,&nodo_hoja)==true)
        {
            existen = Verif_existen_vars(nodo_hoja);
            if (existen!=true)
            {
                Quitar_valores(nodo_hoja);
            }
            else
            {
                Cambiar_variables(nodo_hoja);
                respuesta=true;
                //break;         // paul
                //return true;
            }
        }
        else
        {
            respuesta=false;
            break; //paul
        }
    }while(existen != true);

    return respuesta;
}
/*------------------- (fin Nivel 2. Cambio de variable) -----------------*/
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/*----- Buscar hoja más a la derecha con instanciación de variables -----*/
/*----------- (Pertenece al nivel 2 del cambio de variables) ------------*/
bool Motor::Buscar_hoja_mas_derecha(Nodo *nodo_h, Nodo **hoja_devuelta)
{
 bool devuelve=false;
 if (nodo_h!=NULL)
  {
    if ((nodo_h->INVA1 == 0) && (nodo_h->INVA2 == 0))
    //si no tiene instaciación de variables
    {
       // bool encontro=Buscar_hoja_mas_derecha(nodo_h->Hijo_der, hoja_devuelta);
        devuelve=Buscar_hoja_mas_derecha(nodo_h->Hijo_der, hoja_devuelta);
        //cambiado por paul
        if( devuelve==false ) //encontro==false
         {
            devuelve=Buscar_hoja_mas_derecha(nodo_h->Hijo_izq, hoja_devuelta);
         }
    }
    else  //si tiene instanciación de variables
    {
        *hoja_devuelta = nodo_h;
        devuelve=true;
    }
  }
  return devuelve;
}

/*-----------------------------------------------------------------------*/
/*--------- Verificar si existen más variables para instanciar ----------*/
/*----------- (Pertenece al nivel 2 del cambio de variables) ------------*/
bool Motor::Verif_existen_vars(Nodo *hoja)
{
    bool devuelve=false;
    //verificar primero si el nodo llamado hoja es realmente una hoja,
    //es decir, si es un hecho
    if (hoja->Hijo_izq == NULL) //si el nodo no tiene hijo izquierdo
    {                           //entonces es una hoja
        if (hoja->IDVA2 == 0) //si nodo es unario (si no tiene valor el segundo
        {                     //argumento)
            if (BH.Iniciar_variable_hecho_unario(hoja->Predicado,
                (hoja->INVA1)+1) != NULL) //si existen más variables del mismo
            {                             //predicado
                devuelve = true;
            }
        }
        else //nodo no unario (binario)
        {
        if ( hoja->INVA1 > 0  && hoja->INVA2 > 0 )
             //si se cambiar inicializar dos variables
            {
                if (BH.Iniciar_variable_en_hecho
                   (hoja->Predicado,NULL,NULL,(hoja->INVA1)+1)!= NULL)
                   //si existen más pares de variables del mismo predicado
                    devuelve = true;
            }
        if ( hoja->INVA1>0 && hoja->INVA2==0)
                //si se necesita cambiar sólo la primera variable
                //(el segundo argumento es un átomo)
            {
                if (BH.Iniciar_variable_en_hecho(hoja->Predicado,
                    NULL, Lista_variable->Busca_valor(hoja->IDVA2) ,
                    (hoja->INVA1)+1) != NULL)//si existen más variables del
                                             //mismo predicado
                    devuelve = true;
            }

        if ( hoja->INVA1==0 && hoja->INVA2>0)
                //si se necesita inicializar sólo la segunda variable
                //(el primer argumento es un átomo)
            {
                if (BH.Iniciar_variable_en_hecho(hoja->Predicado,
                    Lista_variable->Busca_valor(hoja->IDVA1), NULL ,
                    (hoja->INVA2)+1) != NULL)//si existen más variables del
                                             //mismo predicado
                    devuelve = true;
            }
        }
    }
    return devuelve;
}

/*-----------------------------------------------------------------------*/
/*------------ Quita los valores y prioridad del nodo -------------------*/
/*----------- (Pertenece al nivel 2 del cambio de variables) ------------*/
void Motor::Quitar_valores(Nodo *nodo_muerto)
{
 // si el primer argumento a sido inicializado le quita la inicializacion
    if (nodo_muerto->INVA1!=0)
        {
        Lista_variable->Cambia_valor_elemento_lista(nodo_muerto->IDVA1,NULL);
        nodo_muerto->INVA1 = 0;
        }

// si el segundo argumento a sido inicializado le quita la inicializacion
   if (nodo_muerto->INVA2!=0)
        {
        Lista_variable->Cambia_valor_elemento_lista(nodo_muerto->IDVA2,NULL);
        nodo_muerto->INVA2 = 0;
        }

}

/*-----------------------------------------------------------------------*/
/*---------- Cambia las variables por las nuevas encontradas ------------*/
/*----------- (Pertenece al nivel 2 del cambio de variables) ------------*/
void Motor::Cambiar_variables(Nodo *nodo_vivo)
{
    Predicado *obj;

    //si nodo es unario
    if (nodo_vivo->IDVA2 == 0)//inicializa la primera variable
    {
        nodo_vivo->INVA1++;
        obj=BH.Iniciar_variable_hecho_unario(nodo_vivo->Predicado,
            nodo_vivo->INVA1);

        Lista_variable->Cambia_valor_elemento_lista(nodo_vivo->IDVA1,
            obj->obtieneArgumento1());
    }
    else //nodo no es unario
    {
         //Cambiar las dos variables
        if ( nodo_vivo->INVA1 > 0  && nodo_vivo->INVA2 > 0 )
        {
            nodo_vivo->INVA1++;
            nodo_vivo->INVA2++;

            obj=BH.Iniciar_variable_en_hecho(nodo_vivo->Predicado, NULL, NULL,
                nodo_vivo->INVA1);
            Lista_variable->Cambia_valor_elemento_lista(nodo_vivo->IDVA1,
                obj->obtieneArgumento1());
            Lista_variable->Cambia_valor_elemento_lista(nodo_vivo->IDVA2,
                obj->obtieneArgumento2());
        }
        else
        {
            //Cambia sólo la segunda variable
            if ( nodo_vivo->INVA1 == 0 && nodo_vivo->INVA2>0  )
            {
                nodo_vivo->INVA2++;

                obj=BH.Iniciar_variable_en_hecho(nodo_vivo->Predicado,
                       Lista_variable->Busca_valor(nodo_vivo->IDVA1),NULL,
                       nodo_vivo->INVA2);

                Lista_variable->Cambia_valor_elemento_lista(nodo_vivo->IDVA2,
                   obj->obtieneArgumento2());
            }
            else
            {
                //Cambia sólo la primera variable
                if ( nodo_vivo->INVA1>0 && nodo_vivo->INVA2==0)
                {
                    nodo_vivo->INVA1++;

                    obj=BH.Iniciar_variable_en_hecho(nodo_vivo->Predicado, NULL,
                         Lista_variable->Busca_valor(nodo_vivo->IDVA2),
                         nodo_vivo->INVA1);
                    Lista_variable->Cambia_valor_elemento_lista(nodo_vivo->IDVA1,
                        obj->obtieneArgumento1());
                }
            }
        }
    }
  delete(obj);
}

/*-----------------------------------------------------------------------*/
/*------------------- Cambio Conflicto NIvel 2 --------------------------*/
bool Motor::Cambio_conflicto()
  {
   bool cambioconflicto=false;
   bool estadoConflicto=false;
   Nodo *nodoconflicto=Nodo_raiz;

   // Aqui traspasara un hecho a un regla si es que se puede
   Pasar_Hecho_a_Regla(nodoconflicto,&cambioconflicto);
    if (cambioconflicto==true) return true;


  // si no hay hechos que traspase a una regla
    do
      {
       nodoconflicto=NULL;
       estadoConflicto=false;
       Busca_nodo_interno_mas_derecho(Nodo_raiz,&nodoconflicto);

       if (nodoconflicto!=NULL)
          {
           if(nodoconflicto->Conflicto==nodoconflicto->Max_conflicto)
              {
              // volviendo a la priemra regla
               Elimina_hijos(nodoconflicto->Hijo_izq);
               Elimina_hijos(nodoconflicto->Hijo_der);
               // borrando la variable si creo una variable el nodo
               if (nodoconflicto->ID_creaVariable!=0)
                 {
                 Lista_variable->Borra_elemento_lista(nodoconflicto->ID_creaVariable);
                 nodoconflicto->ID_creaVariable=0;
                 }
               nodoconflicto->Hijo_izq=NULL;
               nodoconflicto->Hijo_der=NULL;
               Crea_hijos(nodoconflicto,1);
               nodoconflicto->Conflicto=-2;
                //-2 es un indicador temporal del nodo para que no cambie
                //temporalmente su regla (sólo afecta a esta función)
              }
          else estadoConflicto=true;
         }
      }while (nodoconflicto!=NULL && estadoConflicto==false);

 /// Empezar a cambiar el conflicto a una regla
   if (estadoConflicto==true)
        {
         Elimina_hijos(nodoconflicto->Hijo_izq);
         Elimina_hijos(nodoconflicto->Hijo_der);
        // borrando la variable si creo una variable el nodo
         if(nodoconflicto->ID_creaVariable!=0)
             {
              Lista_variable->Borra_elemento_lista(nodoconflicto->ID_creaVariable);
              nodoconflicto->ID_creaVariable=0;
             }
         nodoconflicto->Hijo_izq=NULL;
         nodoconflicto->Hijo_der=NULL;
         Crea_hijos(nodoconflicto,++nodoconflicto->Conflicto);
         Borrar_indicador_conflicto(Nodo_raiz);
         cambioconflicto=true;
        }

   return cambioconflicto;
 }

/*------------------------------------------------------------------------*/
/*---------------------------Elimina hijos -------------------------------*/
/*------------- (pertenece al Nivel 2. Cambio de conflicto) --------------*/
void Motor::Elimina_hijos(Nodo *nodo_Conflicto_hijo)
   {
     // aqui elimina el nodo, las variables credas por el mimsmo
     // y tambien ordena borra los valores que ha inicializado
    if (nodo_Conflicto_hijo!=NULL)
      {
       Elimina_hijos(nodo_Conflicto_hijo->Hijo_izq);
       Elimina_hijos(nodo_Conflicto_hijo->Hijo_der);
       Quitar_valores(nodo_Conflicto_hijo);
       if (nodo_Conflicto_hijo->ID_creaVariable!=0)
       Lista_variable->Borra_elemento_lista(nodo_Conflicto_hijo->ID_creaVariable);
       Numeros_de_nodos--;
       delete(nodo_Conflicto_hijo);
      }
   }

/*------------------------------------------------------------------------*/
/*---------- Busca nodo interno mas derecho con conflicto-----------------*/
/*------------- (pertenece al Nivel 2. Cambio de conflicto) --------------*/
void Motor::Busca_nodo_interno_mas_derecho(Nodo *Raiz,Nodo **NodoConflicto)
    {
      // busca la interna mas derecha con un conflicto
      if (Raiz!=NULL && *NodoConflicto==NULL)
       {
        if (*NodoConflicto==NULL) Busca_nodo_interno_mas_derecho(Raiz->Hijo_der,NodoConflicto);
        if (*NodoConflicto==NULL) Busca_nodo_interno_mas_derecho(Raiz->Hijo_izq,NodoConflicto);
        if (*NodoConflicto==NULL && Raiz->Conflicto>0)
            *NodoConflicto=Raiz;
       }
    }

/*------------------------------------------------------------------------*/
/*--------------- Borrar indicador temporal de conflicto -----------------*/
/*------------- (pertenece al Nivel 2. Cambio de conflicto) --------------*/
void Motor::Borrar_indicador_conflicto(Nodo *Raiz)
   {
   // setae nuevamente los valores de conflicto a la normalidad
    if (Raiz!=NULL)
     {
      if (Raiz->Conflicto==-2) Raiz->Conflicto=1;
      Borrar_indicador_conflicto(Raiz->Hijo_izq);
      Borrar_indicador_conflicto(Raiz->Hijo_der);
     }
   }
/*------------------------------------------------------------------------*/
/*--------------- parche para pasar hecho a regla-------------------------*/
/*------------- (pertenece al Nivel 2. Cambio de conflicto)---------------*/
void Motor::Pasar_Hecho_a_Regla(Nodo *nodoconflicto,bool *cambio)
  {
  // busca un hecho que posible tambien es una regla
  // y traspasa a la priemra regla encontrada
   if (nodoconflicto!=NULL && *cambio==false)
      {
       Pasar_Hecho_a_Regla(nodoconflicto->Hijo_der,cambio);
       if (*cambio==false)
       Pasar_Hecho_a_Regla(nodoconflicto->Hijo_izq,cambio);
       if (*cambio==false && nodoconflicto->Hecho==true)
           if (BC.Existe_regla(nodoconflicto->Predicado))
                {
                 Crea_hijos(nodoconflicto,1);
                *cambio=true;
                 nodoconflicto->Hecho=false;
                }
        }
    }
/*------------------ Fin Nivel 2. Cambio de Conflicto --------------------*/
/*------------------------------------------------------------------------*/


/*------------------ Fin Nivel 1. Motor de inferencias -------------------*/
/*------------------------------------------------------------------------*/


/*------------------------------------------------------------------------*/
/*------------------funciones temporales----------------------------------*/
// ingresa String NULL
void Motor::EntregarStringArbol(Nodo *aux,String *Preorden)
 {
 //sigue siendo un funcion temporal
  if (aux!=NULL)
    {
     String idva1=IntToStr(aux->IDVA1);
     String idva2=IntToStr(aux->IDVA2);
     /**Preorden+=" ("+aux->Predicado+" "+idva1+"="+Lista_variable->
     Busca_valor(aux->IDVA1)+" "+idva2+"="+Lista_variable->
     Busca_valor(aux->IDVA2)+") ";*/
     *Preorden+=" ("+aux->Predicado+"  X"+idva1;
      if (aux->IDVA2!=NULL) *Preorden+="  X"+idva2;
      *Preorden+=" )";
     EntregarStringArbol(aux->Hijo_izq,Preorden);
     EntregarStringArbol(aux->Hijo_der,Preorden);
    }
  }




/*---------------fin funciones temporales----------------------------------*/
/*------------------------------------------------------------------------*/


int Motor::atributosConocidos(Nodo *aux)
      {
        int res=0;
        if (aux!=NULL)
            {
            if (Lista_variable->Busca_valor(aux->IDVA1)!=NULL)
            {res++;if (aux->IDVA2==NULL) res++;}
             if (aux->IDVA2!=NULL &&  Lista_variable->Busca_valor(aux->IDVA2)!=NULL)
             res++;
            }
       return res;
      }
