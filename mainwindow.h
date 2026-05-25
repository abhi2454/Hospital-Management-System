#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include "Hospital.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAdmitPatientClicked();
    void onDiagnosePatientClicked();
    void onTreatPatientClicked();
    void onDischargePatientClicked();
    void onHandleEmergencyClicked();
    void onShowActivePatientsClicked();
    void onShowDischargedPatientsClicked();

private:
    Hospital hospital;

    // UI elements for Patient Admission
    QLineEdit *patientNameLineEdit;
    QLineEdit *patientAgeLineEdit;
    QLineEdit *patientGenderLineEdit;
    QRadioButton *emergencyRadioButton;
    QPushButton *admitPatientButton;

    // UI elements for Patient Management
    QLineEdit *patientIdLineEdit;
    QLineEdit *patientDiseaseLineEdit;
    QRadioButton *curedRadioButton;
    QPushButton *diagnosePatientButton;
    QPushButton *treatPatientButton;
    QPushButton *dischargePatientButton;

    // UI elements for Emergency and Reports
    QPushButton *handleEmergencyButton;
    QPushButton *showActivePatientsButton;
    QPushButton *showDischargedPatientsButton;

    // Display area
    QTextEdit *outputDisplay;

    // Helper function to update the display
    void updateOutput(const QString &text);

    // Helper function to find a patient by ID (needed for GUI logic)
    Patient* findPatientByID(int id);
};

#endif
