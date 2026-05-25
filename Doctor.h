#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
using namespace std;

struct Doctor {
    int id;
    string name;
    string specialization;
    bool isAvailable = true;
};

#endif
