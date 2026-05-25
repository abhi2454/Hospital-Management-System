cmake_minimum_required(VERSION 3.19)
project(HospitalManagement2 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

# Use 'file' to list the files in the same directory as this CMakeLists.txt
# This is more robust than listing them manually.
file(GLOB_RECURSE SOURCES
    main.cpp
    Hospital.cpp
    mainwindow.cpp
)

file(GLOB_RECURSE HEADERS
    mainwindow.h
    Hospital.h
    Patient.h
    Nurse.h
    Doctor.h
)

# Add all source and header files to the executable
qt_add_executable(HospitalManagement2
    WIN32 MACOSX_BUNDLE
    ${SOURCES}
    ${HEADERS}
)

# Link the necessary Qt libraries
target_link_libraries(HospitalManagement2
    PRIVATE
        Qt6::Core
        Qt6::Widgets
)

# Set up include directories
target_include_directories(HospitalManagement2
    PRIVATE
        .
)

# This is a standard setup for deployment and installation
include(GNUInstallDirs)
install(TARGETS HospitalManagement2
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
qt_generate_deploy_app_script(
    TARGET HospitalManagement2
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
