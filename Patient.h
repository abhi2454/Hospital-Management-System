#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <vector>
using namespace std;

struct Patient {
    int id;
    string name;
    int age;
    string gender;
    string disease;
    bool emergency;
    string status; // Admitted, Diagnosed, Surgery, ICU, Discharged
    int doctorAssigned = -1;
    vector<int> nursesAssigned;
};

#endif
