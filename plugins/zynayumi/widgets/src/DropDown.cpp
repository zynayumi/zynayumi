#include "DropDown.hpp"

START_NAMESPACE_DISTRHO

DropDown::DropDown(Window &parent) noexcept
    : NanoWidget(parent)
{
    item = "item";
    font_size = 14.f;
    parent.addIdleCallback(this);
    has_mouse_ = false;
    background_color = Color(0.0f, 0.0f, 0.0f);
    foreground_color = Color(0.5f, 0.5f, 0.5f);
    highlight_color = Color(0.3f, 0.3f, 0.3f);
    text_color = Color(1.0f, 1.0f, 1.0f);
    callback_ = nullptr;
}
DropDown::DropDown(Widget *widget) noexcept
    : NanoWidget(widget)
{
    item = "item";
    font_size = 14.f;
    widget->getParentWindow().addIdleCallback(this);
    has_mouse_ = false;
    background_color = Color(0.0f, 0.0f, 0.0f);
    foreground_color = Color(0.5f, 0.5f, 0.5f);
    highlight_color = Color(0.3f, 0.3f, 0.3f);
    text_color = Color(1.0f, 1.0f, 1.0f);
    callback_ = nullptr;
}

bool DropDown::onMouse(const MouseEvent &ev)
{
    if (!isVisible())
        return false;
    
    if (contains(ev.pos) && ev.press && ev.button == 1)
    {
        if (callback_)
            callback_->onDropDownClicked(this);
        return false;
    }
    else
    {
        return false;
    }
}

bool DropDown::onMotion(const MotionEvent &ev)
{
    if (!isVisible())
        return false;

    if (contains(ev.pos))
        has_mouse_ = true;
    else
        has_mouse_ = false;

    return false;
}

void DropDown::idleCallback()
{
    if (!menu_)
        return;
    if (has_mouse_)
    {
        menu_->timer = menu_->time_out;
        menu_->dropdown_has_mouse = true;
    }
    else
    {
        menu_->dropdown_has_mouse = false;
    }
}

void DropDown::onNanoDisplay()
{
    int width = getWidth();
    int height = getHeight();

    // black border
    beginPath();
    fillColor(background_color);
    rect(0, 0, width, height);
    fill();
    stroke();
    closePath();

    // down arrow
    // left
    const auto lx = width - 11;
    const auto ly = 4;
    // center
    const auto cx = width - 6;
    auto cy = 11;
    // right
    const auto rx = width - 3;
    const auto ry = ly;
    beginPath();
    fillColor(foreground_color);
    moveTo(lx, ly);
    lineTo(cx, cy);
    lineTo(rx, ry);
    lineTo(lx, ly);
    fill();
    closePath();

    // text
    fillColor(text_color);
    beginPath();
    fontFaceId(font_);
    fontSize(font_size);
    textAlign(ALIGN_LEFT | ALIGN_TOP);

    text(2, height - font_size, item.c_str(), nullptr);
    closePath();
}

void DropDown::setCallback(Callback *cb)
{
    callback_ = cb;
}

void DropDown::setValue(float val)
{
    uint index = static_cast<uint>(val);
    item = menu_->getItem(index);
    repaint();
}

void DropDown::setMenu(std::shared_ptr<Menu> menu)
{
    menu_ = menu;
}

void DropDown::setFont(const char *fontName, const uchar *data, uint dataSize)
{
    font_ = createFontFromMemory(fontName, data, dataSize, false);
}

END_NAMESPACE_DISTRHO
