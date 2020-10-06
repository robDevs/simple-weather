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

#include "controller.h"

Controller::Controller() {
  gamestatus = STATUS_LOOP;
  xScale = 1;
  yScale = 1;

  View::instance()->initView(1280,720, &xScale, &yScale);

  city.init(1, "885c28e2cc75e558523fd7d325efb1df");

  city_input.init(30, 720 - 50, 200, 40, 100);

  Loop();
}

void Controller::doIntro() {
    //coming soon
}

void Controller::Loop() {
    while(!View::instance()->getWindowStatus() && gamestatus != STATUS_QUIT) {
    //doIntro(); //un-comment to test sprites after re-scaling.
    if(gamestatus == STATUS_START) {
      doIntro();
    }

    if(gamestatus == STATUS_LOOP) {
        showUI();
    }
    
  }
  View::instance()->freeTextures();
  //view.freeSounds();
}

void Controller::drawDay(int x, int index) {
    View::instance()->drawRectBorders(x, 30 + 45 + 10, 240, 400, WHITE, BLACK);

    View::instance()->drawText(city.get_day_time(index, 0), x + 10, 30 + 45 + 10, 25, WHITE);
    View::instance()->drawText(city.get_day_time(index, 1), x + 10, 30 + 45 + 10 + 30, 25, WHITE);

    View::instance()->drawTexture(x, 30 + 65, city.get_day_icon(index), WHITE);

    std::string weather_string = city.get_day_desc(index);
    View::instance()->drawText(weather_string.c_str(), x + 10, 30 + 150 + 100, 25, WHITE);

    weather_string = "High: " + city.get_day_high(index);
    View::instance()->drawText(weather_string.c_str(), x + 10, 30 + 150 + 100 + 45, 35, WHITE);

    weather_string = "Low: " + city.get_day_low(index);
    View::instance()->drawText(weather_string.c_str(), x + 10, 30 + 150 + 100 + 45 + 45, 35, WHITE);
}

void Controller::showUI() {
    city_input.update();
    View::instance()->startFrame();

    View::instance()->drawRectBorders(10, 10, 1280 - 20, 720 - 80, WHITE, BLACK);

    city_input.draw();

    View::instance()->drawText("Missoula Montana, US", 1280 / 2 - MeasureText("Missoula Montana, US", 45) / 2, 30, 45, GRAY);

    View::instance()->drawText("Feels Like:", 1280 - 20 - MeasureText("Feels Like:", 45), 720 - 80 - 55 - 55, 45, GRAY);
    View::instance()->drawText(city.getFeel(), 1280 - 20 - MeasureText(city.getFeel().c_str(), 55), 720 - 80 - 55, 55, WHITE);

    View::instance()->drawText("Current Temp:", 20, 720 - 80 - 55 - 60, 45, GRAY);

    View::instance()->drawText(city.getTemp(), 20, 720 - 80 - 55, 55, WHITE);

    View::instance()->drawTexture(1280 / 2 - 100, 720 - 80 - 55 - 140, city.getIcon(), WHITE);
    View::instance()->drawText(city.getDesc(), 1280 / 2 - MeasureText(city.getDesc().c_str(), 55) / 2, 720 - 80 - 55, 55, WHITE);

    for(int i = 0; i < 5; i++) {
      drawDay(20+i*250, i);
    }

    View::instance()->endFrame();
}