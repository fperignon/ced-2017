/*! \file linearAlgebraTools.hpp
  \brief Header pour l'interface à boost ublas
*/
#ifndef LATOOLS_HPP
#define LATOOLS_HPP

#include "tools_config.hpp"

// Ce qui suit n'est inclu que si boost est disponible
#ifdef HAS_BOOST

#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

/** Alias vers les matrices boost*/
typedef boost::numeric::ublas::matrix<double> LAMatrix;

/*! \brief Description de la classe linearAlgebraTools

  Cette classe n'est compilée que si boost est détecté par cmake.
  Voir cmakedefine et le fichier config.hpp.in

**/
class linearAlgebraTools
{
private : 
  /** Matrice boost */
  LAMatrix _localMatrix;

  /** Dimension de la matrice*/
  unsigned int _size;

public:
  /** Constructeur par défaut : matrice 2X2 intialisée à 0.
   */
  linearAlgebraTools();

  /** Construit une matrice size X size intialisée à 0.
        \param int size : dimension de la matrice
  */
  linearAlgebraTools(unsigned int size);
  
  /** Affichage du contenu de la matrice
   */
  void display();

  /** Taille de la matrice */
  inline unsigned int size(){return _size;};
  
};
#endif
#endif
