

#ifndef SWITCH_HPP
#define SWITCH_HPP

#include "Widget.hpp"
#include "NanoVG.hpp"

START_NAMESPACE_DISTRHO

class Switch : public NanoWidget
{
public:
  class Callback
  {
  public:
    virtual ~Callback() {}
    virtual void onSwitchClicked(Switch *, bool lr) = 0;
  };
  explicit Switch(Window &parent) noexcept;
  explicit Switch(Widget *widget) noexcept;
  void setCallback(Callback *cb);
  Color background_color;
  Color foreground_color;
  Color highlight_color;
  bool left_right;

protected:
  void onNanoDisplay() override;
  bool onMouse(const MouseEvent &) override;
  bool onMotion(const MotionEvent &) override;

private:
  Callback *callback;

  DISTRHO_LEAK_DETECTOR(Switch)
};

END_NAMESPACE_DISTRHO

#endif // TEXT_BUTTON_HPP
