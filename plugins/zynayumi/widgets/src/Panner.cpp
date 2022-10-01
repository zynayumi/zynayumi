#include "Panner.hpp"

START_NAMESPACE_DISTRHO

Panner::Panner(Window &parent) noexcept
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
    handle_.setPos(0, 0);
    handle_.setSize(5, 10); // TODO: magic numbers
}

Panner::Panner(Widget *widget) noexcept
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

float Panner::getValue() noexcept
{
    return value_;
}
bool Panner::onMouse(const MouseEvent &ev)
{
    const bool containsMouse = handle_.contains(ev.pos);
    if (ev.press == 1 && containsMouse)
    {
        has_mouse_ = true;
        dragging_ = true;
        last_mouse_x_ = ev.pos.getX();
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

bool Panner::onScroll(const ScrollEvent &ev)
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
        callback->onPannerValueChanged(this, value_);
    repaint();
    return true;
}

bool Panner::onMotion(const MotionEvent &ev)
{
    if (handle_.contains(ev.pos) && !has_mouse_)
    {
        has_mouse_ = true;
        repaint();
    }
    if (!handle_.contains(ev.pos) && !dragging_ && has_mouse_)
    {
        has_mouse_ = false;
        repaint();
    }
    if (!dragging_)
        return false;
    const int x = ev.pos.getX();
    float vper;
    vper = float(x - panner_area_.getX()) / float(panner_area_.getWidth());
    float value;
    value = min_value + vper * (max_value - min_value);
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
        callback->onPannerValueChanged(this, value_);
    last_mouse_x_ = ev.pos.getX();
    repaint();
    return true;
}

void Panner::onNanoDisplay()
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
    const float normalized_val = (value_ - min_value) / (max_value - min_value);
    const float normalized_X = panner_area_.getWidth() * normalized_val;
    const float hw = handle_.getWidth();
    handle_.setX(panner_area_.getX() + normalized_X);
    const float hx = handle_.getX();
    const float hy = handle_.getY();
    const float hh = handle_.getHeight();
    fillColor(fill_color_);
    beginPath();
    rect(hx, hy, hw, hh);
    fill();
    closePath();
}

void Panner::setValue(float val) noexcept
{
    value_ = std::max(min_value, std::min(val, max_value));
    tmp_value_ = value_;
}

void Panner::setHandle(const Size<int> &sz)
{
    handle_.setSize(sz);
    const int w = static_cast<float>(getWidth()) - sz.getWidth();
    const int h = static_cast<float>(getHeight());
    panner_area_.setSize(w, h);
    panner_area_.setPos(0, 0);
}

float Panner::_logscale(float value) const
{
    const float b = std::log(max_value / min_value) / (max_value - min_value);
    const float a = max_value / std::exp(max_value * b);
    return a * std::exp(b * value);
}

float Panner::_invlogscale(float value) const
{
    const float b = std::log(max_value / min_value) / (max_value - min_value);
    const float a = max_value / std::exp(max_value * b);
    return std::log(value / a) / b;
}

void Panner::setCallback(Callback *cb)
{
    callback = cb;
}

END_NAMESPACE_DISTRHO
