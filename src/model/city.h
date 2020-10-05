/**
This file is part of simple-weather.

    simple-weather is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    simple-weather is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with simple-weather.  If not, see <https://www.gnu.org/licenses/>
**/

#ifndef _CITY_
#define _CITY_

#include <string>

class City {
private:
    std::string json;
    int lat, lon, id;
    std::string name, state, country;
    std::string time;
    double temp, feels_like;
    int humidity;
    std::string icon;

public:
    void init(int id, std::string key);
    std::string getName();
    std::string getState();
    std::string getCountry();
    std::string getTemp();
    std::string getFeel();
};

#endif