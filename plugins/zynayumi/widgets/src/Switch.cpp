
#include "Switch.hpp"

START_NAMESPACE_DISTRHO

Switch::Switch(Window &parent) noexcept
    : NanoWidget(parent)
{
    background_color = Color(0.8f, 0.8f, 0.8f);
    foreground_color = Color(0.1f, 0.1f, 0.1f);
}

Switch::Switch(Widget *widget) noexcept
    : NanoWidget(widget)
{
    background_color = Color(0.8f, 0.8f, 0.8f);
    foreground_color = Color(0.1f, 0.1f, 0.1f);
}

bool Switch::onMouse(const MouseEvent &ev)
{
    if (contains(ev.pos) && ev.press && ev.button == 1)
    {
        left_right = !left_right;
        callback->onSwitchClicked(this, left_right);
        repaint();
        return true;
    }
    else
    {
        return false;
    }
}
bool Switch::onMotion(const MotionEvent &ev)
{
    // TODO: maybe implement drag ?
    return false;
}

void Switch::onNanoDisplay()
{
    const int width = getWidth();
    const int height = getHeight();

    const float f = .5f;
    float r = height * f;
    // white border
    beginPath();
    fillColor(255, 255, 255);
    roundedRect(0, 0, width, height, r);
    fill();
    closePath();
    // black center
    beginPath();
    fillColor(0, 0, 0);
    roundedRect(2, 2, width - 4, height - 4, (height - 4) * f);
    fill();
    closePath();
    // switch
    r = height * .25f;
    const int x = left_right ? 4 + r : width - 3 - r;
    const int y = height * .5f;
    beginPath();
    fillColor(foreground_color);
    circle(x, y, r);
    fill();
    closePath();
}

void Switch::setCallback(Callback *cb)
{
    callback = cb;
}

END_NAMESPACE_DISTRHO
