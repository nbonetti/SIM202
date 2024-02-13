#ifndef VOYAGE_HPP
#define VOYAGE_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <string>
#include "algogenetique.hpp"
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
    vector<string> nom;               // nom de la ville en vecteur
    vector<vector<double>> distances; // distances villes sous forme de tableau
    void print(ostream &out) const;
    // constructeur générique de ville
    Ville(){};
    // constructeur
    Ville(const vector<string> &n, const vector<Point> &p) : nom(n), coord(p.size())
    {
        for (int i = 0; i < p.size(); ++i)
        {
            coord[i] = p[i];
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
                distances[i][j] = 0;
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
    const Ville *vsp;
    Chemin()
    {
        type = IndividuType::CheminType;
        vsp = &Ville();
    };
    Chemin(vector<double> premiersGenes, const Ville &v) : Individu(premiersGenes), vsp(&v)
    {
        type = IndividuType::CheminType;
        int n = nombreGenes;
        int r = 0;
        for (int i = 1; i < n; ++i)
        {
            r = r + vsp->distances[genes[i]][genes[i - 1]];
        }
    };
    void print(ostream &out) const; // afficher les villes dans le chemin
    double poids() const;           // calcul de la distance totale parcourue dans la tournée (adaptation)
    ~Chemin(){};                    // deconstructeur
};

// définition des fonctions de chemin
void Chemin ::print(ostream &out) const
{
    cout << "[";
    for (int i = 0; i < nombreGenes - 1; i++)
    {
        out << genes[i] << ", ";
    }
    out << genes[nombreGenes - 1] << "]" << endl;
}

double Chemin ::poids() const
{
    double poid = 0;
    int n = nombreGenes;
    for (int i = 0; i < n; ++i)
    {
        poid += vsp->distances[genes[i]][genes[i - 1]];
    }
    poid += vsp->distances[genes.back()][genes[0]];
    return poid;
}

//=========================================================================================
//=================================SELECTION===============================================
/*population selection_roulette(population&P,int p);

population selection_roulette(population&P,int p)
{
    population Q(p);//population à retourner
    vector<double> vdist;
    vector<double> vdist_temp;
    double s=0; //somme de toutes les fonctions d'adaptation d'une population
    vector <int> rang ;

    int n= P.individu.size();
    for (int i=0;i<n;++i)
    {
        vdist.push_back(P.individu[i]->poids());
        s=s+P.individu[i]->poids();
        rang.push_back(i);
    }

     for (int j=0;j<p;j++) {
        int a=0;
        double r=s*((double) rand() / (RAND_MAX));// génère aléatoirement suivant une loi uniforme
        double S_temp=0;
        while (S_temp<r) { //on somme les fonctions jusqu'à atteindre la valeur r
            S_temp= S_temp + vdist[rang[a]];
            a=a+1;
        }
        Q.individu.push_back(P.individu[rang[a]]);
        rang.erase(rang.begin()+a);
    }
    return Q;// dernier individu qui a contribué à cette somme


}


population selection_rang(const population&P, int p);
population selection_rang(const population&P, int p)
{

}*/

#endif