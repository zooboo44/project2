#include <vector>
#include <string>
#include <iostream>
#include <utility>

using namespace std;

class person {
    public:
        vector<pair<int, int>> busySchedule;
        pair<int, int> workingPeriod;

};

int getEarliestTimeToMeet(const vector<person*>& group) {
    int earliestTime = group.at(0)->workingPeriod.first;
    for (int i = 0; i < group.size(); i++) {
        int beginWorkingPeriod = group.at(i)->workingPeriod.first;
        if (beginWorkingPeriod > earliestTime) {
            earliestTime = beginWorkingPeriod;
        }
    }
    return earliestTime;
}

pair<int,int> schedule(vector<person*>& group, int durration) {
    pair<int, int> output;

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

    p1->workingPeriod.first = 7;
    p1->workingPeriod.second = 18;
    
    p2->workingPeriod.first = 8;
    p2->workingPeriod.second = 17;
    
    p3->workingPeriod.first = 6;
    p3->workingPeriod.second = 16;

    pair<int, int> available = schedule(group, 5);

}