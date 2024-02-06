#ifndef INPUT_HPP
#define INPUT_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <string>
using namespace std;

/*classe représentant la matrice du graphe*/
/*valeur -1 s'il n'y a pas de chemins entre les villes*/
/*villes indicées de 0 à n-1*/
/*les pondérations sont des distances entre deux villes ou un temps*/
class Graphe 
{
    private : 
    // on veut récupérer le nombre de villes à traiter 
    int nbrevilles;
    //création de la matrice 
    vector<vector<double>> Matrice;
    public : 
    
    //constructeur 
    // je crée une matrice avec autnat de villes qu'on va traiter et initialiser à -1
    Graphe(int nbrevilles): nbrevilles(nbrevilles)
    {
        Matrice.resize(nbrevilles,vector<double>(nbrevilles, -1)); 
    }


    //ajouter les distances entre deux villes 
    //ajouter un coefficient entre la ville i et la ville j
    void dist (int ville_1, int ville_2, double distance)
    {
        if (ville_1 != ville_2) 
       {
        Matrice[ville_1][ville_2]=distance; 
        Matrice[ville_2][ville_1]=distance; 
       } 
    }
    //on met dans les deux sens car le graphe est non orienté 


    //on veut récupérer une distance entre deux villes 
    double poids (int ville_1, int ville_2)
    {
        return Matrice[ville_1][ville_2]; 
    }


    //on peut essayer d'afficher la matrice pour vérifier que toutes les distances sont au bon endroit 
    void affichage()
    {
        cout << "Matrice du graphe :" << endl;

        // En-tête
        cout << "   ";
        for (int i = 0; i < nbrevilles; ++i)
        {
            cout << "Ville " << i << "    ";
        }
        cout << endl;

        // Contenu
        for (int i = 0; i < nbrevilles; ++i)
        {
            cout << "Ville " << i << " ";
            for (int j = 0; j < nbrevilles; ++j)
            {
                
                {
                    cout << Matrice[i][j] << "      ";
                }
            }
            cout << endl;
        }
    }

};


/*classe pour les chemins*/
class Chemin : public Graphe 
{
    public:
    vector <int> villes;

    //constructeur 
    Chemin (vector <int>& chem, int nbrevilles): villes(chem), Graphe(nbrevilles){}

    // calcul de la distance du chemin 
    double calcul(const Graphe& graphe)
    {
        double total=0.0; 
        for (int i=0; i<villes.size()-1;++i)
        {
            total+=poids(villes[i],villes[i+1]);

        }
        total+=poids(villes.back(),villes.front()); //je retourne sur la ville de départ 
        return total;
    }
}; 


   

/*représentation des villes (noms et coordonnées)*/
/*classe qui devra rendre un fihcier pour visualiser le chemin à l'aide de Matlab*/
class Villes
{
    public : 
    string nom; //nom de la ville 
    double x; // abscisse de la ville 
    double y; // ordonnée de la ville 

    //constructeur 
    Villes(const string &nomville, const double a, const double b): nom(nomville), x(a), y(b){}

    //fichier 

}; 

#endif 