#ifndef SEQ_SPINNER_HPP
#define SEQ_SPINNER_HPP

#include "Window.hpp"
#include "Widget.hpp"
#include "NanoVG.hpp"
#include <string>
#include <sstream>
#include <initializer_list>
#include <ostream>

START_NAMESPACE_DISTRHO

class SeqSpinner : public NanoWidget
{
public:
  class Callback
  {
  public:
    virtual ~Callback() {}
    virtual void onSeqSpinnerValueChanged(SeqSpinner *sp, uint value) = 0;
  };
  //  virtual void onSeqSpinnerValueChanged(SeqSpinner *SeqSpinner, uint index, std::string item) = 0;

  explicit SeqSpinner(Window &parent) noexcept;
  explicit SeqSpinner(Widget *widget) noexcept;

  void addItems(std::initializer_list<std::string> items);
  void addItems(std::initializer_list<int> items);
  void addItems(std::initializer_list<float> items);
  template <typename T>
  void addItems(T lo, T hi, T step)
  {
    items_.clear();
    T i = lo;
    while (i <= hi)
    {
      items_.push_back(std::to_string(i));
      i += step;
    }
  }

  void setFont(const char *name, const uchar *data, uint dataSize);
  void setValue(int index, bool doCallback = false);

  float font_size;
  Color background_color;
  Color foreground_color;
  Color highlight_color;
  Color text_color;
  Callback *callback;

protected:
  void onNanoDisplay() override;
  bool onMouse(const MouseEvent &) override;
  bool onMotion(const MotionEvent &) override;
  bool onScroll(const ScrollEvent &) override;

private:
  std::vector<std::string> items_;
  int item_;

  bool has_mouse_;
  FontId spinner_font_;

  DISTRHO_LEAK_DETECTOR(SeqSpinner)
};

END_NAMESPACE_DISTRHO

#endif
