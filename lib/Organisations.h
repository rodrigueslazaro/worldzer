#pragma once
#include "Character.h"

typedef enum {
    house,
    club,
    society,
    school,
    university,
    library
} type;

class Organisation {
public:
    Organisation Organisation(){};
private:
    type type;
    Character head;
    string goal;
    int num_members;
    vector<Character> members;
};