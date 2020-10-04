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

  view.initView(1280,720, &xScale, &yScale);

  Loop();
}

void Controller::doIntro() {
    //coming soon
}

void Controller::Loop() {
    while(!view.getWindowStatus() && gamestatus != STATUS_QUIT) {
    //doIntro(); //un-comment to test sprites after re-scaling.
    if(gamestatus == STATUS_START) {
      doIntro();
    }

    if(gamestatus == STATUS_LOOP) {
        showUI();
    }
    
  }
  view.freeTextures();
  view.freeSounds();
}

void Controller::showUI() {
    view.startFrame();

    view.endFrame();
}