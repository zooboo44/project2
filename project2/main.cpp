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
    Time(int h, int m) : hour(h), min(m) {}
    Time() {}

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

bool withinWorkingHours(pair<Time*, Time*> event, pair<Time*, Time*> workingHours) {
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
    vector<pair<Time*, Time*>> output;

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
        output.push_back({ unavailabilities.at(unavailabilities.size() - 1).second, workingHours.second });
    }


    return output;
}

int main() {
    vector<person*> group;
    int groupSize;
    int startHour, startMin, endHour, endMin, durrationHour, durrationMin;

    cout << "Enter number of group members: ";
    cin >> groupSize;

    cout << "Enter durration of event: " << endl;
    cout << "HH: "; cin >> durrationHour;
    cout << "MM: "; cin >> durrationMin;
    Time* durration = new Time(durrationHour, durrationMin);
    cout << endl;

    for (int i = 0; i < groupSize; i++) {
        person* p1 = new person;
        cout << "\nPerson #" << i + 1 << endl;
        cout << "Enter work hours for person " << i + 1 << " (HH:MM) : " << endl;
        cout << "Start HH: ";  cin >> startHour;
        cout << "Start MM: "; cin >> startMin;
        cout << "End HH: ";  cin >> endHour;
        cout << "End MM: "; cin >> endMin;
        Time* startWork = new Time(startHour, startMin);
        Time* endWork = new Time(endHour, endMin);
        p1->workingPeriod.first = startWork;
        p1->workingPeriod.second = endWork;

        int schedule = 0;
        while (schedule != -1) {
            cout << "\nEnter busy times: " << endl;
            cout << "Start HH: "; cin >> startHour;
            cout << "Start MM: "; cin >> startMin;
            cout << "End HH: "; cin >> endHour;
            cout << "End MM: "; cin >> endMin;
            Time* start = new Time(startHour, startMin);
            Time* end = new Time(endHour, endMin);
            p1->busySchedule.push_back(make_pair(start, end));
            cout << "Add another entry? (-1 to exit): ";
            cin >> schedule;
        }
        group.push_back(p1);
    }

    vector<pair<Time*, Time*>> available = schedule(group, durration);
    cout << "Available times: ";
    printTimes(available);
}