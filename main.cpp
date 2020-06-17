#include <iostream>
#include <string>
#include <vector>
#include "events.hpp"

using namespace std;
int main() {
    event_t beginning;
    beginning.text = "Hello there";
    beginning.children = {{"Option 1", "event001"}, {"Option 2", "event002"}};
    cout << beginning.text << endl;

    event_t * cur;
    cur = &beginning;
    for (vector<string> option : cur->children) {
        cout << option[0] << ", " << option[1] << endl;
    }
    return 0;
}
