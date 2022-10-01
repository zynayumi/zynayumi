#include "EG.hpp"

START_NAMESPACE_DISTRHO

EG::EG(Window &parent) noexcept
    : NanoWidget(parent)
{
    background_color = Color(0.8f, 0.8f, 0.8f);
    foreground_color = Color(0.1f, 0.1f, 0.1f);
}

EG::EG(Widget *widget) noexcept
    : NanoWidget(widget)
{
    background_color = Color(0.8f, 0.8f, 0.8f);
    foreground_color = Color(0.1f, 0.1f, 0.1f);
}

void EG::onNanoDisplay()
{
    const int width = getWidth();
    const int height = getHeight();
    const float stroke_width = 3.f;
    // max time width
    const float stroke_margin = stroke_width * .5f;
    float max_time_width = ((width - stroke_width) / 5.f) / 10.f; // 5 time values: atk,t1,t2,decay,rel
    float eg_height = (height - stroke_width) / 15.f;

    // start, bottom left
    const float x_atk = stroke_margin;
    const float y_atk = height - stroke_margin;
    // attack time, L1
    const float x_l1 = env_attack_time * max_time_width;
    const float y_l1 = height - stroke_margin - eg_height * env_hold1_level;
    // time1 , L2
    const float x_l2 = x_l1 + (env_inter1_time * max_time_width);
    const float y_l2 = height - stroke_margin - eg_height * env_hold2_level;
    // time2, L3
    const float x_l3 = x_l2 + (env_inter2_time * max_time_width);
    const float y_l3 = height - stroke_margin - (eg_height * env_hold3_level);
    // decay, sus
    const float x_sus = x_l3 + (env_decay_time * max_time_width);
    const float y_sus = height - stroke_margin - eg_height * env_sustain_level;
    // release time, 0
    const float x_release = x_sus + (env_release * max_time_width);
    const float y_release = height - stroke_margin;

    // gradient
    const Paint bg = linearGradient(width / 2, 0,
                                    width / 2, height,
                                    background_color, Color(0.f, 0.f, 0.f, 0.f));
    pathWinding(Winding::CCW);
    beginPath();
    moveTo(x_atk, y_atk);
    lineTo(x_l1, y_l1);
    lineTo(x_l2, y_l2);
    lineTo(x_l3, y_l3);
    lineTo(x_sus, y_sus);
    lineTo(x_release, y_release);
    lineTo(x_atk, y_atk);
    fillPaint(bg);
    fill();
    closePath();

    strokeWidth(stroke_width);
    lineCap(LineCap::ROUND);
    strokeColor(foreground_color);
    beginPath();
    moveTo(x_atk, y_atk);
    lineTo(x_l1, y_l1);
    lineTo(x_l2, y_l2);
    lineTo(x_l3, y_l3);
    lineTo(x_sus, y_sus);
    lineTo(x_release, y_release);
    stroke();
    closePath();
}

END_NAMESPACE_DISTRHO
