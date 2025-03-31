//Christian Ziobro
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

class Time { //time class
public:
    int hour = 0;
    int min = 0;
    int totalTime = hour * 60 + min;
    Time(int h, int m) : hour(h), min(m) {}
    Time() {}
};

class person { //person class
public:
    vector<pair<Time*, Time*>> busySchedule; //holds a pair of times for the busy schedule
    pair<Time*, Time*> workingPeriod; //holds a pair of times for 
};

void printTimes(vector<pair<Time*, Time*>> output) { //iterates through a list and prints times
    for (int i = 0; i < output.size(); i++)
    {
        cout << setfill('0') << setw(2) << output.at(i).first->hour << ":" << setfill('0') << setw(2) << output.at(i).first->min << "-" << setfill('0') << setw(2) << output.at(i).second->hour << ":" << setfill('0') << setw(2) << output.at(i).second->min << "\t";
    }
}


bool comp(pair<Time*, Time*> p1, pair<Time*, Time*> p2) { //compares two times to order
    if (p1.first->totalTime == p2.first->totalTime) {
        return p1.second->totalTime < p2.second->totalTime;
    }
    return p1.first->totalTime < p2.first->totalTime;
}

bool withinWorkingHours(pair<Time*, Time*> event, pair<Time*, Time*> workingHours) { //checks if event is within working hours of the group
    if ((event.first->totalTime >= workingHours.first->totalTime) && (event.second->totalTime <= workingHours.second->totalTime)) {
        return true;
    }
    return false;
}
bool getAvailableStartTime(Time* end, Time* start, Time* durration) {
    //checks if time between events is greater than or equal to the durration
    if (end->totalTime < start->totalTime && (start->totalTime - end->totalTime) >= durration->totalTime) {
        return true;
    }
    return false;
}

Time* getEarliestTimeToMeet(const vector<person*>& group) {
    //finds the earliest time everyone can meet
    Time* earliestTime = new Time();
    earliestTime = group.at(0)->workingPeriod.first;

    for (int i = 0; i < group.size(); i++) {
        Time* beginWorkingPeriod = new Time();
        beginWorkingPeriod = group.at(i)->workingPeriod.first;
        //get earliest time everyone can meet
        if (beginWorkingPeriod > earliestTime) {
            earliestTime = beginWorkingPeriod;
        }
    }
    return earliestTime;
}

Time* getEarliestLatestTime(const vector<person*>& group) {
    //finds the soonest latest time everyone can meet
    Time* earliestLatestTime = new Time();
    earliestLatestTime = group.at(0)->workingPeriod.second;

    //iterate through people
    for (int i = 0; i < group.size(); i++) {
        Time* endWorkingPeriod = new Time();
        endWorkingPeriod = group.at(i)->workingPeriod.second;
        //get earliest time people can meet
        if (endWorkingPeriod < earliestLatestTime) {
            earliestLatestTime = endWorkingPeriod;
        }
    }
    return earliestLatestTime;
}

vector<pair<Time*, Time*>> schedule(vector<person*>& group, Time* durration) { //schedules the available times
    //vector of available times
    vector<pair<Time*, Time*>> output;

    //earliest time to meet and latest time to meet based on poeple's working time
    Time* earliestTimeToMeet = new Time();
    Time* earliestLatestTime = new Time();
    earliestTimeToMeet = getEarliestTimeToMeet(group);
    earliestLatestTime = getEarliestLatestTime(group);

    //put time window in pair
    pair<Time*, Time*> workingHours;
    workingHours.first = earliestTimeToMeet;
    workingHours.second = earliestLatestTime;

    vector<pair<Time*, Time*>> unavailabilities;

    //combines the unavilable times from every person
    for (int i = 0; i < group.size(); i++) {
        for (int j = 0; j < group.at(i)->busySchedule.size(); j++) {
            unavailabilities.push_back(group.at(i)->busySchedule.at(j));
        }
    }

    //sorts unavailable times in ascending order
    sort(unavailabilities.begin(), unavailabilities.end(), comp);

    int i = 0;
    int j = 1;
    //if there is time within the working window and before an event, add it to availabilities
    if (earliestTimeToMeet->totalTime < unavailabilities.at(0).first->totalTime) {
        output.push_back({ earliestTimeToMeet,unavailabilities.at(0).first });
    }
    //iterate through unavailabilities vector
    while (j != unavailabilities.size()) {
        //if time between events is within working hour, add time block to availabilities list
        if (withinWorkingHours(unavailabilities.at(i), workingHours) && getAvailableStartTime(unavailabilities.at(i).second, unavailabilities.at(j).first, durration)) {
            output.push_back({ unavailabilities.at(i).second, unavailabilities.at(j).first });
        }
        i++;
        j++;
    }
    
    //checks if there are any availabilities after the last event that is within working hours
    if ((unavailabilities.at(unavailabilities.size() - 1).second->totalTime < earliestLatestTime->totalTime) && (earliestLatestTime->totalTime - unavailabilities.at(unavailabilities.size() - 1).second->totalTime)) {
        output.push_back({ unavailabilities.at(unavailabilities.size() - 1).second, workingHours.second });
    }

    //return list of available time blocks
    return output;
}

int main() {
    vector<person*> group; //holds people
    int groupSize; //size of group
    int startHour, startMin, endHour, endMin, durrationHour, durrationMin;

    //get number of members in group
    cout << "Enter number of group members: ";
    cin >> groupSize;

    //gets durration of event
    cout << "Enter durration of event: " << endl;
    cout << "HH: "; cin >> durrationHour;
    cout << "MM: "; cin >> durrationMin;
    Time* durration = new Time(durrationHour, durrationMin);
    cout << endl;

    //iterates through the group and prompts for working time and event times
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
        //pushes created person in the group vector
        group.push_back(p1);
    }

    //gets vector of available time
    vector<pair<Time*, Time*>> available = schedule(group, durration);
    cout << "Available times: ";
    printTimes(available); //prints available times
}