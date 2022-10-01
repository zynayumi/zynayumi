#include "Waveform.hpp"

START_NAMESPACE_DISTRHO

Waveform::Waveform(Window &parent) noexcept
    : NanoWidget(parent)
{
    left_button_ = false;
    value_ = 0;
    tmp_value_ = 0;
    max_value = 15;
    min_value = 0;

    foreground_color = Color(255, 255, 255);
    background_color = Color(0, 0, 0);
    fill_color_ = foreground_color;
    callback = nullptr;
}

Waveform::Waveform(Widget *widget) noexcept
    : NanoWidget(widget)
{

    left_button_ = false;
    value_ = 0;
    tmp_value_ = 0;
    max_value = 15;
    min_value = 0;

    foreground_color = Color(255, 255, 255);
    background_color = Color(0, 0, 0);
    fill_color_ = foreground_color;
    callback = nullptr;
}

int Waveform::getValue() noexcept
{
    return value_;
}
bool Waveform::onMouse(const MouseEvent &ev)
{
    if (ev.press && ev.button == 1)
    {
        left_button_ = true;
        if (contains(ev.pos))
        {
            tmp_value_ = value_;
            const int mouse_y = getHeight() - ev.pos.getY() + 1;
            const float norm_val = (float)mouse_y / (float)getHeight();
            const int val = norm_val * 15.f + .5f;
            if (val != tmp_value_)
            {
                setValue(val);
                if (callback)
                    callback->onWaveformValueChanged(this, value_);
                repaint();
            }
        }
    }
    else
        left_button_ = false;

    return false;
}

bool Waveform::onScroll(const ScrollEvent &ev)
{
    if (!contains(ev.pos))
        return false;
    int value = value_ + ev.delta.getY();

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
        callback->onWaveformValueChanged(this, value_);
    repaint();
    return true;
}

bool Waveform::onMotion(const MotionEvent &ev)
{
    if (contains(ev.pos) && left_button_)
    {
        tmp_value_ = value_;
        const float mouse_y = getHeight() - ev.pos.getY() + 1;
        const float norm_val = mouse_y / static_cast<float>(getHeight());
        const int val = norm_val * 15.f + .5f;
        if (val != tmp_value_)
        {
            setValue(val);
            if (callback)
                callback->onWaveformValueChanged(this, value_);
            repaint();
        }
    }
    return false;
}

void Waveform::onNanoDisplay()
{
    const float height = getHeight();
    const float width = getWidth();

    // draw back
    for (int i = 0; i < 16; i++)
    {
        int y = height - (i * 5);
        beginPath();
        fillColor(background_color);
        rect(0, y - 4, width, 4);
        fill();
        closePath();
    }

    fillColor(foreground_color);
    for (int i = 0; i < value_ + 1; i++)
    {
        beginPath();
        rect(0, height - (i * 5) - 4, width, 4);
        fill();
        closePath();
    }
}

void Waveform::setValue(int val) noexcept
{
    value_ = std::max(min_value, std::min(val, max_value));
    tmp_value_ = value_;
}

void Waveform::setCallback(Callback *cb)
{
    callback = cb;
}

END_NAMESPACE_DISTRHO
