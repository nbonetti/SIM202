#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "voyage.hpp"
#include "algogenetique.hpp"

// fonction de factory renvoie un pointeur d'individu en fonction du type mis en argument

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

// création du pointeur de la fonction de factory methode (necessaire pour l'hybridation)
Individu *(*pointeur_FactoryMethod)(IndividuType type) = FactoryMethod;

#endif