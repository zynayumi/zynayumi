

#ifndef UI_HPP_INCLUDED
#define UI_HPP_INCLUDED

// #include "external/src/nanosvg.h"
// #include "external/src/nanosvgrast.h"

#include "DistrhoUI.hpp"
#include "NanoVG.hpp"
#include "Window.hpp"
#include <vector>

// #include "DropsGeometry.hpp"
//#include "DropsPlugin.hpp"
// #include "TextButton.hpp"
#include "Knob.hpp"
#include "DropDown.hpp"
#include "Menu.hpp"
#include "Slider.hpp"
// #include "RadioButton.hpp"
#include "HBox.hpp"
#include "VBox.hpp"
#include "PopUp.hpp"
//#include "fonts.hpp"
#include "CheckBox.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------------------------------------------

class UIZynayumi : public UI,
                   public Knob::Callback,
                   public DropDown::Callback,
                   public Menu::Callback,
                   public Slider::Callback,
                   public CheckBox::Callback
{
public:
    UIZynayumi();
    ~UIZynayumi();

protected:
    void parameterChanged(uint32_t index, float value) override;
    void onNanoDisplay() override;
    bool onMouse(const MouseEvent &ev) override;
    bool onScroll(const ScrollEvent &) override;
    bool onMotion(const MotionEvent &) override;
    void programLoaded(uint32_t index);
    void onDropDownClicked(DropDown *dropdown) override;
    void knobDragStarted(Knob *knob) override;
    void knobDragFinished(Knob *knob, float value) override;
    void knobValueChanged(Knob *knob, float value) override;
    void onSliderValueChanged(Slider *slider, float value) override;
    void onMenuClicked(Menu *menu, uint id, std::string item);
    void onCheckBoxClicked(CheckBox *checkbox, bool is_checked);

private:
    // parameters

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIZynayumi)
};

END_NAMESPACE_DISTRHO

#endif