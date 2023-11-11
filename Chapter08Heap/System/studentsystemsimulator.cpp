#include "studentsystemsimulator.h"

#include "stdio.h"

#include <iostream>
#include <string>
#include <iostream>
#include <queue>
#include <vector>
#include <assert.h>

#include <sstream>
#include <fstream>


using namespace std;


const char* nameOfStudent(){
    return "Homer Simpson";
}

struct Customer{
    string m_name;
    int    m_arrival;
    int    m_timeSpent;
};

struct Event{
    string m_name;
    int    m_timeToLeave;
    Event(string name, int timeToLeave): m_name(name), m_timeToLeave(timeToLeave) {}
};


struct AWorseThanB {
    bool operator()(const Event& a, const Event& b){
        return a.m_timeToLeave >b.m_timeToLeave;
    }
};

// ANROP:   string str = timestring( secondsAfterMidnight)
string timestring(int secondsAfterMidnight){

    const int secondsPerMinute = 60;
    const int secondsPerHour = 60 * secondsPerMinute;
    const int secondsPerDay  = 24 * secondsPerHour;

    int d = secondsAfterMidnight/secondsPerDay;
    int h = (secondsAfterMidnight / secondsPerHour ) % 24;
    int m = (secondsAfterMidnight / secondsPerMinute) % 60;
    int s = secondsAfterMidnight % secondsPerMinute;

    char buffer[100];
    snprintf ( buffer, 100, "[%d] %02d:%02d:%02d", d,h,m,s);

    return string( buffer );
}


// ANROP: infil >> customer;
istream& operator>>(istream& infil, Customer &customer){
    infil >> customer.m_name >> customer.m_arrival >> customer.m_timeSpent;
    return infil;
}



// Det kan vara lämpligt att flytta fram tiden med hjälp av denna funktion
// Funktionen verifierar att den nya tiden är större än den gamla, och
// kraschar om du har en bug.
void increaseValue(int &theTime, int newTime){
    assert( newTime>= theTime );
    theTime = newTime;
}


//TODO implementera simulatorn!
void simulate(int antalKassor){

    cout << "---- antal Kassor " << antalKassor << " -------------------\n";

    std::ifstream infil;
    infil.open("../../Chapter08Heap/System/customers.txt");
    assert(infil);

    // Nedanstående que kommer att lagra Event-objekt
    // sorterade med avseende på m_timeToLeave.
    priority_queue<Event, vector<Event>, AWorseThanB> que;


    Customer customer;
    // Nedanstående kod är felaktig/ofullständig
    while (infil >> customer){
        cout <<  customer.m_name << "  arrival:" <<  timestring( customer.m_arrival ) << endl;
    }

}




void studentSystemSimulator(){


    for (int kassor = 1; kassor <=20 ; kassor +=1)
        simulate(kassor);

}



/********************************************************************************************

  GE resultatet här!


  för antalKasor=1..20


TODO

********************************************************************************************/
