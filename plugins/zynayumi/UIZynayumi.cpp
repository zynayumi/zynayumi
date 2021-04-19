#include "UIZynayumi.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------------

UIZynayumi::UIZynayumi()
    : UI(1000, 600)
{
}

UIZynayumi::~UIZynayumi()
{
}

void UIZynayumi::parameterChanged(uint32_t index, float value)
{
    // do stuff
}

void UIZynayumi::programLoaded(uint32_t id)
{
    // do stuff
}

void UIZynayumi::onNanoDisplay()
{
    float width = getWidth();
    float height = getHeight();
    // background
    beginPath();
    fillColor(Color(0,0,0));
    rect(0.0f, 0.0f, width, height);
    fill();
    closePath();
}

bool UIZynayumi::onMouse(const MouseEvent &ev)
{
    return false;
}

bool UIZynayumi::onScroll(const ScrollEvent &ev)
{
    return false;
}

bool UIZynayumi::onMotion(const MotionEvent &ev)
{
    return false;
}

void UIZynayumi::onDropDownClicked(DropDown *dropDown)
{
    auto id = dropDown->getId();

#ifdef DEBUG
    printf("dropdown %i clicked\n", id);
#endif
}

void UIZynayumi::knobDragStarted(Knob *)
{
    // const uint id = knob->getId();
    // #ifdef DEBUG
    //     printf("%i , drag started\n", id);
    // #endif
}
void UIZynayumi::knobDragFinished(Knob *knob, float value)
{
    auto id = knob->getId();
#ifdef DEBUG
    printf("%i , drag finished\n", id);
#endif
}
void UIZynayumi::knobValueChanged(Knob *knob, float value)
{

    auto id = knob->getId();

#ifdef DEBUG
    printf("knobValueChanged(%i, %f)\n", id, value);
#endif
}

void UIZynayumi::onSliderValueChanged(Slider *slider, float value)
{
    uint id = slider->getId();
#ifdef DEBUG
    printf("slider %i, value %f\n", id, value);
#endif
}

void UIZynayumi::onMenuClicked(Menu *menu, uint menu_id, std::string item)
{
    const uint id = menu->getId();
#ifdef DEBUG
    printf("menu %i ,menu_id %i, item %s\n", id, menu_id, item.c_str());
#endif
}

void UIZynayumi::onCheckBoxClicked(CheckBox *checkbox, bool is_checked)
{
    // float value = static_cast<float>(is_checked);
    const int id = checkbox->getId();
#ifdef DEBUG
    printf("onCheckBoxClicked(CheckBox %i, %i)\n", id, is_checked);
#endif
}


UI *createUI()
{
    return new UIZynayumi();
}

// -----------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
