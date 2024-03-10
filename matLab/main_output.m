clear all

%Acquisition du tableau renvoyé par l'algorithme génétique 
Villes=readtable('solution.csv','PreserveVariableNames',true);
file=readtable('93 villes France.csv','PreserveVariableNames', true);

%On a dans ce tableau une colonne donnant l'index des villes(la première).
%Puis la dexième donnant l'ordre dans lequel on les parcours.
Index=Villes.index;

LON=file.LongitudeDMS;
LAT=file.LatitudeDMS;
[Coord]=Conversion_coordonnees_bis(LON,LAT);

X=Coord(:,1);
Y=Coord(:,2);

n=length(Index);
geoplot(Y(Index(1)),X(Index(1)),".")
for i=1:(n-1)
    geoplot([Y(Index(i)) Y(Index(i+1))],[X(Index(i)) X(Index(i+1))],'-*')
    
    hold on
end
geoplot([Y(Index(n)) Y(Index(1))],[X(Index(n)) X(Index(1))],'-*') %Il ne faut pas oublier que l'on cherche à revenir au point de départ
geolimits([41 54],[-5 10])


geobasemap streets