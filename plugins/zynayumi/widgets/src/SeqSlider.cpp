#include "SeqSlider.hpp"

START_NAMESPACE_DISTRHO

SeqSlider::SeqSlider(Window &parent) noexcept
    : NanoWidget(parent)
{
    dragging_ = false;
    has_mouse_ = false;
    value_ = 0;
    tmp_value_ = 0;
    max_value = 16.0f;
    min_value = 0.0f;
    foreground_color = Color(1, 1, 1);
    background_color = Color(0, 0, 0);
    fill_color_ = foreground_color;
    callback = nullptr;
    step = 28;
    left_right = true;
    striped = false;
}

SeqSlider::SeqSlider(Widget *widget) noexcept
    : NanoWidget(widget)
{
    dragging_ = false;
    has_mouse_ = false;
    value_ = 0;
    tmp_value_ = 0;
    max_value = 16;
    min_value = 0;
    foreground_color = Color(1, 1, 1);
    background_color = Color(0, 0, 0);
    fill_color_ = foreground_color;
    callback = nullptr;
    left_right = true;
    striped = false;
    step = 28;
}

int SeqSlider::getValue() noexcept
{
    return value_;
}
bool SeqSlider::onMouse(const MouseEvent &ev)
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

bool SeqSlider::onScroll(const ScrollEvent &ev)
{
    if (!isVisible())
        return false;
    if (!contains(ev.pos))
        return false;
    const int delta = static_cast<int>(ev.delta.getY());

    int value = tmp_value_ + delta;
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
        callback->onSeqSliderValueChanged(this, value_);
    repaint();
    return true;
}

bool SeqSlider::onMotion(const MotionEvent &ev)
{
    // if (contains(ev.pos) && !has_mouse_)
    // {
    //     has_mouse_ = true;
    //     repaint();
    // }
    //     if (!contains(ev.pos) && !dragging_ && has_mouse_)
    //     {
    //         has_mouse_ = false;
    //      repaint();
    //     }
    if (!contains(ev.pos))
        return false;
    if (!dragging_)
        return false;
    const int y = ev.pos.getY();
    int value = y / step;

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
        callback->onSeqSliderValueChanged(this, value_);

    repaint();
    return false;
}

void SeqSlider::onNanoDisplay()
{
    const int height = getHeight();
    const int width = getWidth();
    const int handleY = value_ * step;
    // debug
    // beginPath();
    // fillColor(255, 0, 0);
    // rect(0, 0, width, height);
    // fill();
    // closePath();

    // background

    if (left_right == true) // left hand , point to right
    {
        fillColor(background_color);
        beginPath();
        moveTo(0, 0);
        lineTo(width, 10);
        lineTo(width, handleY + 10);
        lineTo(0, handleY);
        lineTo(0, 0);
        fill();
        closePath();
        // handle
        fillColor(foreground_color);
        beginPath();
        moveTo(0, handleY);
        lineTo(width, handleY + 10);
        lineTo(0, handleY + 20);
        lineTo(0, handleY);
        fill();
        closePath();
    }
    else
    {
        fillColor(background_color);
        for (int y = 0; y < handleY; y += 8)
        {
            beginPath();
            moveTo(width, y);
            lineTo(width, y + 3);
            lineTo(0, y + 13);
            lineTo(0, y + 10);
            lineTo(width, y);
            fill();
            closePath();
        }
        // handle
        fillColor(foreground_color);
        beginPath();
        moveTo(width, handleY);
        lineTo(0, handleY + 10);
        lineTo(width, handleY + 20);
        lineTo(width, handleY);
        fill();
        closePath();
    }
}

void SeqSlider::setValue(int val) noexcept
{
    value_ = std::max(min_value, std::min(val, max_value));
    tmp_value_ = value_;
}

void SeqSlider::setCallback(Callback *cb)
{
    callback = cb;
}

END_NAMESPACE_DISTRHO
