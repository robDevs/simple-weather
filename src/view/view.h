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

 
#ifndef _VIEW_
#define _VIEW_

#include "raylib.h"

#include <string>
#include <vector>

#include <iostream>

#define BG_00001        1

#define BURST_SPRITESHEET             0

#define SONG_ALERT                    0

#define MAX_INPUT_CHARS     30

//-------------------------------------------------------------------------------------------
// Control info struct.
// Allows the controller (controller.h) not worry about the button and only the action.
//-------------------------------------------------------------------------------------------

struct frame {
    float x;
    float y;
    float width;
    float height;
};

struct sprite_sheet {
    Texture2D texture;
    float frameWidth;
    float frameHeight;
    std::vector<frame> frames;
    void setFrames(std::string path, float xScale, float yScale);
    void unloadTexture();
};

struct textBox{
    char message[MAX_INPUT_CHARS + 1];
    Rectangle rect;
    int max;
    bool mouseOnText;
    int letterCount;
    int framesCounter;
    textBox(int x, int y, int w, int h, int max);
    void update();
    void draw();
    void setMessage(const char newMessage[MAX_INPUT_CHARS + 1]);
};

//------------------------------------------------------------------------------------------
// The view handles drawing things and getting input from user.
//------------------------------------------------------------------------------------------
class View {
private:
  float screenWidth;
  float screenHeight;
  Texture2D textures[1];
  sprite_sheet sprite_sheets[1];

  Sound sounds[1];

public:
  void initView(int width, int height, float *xScale, float *yScale); // Create a window with the given attributes.
  void setFullScreen(float *xScale, float *yScale);
  void setScale(float width, float height,float *xScale, float *yScale);
  void startFrame();
  void endFrame();
  bool getWindowStatus(); // check if the window should close (If x thing was pressed. )
  bool loadTextures(float xScale, float yScale); //return false if textures failed to load.
  void freeTextures();
  void drawTexture(int x, int y, int texture, Color color); // Draws a texture at the given pos.
  void drawText(std::string text, int x, int y, int size, Color color); // draws text at given pos.

  void drawSprite(int x, int y, int spriteSheet, int frame, Color color);

  float getScreenWidth();
  float getScreenHeight();

  int getTextureWidth(int i);
  int getTextureHeight(int i);

  void drawRectBorders(int x, int y, int h, int w, Color color_outline, Color color_fill);

  void readFolder(std::string path, std::vector<std::string> *list);
  void freeSounds();

  void playSound(int Sound);
  void stodSound(int Sound);
  void loopSound(int Sound);
};

#endif
