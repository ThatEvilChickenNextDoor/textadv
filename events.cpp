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

event::event(std::string name, std::string desc, std::vector<option_t> children, std::string time) : desc(desc), children(children), time(time)
{
    eventTree.insert({name, this});
}

void makeIntroCalendar()
{
    // intro event
    new event("intro000", "You open your eyes. Something is off.", {option_t{.text{"..."}, .next{"intro001"}}});
    new event(
        "intro001",
        "What could it be? You take a moment to gather your thoughts. It must be...",
        {option_t{
             .effects{"introBlue"},
             .prereq{"-introBlue"},
             .text{"Everything is blue."},
             .onClickText{"Ah yes, of course. There's a mysterious blue light filling the room. Not just that, but all the furniture seems to have turned blue as well. You try to remember when that happened, but you can't."},
             .next{"intro001"}},
         option_t{
             .effects{"introQuiet"},
             .prereq{"-introQuiet"},
             .text{"It's too quiet."},
             .onClickText{"Ah yes, of course. Even in the middle of the night, there should be some noise. But for the first time in a long time, your ears hear... absolutely nothing at all."},
             .next{"intro001"}},
         option_t{
             .effects{"introIgor"},
             .prereq{"-introIgor"},
             .text{"There is a bizarre old man sitting in my chair."},
             .onClickText{"Ah yes, of course. There's a old man sitting hunched over in your chair, with bulging eyes and a disturbingly long nose. He wasn't there before."},
             .next{"intro001"}},
         option_t{
             .prereq{{"introBlue", "introQuiet", "introIgor"}},
             .text{"Curious."},
             .next{"intro002"}}});
    new event("intro002", "The old man coughs quietly, and turns his head to look at you. You try to get out of bed, only to realize that you did not exist.", {option_t{.text{""}, .next{"intro003"}}});
    new event(
        "intro003",
        "Old Man\n\nAh, welcome to the Velvet Room. This place exists between dream and reality, mind and matter. My name is Igor. Do not be alarmed. I am here to guide you.",
        {option_t{
             .text{"Why are you in my room?"},
             .next{"intro004"}},
         option_t{
             .text{"..."},
             .next{"intro004"}}});
    new event(
        "intro004",
        "Igor\n\nThe Velvet Room takes many forms. To different people, it will manifest as different places. Rest assured, the actual you is still sleeping in your bed.",
        {option_t{
             .text{"Am I dreaming?"},
             .next{"intro005"}},
         option_t{
             .text{"..."},
             .next{"intro005"}}});
    new event(
        "intro005",
        "Igor\n\nThis is not a dream, though you are free to regard it as such, if you would prefer. Regardless, I bring words of warning, if you will hear them.",
        {option_t{.text{"..."}, .next{"intro006"}}});
    new event(
        "intro006",
        "Igor spread his arms, and the air was suddenly filled with blue playing cards. They shuffled themselves and came to rest in a neat deck in front of him. Igor started dealing them out onto the air in front of him. Each card had an elaborate design. The first card featured a tower split in half by lightning.",
        {option_t{.text{""}, .next{"intro007"}}});
    new event(
        "intro007",
        "Igor\n\nThe world faces a disaster of unparalleled magnitude...",
        {option_t{.text{""}, .next{"intro008"}}});
    new event(
        "intro008",
        "The next card was a large skull in front of a closed door.",
        {option_t{.text{""}, .next{"intro009"}}});
    new event(
        "intro009",
        "Igor\n\nThere will be much suffering, but through sacrifice...",
        {option_t{.text{""}, .next{"intro010"}}});
    new event(
        "intro010",
        "The third card showed a woman laid on a multicolored background.",
        {option_t{.text{""}, .next{"intro011"}}});
    new event(
        "intro011",
        "Igor\n\nThe world shall triumph and be born anew. And you...",
        {option_t{.text{""}, .next{"intro012"}}});
    new event(
        "intro012",
        "Igor dealt a final card, a lantern above an half-opened eye. Evidently he wasn't expecting this card, as he paused for a brief moment.",
        {option_t{.text{""}, .next{"intro013"}}});
    new event(
        "intro013",
        "Igor\n\n...and you have your role to play.",
        {option_t{.text{""}, .next{"intro014"}}});
    new event(
        "intro014",
        "Igor seems disappointed in something.",
        {option_t{.text{""}, .next{"intro015"}}});
    new event(
        "intro015",
        "Igor\n\nYou have great potential. But in the near future, you will face something you can't overcome alone. In that moment, you must learn to rely on your friends.",
        {option_t{.text{""}, .next{"intro016"}}});
    new event(
        "intro016",
        "Igor\n\nNow, I must take my leave. It seems that I have more that I must tend to.",
        {option_t{.text{""}, .next{"intro017"}}});
    new event(
        "intro017",
        "Igor gets up, and walks to the door.",
        {option_t{.text{""}, .next{"intro018"}}});
    new event(
        "intro018",
        "Igor\n\nI hope our paths cross again. The future is always so entangled... even I can't see where every thread goes.",
        {option_t{.text{""}, .next{"intro019"}}});
    new event(
        "intro019",
        "Igor chuckled, walked out of my room, and I woke up.",
        {});

    new event("introEnd", "The winds shift.", {});
    new event("intro100", "You've been here for a very long time.", {option_t{.text{"I..."}, .onClickText{"...where am I?"}, .next{"introEnd"}}});
    new event(
        "intro200",
        "A strong gust kicks up a cloud of dust.\nFor an instant, it looks like a familiar silouette.",
        {option_t{
             .effects{"m"},
             .text{"\"...Michael?"},
             .onClickText{"You reach out, but it is gone."},
             .next{"introEnd"}},
         option_t{
             .effects{"t"},
             .text{"\"...Taylor?"},
             .onClickText{"You reach out, but it is gone."},
             .next{"introEnd"}},
         option_t{
             .effects{"r"},
             .text{"\"...Reehan?"},
             .onClickText{"You reach out, but it is gone."},
             .next{"introEnd"}},
         option_t{
             .effects{"j"},
             .text{"\"...Julia?"},
             .onClickText{"You reach out, but it is gone."},
             .next{"introEnd"}}});
}

void makeEvents(std::string chara) // makes events
{
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
