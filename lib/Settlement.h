#pragma once

typedef enum {
    community,
    village,
    town,
    city,
    metropole
} type;

typedef struct {
    bool capital;
    int walls;
    int ports;
    vector<Castle> buildings;
    int markets;
    int favelas;
} features;

class Settlement {
public:
    Settlement Settlement(){};
private:
    type type;
    Culture culture;
    features features;

}