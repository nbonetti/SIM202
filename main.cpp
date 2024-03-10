#include <cmath>
#include <cstdlib>
#include <vector>
#include <random>
#include <ctime>
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include "algogenetique.hpp"
#include "voyage.hpp"
#include "Factory.hpp"
#include "selection.hpp"
#include "csv.hpp"
using namespace std;

Ville Chemin::vsp;

template <typename T>
std::string getTypeName(const T &variable)
{
    return typeid(variable).name();
}
Population algogenetique(Population &Pop_initiale, int nb_iter, int nb_reproducteurs)
{

// Génération de la population initiale avec des chemins corrects
    Population population_initiale;
    int nombre_chemins = Pop_initiale.getTaillePopulation(); // Nombre de chemins à générer
    Ville city; // Définissez votre objet Ville avec les coordonnées des villes
    population_initiale = generateur_chemins(nombre_chemins, city, Pop_initiale);

    //====================================================================================================================================
    //                          initialisation
    //====================================================================================================================================

    int k = 0;
    // nb de parents nécessaires pour que la population après reproduction et sélection garde la même taille intiale
    int nb_parents_conserves = Pop_initiale.getTaillePopulation() - nb_reproducteurs;

    Population population_parents = Pop_initiale;
    Population parents_selectionnes;
    Population enfants;
    Population parents_conserves;

    //====================================================================================================================================
    //                          iteration jusqu'à fin (critère d'arret )
    //====================================================================================================================================
    while (k < nb_iter)
    {
        //====================================================================================================================================
        //                          SELECTION DES REPRODUCTEURS
        //====================================================================================================================================

        // proba de gagner lors de la selection par tournoi
        double proba_tournoi;

        // parents_selectionnes = selection_eugenisme(population_parents, nb_reproducteurs);
        //  parents_selectionnes = selection_roulette(population_parents, nb_reproducteurs);
        parents_selectionnes = selection_rang(population_parents, nb_reproducteurs);
        // parents_selectionnes = selection_tournoi(population_parents, nb_reproducteurs, proba_tournoi);

        //====================================================================================================================================
        //                          REPRODUCTION DES ENFANTS + MUTATION
        //====================================================================================================================================
        // il faut choisir la mutation appliquée aux enfants
        // enfants des parents issus de la sélection
        enfants = reproduction(parents_selectionnes, FactoryMethod, CheminType);

        // mutation des enfants
        for (int i = 0; i < nb_reproducteurs; i++)
        {
            Individu* enfant =enfants.getIndividu(i);
            enfant->mutationAleatoire();
            //enfants.getIndividu(i)->mutationAleatoire();
            // enfants.getIndividu(i)->mutationPermutation();
            int s=0;
            while (!enfant->respecteContraintes() && s<1000)
            {
                // Générer un nouvel enfant à la place de l'enfant non conforme
                enfants.remplacerIndividu(i, reproduction(parents_selectionnes, FactoryMethod, CheminType).getIndividu(0));
                enfant = enfants.getIndividu(i);
                enfant->mutationAleatoire(); // Effectuer une mutation sur le nouvel enfant
                ++s; 
            }
        }

        //====================================================================================================================================
        //                          COMPLEMENT DE LA POPULATION ENFANTS POUR CONSERVER LE NB D'INDIVIDUS
        //====================================================================================================================================

        // à définir si sélection par tournoi
        double proba_tournoi_conserves;
        // sélection des parents que l'on va conservés pour la prochaine génération
        // parents_conserves = selection_eugenisme(population_parents, nb_reproducteurs);
        //parents_conserves = selection_roulette(population_parents, nb_parents_conserves);
        //parents_conserves = selection_rang(population_parents, nb_parents_conserves);
        parents_conserves = selection_tournoi(population_parents, nb_parents_conserves, proba_tournoi_conserves);

        enfants = enfants + parents_conserves;

        //====================================================================================================================================
        //                         ITERATEURS
        //====================================================================================================================================

        population_parents = enfants;
        k = k + 1;
    };

    // la population finale est
    Population pop_finale = population_parents;

    return pop_finale;
};

int main()

{

    //=========================================================================================================
    //                                             LECTURE DU FICHIER
    //==========================================================================================================

    vector<vector<double>> content = csv_reader("Villes_csv"); // on récupère le fichier

    //========================================================================================
    //                                      DEBUT
    //========================================================================================

    vector<int> citynumber; // index des villes dans le fichier
    vector<Point> coord;    // coordonées (x,y)

    for (const auto &row : content)
    {
        //cout << row[0];
        citynumber.push_back(row[0]);           // Première colonne : indices
        coord.push_back(Point(row[1], row[2])); // Deuxième et troisième colonnes : coordonnées x et y
    }
    // création de l'objet ville
    Ville city(citynumber, coord);
    city.calcul_distance();
    city.print(cout);
    cout << "Distances between cities:" << endl;
    for (const auto &row : city.distances)
    {
        for (double dist : row)
        {
            cout << dist << "\t";
        }
        cout << endl;
    }
    Chemin::setVille(city);

    //==============================================================================
    //                                  RESOLUTION
    //==============================================================================
    Population paths;        // population initiale avec tou sles chemins possibles avec le fichier de départ
    int nombre_chemins = 10; // choisir le nombre de chemins que l'on veut dans notre population

    // faire une fonction qui génère la population totale avec tous les chemins possibles avec le fichier de départ
    Population generee = generateur_chemins(nombre_chemins, city, paths); // initialisation
    printf("population generee=");
    generee.print(cout);

    //paths.print(cout);

    int nombre_iterations = 4;
    int nombre_reproducteurs = 10;

    Population resultat = algogenetique(generee, nombre_iterations, nombre_reproducteurs);
    Population resultat_2 = trierPopulation(resultat);
    printf("resultat_2=");
    resultat_2.print(cout);
    Individu *I = resultat_2.getIndividu(0); // je prends le chemin avec le poids le plus petit
    vector<double> sol = I->genes;

    //===========================================================================================
    //                                       SORTIE
    //===========================================================================================
    csv_write(sol);

    return 0;
}

