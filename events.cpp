#include <iostream>
#include "globals.hpp"
#include "events.hpp"

std::string event::getDesc()
{
    return desc;
}

std::vector<option_t> event::getChildren()
{
    return children;
}

event::event(std::string name, std::string desc, std::vector<option_t> children) : desc(desc), children(children)
{
    eventTree.insert({name, this}); // event constructor, adds event/pointer pair to eventTree on creation
}

void makeIntroCalendar()
{
    // intro event
    new event("intro000", "You open your eyes. Something is off.", {option_t{.text{"..."}, .next{"intro001"}}});
    new event("intro001", "What could it be? You take a moment to gather your thoughts. It must be...",
        {
            option_t{
                .effects{"introBlue"},
                .prereq{"-introBlue"},
                .text{"The room is blue."},
                .onClickText{"Ah yes, of course. There's a mysterious blue light filling the room. Not just that, but all the furniture seems to have turned blue as well. You try to remember when you changed everything out, but you can't."},
                .next{"intro001"}
            },
            option_t{
                .effects{"introQuiet"},
                .prereq{"-introQuiet"},
                .text{"It's too quiet."},
                .onClickText{"Ah yes, of course. Even in the middle of the night, there should be some noise. But for the first time in a long time, your ears hear... absolutely nothing at all."},
                .next{"intro001"}
            },
            option_t{
                .effects{"introIgor"},
                .prereq{"-introIgor"},
                .text{"There is a bizarre old man sitting in my chair."},
                .onClickText{"Ah yes, of course. There's a old man sitting hunched over in your chair, with bulging eyes and a disturbingly long nose. He wasn't there before."},
                .next{"intro001"}
            },
            option_t{
                .prereq{{"introBlue", "introQuiet", "introIgor"}},
                .text{"Hmm."},
                .next{"intro002"}
            },
        });
    new event("intro002", "The old man coughs quietly, and turns his head to look at you.", {option_t{.text{""}, .next{"intro003"}}});
    new event("intro003", "Igor\n\nAh, welcome to the Velvet Room. This place exists between dram and reality, mind and matter. My name is Igor. Do not be alarmed. I am here to guide you.", {option_t{.text{"..."}, .next{"intro004"}}});
    new event("introEnd", "The winds shift.", {});
    new event("intro100", "You've been here for a very long time.", {option_t{.text{"I..."}, .onClickText{"...where am I?"}, .next{"introEnd"}}});
    new event("intro200", "A strong gust kicks up a cloud of dust.\nFor an instant, it looks like a familiar silouette.", {option_t{.effects{"m"}, .text{"\"...Michael?"}, .onClickText{"You reach out, but it is gone."}, .next{"introEnd"}}, option_t{.effects{"t"}, .text{"\"...Taylor?"}, .onClickText{"You reach out, but it is gone."}, .next{"introEnd"}}, option_t{.effects{"r"}, .text{"\"...Reehan?"}, .onClickText{"You reach out, but it is gone."}, .next{"introEnd"}}, option_t{.effects{"j"}, .text{"\"...Julia?"}, .onClickText{"You reach out, but it is gone."}, .next{"introEnd"}}});
}

void makeEvents(std::string chara)
{ // makes events
    new event(
        "event000",
        "This is the beginning of the story!",
        {option_t{
             .effects{"flag"},
             .text{"Hi " + chara},
             .next{"event001"}},
         option_t{
             .prereq{{"flag"}},
             .text{"Option 2"},
             .next{"event002"}},
         option_t{
             .text{"Crash the game"},
             .next{"asefygasekfiuygaskyf"}}});
    new event(
        "event001",
        "You picked option 1!\nNow go back.",
        {option_t{
            .text{"Go back"},
            .onClickText{"You went back."},
            .next{"event000"}}});
    new event(
        "event002",
        "You picked option 2!",
        {option_t{
            .text{"End story"},
            .next{"event_end"}}});
    new event(
        "event_end",
        "This is the end of the story. Goodbye!",
        {});
    new event(
        "newthing",
        "Hey look, it's something new!",
        {option_t{
            .text{"Intriguing"},
            .next{"event_end"}}});
}
