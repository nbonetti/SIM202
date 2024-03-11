clear all

%Acquisition du tableau renvoyé par l'algorithme génétique 
file=readtable('93 villes France.csv','PreserveVariableNames', true);
Villes=readtable('FICHIER_SOLUTION','PreserveVariableNames',true); %Exemple de fichier solutions données dans dossier solution

%On a dans ce tableau une colonne donnant l'index des villes(la première).
%Puis la dexième donnant l'ordre dans lequel on les parcours.
Index=Villes.Chemin_solution;

LON=file.LongitudeDMS;
LAT=file.LatitudeDMS;
[Coord]=Conversion_coordonnees(LON,LAT);

X=Coord(:,1);
Y=Coord(:,2);

n=length(Index);
intIndex=zeros(n,1);

%Fonction pour convertir sortie csv de C++ (contenant une liste de doubles)
%en un vecteur d'entier
for i=1:n
    k=0;
    index=Index(i);
    while k~=index
        k=k+1;
        
    end
    intIndex(i)=k+1; %Dans le fichier retour on part de 0
end


geoplot(Y(intIndex(1)),X(intIndex(1)),".")
for i=1:(n-1)
    geoplot([Y(intIndex(i)) Y(intIndex(i+1))],[X(intIndex(i)) X(intIndex(i+1))],'-*')
    
    hold on
end
geoplot([Y(intIndex(n)) Y(intIndex(1))],[X(intIndex(n)) X(intIndex(1))],'-*') %Il ne faut pas oublier que l'on cherche à revenir au point de départ
geolimits([41 54],[-5 10])


geobasemap streets