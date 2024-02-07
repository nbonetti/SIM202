#include "algogenetique.hpp"
using namespace std;

int main()
{
    IndividuCreator creator;
    Individu *child1 = creator.CreateChemin();
    child1->print(cout);
}