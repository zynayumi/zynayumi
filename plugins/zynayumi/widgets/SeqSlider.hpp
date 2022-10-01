#ifndef SEQ_SLIDER_HPP
#define SEQ_SLIDER_HPP

#include "Window.hpp"
#include "Widget.hpp"
#include "NanoVG.hpp"

START_NAMESPACE_DISTRHO

class SeqSlider : public NanoWidget
{
public:
    class Callback
    {
    public:
        virtual ~Callback() {}
        virtual void onSeqSliderValueChanged(SeqSlider *seq_slider, int value) = 0;
    };
    explicit SeqSlider(Window &parent) noexcept;
    explicit SeqSlider(Widget *widget) noexcept;
    void setCallback(Callback *cb);
    void setValue(int val) noexcept;
    int getValue() noexcept;

    Color background_color;
    Color foreground_color; // triangle
    Color highlight_color;
    int default_value;
    int min_value;
    int max_value;
    int step;
    bool left_right;
    bool striped;
    Callback *callback;

protected:
    void onNanoDisplay() override;
    bool onMouse(const MouseEvent &) override;
    bool onMotion(const MotionEvent &) override;
    bool onScroll(const ScrollEvent &) override;

private:
    
    bool dragging_;
    float value_;
    Color fill_color_;
    bool has_mouse_;
    float tmp_value_;
    int last_mouse_x_;
    int last_mouse_y_;
  
    DISTRHO_LEAK_DETECTOR(SeqSlider)
};

END_NAMESPACE_DISTRHO

#endif // SCROLLBAR_HPP
