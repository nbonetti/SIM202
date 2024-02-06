#ifndef VOYAGE_HPP
#define VOYAGE_HPP


#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <string>
using namespace std;

//=========================================================================
//===========================CLASS POINT===================================
class Point 
{
    public:
    double x,y; // se sera les coordonnées des villes
    //constructeur 
    Point(double a, double b): x(a),y(b){}
    void print(ostream& out) const; // affichage 
    //distance entre deux points 
    double dist(const Point&p, const Point &q); 
};


//définition des fonctions 

void Point :: print(ostream& out) const 
{
    out << "(" << x << ","<< y <<")"; 
}

double Point :: dist (const Point&p, const Point&q)
{
    double resultat; 
    resultat=sqrt((p.x-q.x)*(p.x-q.x) + (p.y-q.y)*(p.y-q.y));
    return resultat; 
}
 



 //==============================================================
 //===============================CLASS VILLE====================

class Ville
{
    public: 
    vector<Point> coord; //coordonnées des villes 
    vector<string> nom; // nom de la ville 
    vector<vector<double>> distances; // distances villes sous forme de tableau 
    void print(ostream& out) const; 
    //constructeur
    Ville(const vector<string> &n, const vector <Point> &p): nom(n),coord(p){}
    // calcul de la distance 
    void calcul_distance();
    int nombre_villes()
    {
        return nom.size();
    }; 
};



//définition des fonctions de villes 

void Ville:: print(ostream &out ) const 
{
    int n= nombre_villes();
    out << "["; 
    for (int i=0; i<m-1; ++i)
    {
        out << nom[i] << ",";
    }
    out << nom[m-1]<< "]" << endl; 
}



void Ville :: calcul_distance()
{
    int n= nom.size();
    distances.resize(n,vector<double> (n)); //redimension de la matrice
    for (int i=0; i<n;++i)//lignes
    {
        for (int j=0; j<n;++j)//colonnes
        {
            if (i==j)
            {
                distances[i][j]=0;
            }
            else
            {// on applique à la ieme ligen et jieme colonne la distance entre les deux points (deux villes)
                distances[i][j]= dist(coord[i],coord[j]);
                distances[j][i]= dist(coord[i],coord[j]);
            }
        }
    }
}



//====================================================================
//============================== CLASS CHEMIN ========================
class Chemin : public individu 
{
    public:
    Chemin* crossover ();
    Chemin* mutation (); 
    vector <int> trajet; // liste de villes 
    const Ville* villes; 
    //constructeur 
    Chemin(const vector<int> &t, const Ville &v): trajet(t), villes(v)
    {
        int n =trajet.size(); 
        int r=0; 
        for (int i=1; i<n;++i)
        {
            r=r+v.distances[t[i]][t[i-1]];
        }
    }; 
    Chemin(){}

    void print(ostream&out) const; //afficher les villes dans le chemin
    double poids(const vector<vector<double>>& distances) const; // calcul de la distance totale parcourue dans la tournée 
    double adapter(const vector<vector<double>>& distances ) const //fonction d'adaptation: retourne la distance totale parcourue
    {
        return poids(distances); 
    }
};


//définition des fonctions de chemin 
void Chemin :: print(ostream&out ) const 
{
    int n=trajet.size();
    out << "["; 
    for (int i=0; i<n-1; ++i)
    {
        out << villes->nom[trajet[i]]<<","; 

    }
    out << villes->nom[trajet[n-1]]<<"]"<<endl; 

}


double Chemin :: poids(const vector<vector<double>>& distances) const 
{
    double poid=0;
    int n=villes->nombre_villes();
    for (int i=0;i<n;++i)
    {
        poid+=villes->distances[trajet[i]][trajet[i-1]];
    }
    poids+=distances[trajet.back()][trajet[0]];
    return poids; 
}












#endif