#include "Hospital.h"
#include <iostream>
#include <algorithm>
using namespace std;

// Destructor to free all dynamically allocated Patient objects
Hospital::~Hospital() {
    for (Patient* p : activePatients) {
        delete p;
    }
    for (Patient* p : dischargedPatients) {
        delete p;
    }
}

// Add a doctor to the hospital staff
void Hospital::addDoctor(string name, string spec) {
    doctors.push_back({nextDoctorID++, name, spec, true});
}

// Add a nurse to the hospital staff
void Hospital::addNurse(string name) {
    nurses.push_back({nextNurseID++, name, true});
}

// Admit a new patient and add them to the system
Patient* Hospital::admitPatient(string name, int age, string gender, bool emergency) {
    Patient* p = new Patient();
    p->id = nextPatientID++;
    p->name = name;
    p->age = age;
    p->gender = gender;
    p->emergency = emergency;
    p->status = "Admitted";

    activePatients.push_back(p);
    if (emergency) {
        emergencyQueue.push(p);
    }
    cout << "\n✅ Patient " << p->name << " admitted successfully.\n";
    return p;
}

// Find a patient by their unique ID
Patient* Hospital::findPatientByID(int id) {
    for (auto* p : activePatients) {
        if (p->id == id) {
            return p;
        }
    }
    return nullptr;
}

// Diagnose a patient and assign staff
void Hospital::diagnosePatient(Patient* p, string disease) {
    p->disease = disease;
    p->status = "Diagnosed";
    assignStaff(p);
    cout << "\n🩺 " << p->name << " diagnosed with " << disease << ".\n";
}

// Assign available staff (1 doctor, 2 nurses) to a patient
void Hospital::assignStaff(Patient* p) {
    // Assign 1 doctor
    for (auto &doc : doctors) {
        if (doc.isAvailable) {
            p->doctorAssigned = doc.id;
            doc.isAvailable = false;
            break;
        }
    }
    // Assign 2 nurses
    int assigned = 0;
    for (auto &n : nurses) {
        if (n.isAvailable && assigned < 2) {
            p->nursesAssigned.push_back(n.id);
            n.isAvailable = false;
            assigned++;
        }
    }
    cout << "👨‍⚕️ A doctor and 👩‍⚕️ 2 nurses have been assigned to " << p->name << ".\n";
}

// Prescribe medication or schedule surgery based on patient's condition
void Hospital::treatPatient(Patient* p, bool cured) {
    if (cured) {
        p->status = "Cured";
        prescription(p);
    } else {
        cout << "\nPatient's condition is serious. Scheduling surgery...\n";
        scheduleSurgery(p);
    }
}

// Give a prescription and prepare for discharge
void Hospital::prescription(Patient* p) {
    cout << "\n💊 Prescription given to " << p->name << ". Ready for discharge.\n";
}

// Schedule surgery and assign more nurses
void Hospital::scheduleSurgery(Patient* p) {
    p->status = "Surgery Scheduled";
    int assigned = 0;
    for (auto &n : nurses) {
        if (n.isAvailable && assigned < 2) {
            p->nursesAssigned.push_back(n.id);
            n.isAvailable = false;
            assigned++;
        }
    }
    cout << "🩹 Surgery scheduled for " << p->name << " with 2 extra nurses.\n";
    // The patient is shifted to ICU after surgery for observation
    p->status = "ICU";
    cout << "🏥 " << p->name << " shifted to ICU for observation.\n";
}

// Discharge a patient from the hospital
void Hospital::dischargePatient(Patient* p) {
    p->status = "Discharged";
    releasedStaff(p);
    dischargedPatients.push_back(p);

    // Remove patient from active list
    auto it = find(activePatients.begin(), activePatients.end(), p);
    if (it != activePatients.end()) {
        activePatients.erase(it);
    }

    cout << "\n✅ " << p->name << " discharged successfully.\n";
}

// Release staff back to the available pool
void Hospital::releasedStaff(Patient* p) {
    // Free doctor
    for (auto &doc : doctors) {
        if (doc.id == p->doctorAssigned) {
            doc.isAvailable = true;
        }
    }
    // Free nurses
    for (int nurseId : p->nursesAssigned) {
        for (auto &n : nurses) {
            if (n.id == nurseId) {
                n.isAvailable = true;
                break;
            }
        }
    }
}

// Show all currently active patients
void Hospital::showActivePatients() {
    cout << "\n--- Active Patients ---\n";
    if (activePatients.empty()) {
        cout << "No active patients.\n";
    }
    for (auto *p : activePatients) {
        cout << p->id << ". " << p->name << " ("
             << (p->emergency ? "🚨 Emergency" : "Normal")
             << ") - " << p->status << "\n";
    }
}

// Show all discharged patients
void Hospital::showDischargedPatients() {
    cout << "\n--- Discharged Patients ---\n";
    if (dischargedPatients.empty()) {
        cout << "No discharged patients.\n";
    }
    for (auto *p : dischargedPatients) {
        cout << p->id << ". " << p->name << " - " << p->disease << " (Discharged)\n";
    }
}

// Handle the highest priority emergency patient
void Hospital::handleEmergency() {
    if (!emergencyQueue.empty()) {
        Patient* p = emergencyQueue.top();
        emergencyQueue.pop();
        cout << "\n🚨 Handling emergency patient: " << p->name << endl;
        diagnosePatient(p, "Critical Condition");
        scheduleSurgery(p);
    } else {
        cout << "\nNo emergency patients waiting.\n";
    }
}
