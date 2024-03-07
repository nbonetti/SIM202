#include <cmath>
#include <cstdlib>
#include <vector>
#include <random>
#include <ctime>
#include <list>
#include <iostream>
#include <fstream>
#include <string>

#include "algogenetique.hpp"
#include "voyage.hpp"
#include "Factory.hpp"
#include "selection.hpp"
#include "csvreader.hpp"
using namespace std;


int main()

{/*=========================================================================================================
//                                             LECTURE DU FICHIER 
//==========================================================================================================
*/
    vector<vector<double>> content= csv_reader("Villes_csv");//on récupère le fichier 

//========================================================================================
//                                      DEBUT 
//========================================================================================


    vector<int> citynumber;//index des villes dans le fichier 
    vector<Point> coord;//coordonées (x,y)
    
    for (const auto &row : content)
    {
        citynumber.push_back(row[0]); // Première colonne : indices
        coord.push_back(Point(row[1], row[2])); // Deuxième et troisième colonnes : coordonnées x et y
    }
    //création de l'objet ville 
    Ville city(citynumber,coord);
    city.calcul_distance();
    city.print(cout); 

    /*vector<double> vmin;



    



//==============================================================================
//                                  DEBUT 
//==============================================================================
    Population paths;//population initaile avec tou sles chemins possibles avec le fichier de départ 
    int nombre_chemins; //choisir le nombre de chemins que l'on veut dans notre porpulation
    int i = 0;
    int k = 0;
//faire une fonction qui génère la population totale avec tous les chemins possibles avec le fichier de départ 
    generateur_chemins(nombre_chemins,city,paths);
    paths.print(cout);


    Population enfants; 
    int p; //choisir nous mêmes 
    //test d'arrêt 
    while (k<=5 && i<=100)
    {
        //SELECTION DE LA POPULATION  
        Population selection=selection_rang(paths);
        //Population selection=select_roulette(paths,p);
        //Population selection=select_eugenisme(paths,p);
        cout << "\nIndividus sélectionnés pour la reproduction:" << endl;
        selection.print(cout);


        paths.trierPopulation(&Individu::poids);
        Individu* I=paths.getIndividu(0);
        double minimum= I->poids();

        //HYBRIDATION -REPRODUCTION 
        // Reproduction des individus sélectionnés
        enfants = reproduction(selection, FactoryMethod);
        cout << "\nEnfants après reproduction:" << endl;
        enfants.print(cout);


        //MUTATION 
        for (int i = 0; i < enfants.getTaillePopulation(); ++i)
        {
            enfants.getIndividu(i)->mutationPermutation();
        }

        cout << "\nEnfants après mutation:" << endl;
        enfants.print(cout);

        
        



    }*/

    return 0; 
}



