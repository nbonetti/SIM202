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

void Population::trierPopulation(double (Individu::*pointeur_fct_poids)() const)
{
    // Utilisez std::sort pour trier la population en fonction de la fonction de poids
    sort(individus.begin(), individus.end(), [pointeur_fct_poids](const Individu *a, const Individu *b)
         { return (a->*pointeur_fct_poids)() < (b->*pointeur_fct_poids)(); });
}

// selection par rang
Population selection_rang(Population &Pop_initiale)
{
    // Triez la population en fonction de la fonction d'adaptation
    Pop_initiale.trierPopulation(&Population::poids);

    int p = Pop_initiale.getTaillePopulation();
    std::vector<double> probSelection(p);
    double sommeProb = 0.0;

    // Attribuer un rang à chaque individu (1 pour le plus mauvais)
    for (int i = 0; i < p; ++i)
    {
        probSelection[i] = static_cast<double>(p - i) / (p * (p + 1) / 2);
        sommeProb += probSelection[i];
    }

    // Sélection d'individus par rang
    Population P_finale;

    for (int i = 0; i < p; ++i)
    {
        double r = sommeProb * ((double)rand() / RAND_MAX);
        double S_temp = 0.0;
        int a = 0;

        while (S_temp < r && a < p)
        {
            S_temp += probSelection[a];
            ++a;
        }

        Individu *individu_selectionne = Pop_initiale.getIndividu(a - 1); // a - 1 car les indices commencent à 0
        P_finale = P_finale + Population({individu_selectionne});
    }

    return P_finale;
}

#endif