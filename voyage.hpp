#ifndef VOYAGE_HPP
#define VOYAGE_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <string>
#include "algogenetique.hpp"
#include <list>
using namespace std;

//==================================================================================================================
//===========================CLASS POINT============================================================================
class Point
{
public:
    double x, y; // se sera les coordonnées des villes
    // constructeur par défaut
    Point() : x(0), y(0) {}
    // constructeur
    Point(double a, double b) : x(a), y(b) {}
    void print(ostream &out) const; // affichage
    // distance entre deux points
    double dist(const Point &p, const Point &q);
};

// définition des fonctions

void Point ::print(ostream &out) const
{
    out << "(" << x << "," << y << ")";
}

double Point ::dist(const Point &p, const Point &q)
{
    double resultat;
    resultat = sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
    return resultat;
}

//========================================================================================================
//===============================CLASS VILLE==============================================================

class Ville : public Point
{
public:
    vector<Point> coord;              // coordonnées des villes
    vector<int> nom;                  // nom de la ville en vecteur
    vector<vector<double>> distances; // distances villes sous forme de tableau
    void print(ostream &out) const;
    // constructeur générique de ville
    Ville(){};
    // constructeur
    Ville(const vector<int> &n, const vector<Point> &p) : nom(n.size()), coord(p.size())
    {
        for (int i = 0; i < p.size(); ++i)
        {
            coord[i] = p[i];
        }
        for (int i = 0; i < n.size(); ++i)
        {
            nom[i] = n[i];
        }
    }
    // calcul de la distance
    void calcul_distance();
    int nombre_villes() const
    {
        return nom.size();
    };
};

// définition des fonctions de villes

void Ville::print(ostream &out) const
{
    int n = nombre_villes();
    out << "[";
    for (int i = 0; i < n - 1; ++i)
    {
        out << nom[i] << ",";
    }
    out << nom[n - 1] << "]" << endl;
}

void Ville ::calcul_distance()
{
    int n = nom.size();
    distances.resize(n, vector<double>(n)); // redimension de la matrice
    for (int i = 0; i < n; ++i)             // lignes
    {
        for (int j = 0; j < n; ++j) // colonnes
        {
            if (i == j)
            {
                distances[i][j] = -1;
            }
            else
            { // on applique à la ieme ligen et jieme colonne la distance entre les deux points (deux villes)
                distances[i][j] = dist(coord[i], coord[j]);
                distances[j][i] = dist(coord[i], coord[j]);
            }
        }
    }
}

//=========================================================================================================================
//============================== CLASS CHEMIN =============================================================================

class Chemin : public Individu
{
    /*on a dans protected le nombre de genes et le vecteur de genes
    qui ici dans la classe chemin représente le nombre de villes
    et le numéro des villes présentes dans le chemin */
public:
    static Ville vsp;
    Chemin()
    {
        type = IndividuType::CheminType;
    };
    Chemin(vector<double> premiersGenes) : Individu(premiersGenes)
    {
        type = IndividuType::CheminType;
    };
    Chemin(const Chemin &c) : Chemin(c.genes){}

    void print(ostream &out) const; // afficher les villes dans le chemin
    double poids() const;           // calcul de la distance totale parcourue dans la tournée (adaptation)
    ~Chemin(){};                    // deconstructeur

    Individu *mutationPermutation()
    {
        return Individu::mutationPermutation();
    }
    Individu *clone() const;
    Chemin *clone();
    static void setVille(const Ville& v)
    {
        vsp = v;
    }
};

// définition des fonctions de chemin
void Chemin::print(ostream &out) const
{
    cout << "[";
    for (int i = 0; i < nombreGenes; i++) // Itérer jusqu'à nombreGenes
    {
        out << genes[i];
        if (i < nombreGenes - 1) // Ajouter une virgule si ce n'est pas le dernier élément
        {
            out << ", ";
        }
    }
    out << "]" << endl;
}

double Chemin::poids() const
{
    double poid = 0;
    int n = nombreGenes;
    for (int i = 0; i < n - 1; ++i)
    {
        poid = poid + vsp.distances[genes[i]][genes[i + 1]];
    }
    poid = poid + vsp.distances[genes.back()][genes[0]];
    return poid;
}
Individu *Chemin::clone() const
{
    return new Chemin(*this);
}

Chemin *Chemin::clone()
{
    return new Chemin(*this);
}

//==========================================================================
//                              FONCTION A PART
//==========================================================================
/*dans notre cas on va avoir un fichier avec plusieurs villes, on va donc pouvoir générer plien de chemins possibles et il faut donc que l'on génère une population
avec tous ces chemins possibles*/

/*Population &generateur_chemins(int nombre_chemins, const Ville city, Population &P)
{
    Chemin::setVille(city);
    
    srand(time(NULL));

    for (int j = 0; j < nombre_chemins; j++)
    {
        list<int> indice;
        vector<double> trace;//vecteur pour stocker le chemin 

        // Remplissage du vecteur d'indices
        for (int i = 0; i < city.nombre_villes(); i++)
        {
            indice.push_back(i);
        }
        // Génération du chemin :
        for (int k = 0; k < city.nombre_villes(); k++)
        {
            int r = rand() % indice.size();
            // on enlève d'indice
            list<int>::iterator itr = indice.begin();
            advance(itr, r);

            trace.push_back(*itr);
            indice.erase(itr);
        }

        Chemin *path = new Chemin(trace);
        P.addIndividu(path);
    }
    return P;
}*/
//changement de la fonction pour tester les contraintes et ne pas prendre deux fois la meme ville 
Population generateur_chemins(int nombre_chemins, const Ville& city, Population& P) {
    Chemin::setVille(city);
    srand(time(NULL));

    for (int j = 0; j < nombre_chemins; j++) {
        vector<double> trace; // Vecteur pour stocker le chemin

        vector<bool> visited(city.nombre_villes(), false); // Indique si une ville a été visitée

        // Choisir une ville de départ aléatoire
        int currentCityIndex = rand() % city.nombre_villes();
        trace.push_back(currentCityIndex);
        visited[currentCityIndex] = true;

        // Construire le chemin en sélectionnant aléatoirement une ville non visitée à chaque étape
        while (trace.size() < city.nombre_villes()) {
            // Construire une liste de villes non visitées
            vector<int> availableCities;
            for (int i = 0; i < city.nombre_villes(); ++i) {
                if (!visited[i]) {
                    availableCities.push_back(i);
                }
            }

            // Choisir aléatoirement une ville non visitée parmi les villes disponibles
            int nextCityIndex = availableCities[rand() % availableCities.size()];

            // Vérifier si le chemin entre la ville courante et la prochaine ville n'est pas déjà dans le chemin
            if (nextCityIndex != currentCityIndex) {
                trace.push_back(nextCityIndex);
                visited[nextCityIndex] = true;
                currentCityIndex = nextCityIndex;
            }
        }

        // Ajouter la première ville à la fin pour fermer la boucle
        trace.push_back(trace.front());

        Chemin* path = new Chemin(trace);
        P.addIndividu(path);
    }

    return P;
}



#endif