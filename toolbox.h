#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
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
    getline(cin, option, '\n');
    return option;
}

/*compares how quickly a hash table using linear probing and a hash table
using separate chaining retrieve information*/
void compareMaps(hashMapLinear& linear, hashMapChaining& chaining)
{
    vector<string> cityNames;
    fstream cityInfo;
    string line, attribute;
    cityInfo.open("uscities.csv",ios::in);
    while(!cityInfo.eof()){
        getline(cityInfo,line);
        stringstream s(line);
        getline(s,attribute,',');
        cityNames.push_back(attribute);
    }
    auto startChaining = clock();
    for(auto city : cityNames){
        vector<string> result2 = chaining.find(city);
    }
    auto endChaining = clock();
    auto durationChaining = (endChaining - startChaining) / CLOCKS_PER_SEC;
    cout << "Time for Seperate Chaining Hash Table to find city is: " << durationChaining << endl;

    auto startLinear = clock();
    for(auto& city : cityNames){
        vector<string> result1 = linear.find(city);
    }
    auto endLinear = clock();
    auto durationLinear = (endLinear - startLinear) / CLOCKS_PER_SEC;
    cout << "Time for Linear Hash Table to find city is: " << durationLinear << endl;

}

//searches for a city in a hash table using its name and pushes its information into priority queues for future ranking
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
    //pushes city's population and name into max population priority queue
    dataPairs.first = stoi(cityData[2]);
    dataPairs.second = cityName;
    maxPop.push(dataPairs);

    //pushes population density of city and city's name into max density priority queue
    dataPairs.first = stoi(cityData[3]);
    maxDen.push(dataPairs);

    //pushes average household size of city and city's name into max household size priority queue
    dataPairs.first = stoi(cityData[4]);
    maxSize.push(dataPairs);
    
    //pushes median age of city and city's name into max age priority queue
    dataPairs.first = stoi(cityData[5]);
    maxAge.push(dataPairs);

};

//ranks cities based on the category that the user chooses using priority queues
template<typename HashMapType>
void Rank(string menu_option, HashMapType& myMap, priority_queue<pair<int, string>> maxPop, priority_queue<pair<int, string>> maxDen, priority_queue<pair<int, string>> maxSize, priority_queue<pair<int, string>> maxAge)
{
    cout << endl;
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
    //ranks cities based on their population density
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
    //ranks cities based on their avergae household size
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
    //ranks cities based on their median age
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

//
void setText(sf::Text &text, float x, float y)
{
    sf::FloatRect textRect = text.getGlobalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

class Button
{
    enum State {UNCLICKED, CLICKED};
private:
    sf::RectangleShape button;
    sf::Text text;
    string buttonText;
    State currentState;
public:
    Button(const sf::Vector2f& buttonPosition, const sf::Vector2f& buttonSize, const sf::Color& buttonFill,
           const std::string& textString, const sf::Font& textFont, const sf::Color& textFill,
           unsigned int textSize, const sf::Vector2f& textPosition) : currentState(UNCLICKED)
    {
        button.setSize(buttonSize);
        button.setFillColor(buttonFill);
        button.setOutlineThickness(2.0f);
        button.setOutlineColor(sf::Color::White);
        button.setPosition(buttonPosition);

        text.setString(textString);
        text.setFont(textFont);
        text.setCharacterSize(textSize);
        text.setFillColor(textFill);
        text.setPosition(textPosition);
    }

    //draws button and text inside button
    void draw(sf::RenderWindow& window)
    {
        window.draw(button);
        window.draw(text);
    }

    //Determines if mouse is clicking on area
    bool OnClickLeft(const sf::Vector2i& mousePosition)
    {
        if (button.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
        {
            if (currentState == UNCLICKED)
                currentState = CLICKED;
            else
                currentState = UNCLICKED;
        }
    }

    //Returns when button is clicked or not
    bool getState()
    {
        if(currentState == CLICKED)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

//returns vector of pairs from max population priority queue
vector<pair<string,string>> rankPopulation(priority_queue<pair<int, string>> maxPop)
{
    vector<pair<string,string>> populationRanking;
    while(!maxPop.empty())
    {
        pair<int, std::string> top = maxPop.top();
        populationRanking.push_back(make_pair(top.second, std::to_string(top.first)));
        maxPop.pop();
    }
    return populationRanking;
}
//Returns a vector<pair<string,string>> where it uses a priority queue that organizes the density accordingly
//And it also includes their matching country
vector<pair<string,string>> rankDensity(priority_queue<pair<int, string>> maxDen)
{
    vector<pair<string,string>> densityRanking;
    while(!maxDen.empty())
    {
        pair<int, std::string> top = maxDen.top();
        densityRanking.push_back(make_pair(top.second, std::to_string(top.first)));
        maxDen.pop();
    }
    return densityRanking;
}

//This uses a priority queue to organize the countries with highest age and
//Returns a vector of pairs to be used in the UI
vector<pair<string,string>> rankAge(priority_queue<pair<int, string>> maxAge)
{
    vector<pair<string,string>> ageRanking;
    while(!maxAge.empty())
    {
        pair<int, std::string> top = maxAge.top();
        ageRanking.push_back(make_pair(top.second, std::to_string(top.first)));
        maxAge.pop();
    }
    return ageRanking;
}

//This returns a vector of pairs of the college and the average home population size
//This uses priority queue to organize the countries numbers
vector<pair<string,string>> rankHS(priority_queue<pair<int, string>> maxSize)
{
    vector<pair<string,string>> hsRanking;
    while(!maxSize.empty())
    {
        pair<int, std::string> top = maxSize.top();
        hsRanking.push_back(make_pair(top.second, std::to_string(top.first)));
        maxSize.pop();
    }
    return hsRanking;
}

//Similar to the searchCity function above but except this returns a vector of city values
template<typename HashMapType>
vector<string> search(HashMapType& myMap, string cityName, priority_queue<pair<int, string>>& maxPop, priority_queue<pair<int, string>>& maxDen, priority_queue<pair<int, string>>& maxSize, priority_queue<pair<int, string>>& maxAge)
{
    vector<string> cityData;
    cityData = myMap.find(cityName);
    if (cityData.empty()){
        return {};
    }

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

    return cityData;
}
