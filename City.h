#pragma once
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class City {
private:

    string name;
    float temp;
    int plane_ticket;
    float rel_price;
    string country;

public:
    City(string city_name, string city_country, float lat, int ticket, float r_price){
        name = city_name;
        country = city_country;

        // Calculate city temp based on month and latutude
        float base_temp = 35.0 - fabs(lat) / 90.0 * 70.0;
        temp = base_temp * 9.0 / 5.0 + 32.0;

        plane_ticket = ticket;
        rel_price = r_price;
    }
    City() : name(""), country(""), temp(0.0), plane_ticket(0.0), rel_price(0.0) {};
    string get_name(){
        return name;
    }
    float get_temp(){
        return temp;
    }
    int get_plane_ticket(){
        return plane_ticket;
    }
    float get_rel_price(){
        return rel_price;
    }
    string get_country(){
        return country;
    }
    void print(){
        cout << "Name of the city : " << name << endl;
        cout << "Temperature : " << temp << endl;
        cout << "Plane ticket price : " << plane_ticket << endl;
        cout << "Relative price : " << rel_price << endl;
        cout << "Country : " << country << endl;
    }
};