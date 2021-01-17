/*---------------------------------------------------------------------------*\
 | Archivo       : Meta.cpp                                                  |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Héctor Díaz - Paul Leger.               |
 | Descripción   : Este es la Form donde el usuario debe realizan las        |
 |                 consultas al Prolog (metas). Aquí también se muestran los |
 |                 resultados obtenidos de la consulta efectudada.           |
 | Usada por     : Editor.cpp.                                               |
\*---------------------------------------------------------------------------*/

#include <vcl.h>
#pragma hdrstop
#include "Meta.h"
#include "Editor.h"
#include "SQL.h"
#include "Grafica.h"
#include "Avance.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

// Puntero a la TForm3.
TForm3 *Form3;

/*---------------------------------------------------------------------------*\
 | Nombre        : __fastcall TForm3(TComponent* Owner)                      |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : Un puntero a TComponent.                                  |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método constructor en el cual se crean e inicializan.     |
 |                 algunas variables del motor de inferencia. También se     |
 |                 llama al método que deshabilita las metas.                |
\*---------------------------------------------------------------------------*/
__fastcall TForm3::TForm3(TComponent* Owner):TForm(Owner)
{
    // Font por defecto.
    fuente1 = new TFont();
    fuente2 = new TFont();
    fuente1->Assign(Memo1->Font);
    fuente2->Assign(Memo2->Font);

    // Número de nodos por defecto.
    Max_Nodos = 10;

    deshabilita();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void __fastcall cierraForm(TObject *Sender,               |
 |                                            TCloseAction &Action)          |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : Un puntero a TObject y un puntero a TCloseAction.         |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que se activa cuando el usuario cierra la Form de  |
 |                 las Metas.                                                |
\*---------------------------------------------------------------------------*/
void __fastcall TForm3::cierraForm(TObject *Sender, TCloseAction &Action)
{
    Form3->Visible = false;
    Form1->Metas1->Checked = false;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void deshabilita()                                        |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que deshabilita los botones y la escritura en el   |
 |                 <Memo1> y el <Memo2>.                                     |
\*---------------------------------------------------------------------------*/
void TForm3::deshabilita()
{
    Button1->Enabled = false;
    Button2->Enabled = false;
    Memo1->Clear();
    Memo2->Clear();
    Memo1->Enabled  = false;
    Memo2->Enabled  = false;
    Memo2->ReadOnly = true;
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void habilita()                                           |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que habilita los botones y la escritura en el      |
 |                 <Memo1> y el <Memo2>.                                     |
\*---------------------------------------------------------------------------*/
void TForm3::habilita()
{
    Button1->Enabled = true;
    Button2->Enabled = true;
    Memo1->Clear();
    Memo2->Clear();
    Memo1->Enabled = true;
    Memo2->Enabled = true;
    Memo1->SetFocus();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void Button1Click(TObject *Sender)                        |
 | Programado por: Patricio Merino - Héctor Díaz - Paul Leger.               |
 | Entradas      : Un puntero al TObjetct.                                   |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que se activa cuando el usuario hace click en el   |
 |                 botón Consultar.                                          |
 |                 Se revisa la consulta y posteriormente se ejecuta.        |
\*---------------------------------------------------------------------------*/
void __fastcall TForm3::Button1Click(TObject *Sender)
{
    int numHechos = 0;
    Predicado *hechos;
    Consulta consulta;
    String programa;
    int i, j, longitud, error;
    char *cadena, *auxiliar;

    consulta   = Consulta();
    programa   = Memo1->Text;
    cadena     = programa.c_str();
    longitud   = strlen(cadena);
    auxiliar   = new char[longitud];
    error      = 0;

    // Ciclo en el cual se transforma la cadena a una auxiliar.
    // Se ingresa al interprete caracter a caracter el programa Prolog.
    for (i = 0, j = 0; i < longitud; i++, j++)
    {
      // Transformación de la cadena a auxiliar.
      if (cadena[i] == 13)
      {
        auxiliar[j] = '\n';
        i++;
      }
      else auxiliar[j] = cadena[i];

      // Ingresa al AFD el caracter.
      consulta.interpreta(auxiliar[j]);
      error = consulta.obtieneTipoError();

      // Si existe un error se quebra el ciclo. (Es un interprete).
      if (error != 0)
        break;
    }

    // Limpia los Resultados y las Gráficas.
    Memo2->Lines->Clear();
    Form5->limpia();
    Form5->habilita();
    Memo1->SetFocus();

    // Si la consulta nos llevó a cualquier estado, menos al 1, entonces hacer
    // hacer la consulta al motor de Inferencia.
    if (consulta.obtieneEstado() != 1)
    {
      // Si hay errores.
      if (error != 0)
        Memo2->Text = consulta.obtieneMensajeError();
      else
      {
        // Si no es reconocido.
        if (!consulta.reconoce())
          Memo2->Text = "Error de sintaxis.";
        else
        {
          // Si está libre de errores.
          Form9->activa();
          hechos = consulta.obtieneHechos();
          numHechos = consulta.obtieneNumeroHechos();

          /*----------------------------agregado por paul--------------------*/
          motorInferencia.~Motor();
          motorInferencia = Motor();
          motorInferencia.setMAX_NODOS(Max_Nodos);
          numeroSoluciones = 0;
          Soluciones = NULL;
          RespuestaTexto = "";
          MostrarArbolInferencia = "";
          Respuesta_unitaria = motorInferencia.Consulta_a_motor(hechos,numHechos);

          if (motorInferencia.getUna_Solucion() == false)
            numeroSoluciones =
                   motorInferencia.getListasolucion()->getNumerosdeSoluciones();

          // Si encuentra soluciones o si es verdadero graficara la inferencia
          // en la forma graficar.
          if ((numeroSoluciones != 0) || (Respuesta_unitaria == true))
            Form5->recibeNodoRaiz(motorInferencia.getArbol(),
                                  motorInferencia.getLista_variable(),
                                  motorInferencia.getUna_Solucion());

          // Aqui empieza el ciclo para mostrar las soluciones encontrada
          // si es se pide mostrar soluciones.
          if (motorInferencia.getUna_Solucion() == false)
          {
            Soluciones = motorInferencia.getListasolucion();
            if (numeroSoluciones == 0)
              RespuestaTexto="No hay Solucion.";
            else
            {
              for (int indice_sol = 1; indice_sol <= numeroSoluciones;
                   indice_sol++)
              {
                GrupoSolucion = Soluciones->getSolucion(indice_sol);
                SolucionParticular1 = GrupoSolucion->getPrimera();
                SolucionParticular2 = GrupoSolucion->getSegunda();
                SolucionParticular3 = GrupoSolucion->getTercera();

                if (SolucionParticular1.getAlmacenavalor () == true)
                {
                  if (SolucionParticular1.getValor() == NULL)
                    SolucionParticular1.setValor(" 'Sin Valor' ");
                  RespuestaTexto += SolucionParticular1.getIdvax()+ "=" +
                                    SolucionParticular1.getValor()+ " ";
                }

                if (SolucionParticular2.getAlmacenavalor() == true)
                {
                  if (SolucionParticular2.getValor() == NULL)
                    SolucionParticular2.setValor(" 'Sin Valor' ");
                  RespuestaTexto += SolucionParticular2.getIdvax()+ "=" +
                                    SolucionParticular2.getValor()+ " ";
                }

                if(SolucionParticular3.getAlmacenavalor() == true)
                {
                  if (SolucionParticular3.getValor() == NULL)
                    SolucionParticular3.setValor(" 'Sin Valor' ");
                  RespuestaTexto += SolucionParticular3.getIdvax()+ "=" +
                                    SolucionParticular3.getValor()+ " ";
                }

                RespuestaTexto+= char(13);
                RespuestaTexto+= char(10);
              }
              RespuestaTexto+= IntToStr(numeroSoluciones)+ " Solucion(es).";
            }
          }
          else
          {
            // Si pide saber si acaso una consulta es verdera o no.
            if (Respuesta_unitaria == true)
              RespuestaTexto = "Verdadero";
            else RespuestaTexto = "Fracaso";
          }
          Form9->desactiva();
          Memo2->Text = RespuestaTexto; // Imprime texto de solución.
          /*-------------------------fin agregado por paul--------------------*/
        }
      }
    }
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void Button2Click(TObject *Sender)                        |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : Un puntero al TObjetct.                                   |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que se activa cuando el usuario hace click en el   |
 |                 botón Nueva Consulta.                                     |
 |                 Se limpian los Memos.                                     |
\*---------------------------------------------------------------------------*/
void __fastcall TForm3::Button2Click(TObject *Sender)
{
    Memo1->Lines->Clear();
    Memo2->Lines->Clear();
    Form5->limpia();
    Form5->deshabilita();
    Memo1->SetFocus();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void porDefecto()                                         |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método que setea la fuente y el color por defecto del     |
 |                 <Memo11> y del <Memo2>.                                   |
\*---------------------------------------------------------------------------*/
void TForm3::porDefecto()
{
    // Valores por defecto del Editor.
    Memo1->Font->Assign(fuente1);
    Memo2->Font->Assign(fuente2);
    Memo1->Color = clWindow;
    Memo2->Color = clWindow;
    Max_Nodos = 10;
}
