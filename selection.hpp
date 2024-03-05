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


//sélection par eugénisme

population select_eugenisme(population& P, int p) 
{
    // Trier par la fonction d'adaptation (le plus faible est le mieux)
    sort(P.individus.begin(), P.individus.end(), [](const individu* a, const individu* b) {
        return a->coute() < b->coute();
    });
    
    // Séléctionner le meilleur pourcentage p% d'individus reproducteurs
    int n = P.individus.size();
    int m = (int) ((double) p)/100.0 * (double) n;
    population Q(m);

    for (int i = 0; i < m; i++) {
        Q.individus[i] = P.individus[i]->clone();
    }
    
    return Q;
}

//Sélection par roulette

population select_roulette(population &P, int p) {
    srand(time(0));
    population P_select(p);
    vector<double> vdist;
    vector<double> vdist_temp;
    double S=0;
    vector<int> rang;

    //Remplissage des vecteurs des longueurs des individus et de leur rang, et calcul de la somme des fonctions d'adaptation
    for (int i;i<P.individus.size();i++) {
        vdist.push_back(P.individus[i]->coute());
        S=S+P.individus[i]->coute();
        rang.push_back(i);
        }

    //Sélection par roulette avec la fonction d'adaptation 

    for (int j=0;j<p;j++) {
        int a=0;
        double r=S*((double) rand() / (RAND_MAX));
        double S_temp=0;
        while (S_temp<r) {
            S_temp= S_temp + vdist[rang[a]];
            a=a+1;
        }
        P_select.individus.push_back(P.individus[rang[a]]);
        rang.erase(rang.begin()+a);
    }
    return P_select;
}

//Sélection par rang

population select_rang(population &P, int p) {
    srand(time(0));
    population P_select(p);
    vector<double> vdist;
    vector<double> vdist_temp;
    int S=0;
    vector<int> rang;

    //Remplissage de vecteurs de fonctions d'adaptation puis tri

    for (int i;i<P.individus.size();i++) {
        vdist.push_back(P.individus[i]->coute());
        vdist_temp.push_back(P.individus[i]->coute());
        S=S+i;
        rang.push_back(i);
        }
    sort(vdist.begin(), vdist.end());

    //Tri des individus du plus mauvais au meilleur
    int index=0;
    for (int j;j<P.individus.size();j++) {
        index = findIndex(vdist_temp, vdist[j]);
        P.individus[P.individus.size()-1-j]=P.individus[index];
        }

    //Sélection par roulette avec la fonction de rang
    for (int k=0;k<p;k++) {
        int l= rand() % S;
        int S_temp=0;
        int a=0;
        while (S_temp<l) {
            S_temp=S_temp+rang[a];
            a=a+1;
        }
        P_select.individus.push_back(P.individus[rang[a]]);
        rang.erase(rang.begin()+a);

    }
    return P_select;

}


#endif