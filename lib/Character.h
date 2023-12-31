#pragma once
#include <string>
#include <vector>
#include "rapidjson/document.h"
using namespace std;

enum alignment {
    lawful_good,
    lawful_neutral,
    lawful_evil,
    neutral_good,
    neutral_neutral,
    neutral_evil,
    chaotic_good,
    chaotic_neutral,
    chaotic_evil
};

enum sex {
    male,
    female
};

struct body_structure {
    int build;
    vector<string> disability;
};

struct hair {
    string color;
    int fur;
    string texture;
    bool alopecia;
};

struct skin {
    string color;
};

struct body {
    enum sex sex;
    struct body_structure structure;
    int height;
    struct skin skin;
    struct hair hair;
};

struct jaw{
    int width;
    int definition;
};

struct nose{
    int width;
    int length;
    int bridge;
};

struct chin{
    int width;
    int forward;
};

struct eyes{
    string left;
    string right;
    int size;
    int monolid;
};

struct face{
    struct jaw jaw;
    struct chin chin;
    struct eyes eyes;
    struct nose nose;
    int width;
    int height;
    int lips;
    int brow_forward;
    int cheeckbone_height;
};

struct calendar_date{
    int year;
    int month;
    int day;
    int age;
};

struct age {
    int num;
    struct calendar_date birth;
    struct calendar_date death;
};

enum sexuality {
    straight,
    bisexual,
    homosexual
};

struct brain {
    /* 0-9 */
    int resilience;
    int flexibility;
    int intelligence;
    enum sexuality sexuality;
};

struct mind {
    /* 0-20 */
    int extroversion;
    int creativity;
    int rationality;
    int organization;
    int assertiveness;
};

struct views {
    /* 0-9 */
    int authorities;
    int individualism;
    int tradition;
    int hedonism;
    int religion;
};

struct scores {
    int strenght;
    int dexterity;
    int constitution;
    int cleverness;
    int wisdom;
    int charisma;
};

struct skills {
    /* 0-20 */
    struct scores scores;
    vector<string> languages;
};

class Character {
public:
    Character(string spc = "", string eth = "", string cul = "", string sub = "", int alive = 713, int age = -1);
    void getDBs();
    void setSpecies(string spc) {species = spc;};
    void setEthnicity(string eth) {species = eth;};
    void setCulture(string cul) {species = cul;};
    void setSubculture(string sub) {species = sub;};
    string getSpecies() {return species;};
    string getEthnicity() {return ethnicity;};
    string getCulture() {return culture;};
    string getSubculture() {return subculture;};
    void printCharacter();
private:
    rapidjson::Document speciesdb;
    rapidjson::Document ethnicitiesdb;
    rapidjson::Document culturesdb;
    rapidjson::Document subculturesdb;
    void setRandSpecies();
    void setRandEthnicity();
    void setRandCulture();
    void setRandSubculture();
    void setAge(int alive, int age);
    void setBody();
    void setMindAndSkills();
    string species;
    string ethnicity;
    string culture;
    string subculture;
    struct body body;
    struct face face;
    struct age age;

    struct brain brain;
    struct mind mind;
    struct views views;


};