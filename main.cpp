#include <iostream>
#include <string>
#include <vector>
#include "events.hpp"

using namespace std;
int main() {
    event beginning("Hello world", {{"Option 1", "event001"}, {"Option 2", "event002"}});
    
    cout << beginning.getDesc() << endl;

    event * cur;
    cur = &beginning;
    for (vector<string> option : cur->getChildren()) {
        cout << option[0] << ", " << option[1] << endl;
    }
    return 0;
}
