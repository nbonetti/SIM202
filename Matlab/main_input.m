clear all

%Acquisition des données
file=readtable('93 villes France.csv','PreserveVariableNames', true);

%Mise en forme des variables que nous allons utiliser
NAMES=file.Slug;
LON=file.LongitudeDMS;
LAT=file.LatitudeDMS;



% Conversion des coordonnées afin d'avoir des coordonnées en
% latitude/longitude exact pour chaque ville (et non plus un format DMS)
[Coord]=Conversion_coordonnees(LON,LAT);

%Selection de n villes parmis les 93 disponibles dans notre base de données
Select_villes(Coord,10);

