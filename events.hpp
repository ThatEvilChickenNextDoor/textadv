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

class event // event structure forward declaration
{
private:
    std::string desc{};
    std::vector<option_t> children{};
public:
    std::string getDesc();
    std::vector<option_t> getChildren();
    std::string time{};
    event(std::string name, std::string desc, std::vector<option_t> children);
    event(std::string name, std::string desc, std::vector<option_t> children, std::string time);
};

void makeCommon();
void makeIntroCalendar();
void makeEvents(std::string chara);
#endif