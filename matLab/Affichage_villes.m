function [outputArg1,outputArg2] = Affichage_villes(tab_csv_chemin)
%AFFICHAGE_VILLES Summary of this function goes here
%   Detailed explanation goes here

file=readtable('tab_csv_chemin','PreserveVariableNames', true);

% tab_csv_chemin contient l'index des villes + la résolution du pb c'est à
% dire l'ordre dans laquelleles villes sont parcourus. Ce programme fait
% comme si on avait une matrice à 2 colonnes : la première étant l'index
% des villes, la deuxième étant leur ordre de parcours. 
% 



outputArg1 = inputArg1;
outputArg2 = inputArg2;
end

