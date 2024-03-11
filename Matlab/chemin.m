function [liste_chemin] = chemin(fichier_chemin)
%Pour utiliser cette fonction, on aura besoin d'avoir récupérer les villes
%visités et leur ordre de visite. Ici, on va manipuler la table Coord pour
%afficher les cordonnées




%CHEMIN Cette fonction a pour but d'afficher les villes que l'on a visité
%avec l'ordre de parcours
%   
table_chemin=readtable(fichier_chemin);
Villes=table_chemin.Ville;
lVilles=length(Villes);

% Ouvrir fichier 93 villes e france avant 
%Faire table des villes pour correspndance (regarder potentiel link des
%tables?
%Tracer d'abord toutes les villes à l'aide du travail fait dans main puis
%les relier dans l'ordre du fichier chemin. 
%Parler des outputs avec nastia, agathe. 
for i=1:(lVilles-1)
    k=Villes(i);
    l=Villes(i+1);
    geoplot([Y(k) Y(l)],[X(k) X(l)],'-*')
    hold on
end
geolimits([41 54],[-5 10]) %Limites longitude/latitude pour la France
geobasemap streets


end

