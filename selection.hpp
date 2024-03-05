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

// selection par rang
Population selection_rang(Population &Pop_initiale)
{
    // Triez la population en fonction de la fonction d'adaptation
    Pop_initiale.trierPopulation(&Individu::poids);

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

// sélection par eugénisme

Population select_eugenisme(Population &P, int p)
{
    // Trier par la fonction d'adaptation (le plus faible est le mieux)
    sort(P.getIndividus().begin(), P.getIndividus().end(), [](const Individu *a, const Individu *b)
         { return a->poids() < b->poids(); });

    // Séléctionner le meilleur pourcentage p% d'individus reproducteurs
    int n = P.getTaillePopulation();
    int m = (int)((double)p) / 100.0 * (double)n;
    Population Q(m);

    for (int i = 0; i < m; i++)
    {
        *Q.getIndividu(i) = *(P.getIndividu(i)->clone());
    }

    return Q;
}

// Sélection par roulette

Population select_roulette(Population &P, int p)
{
    srand(time(0));
    Population P_select(p);
    vector<double> vdist;
    vector<double> vdist_temp;
    double S = 0;
    vector<int> rang;

    // Remplissage des vecteurs des longueurs des individus et de leur rang, et calcul de la somme des fonctions d'adaptation
    for (int i; i < P.getTaillePopulation(); i++)
    {
        vdist.push_back(P.getIndividu(i)->poids());
        S = S + P.getIndividu(i)->poids();
        rang.push_back(i);
    }

    // Sélection par roulette avec la fonction d'adaptation

    for (int j = 0; j < p; j++)
    {
        int a = 0;
        double r = S * ((double)rand() / (RAND_MAX));
        double S_temp = 0;
        while (S_temp < r)
        {
            S_temp = S_temp + vdist[rang[a]];
            a = a + 1;
        }
        P_select.getIndividus().push_back(P.getIndividu(rang[a]));
        rang.erase(rang.begin() + a);
    }
    return P_select;
}

// Sélection par rang

Population select_rang(Population &P, int p)
{
    srand(time(0));
    Population P_select(p);
    vector<double> vdist;
    vector<double> vdist_temp;
    int S = 0;
    vector<int> rang;

    // Remplissage de vecteurs de fonctions d'adaptation puis tri

    for (int i; i < P.getTaillePopulation(); i++)
    {
        vdist.push_back(P.getIndividu(i)->poids());
        vdist_temp.push_back(P.getIndividu(i)->poids());
        S = S + i;
        rang.push_back(i);
    }
    sort(vdist.begin(), vdist.end());

    // Tri des individus du plus mauvais au meilleur
    int index = 0;
    for (int j; j < P.getTaillePopulation(); j++)
    {
        index = findIndex(vdist_temp, vdist[j]);
        *P.getIndividu(P.getTaillePopulation() - 1 - j) = *P.getIndividu(index);
    }

    // Sélection par roulette avec la fonction de rang
    for (int k = 0; k < p; k++)
    {
        int l = rand() % S;
        int S_temp = 0;
        int a = 0;
        while (S_temp < l)
        {
            S_temp = S_temp + rang[a];
            a = a + 1;
        }
        P_select.getIndividus().push_back(P.getIndividu(rang[a]));
        rang.erase(rang.begin() + a);
    }
    return P_select;
}

#endif