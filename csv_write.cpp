#include <iostream>
#include <fstream>
int main( int argc, char* argv[] )
{
      std::ofstream myfile;
      myfile.open ("solution.csv");
      myfile << "index\n";
      myfile << "4\n";
      myfile << "3\n";
      myfile << "1\n";
      myfile << "2\n";
      myfile.close();
      return 0;
}