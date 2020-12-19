#ifndef EVENTS
#define EVENTS
#include <string>
#include <vector>

struct option_t
{
    std::vector<std::string> effects{};
    std::vector<std::string> prereq{};
    std::string text{};
    std::string onClickText{};
    std::string next{};
};

class event
{ // event structure forward declaration
public:
    std::string getDesc();
    std::vector<option_t> getChildren();
    event(std::string name, std::string desc, std::vector<option_t> children);

private:
    std::string desc{};
    std::vector<option_t> children{};
};

void makeIntroCalendar();
void makeEvents(std::string chara);
#endif