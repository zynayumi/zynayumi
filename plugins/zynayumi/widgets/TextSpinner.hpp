/* TODO Let the parentwindow do the drawing  */

#ifndef TEXT_SPINNER_HPP
#define TEXT_SPINNER_HPP

#include "Widget.hpp"
#include "NanoVG.hpp"

START_NAMESPACE_DISTRHO

class TextSpinner : public NanoWidget
{
public:
  class Callback
  {
  public:
    virtual ~Callback() {}
    virtual void onTextSpinnerValueChanged(TextSpinner *sp, int value) = 0;
  };
  //  virtual void onTextSpinnerValueChanged(TextSpinner *TextSpinner, uint index, std::string item) = 0;

  explicit TextSpinner(Window &parent) noexcept;
  explicit TextSpinner(Widget *widget) noexcept;

  int min;
  int max;
  int value;
  Callback *callback;

  // void setValue(int index, bool doCallback);

protected:
  // bool onMouse(const MouseEvent &) override;
  // bool onMotion(const MotionEvent &) override;
  bool onScroll(const ScrollEvent &) override;
  void onNanoDisplay() override;

private:
  DISTRHO_LEAK_DETECTOR(TextSpinner)
};

END_NAMESPACE_DISTRHO

#endif
