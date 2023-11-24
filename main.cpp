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
using namespace std;

int main(){
    random_device rd;
    RBTree tree;


    // Get user input for tree or map
//    int option;
//    cout << "Select 1 for tree, 2 for map" << endl;
//    cin >> option;

    // predefined value for Gainesville temp
//    float temp[12] = {55.5, 58, 64, 69, 75.5, 80, 82, 82, 79, 72, 64.5, 59};
//    cout << "What month is it now? ";
//    int month;
//    cin >> month;
//
//    float curr_temp = temp[month-1];


    // read file
    ifstream file("worldcities.csv");
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

        tree.insert(city);
        // 여기서 tree 나 map 으로 이 city object 넣으면서 build

//        if (option == 1){ // tree
//
//        }
//        else{ // map
//
//        }
        //city.print();
        if(count == 50){ // 지워야함 just for test
            break;
        }

    }
    tree.printInorder();


    return 0;
}