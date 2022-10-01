#include "SeqSpinner.hpp"

START_NAMESPACE_DISTRHO

SeqSpinner::SeqSpinner(Window &parent) noexcept
    : NanoWidget(parent)
{
    font_size = 12;
    has_mouse_ = false;
    spinner_font_ = 0;
    item_ = 0;
    callback = nullptr;
}

SeqSpinner::SeqSpinner(Widget *widget) noexcept
    : NanoWidget(widget)
{
    font_size = 12;
    has_mouse_ = false;
    spinner_font_ = 0;
    item_ = 0;
    callback = nullptr;
}

bool SeqSpinner::onMouse(const MouseEvent &ev)
{
    return false;
}

bool SeqSpinner::onMotion(const MotionEvent &ev)
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

bool SeqSpinner::onScroll(const ScrollEvent &ev)
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
        callback->onSeqSpinnerValueChanged(this, item_);
    repaint();
    return true;
}

void SeqSpinner::onNanoDisplay()
{
    int width = getWidth();
    int height = getHeight();

    fontFaceId(spinner_font_);
    fontSize(font_size);
    // back
    // beginPath();
    // fillColor(1.f, 0.f, 0.f, .5f);
    // rect(0, 0, width, height);
    // fill();
    // closePath();

    // triangles
    // up arrow
    // left
    const auto lx = width - 10;
    auto ly = 5;
    // center
    const auto cx = width - 5;
    auto cy = 0;
    // right
    const auto rx = width;
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
    cy = height;
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
    const float text_center_x = (width - 10) * .5f;
    const float text_center_y = height * .5f - 1.f;
    const char *str = items_[item_].c_str();
    text(text_center_x, text_center_y, str, nullptr);
    closePath();
}

void SeqSpinner::addItems(std::initializer_list<int> item_list)
{
    items_.clear();
    for (auto &&i : item_list)
        items_.push_back(std::to_string(i));
}

void SeqSpinner::addItems(std::initializer_list<float> item_list)
{
    items_.clear();
    for (auto &&i : item_list)
        items_.push_back(std::to_string(i));
}

void SeqSpinner::addItems(std::initializer_list<std::string> item_list)
{
    items_.clear();
    for (auto &&i : item_list)
        items_.push_back(i);
}

void SeqSpinner::setFont(const char *fontName, const uchar *data, uint dataSize)
{
    spinner_font_ = createFontFromMemory(fontName, data, dataSize, false);
}

void SeqSpinner::setValue(int index, bool doCallback)
{
    item_ = index;
    if (doCallback && (callback != nullptr))
        callback->onSeqSpinnerValueChanged(this, item_);
}

END_NAMESPACE_DISTRHO
