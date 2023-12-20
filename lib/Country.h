#pragma once
#include "Governments.h"

typedef enum {
    frozen,
    cold,
    temperate,
    warm,
    hot 
} climates;

typedef enum {
    arid,
    dry,
    moderate,
    humid,
    wet
} humidities;

typedef enum {
    flat,
    lhills, /* low rolling hills */
    mhills, /* medium rolling hills */
    hhills, /* high rolling hills */
    mountains,
    hmountains, /* high mountains */
} terrains;

typedef struct {
    int coverage;
    terrains terrain;
} terrain_coverage;

typedef struct {
    int coverage;
    humidities humidity;
} humidity_coverage;

typedef struct {
    int coverage;
    climates climate;
} climate_coverage;

typedef struct {
    vector<terrain_coverage> terrain;
    vector<climate_coverage> climate;
    vector<humidity_coverage> humidity;
} nat; /* natural characteristics */

typedef struct {
    int area;
    Character leader;
    governments government;
    Settlement capital;
} geo; /* geography and politics */

class Country {
public:
    Country Country(){};
    void ~Country(){};
private:
    
}