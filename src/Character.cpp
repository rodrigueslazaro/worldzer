#include "Character.h"
#include "constants.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <random>
using namespace std;

Character::Character(string spc, string eth, string cul, string sub, int alive, int age) {
    getDBs();
    (spc != "") ? setSpecies(spc) : setRandSpecies();
    setAge(alive, age);
    (eth != "") ? setEthnicity(eth) : setRandEthnicity();
    setBody();
    (cul != "") ? setCulture(cul) : setRandCulture();
    setMindAndSkills();
}

void Character::printCharacter() {
    bool hashet = 0;
    string sexes[2] = {"male", "female"};
    string sexuality[3] = {"straight", "bisexual", "homosexual"};
    cout << "<---<💪🏻>---=== BODY ===---<🦵🏻>--->" << endl
         << "Species: " << species << endl
         << "Sex: " << sexes[body.sex] << endl
         << "Ethnicity: " << ethnicity << endl
         << "Height: " << body.height << endl
         << "Build: " << body.structure.build << endl
         << "Skin color: " << body.skin.color << endl
         << "Hair texutre: " << body.hair.texture << endl
         << "Hair color: " << body.hair.color << endl
         << "Body hair volume: " << body.hair.fur << endl;
    if (body.structure.disability.size() > 0) {
        cout << "Disabilities: ";
        for (auto d : body.structure.disability)
            cout << d << ", ";
        cout << endl;
    }
    cout << "<---<👩🏻‍🦳>---=== FACE ===---<🧑🏻‍🦰>--->" << endl
         << "Width: " << face.width << endl
         << "Height: " << face.height << endl
         << "Jaw width: " << face.jaw.width << endl
         << "Jaw definition: " << face.jaw.definition << endl
         << "Chin width: " << face.chin.width << endl
         << "Chin forward: " << face.chin.forward << endl
         << "Nose width: " << face.nose.width << endl
         << "Nose length: " << face.nose.length << endl
         << "Nose bridge: " << face.nose.bridge << endl
         << "Lips thickness: " << face.lips << endl
         << "Cheeckbones height: " << face.cheeckbone_height << endl
         << "Brow forward: " << face.brow_forward << endl
         << "Eyes size: " << face.eyes.size << endl
         << "Eyes monolid: " << face.eyes.monolid << endl;
        for (auto d : body.structure.disability) {
            if (d == "heterochromia") {
                hashet = true;
                cout << "Left eye color: " << face.eyes.left << endl;
                cout << "Right eye color: " << face.eyes.right << endl;
            }
        }
        if (not hashet)
            cout << "Eyes color: " << face.eyes.left << endl;

    cout << "<---<❤️>---=== HISTORY ===---<💀>--->" << endl
         << "Age in " << CURRENT_YEAR << ": " << age.num << endl
         << "Culture: " << culture << endl
         << "Birth: " << age.birth.year << "-" << age.birth.month << "-" << age.birth.day << endl
         << "Death: " << age.death.year << "-" << age.death.month << "-" << age.death.day << endl
         << "Death age: " << age.death.year - age.birth.year << endl;

    cout << "<---<🧠>---=== BRAIN ===---<🧟>--->" << endl
         << "Resilience: " << brain.resilience << endl
         << "Flexibility: " << brain.flexibility << endl
         << "Intelligence: " << brain.intelligence << endl
         << "Sexuality: " << sexuality[brain.sexuality] << endl;

    cout << "<---<💃🏻>---=== PERSONALITY ===---<🎵>--->" << endl
         << "Extroversion: " << mind.extroversion << endl
         << "Creativity: " << mind.creativity << endl
         << "Rationality: " << mind.rationality << endl
         << "Organisation: " << mind.organization << endl
         << "Assertiveness: " << mind.assertiveness << endl;

     cout << "<---<🍆>---=== VIEWS ===---<👑>--->" << endl
         << "Authorities: " << views.authorities << endl
         << "Individualism: " << views.individualism << endl
         << "Tradition: " << views.tradition << endl
         << "Hedonism: " << views.hedonism << endl
         << "Religion: " << views.religion << endl;
}

void Character::setMindAndSkills() {
    random_device rd;
    mt19937 gen(rd());
    struct brain newbrain;
    struct mind newmind;
    struct views newviews;
    
    /* set brain */
    uniform_int_distribution<> randbrain(0, 9);
    newbrain.resilience = randbrain(gen);
    newbrain.flexibility = randbrain(gen);
    newbrain.intelligence = randbrain(gen);
    uniform_int_distribution<> sexuality(0, 99);
    int sexdist = sexuality(gen);
    if (sexdist < 90)
        newbrain.sexuality = straight;
    else if (sexdist < 95)
        newbrain.sexuality = bisexual;
    else
        newbrain.sexuality = homosexual;
    brain = newbrain;

    /* set mind (personality) */
    uniform_int_distribution<> randmind(0, 20);
    newmind.assertiveness = randmind(gen);
    newmind.creativity = randmind(gen);
    newmind.extroversion = randmind(gen);
    newmind.organization = randmind(gen);
    newmind.rationality = randmind(gen);
    mind = newmind;

    /* set views (based on culture, and personality) */
    for (rapidjson::SizeType i=0; i<culturesdb.Size(); i++) {
        if (culturesdb[i]["name"].GetString() == culture) {
            newviews.authorities = static_cast<int>(culturesdb[i]["protocols"].GetFloat())
                                  +static_cast<int>(culturesdb[i]["centralization"].GetFloat())
                                  +static_cast<int>(culturesdb[i]["flexibility"].GetFloat())
                                  +static_cast<int>(culturesdb[i]["religion"].GetFloat())
                                  +mind.organization/2;
            newviews.individualism = static_cast<int>(culturesdb[i]["individualism"].GetFloat())
                                    +static_cast<int>(culturesdb[i]["masculinity"].GetFloat())
                                    +static_cast<int>(culturesdb[i]["isolation"].GetFloat())
                                    +mind.rationality/2;
            newviews.tradition = static_cast<int>(culturesdb[i]["individualism"].GetFloat())
                                +static_cast<int>(culturesdb[i]["protocols"].GetFloat())
                                +static_cast<int>(culturesdb[i]["centralization"].GetFloat())
                                +static_cast<int>(culturesdb[i]["flexibility"].GetFloat())
                                +static_cast<int>(culturesdb[i]["isolation"].GetFloat())
                                +static_cast<int>(culturesdb[i]["religion"].GetFloat())
                                +mind.organization/2;
            newviews.hedonism = static_cast<int>(culturesdb[i]["hedonism"].GetFloat())
                               +static_cast<int>(culturesdb[i]["masculinity"].GetFloat())
                               +mind.extroversion/2;
            newviews.religion = static_cast<int>(culturesdb[i]["religion"].GetFloat())
                               +static_cast<int>(culturesdb[i]["centralization"].GetFloat())
                               +mind.rationality/2;
        }
    }
    views = newviews;
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
    bool hasdis = 0;
    random_device rd;
    mt19937 gen(rd());
    struct body newbody;
    struct face newface;
    /* get ethnicity */
    for (rapidjson::SizeType i=0; i<ethnicitiesdb.Size(); i++) {
        if (ethnicitiesdb[i]["name"].GetString() == ethnicity) {
            /* set sex */
            uniform_int_distribution<> randsex(0,1);
            newbody.sex = static_cast<enum sex>(randsex(gen));

            /* set height */
            uniform_int_distribution<> randheight(static_cast<int>(ethnicitiesdb[i]["min-height"].GetFloat()),static_cast<int>(ethnicitiesdb[i]["max-height"].GetFloat()));
            newbody.height = randheight(gen);

            hasdis = false;
            for (auto d : body.structure.disability) {
                if (d == "nanism") {
                    hasdis = true;
                    uniform_int_distribution<> randnansim(static_cast<int>(ethnicitiesdb[i]["min-height"].GetFloat()/2),static_cast<int>(ethnicitiesdb[i]["min-height"].GetFloat()));
                    newbody.height = randnansim(gen);
                }
            }

            /* set disabilities */
            uniform_int_distribution<> randgenetics(0,5000);
            if (not randgenetics(gen)) {
                vector<string> disabilities = {
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
                    "alopecia",
                    "vitiligo",
                    "heterochromia",
                    "nanism",
                };
                uniform_int_distribution<> randdis(0,19);
                newbody.structure.disability.push_back(disabilities[randdis(gen)]);
                uniform_int_distribution<> randgenetics2(0,15000);
                if (not randgenetics2(gen) and newbody.structure.disability.size() == 1) {
                    newbody.structure.disability.push_back(newbody.structure.disability[0]);
                    while (newbody.structure.disability[0] == newbody.structure.disability[1])
                        newbody.structure.disability[1] = disabilities[randdis(gen)];
                }
                uniform_int_distribution<> randgenetics3(0,50000);
                if (not randgenetics2(gen) and newbody.structure.disability.size() == 2) {
                    newbody.structure.disability.push_back(newbody.structure.disability[0]);
                    while (newbody.structure.disability[0] == newbody.structure.disability[1]
                           or newbody.structure.disability[1] == newbody.structure.disability[2])
                        newbody.structure.disability[2] = disabilities[randdis(gen)];
                }
            }

            /* set body hair */
            uniform_int_distribution<> pm2(-2,2);
            uniform_int_distribution<> pm1(-1,1);
            newbody.hair.fur = static_cast<int>(ethnicitiesdb[i]["body-hair"].GetFloat()) + pm2(gen);
            if (newbody.sex == female)
                newface.jaw.width -= 1;
            (newbody.hair.fur > 9) ? newbody.hair.fur = 9:0;
            (newbody.hair.fur < 0) ? newbody.hair.fur = 0:0;

            /* set body build */
            newbody.structure.build = static_cast<int>(ethnicitiesdb[i]["bone-structure"].GetFloat()) + pm2(gen);
            if (newbody.sex == female)
                newface.jaw.width -= 1;
            (newbody.structure.build > 9) ? newbody.structure.build = 9:0;
            (newbody.structure.build < 0) ? newbody.structure.build = 0:0;

            /* set face jaw-width */
            newface.jaw.width = static_cast<int>(ethnicitiesdb[i]["jaw-width"].GetFloat()) + pm2(gen);
            if (newbody.sex == female)
                newface.jaw.width -= 1;
            (newface.jaw.width > 9) ? newface.jaw.width = 9:0;
            (newface.jaw.width < 0) ? newface.jaw.width = 0:0;

            /* set face jaw-definition */
            newface.jaw.definition = static_cast<int>(ethnicitiesdb[i]["jaw-width"].GetFloat()) + pm2(gen);
            if (newbody.sex == female)
                newface.jaw.definition -= 2;
            (newface.jaw.definition > 9) ? newface.jaw.definition = 9:0;
            (newface.jaw.definition < 0) ? newface.jaw.definition = 0:0;

            /* set face chin-width */
            newface.chin.width = static_cast<int>(ethnicitiesdb[i]["chin-width"].GetFloat()) + pm2(gen);
            if (newbody.sex == female)
                newface.chin.width -= 1;
            (newface.chin.width > 9) ? newface.chin.width = 9:0;
            (newface.chin.width < 0) ? newface.chin.width = 0:0;

            /* set face chin-width */
            newface.chin.forward = static_cast<int>(ethnicitiesdb[i]["chin-forward"].GetFloat()) + pm2(gen);
            if (newbody.sex == female)
                newface.chin.forward -= 1;
            (newface.chin.forward > 9) ? newface.chin.forward = 9:0;
            (newface.chin.forward < 0) ? newface.chin.forward = 0:0;

            /* set cheeckbone height */
            newface.cheeckbone_height = static_cast<int>(ethnicitiesdb[i]["cheeck-height"].GetFloat()) + pm2(gen);
            if (newbody.sex == female)
                newface.cheeckbone_height += 1;
            (newface.cheeckbone_height > 9) ? newface.cheeckbone_height = 9:0;
            (newface.cheeckbone_height < 0) ? newface.cheeckbone_height = 0:0;

            /* set face width */
            newface.width = static_cast<int>(ethnicitiesdb[i]["face-width"].GetFloat()) + pm1(gen);
            (newface.width > 9) ? newface.width = 9:0;
            (newface.width < 0) ? newface.width = 0:0;

            /* set face height */
            newface.height = static_cast<int>(ethnicitiesdb[i]["face-height"].GetFloat()) + pm1(gen);
            (newface.height > 9) ? newface.height = 9:0;
            (newface.height < 0) ? newface.height = 0:0;

            /* set eyes size */
            newface.eyes.size = static_cast<int>(ethnicitiesdb[i]["eye-size"].GetFloat()) + pm2(gen);
            if (newbody.sex == female)
                newface.eyes.size -= 1;
            (newface.eyes.size > 9) ? newface.eyes.size = 9:0;
            (newface.eyes.size < 0) ? newface.eyes.size = 0:0;

            /* set eyes monolid */
            newface.eyes.monolid = static_cast<int>(ethnicitiesdb[i]["monolid"].GetFloat());

            /* set lips size */
            newface.lips = static_cast<int>(ethnicitiesdb[i]["lips"].GetFloat()) + pm2(gen);
            if (newbody.sex == female)
                newface.lips += 1;
            (newface.lips > 9) ? newface.lips = 9:0;
            (newface.lips < 0) ? newface.lips = 0:0;

            /* set brow forward */
            newface.brow_forward = static_cast<int>(ethnicitiesdb[i]["brow-forward"].GetFloat()) + pm2(gen);
            if (newbody.sex == female)
                newface.brow_forward -= 1;
            (newface.brow_forward > 9) ? newface.brow_forward = 9:0;
            (newface.brow_forward < 0) ? newface.brow_forward = 0:0;

            /* set nose width */
            newface.nose.width = static_cast<int>(ethnicitiesdb[i]["nose-width"].GetFloat()) + pm2(gen);
            (newface.nose.width > 9) ? newface.nose.width = 9:0;
            (newface.nose.width < 0) ? newface.nose.width = 0:0;

            /* set nose length */
            newface.nose.length = static_cast<int>(ethnicitiesdb[i]["nose-length"].GetFloat()) + pm2(gen);
            (newface.nose.length > 9) ? newface.nose.length = 9:0;
            (newface.nose.length < 0) ? newface.nose.length = 0:0;

            /* set nose bridge */
            newface.nose.bridge = static_cast<int>(ethnicitiesdb[i]["nose-bridge"].GetFloat()) + pm2(gen);
            (newface.nose.bridge > 9) ? newface.nose.bridge = 9:0;
            (newface.nose.bridge < 0) ? newface.nose.bridge = 0:0;

            /* set hair texture */
            rapidjson::Value::Array textures = ethnicitiesdb[i]["hair-textures"].GetArray();
            uniform_int_distribution<> randtexture(0,textures.Size()-1);
            newbody.hair.texture = textures[randtexture(gen)].GetString();

            /* set hair color */
            rapidjson::Value::Array colors = ethnicitiesdb[i]["hair-colors"].GetArray();
            uniform_int_distribution<> randcolor(0,colors.Size()-1);
            newbody.hair.color = colors[randcolor(gen)].GetString();

            /* set eyes color */
            rapidjson::Value::Array eyecolors = ethnicitiesdb[i]["eyes-color"].GetArray();
            uniform_int_distribution<> randeyecolor(0,eyecolors.Size()-1);

            hasdis = false;
            for (auto d : body.structure.disability) {
                if (d == "heterochromia") {
                    hasdis = true;
                    newface.eyes.right = eyecolors[randeyecolor(gen)].GetString();
                    newface.eyes.left = newface.eyes.right;
                    while (newface.eyes.right == newface.eyes.left)
                        newface.eyes.left = eyecolors[randeyecolor(gen)].GetString();
                }
            }
            if (not hasdis) {
                newface.eyes.right = eyecolors[randeyecolor(gen)].GetString();
                newface.eyes.left = newface.eyes.right;
            }

            /* set skin color */
            rapidjson::Value::Array skin = ethnicitiesdb[i]["skin-color"].GetArray();
            uniform_int_distribution<> randskin(0,skin.Size()-1);
            uniform_int_distribution<> randtone(1,5);
            newbody.skin.color = skin[randskin(gen)].GetString();
            newbody.skin.color += "-" + to_string(randtone(gen));

            body = newbody;
            face = newface;
        }
    }
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

