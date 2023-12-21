#pragma once;

typedef enum {
    human,
    dwarf,
    mast,
    sakin,
    holgen,
    hizdal,
    ilz,
    felcin,
    izmiin
} species;

typedef enum {
    very_dark,
    dark,
    brown,
    light_brown,
    white,
    very_white,
    blue,
    yellow,
    ocre,
    red,
    green,
    orange
} colors;

typedef struct {
    int height;
    int weight;
    int size;
    int skin;
    pair<colors, colors> eyes;
    int beauty;
} apperance;

typedef stryct {
    int age;
    int birth;
    int death;
} age;

typedef struct {
    int eye_size;
    int chin_width;
    int chin_forward;
    int jaw_definition;
    int face_width;
    int face_height;
    int brow_forward;
    int nose_forward;
    int nose_bridge;
    int nose_width;
    int lip_size;
} face;

class Character {
public:
    Character Character();
private:
    int age;
    int birth;
    int death;
    species species;
    apperance apperance;

};