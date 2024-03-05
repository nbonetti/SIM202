#include <iostream>
#include <fstream>

using namespace std;

void csv_write(int* parcours, int n_index)
{
      std::ofstream myfile;
      myfile.open ("solution.csv");
      myfile << "index\n";
      int x;
      for (int i=0;i<n_index;i++){
            x=parcours[i];
            myfile << x<<endl;
      }
      myfile.close();
}