#include "algogenetique.hpp"
#include "voyage.hpp"
#include "Factory.hpp"
#include "selection.hpp"

using namespace std;

#include <typeinfo>
#include <string>

template <typename T>
std::string getTypeName(const T &variable)
{
    return typeid(variable).name();
}

Population algogenetique(Population &Pop_initiale, int nb_iter, int nb_reproducteurs)
{

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

        // parents_selectionnés = selection_eugenisme(population_parents, nb_reproducteurs);
        // parents_selectionnés = selection_roulette(population_parents, nb_reproducteurs);
        parents_selectionnes = selection_rang(population_parents, nb_reproducteurs);
        // parents_selectionnés = selection_tournoi(population_parents, nb_reproducteurs, proba_tournoi);

        //====================================================================================================================================
        //                          REPRODUCTION DES ENFANTS + MUTATION
        //====================================================================================================================================
        // il faut choisir la mutation appliquée aux enfants
        // enfants des parents issus de la sélection
        enfants = reproduction(parents_selectionnes, FactoryMethod);

        // mutation des enfants
        for (int i = 0; i < nb_reproducteurs; i++)
        {
            enfants.getIndividu(i)->mutationAleatoire();
            // enfants.getIndividu(i)->mutationPermutation();
        }

        //====================================================================================================================================
        //                          COMPLEMENT DE LA POPULATION ENFANTS POUR CONSERVER LE NB D'INDIVIDUS
        //====================================================================================================================================

        // à définir si sélection par tournoi
        double proba_tournoi_conserves;
        // sélection des parents que l'on va conservés pour la prochaine génération
        // parents_conservés = selection_eugenisme(population_parents, nb_reproducteurs);
        // parents_selectionnés = selection_roulette(population_parents, nb_parents_conservés);
        parents_conserves = selection_rang(population_parents, nb_parents_conserves);
        // parents_conservés = selection_tournoi(population_parents, nb_parents_conservés, proba_tournoi_conservés);

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
}

int main()
{
    // Création des données des villes à parcourir
    vector<int> cityNames = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    vector<Point> cityCoords = {Point(0, 0), Point(3, 4), Point(6, 8), Point(10, 5), Point(12, 2), Point(10, 7), Point(14, 1), Point(5, 4), Point(5, 9)}; // coordonnées de chaque ville
    Ville city(cityNames, cityCoords);
    city.calcul_distance();

    // Création de plusieurs chemins initiaux
    vector<vector<double>> paths = {
        {0, 1, 2, 3, 4}, // Chemin 1
        {0, 2, 4, 1, 3}, // Chemin 2
        {0, 2, 3, 4, 1},
        {0, 2, 3, 4, 1},
        {0, 2, 3, 4, 1},
    };

    // Création des individus pour chaque chemin initial
    vector<Individu *> populationInitiale;
    for (auto &path : paths)
    {
        populationInitiale.push_back(new Chemin(path, city));
    }

    // Création de la population initiale
    Population population(populationInitiale);

        Population Pop_finale = algogenetique(population, 5, 5);
    Pop_finale.print(cout);

    // cout << "Population initiale:" << endl;
    // // population.print(cout);
    // cout << " hello taille de pop \n"
    //      << population.getTaillePopulation() << "\n"
    //      << "type de taille " << getTypeName(population.getTaillePopulation());

    // // Sélection des individus pour la reproduction
    // Population selection = selection_rang(population, 4);
    // // Population selection = selection_roulette(population, 2);
    // // Population selection = selection_eugenisme(population, 3);
    // // Population selection = selection_tournoi(population, 2, 0.7);

    // cout << "\nIndividus sélectionnés pour la reproduction:" << endl;
    // selection.print(cout);

    // // Reproduction des individus sélectionnés
    // Population enfants = reproduction(selection, FactoryMethod);

    // cout << "\nEnfants après reproduction:" << endl;
    // enfants.print(cout);

    // // Mutation des enfants
    // for (int i = 0; i < enfants.getTaillePopulation(); ++i)
    // {
    //     enfants.getIndividu(i)->mutationPermutation();
    // }

    // cout << "\nEnfants après mutation:" << endl;
    // enfants.print(cout);

    return 0;
}