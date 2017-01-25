#include "linearAlgebraTools.hpp"
#ifdef HAS_BOOST
linearAlgebraTools::linearAlgebraTools():_size(2)
{
  _localMatrix.resize(_size,_size);
  for (unsigned i = 0; i < _localMatrix.size1 (); ++ i)
        for (unsigned j = 0; j < _localMatrix.size2 (); ++ j)
            _localMatrix (i, j) = 3 * i + j;
}

linearAlgebraTools::linearAlgebraTools(unsigned int size):_size(size)
{
 _localMatrix.resize(_size,_size);
    for (unsigned i = 0; i < _localMatrix.size1 (); ++ i)
        for (unsigned j = 0; j < _localMatrix.size2 (); ++ j)
            _localMatrix (i, j) = 3 * i + j;
}

void linearAlgebraTools::display()
{
      std::cout << _localMatrix << std::endl;
}
#endif
