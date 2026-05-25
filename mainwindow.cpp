#include "mainwindow.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QScrollArea>

// Helper function to create line edits
QLineEdit* createLineEdit(const QString& placeholder) {
    QLineEdit* lineEdit = new QLineEdit();
    lineEdit->setPlaceholderText(placeholder);
    return lineEdit;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Hospital Management System");
    setMinimumSize(800, 600);

    // Main layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Main menu layout (buttons on the left)
    QGroupBox *menuGroupBox = new QGroupBox("Menu");
    QVBoxLayout *menuLayout = new QVBoxLayout(menuGroupBox);

    admitPatientButton = new QPushButton("1. Admit Patient");
    diagnosePatientButton = new QPushButton("2. Diagnose Patient");
    treatPatientButton = new QPushButton("3. Treat Patient");
    dischargePatientButton = new QPushButton("4. Discharge Patient");
    handleEmergencyButton = new QPushButton("5. Handle Emergency");
    showActivePatientsButton = new QPushButton("6. Show Active Patients");
    showDischargedPatientsButton = new QPushButton("7. Show Discharged Patients");

    menuLayout->addWidget(admitPatientButton);
    menuLayout->addWidget(diagnosePatientButton);
    menuLayout->addWidget(treatPatientButton);
    menuLayout->addWidget(dischargePatientButton);
    menuLayout->addWidget(handleEmergencyButton);
    menuLayout->addWidget(showActivePatientsButton);
    menuLayout->addWidget(showDischargedPatientsButton);
    menuLayout->addStretch();

    // Form layout (forms on the right)
    QGroupBox *formGroupBox = new QGroupBox("Patient Forms");
    QVBoxLayout *formLayout = new QVBoxLayout(formGroupBox);

    // Admit Patient Form
    QGroupBox *admitPatientForm = new QGroupBox("Admit Patient");
    QFormLayout *admitFormLayout = new QFormLayout(admitPatientForm);
    patientNameLineEdit = createLineEdit("Patient Name");
    patientAgeLineEdit = createLineEdit("Age");
    patientGenderLineEdit = createLineEdit("Gender");
    emergencyRadioButton = new QRadioButton("Is Emergency?");
    admitFormLayout->addRow("Name:", patientNameLineEdit);
    admitFormLayout->addRow("Age:", patientAgeLineEdit);
    admitFormLayout->addRow("Gender:", patientGenderLineEdit);
    admitFormLayout->addRow("", emergencyRadioButton);
    formLayout->addWidget(admitPatientForm);

    // Diagnose and Treat Forms
    QGroupBox *managePatientForm = new QGroupBox("Manage Patient");
    QFormLayout *manageFormLayout = new QFormLayout(managePatientForm);
    patientIdLineEdit = createLineEdit("Patient ID");
    patientDiseaseLineEdit = createLineEdit("Disease");
    curedRadioButton = new QRadioButton("Is Cured?");
    manageFormLayout->addRow("Patient ID:", patientIdLineEdit);
    manageFormLayout->addRow("Disease:", patientDiseaseLineEdit);
    manageFormLayout->addRow("Cured:", curedRadioButton);
    formLayout->addWidget(managePatientForm);

    // Output Display
    QGroupBox *outputGroupBox = new QGroupBox("Output");
    QVBoxLayout *outputLayout = new QVBoxLayout(outputGroupBox);
    outputDisplay = new QTextEdit();
    outputDisplay->setReadOnly(true);
    outputLayout->addWidget(outputDisplay);

    // Split layout for menu and forms
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(menuGroupBox);
    topLayout->addWidget(formGroupBox);
    topLayout->addWidget(outputGroupBox);
    topLayout->setStretchFactor(outputGroupBox, 1);
    mainLayout->addLayout(topLayout);

    // Connect signals and slots
    connect(admitPatientButton, &QPushButton::clicked, this, &MainWindow::onAdmitPatientClicked);
    connect(diagnosePatientButton, &QPushButton::clicked, this, &MainWindow::onDiagnosePatientClicked);
    connect(treatPatientButton, &QPushButton::clicked, this, &MainWindow::onTreatPatientClicked);
    connect(dischargePatientButton, &QPushButton::clicked, this, &MainWindow::onDischargePatientClicked);
    connect(handleEmergencyButton, &QPushButton::clicked, this, &MainWindow::onHandleEmergencyClicked);
    connect(showActivePatientsButton, &QPushButton::clicked, this, &MainWindow::onShowActivePatientsClicked);
    connect(showDischargedPatientsButton, &QPushButton::clicked, this, &MainWindow::onShowDischargedPatientsClicked);

    // Initial hospital setup
    hospital.addDoctor("Dr. Smith", "General");
    hospital.addDoctor("Dr. Adams", "Cardiology");
    hospital.addDoctor("Dr. Brown", "Neurology");
    hospital.addDoctor("Dr. Davis", "Pediatrics");
    hospital.addNurse("Alice");
    hospital.addNurse("Emma");
    hospital.addNurse("Sophia");
    hospital.addNurse("Lily");
    hospital.addNurse("James");
    hospital.addNurse("Maria");
    hospital.addNurse("Olivia");
    hospital.addNurse("David");
}

MainWindow::~MainWindow()
{
    // Destructor (Qt handles child widgets automatically)
}

void MainWindow::updateOutput(const QString &text) {
    outputDisplay->append(text);
}

Patient* MainWindow::findPatientByID(int id) {
    return hospital.findPatientByID(id);
}

void MainWindow::onAdmitPatientClicked() {
    QString name = patientNameLineEdit->text();
    int age = patientAgeLineEdit->text().toInt();
    QString gender = patientGenderLineEdit->text();
    bool isEmergency = emergencyRadioButton->isChecked();

    if (name.isEmpty() || age == 0 || gender.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all patient details.");
        return;
    }

    hospital.admitPatient(name.toStdString(), age, gender.toStdString(), isEmergency);
    updateOutput(QString("✅ Patient %1 admitted successfully.").arg(name));

    // Clear form fields
    patientNameLineEdit->clear();
    patientAgeLineEdit->clear();
    patientGenderLineEdit->clear();
    emergencyRadioButton->setChecked(false);
}

void MainWindow::onDiagnosePatientClicked() {
    int id = patientIdLineEdit->text().toInt();
    QString disease = patientDiseaseLineEdit->text();

    if (id == 0 || disease.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid Patient ID and Disease.");
        return;
    }

    Patient* target = findPatientByID(id);
    if (target) {
        hospital.diagnosePatient(target, disease.toStdString());
        updateOutput(QString("🩺 Patient %1 diagnosed with %2.").arg(target->name.c_str()).arg(disease));
    } else {
        updateOutput(QString("❌ Patient with ID %1 not found.").arg(id));
    }
}

void MainWindow::onTreatPatientClicked() {
    int id = patientIdLineEdit->text().toInt();
    bool isCured = curedRadioButton->isChecked();

    if (id == 0) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid Patient ID.");
        return;
    }

    Patient* target = findPatientByID(id);
    if (target) {
        hospital.treatPatient(target, isCured);
        updateOutput(QString("Patient %1 is being treated.").arg(target->name.c_str()));
    } else {
        updateOutput(QString("❌ Patient with ID %1 not found.").arg(id));
    }
}

void MainWindow::onDischargePatientClicked() {
    int id = patientIdLineEdit->text().toInt();

    if (id == 0) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid Patient ID.");
        return;
    }

    Patient* target = findPatientByID(id);
    if (target) {
        hospital.dischargePatient(target);
        updateOutput(QString("✅ Patient %1 discharged successfully.").arg(target->name.c_str()));
    } else {
        updateOutput(QString("❌ Patient with ID %1 not found.").arg(id));
    }
}

void MainWindow::onHandleEmergencyClicked() {
    hospital.handleEmergency();
    // updateOutput("🚨 Handling emergency patient.");
    // The handleEmergency function already prints its output to the console.
    // The previous updateOutput call was redundant and not necessary.
}

void MainWindow::onShowActivePatientsClicked() {
    QString output = "\n--- Active Patients ---\n";
    if (hospital.getActivePatients().empty()) {
        output += "No active patients.\n";
    }
    for (auto* p : hospital.getActivePatients()) {
        output += QString("%1. %2 (%3) - %4\n")
        .arg(p->id)
            .arg(p->name.c_str())
            .arg(p->emergency ? "🚨 Emergency" : "Normal")
            .arg(p->status.c_str());
    }
    outputDisplay->setText(output); // Use setText to clear previous output
}

void MainWindow::onShowDischargedPatientsClicked() {
    QString output = "\n--- Discharged Patients ---\n";
    if (hospital.getDischargedPatients().empty()) {
        output += "No discharged patients.\n";
    }
    for (auto* p : hospital.getDischargedPatients()) {
        output += QString("%1. %2 - %3 (Discharged)\n")
        .arg(p->id)
            .arg(p->name.c_str())
            .arg(p->disease.c_str());
    }
    outputDisplay->setText(output); // Use setText to clear previous output
}
