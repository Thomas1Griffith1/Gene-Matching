#include <stdio.h>
#include <dirent.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <queue>
#include <math.h>
#include <string>
#include <set>
#include <string.h>
#include <fstream>

using namespace std;

//allow to know where each combination is from
struct numbers
{
      int first;
      int second;
};
//keeps track of the two species and their score
struct relation
{
      string head;
      string other;
      double score = -10000.0;

      //vector<pair<numbers,numbers>> spotsFound;

      bool operator<(const relation& rhs) const
      {
            return score < rhs.score;
      }
};

//holds all relevant information on each species
//including the combinations of its genetic code for comparison
struct Species
{
      string SpecieName;
      string GeneticCode;
      vector<pair<string,numbers>>GeneticVector;
};



class compareGenes{
private:
      //private storage of all relevant information
      vector<Species> SpeciesVector;
public:
      void getSpeciesAndGenes(vector<pair<string,string>> input);
      vector<pair<string,numbers>> misspellWordCount2(string input);
      relation findClosestMatch( Species reference,  Species looker);

};



//sets the variable with all the species and genetic code to look at
//and calls functions to determine what combo it the best and most related
void compareGenes::getSpeciesAndGenes(vector<pair<string,string>> input){

//from the input of a specie name and genetic string make a more accessible struct for them
      for(int x = 0; x < input.size(); x++){
            Species getData;
            //the name
            getData.SpecieName = input[x].first;

            //genetic string
            getData.GeneticCode = input[x].second;
            //genetic vector of combinations
            getData.GeneticVector = misspellWordCount2(input[x].second);
            SpeciesVector.push_back(getData);
      }
      //holds all the answers and best one is on top
      priority_queue<relation> getTheBest;

      //go through all species and compare
      //order matters
      for(int i = 0; i < SpeciesVector.size(); i++)
      {
            int x = i+1;
            while(x < SpeciesVector.size())
            {
                  relation newOne = findClosestMatch(SpeciesVector[i], SpeciesVector[x]);
                  relation newOne2 = findClosestMatch(SpeciesVector[x], SpeciesVector[i]);
                  getTheBest.push(newOne);
                  getTheBest.push(newOne2);
                  x++;
            }
      }




      cout << getTheBest.top().head << "-" <<getTheBest.top().other << ": " <<getTheBest.top().score << endl;


}


/*
 * this function takes a one word string that you will compare
 * with the query but turn it into vector form with every combination
 * of two or more letters in the word
*/
//make a vector of parsed letters for a word
vector<pair<string,numbers>> compareGenes::misspellWordCount2(string input)
{

      vector<pair<string,numbers>> possibleCount;
      int length = input.length();
      //loop that goes through all but the last letter of the string input (word)
      for(int start = 0; start <= length-2; start++)
      {
            //loop to get all the combinations of letters from the first letter from the first loop
            for(int goTill = 2; goTill <= length-start; goTill++)
            {
                  string word = input;
                  numbers numGet;
                  numGet.first = start;
                  numGet.second = start + goTill-1;
                  //get at least 2 letter pairs from word (tess -> te, tes, tess, es, ess, ss)
                  possibleCount.push_back(make_pair(word.substr (start, goTill),numGet));
            }

      }


      return possibleCount;
}











/*
 * This function gets the closest  match to another gene
 * going through the letters in their sequence.
*/
relation compareGenes::findClosestMatch( Species reference,  Species looker)
{
      //create variables to use in function
      relation bestFound;
      bestFound.head = reference.SpecieName;
      bestFound.other = looker.SpecieName;



      set<int> myset;
      set<int> lookset;
      bool foundTrue = false;
      //go through the looker vector of combinations

      for(int looksPos = 0; looksPos <looker.GeneticVector.size(); looksPos++)
      {      //go through the reference vector of combinations

            foundTrue = false;//to see if there is a match
            //goes through the reference combos for each looker combination
                  for(int refPos = 0; refPos <reference.GeneticVector.size(); refPos++)
                  {

                              //if they have the same letters in a row in vector
                              //found a match
                              if(looker.GeneticVector[looksPos].first == reference.GeneticVector[refPos].first)
                              {

                                    //there is a match of combinations
                                    //get the numbers for each vector the match is found in
                                    foundTrue = true;
                                    numbers head = reference.GeneticVector[refPos].second;//numbers to the combo
                                    numbers look = looker.GeneticVector[looksPos].second;// numbers to the combo
                                    //add all the letters of the reference to the reference set and same for looker
                                    for(int x = head.first; x <= head.second; x ++)
                                    {
                                          myset.insert(x);

                                    }
                                    for(int x = look.first; x <= look.second; x ++)
                                    {
                                          lookset.insert(x);

                                    }
                                    //if is a match, this makes the next term be the longer better match of the previous
                                    looksPos++;
/////////////////////////////////////////////////////
                              }else{
                                    //skip ahead if no match like: (r)CA-GT dont go to  (r)CAG-GT
                                    int headExit = reference.GeneticVector[refPos].second.first;
                                    refPos += (reference.GeneticCode.size() - headExit) -2;

                              }

                  }
            if(!foundTrue)
            {
                  //skip ahead if no match like: CA-GT(l) dont go to  CAG-GT(l)
                  int lookExit = looker.GeneticVector[looksPos].second.first;

                  looksPos += (looker.GeneticCode.size() - lookExit) -2;

            }
      }


//get the score
double partOne = (((double)myset.size()/reference.GeneticCode.length())*100) ;
double partTwo = ((abs ((double)myset.size() - reference.GeneticCode.length()) )/1000);
double score = partOne - partTwo;
bestFound.score = score;
return bestFound;

}
