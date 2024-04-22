#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

int gui() {

    float width = 740;
    float height = 800;

    vector<string> cities;
    vector<string> cityData;
    hashMapChaining chainMap(10);
    parseCSV(chainMap);

    priority_queue<pair<int, string>> maxPop;
    priority_queue<pair<int, string>> maxDen;
    priority_queue<pair<int, string>> maxSize;
    priority_queue<pair<int, string>> maxAge;

    sf::Font font;
    if (!font.loadFromFile("Arial.ttf"))
    {
        cerr << "Failed to load font!" << endl;
        return 1;
    }

    sf::RenderWindow introWindow(sf::VideoMode(width, height), "City Searcher");

    sf::Color purple(160,32,240);

    sf::Text welcomeMessage;
    welcomeMessage.setFont(font);
    welcomeMessage.setString("Welcome to CITY SEARCHER!");
    welcomeMessage.setCharacterSize(24);
    welcomeMessage.setFillColor(sf::Color::Yellow);
    setText(welcomeMessage, width/2, height/2-150);
    welcomeMessage.setPosition(width/2, height/2-150);
    //This program will generate numerical demographic information for any USA city!

    sf::Text nameText;
    nameText.setFont(font);
    nameText.setString("What is your name?");
    nameText.setCharacterSize(20);
    nameText.setFillColor(sf::Color::Yellow);
    setText(nameText, width/2, height/2-75);
    nameText.setPosition(width/2, height/2-75);

    string inputName;
    sf::Text inputNameText;
    inputNameText.setFont(font);
    inputNameText.setCharacterSize(20);
    inputNameText.setFillColor(sf::Color::Yellow);
//    setText(inputNameText, width/2, height/2-45);
    inputNameText.setPosition(width/2, height/2-45);

    while(introWindow.isOpen())
    {
        sf::Event event;
        while(introWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                introWindow.close();
                return 0;
            }
            if(event.type == sf::Event::TextEntered)
            {
                if(event.text.unicode == '\b')
                {
                    if(!inputName.empty())
                    {
                        inputName.pop_back();
                    }
                }
                else if(event.text.unicode == '\r')
                {
                    introWindow.close();
                }
                else
                {
                    inputName += static_cast<char>(event.text.unicode);
                }
                inputNameText.setOrigin(inputNameText.getGlobalBounds().width/2, inputNameText.getGlobalBounds().height/2-45);
                inputNameText.setString(inputName);
            }
        }

        introWindow.clear(purple);
        introWindow.draw(welcomeMessage);
        introWindow.draw(nameText);
        introWindow.draw(inputNameText);
        introWindow.display();
    }


    sf::RenderWindow mainWindow(sf::VideoMode(width, height), "City Searcher");

    sf::Text title;
    title.setFont(font);
    title.setString("CITY SEARCHER!");
    title.setCharacterSize(24);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    title.setFillColor(sf::Color::Cyan);
    //title.setStyle()
    setText(title, width/2, height/4-150);
    title.setPosition(width/2, height/4-150);

    sf::Text promptCity;
    promptCity.setFont(font);
    promptCity.setString("ENTER A CITY!");
    promptCity.setCharacterSize(20);
    promptCity.setStyle(sf::Text::Bold | sf::Text::Underlined);
    promptCity.setFillColor(sf::Color::Cyan);
    setText(promptCity, width/4-75, height/4-75);
    promptCity.setPosition(width/4-75, height/4-75);

    string inputCity;

    sf::RectangleShape inputBackground(sf::Vector2f(250.0f, 30.0f));
    inputBackground.setFillColor(sf::Color::Black);
    inputBackground.setOutlineThickness(2.0f);
    inputBackground.setOutlineColor(sf::Color::White);
    inputBackground.setPosition(width/4-145, height/4-50);

    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(20);
    inputText.setFillColor(sf::Color::Cyan);
    setText(inputText, width/4-140, height/4-45);
    inputText.setPosition(width/4-140,height/4-45);

    sf::RectangleShape outputBackground(sf::Vector2f(390.0f, 450.0f));
    outputBackground.setFillColor(sf::Color::Black);
    outputBackground.setOutlineThickness(2.0f);
    outputBackground.setOutlineColor(sf::Color::White);
    outputBackground.setPosition(width/2-50, height/4-50);

    sf::Text outputText;
    outputText.setFont(font);
    outputText.setCharacterSize(20);
    outputText.setFillColor(sf::Color::Cyan);
    outputText.setPosition(width/2-40, height/4-40);

    Button rankButton({width/4-145, height/4+45}, {250.0f, 30.0f}, sf::Color::Black, "RANK CITIES", font, sf::Color::Cyan, 20, {width/4-140,height/4+47.5f});
    Button exitButton({width/4-145, height/4+135}, {250.0f, 30.0f}, sf::Color::Black, "EXIT", font, sf::Color::Cyan, 20, {width/4-140,height/4+137.5f});

    Button rankPopulationButton({width/4-145, height/4+225}, {250.0f, 30.0f}, sf::Color::Black, "RANK BY POPULATION", font, sf::Color::Cyan, 20, {width/4-140,height/4+227.5f});
    Button rankDensityButton({width/4-145, height/4+315}, {250.0f, 30.0f}, sf::Color::Black, "RANK BY DENSITY", font, sf::Color::Cyan, 20, {width/4-140,height/4+317.5f});
    Button rankHouseholdSizeButton({width/4-145, height/4+415}, {280.0f, 30.0f}, sf::Color::Black, "RANK BY HOUSEHOLD SIZE", font, sf::Color::Cyan, 20, {width/4-140,height/4+417.5f});
    Button rankMedianAgeButton({width/4-145, height/4+505}, {250.0f, 30.0f}, sf::Color::Black, "RANK BY MEDIAN AGE", font, sf::Color::Cyan, 20, {width/4-140,height/4+507.5f});

    vector<pair<string,string>> cityRanks;

    while(mainWindow.isOpen())
    {
        sf::Event event;
        while(mainWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                mainWindow.close();
                return 0;
            }
            else if(event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if(!inputCity.empty()) {
                        inputCity.pop_back();
                    }
                }
                else if(event.text.unicode == '\r')
                {
                    if(!inputCity.empty())
                    {
                        cityData = search(chainMap, inputCity, maxPop, maxDen, maxSize, maxAge);
                        if(!cityData.empty())
                        {
                            cities.push_back(inputCity);
                            inputCity = "";
                            outputText.setString("City: " + cityData[0] + "\n");
                            outputText.setString(outputText.getString() + "State: " + cityData[1] + "\n");
                            outputText.setString(outputText.getString() + "Population: " + cityData[2] + "\n");
                            outputText.setString(outputText.getString() + "Population Density: " + cityData[3] + "\n");
                            outputText.setString(outputText.getString() + "Average Household Size: " + cityData[4] + "\n");
                            outputText.setString(outputText.getString() + "Median Age: " + cityData[5] + "\n");
                        }
                        else
                        {
                            inputCity = "";
                            outputText.setString("CITY DOES NOT EXIST!");
                        }
                    }
                }
                else {
                    inputCity += static_cast<char>(event.text.unicode);
                }
                inputText.setString(inputCity);
            }
            else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(mainWindow);
                rankButton.OnClickLeft(mousePos);
                if(exitButton.OnClickLeft(mousePos))
                {
                    mainWindow.close();
                    return 0;
                }
                else if(rankButton.getState())
                {
                    if(rankPopulationButton.OnClickLeft(mousePos))
                    {
                        outputText.setString("");
                        cityRanks = rankPopulation(maxPop);
                        for(int i = 0; i < cityRanks.size(); i++)
                        {
                            cout << cityRanks[i].first << cityRanks[i].second << endl;
                            outputText.setString(outputText.getString() + to_string(i+1) + ". " + cityRanks[i].first + " = " + cityRanks[i].second + "\n");
                        }
                    }
                    else if(rankHouseholdSizeButton.OnClickLeft(mousePos))
                    {
                        outputText.setString("");
                        cityRanks = rankHS(maxSize);
                        for(int i = 0; i < cityRanks.size(); i++)
                        {
                            cout << cityRanks[i].first << cityRanks[i].second << endl;
                            outputText.setString(outputText.getString() + to_string(i+1) + ". " + cityRanks[i].first + " = " + cityRanks[i].second + "\n");
                        }
                    }
                    if(rankMedianAgeButton.OnClickLeft(mousePos))
                    {
                        outputText.setString("");
                        cityRanks = rankAge(maxAge);
                        for(int i = 0; i < cityRanks.size(); i++)
                        {
                            cout << cityRanks[i].first << cityRanks[i].second << endl;
                            outputText.setString(outputText.getString() + to_string(i+1) + ". " + cityRanks[i].first + " = " + cityRanks[i].second + "\n");
                        }
                    }
                    if(rankDensityButton.OnClickLeft(mousePos))
                    {
                        outputText.setString("");
                        cityRanks = rankDensity(maxDen);
                        for(int i = 0; i < cityRanks.size(); i++)
                        {
                            cout << cityRanks[i].first << cityRanks[i].second << endl;
                            outputText.setString(outputText.getString() + to_string(i+1) + ". " + cityRanks[i].first + " = " + cityRanks[i].second + "\n");
                        }
                    }
                }
            }
        }
        mainWindow.clear(purple);
        mainWindow.draw(title);
        mainWindow.draw(promptCity);
        mainWindow.draw(inputBackground);
        mainWindow.draw(inputText);
        mainWindow.draw(outputBackground);
        mainWindow.draw(outputText);
        rankButton.draw(mainWindow);
        exitButton.draw(mainWindow);
        if(rankButton.getState())
        {
            rankPopulationButton.draw(mainWindow);
            rankDensityButton.draw(mainWindow);
            rankHouseholdSizeButton.draw(mainWindow);
            rankMedianAgeButton.draw(mainWindow);
        }
        mainWindow.display();
    }


    return 0;
}
