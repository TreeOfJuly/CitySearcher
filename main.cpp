#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "parsingCSV.h"
#include "hashTable.h"
#include "toolbox.h"
#include <ctime>
#include <bits/stdc++.h>

using namespace std;

//group 50: Julio Arboleda, Carmen Cruz Arana, Graciela Strand



int main() {


    hashMapLinear linearMap(10);
    parseCSV(linearMap);

    hashMapChaining chainMap(10);
    parseCSV(chainMap);

    priority_queue<pair<int, string>> maxPop;
    priority_queue<pair<int, string>> maxDen;
    priority_queue<pair<int, string>> maxSize;
    priority_queue<pair<int, string>> maxAge;

    cout << "Welcome to CITY SEARCHER!\nThis program will generate numerical demographic information for a US city!"<< endl;
    cout << "What is your name?" << endl;
    string userName;
    getline(cin, userName, '\n');
    cout << "Hi there " << userName << "!\n" << endl;
    int iteration = 1;
    string cityName;
    string option;
    string menu_option;
    string city;
    while(true)
    {
        if (iteration == 1){
            cout << "Input the name of the city (please capitalize, e.g., \"Los Angeles\"):" << endl;
            getline(cin, cityName, '\n');
            searchCity(chainMap, cityName, maxPop, maxDen, maxSize, maxAge);
        }
        else{
            menu_option = menu();
            if(menu_option == "1")
            {
                cout << endl;
                cout << "Input the name of the city: " << endl;
                getline(cin, cityName, '\n');
                searchCity(chainMap, cityName, maxPop, maxDen, maxSize, maxAge);

                //compareMaps(cityName, linearMap, chainMap);
            }
            else if(menu_option == "2")
            {
                cout << endl;
                cout << "1 - Rank by Population" << endl;
                cout << "2 - Rank by Density" << endl;
                cout << "3 - Rank by Household Size" << endl;
                cout << "4 - Rank by Median Age" << endl;

                getline(cin, option, '\n');
                Rank(option, chainMap, maxPop, maxDen, maxSize, maxAge);
            }
            else if(menu_option == "3")
            {
                exit(1);
            }
            else
            {
                cout << "Invalid selection :(" << endl;
                continue;
            }
        }
        iteration++;
    }

    return 0;
};
