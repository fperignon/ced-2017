#include "tools.hpp"

using namespace std;

tools::tools():a(0),b(0)
{
  cout << "Appel du constructeur par defaut de tools." << endl;
}

bool tools::set_tools(int val_a, int val_b)
{
  a = val_a; b = val_b;
  cout << "appel de set_tools." << endl;
  return true;
}

void tools::affiche() const
{
  cout << "Tools: a = "<< a << ", b = "<< b << endl;
}
