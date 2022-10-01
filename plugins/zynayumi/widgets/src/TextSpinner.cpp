#include "TextSpinner.hpp"

START_NAMESPACE_DISTRHO

TextSpinner::TextSpinner(Window &parent) noexcept
    : NanoWidget(parent)
{
    callback = nullptr;
    min = -48;
    max = 48;
    value = 0;
}

TextSpinner::TextSpinner(Widget *widget) noexcept
    : NanoWidget(widget)
{
    callback = nullptr;
    min = -48;
    max = 48;
    value = 0;
}

void TextSpinner::onNanoDisplay()
{
    // beginPath();
    // fillColor(255, 0, 0);
    // rect(0, 0, getWidth(), getHeight());
    // fill();
    // closePath();
}

// bool TextSpinner::onMouse(const MouseEvent &ev)
// {
//     return false;
// }

// bool TextSpinner::onMotion(const MotionEvent &ev)
// {
//     return false;
// }

bool TextSpinner::onScroll(const ScrollEvent &ev)
{
    if (!contains(ev.pos))
        return false;
    const int delta = static_cast<int>(ev.delta.getY());

    value += delta;
    value = std::min(max, std::max(value, min));
    if (callback)
        callback->onTextSpinnerValueChanged(this, value);
    return true;
}

END_NAMESPACE_DISTRHO
