function [] = Select_villes(Coord,n)
%SELECT_VILLES Choisi un nombre n de villes parmis les 93 de la base de
%données. Renvoie un tableau de taille 3 x n representant l'index de la ville puis ses
%coordonnées 
%   Detailed explanation goes here

Index=randperm(93,n);  %On prend n villes distinctes parmis les 93 de la base de données

Villes=zeros(n,2);

for i=1:n
    Villes(i,1)= Index(i);
    Villes(i,2)= Coord(Index(i),1);
    Villes(i,3)= Coord(Index(i),2);
end 

csvwrite("Villes_csv",Villes);

end

%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%
