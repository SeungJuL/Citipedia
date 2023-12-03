//
// Created by vickH on 11/23/2023.
//

#include "map.h"
#include <iostream>

map::map(){
    capacity=100;
    size=0.0;
    load_factor=0.8;
    vec.resize(capacity);
}
void map::insert(City& c) {
    hash<string> h;
    int code=h(c.get_name()) % capacity;

    vec.at(code).push_back(c);

    size++;
    if(size/capacity >= load_factor){
        rehash();
    }
}
void map::rehash() {
    capacity*=2;
    vector<vector<City>> temp=vec;

    vec.clear();
    vec.resize(capacity);

    hash<string> h;
    int code;

    for(auto i:temp){
        for(int j=0; j<i.size(); j++){
            code=h(i.at(j).get_name()) % capacity;

            vec.at(code).push_back(i.at(j));
        }
    }
}
void map::traverse(string country) {
    for(auto i:vec){
        for(int j=0; j<i.size(); j++){
            City temp=i.at(j);

            if(temp.get_country()==country){
                temp.print();
                cout<<endl;
            }
        }
    }
}
