#pragma once

typedef enum {
    island,
    continent,
    water
} type;

class Cell {
public:
    Cell Cell(){};

private:
    string name;
    float area;
    float latitude;
    float longitude;
    type type;
    int precipitation;
    bool river;
    int population;
    int elevation;
    int temperature;
    
    
}