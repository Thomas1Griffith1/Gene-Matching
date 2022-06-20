#include <stdio.h>
#include <dirent.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <math.h>
#include <string>
#include <cmath>
#include <string.h>
#include <fstream>
#include "compareGenes.h"
using namespace std;





int main (void)
{
      compareGenes compareClass;

      vector<pair<string,string>> Species;
      vector<string> specie;
      vector<string> genes;
      string speciesName;
      string GeneticCode = "";
      ifstream myReadFile;
      myReadFile.open("sequences.txt");
      string line;
      bool foundAnimal = false;
      bool first = true;

      if (myReadFile.is_open()){

            while (getline(myReadFile,line)) {
                  //see if it is an animal name
                  if(line[0] == '-' )
                  {
                        //it if the first animal name just store the name for now
                        if(first)
                        {
                              speciesName = line.substr(2,line.length());
                              first = false;
                              foundAnimal = true;
                        }
                        else{
                                    //create a vector of a animal name and its genetic code and reset variables
                                    Species.push_back(make_pair(speciesName,GeneticCode));
                                    foundAnimal = false;
                                    GeneticCode = "";
                                    speciesName = line.substr(2,line.length());
                                    foundAnimal = true;


                        }
                  }else{
                        //store lines of genetic code if not a name
                        GeneticCode+=line;
                  }


            }
            //store the last animal name
Species.push_back(make_pair(speciesName,GeneticCode));


      }



//call other class to get answer
      compareClass.getSpeciesAndGenes(Species);

}
