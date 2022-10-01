#include "Slider.hpp"

START_NAMESPACE_DISTRHO

Slider::Slider(Window &parent) noexcept
    : NanoWidget(parent)
{
    dragging_ = false;
    has_mouse_ = false;
    value_ = 0.f;
    tmp_value_ = 0.f;
    max_value = 1.0f;
    min_value = 0.0f;
    using_log_ = false;
    foreground_color = Color(1, 1, 1);
    background_color = Color(0, 0, 0);
    fill_color_ = foreground_color;
    callback = nullptr;
}

Slider::Slider(Widget *widget) noexcept
    : NanoWidget(widget)
{
    dragging_ = false;
    has_mouse_ = false;
    value_ = 0.f;
    tmp_value_ = 0.f;
    max_value = 1.0f;
    min_value = 0.0f;
    using_log_ = false;
    foreground_color = Color(1, 1, 1);
    background_color = Color(0, 0, 0);
    fill_color_ = foreground_color;
    callback = nullptr;
}

float Slider::getValue() noexcept
{
    return value_;
}
bool Slider::onMouse(const MouseEvent &ev)
{
    const bool containsMouse = contains(ev.pos);
    if (ev.press == 1 && containsMouse)
    {
        has_mouse_ = true;
        dragging_ = true;
        last_mouse_y_ = ev.pos.getY();
        return false;
    }
    else if (dragging_)
    {
        has_mouse_ = false;
        dragging_ = false;
        repaint();
        return false;
    }

    return false;
}

bool Slider::onScroll(const ScrollEvent &ev)
{
    if (!isVisible())
        return false;
    if (!contains(ev.pos))
        return false;

    const float d = (ev.mod & kModifierControl) ? 2000.0f : 200.0f;
    float value = (using_log_ ? _invlogscale(tmp_value_) : tmp_value_) + (float(max_value - min_value) / d * 10.f * ev.delta.getY());

    if (using_log_)
        value = _logscale(value);

    if (value < min_value)
    {
        tmp_value_ = value = min_value;
    }
    else if (value > max_value)
    {
        tmp_value_ = value = max_value;
    }
    setValue(value);
    if (callback)
        callback->onSliderValueChanged(this, value_);
    repaint();
    return true;
}

bool Slider::onMotion(const MotionEvent &ev)
{
    if (contains(ev.pos) && !has_mouse_)
    {
        has_mouse_ = true;
        repaint();
    }
    if (!contains(ev.pos) && !dragging_ && has_mouse_)
    {
        has_mouse_ = false;
        repaint();
    }
    if (!dragging_)
        return false;

    bool doVal = false;
    float d, value = 0.0f;

    if (const int movY = last_mouse_y_ - ev.pos.getY())
    {
        d = (ev.mod & kModifierControl) ? 2000.0f : 200.0f;
        value = tmp_value_ + (float(max_value - min_value) / d * float(movY));
        doVal = true;
    }

    if (!doVal)
        return false;
    if (value < min_value)
    {
        tmp_value_ = value = min_value;
    }
    else if (value > max_value)
    {
        tmp_value_ = value = max_value;
    }
    setValue(value);
    if (callback)
        callback->onSliderValueChanged(this, value_);
    last_mouse_x_ = ev.pos.getX();
    last_mouse_y_ = ev.pos.getY();

    repaint();
    return true;
}

void Slider::onNanoDisplay()
{
    const float height = getHeight();
    const float width = getWidth();
    // background
    beginPath();
    fillColor(background_color);
    rect(0, 0, width, height);
    fill();
    closePath();

    //Handle (value)

    if (has_mouse_)
    {
        fill_color_ = highlight_color;
    }
    else
    {
        fill_color_ = foreground_color;
    }
    float normalized_val = (value_ - min_value) / (max_value - min_value);
    const float slider_h = height * normalized_val;
    const float slider_y = height - slider_h;
    if (d_isNotZero(normalized_val))
    {
        //fillColor(fill_color_);
        fillColor(fill_color_);
        beginPath();
        rect(0, slider_y, width, height * normalized_val);
        fill();
        closePath();
    }
}

void Slider::setValue(float val) noexcept
{
    value_ = std::max(min_value, std::min(val, max_value));
    tmp_value_ = value_;
}

float Slider::_logscale(float value) const
{
    const float b = std::log(max_value / min_value) / (max_value - min_value);
    const float a = max_value / std::exp(max_value * b);
    return a * std::exp(b * value);
}

float Slider::_invlogscale(float value) const
{
    const float b = std::log(max_value / min_value) / (max_value - min_value);
    const float a = max_value / std::exp(max_value * b);
    return std::log(value / a) / b;
}

void Slider::setCallback(Callback *cb)
{
    callback = cb;
}

END_NAMESPACE_DISTRHO
