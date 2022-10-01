#include "Spinner.hpp"

START_NAMESPACE_DISTRHO

Spinner::Spinner(Window &parent) noexcept
    : NanoWidget(parent)
{
    font_size = 12;
    has_mouse_ = false;
    spinner_font_ = 0;
    item_ = 0;
    callback = nullptr;
}

Spinner::Spinner(Widget *widget) noexcept
    : NanoWidget(widget)
{
    font_size = 12;
    has_mouse_ = false;
    spinner_font_ = 0;
    item_ = 0;
    callback = nullptr;
}

bool Spinner::onMouse(const MouseEvent &ev)
{
    return false;
}

bool Spinner::onMotion(const MotionEvent &ev)
{
    if (!isVisible())
        return false;
    if (contains(ev.pos))
    {
        has_mouse_ = true;
        const int mouse_y = ev.pos.getY();
        repaint();
        return true;
    }
    else
    {
        has_mouse_ = false;
        return false;
    }
    return true;
}

bool Spinner::onScroll(const ScrollEvent &ev)
{
    if (!contains(ev.pos))
        return false;
    const int delta = static_cast<int>(ev.delta.getY());

    item_ += delta;
    if (item_ < 0)
        item_ = 0;
    if (item_ > items_.size() - 1)
        item_ = items_.size() - 1;
    
    if (callback)
        callback->onSpinnerValueChanged(this, item_);
    repaint();
    return true;
}

void Spinner::onNanoDisplay()
{
    int width = getWidth();
    int height = getHeight();

    fontFaceId(spinner_font_);
    fontSize(font_size);
    // back
    beginPath();
    fillColor(background_color);
    rect(0, 0, width, height);
    fill();
    closePath();

     // triangles
    // up arrow
    // left
    const auto lx = width - 9;
    auto ly = 6;
    // center
    const auto cx = width - 6;
    auto cy = 2;
    // right
    const auto rx = width - 3;
    auto ry = ly;
    beginPath();
    fillColor(foreground_color);
    moveTo(lx, ly);
    lineTo(cx, cy);
    lineTo(rx, ry);
    lineTo(lx, ly);
    fill();
    closePath();
    // down arrow
    // only y values need changing
    ly = ry = height - 5;
    cy = height - 1;
    beginPath();
    moveTo(lx, ly);
    lineTo(cx, cy);
    lineTo(rx, ry);
    lineTo(lx, ly);
    fill();
    closePath();

    // item
    beginPath();
    fillColor(text_color);
    textAlign(ALIGN_CENTER | ALIGN_MIDDLE);
    // center of text area
    const float text_center_x = (width - 13) / 2 + 1;
    const float text_center_y = (height - 1) / 2 + 1;
    const char *str = items_[item_].c_str();
    text(text_center_x, text_center_y, str, nullptr);
    closePath();
}

void Spinner::addItems(std::initializer_list<int> item_list)
{
    items_.clear();
    for (auto &&i : item_list)
        items_.push_back(std::to_string(i));
}

void Spinner::addItems(std::initializer_list<float> item_list)
{
    items_.clear();
    for (auto &&i : item_list)
        items_.push_back(std::to_string(i));
}

void Spinner::addItems(std::initializer_list<std::string> item_list)
{
    items_.clear();
    for (auto &&i : item_list)
        items_.push_back(i);
}

void Spinner::setFont(const char *fontName, const uchar *data, uint dataSize)
{
    spinner_font_ = createFontFromMemory(fontName, data, dataSize, false);
}

void Spinner::setValue(int index, bool doCallback)
{
    item_ = index;
    if (doCallback && (callback != nullptr))
        callback->onSpinnerValueChanged(this, item_);
}


END_NAMESPACE_DISTRHO
