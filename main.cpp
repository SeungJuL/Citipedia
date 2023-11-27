#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <random>
#include <algorithm>
#include "RBTree.h"
#include "City.h"
#include "map.h"
using namespace std;

int main(){
    random_device rd;
    RBTree tree;
    map m;


    // Get user input for tree or map
//    int option;
//    cout << "Select 1 for tree, 2 for map" << endl;
//    cin >> option;

    // predefined value for Gainesville temp
    float temp[12] = {55.5, 58, 64, 69, 75.5, 80, 82, 82, 79, 72, 64.5, 59};
    cout << "What month is it now? "<<endl;
    int month;
    cin >> month;
//
    float curr_temp = temp[month-1];

    // first question: temperature
    cout << "What temperature range do you prefer?" << endl;
    cout << "1: colder than current location" << endl;
    cout << "2: similar to current location" << endl;
    cout << "3: hotter than current location" << endl;
    int option;
    cin >> option;

    float tempMin = -100; // arbitrary small number
    float tempMax = 200; // arbitrary big number
    // set temperature range
    if (option == 1)
        tempMax = curr_temp - 10;
    else if (option == 2) {
        tempMin = curr_temp - 10;
        tempMax = curr_temp + 10;
    }
    else if (option == 3)
        tempMin = curr_temp + 10;

    // Second question: plane ticket
    cout << "Select the maximum price range you can spend on a plane ticket." << endl;
    cout << "1: $1 - $500" << endl;
    cout << "2: $500 - $1,000" << endl;
    cout << "3: $1,000 - $1,500" << endl;
    cout << "4: $1,500 - $2,000" << endl;
    cin >> option;
    int ticketMin, ticketMax = 0;
    // set plane ticket price range
    if (option == 1) {
        ticketMin = 1;
        ticketMax = 500;
    }
    else if (option == 2) {
        ticketMin = 500;
        ticketMax = 1000;
    }
    else if (option == 3) {
        ticketMin = 1000;
        ticketMax = 1500;
    }
    else if (option == 4) {
        ticketMin = 1500;
        ticketMax = 2000;
    }


    // read file
    ifstream file("new_worldcities.csv");
    string line;

    // skip first line (header)
    getline(file, line);

    int count = 0; // 지워야함 just for test

    // read each line
    while (getline(file, line)) {

        stringstream ss(line);
        vector<string> fields;
        string field;

        // Parsing each line
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }

        std::mt19937 gen1(rd());
        uniform_int_distribution<> distr1(100, 2000);
        int ticket = distr1(gen1);
        count++;
        // relative price
        std::mt19937 gen2(rd());
        uniform_real_distribution<> distr2(0.5, 1.5);
        float r_price = round(distr2(gen2) * 10.0) / 10.0;

        // remove '\"' each string from csv file
        fields[0].erase(remove(fields[0].begin(), fields[0].end(), '\"'), fields[0].end());
        fields[2].erase(remove(fields[2].begin(), fields[2].end(), '\"'), fields[2].end());
        fields[4].erase(remove(fields[4].begin(), fields[4].end(), '\"'), fields[4].end());

        City city(fields[0], fields[4], stof(fields[2]), ticket, r_price);

        //city.print();

        // insert the cities within the temperature range only
        if (city.get_temp() >= tempMin && city.get_temp() < tempMax) {
            tree.insert(city);
            m.insert(city);
        }
        // 여기서 tree 나 map 으로 이 city object 넣으면서 build

//        if (option == 1){ // tree
//
//        }
//        else{ // map
//
//        }
        //city.print();
        if(count == 500){ // 지워야함 just for test
            break;
        }

    }
    tree.printInorder();
    m.traverse();

    cout<<endl;
    cout<<"Fisnished"<<endl;
    cout<<curr_temp<<endl;

    return 0;
}