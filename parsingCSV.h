#include <iostream>
#include "hashTable.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

template<typename HashMapType>
void parseCSV(HashMapType& map){
    fstream cityInfo;
    string line, attribute;
    cityInfo.open("uscities.csv",ios::in);
    while(!cityInfo.eof()){
        getline(cityInfo,line);
        stringstream s(line);
        vector<string> attributes;
        while(getline(s,attribute,',')){
            attributes.push_back(attribute);
        }
        map.insert(attributes);
    }
}
