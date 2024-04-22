#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <map>
#pragma once
using namespace std;

//map that is used for hashing function of strings
static map<char,int> alphabet = {{'a',1},{'b',2},{'c',3},{'d', 4},{'e',5},{'f', 6},{'g',7},
                         {'h',8},{'i', 9},{'j',10},{'k',11},{'l',12},{'m',13},{'n',14},
                         {'o',15},{'p',16},{'q',17},{'r',18},{'s',19},{'t',20},{'u',21},
                         {'v',22},{'w',23},{'x',24},{'y',25},{'z',26}};


//linear probing hash table
class hashMapLinear{
private:

   //this is the container for the hash table
   vector<vector<string>> map = {};
   //keeps track of the max capacity of the hash table
   int capacity;
    //keeps track of current # of elements of the hash table
   int size;
   //max fraction of number of elements based on the capacity
   double maxLoadFactor;


public:

   hashMapLinear(int cap){
       //creates empty 2d array with cap number of rows
       for(int i = 0; i < cap;i++){
           map.push_back({});
       }
       capacity = cap;
       size = 0;
       maxLoadFactor = 0.75;
   }

   // hash function that hashes the city's name
   long hashFunc(string cityName){
       long value = 0;
       int i = 0;
       for(auto s : cityName){
           //ignores space in string
           if(s == ' ') {
               i++;
               continue;
           }
           s = tolower(s);
           //gets value from alphabet map corresponding to letter character s and multiples that by 30^i
           value += alphabet[(char) s] * (30^i);
           i++;
       }

       return value % capacity;
   }

   void insertHelper(vector<string> cityAttributes, vector<vector<string>>& Map){
       if(cityAttributes.empty())
           return;
       //checks if the current capacity exceeds max load factor
       if(size > maxLoadFactor*(double)capacity){
           //rehashes if resizing is needed
           reHash();
       }

       //hashes based on city name which is in cityAttributes[0]
       int index = hashFunc(cityAttributes[0]);
       //places city at that index in the hash table if it is empty
       if(Map[index].empty()){
           Map[index] = cityAttributes;
           size++;
       }
       else{
           //increases index by one until empty spot is found
           while(!Map[index].empty()){
               index += 1;
               if(index >= capacity){
                   index = 0;
               }
           }
           Map[index] = cityAttributes;
           size++;


       }
   }

   void insert(vector<string>& attributes){
       insertHelper(attributes,map);
   }

   //creates new hash table of capacity * 3
   void reHash(){
       vector<vector<string>> newMap;
       for(int i = 0; i < capacity * 3; i++){
           newMap.push_back({});
       }
       capacity *= 3;
       //takes all cities in old hash table and reassigns indices for new hash table
       for(const auto& vec : map){
           insertHelper(vec,newMap);
       }
       map = newMap;
   }

   //finds city in hash table
   vector<string> find(const string& city){
       //calculates index based on hashing function
       int index = hashFunc(city);
       //searches linearly for city if it is not found at original index
       while(!map[index].empty() and map[index][0] != city){
           index++;
           if(index >= capacity){
               index = 0;
           }
       }
       //if an empty index is found then city cannot exist in hash table
       if(map[index].empty()){
           cout << "Could not find city" << endl;
           return {};
       }
       //retrieves information for city once it is found
       return map[index];
   }

};


class hashMapChaining{
private:

    vector<vector<vector<string>>> buckets;
    // Keeps track of number of buckets
    int bucket_count;
    // Keeps track of number of elements
    int elements;
    // Keeps track of LF; elements/bucket_count
    double maxLoadFactor;

public:

    //Initializes the hash table and therefore creates the number of startings buckets
    hashMapChaining(int numOfBuckets)
    {
        buckets.resize(numOfBuckets);
        bucket_count = numOfBuckets;
        elements = 0;
        maxLoadFactor = 0.75;
    };

    //Return the hash value of the city name
    long hash(string cityName)
    {
        long hashValue = 0;
        int i = 0;
        //this is the process of where the hash value is created by using the letters as a way to calculate
        for(auto& value : cityName)
        {
            if(value == ' ')
            {
                i++;
                continue;
            }
            value = tolower(value);
            //gets value from alphabet map corresponding to letter character s
            hashValue += alphabet[(char) value] * (30^i);
            i++;
        }
        return hashValue % bucket_count;
    };

    void insert(vector<string>& attributes)
    {
        //A cleaner more sylstic approach
        insertHelper(attributes, buckets);
    };

    void insertHelper(vector<string>& cityAttributes, vector<vector<vector<string>>>& hashMap)
    {
        //If the cityAttributes is empty it does nothing which is to prevent empty buckets
        if(cityAttributes.empty())
        {
            return;
        }
        //If load factor is exceeded it will call the rehash function
        if(elements > maxLoadFactor*(double)bucket_count)
        {
            rehash();
        }
        //Grabs the hash value using city name
        int hashValue = hash(cityAttributes[0]);
        //Simple matter of just pushing the value into vector
        hashMap[hashValue].push_back(cityAttributes);
        elements++;
        //printBuckets();
    }

    //When the load factor is exceeded it then creates more buckets and grabs the hash
    //values of all the elements to reassign them
    void rehash()
    {
        //When rehashing we multiply coexisiting buckets by 3 to increase space
        bucket_count *= 3;
        vector<vector<vector<string>>> newBuckets(bucket_count);
        for(auto& bucket: buckets)
        {
            for(auto& city : bucket)
            {
                long hashValue = hash(city[0]);
                newBuckets[hashValue].push_back(city);
            }
        }
        //reassigns the old vector to the new vector
        buckets = newBuckets;
    }

    vector<string> find(string cityName)
    {
        long hashValue = hash(cityName);
        for(auto& city : buckets[hashValue])
        {
            if(city[0] == cityName)
            {
                return city;
            }
        }
        cout << "Could not find city!" << endl;
        return {};
    }

    //Prints out the buckets by using a for each loop that iterates through each bucket
    //And the vector within it
    void printBuckets()
    {
        for (int i = 0; i < bucket_count; ++i)
        {
            //The i is used to keep track of the number of buckets to show how many are left empty due to separate chaining
            cout << "Bucket " << i << ":" << endl;
            for (auto& bucket : buckets[i])
            {
                cout << "  ";
                for (auto& cityAttributes : bucket)
                {
                    for (auto& attribute : cityAttributes)
                    {
                        cout << attribute << " ";
                    }
                    //Used to separate
                    cout << "| ";
                }
                cout << endl;
            }
        }
    }

};

