#ifndef WAVEFORM_HPP
#define WAVEFORM_HPP

#include "Window.hpp"
#include "Widget.hpp"
#include "NanoVG.hpp"

START_NAMESPACE_DISTRHO

class Waveform : public NanoWidget
{
public:
    class Callback
    {
    public:
        virtual ~Callback() {}
        virtual void onWaveformValueChanged(Waveform *waveform, int value) = 0;
    };
    explicit Waveform(Window &parent) noexcept;
    explicit Waveform(Widget *widget) noexcept;
    void setCallback(Callback *cb);
    void setValue(int val) noexcept;
    int getValue() noexcept;

    Color background_color;
    Color foreground_color;
    float default_value;
    int min_value;
    int max_value;

protected:
    void onNanoDisplay() override;
    bool onMouse(const MouseEvent &) override;
    bool onMotion(const MotionEvent &) override;
    bool onScroll(const ScrollEvent &) override;

private:
    Callback *callback;
    bool left_button_;
    int value_;
    Color fill_color_;
    int tmp_value_;
    bool using_default_;
  
    DISTRHO_LEAK_DETECTOR(Waveform)
};

END_NAMESPACE_DISTRHO

#endif 
