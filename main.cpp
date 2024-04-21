#include <iostream>
#include <string>
#include <vector>
#include "parsingCSV.h"
#include "hashTable.h"
#include "toolbox.h"
#include <ctime>
#include <bits/stdc++.h>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

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

    cout << "Welcome to CITY SEARCHER!\nThis program will generate numerical demographic information for any USA city!"<< endl;
    cout << "What is your name?" << endl;
    string userName;
    cin >> userName;
    cout << "Hi there " << userName << "!\n" << endl;
    int iteration = 1;
    string cityName;
    string option;
    string menu_option;

    while(true)
    {
        if (iteration == 1){
            cout << "Input the name of the city: " << endl;
            cin >> cityName;
            searchCity(chainMap, cityName, maxPop, maxDen, maxSize, maxAge);
        }
        else{
            menu_option = menu();
            if(menu_option == "1")
            {
                cout << "Input the name of the city: " << endl;
                cin >> cityName;
                searchCity(chainMap, cityName, maxPop, maxDen, maxSize, maxAge);

                //compareMaps(cityName, linearMap, chainMap);
            }
            else if(menu_option == "2")
            {
                cout << "1 - Rank by Population" << endl;
                cout << "2 - Rank by Density" << endl;
                cout << "3 - Rank by Household Size" << endl;
                cout << "4 - Rank by Median Age" << endl;
                cin >> option;
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
