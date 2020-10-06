# simple-weather
A weather app designed with a simple user interface. Built with [RayLib](https://www.raylib.com/index.html).

## About 
This application pulls weather data from [OpenWeather](https://www.raylib.com/index.html). The data is fetched over HTTP using [libCurl](https://curl.haxx.se/libcurl/). Once recieved the data is parsed using [cJSON](https://github.com/DaveGamble/cJSON).

## Why
The project was created for a class called Object Oriented Programming at the University of Montana. The goal was to build a project using a Model View Controller design pattern, a creational pattern, and another design or behavioral pattern. For my project I used the Singleton pattern to create the view which ensures that only one instance of the view is ever created. I also used a Facade pattern to bundle all of the functions for fetching, parsing, and returning weather data for a given location. This allows the controller to only worry about pulling data from a city and using that with the view to create a usable application. The controller does not have to worry about how data is fetched or parsed.

## Dependencies
 - [RayLib](https://www.raylib.com/index.html)
 - [LibCurl](https://curl.haxx.se/libcurl/)
 - [cJSON](https://github.com/DaveGamble/cJSON)
 
 ## Compiling & running
 This project was made for Linux. 
 ```
 $ git clone https://github.com/robDevs/simple-weather.git
 $ cd simple-weather/src
 $ make
 $ ./simple-weather
```
