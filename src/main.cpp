#include "Character.h"
#include <iostream>
using namespace std;

int main() {
    Character char1;
    cout << "Species: " << char1.getSpecies() << endl;
    cout << "Ethnicity: " << char1.getEthnicity() << endl;
    return 0;
}