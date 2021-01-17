/*---------------------------------------------------------------------------*\
 | Archivo       : Interprete.cpp                                            |
 | Proyecto      : Prolog.bpr                                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Descripción   : Este es el interprete de comandos del Prolog, el cual     |
 |                 utiliza un AFD (Autómata Finito Determinista) para        |
 |                 reconocer la sintaxis del lenguaje Prolog y las           |
 |                 instrucciones SQL para ir almacendando los datos en la    |
 |                 Base de Hechos y la Base de Conocimiento.                 |
 | Usado por     : Editor.cpp.                                               |
\*---------------------------------------------------------------------------*/

#include <vcl.h>
#pragma hdrstop
#include "Interprete.h"
#include "SQL.h"
#pragma package(smart_init)

/*---------------------------------------------------------------------------*\
 | Nombre        : Interprete()                                              |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método constructor en el cual se inicializan los valores  |
 |                 de las variables que serán usadas más adelante en por el  |
 |                 interprete.                                               |
\*---------------------------------------------------------------------------*/
Interprete::Interprete()
{
    estado       = 1;
    tipo_error   = 0;
    antecedentes = 0;
    cadena       = Cadena();
    objeto       = Objeto();
    predicado    = Predicado();
    hecho        = Predicado();
    regla        = Regla();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void interpreta(char c)                                   |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : Un caracter de entrada.                                   |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método en el cual se implementa el comportamiento del AFD |
 |                 que reconoce la sintaxis Prolog. Depende de los valores   |
 |                 que tenga el estado y del caracter de entrada.            |
 |                 En algunos <case> (sólo los necesarios) se llama a        |
 |                 métodos de esta clase que revisan diversos tipos de       |
 |                 errores.                                                  |
\*---------------------------------------------------------------------------*/
void Interprete::interpreta(char c)
{
    switch (estado)
    {
      // Estado = 1
      case 1:
      {
	    if (c == 'D' || c == 'd')
	      estado = 2;
	    else if (c == ' ' || c == '\n')
		       estado = 1;
		     else estado = 67;
	    break;
      }

      // Estado = 2
      case 2:
      {
	    if (c == 'O' || c == 'o')
	      estado = 3;
	    else estado = 67;
	    break;
      }

      // Estado = 3
      case 3:
      {
	    if (c == 'M' || c == 'm')
	      estado = 4;
	    else estado = 67;
	    break;
      }

      // Estado = 4
      case 4:
      {
	    if (c == 'A' || c == 'a')
	      estado = 5;
	    else estado = 67;
	    break;
      }

      // Estado = 5
      case 5:
      {
	    if (c == 'I' || c == 'i')
	      estado = 6;
	    else estado = 67;
	    break;
      }

      // Estado = 6
      case 6:
      {
	    if (c == 'N' || c == 'n')
	      estado = 7;
	    else estado = 67;
	    break;
      }

      // Estado = 7
      case 7:
      {
        if (c == 'S' || c == 's')
	      estado = 8;
        else estado = 67;
        break;
      }

      // Estado = 8
      case 8:
      {
        if (c == ' ' || c == '\n')
	      estado = 9;
        else estado = 67;
        break;
      }

      // Estado = 9
      case 9:
      {
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
          if (!objeto.ingresa(c))
            revisaError(14);
          estado = 10;
        }
        else if (c ==  ' ' || c == '\n')
	           estado = 9;
	         else estado = 67;
        break;
      }

      // Estado = 10
      case 10:
      {
        if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
          if (!objeto.ingresa(c))
	        revisaError(14);
          estado = 10;
        }
        else if (c ==  ' ' || c == '\n')
               estado = 11;
	         else if (c == '=')
                  {
                    revisaDominio();
                    estado = 12;
                  }
		          else if (c == ',')
                       {
                         revisaDominio();
                         estado = 68;
                       }
		               else estado = 67;
        break;
      }

      // Estado = 11
      case 11:
      {
        if (c ==  ' ' || c == '\n')
          estado = 11;
        else if (c == '=')
	         {
               revisaDominio();
               estado = 12;
             }
	         else if (c == ',')
                  {
                    revisaDominio();
                    estado = 68;
                  }
                  else estado = 67;
        break;
      }

      // Estado = 12
      case 12:
      {
        if (c == 'S' || c == 's')
	      estado = 13;
        else if (c == ' ' || c == '\n')
	           estado = 12;
	         else estado = 67;
        break;
      }

      // Estado = 13
      case 13:
      {
        if (c == 'Y' || c == 'y')
	      estado = 14;
        else estado = 67;
        break;
      }

      // Estado = 14
      case 14:
      {
        if (c == 'M' || c == 'm')
	      estado = 15;
        else estado = 67;
        break;
      }

      // Estado = 15
      case 15:
      {
        if (c == 'B' || c == 'b')
	      estado = 16;
        else estado = 67;
        break;
      }

      // Estado = 16
      case 16:
      {
        if (c == 'O' || c == 'o')
	      estado = 17;
        else estado = 67;
        break;
      }

      // Estado = 17
      case 17:
      {
        if (c == 'L' || c == 'l')
	      estado = 18;
        else estado = 67;
        break;
      }

      // Estado = 18
      case 18:
      {
        if (c == ' ' || c == '\n')
          estado = 19;
        else estado = 67;
	    break;
      }

      // Estado = 19
      case 19:
      {
        if (c == 'P' || c == 'p')
        {
          if (!objeto.ingresa(c))
            revisaError(14);
          estado = 20;
        }
        else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	         {
               if (!objeto.ingresa(c))
                 revisaError(14);
               estado = 10;
             }
	         else if (c == ' ' || c == '\n')
		            estado = 19;
			  else estado = 67;
        break;
      }

      // Estado = 20
      case 20:
      {
        if (c == 'R' || c == 'r')
        {
          if (!objeto.ingresa(c))
            revisaError(14);
          estado = 21;
        }
        else if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
                 (c >= 97 && c <= 122))
	         {
               if (!objeto.ingresa(c))
                 revisaError(14);
               estado = 10;
             }
	         else if (c == ' ' || c == '\n')
			    estado = 11;
		          else if (c == '=')
		               {
                         revisaDominio();
                         estado = 12;
                       }
		               else if (c == ',')
			                {
                              revisaDominio();
                              estado = 68;
                            }
			                else estado = 67;
        break;
      }

      // Estado = 21
      case 21:
      {
        if (c == 'E' || c == 'e')
        {
	      if (!objeto.ingresa(c))
            revisaError(14);
          estado = 22;
        }
        else if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
                 (c >= 97 && c <= 122))
	         {
               if (!objeto.ingresa(c))
                 revisaError(14);
               estado = 10;
             }
	         else if (c == ' ' || c == '\n')
		            estado = 11;
                  else if (c == '=')
		               {
                         revisaDominio();
                         estado = 12;
                       }
		               else if (c == ',')
			                {
                              revisaDominio();
			                  estado = 68;
                            }
			                else estado = 67;
        break;
      }

      // Estado = 22
      case 22:
      {
        if (c == 'D' || c == 'd')
        {
          if (!objeto.ingresa(c))
            revisaError(14);
          estado = 23;
        }
        else if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
                 (c >= 97 && c <= 122))
	         {
               if (!objeto.ingresa(c))
                 revisaError(14);
               estado = 10;
	         }
	         else if (c == ' ' || c == '\n')
		            estado = 11;
                  else if (c == '=')
		               {
                         revisaDominio();
                         estado = 12;
                       }
		               else if (c == ',')
			                {
                              revisaDominio();
                              estado = 68;
                            }
			                else estado = 67;
        break;
      }

      // Estado = 23
      case 23:
      {
	    if (c == 'I' || c == 'i')
        {
          if (!objeto.ingresa(c))
            revisaError(14);
          estado = 24;
        }
        else if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
                 (c >= 97 && c <= 122))
	         {
               if (!objeto.ingresa(c))
                 revisaError(14);
               estado = 10;
             }
	         else if (c == ' ' || c == '\n')
                    estado = 11;
		          else if (c == '=')
		               {
                         revisaDominio();
                         estado = 12;
                       }
		               else if (c == ',')
					        {
                              revisaDominio();
                              estado = 68;
                            }
			                else estado = 67;
        break;
      }

      // Estado = 24
      case 24:
      {
        if (c == 'C' || c == 'c')
        {
          if (!objeto.ingresa(c))
            revisaError(14);
          estado = 25;
        }
        else if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
                 (c >= 97 && c <= 122))
	         {
               if (!objeto.ingresa(c))
		         revisaError(14);
               estado = 10;
             }
             else if (c == ' ' || c == '\n')
                    estado = 11;
		          else if (c == '=')
		               {
                         revisaDominio();
                         estado = 12;
                       }
		               else if (c == ',')
			                {
                              revisaDominio();
                              estado = 68;
                            }
			                else estado = 67;
        break;
      }

      // Estado = 25
      case 25:
      {
        if (c == 'A' || c == 'a')
        {
          if (!objeto.ingresa(c))
            revisaError(14);
          estado = 26;
        }
        else if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
                 (c >= 97 && c <= 122))
             {
               if (!objeto.ingresa(c))
                 revisaError(14);
               estado = 10;
             }
	         else if (c == ' ' || c == '\n')
                    estado = 11;
		          else if (c == '=')
		               {
                         revisaDominio();
                         estado = 12;
		               }
		               else if (c == ',')
			                {
                              revisaDominio();
                              estado = 68;
                            }
			                else estado = 67;
        break;
      }

      // Estado = 26
      case 26:
      {
        if (c == 'T' || c == 't')
        {
          if (!objeto.ingresa(c))
            revisaError(14);
          estado = 27;
        }
        else if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
                 (c >= 97 && c <= 122))
		     {
               if (!objeto.ingresa(c))
                 revisaError(14);
               estado = 10;
             }
	         else if (c == ' ' || c == '\n')
                    estado = 11;
		          else if (c == '=')
		               {
                         revisaDominio();
                         estado = 12;
                       }
		               else if (c == ',')
			                {
                              revisaDominio();
                              estado = 68;
                            }
                            else estado = 67;
        break;
      }

      // Estado = 27
      case 27:
      {
        if (c == 'E' || c == 'e')
        {
          if (!objeto.ingresa(c))
            revisaError(14);
          estado = 28;
        }
        else if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
                 (c >= 97 && c <= 122))
	         {
               if (!objeto.ingresa(c))
                 revisaError(14);
               estado = 10;
             }
	         else if (c == ' ' || c == '\n')
                    estado = 11;
		          else if (c == '=')
		               {
			             revisaDominio();
                         estado = 12;
                       }
		               else if (c == ',')
			                {
                              revisaDominio();
                              estado = 68;
                            }
			                else estado = 67;
        break;
      }

      // Estado = 28
      case 28:
      {
        if (c == 'S' || c == 's')
        {
          if (!objeto.ingresa(c))
            revisaError(14);
          estado = 29;
	    }
        else if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
                 (c >= 97 && c <= 122))
	         {
               if (!objeto.ingresa(c))
                 revisaError(14);
               estado = 10;
             }
	         else if (c == ' ' || c == '\n')
                    estado = 11;
		          else if (c == '=')
		               {
                         revisaDominio();
                         estado = 12;
                       }
                       else if (c == ',')
			                {
                              revisaDominio();
                              estado = 68;
                            }
			                else estado = 67;
	    break;
      }

      // Estado = 29
      case 29:
      {
        if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
            (c >= 97 && c <= 122))
      	{
          if (!objeto.ingresa(c))
            revisaError(14);
          estado = 10;
        }
        else if (c == ' ' || c == '\n')
               estado = 30;
	         else if (c == '=')
		          {
                    revisaDominio();
                    estado = 12;
                  }
		          else if (c == ',')
				       {
                         revisaDominio();
                         estado = 68;
                       }
			           else estado = 67;
        break;
      }

      // Estado = 30
      case 30:
      {
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
          objeto.limpia();
          if (!cadena.ingresa(c))
            revisaError(14);
          estado = 31;
        }
        else if (c == ' ' || c == '\n')
	           estado = 30;
             else if (c == '=')
			      {
                    revisaDominio();
                    estado = 12;
                  }
		          else if (c == ',')
			           {
                         revisaDominio();
                         estado = 68;
                       }
			           else estado = 67;
        break;
      }

      // Estado = 31
      case 31:
      {
        if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
            (c >= 97 && c <= 122))
        {
          if (!cadena.ingresa(c))
            revisaError(14);
	      estado = 31;
        }
        else if (c == ' ' || c == '\n')
	           estado = 32;
	         else if (c == '(')
		          {
                    predicado.ingresaNombre(cadena);
                    estado = 33;
                  }
		          else estado = 67;
        break;
      }

      // Estado = 32
      case 32:
      {
        if (c == ' ' || c == '\n')
	      estado = 32;
        else if (c == '(')
		     {
               predicado.ingresaNombre(cadena);
               estado = 33;
             }
	         else estado = 67;
        break;
      }

      // Estado = 33
      case 33:
      {
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
          if (predicado.obtieneArgumentos() < 2)
            if (!objeto.ingresa(c))
              revisaError(14);
          estado = 37;
        }
        else if (c == ' ' || c == '\n')
	           estado = 33;
		     else if (c == ')')
		          {
                    revisaPredicado();
                    estado = 36;
                  }
		          else estado = 67;
        break;
      }

      // Estado = 35
      case 35:
      {
        if (c == ' ' || c == '\n')
	      estado = 35;
        else if (c == ')')
             {
               if (predicado.obtieneArgumentos() == 0)
                 predicado.ingresaArgumento1(objeto);

               if (predicado.obtieneArgumentos() == 1)
                 predicado.ingresaArgumento2(objeto);

               predicado.incrementaArgumentos();
	           revisaPredicado();
	           estado = 36;
             }
	         else if (c == ',')
		          {
                    if (predicado.obtieneArgumentos() == 0)
                      predicado.ingresaArgumento1(objeto);

                    if (predicado.obtieneArgumentos() == 1)
                      predicado.ingresaArgumento2(objeto);

                    predicado.incrementaArgumentos();
                    objeto.limpia();
                    estado = 33;
                  }
		          else estado = 67;
        break;
      }

      // Estado = 36
      case 36:
      {
        if (c == ' ' || c == '\n')
	      estado = 38;
        else estado = 67;
        break;
      }

      // Estado = 37
      case 37:
      {
        if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
            (c >= 97 && c <= 122))
	    {
          if (predicado.obtieneArgumentos() < 2)
            if (!objeto.ingresa(c))
              revisaError(14);
          estado = 37;
	    }
        else if (c == ' ' || c == '\n')
               estado = 35;
	         else if (c == ')')
		          {
                    if (predicado.obtieneArgumentos() == 0)
                      predicado.ingresaArgumento1(objeto);

                    if (predicado.obtieneArgumentos() == 1)
                      predicado.ingresaArgumento2(objeto);

                    predicado.incrementaArgumentos();
                    revisaPredicado();
                    estado = 36;
                  }
		          else if (c == ',')
		               {
                         if (predicado.obtieneArgumentos() == 0)
                           predicado.ingresaArgumento1(objeto);

			             if (predicado.obtieneArgumentos() == 1)
                           predicado.ingresaArgumento2(objeto);

                         predicado.incrementaArgumentos();
                         objeto.limpia();
                         estado = 33;
                       }
		               else estado = 67;
        break;
      }

      // Estado = 38
      case 38:
      {
        if (c == 'C' || c == 'c')
	    {
          if (!cadena.ingresa(c))
            revisaError(14);
          estado = 39;
        }
	    else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	         {
               if (!cadena.ingresa(c))
                 revisaError(14);
               estado = 31;
             }
	         else if (c == ' ' || c == '\n')
		            estado = 38;
		          else estado = 67;
        break;
      }

      // Estado = 39
      case 39:
      {
        if (c == 'L' || c == 'l')
	    {
          if (!cadena.ingresa(c))
            revisaError(14);
          estado = 40;
	    }
        else if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
                 (c >= 97 && c <= 122))
	         {
               if (!cadena.ingresa(c))
                 revisaError(14);
               estado = 31;
             }
	         else if (c == ' ' || c == '\n')
                    estado = 32;
		          else if (c == '(')
			           {
                         predicado.ingresaNombre(cadena);
                         estado = 33;
                       }
		               else estado = 67;
        break;
      }

      // Estado = 40
      case 40:
      {
        if (c == 'A' || c == 'a')
	    {
          if (!cadena.ingresa(c))
            revisaError(14);
          estado = 41;
        }
        else if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
                 (c >= 97 && c <= 122))
	         {
               if (!cadena.ingresa(c))
                 revisaError(14);
               estado = 31;
             }
	         else if (c == ' ' || c == '\n')
                    estado = 32;
		          else if (c == '(')
		               {
                         predicado.ingresaNombre(cadena);
                         estado = 33;
                       }
		               else estado = 67;
        break;
      }

      // Estado = 41
      case 41:
      {
        if (c == 'U' || c == 'u')
	    {
          if (!cadena.ingresa(c))
            revisaError(14);
          estado = 42;
        }
        else if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
                 (c >= 97 && c <= 122))
	         {
               if (!cadena.ingresa(c))
                 revisaError(14);
               estado = 31;
	         }
	         else if (c == ' ' || c == '\n')
                    estado = 32;
		          else if (c == '(')
		               {
                         predicado.ingresaNombre(cadena);
                         estado = 33;
                       }
		               else estado = 67;
        break;
      }

      // Estado = 42
      case 42:
      {
        if (c == 'S' || c == 's')
	    {
          if (!cadena.ingresa(c))
            revisaError(14);
	      estado = 43;
        }
        else if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
                 (c >= 97 && c <= 122))
	         {
               if (!cadena.ingresa(c))
                 revisaError(14);
               estado = 31;
             }
	         else if (c == ' ' || c == '\n')
                    estado = 32;
		          else if (c == '(')
		               {
                         predicado.ingresaNombre(cadena);
                         estado = 33;
                       }
		               else estado = 67;
        break;
      }

      // Estado = 43
      case 43:
      {
        if (c == 'E' || c == 'e')
	    {
          if (!cadena.ingresa(c))
            revisaError(14);
          estado = 44;
        }
        else if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
                 (c >= 97 && c <= 122))
	         {
               if (!cadena.ingresa(c))
                 revisaError(14);
               estado = 31;
             }
	         else if (c == ' ' || c == '\n')
                    estado = 32;
		          else if (c == '(')
		               {
                         predicado.ingresaNombre(cadena);
                         estado = 33;
                       }
		               else estado = 67;
        break;
      }

      // Estado = 44
      case 44:
      {
        if (c == 'S' || c == 's')
	    {
          if (!cadena.ingresa(c))
            revisaError(14);
          estado = 45;
        }
        else if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
                 (c >= 97 && c <= 122))
	         {
               if (!cadena.ingresa(c))
                 revisaError(14);
	           estado = 31;
             }
	         else if (c == ' ' || c == '\n')
                    estado = 32;
		          else if (c == '(')
		               {
                         predicado.ingresaNombre(cadena);
                         estado = 33;
                       }
		               else estado = 67;
        break;
      }

      // Estado = 45
      case 45:
      {
        if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
            (c >= 97 && c <= 122))
        {
          if (!cadena.ingresa(c))
	        revisaError(14);
          estado = 31;
        }
        else if (c == ' ' || c == '\n')
               estado = 46;
	         else if (c == '(')
                  {
                    predicado.ingresaNombre(cadena);
		            estado = 33;
                  }
		          else estado = 67;
        break;
      }

      // Estado = 46
      case 46:
      {
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
          cadena.limpia();
	      if (!cadena.ingresa(c))
            revisaError(14);
          estado = 48;
        }
        else if (c == ' ' || c == '\n')
	           estado = 46;
	         else if (c == '(')
		          {
                    predicado.ingresaNombre(cadena);
                    estado = 33;
                  }
		          else estado = 67;
        break;
      }

      // Estado = 48
      case 48:
      {
        if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
            (c >= 97 && c <= 122))
	    {
          if (!cadena.ingresa(c))
            revisaError(14);
          estado = 48;
        }
        else if (c == ' ' || c == '\n')
	           estado = 49;
             else if (c == '(')
                  {
                    hecho.ingresaNombre(cadena);
                    estado = 50;
                  }
		          else estado = 67;
        break;
      }

      // Estado = 49
      case 49:
      {
        if (c == ' ' || c == '\n')
	      estado = 49;
        else if (c == '(')
	         {
               hecho.ingresaNombre(cadena);
               estado = 50;
             }
		     else estado = 67;
        break;
      }

      // Estado = 50
      case 50:
      {
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
          if (hecho.obtieneArgumentos() < 2)
            if (!objeto.ingresa(c))
              revisaError(14);
          estado = 51;
        }
        else if (c == ' ' || c == '\n')
	           estado = 50;
             else if (c == ')')
                    estado = 54;
	              else estado = 67;
        break;
      }

      // Estado = 51
      case 51:
      {
        if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
            (c >= 97 && c <= 122))
        {
          if (hecho.obtieneArgumentos() < 2)
            if (!objeto.ingresa(c))
              revisaError(14);
          estado = 51;
        }
	    else if (c == ' ' || c == '\n')
               estado = 53;
	         else if (c == ')')
                  {
                    if (hecho.obtieneArgumentos() == 0)
                      hecho.ingresaArgumento1(objeto);

                    if (hecho.obtieneArgumentos() == 1)
                      hecho.ingresaArgumento2(objeto);

                    hecho.incrementaArgumentos();
                    estado = 54;
                  }
		          else if (c == ',')
		               {
                         if (hecho.obtieneArgumentos() == 0)
                           hecho.ingresaArgumento1(objeto);

			             if (hecho.obtieneArgumentos() == 1)
                           hecho.ingresaArgumento2(objeto);

                         hecho.incrementaArgumentos();
                         objeto.limpia();
                         estado = 50;
                       }
		               else estado = 67;
        break;
      }

      // Estado = 53
      case 53:
      {
        if (c == ' ' || c == '\n')
	      estado = 53;
        else if (c == ')')
		     {
               if (hecho.obtieneArgumentos() == 0)
                 hecho.ingresaArgumento1(objeto);

               if (hecho.obtieneArgumentos() == 1)
                 hecho.ingresaArgumento2(objeto);

               hecho.incrementaArgumentos();
	           estado = 54;
             }
	         else if (c == ',')
		          {
                    if (hecho.obtieneArgumentos() == 0)
                      hecho.ingresaArgumento1(objeto);

                    if (hecho.obtieneArgumentos() == 1)
                      hecho.ingresaArgumento2(objeto);

                    hecho.incrementaArgumentos();
                    objeto.limpia();
                    estado = 50;
                  }
		          else estado = 67;
        break;
      }

      // Estado = 54
      case 54:
      {
        if (c == ' ' || c == '\n')
	      estado = 54;
        else if (c == '.')
	         {
               revisaHecho(1);
               estado = 55;
             }
	         else if (c == ':')
		            estado = 57;
		          else estado = 67;
        break;
      }

      // Estado = 55
      case 55:
      {
        if (c == ' ' || c == '\n')
	      estado = 56;
        else estado = 67;
        break;
      }

      // Estado = 56
      case 56:
      {
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
          cadena.limpia();
	      if (!cadena.ingresa(c))
            revisaError(14);
          estado = 48;
        }
        else if (c == ' ' || c == '\n')
	           estado = 56;
	         else estado = 67;
        break;
      }

      // Estado = 57
      case 57:
      {
        if (c == '-')
	    {
          regla.ingresaConsecuente(hecho);
          hecho.limpia();
          estado = 58;
        }
        else estado = 67;
	    break;
      }

      // Estado = 58
      case 58:
      {
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
          cadena.limpia();
          objeto.limpia();
	      if (!cadena.ingresa(c))
            revisaError(14);
          estado = 59;
        }
        else if (c == ' ' || c == '\n')
	           estado = 58;
             else estado = 67;
        break;
      }

      // Estado = 59
      case 59:
      {
        if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
            (c >= 97 && c <= 122))
        {
          if (!cadena.ingresa(c))
            revisaError(14);
          estado = 59;
        }
        else if (c == ' ' || c == '\n')
               estado = 60;
	         else if (c == '(')
                  {
                    hecho.ingresaNombre(cadena);
                    estado = 61;
                  }
		          else estado = 67;
        break;
      }

      // Estado = 60
      case 60:
      {
        if (c == ' ' || c == '\n')
	      estado = 60;
        else if (c == '(')
	         {
               hecho.ingresaNombre(cadena);
               estado = 61;
             }
	         else estado = 67;
        break;
      }

      // Estado = 61
      case 61:
      {
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
          if (hecho.obtieneArgumentos() < 2)
            if (!objeto.ingresa(c))
              revisaError(14);
          estado = 62;
        }
        else if (c == ' ' || c == '\n')
	           estado = 61;
	         else if (c == ')')
		            estado = 64;
		          else estado = 67;
        break;
      }

      // Estado = 62
      case 62:
      {
        if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) ||
            (c >= 97 && c <= 122))
        {
          if (hecho.obtieneArgumentos() < 2)
            if (!objeto.ingresa(c))
              revisaError(14);
          estado = 62;
        }
        else if (c == ' ' || c == '\n')
	           estado = 63;
	         else if (c == ')')
                  {
                    if (hecho.obtieneArgumentos() == 0)
                      hecho.ingresaArgumento1(objeto);

                    if (hecho.obtieneArgumentos() == 1)
                      hecho.ingresaArgumento2(objeto);

                    hecho.incrementaArgumentos();
                    estado = 64;
                  }
		          else if (c == ',')
                       {
                         if (hecho.obtieneArgumentos() == 0)
                           hecho.ingresaArgumento1(objeto);

			             if (hecho.obtieneArgumentos() == 1)
                           hecho.ingresaArgumento2(objeto);

                         hecho.incrementaArgumentos();
                         objeto.limpia();
                         estado = 61;
                       }
		               else estado = 67;
        break;
      }

      // Estado = 63
      case 63:
      {
        if (c == ' ' || c == '\n')
	      estado = 63;
        else if (c == ')')
	         {
               if (hecho.obtieneArgumentos() == 0)
                 hecho.ingresaArgumento1(objeto);

               if (hecho.obtieneArgumentos() == 1)
                 hecho.ingresaArgumento2(objeto);

               hecho.incrementaArgumentos();
               estado = 64;
             }
	         else if (c == ',')
			      {
                    if (hecho.obtieneArgumentos() == 0)
                      hecho.ingresaArgumento1(objeto);

                    if (hecho.obtieneArgumentos() == 1)
                      hecho.ingresaArgumento2(objeto);

                    hecho.incrementaArgumentos();
                    objeto.limpia();
                    estado = 61;
                  }
		          else estado = 67;
        break;
      }

      // Estado = 64
      case 64:
      {
        if (c == ' ' || c == '\n')
	      estado = 64;
        else if (c == '.')
	         {
               if (antecedentes == 0)
                 regla.ingresaAntecedente1(hecho);

               if (antecedentes == 1)
                 regla.ingresaAntecedente2(hecho);

               antecedentes++;
               revisaRegla();
               estado = 65;
             }
	         else if (c == ',')
		          {
                    if (antecedentes == 0)
                      regla.ingresaAntecedente1(hecho);

                    if (antecedentes == 1)
                      regla.ingresaAntecedente2(hecho);

                    antecedentes++;
                    hecho.limpia();
                    estado = 58;
                  }
		          else estado = 67;
        break;
      }

      // Estado = 65
      case 65:
      {
        if (c == ' ' || c == '\n')
	      estado = 66;
        else estado = 67;
	    break;
      }

      // Estado = 66
      case 66:
      {
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
          cadena.limpia();
	      if (!cadena.ingresa(c))
            revisaError(14);
          estado = 48;
        }
        else if (c == ' ' || c == '\n')
	           estado = 66;
	         else estado = 67;
        break;
      }

      // Estado = 68
      case 68:
      {
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
          if (!objeto.ingresa(c))
            revisaError(14);
          estado = 10;
	    }
        else if (c == ' ' || c == '\n')
               estado = 68;
             else estado = 67;
        break;
      }
    }
    if (tipo_error == 0)
      revisaError(1);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void revisaDominio()                                      |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : En este método se revisan todos los tipos de errores que  |
 |                 se puedan presentar en la parte del 'dominio' del programa|
 |                 que se está revisando.                                    |
 |                 Se llama varias veces al método <revisaError()> para que  |
 |                 este asigne valores a la variable <tipo_error>.           |
\*---------------------------------------------------------------------------*/
void Interprete::revisaDominio()
{
    revisaError(2);
    if (tipo_error != 2)
    {
      revisaError(3);
      if (tipo_error != 3)
        guardaObjeto();
    }
    objeto.limpia();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void revisaPredicado()                                    |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : En este método se revisan todos los tipos de errores que  |
 |                 se puedan presentar en la parte del 'predicates' del      |
 |                 programa que se está revisando.                           |
 |                 Se llama varias veces al método <revisaError()> para que  |
 |                 este asigne valores a la variable <tipo_error>.           |
\*---------------------------------------------------------------------------*/
void Interprete::revisaPredicado()
{
    revisaError(4);
    if (tipo_error == 0)
    {
      revisaError(8);
      if (tipo_error == 0)
      {
        revisaError(5);
        if (tipo_error == 0)
        {
          revisaError(6);
          if (tipo_error == 0)
          {
            revisaError(7);
	        if (tipo_error == 0)
              guardaPredicado();
          }
        }
      }
    }
    cadena.limpia();
    objeto.limpia();
    predicado.limpia();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void revisaHecho(int id_tipo_hecho)                       |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El tipo de hecho.                                         |
 |                 1 = Hecho                                                 |
 |                 2 = Consecuente                                           |
 |                 3 = Antecedente                                           |
 | Salidas       : No tiene.                                                 |
 | Descripción   : En este método se revisan varios tipos de errores que se  |
 |                 pueden presentar en la parte del 'clauses' del programa   |
 |                 que se está revisando. Las reglas también utilizan este   |
 |                 método para revisar los hechos que la componen.           |
 |                 Se llama varias veces al método <revisaError()> para que  |
 |                 este asigne valores a la variable <tipo_error>.           |
\*---------------------------------------------------------------------------*/
void Interprete::revisaHecho(int id_tipo_hecho)
{
    revisaError(9);
    if (tipo_error == 0)
    {
      revisaError(10);
      if (tipo_error == 0)
      {
        revisaError(15);
        if (tipo_error == 0)
        {
          if (id_tipo_hecho == 1)
            revisaError(17);
          else if (id_tipo_hecho == 2)
                 revisaError(18);

          if (tipo_error == 0)
            guardaHecho(id_tipo_hecho);
        }
      }
    }
    cadena.limpia();
    objeto.limpia();
    hecho.limpia();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void revisaRegla()                                        |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : En este método se revisan varios tipos de errores que se  |
 |                 pueden presentar en la parte del 'clauses' del programa   |
 |                 que se está revisando. En particular las de las reglas.   |
 |                 Se capturan los hechos que conforman a una regla y se     |
 |                 revisan con el método <revisaHecho()>.                    |
 |                 Se llama varias veces al método <revisaError()> para que  |
 |                 este asigne valores a la variable <tipo_error>.           |
\*---------------------------------------------------------------------------*/
void Interprete::revisaRegla()
{
    hecho = regla.obtieneConsecuente();
    revisaHecho(2);
    if (tipo_error == 0)
    {
      hecho = regla.obtieneAntecedente1();
      revisaHecho(3);

      if (tipo_error == 0)
      {
        if (regla.obtieneTipo() == 2)
        {
          hecho = regla.obtieneAntecedente2();
          revisaHecho(3);
        }

        if (tipo_error == 0)
        {
          revisaError(12);
          if (tipo_error == 0)
          {
            revisaError(18);

            if (tipo_error == 0)
              guardaRegla();
          }
        }
      }
    }

    antecedentes = 0;
    cadena.limpia();
    objeto.limpia();
    hecho.limpia();
    regla.limpia();
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void revisaError(int tipo)                                |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El tipo de error que se quiere revisar.                   |
 |                 1. Error de sintaxis.                                     |
 |                 2. Dominio no válido.                                     |
 |                 3. Dominio declarado anteriormente.                       |
 |                 4. Predicado no válido.                                   |
 |                 5. Argumento no válido.                                   |
 |                 6. Argumento no declarado en el dominio.                  |
 |                 7. Predicado con mas de dos argumentos.                   |
 |                 8. Predicado declarado anteriormente.                     |
 |                 9. Predicado no declarado o mal escrito.                  |
 |                10. Número ilegal de argumentos.                           |
 |                11. Las cláusulas para los predicados deben estar agrupadas|
 |                12. Cuerpo de la regla con mas de dos hechos.              |
 |                13. No existen cláusulas para este predicado.              |
 |                14. Identificador con más de 255 caracteres.               |
 |                15. Argumento no válido.                                   |
 |                16. Consulta con más de dos hechos.                        |
 |                17. Variable usada solamente una vez.                      |
 |                18. Variable usada dos veces en el mismo predicado.        |
 | Salidas       : No tiene.                                                 |
 | Descripción   : En este método se revisa el tipo de error que se pida.    |
 |                 En casi todas las revisiones, se hacen consultas SQL y    |
 |                 en caso de ocurrir existir algún tipo error, entonces se  |
 |                 le da valor a la varible <tipo_error>.                    |
\*---------------------------------------------------------------------------*/
void Interprete::revisaError(int tipo)
{
    String consulta;

    switch (tipo)
    {
      // 1. Error de sintaxis.
      case 1:
      {
	    if (estado == 67)
          tipo_error = 1;
        break;
      }

      // 2. Dominio no válido.
      case 2:
      {
        consulta = "Select Count(*) As Total From Palabra_Reservada Where Nombre_Palabra_Reservada = '" +objeto.obtiene()+ "'";
        if (Form4->obtieneInteger(consulta, "Total") > 0)
          tipo_error = 2;
        break;
      }

      // 3. Dominio declarado anteriormente.
      case 3:
      {
        consulta = "Select Count(*) As Total From Objeto Where Nombre_Objeto = '" +objeto.obtiene()+ "'";
        if (Form4->obtieneInteger(consulta, "Total") > 0)
          tipo_error = 3;
        break;
      }

      // 4. Predicado no válido.
      case 4:
      {
        consulta = "Select Count(*) As Total From Palabra_Reservada Where Nombre_Palabra_Reservada = '" +predicado.obtieneNombre()+ "'";
        if (Form4->obtieneInteger(consulta, "Total") > 0)
          tipo_error = 4;
        break;
      }

      // 5. Argumento no válido.
      case 5:
      {
        int tipo_predicado = predicado.obtieneTipo();

        if (tipo_predicado > 0)
        {
          consulta = "Select Count(*) As Total From Palabra_Reservada Where Not (Nombre_Palabra_Reservada = 'symbol') And (Nombre_Palabra_Reservada = '" +predicado.obtieneArgumento1()+ "')";
          if (Form4->obtieneInteger(consulta, "Total") > 0)
          {
            tipo_error = 5;
            return;
          }

          if (tipo_predicado == 2)
	      {
	        consulta = "Select Count(*) As Total From Palabra_Reservada Where Not (Nombre_Palabra_Reservada = 'symbol') And (Nombre_Palabra_Reservada = '" +predicado.obtieneArgumento2()+ "')";
	        if (Form4->obtieneInteger(consulta, "Total") > 0)
              tipo_error = 5;
	      }
        }
	    break;
      }

      // 6. Argumento no declarado en el dominio.
      case 6:
      {
        int tipo_predicado = predicado.obtieneTipo();

        if (tipo_predicado > 0)
	    {
          String argumento1 = predicado.obtieneArgumento1();

          if (argumento1 != "symbol")
	      {
            consulta = "Select Count(*) As Total From Objeto Where Nombre_Objeto = '" +argumento1+ "'";
            if (Form4->obtieneInteger(consulta, "Total") == 0)
            {
              tipo_error = 6;
              return;
            }
          }

	      if (tipo_predicado == 2)
	      {
            String argumento2 = predicado.obtieneArgumento2();

            if (argumento2 != "symbol")
	        {
              consulta = "Select Count(*) As Total From Objeto Where Nombre_Objeto = '" +argumento2+ "'";
              if (Form4->obtieneInteger(consulta, "Total") == 0)
                tipo_error = 6;
            }
          }
        }
        break;
      }

      // 7. Predicado con mas de dos argumentos.
      case 7:
      {
	    if (predicado.obtieneArgumentos() > 2)
	      tipo_error = 7;
	    break;
      }

      // 8. Predicado declarado anteriormente.
      case 8:
      {
	    consulta = "Select Count(*) As Total From Predicado Where Nombre_Predicado = '" +predicado.obtieneNombre()+ "'";
	    if (Form4->obtieneInteger(consulta, "Total") > 0)
	      tipo_error = 8;
	    break;
      }

      // 9. Predicado no declarado o mal escrito.
      case 9:
      {
        consulta = "Select Count(*) As Total From Predicado Where Nombre_Predicado = '" +hecho.obtieneNombre()+ "'";
        if (Form4->obtieneInteger(consulta, "Total") == 0)
	      tipo_error = 9;
        break;
      }

      // 10. Número ilegal de argumentos.
      case 10:
      {
        consulta = "Select Count(*) As Total From Predicado, Argumento_Predicado Where Predicado.ID_Predicado = Argumento_Predicado.ID_Predicado And Predicado.Nombre_Predicado = '" +hecho.obtieneNombre()+ "'";
        if (Form4->obtieneInteger(consulta, "Total") != hecho.obtieneArgumentos())
          tipo_error = 10;
        break;
      }

      // 12. Cuerpo de la regla con mas de dos hechos.
      case 12:
      {
        if (antecedentes > 2)
	      tipo_error = 12;
        break;
      }

      // 13. No existen cláusulas para este predicado.
      case 13:
      {
        consulta = "Select Count(*) As Total From Predicado";
        int total = Form4->obtieneInteger(consulta, "Total");

        if (total > 0)
	    {
          for (int i = 1; i <= total; i++)
          {
             consulta = "Select Count(*) As Total From Hecho Where ID_Predicado = " +IntToStr(i)+ " And (ID_Tipo_Hecho = 1 Or ID_Tipo_Hecho = 2)";
             if (Form4->obtieneInteger(consulta, "Total") == 0)
             {
               tipo_error = 13;
               break;
             }
          }
        }
        break;
      }

      // 14. Identificador con más de 255 caracteres.
      case 14:
      {
	     tipo_error = 14;
	     break;
      }

      // 15. Argumento no válido.
      case 15:
      {
        int tipo_predicado = hecho.obtieneTipo();

        if (tipo_predicado == 1)
        {
          consulta = "Select Count(*) As Total From Palabra_Reservada Where Not (Nombre_Palabra_Reservada = 'symbol') And (Nombre_Palabra_Reservada = '" +hecho.obtieneArgumento1()+ "')";
          if (Form4->obtieneInteger(consulta, "Total") > 0)
          {
            tipo_error = 5;
            return;
          }

          if (tipo_predicado == 2)
	      {
	        consulta = "Select Count(*) As Total From Palabra_Reservada Where Not (Nombre_Palabra_Reservada = 'symbol') And (Nombre_Palabra_Reservada = '" +hecho.obtieneArgumento2()+ "')";
	        if (Form4->obtieneInteger(consulta, "Total") > 0)
              tipo_error = 5;
	      }
        }
	    break;
      }

      // 17. Variable usada solamente una vez.
      case 17:
      {
        int tipo_predicado = hecho.obtieneTipo();

        if (tipo_predicado > 0)
        {
          if (hecho.capturaArgumento1().obtieneTipo() == 2)
          {
            tipo_error = 17;
            return;
          }

          if (tipo_predicado == 2)
          {
            if (hecho.capturaArgumento2().obtieneTipo() == 2)
            {
              tipo_error = 17;
              return;
            }
          }
        }
        break;
      }

      // 18. Variable usada dos veces en el mismo predicado.
      case 18:
      {
        int tipo_predicado = hecho.obtieneTipo();

        // Hecho binario.
        if (tipo_predicado == 2)
        {
          if ((hecho.capturaArgumento1().obtieneTipo() == 2) &&
              (hecho.capturaArgumento2().obtieneTipo() == 2) &&
              (hecho.obtieneArgumento1() == hecho.obtieneArgumento2()))
            tipo_error = 18;
        }

        break;
      }
    }
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void guardaObjeto()                                       |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : En este método se guarda un objeto (Atomo o Variable) en  |
 |                 la tabla Objeto.db.                                       |
\*---------------------------------------------------------------------------*/
void Interprete::guardaObjeto()
{
    Form4->insertaObjeto(Form4->nuevoIDObjeto(), 1, objeto.obtieneTipo(),
                         objeto.obtiene());
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void guardaPredicado()                                    |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método en el cual se guarda un predicado en la tabla      |
 |                 Predicado.db.                                             |
 |                 Se realizan una serie de consultas previas para obtener   |
 |                 información relevante antes de insertar el predicado en la|
 |                 tabla.                                                    |
\*---------------------------------------------------------------------------*/
void Interprete::guardaPredicado()
{
    String consulta;
    int id_predicado, id_objeto, tipo_predicado;

    id_predicado   = Form4->nuevoIDPredicado();
    tipo_predicado = predicado.obtieneTipo();
    Form4->insertaPredicado(id_predicado, tipo_predicado,
                            predicado.obtieneNombre());

    if (tipo_predicado > 0)
    {
      String argumento1 = predicado.obtieneArgumento1();

      consulta = "Select Count(*) As Total From Objeto Where Nombre_Objeto = '" +argumento1+ "'";
      if (Form4->obtieneInteger(consulta, "Total") == 0)
        Form4->insertaObjeto(Form4->nuevoIDObjeto(), 1, 0, argumento1);

      consulta = "Select ID_Objeto From Objeto Where Nombre_Objeto = '" +argumento1+ "'";
      id_objeto = Form4->obtieneInteger(consulta, "ID_Objeto");
      Form4->insertaArgumentoPredicado(Form4->nuevoIDArgumentoPredicado(), id_predicado, id_objeto, 1);

      if (tipo_predicado == 2)
      {
        String argumento2 = predicado.obtieneArgumento2();

        consulta = "Select Count(*) As Total From Objeto Where Nombre_Objeto = '" +predicado.obtieneArgumento2()+ "'";
        if (Form4->obtieneInteger(consulta, "Total") == 0)
          Form4->insertaObjeto(Form4->nuevoIDObjeto(), 1, 0, argumento2);

        consulta = "Select ID_Objeto From Objeto Where Nombre_Objeto = '" +argumento2+ "'";
        id_objeto = Form4->obtieneInteger(consulta, "ID_Objeto");
        Form4->insertaArgumentoPredicado(Form4->nuevoIDArgumentoPredicado(), id_predicado, id_objeto, 2);
      }
    }
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void guardaHecho(int id_tipo_hecho)                       |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : El tipo del hecho.                                        |
 |                 1. Hecho                                                  |
 |                 2. Consecuente                                            |
 |                 3. Antecedente                                            |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método en el cual se guarda un hecho en la tabla Hecho.db |
 |                 Se realizan una serie de consultas previas para obtener   |
 |                 información relevante antes de insertar el predicado en la|
 |                 tabla.                                                    |
\*---------------------------------------------------------------------------*/
void Interprete::guardaHecho(int id_tipo_hecho)
{
    String consulta, argumento1, argumento2;
    int id_hecho, id_predicado, indice_hecho, id_objeto, tipo_hecho;

    id_hecho = Form4->nuevoIDHecho();

    consulta = "Select ID_Predicado From Predicado Where Nombre_Predicado = '" +hecho.obtieneNombre() +"'";
    id_predicado = Form4->obtieneInteger(consulta, "ID_Predicado");

    if (id_tipo_hecho == 3)
      indice_hecho = 0;
    else indice_hecho = Form4->nuevoIndiceHecho(id_predicado, id_tipo_hecho);

    if (indice_hecho > 0)
    {
      int ultimo_id_hecho = Form4->ultimoIDHecho(id_predicado);
      int ultimo_id_tipo  = Form4->ultimoHechoConsecuente();

      if ((ultimo_id_hecho != ultimo_id_tipo) && (ultimo_id_hecho != 0))
      {
        tipo_error = 11;
        return;
      }
    }

    Form4->insertaHecho(id_hecho, indice_hecho, id_predicado, id_tipo_hecho);

    tipo_hecho = hecho.obtieneTipo();
    if (tipo_hecho > 0)
    {
      argumento1 = hecho.obtieneArgumento1();

      consulta = "Select Count(*) As Total From Objeto Where Nombre_Objeto = '" +argumento1+ "'";
      if (Form4->obtieneInteger(consulta, "Total") == 0)
        Form4->insertaObjeto(Form4->nuevoIDObjeto(), 1, hecho.capturaArgumento1().obtieneTipo(), argumento1);

      consulta = "Select ID_Objeto From Objeto Where Nombre_Objeto = '" +argumento1+ "'";
      id_objeto = Form4->obtieneInteger(consulta, "ID_Objeto");
      Form4->insertaArgumentoHecho(Form4->nuevoIDArgumentoHecho(), id_objeto, id_hecho, 1);

      if (tipo_hecho == 2)
      {
        argumento2 = hecho.obtieneArgumento2();

        consulta = "Select Count(*) As Total From Objeto Where Nombre_Objeto = '" +argumento2+ "'";
        if (Form4->obtieneInteger(consulta, "Total") == 0)
          Form4->insertaObjeto(Form4->nuevoIDObjeto(), 1, hecho.capturaArgumento2().obtieneTipo(), argumento2);

        consulta = "Select ID_Objeto From Objeto Where Nombre_Objeto = '" +argumento2+ "'";
        id_objeto = Form4->obtieneInteger(consulta, "ID_Objeto");
        Form4->insertaArgumentoHecho(Form4->nuevoIDArgumentoHecho(), id_objeto, id_hecho, 2);
      }
    }
}

/*---------------------------------------------------------------------------*\
 | Nombre        : void guardaRegla()                                        |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : No tiene.                                                 |
 | Descripción   : Método en el cual se guarda una rela en la tabla Regla.db |
 |                 Se realizan una serie de consultas previas para obtener   |
 |                 información relevante antes de insertar el predicado en la|
 |                 tabla.                                                    |
\*---------------------------------------------------------------------------*/
void Interprete::guardaRegla()
{
    int id_regla, tipo_regla, ultimo_id_hecho;

    id_regla   = Form4->nuevoIDRegla();
    tipo_regla = regla.obtieneTipo();
    Form4->insertaRegla(id_regla, tipo_regla);

    ultimo_id_hecho = Form4->ultimoHecho();

    if (tipo_regla == 1)
    {
      Form4->insertaOrdenHecho(Form4->nuevoIDOrdenHecho(),id_regla,
                               ultimo_id_hecho - 1, 1);
      Form4->insertaOrdenHecho(Form4->nuevoIDOrdenHecho(),id_regla,
                               ultimo_id_hecho, 2);
    }
    else
    {
      if (regla.obtieneTipo() == 2)
      {
        Form4->insertaOrdenHecho(Form4->nuevoIDOrdenHecho(),id_regla,
                                 ultimo_id_hecho - 2, 1);
        Form4->insertaOrdenHecho(Form4->nuevoIDOrdenHecho(),id_regla,
                                 ultimo_id_hecho - 1, 2);
        Form4->insertaOrdenHecho(Form4->nuevoIDOrdenHecho(),id_regla,
                                 ultimo_id_hecho, 3);
      }
    }
}

/*---------------------------------------------------------------------------*\
 | Nombre        : int obtieneTipoError()                                    |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El valor del <tipo_error>.                                |
 | Descripción   : Método en el cual se retorna el valor del <tipo_error>.   |
\*---------------------------------------------------------------------------*/
int Interprete::obtieneTipoError()
{
    return (tipo_error);
}

/*---------------------------------------------------------------------------*\
 | Nombre        : String obtieneMensajeError()                              |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : El mensaje del tipo de error.                             |
 | Descripción   : Método en el cual se retorna el mensaje del tipo de error.|
 |                 Se hace una consulta SQL a la Tabla Tipo_Error.db.        |
\*---------------------------------------------------------------------------*/
String Interprete::obtieneMensajeError()
{
    String consulta;

    consulta = "Select Mensaje_Error From Tipo_Error Where ID_Tipo_Error = " +
                IntToStr(tipo_error)+ "";
    return (Form4->obtieneString(consulta, "Mensaje_Error"));
}

/*---------------------------------------------------------------------------*\
 | Nombre        : bool reconoce()                                           |
 | Programado por: Patricio Merino - Héctor Díaz.                            |
 | Entradas      : No tiene.                                                 |
 | Salidas       : Si es el AFD recone el programa, entonces retorna <true>. |
 |                 En caso contrario, retorna <false>.                       |
 | Descripción   : Método en el cual se retorna la respuesta de si el AFD    |
 |                 reconoce o no el programa Prolog ingresado.               |
\*---------------------------------------------------------------------------*/
bool Interprete::reconoce()
{
    if (estado == 1  || estado == 8  || estado == 9  || estado == 18 ||
        estado == 19 || estado == 29 || estado == 30 || estado == 36 ||
        estado == 38 || estado == 45 || estado == 46 || estado == 55 ||
        estado == 56 || estado == 65 || estado == 66)
      return (true);
    return (false);
}