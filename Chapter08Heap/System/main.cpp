#include <QCoreApplication>
#include "studentsystemsimulator.h"
#include <iostream>
#include <string>

const char* nameOfStudent();

int main(int argc, char *argv[])
{
    assert( std::string( nameOfStudent()) != "Homer Simpson" );

    std::cout <<  "Running simulator by " << nameOfStudent() << std::endl;

    studentSystemSimulator();

}
