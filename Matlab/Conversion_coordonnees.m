function [Coord] = Conversion_coordonnees_bis(LON,LAT)
%On convertit ici des coordonnées données en format DMS
%(degrés/minutes/secondes) en Coordonnées "brut". Autrement dit, on trouve
%la valeur exacte de la latitude

n=length(LON);

for i=1:n
%On converti les nb en chaine de caractère pour pouvoir isoler les degrés, 
%minutes, secondes de la latitude/longitude
strlon=num2str(LON(i));
strlat=num2str(LAT(i));

%Ici, on va regarder si la première valeur de la chaine de caractère est un
%moins. Si c'est le cas, il faudra l'encoder dans la chaine de caractère
%(et il faudra donc une place de plus). 
%De plus, pour que notre programme focntionne, il faut avoir un format de 6
%chiffres : 2 pour les degrés, 2 pour les minutes et 2 pour les secondes



if (strlon(1)=='-') 
    strlon=num2str(LON(i),'%07.f');
else
    strlon=num2str(LON(i),'%06.f');
end 
%Seuls les latitudes peuvent être négatives au niveau de la France donc on
%fait le traitement pour conserver le '-' seulement pour celles-ci
    


nlon=length(strlon);
nlat=length(strlat);

%Les degrés de latitude et longitude en France étant inférieur à +-100, on
%a deux nombres pour les définir. Ainsi, 2 nombres pour les degrés, 2 pour
%les minutes et 2 pour les secondes. Les chaines de caractères définis
%précedemment sont donc soit de 6 caractère (lorsque le degré est positif,
%soit de 7 lorsque l'on a le moins en position 1).


sec(i,1)=str2num(strlon(nlon-1:nlon));sec(i,2)=str2num(strlat(nlat-1:nlat));
min(i,1)=str2num(strlon(nlon-3:nlon-2));min(i,2)=str2num(strlat(nlat-3:nlat-2));
deg(i,1)=str2num(strlon(nlon-5:nlon-4));deg(i,2)=str2num(strlat(nlat-5:nlat-4));



LONGITUDE(i)=deg(i,1)+min(i,1)*(1/60)+sec(i,1)*(1/3600);
LATITUDE(i)=deg(i,2)+min(i,2)*(1/60)+sec(i,2)*(1/3600);

if nlon==7
    LONGITUDE(i)=-LONGITUDE(i);
    
end

Coord(i,1) = LONGITUDE(i);
Coord(i,2) = LATITUDE(i);
end

end


