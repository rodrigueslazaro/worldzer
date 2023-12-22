#include "Character.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <map>
#include <vector>
using namespace std;

int main() {
    ifstream file("data/ehtinicities.csv");
    string line, header;
    map<string, vector<string>> data;

    // Read the header
    if (getline(file, header)) {
        istringstream headerStream(header);
        string columnName;
        while (getline(headerStream, columnName, '\t')) {
            data[columnName] = vector<string>(); // Initialize columns
        }
    }

    // Read and parse data rows
    while (getline(file, line)) {
        istringstream lineStream(line);
        string value;
        int index = 0;
        while (getline(lineStream, value, '\t')) {
            data[header[index]].push_back(value); // Populate data
            index++;
        }
    }

    // Accessing data using column headers
    // Example: Access height of malkani
    vector<string> malkaniHeight = data["height"];
    cout << "Malkani's height: " << malkaniHeight[0] << endl;

    // Example: Access hair-textures of almani
    vector<string> almaniHairTextures = data["hair-textures"];
    cout << "Almani's hair textures: " << almaniHairTextures[2] << endl;

    // Further processing or usage of the data...

    return 0;
}
