#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "Patient.h"
#include "Doctor.h"
#include "Nurse.h"
#include <vector>
#include <queue>
#include <string>

// A custom comparator for the priority queue, ensuring emergency patients are handled first.
struct ComparePatients {
    bool operator()(Patient* p1, Patient* p2) {
        return p1->emergency < p2->emergency;
    }
};

class Hospital {
private:
    int nextPatientID = 1;
    int nextDoctorID = 1;
    int nextNurseID = 1;

    vector<Patient*> activePatients;
    vector<Patient*> dischargedPatients;
    vector<Doctor> doctors;
    vector<Nurse> nurses;
    priority_queue<Patient*, vector<Patient*>, ComparePatients> emergencyQueue;

public:
    // Destructor to clean up dynamically allocated memory
    ~Hospital();

    // Staff Management
    void addDoctor(string name, string spec);
    void addNurse(string name);

    // Patient Workflow
    Patient* admitPatient(string name, int age, string gender, bool emergency);
    void diagnosePatient(Patient* p, string disease);
    void treatPatient(Patient* p, bool cured);
    void handleEmergency();
    void dischargePatient(Patient* p);

    // Helper Functions
    void assignStaff(Patient* p);
    void releasedStaff(Patient* p);
    void scheduleSurgery(Patient* p);
    void prescription(Patient* p);
    Patient* findPatientByID(int id);

    // Reporting
    void showActivePatients();
    void showDischargedPatients();

    // Accessors
    vector<Patient*>& getActivePatients() { return activePatients; }
    vector<Patient*>& getDischargedPatients() { return dischargedPatients; }
};

#endif
