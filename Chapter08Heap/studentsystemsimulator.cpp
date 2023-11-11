#include "studentsystemsimulator.h"

#include "stdio.h"

#include <iostream>
#include <string>
#include <iostream>
#include <queue>
#include <vector>
#include <assert.h>

#include <sstream>


using namespace std;

struct Customer{
    string _name;
    int    _arrival;
    int    _timeSpent;

};

struct Event{
    string _name;
    int    _timeToLeave;
    Event(string name, int timeToLeave): _name(name), _timeToLeave(timeToLeave) {}
};


struct AWorseThanB {
    bool operator()(const Event& a, const Event& b){
        return a._timeToLeave >b._timeToLeave;
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

// ANROP: ok = didReadCustomer(fp, (&customer));
bool didReadCustomer(FILE* fp, Customer *pCustomer){

    char name[100];
    int timeArrive;
    int timeSpent;

    int nbrRead = fscanf( fp, "%s %d %d" , name , &timeArrive, &timeSpent);
    if (nbrRead==3){
        pCustomer->_name = name;
        pCustomer->_arrival = timeArrive;
        pCustomer->_timeSpent = timeSpent;
        return true;
    }
    return false;
}

void increaseValue(int &theTime, int newTime){
    assert( newTime>= theTime );
    theTime = newTime;
}

void simulate(int antalKassor){

    cout << "--- antal Kassor " << antalKassor << " -------------------\n";

    FILE *fp = fopen("../../Chap8/System/customers.txt", "r");

    Customer customer;
    priority_queue<Event, vector<Event>, AWorseThanB> que;
    int theTime = 0;
    int totalTimeInQue = 0;
    int totalTimeSpent = 0;
    int closingTime = 0;

    while (didReadCustomer(fp, (&customer)) ){

       //  cout << timestring( customer._arrival ) << endl;

        if (theTime<customer._arrival)
            increaseValue((theTime), customer._arrival);

        while (!que.empty() && que.top()._timeToLeave <= theTime) {
            que.pop();
        }

        if (que.size()==antalKassor){
            increaseValue((theTime), que.top()._timeToLeave);
            que.pop();
        }

        Event event(customer._name, theTime+customer._timeSpent);
        if (event._name=="Ragnar"){
            cout << "Ragnar blir klar " << timestring(event._timeToLeave) << endl;
        }
        que.push(event);
        closingTime = max(event._timeToLeave, closingTime);
        totalTimeInQue += (event._timeToLeave-customer._arrival-customer._timeSpent);
        totalTimeSpent += (event._timeToLeave-customer._arrival);

    }

    cout << "total kötid " << timestring(totalTimeInQue) << endl;

    int personTime = (closingTime-11*60*60)*antalKassor + totalTimeSpent;
    cout << "total persontid " << timestring(personTime) << endl;

    fclose(fp);

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
