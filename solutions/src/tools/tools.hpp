/*! \file tools.hpp
  \brief Header pour la classe tools
*/
#ifndef TOOLS_HPP
#define TOOLS_HPP
#include <iostream>
#include "tools_config.hpp"

/*! \brief Description de la classe tools

	Ici on peut mettre par exemple des formules latex :
	\f[
	g(\dot x, x, t, z) = 0
	\f]

	Ou des todo :
	\todo un truc à faire

	des bugs 
	\bug il y a un bug dans la fonction set_toto
	et plein d'autres choses encore : voir le manuel doxygen. 
**/
class tools
{
private : 
  /** description de a */
  int a;
  /** description de b */
  int b;
public:
  /** Le constructeur par défaut */
  tools();
  /** Description de la fonction
	  \param arg1 description du premier argument
	  \param arg2 description du second argument
	  \return description de la variable de retour
   */
  bool set_tools(int,int);

  /** Une fonction d'affichage 
   */
  void affiche() const;
  
};
#endif
