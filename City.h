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
    City(string city_name, string city_country, float lat, int ticket, float r_price){ // constructor
        name = city_name;
        country = city_country;

        // calculate city temperature based on month and its latitude
        float base_temp = 35.0 - fabs(lat) / 90.0 * 70.0;
        temp = round((base_temp * 9.0 / 5.0 + 32.0) * 100) / 100.0;

        plane_ticket = ticket;
        rel_price = r_price;
    }

    City() : name(""), country(""), temp(0.0), plane_ticket(0.0), rel_price(0.0) {}; // constructor

    string get_name(){ // return city name
        return name;
    }

    float get_temp(){ // return temperature
        return temp;
    }

    int get_plane_ticket(){ // return plane ticket price
        return plane_ticket;
    }

    float get_rel_price(){ // return relative price
        return rel_price;
    }

    string get_country(){ // return country name
        return country;
    }

    void print(){
        cout << "City Name : " << name << endl;
        cout << "Temperature : " << temp << " Farenheit"<< endl;
        cout << "Plane Ticket Price : $" << plane_ticket << endl;
        cout << "Relative Price Value: " << rel_price << endl;
    }
};