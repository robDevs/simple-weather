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

void Controller::showUI() {
    View::instance()->startFrame();

    View::instance()->drawRectBorders(10, 10, 1280 - 20, 720 - 80, WHITE, BLACK);

    View::instance()->drawText("Missoula Montana, US", 1280 / 2 - MeasureText("Missoula Montana, US", 45) / 2, 30, 45, GRAY);

    View::instance()->drawText("Feels Like:", 1280 - 20 - MeasureText("Feels Like:", 45), 720 - 80 - 55 - 55, 45, GRAY);
    View::instance()->drawText(city.getFeel(), 1280 - 20 - MeasureText(city.getFeel().c_str(), 55), 720 - 80 - 55, 55, WHITE);

    View::instance()->drawText("Current Temp:", 20, 720 - 80 - 55 - 60, 45, GRAY);

    View::instance()->drawText(city.getTemp(), 20, 720 - 80 - 55, 55, WHITE);

    View::instance()->endFrame();
}