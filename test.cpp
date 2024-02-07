#include "algogenetique.hpp"
using namespace std;

int main()
{
    Individu *child1 = FactoryMethod(CheminType);
    child1->print(cout);

    return (0);
}