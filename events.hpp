#ifndef EVENTS
#define EVENTS
#include <string>
#include <vector>
class event {
    public:
        std::string getDesc();
        std::vector< std::vector<std::string> > getChildren();
        void action();
        event(std::string desc, std::vector< std::vector<std::string> > children);
    private:
        std::string desc;
        std::vector< std::vector<std::string> > children;
};
#endif