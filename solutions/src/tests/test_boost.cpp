#include "tools_interface.hpp"
#include <iostream>

int main(void)
{
  int info = 1;
  #ifdef HAS_BOOST
  linearAlgebraTools latools(3);
  latools.display();
  
  // Si tout se passe bien info = 0
  if (latools.size() == 3)
  {
    std::cout << latools.size() << std::endl;
    info = 0;
  }
  #endif
  return info;
  
}
