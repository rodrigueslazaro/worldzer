#include "Character.h"
#include "constants.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <random>
#include <string>
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
    cout << "Sex: " << body.sex << endl;
    cout << "Birth: " << age.birth.year << "-" << age.birth.month << "-" << age.birth.day << endl;
    cout << "Death: " << age.death.year << "-" << age.death.month << "-" << age.death.day << endl;
    cout << "Death age: " << age.death.year - age.birth.year << endl;
    cout << "Hair texutre: " << body.hair.texture << endl;
    cout << "Height: " << body.height << endl;
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
    random_device rd;
    mt19937 gen(rd());
    struct body newbody;
    /* get ethnicity */
    for (rapidjson::SizeType i=0; i<ethnicitiesdb.Size(); i++) {
        if (ethnicitiesdb[i]["name"].GetString() == ethnicity) {
            uniform_int_distribution<> randsex(0,1);
            newbody.sex = static_cast<enum sex>(randsex(gen));
            uniform_int_distribution<> randheight(static_cast<int>(ethnicitiesdb[i]["min-height"].GetFloat()),static_cast<int>(ethnicitiesdb[i]["max-height"].GetFloat()));
            newbody.height = randheight(gen);
            uniform_int_distribution<> randgenetic(0,10000);
            newbody.hair.alopecia = !randgenetic(gen);
            newbody.skin.vitiligo = !randgenetic(gen);
            newbody.structure.nanism = !randgenetic(gen);
            newbody.structure.hasdisability = !randgenetic(gen);
            if (newbody.structure.hasdisability) {
                vector<string> bodyparts = {
                    "right-hand",
                    "right-elbow",
                    "right-arm",
                    "right-feet",
                    "right-knee",
                    "right-leg",
                    "left-hand",
                    "left-elbow",
                    "left-arm",
                    "left-feet",
                    "left-knee",
                    "left-leg",
                    "partial blindness",
                    "total blindness",
                    "deafness",
                };
                uniform_int_distribution<> randdis(0,14);
                newbody.structure.disability = bodyparts[randdis(gen)];
            }
            uniform_int_distribution<> pm2(-2,2);
            newbody.hair.fur = static_cast<int>(ethnicitiesdb[i]["body-hair"].GetFloat()) + pm2(gen);
            (newbody.hair.fur > 9) ? newbody.hair.fur = 9:0;
            (newbody.hair.fur < 0) ? newbody.hair.fur = 0:0;
            rapidjson::Value::Array textures = ethnicitiesdb[i]["hair-textures"].GetArray();
            uniform_int_distribution<> randtexture(0,textures.Size()-1);
            newbody.hair.texture = textures[randtexture(gen)].GetString();
            rapidjson::Value::Array colors = ethnicitiesdb[i]["hair-colors"].GetArray();
            uniform_int_distribution<> randcolor(0,colors.Size()-1);
            newbody.hair.color = colors[randcolor(gen)].GetString();
            rapidjson::Value::Array skin = ethnicitiesdb[i]["skin-color"].GetArray();
            uniform_int_distribution<> randskin(0,skin.Size()-1);
            uniform_int_distribution<> randtone(1,5);
            newbody.hair.color = str(skin[randcolor(gen)].GetString()) + "-" + to_string(randtone(gen));
            body = newbody;
        }
    }
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

