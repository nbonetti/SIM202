function [Poids] = Poids_chemin(Villes)
%POIDS_CHEMIN Return the matrix of the distance between different cities
%   If n is the number of cities, Poids is a n*n matrix and coord a n*2
%   matrix

X=Villes(:,1);  
Y=Villes(:,2);
n=length(X);
Poids=zeros(n);
for i=1:n
    for j=1:n
        Poids(i,j)=sqrt(((X(i)-X(j))^2)+(Y(i)-Y(j))^2); 
        %On calcule la distance entre chaque point pour remplir la matrice
    end
end
for i=1:n
    Poids(i,i)=-1;
    %On affecte la valeur -1 aux distances nulles

end



