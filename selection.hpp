#ifndef SELECTION_HPP
#define SELECTION_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <random>
#include <random>
#include <algorithm>
using namespace std;

#include "algogenetique.hpp"
#include "voyage.hpp"
#include "Factory.hpp"

int findIndex(const vector<double> &arr, double item)
{

    for (auto i = 0; i < arr.size(); ++i)
    {
        if (arr[i] == item)
            return i;
    }

    return -1;
}
// selection par rang p= nb d'individus à sélectionner
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

// sélection par eugénisme p= nb d'individus à sélectionner

Population selection_eugenisme(Population &Pop_initiale, int p)
{
    // Trier par la fonction d'adaptation (le plus faible est le mieux)
    Pop_initiale.trierPopulation(&Individu::poids);

    // Séléctionner le meilleur pourcentage p% d'individus reproducteurs
    int n = Pop_initiale.getTaillePopulation();
    Population P_finale;

    for (int i = n - p; i < n; i++)
    {
        Individu *individu_selectionne = Pop_initiale.getIndividu(i); // a - 1 car les indices commencent à 0
        P_finale = P_finale + Population({individu_selectionne});
    }

    return P_finale;
}

// Sélection par roulette p= nb d'individus à sélectionner

Population selection_roulette(Population &Pop_initiale, int p)
{
    Population P_finale;
    // vecteur des poids aka distances
    vector<double> liste_poids_individu;
    vector<double> liste_poids_temp;

    // somme de tous les poids
    double Somme_poids = 0;

    // vecteur des rangs
    vector<int> rang;

    // Remplissage des vecteurs du poids des individus et de leur rang, et calcul de la somme des fonctions d'adaptation
    for (int i = 0; i < Pop_initiale.getTaillePopulation(); i++)
    {
        liste_poids_individu.push_back(Pop_initiale.getIndividu(i)->poids());
        liste_poids_temp.push_back(Pop_initiale.getIndividu(i)->poids());
        Somme_poids = Somme_poids + Pop_initiale.getIndividu(i)->poids();
        rang.push_back(i);
    }

    // selection roulette
    for (int j = 0; j < p; j++)

    { // k = rang que l'on cherche de l'individu
        int k = 0;
        // double définissant la limite à partir de laquelle on sélectionne 1 individu
        double r = Somme_poids * ((double)rand() / (RAND_MAX));

        // permet itération
        double Somme_temp = 0;

        // Trouver l'indice k sans modifier rang ie le dernier indice avant de dépasser r (aleatoire)
        while (Somme_temp < r)
        {
            Somme_temp = Somme_temp + liste_poids_individu[rang[k]];
            k = k + 1;
        }

        Individu *individu_selectionne = Pop_initiale.getIndividu(rang[k]); // a - 1 car les indices commencent à 0
        P_finale = P_finale + Population({individu_selectionne});
    }

    return P_finale;
};

Population selection_tournoi(Population &Pop_initiale, int nb_individus, double proba_de_WIN)
{
    Population P_finale;
    int taille = Pop_initiale.getTaillePopulation();

    // selection du nombre d'individus voulus

    for (int i = 0; i < nb_individus; i++)
    {
        // selection des deux individus parmi les n individus pour creer un couple de façon aléatoire
        int p = unif_rand(0, taille);
        int q = unif_rand(0, taille);
        Individu *individu_1 = Pop_initiale.getIndividu(p);
        Individu *individu_2 = Pop_initiale.getIndividu(q);

        Individu *best;

        // définit le meilleur individu selon la fonction poids

        if (individu_1->poids() >= individu_2->poids())
        {
            best = individu_1;
        }
        else
        {
            best = individu_2;
        }

        // génère un nombre aléatoire entre 0 et 1
        double random = rand() / RAND_MAX;

        // si le nombre aléatoire est plus grang que la proba définie alors l'individu selectionner est le moins bon sinon c'est le best
        if (random > proba_de_WIN)
        {
            best = individu_2;
        }

        // ajout de l'individu sélectionné dans la population finale
        P_finale = P_finale + Population({best});
    };

    return P_finale;
};

#endif