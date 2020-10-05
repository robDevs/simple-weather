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

#include "city.h"
#include "tools/curl-tools.h"
#include "tools/cJSON.h"

void City::init(int id, std::string key) {
    std::string url = "https://api.openweathermap.org/data/2.5/onecall?units=imperial&lat=46.87215&lon=-113.994003&exclude=hourly,daily,minutely&appid=";
    url += key;

    json = curl_get_string(url);

    fprintf(stderr, "Error before: %s\n", json.c_str());

    const cJSON *weather_json = NULL;
    const cJSON *weather_items_json = NULL;
    const cJSON *temp_json = NULL;
    const cJSON *feels_json = NULL;
    const cJSON *current_json = NULL;
    int status = 0;
    cJSON *weather = cJSON_Parse(json.c_str());
    if (weather == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        status = 0;
        return;
    }

    current_json = cJSON_GetObjectItemCaseSensitive(weather, "current");

    temp_json = cJSON_GetObjectItemCaseSensitive(current_json, "temp");
    feels_json = cJSON_GetObjectItemCaseSensitive(current_json, "feels_like");

    if(cJSON_IsNumber(temp_json)) {
        temp = temp_json->valuedouble;
    }

    if(cJSON_IsNumber(feels_json)) {
        feels_like = feels_json->valuedouble;
    }
}
std::string City::getName() {
    return "  ";
}
std::string City::getState() {
    return " ";
}
std::string City::getCountry() {
    return " ";
}

std::string City::getTemp() {
    return std::to_string(temp);
}
std::string City::getFeel() {
    return std::to_string(feels_like);
}