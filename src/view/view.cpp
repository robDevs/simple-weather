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


#include "view.h"

View *View::s_instance = 0;

void sprite_sheet::setFrames(std::string path, float xScale, float yScale) {
    float x = 0;
    float y = 0;

    Image tempImage;

    //empty the frames vector #spritesheet scaling bug fix attempt 1
    while(!frames.empty()) {
        frames.pop_back();
    }

    tempImage = LoadImage(path.c_str());
    ImageResizeNN(&tempImage, (float)tempImage.width * xScale, (float)tempImage.height * yScale);
    texture = LoadTextureFromImage(tempImage);
    UnloadImage(tempImage);

    float x_frames = (float) texture.width / (frameWidth * xScale);
    float y_frames = (float) texture.height / (frameHeight * yScale);
    std::cout << "-----------frames: " <<  x_frames * y_frames << std::endl;
    for(int i = 0; i < x_frames * y_frames; i++) {
        frame currentFrame;
        currentFrame.x = x;
        currentFrame.y = y;
        currentFrame.width = frameWidth*xScale;
        currentFrame.height = frameHeight*yScale;

        frames.push_back(currentFrame);

        x += frameWidth*xScale;
        if(x >= texture.width) {
            x = 0;
            y += frameHeight*xScale;
        }
    }
}

void sprite_sheet::unloadTexture() {
  UnloadTexture(texture);
}

textBox::textBox(int x, int y, int w, int h, int max) {
    for(int i = 0; i < MAX_INPUT_CHARS + 1; i++) {
        message[i] = '\0';
    }
    this->rect.x = x;
    this->rect.y = y;
    this->rect.width = w;
    this->rect.height = h;
    this->max = max;
    this->mouseOnText = false;
    this->letterCount = 0;
    this->framesCounter = 0;
}

void textBox::update() {

    if (CheckCollisionPointRec(GetMousePosition(), rect)) mouseOnText = true;
    else mouseOnText = false;

    if (mouseOnText)
    {
        int key = GetKeyPressed();

        // NOTE: Only allow keys in range [32..125]
        if ((key >= 32) && (key <= 125) && (letterCount < max))
        {
            message[letterCount] = (char)key;
            letterCount++;
        }

        if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0)
        {
            letterCount--;
            message[letterCount] = '\0';

            if (letterCount < 0) letterCount = 0;
        }
    }

    if (mouseOnText) framesCounter++;
    else framesCounter = 0;
}

void textBox::draw() {
    DrawRectangleRec(rect, LIGHTGRAY);

    if (mouseOnText) DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, RED);
    else DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, DARKGRAY);

    DrawText(message, rect.x + 5, rect.y + 8, 20, RED);

    if (mouseOnText)
    {
        if (letterCount < MAX_INPUT_CHARS)
        {
            // Draw blinking underscore char
            if (((framesCounter/20)%2) == 0) DrawText("_", rect.x + 8 + MeasureText(message, 20), rect.y + 12, 20, VIOLET);
        }
    }
}

void textBox::setMessage(const char newMessage[MAX_INPUT_CHARS + 1]) {
  for(int i = 0; i < MAX_INPUT_CHARS + 1; i++) {
    if(newMessage[i] == ' ' || newMessage[i] == NULL || !newMessage[i])
      break;
    message[i] = newMessage[i];
    letterCount++;
  }
}

void View::initView(int width, int height, float *xScale, float *yScale) {
  screenWidth = width;
  screenHeight = height;

  *xScale = screenWidth/1280.00;
  *yScale = screenHeight/720.00;

  if(!IsAudioDeviceReady()) InitAudioDevice();


  if(!IsWindowReady()) InitWindow(screenWidth, screenHeight, "simple-weather");
  else SetWindowSize(width, height);

  SetWindowPosition(0, 0);

  freeTextures();

  loadTextures(*xScale, *yScale);

 // sprite_sheets[0].frameWidth = 400;
 // sprite_sheets[0].frameHeight = 400;
 // sprite_sheets[0].setFrames("assets/BurstEffect/Burst_SpriteSheet.png", *xScale, *yScale);

  //sounds[0] = LoadSound("assets/Audio/Music/Alert\ Bagel\ Danger\ BulletDarkness.mp3");

  for(int i = 0; i < 1; i++) {
      //SetSoundVolume(sounds[i], 0.1);
  }

  SetTargetFPS(60);

  //SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
}

void View::setFullScreen(float *xScale, float *yScale) {
    ToggleFullscreen();

    initView(GetScreenWidth(), GetScreenHeight(), xScale, yScale);
}

void View::setScale(float width, float height,float *xScale, float *yScale) {
    screenWidth = width;
    screenHeight = height;

    *xScale = width/1280.00;
    *yScale = height/720.00;
}

void View::loadTextureTemplate(int index, std::string path) {
    Image tempImage;
  
    tempImage = LoadImage(path.c_str());
    ImageResizeNN(&tempImage, tempImage.width * 2, tempImage.height * 2);
    textures[index] = LoadTextureFromImage(tempImage);
    UnloadImage(tempImage);
}

bool View::loadTextures(float xScale, float yScale) {
    Image tempImage;

    for(int i = 0; i < 18; i++) {
        UnloadTexture(textures[i]);
    }

    std::string path = " ";

    path = "assets/01d.png";
    loadTextureTemplate(0, path);
    path = "assets/01n.png";
    loadTextureTemplate(1, path);

    path = "assets/02d.png";
    loadTextureTemplate(2, path);
    path = "assets/02n.png";
    loadTextureTemplate(3, path);

    path = "assets/03d.png";
    loadTextureTemplate(4, path);
    path = "assets/03n.png";
    loadTextureTemplate(5, path);

    path = "assets/04d.png";
    loadTextureTemplate(6, path);
    path = "assets/04n.png";
    loadTextureTemplate(7, path);

    path = "assets/09d.png";
    loadTextureTemplate(8, path);
    path = "assets/09n.png";
    loadTextureTemplate(9, path);

    path = "assets/10d.png";
    loadTextureTemplate(10, path);
    path = "assets/10n.png";
    loadTextureTemplate(11, path);

    path = "assets/11d.png";
    loadTextureTemplate(12, path);
    path = "assets/11n.png";
    loadTextureTemplate(13, path);

    path = "assets/13d.png";
    loadTextureTemplate(14, path);
    path = "assets/13n.png";
    loadTextureTemplate(15, path);

    path = "assets/50d.png";
    loadTextureTemplate(16, path);
    path = "assets/50n.png";
    loadTextureTemplate(17, path);
}

void View::freeTextures() {
    for(int i = 0; i < 18; i++) {
        UnloadTexture(textures[i]);
    }
    for(int i = 0; i < 0; i++) {
      sprite_sheets[i].unloadTexture();
    }
}

void View::freeSounds() {
  for(int i = 0; i < 0; i++) {
    UnloadSound(sounds[i]);
  }
  CloseAudioDevice();
}

void View::startFrame() {
  BeginDrawing();
  ClearBackground(BLACK);
}

void View::endFrame() {
  EndDrawing();
}

bool View::getWindowStatus() {
  return WindowShouldClose();
}

void View::drawTexture(int x, int y, int texture, Color color) {
  DrawTexture(textures[texture], x, y, color);
}

void View::drawSprite(int x, int y, int spriteSheet, int frame, Color color) {
    Rectangle rect;
    rect.x = sprite_sheets[spriteSheet].frames[frame].x;
    rect.y = sprite_sheets[spriteSheet].frames[frame].y;
    rect.width = sprite_sheets[spriteSheet].frames[frame].width;
    rect.height = sprite_sheets[spriteSheet].frames[frame].height;
    DrawTextureRec(sprite_sheets[spriteSheet].texture, rect, (Vector2) {x, y}, color);
}

void View::drawText(std::string text, int x, int y, int size, Color color) {
  DrawText(text.c_str(), x, y, size, color);
}

float View::getScreenWidth() {
    return GetScreenWidth();
}

float View::getScreenHeight() {
    return screenHeight;
}

int View::getTextureWidth(int i) {
    return textures[i].width;
}

int View::getTextureHeight(int i) {
    return textures[i].height;
}

void View::drawRectBorders(int x, int y, int w, int h, Color color_outline, Color color_fill) {
  DrawRectangle(x,y,w,h,color_fill);
  DrawRectangleLines(x,y,w,h,color_outline);
  DrawRectangleLines(x+1,y+1,w-2,h-2,color_outline);
}

void View::readFolder(std::string path, std::vector<std::string> *list) {
  int fileCount = 0;
  char **files = GetDirectoryFiles(path.c_str(), &fileCount);

  for(int i = 0; i < fileCount; i++) {
      std::string fileName = GetFileNameWithoutExt(files[i]);
      if(fileName.length() > 2)
        list->push_back(fileName);
  }

  ClearDirectoryFiles();
}

void View::playSound(int sound) {
  PlaySound(sounds[sound]);
}

void View::stodSound(int sound) {
  StopSound(sounds[sound]);
}

void View::loopSound(int sound) {
    if(!IsSoundPlaying(sounds[sound])) PlaySound(sounds[sound]);
}