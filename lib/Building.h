#pragma once

typedef enum {
    shack,
    house,
    mansion,
    castle,
    temple
} type;

typedef enum {
    greek,
    roman,
    gothic,
    asian,
    islamic,
    byzantine,
    medieval,
    baroque,
} architectures;

class Building {
public:
    Castle Castle(){};
private:
    Organisation owner;
    architectures style;
}