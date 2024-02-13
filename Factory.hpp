#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "voyage.hpp"
#include "algogenetique.hpp"

Individu *FactoryMethod(IndividuType type)
{
    if (type == CheminType)
    {
        return new Chemin;
    }
    else
    {
        return nullptr;
    }
}

Individu *(*pointeur_FactoryMethod)(IndividuType type) = FactoryMethod;

#endif