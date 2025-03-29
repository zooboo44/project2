#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Time {
public:
    int hour = 0;
    int min = 0;
    Time(int h, int m) {
        hour = h;
        min = m;
    }
};

class person {
    public:
        vector<pair<Time*, Time*>> busySchedule;
        pair<Time*, Time*> workingPeriod;
};

int getEarliestTimeToMeet(const vector<person*>& group) {
    int earliestTime = group.at(0)->workingPeriod.first->hour;
    for (int i = 0; i < group.size(); i++) {
        int beginWorkingPeriod = group.at(i)->workingPeriod.first->hour;
        if (beginWorkingPeriod > earliestTime) {
            earliestTime = beginWorkingPeriod;
        }
    }
    cout << "earliest time to meet" << earliestTime;
    return earliestTime;
}

vector<pair<Time*, Time*>> schedule(vector<person*>& group, int durration) {
    vector<pair<Time*,Time*>> output;

    int earliestTimeToMeet = getEarliestTimeToMeet(group);

    return output;
}

int main() {
    vector<person*> group;
    
    person* p1 = new person;
    person* p2 = new person;
    person* p3 = new person;

    group.push_back(p1);
    group.push_back(p2);
    group.push_back(p3);

    Time* p1t1 = new Time(7, 0);
    Time* p1t2 = new Time(18, 0);
    Time* p2t1 = new Time(8, 0);
    Time* p2t2 = new Time(17, 0);
    Time* p3t1 = new Time(6, 0);
    Time* p3t2 = new Time(16, 0);

    p1->workingPeriod.first = p1t1;
    p1->workingPeriod.second = p1t2;
    
    p2->workingPeriod.first = p2t1;
    p2->workingPeriod.second = p2t2;
    
    p3->workingPeriod.first = p3t1;
    p3->workingPeriod.second = p3t2;

    

    vector<pair<Time*, Time*>> available = schedule(group, 5);
}