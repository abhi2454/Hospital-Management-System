#include "Hospital.h"
#include <iostream>
#include <limits>
#include <mainwindow.h>
#include <QApplication>
using namespace std;

// Function to pause console output
void pauseConsole() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main(int argc, char *argv[]) {

    // The QApplication object manages the application's control flow and main settings.
    QApplication a(argc, argv);

    // Create an instance of your main window (the GUI)
    MainWindow w;

    // Show the main window
    w.show();

    // Enter the application's main event loop and wait for the user to exit
    return a.exec();
    Hospital h;

    // --- Setup Staff ---
    h.addDoctor("Dr. Smith", "General");
    h.addDoctor("Dr. Adams", "Cardiology");
    h.addDoctor("Dr. Brown", "Neurology");
    h.addDoctor("Dr. Davis", "Pediatrics");
    h.addNurse("Alice");
    h.addNurse("Emma");
    h.addNurse("Sophia");
    h.addNurse("Lily");
    h.addNurse("James");
    h.addNurse("Maria");
    h.addNurse("Olivia");
    h.addNurse("David");

    int choice;
    while (true) {
        cout << "\n===== Hospital Management System =====\n";
        cout << "1. Admit Patient\n";
        cout << "2. Diagnose Patient\n";
        cout << "3. Treat Patient (Prescription/Surgery)\n";
        cout << "4. Discharge a Cured Patient\n";
        cout << "5. Handle Emergency\n";
        cout << "6. Show Active Patients\n";
        cout << "7. Show Discharged Patients\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n❌ Invalid input! Please enter a number.\n";
            continue;
        }

        if (choice == 1) {
            string name, gender;
            int age;
            char isEmergency;

            // Form for patient details
            cout << "\n===== Patient Admission Form =====\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter Patient Name: ";
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Gender: ";
            cin >> gender;
            cout << "Is this an emergency? (y/n): ";
            cin >> isEmergency;

            bool emergency = (isEmergency == 'y' || isEmergency == 'Y');
            h.admitPatient(name, age, gender, emergency);
            pauseConsole();

        } else if (choice == 2) {
            int id;
            string disease;
            cout << "\n===== Diagnose Patient =====\n";
            cout << "Enter Patient ID to Diagnose: ";
            cin >> id;
            cout << "Enter Disease: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, disease);

            Patient* target = h.findPatientByID(id);
            if (target) {
                h.diagnosePatient(target, disease);
            } else {
                cout << "\n❌ Patient with ID " << id << " not found.\n";
            }
            pauseConsole();

        } else if (choice == 3) {
            int id;
            char curedFlag;
            cout << "\n===== Treat Patient =====\n";
            cout << "Enter Patient ID to Treat: ";
            cin >> id;
            cout << "Is the patient cured? (y/n): ";
            cin >> curedFlag;

            bool cured = (curedFlag == 'y' || curedFlag == 'Y');
            Patient* target = h.findPatientByID(id);
            if (target) {
                h.treatPatient(target, cured);
            } else {
                cout << "\n❌ Patient with ID " << id << " not found.\n";
            }
            pauseConsole();

        } else if (choice == 4) {
            int id;
            cout << "\n===== Discharge Patient =====\n";
            cout << "Enter Patient ID to Discharge: ";
            cin >> id;

            Patient* target = h.findPatientByID(id);
            if (target) {
                h.dischargePatient(target);
            } else {
                cout << "\n❌ Patient with ID " << id << " not found.\n";
            }
            pauseConsole();

        } else if (choice == 5) {
            cout << "\n===== Emergency =====\n";
            h.handleEmergency();
            pauseConsole();

        } else if (choice == 6) {
            h.showActivePatients();
            pauseConsole();

        } else if (choice == 7) {
            h.showDischargedPatients();
            pauseConsole();

        } else if (choice == 8) {
            cout << "\nExiting the system...\n";
            break;
        } else {
            cout << "\n❌ Invalid choice. Please try again.\n";
            pauseConsole();
        }
    }

    return 0;
}
