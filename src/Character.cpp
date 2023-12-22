#include "Character.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

Character::Character(string spc, string eth, string cul, string sub) {
    getDBs();
    (spc != "") ? setSpecies(spc) : setRandSpecies();
    (eth != "") ? setEthnicity(eth) : setRandEthnicity();
}

void Character::setRandEthnicity() {
    srand(static_cast<unsigned int>(time(nullptr)));
    bool selected = 0;
    while (not selected) {
        const rapidjson::Value& neweth = ethnicitiesdb[rand() % (ethnicitiesdb.Size())];
        cout << "species: " << neweth["species"].GetString() << endl;
        cout << "currentspecies: " << species << endl;
        if (neweth["species"].GetString() == species) {
            selected = 1;
            ethnicity = neweth["name"].GetString();
        }
    }
}
void Character::setRandSpecies() {
    srand(static_cast<unsigned int>(time(nullptr)));
    const rapidjson::Value& newspc = speciesdb[rand() % (speciesdb.Size()-1)];
    species = newspc["species"].GetString();
}
void Character::setRandCulture() {
    srand(static_cast<unsigned int>(time(nullptr)));
    const rapidjson::Value& newcul = culturesdb[rand() % (culturesdb.Size()-1)];
    culture = newcul["name"].GetString();
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

