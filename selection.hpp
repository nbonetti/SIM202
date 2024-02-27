#ifndef SELECTION_HPP
#define SELECTION_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <random>
#include <random>

#include "algogenetique.hpp"
#include "voyage.hpp"
#include "Factory.hpp"

// prend en argument une population P et une fonction d'adaptationn et retourne 1 seul individu sélectionné de cette population
Individu *selection_roulette_unique(Population &P, double (Individu::*pointeur_fct_poids)() const)
{
    int p = P.getTaillePopulation();
    vector<double> vdist;
    double s = 0.0; // somme de toutes les fonctions d'adaptation d'une population

    // Calcul de la somme des fonctions d'adaptation et initialisation des vecteurs
    for (int i = 0; i < P.getTaillePopulation(); ++i)
    {
        Individu *individu = P.getIndividu(i);
        if (individu)
        {
            vdist.push_back((individu->*pointeur_fct_poids)());
            s += (individu->*pointeur_fct_poids)();
        }
    }

    // recherche du rang dans la population de l'individu recherché
    int a = 0;
    // Sélection des individus par roulette
    for (int j = 0; j < p; ++j)
    {

        double r = s * ((double)rand() / RAND_MAX); // génère aléatoirement suivant une loi uniforme
        double S_temp = 0.0;

        // Recherche du rand de l'individu sélectionné appelé a
        while (S_temp < r && a < p)
        {
            S_temp += vdist[a];
            ++a;
        }
    }
    // individu sélectionné
    return (P.getIndividu(a));
}

Population selection_roulette(int n, Population &Pop_initiale, double (Individu::*pointeur_fct_poids)() const)
{
    Population P_finale;
    while (P_finale.getTaillePopulation() < n)
    {
        Individu *individu_selectionne = selection_roulette_unique(Pop_initiale, pointeur_fct_poids);
        P_finale = P_finale + Population({individu_selectionne});
    }

    return (P_finale);
};

#endif