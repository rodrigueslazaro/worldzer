#pragma once


typedef enum {
    lawful_good,
    lawful_neutral,
    lawful_evil,
    neutral_good,
    neutral_neutral,
    neutral_evil,
    chaotic_good,
    chaotic_neutral,
    chaotic_evil
} alignment;

typedef enum {
    male,
    female
} sex;

typedef struct {
    int build;
    bool nanism;
    bool lost_limb;
    string disability;
} bone_structure;

typedef struct {
    string color;
    int fur;
    string texture;
    bool alopecia;
} hair;

typedef struct {
    string color;
    bool vitiligo;
} skin;

typedef struct {
    sex sex;
    bone_structure structure;
    int height;
    skin skin;
    hair hair;
} body;

typedef struct {
    int width;
    int definition;
} jaw;

typedef struct {
    int width;
    int length;
    int bridge;
} nose;

typedef struct {
    int width;
    int forward;
} chin;

typedef struct {
    bool heterochromia;
    string left;
    string right;
    int size;
    int monolid;
} eyes;

typedef struct {
    jaw jaw;
    chin chin;
    eyes eyes;
    nose nose;
    int width;
    int height;
    int lips;
    int brow_forward;
    int cheeckbone_height;
} face;

typedef struct {
    int num;
    time_point birth;
    time_point death;
} age;

class Character {
public:
    Character Character();
private:
    string species;
    strig ethnicity;
    string culture;
    string subculture;
    body body;
    face face;
    age age;
};