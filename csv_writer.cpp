#include <iostream>
#include <fstream>

int main( int argc, char* argv[] ){
    int Index_Ville;
      std::ofstream myfile;
      myfile.open ("example.csv");
      for (int i=0;i<nb_villes;i++){
        Index_Ville=index[i];
        myfile << "Index_Ville\n";
      }
      myfile.close();
      return 0;
}