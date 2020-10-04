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

#ifndef _CONTROLLER_
#define _CONTROLLER_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>

//#include "../Model/Model.h"
#include "../view/view.h"

#define STATUS_START        0
#define STATUS_LOOP         1
#define STATUS_QUIT         2

class Controller {
private:
  View view;
  int gamestatus;
  float xScale, yScale;

public:
  Controller();
  void doIntro();
  void Loop();
  void showUI();
};

#endif