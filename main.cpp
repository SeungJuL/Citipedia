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
    int ds_option;
    cout<<"Select a data structure to store data"<<endl;
    cout << "1 for tree; 2 for map" << endl;
    cin >> ds_option;

    // predefined value for Gainesville temp
    float temp[12] = {55.5, 58, 64, 69, 75.5, 80, 82, 82, 79, 72, 64.5, 59};
    cout << "What month is it now? "<<endl;
    int month;
    cin >> month;
//
    float curr_temp = temp[month-1];

    // first question: temperature
    cout << "Select a temperature range for your vacation site:" << endl;
    cout << "1: less than 10 degrees (°F) than current temperature" << endl;
    cout << "2: within +-10 degrees (°F) to current temperature" << endl;
    cout << "3: more than 10 degrees (°F) higher than current temperature" << endl;
    int option;
    cin >> option;

    float tempMin = -100; // arbitrary small number
    float tempMax = 200; // arbitrary big number
    // set temperature range
    if (option == 1)
        tempMax = curr_temp - 10.0001;
    else if (option == 2) {
        tempMin = curr_temp - 10;
        tempMax = curr_temp + 10;
    }
    else if (option == 3)
        tempMin = curr_temp + 10.0001;

    // Second question: plane ticket
    cout << "Select a price range for your airplane ticket:" << endl;
    cout << "1: $1 - $500" << endl;
    cout << "2: $501 - $1,000" << endl;
    cout << "3: $1,001 - $1,500" << endl;
    cout << "4: $1,501 - $2,000" << endl;
    cin >> option;
    int ticketMin, ticketMax = 0;
    // set plane ticket price range
    if (option == 1) {
        ticketMin = 1;
        ticketMax = 500;
    }
    else if (option == 2) {
        ticketMin = 501;
        ticketMax = 1000;
    }
    else if (option == 3) {
        ticketMin = 1001;
        ticketMax = 1500;
    }
    else if (option == 4) {
        ticketMin = 1501;
        ticketMax = 2000;
    }

    //Third question: relative price value
    cout<<"Select a range for the US dollar relative price value in relation to your vacation site:"<<endl;
    cout<<"Note: A relative price value of 0.5 indicates that 1 US dollar is worth half of the"<<endl;
    cout<<"individual unit of currency of your desired vacation region."<<endl;
    cout<<"1: 0.5-0.8" <<endl;
    cout<<"2: 0.9-1.1" <<endl;
    cout<<"3: 1.2-1.5" <<endl;
    cin>>option;

    double priceMin,priceMax=0;

    if(option==1){
        priceMin=0.5;
        priceMax=0.8;
    }
    else if(option==2){
        priceMin=0.9;
        priceMax=1.1;
    }
    else{
        priceMin=1.2;
        priceMax=1.5;
    }


    // read file
    ifstream file("new_worldcities2.csv");
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
        if (city.get_temp() >= tempMin && city.get_temp() <= tempMax &&
            city.get_plane_ticket() >= ticketMin && city.get_plane_ticket() <= ticketMax &&
            city.get_rel_price() >= priceMin && city.get_rel_price() <= priceMax) {
            if(ds_option==1){
                tree.insert(city);
            }
            else{
                m.insert(city);
            };
        }
        //city.print();

        //debugging purposes
        //cut off at 500 data points
        count++;
        if(count == 500){
            break;
        }

    }
    cout<<"\n\ntraversing time"<<endl;
    tree.printInorder();
    m.traverse();

    cout<<endl;
    cout<<"Finished"<<endl;
    cout<<curr_temp<<endl;

    return 0;
}