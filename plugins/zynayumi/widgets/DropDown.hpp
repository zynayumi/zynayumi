
#ifndef DROP_DOWN_HPP
#define DROP_DOWN_HPP

#include "Window.hpp"
#include "Widget.hpp"
#include "NanoVG.hpp"
#include "Menu.hpp"
#include <string>
#include <memory>

START_NAMESPACE_DISTRHO

class DropDown : public NanoWidget,
                 public IdleCallback
{
public:
  class Callback
  {
  public:
    virtual ~Callback() {}
    virtual void onDropDownClicked(DropDown *dropDown) = 0;
  };
  explicit DropDown(Window &parent) noexcept;
  explicit DropDown(Widget *widget) noexcept;
  void setValue(float value);

  void setCallback(Callback *cb);
  void setMenu(std::shared_ptr<Menu> menu);
  void setFont(const char *name, const uchar *data, uint dataSize);
  void idleCallback() override;
  std::string item;
  float font_size;
  Color background_color, foreground_color, highlight_color, text_color;

protected:
  void onNanoDisplay() override;
  bool onMouse(const MouseEvent &) override;
  bool onMotion(const MotionEvent &) override;
  // todo :: add scrollwheel support

private:
  Callback *callback_;
  bool has_mouse_;
  std::shared_ptr<Menu> menu_;

  FontId font_;

  DISTRHO_LEAK_DETECTOR(DropDown)
};

END_NAMESPACE_DISTRHO

#endif // TEXT_BUTTON_HPP
