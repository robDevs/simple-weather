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

#include <iomanip>      // std::put_time
#include <ctime>        // std::time_t, struct std::tm, std::localtime
#include <chrono>       // std::chrono::system_clock
#include <sstream> 

int icon_to_int(std::string input) {
    if(input.compare("01d") == 0) return 0;
    if(input.compare("01n") == 0) return 1;
    if(input.compare("02d") == 0) return 2;
    if(input.compare("02n") == 0) return 3;
    if(input.compare("03d") == 0) return 4;
    if(input.compare("03n") == 0) return 5;
    if(input.compare("04d") == 0) return 6;
    if(input.compare("04n") == 0) return 7;
    if(input.compare("09d") == 0) return 8;
    if(input.compare("09n") == 0) return 9;
    if(input.compare("10d") == 0) return 10;
    if(input.compare("10n") == 0) return 11;
    if(input.compare("11d") == 0) return 12;
    if(input.compare("11n") == 0) return 13;
    if(input.compare("13d") == 0) return 14;
    if(input.compare("13n") == 0) return 15;
    if(input.compare("50d") == 0) return 16;
    if(input.compare("50n") == 0) return 17; 
}

void City::init(int id, std::string key) {
    std::string url = "https://api.openweathermap.org/data/2.5/onecall?units=imperial&lat=46.87215&lon=-113.994003&exclude=hourly,minutely&appid=";
    url += key;

    json = curl_get_string(url);

    //fprintf(stderr, "Error before: %s\n", json.c_str());

    const cJSON *weather_json = NULL;
    const cJSON *weather_items_json = NULL;
    const cJSON *temp_json = NULL;
    const cJSON *feels_json = NULL;
    const cJSON *current_json = NULL;
    const cJSON *days_json = NULL;
    const cJSON *day_json = NULL;
    int status = 0;
    cJSON *data = cJSON_Parse(json.c_str());
    if (data == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        status = 0;
        return;
    }

    current_json = cJSON_GetObjectItemCaseSensitive(data, "current");
    days_json = cJSON_GetObjectItemCaseSensitive(data, "daily");

    temp_json = cJSON_GetObjectItemCaseSensitive(current_json, "temp");
    feels_json = cJSON_GetObjectItemCaseSensitive(current_json, "feels_like");

    if(cJSON_IsNumber(temp_json)) {
        temp = temp_json->valuedouble;
    }

    if(cJSON_IsNumber(feels_json)) {
        feels_like = feels_json->valuedouble;
    }

    weather_json = cJSON_GetObjectItemCaseSensitive(current_json, "weather");

    cJSON_ArrayForEach(weather_items_json, weather_json) {
        cJSON *desc_json = cJSON_GetObjectItemCaseSensitive(weather_items_json, "description");
        cJSON *icon_json = cJSON_GetObjectItemCaseSensitive(weather_items_json, "icon");

        weather_desc = desc_json->valuestring;
        std::string icon_temp = icon_json->valuestring;

        icon = icon_to_int(icon_temp);        
    }

    int count = 0;
    printf("\n%s", days_json->valuestring);
   cJSON_ArrayForEach(day_json, days_json) {
        //printf("iteration: %d", count);
        cJSON *temp = cJSON_GetObjectItemCaseSensitive(day_json, "temp");
        cJSON *high_json = cJSON_GetObjectItemCaseSensitive(temp, "max");
        cJSON *low_json = cJSON_GetObjectItemCaseSensitive(temp, "min");
        cJSON *time_json = cJSON_GetObjectItemCaseSensitive(day_json, "dt");

        cJSON *weather = NULL;    
        cJSON *weather_items = cJSON_GetObjectItemCaseSensitive(day_json, "weather");
        cJSON *desc_json = NULL;
        cJSON *icon_json = NULL;
        cJSON_ArrayForEach(weather, weather_items) {
            desc_json = cJSON_GetObjectItemCaseSensitive(weather, "description");
            icon_json = cJSON_GetObjectItemCaseSensitive(weather, "icon");        
        }

        days[count].high = high_json->valuedouble;
        days[count].low = low_json->valuedouble;
        days[count].weather_desc = desc_json->valuestring;
        days[count].icon = icon_to_int(icon_json->valuestring);
        days[count].time = time_json->valuedouble;

        if(count >= 4) break;
        count++;
    }


    cJSON_Delete(data);
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
    return std::to_string(temp).substr(0,4);
}
std::string City::getFeel() {
    return std::to_string(feels_like).substr(0,4);
}

int City::getIcon() {
    return icon;
}
std::string City::getDesc() {
    return weather_desc;
}

std::string City::get_day_high(int index) {
    return std::to_string(days[index].high).substr(0,4);
}

std::string City::get_day_low(int index) {
    return std::to_string(days[index].low).substr(0,4);
}

std::string City::get_day_desc(int index) {
    return days[index].weather_desc;
}

int City::get_day_icon(int index) {
    return days[index].icon;
}

std::string City::get_day_time(int index, int style) {
    std::uint32_t time_date_stamp = days[index].time;
    std::time_t temp = time_date_stamp;
    std::tm* t = std::gmtime(&temp);
    std::stringstream ss; // or if you're going to print, just input directly into the output stream
    if(style == 0) ss << std::put_time(t, "%A");
    if(style == 1) ss << std::put_time(t, "%x");
    std::string output = ss.str();
    return output;
}