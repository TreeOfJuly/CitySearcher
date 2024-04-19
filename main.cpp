#include <iostream>
#include <string>
#include <vector>
#include "parsingCSV.h"
#include "hashTable.h"
#include <bits/stdc++.h>


using namespace std;


//group 50: Julio Arboleda, Carmen Cruz Arana, Graciela Strand





template<typename HashMapType>
vector<string> citySearcher(string cityName, HashMapType& myMap, priority_queue<pair<int, string>>& maxPop, priority_queue<pair<int, string>>& maxDen, priority_queue<pair<int, string>>& maxSize, priority_queue<pair<int, string>>& maxAge){
   //RETRIEVAL
   vector<string> data;
   data = myMap.find(cityName);
   if (data.empty() ){
       return {};
   }
   cout << endl<< cityName << endl; //data[0]
   cout << "State: " << data[1] << endl;
   cout << "Population: " << data[2] << endl;
   cout << "Population Density: " << data[3] << endl;
   cout << "Average Household Size: " << data[4] << endl;
   cout << "Median Age: " << data[5] <<  endl;




   //pushes all the new data in a <value, cityname> pair onto each of the 4 heaps
   pair<int, string> dataPairs;
   dataPairs.first = stoi(data[2]);
   dataPairs.second = cityName;
   maxPop.push(dataPairs);


   dataPairs.first = stoi(data[3]);
   maxDen.push(dataPairs);


   dataPairs.first = stoi(data[4]);
   maxSize.push(dataPairs);


   dataPairs.first = stoi(data[5]);
   maxAge.push(dataPairs);


   return data;
}


void Rank(string option, priority_queue<pair<int, string>>& maxPop, priority_queue<pair<int, string>>& maxDen, priority_queue<pair<int, string>>& maxSize, priority_queue<pair<int, string>>& maxAge){
   int counter = 1;
   if (option == "1"){
       cout << "Population Ranking (greatest to least)" << endl;
       //for population in all cities, cout << counter << city name << population, counter ++
       while (!maxPop.empty()){
           //next two lines inspired by https://www.geeksforgeeks.org/priority-queue-of-pairs-in-c-ordered-by-first/
           pair<int, string> top = maxPop.top();
           cout << counter << ". " << top.second << " = " << top.first<< endl;
           maxPop.pop();
           counter++;
       }
       exit(1);
   }
   else if (option == "2"){
       cout << "Population Density Ranking (greatest to least)" << endl;
       while (!maxDen.empty()){
           pair<int, string> top = maxDen.top();
           cout << counter << ". " << top.second << " = " << top.first<< endl;
           maxDen.pop();
           counter++;
       }
       exit(1);
   }
   else if (option == "3"){
       cout <<  "Average Household Size Ranking (greatest to least)" << endl;
       while (!maxSize.empty()){
           pair<int, string> top = maxSize.top();
           cout << counter << ". " << top.second << " = " << top.first<< endl;
           maxSize.pop();
           counter++;
       }
       exit(1);
   }
   else if (option == "4"){
       cout << "Median Age Ranking (greatest to least)" << endl;
       while (!maxAge.empty()){
           pair<int, string> top = maxAge.top();
           cout << counter << ". " << top.second << " = " << top.first<< endl;
           maxAge.pop();
           counter++;
       }
       exit(1);
   }
   else{
       cout << "invalid selection :(" << endl;
       exit(1);
   }
}

template<typename HashMapType>
void menuBasic(HashMapType& myMap, priority_queue<pair<int, string>> maxPop, priority_queue<pair<int, string>> maxDen, priority_queue<pair<int, string>> maxSize, priority_queue<pair<int, string>> maxAge){
   cout << "Pick from the following options: " << endl;
   cout << "1 - Search another city" << endl;
   cout << "2 - Rank Cities" << endl;
   cout << "3 - end" << endl;
   string option;
   string cityName;
   cin >> option;
   if (option == "1") {
       cout << "Enter the name of another city: " << endl;
       cin >> cityName;
       citySearcher(cityName, myMap, maxPop, maxDen, maxSize, maxAge);
       menuBasic(myMap, maxPop, maxDen, maxSize, maxAge);
   }
   else if (option == "2"){
       cout << "1 - Rank by Population" << endl;
       cout << "2 - Rank by Density" << endl;
       cout << "3 - Rank by Household Size" << endl;
       cout << "4 - Rank by Median Age" << endl;
       cin >> option;
       Rank(option, maxPop, maxDen, maxSize, maxAge);


   }
   else if (option == "3"){
       exit(1);
   }
   else{
       cout << "invalid selection :(" << endl;
       menuBasic(myMap, maxPop, maxDen, maxAge, maxSize);
   }
}






int main() {
   hashMapLinear LinearMap(10);
   parseCSV(LinearMap);
   hashMapLinear LinearMap(10);
   parseCSV(LinearMap);


   priority_queue<pair<int, string>> maxPop;
   priority_queue<pair<int, string>> maxDen;
   priority_queue<pair<int, string>> maxSize;
   priority_queue<pair<int, string>> maxAge;


   cout << "Welcome to CITY SEARCHER!\nThis program will generate numerical demographical information for any USA city"<< endl;
   cout << "What is your name?" << endl;
   string userName;
   cin >> userName;
   cout << "Hi there " << userName << "!" << endl;
   cout << "Enter the name of a city: " << endl;
   string cityName;
   cin >> cityName;
   citySearcher(cityName, LinearMap, maxPop, maxDen, maxSize, maxAge);
   cout << "Enter the name of another city: " << endl;
   cin >> cityName;
   citySearcher(cityName, LinearMap, maxPop, maxDen, maxSize, maxAge);
   menuBasic(LinearMap, maxPop, maxDen, maxSize, maxAge);




   return 0;
}
