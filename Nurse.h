#ifndef NURSE_H
#define NURSE_H

#include <string>
using namespace std;

struct Nurse {
    int id;
    string name;
    bool isAvailable = true;
};

#endif
