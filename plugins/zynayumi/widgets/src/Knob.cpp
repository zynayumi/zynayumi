/*
*/
#include "Knob.hpp"

START_NAMESPACE_DISTRHO

Knob::Knob(Window &parent) noexcept
    : NanoWidget(parent)
{
    parent.addIdleCallback(this);
    dragging_ = false;
    has_mouse_ = false;
    value_ = 0.f;
    tmp_value_ = 0.f;
    max = 1.0f;
    min = 0.0f;
    real_min = 0.0f;
    real_max = 1.0f;
    using_log = false;
    is_centered = false;
    margin = 4.0f;
    gauge_width = 8.0f;
    foreground_color = Color(1, 1, 1);
    background_color = Color(0, 0, 0);
    text_color = Color(1, 1, 1);
    fill_color_ = foreground_color;
    popUp = nullptr;
    format_str = "%.2f";
    is_counting_down_ = false;
    countdown_ = 30;
    step_value = 0.f;
    setParamOnMove = true;
    callback = nullptr;
}

Knob::Knob(Widget *parent) noexcept
    : NanoWidget(parent)
{
    //loadSharedResources();
    parent->getParentWindow().addIdleCallback(this);
    dragging_ = false;
    has_mouse_ = false;
    value_ = 0.f;
    tmp_value_ = 0.f;
    max = 1.0f;
    min = 0.0f;
    real_min = 0.0f;
    real_max = 1.0f;
    using_log = false;
    is_centered = false;
    margin = 4.0f;
    gauge_width = 8.0f;
    foreground_color = Color(1, 1, 1);
    background_color = Color(0, 0, 0);
    text_color = Color(1, 1, 1);
    fill_color_ = foreground_color;
    popUp = nullptr;
    format_str = "%.2f";
    is_counting_down_ = false;
    countdown_ = 30;
    step_value = 0.f;
    setParamOnMove = true;
    callback = nullptr;
}

float Knob::getValue() noexcept
{
    return value_;
}

bool Knob::onMouse(const MouseEvent &ev)
{
    if (!isVisible())
        return false;

    if (ev.button != 1)
        return false;

    if (ev.press)
    {
        if (!contains(ev.pos))
            return false;

        if ((ev.mod & kModifierShift) != 0 && using_default_)
        {
            setValue(default_value, true);
            tmp_value_ = value_;
            return false;
        }
        has_mouse_ = true;
        dragging_ = true;
        last_mouse_x_ = ev.pos.getX();
        last_mouse_y_ = ev.pos.getY();

        if (callback != nullptr)
        {
            callback->knobDragStarted(this);
        }
        if (popUp != nullptr)
        {
            int y = getAbsoluteY() + getHeight();
            popUp->setAbsoluteY(y);
            updatePopUp();
            popUp->show();
        }
        repaint();
        return false;
    }
    else if (dragging_)
    {
        if (!setParamOnMove)
        {
            float normValue = 0.0f;
            normValue = (value_ - min) / (max - min);
            if (d_isZero(step_value))
            {
                normValue = (value_ - min) / (max - min);
            }
            else
            {
                normValue = value_;
            }

            if (callback != nullptr)
                callback->knobDragFinished(this, normValue);
        }
        if (popUp != nullptr && !contains(ev.pos))
        {
            popUp->hide();
            is_counting_down_ = false;
        }
        dragging_ = false;
        repaint();
    }
    has_mouse_ = false;
    return false;
}

bool Knob::onScroll(const ScrollEvent &ev)
{
    if (!isVisible())
        return false;
    if (!contains(ev.pos))
        return false;

    const float d = (ev.mod & kModifierControl) ? 2000.0f : 200.0f;
    float value = (using_log ? _invlogscale(tmp_value_) : tmp_value_) + (float(max - min) / d * 10.f * ev.delta.getY());

    if (using_log)
        value = _logscale(value);

    if (value < min)
    {
        tmp_value_ = value = min;
    }
    else if (value > max)
    {
        tmp_value_ = value = max;
    }
    else if (d_isNotZero(step_value))
    {
        tmp_value_ = value;
        const float rest = std::fmod(value, step_value);
        value = value - rest + (rest > step_value / 2.0f ? step_value : 0.0f);
    }
    setValue(value, true);
    float normValue = (value_ - min) / (max - min);
    if (d_isZero(step_value))
    {
        if (callback)
            callback->knobDragFinished(this, normValue);
    }
    else
    {
        callback->knobDragFinished(this, value_);
    }

    return false;
}

bool Knob::onMotion(const MotionEvent &ev)
{
    if (!isVisible())
        return false;

    if (contains(ev.pos) && !has_mouse_)
        has_mouse_ = true;

    // if the popup is visible it is opened by another widget
    if (has_mouse_ && (popUp != nullptr) && (!popUp->isVisible()))
    {
        is_counting_down_ = true;
        countdown_ = 30;
    };

    if (!contains(ev.pos) && !dragging_)
    {
        has_mouse_ = false;
        if (is_counting_down_)
        {
            is_counting_down_ = false;
            if (popUp != nullptr)
                popUp->hide();
        }
    }
   // repaint();

    if (!dragging_)
    {
        return false;
    }

    float d, value = 0.0f;
    const int movY = last_mouse_y_ - ev.pos.getY();
    d = (ev.mod & kModifierControl) ? 2000.0f : 200.0f;
    value = (using_log ? _invlogscale(tmp_value_) : tmp_value_) + (float(max - min) / d * float(movY));

    if (using_log)
        value = _logscale(value);

    if (value < min)
    {
        tmp_value_ = value = min;
    }
    else if (value > max)
    {
        tmp_value_ = value = max;
    }
    else if (d_isNotZero(step_value))
    {
        tmp_value_ = value;
        const float rest = std::fmod(value, step_value);
        value = value - rest + (rest > step_value / 2.0f ? step_value : 0.0f);
    }

    setValue(value, setParamOnMove);

    last_mouse_x_ = ev.pos.getX();
    last_mouse_y_ = ev.pos.getY();

    return false;
}

void Knob::idleCallback()
{
    // are we in a countdown
    if (!is_counting_down_)
        return;

    // yes, start countdown
    countdown_--;
    // if < 0 show popUp
    if (countdown_ < 0)
    {
        int y = getAbsoluteY() + getHeight();
        popUp->setAbsoluteY(y);
        popUp->background_color = background_color;
        popUp->foreground_color = foreground_color;
        popUp->text_color = text_color;
        updatePopUp();
        popUp->show();
    }
}

void Knob::onNanoDisplay()
{
    const float height = getHeight();
    const float width = getWidth();
    // beginPath();
    // fillColor(128, 128, 128);
    // rect(0, 0, width, height);
    // fill();
    // closePath();

    float normValue = (((using_log ? _invlogscale(value_) : value_) - min) / (max - min));
    if (normValue < 0.0f)
        normValue = 0.0f;

    const float radius = (height - margin) * .5f;
    const float center_x = width * .5f;
    const float center_y = radius + margin * .5f;

    // circle
    beginPath();
    fillColor(background_color);
    circle(center_x, center_y, radius);
    fill();
    closePath();

    // arc
    beginPath();
    strokeColor(foreground_color);
    strokeWidth(margin);
    arc(center_x, center_y, radius, 0.75f * M_PI, 0.25f * M_PI, NanoVG::Winding::CW);
    stroke();
    closePath();

    // handle
    auto handleRadius = radius * .6f;
    auto handleWidth = 2.5f;
    auto radians = (0.75f + 1.5f * normValue) * M_PI;
    auto xHandle = handleRadius * cos(radians) + center_x;
    auto yHandle = handleRadius * sin(radians) + center_y;
    beginPath();
    circle(xHandle, yHandle, handleWidth);
    fillColor(foreground_color);
    fill();
    closePath();
    // beginPath();
    // strokeWidth(gauge_width);
    // if (has_mouse_)
    // {
    //     fill_color_ = highlight_color;
    // }
    // else
    // {
    //     fill_color_ = foreground_color;
    // }
    // strokeColor(fill_color_);
    // if (is_centered)
    // {
    //     //   const float stop_angle = normValue > 0.5f ? (0.75 + 1.5f * normValue) * M_PI : (0.75f + normValue) * M_PI;
    //     const NanoVG::Winding w = normValue > 0.5f ? NanoVG::Winding::CW : NanoVG::Winding::CCW;
    //     arc(center_x,
    //         center_y,
    //         radius - gauge_width / 2,
    //         1.5f * M_PI,
    //         (0.75f + 1.5f * normValue) * M_PI,
    //         w);
    // }
    // else
    // {
    // arc(center_x,
    //     center_y,
    //     radius - gauge_width / 2,
    //     0.75f * M_PI,
    //     (0.75f + 1.5f * normValue) * M_PI,
    //     NanoVG::Winding::CW);
    // }
    // stroke();
    // closePath();
    // if centered draw tickmark at top
    // if (is_centered)
    // {
    //     beginPath();
    //     arc(center_x, center_y,
    //         radius - gauge_width / 2,
    //         1.48f * M_PI,
    //         1.52f * M_PI,
    //         NanoVG::Winding::CW);
    //     stroke();
    //     closePath();
    // }
}

void Knob::setValue(float val, bool sendCallback) noexcept
{
    if (d_isEqual(value_, val))
        return;

    value_ = std::max(min, std::min(val, max));
    float normValue = 0.0f;
    tmp_value_ = value_;
    if (d_isZero(step_value))
    {
        normValue = (value_ - min) / (max - min);
    }
    else
    {
        normValue = value_;
    }

    if (popUp != nullptr)
        updatePopUp();

    if (sendCallback && callback != nullptr)
    {
        callback->knobValueChanged(this, normValue);
    }
}

float Knob::_logscale(float value) const
{
    const float b = std::log(max / min) / (max - min);
    const float a = max / std::exp(max * b);
    return a * std::exp(b * value);
}

float Knob::_invlogscale(float value) const
{
    const float b = std::log(max / min) / (max - min);
    const float a = max / std::exp(max * b);
    return std::log(value / a) / b;
}

void Knob::setCallback(Callback *cb)
{
    callback = cb;
}

void Knob::setPopUp(PopUp *p)
{
    popUp = p;
    popUp->background_color = background_color;
    popUp->foreground_color = foreground_color;
    popUp->text_color = text_color;
}

void Knob::updatePopUp()
{
    popUp->background_color = background_color;
    popUp->foreground_color = foreground_color;
    popUp->text_color = text_color;
    if (d_isZero(step_value))
    { // normalize val
        float val = (value_ - min) / (max - min);
        // multiply by real value
        val = fabs(real_min - real_max) * val + real_min;
        char val_str[36];
        sprintf(val_str, format_str, val);
        popUp->setText(val_str);
    }
    else
    {
        int index = value_; // todo: check out of bounds
        popUp->setText(stepText[index]);
    }
    popUp->resize();
    const int pop_x = getAbsoluteX() + getWidth() / 2 - popUp->getWidth() / 2;
    popUp->setAbsoluteX(pop_x);
}

void Knob::setStepText(std::initializer_list<const char *> strings)
{
    stepText.clear();
    stepText.insert(stepText.end(), strings.begin(), strings.end());
}

// void Knob::setFont(const char *name)
// {
//     font_id = findFont("RobotoCondensed");

//     printf("font_id=%i\n", font_id);
// }

END_NAMESPACE_DISTRHO