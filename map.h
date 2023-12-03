//
// Created by vickH on 11/23/2023.
//

#pragma once
#include "City.h"
#include <vector>
using namespace std;


class map {
private:
    double load_factor;
    int capacity;
    double size;
    vector<vector<City>> vec;
public:
    map();
    void rehash();
    void insert(City& city);
    void traverse(string country);

    double getSize(){
        return size;
    }
};

