/*
    Drops - Drops Really Only Plays Samples
    Copyright (C) 2021  Rob van den Berg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include "CheckBox.hpp"

START_NAMESPACE_DISTRHO

CheckBox::CheckBox(Window &parent) noexcept
    : NanoWidget(parent)
{
    active_color = Color(0.8f, 0.8f, 0.8f);
    highlight_color = Color(1.0f, 0.5f, 0.5f);
    border_color = Color(1.f, 1.f, 1.f);
    has_mouse_ = false;
    isActive = false;
    callback = nullptr;
}

CheckBox::CheckBox(Widget *widget) noexcept
    : NanoWidget(widget)
{
    active_color = Color(0.8f, 0.8f, 0.8f);
    highlight_color = Color(1.0f, 0.5f, 0.5f);
    border_color = Color(1.f, 1.f, 1.f);
    has_mouse_ = false;
    isActive = false;
    callback = nullptr;
}

bool CheckBox::onMouse(const MouseEvent &ev)
{
    if (contains(ev.pos) && ev.press && ev.button == 1)
    {
        isActive = !isActive;
        if (callback)
            callback->onCheckBoxClicked(this, isActive);

        repaint();
    }
    return false;
}
bool CheckBox::onMotion(const MotionEvent &ev)
{
    if (contains(ev.pos) && !has_mouse_)
    {
        has_mouse_ = true;
    }
    repaint();

    if (!contains(ev.pos) && has_mouse_)
    {
        has_mouse_ = false;
        repaint();
    }
    return false;
}

void CheckBox::onNanoDisplay()
{
    float width = getWidth();
    float height = getHeight();
    const float cx = width / 2.f;
    const float cy = height / 2.f;
    float radius = cx;
 
    if (has_mouse_)
    {
        fill_color_ = highlight_color;
    }
    else if (isActive)
    {
        fill_color_ = active_color;
    }
    else
    {
        fill_color_ = Color(0, 0, 0);
    }

    // border border
    beginPath();
    fillColor(border_color);
    circle(cx, cy, radius);
    fill();
    closePath();
    // black border
    beginPath();
    fillColor(0.0f, 0.0f, 0.0f);
    circle(cx, cy, radius - 2);
    fill();
    closePath();
    // active circle
    beginPath();
    fillColor(fill_color_);
    circle(cx, cy, radius - 4);
    fill();
    closePath();
}

END_NAMESPACE_DISTRHO
