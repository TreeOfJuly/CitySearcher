#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#pragma once

//priority_queue<pair<int, string>>& maxPop, priority_queue<pair<int, string>>& maxDen, priority_queue<pair<int, string>>& maxSize, priority_queue<pair<int, string>>& maxAge

using namespace std;

string menu()
{
    cout << "Pick from the following options: " << endl;
    cout << "1 - Search another city" << endl;
    cout << "2 - Rank Cities" << endl;
    cout << "3 - End City Searcher!" << endl;
    string option;
    cin >> option;
    return option;
};


void compareMaps(string cityName, hashMapLinear& linear, hashMapChaining& chaining)
{
    auto startLinear = clock();
    linear.find(cityName);
    auto endLinear = clock();
    auto durationLinear = 1000.0 * (endLinear - startLinear) / CLOCKS_PER_SEC;
    auto startChaining = chrono::high_resolution_clock::now();
    chaining.find(cityName);
    auto endChaining = chrono::high_resolution_clock::now();
    chrono::duration<double, nano> durationChaining = endChaining - startChaining;
    cout << "Time for Linear Hash Table to find city is: " << durationLinear << endl;
    cout << "Time for Seperate Chaining Hash Table to find city is: " << durationChaining.count() << endl;
};

template<typename HashMapType>
void searchCity(HashMapType& myMap, string cityName, priority_queue<pair<int, string>>& maxPop, priority_queue<pair<int, string>>& maxDen, priority_queue<pair<int, string>>& maxSize, priority_queue<pair<int, string>>& maxAge)
{
    vector<string> cityData;
    cityData = myMap.find(cityName);
    if (cityData.empty()){
        return;
    }

    cout << endl << cityData[0] << endl; //data[0]
    cout << "State: " << cityData[1] << endl;
    cout << "Population: " << cityData[2] << endl;
    cout << "Population Density: " << cityData[3] << endl;
    cout << "Average Household Size: " << cityData[4] << endl;
    cout << "Median Age: " << cityData[5] << endl << endl;


    pair<int, string> dataPairs;
    dataPairs.first = stoi(cityData[2]);
    dataPairs.second = cityName;
    maxPop.push(dataPairs);

    dataPairs.first = stoi(cityData[3]);
    maxDen.push(dataPairs);

    dataPairs.first = stoi(cityData[4]);
    maxSize.push(dataPairs);

    dataPairs.first = stoi(cityData[5]);
    maxAge.push(dataPairs);

    //return cityData;
};

template<typename HashMapType>
void Rank(string menu_option, HashMapType& myMap, priority_queue<pair<int, string>> maxPop, priority_queue<pair<int, string>> maxDen, priority_queue<pair<int, string>> maxSize, priority_queue<pair<int, string>> maxAge)
{
    int counter = 1;
    if (menu_option == "1"){
        cout << "Population Ranking (greatest to least)" << endl;
        //for population in all cities, cout << counter << city name << population, counter ++
        while (!maxPop.empty()){
            //next two lines inspired by https://www.geeksforgeeks.org/priority-queue-of-pairs-in-c-ordered-by-first/
            pair<int, string> top = maxPop.top();
            cout << counter << ". " << top.second << " = " << top.first<< endl;
            maxPop.pop();
            counter++;
        }
        cout << endl;
    }
    else if (menu_option == "2"){
        cout << "Population Density Ranking (greatest to least)" << endl;
        while (!maxDen.empty()){
            pair<int, string> top = maxDen.top();
            cout << counter << ". " << top.second << " = " << top.first<< endl;
            maxDen.pop();
            counter++;
        }
        cout << endl;
    }
    else if (menu_option == "3"){
        cout <<  "Average Household Size Ranking (greatest to least)" << endl;
        while (!maxSize.empty()){
            pair<int, string> top = maxSize.top();
            cout << counter << ". " << top.second << " = " << top.first<< endl;
            maxSize.pop();
            counter++;
        }
        cout << endl;
    }
    else if (menu_option == "4"){
        cout << "Median Age Ranking (greatest to least)" << endl;
        while (!maxAge.empty()){
            pair<int, string> top = maxAge.top();
            cout << counter << ". " << top.second << " = " << top.first<< endl;
            maxAge.pop();
            counter++;
        }
        cout << endl;
    }
    else{
        cout << "Invalid selection :(" << endl << endl;
    }
};
