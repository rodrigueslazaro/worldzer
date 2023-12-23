#include "Character.h"
#include "constants.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <random>
using namespace std;

Character::Character(string spc, string eth, string cul, string sub, int alive, int age) {
    getDBs();
    (spc != "") ? setSpecies(spc) : setRandSpecies();
    setAge(alive, age);
    (eth != "") ? setEthnicity(eth) : setRandEthnicity();
    setBody();
    setFace();
    (cul != "") ? setCulture(cul) : setRandCulture();
}

void Character::printCharacter() {
    cout << "Species: " << species << endl;
    cout << "Ethnicity: " << ethnicity << endl;
    cout << "Culture: " << culture << endl;
    cout << "Age: " << age.num << endl;
    cout << "Birth: " << age.birth.year << "-" << age.birth.month << "-" << age.birth.day << endl;
    cout << "Death: " << age.death.year << "-" << age.death.month << "-" << age.death.day << endl;
    cout << "Death age: " << age.death.year - age.birth.year << endl;
}

void Character::setAge(int alive, int age) {
    random_device rd;
    mt19937 gen(rd());
    struct age newage;
    int maxage;
    /* get lifespan */
    for (unsigned int i=0; i<speciesdb.Size(); i++)
        if (speciesdb[i]["species"].GetString() == species)
            maxage = speciesdb[i]["lifespan"].GetFloat();
    if (age == -1) {
        uniform_int_distribution<> distr(maxage/10,maxage-(maxage/5));
        age = distr(gen);
    }
    newage.birth.year = CURRENT_YEAR - age;
    uniform_int_distribution<> distrm(1,MONTHS_IN_YEAR);
    newage.birth.month = distrm(gen);
    newage.death.month = distrm(gen);
    uniform_int_distribution<> distrd(1,DAYS_IN_MONTH);
    newage.birth.day = distrd(gen);
    newage.death.day = distrd(gen);
    uniform_int_distribution<> distr(1,maxage-age);
    newage.death.year = CURRENT_YEAR + distr(gen);
    newage.num = age;
    this->age = newage;
};

void Character::setBody() {

};

void Character::setFace() {

};

void Character::setRandEthnicity() {
    srand(static_cast<unsigned int>(time(nullptr)));
    vector<string> possibleeth;
    for (unsigned int i=0; i<ethnicitiesdb.Size(); i++) {
        if (ethnicitiesdb[i]["species"].GetString() == species)
            possibleeth.push_back(ethnicitiesdb[i]["name"].GetString());
    }
    ethnicity = possibleeth[rand() % (possibleeth.size())];
}

void Character::setRandSpecies() {
    srand(static_cast<unsigned int>(time(nullptr)));
    const rapidjson::Value& newspc = speciesdb[rand() % (speciesdb.Size()-1)];
    species = newspc["species"].GetString();
}

void Character::setRandCulture() {
    srand(static_cast<unsigned int>(time(nullptr)));
    vector<string> possiblecul;
    for (unsigned int i=0; i<culturesdb.Size(); i++) {
        if (culturesdb[i]["ethnicity"].GetString() == ethnicity)
            possiblecul.push_back(culturesdb[i]["name"].GetString());
    }
    culture = possiblecul[rand() % (possiblecul.size())];
}

void Character::setRandSubculture() {
    srand(static_cast<unsigned int>(time(nullptr)));
    const rapidjson::Value& newsub = subculturesdb[rand() % (subculturesdb.Size()-1)];
    subculture = newsub["name"].GetString();
}

void Character::getDBs() {
    ifstream spcfile("data/species.json");
    if (spcfile.is_open()) {
        string jsonData;
        string line;
        while (getline(spcfile, line))
            jsonData += line + "\n";
        speciesdb.Parse(jsonData.c_str());
        if (speciesdb.HasParseError())
            cerr << "Error parsing JSON." << endl;
        if (!speciesdb.IsArray())
            cerr << "JSON is not an array." << endl;
    } else
        cerr << "Species file does not exist!" << endl;
    ifstream ethfile("data/ethnicities.json");
    if (ethfile.is_open()) {
        string jsonData;
        string line;
        while (getline(ethfile, line))
            jsonData += line + "\n";
        ethnicitiesdb.Parse(jsonData.c_str());
        if (ethnicitiesdb.HasParseError())
            cerr << "Error parsing JSON." << endl;
        if (!ethnicitiesdb.IsArray())
            cerr << "JSON is not an array." << endl;
    } else
        cerr << "Ethnicities file does not exist!" << endl;
    ifstream culfile("data/cultures.json");
    if (culfile.is_open()) {
        string jsonData;
        string line;
        while (getline(culfile, line))
            jsonData += line + "\n";
        culturesdb.Parse(jsonData.c_str());
        if (culturesdb.HasParseError())
            cerr << "Error parsing JSON." << endl;
        if (!culturesdb.IsArray())
            cerr << "JSON is not an array." << endl;
    } else
        cerr << "Cultures file does not exist!" << endl;
    ifstream subfile("data/subcultures.json");
    if (subfile.is_open()) {
        string jsonData;
        string line;
        while (getline(subfile, line))
            jsonData += line + "\n";
        subculturesdb.Parse(jsonData.c_str());
        if (subculturesdb.HasParseError())
            cerr << "Error parsing JSON." << endl;
        if (!subculturesdb.IsArray())
            cerr << "JSON is not an array." << endl;
    } else
        cerr << "Subcultures file does not exist!" << endl;
}

