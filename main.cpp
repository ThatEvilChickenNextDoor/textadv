#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "globals.hpp"
#include "events.hpp"

using namespace std;

int main() {
    makeEvents();
    string currentEvent = "event000";
    event * cur;
    cur = eventTree.find("event000")->second;
    while (cur != eventTree.end()->second) {
        cout << cur->getDesc() << '\n' << endl;
        auto children = cur->getChildren();
        for (vector<string> option : children) {
            cout << option[0] << endl;
        }
        string in;
        bool valid = false;
        while (!valid) {
            cin >> in;
            int choice = stoi(in);
            choice--;
            if (choice >= 0 && choice < (long int)children.size()){
                valid = true;
                currentEvent = children[choice][1];
                cur = eventTree.find(currentEvent)->second;
            } else{
                cout << "no" << endl;
            }
        }
    }
    cout << "event not found: " << currentEvent << endl;
    return 1;
    //return 0;
}
