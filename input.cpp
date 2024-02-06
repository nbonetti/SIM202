#include "input.hpp"
int main()
{
    // Création du graphe
    Graphe graphe(4);

    // Ajout des distances entre les villes
    graphe.dist(0, 1, 2.0);
    graphe.dist(1, 2, 3.0);
    graphe.dist(2, 3, 1.5);
    graphe.dist(3, 0, 4.0);

    // Affichage de la matrice du graphe
    graphe.affichage();

    // Création d'un chemin
    vector<int> chemin{0, 1, 2, 3};

    // Création de l'objet Chemin en utilisant le chemin et le graphe
    Chemin cheminObjet(chemin, 4);

    // Calcul de la distance du chemin
    double distanceChemin = cheminObjet.calcul(graphe);

    // Affichage de la distance du chemin
    cout << "Distance du chemin : " << distanceChemin << endl;

    // Création de quelques villes
    Villes ville1("Ville A", 0.0, 0.0);
    Villes ville2("Ville B", 1.0, 1.0);

    // Vous pouvez ajouter plus de villes si nécessaire...

    return 0;
}
