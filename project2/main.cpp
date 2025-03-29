#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Time {
public:
    int hour = 0;
    int min = 0;
    Time(int h, int m) : hour(h), min(m){}
    Time(){}
};

class person {
    public:
        vector<pair<Time*, Time*>> busySchedule;
        pair<Time*, Time*> workingPeriod;
};

Time* getEarliestTimeToMeet(const vector<person*>& group) {
    Time* earliestTime = new Time();
    earliestTime = group.at(0)->workingPeriod.first;

    for (int i = 0; i < group.size(); i++) {
        Time* beginWorkingPeriod = new Time();
        beginWorkingPeriod = group.at(i)->workingPeriod.first;
        if (beginWorkingPeriod > earliestTime) {
            earliestTime = beginWorkingPeriod;
        }
    }
    cout << "earliest time to meet: " << earliestTime->hour << ":" << earliestTime->min << endl;
    return earliestTime;
}

vector<pair<Time*, Time*>> schedule(vector<person*>& group, int durration) {
    vector<pair<Time*,Time*>> output;

    Time* earliestTimeToMeet = new Time();

    earliestTimeToMeet = getEarliestTimeToMeet(group);

    return output;
}

int main() {
    vector<person*> group;
    
    person* p1 = new person;
    person* p2 = new person;

    group.push_back(p1);
    group.push_back(p2);

    Time* p1t1 = new Time(9, 0);
    Time* p1t2 = new Time(19, 0);
    Time* p2t1 = new Time(9, 0);
    Time* p2t2 = new Time(18, 30);

    p1->workingPeriod.first = p1t1;
    p1->workingPeriod.second = p1t2;
    
    p2->workingPeriod.first = p2t1;
    p2->workingPeriod.second = p2t2;
    

    vector<pair<Time*, Time*>> available = schedule(group, 5);
}