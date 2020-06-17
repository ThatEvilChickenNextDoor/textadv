#include "events.hpp"

std::string event::getDesc() {
    return desc;
}

std::vector< std::vector<std::string> > event::getChildren() {
    return children;
}

event::event(std::string desc, std::vector< std::vector<std::string> > children): desc(desc), children(children) {

}