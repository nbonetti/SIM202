#ifndef VOYAGE_HPP
#define VOYAGE_HPP


#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <string>
using namespace std;



class Point 
{
    public:
    double x,y; // se sera les coordonnées des villes
    //constructeur 
    Point(double a, double b): x(a),y(b){}
    void print(ostream& out) const; // affichage 
};


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


class Chemin : public individu 
{
    public:
    Chemin crossover ();
    Chemin mutation (); 


    vector <int> trajet; // liste de villes 
    const Ville* villes; 
    //constructeur 
    Chemin(const vector<int> &t, const Ville)
}; 
















#endif