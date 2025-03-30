//Christian Ziobro
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

class Time {
public:
    int hour = 0;
    int min = 0;
    int totalTime = hour * 60 + min;
    Time(int h, int m) : hour(h), min(m){}
    Time(){}

};

class person {
    public:
        vector<pair<Time*, Time*>> busySchedule;
        pair<Time*, Time*> workingPeriod;
};

void printTimes(vector<pair<Time*, Time*>> output) {
    for (int i = 0; i < output.size(); i++)
    {
        cout << setfill('0') << setw(2) << output.at(i).first->hour << ":" << setfill('0') << setw(2) << output.at(i).first->min << "-" << setfill('0') << setw(2) << output.at(i).second->hour << ":" << setfill('0') << setw(2) << output.at(i).second->min << "\t";
    }
}


bool comp(pair<Time*, Time*> p1, pair<Time*, Time*> p2) {
    if (p1.first->totalTime == p2.first->totalTime) {
        return p1.second->totalTime < p2.second->totalTime;
    }
    return p1.first->totalTime < p2.first->totalTime;
}

bool withinWorkingHours(pair<Time* ,Time*> event, pair<Time*, Time*> workingHours) {
    if ((event.first->totalTime >= workingHours.first->totalTime) && (event.second->totalTime <= workingHours.second->totalTime)) {
        return true;
    }
    return false;
}
bool getAvailableStartTime(Time* end, Time* start, Time* durration) {
    if (end->totalTime < start->totalTime && (start->totalTime - end->totalTime) > durration->totalTime) {
        return true;
    }
    return false;
}

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
    return earliestTime;
}

Time* getEarliestLatestTime(const vector<person*>& group) {
    Time* earliestLatestTime = new Time();
    earliestLatestTime = group.at(0)->workingPeriod.second;

    for (int i = 0; i < group.size(); i++) {
        Time* endWorkingPeriod = new Time();
        endWorkingPeriod = group.at(i)->workingPeriod.second;
        if (endWorkingPeriod < earliestLatestTime) {
            earliestLatestTime = endWorkingPeriod;
        }
    }
    return earliestLatestTime;
}

vector<pair<Time*, Time*>> schedule(vector<person*>& group, Time* durration) {
    vector<pair<Time*,Time*>> output;

    Time* earliestTimeToMeet = new Time();
    Time* earliestLatestTime = new Time();

    earliestTimeToMeet = getEarliestTimeToMeet(group);
    earliestLatestTime = getEarliestLatestTime(group);
    pair<Time*, Time*> workingHours;
    workingHours.first = earliestTimeToMeet;
    workingHours.second = earliestLatestTime;

    vector<pair<Time*, Time*>> unavailabilities;

    for (int i = 0; i < group.size(); i++) {
        for (int j = 0; j < group.at(i)->busySchedule.size(); j++) {
            unavailabilities.push_back(group.at(i)->busySchedule.at(j));
        }
    }

    cout << "Unavailable times: ";
    sort(unavailabilities.begin(), unavailabilities.end(), comp);
    printTimes(unavailabilities);
    cout << endl;

    int i = 0;
    int j = 1;
    if (earliestTimeToMeet->totalTime < unavailabilities.at(0).first->totalTime) {
        output.push_back({ earliestTimeToMeet,unavailabilities.at(0).first });
    }
    while (j != unavailabilities.size()) {
        if (withinWorkingHours(unavailabilities.at(i), workingHours) && getAvailableStartTime(unavailabilities.at(i).second, unavailabilities.at(j).first, durration)) {
            output.push_back({ unavailabilities.at(i).second, unavailabilities.at(j).first });
        }
        i++;
        j++;
    }

    if ((unavailabilities.at(unavailabilities.size() - 1).second->totalTime < earliestLatestTime->totalTime) && (earliestLatestTime->totalTime - unavailabilities.at(unavailabilities.size() - 1).second->totalTime)) {
        output.push_back({ unavailabilities.at(unavailabilities.size()-1).second, workingHours.second });
    }


    return output;
}

int main() {
    vector<person*> group;
    
    person* p1 = new person;
    person* p2 = new person;

    group.push_back(p1);
    group.push_back(p2);

    Time* p1t1 = new Time(6, 0);
    Time* p1t2 = new Time(19, 0);
    Time* p2t1 = new Time(6, 0);
    Time* p2t2 = new Time(18, 30);

    p1->workingPeriod.first = p1t1;
    p1->workingPeriod.second = p1t2;
    
    p2->workingPeriod.first = p2t1;
    p2->workingPeriod.second = p2t2;

    Time* p1b1S = new Time(7,0);
    Time* p1b1E = new Time(8,30);

    Time* p1b2S = new Time(12,0);
    Time* p1b2E = new Time(13, 0);

    Time* p1b3S = new Time(16, 0);
    Time* p1b3E = new Time(18, 0);
    
    Time* p2b1S = new Time(9, 0);
    Time* p2b1E = new Time(10, 30);
    
    Time* p2b2S = new Time(12, 20);
    Time* p2b2E = new Time(13, 30);
    
    Time* p2b3S = new Time(14, 0);
    Time* p2b3E = new Time(15, 0);
    
    Time* p2b4S = new Time(16, 0);
    Time* p2b4E = new Time(17, 0);
    
    p1->busySchedule.push_back({ p1b1S,p1b1E });
    p1->busySchedule.push_back({ p1b2S,p1b2E });
    p1->busySchedule.push_back({ p1b3S,p1b3E });
    p2->busySchedule.push_back({ p2b1S,p2b1E });
    p2->busySchedule.push_back({ p2b2S,p2b2E });
    p2->busySchedule.push_back({ p2b3S,p2b3E });
    p2->busySchedule.push_back({ p2b4S,p2b4E });

    Time* durration = new Time(0,30);
    vector<pair<Time*, Time*>> available = schedule(group, durration);
    cout << "Available times: ";
    printTimes(available);
}