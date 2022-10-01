

#ifndef EG_HPP
#define EG_HPP

#include "Window.hpp"
#include "Widget.hpp"
#include "NanoVG.hpp"

START_NAMESPACE_DISTRHO

class EG : public NanoWidget
{
public:
  explicit EG(Window &parent) noexcept;
  explicit EG(Widget *widget) noexcept;

  Color background_color;
  Color foreground_color;
  Color highlight_color;  
  
  float  env_attack_time;
  float  env_hold1_level;
  float  env_inter1_time;
  float  env_hold2_level;
  float  env_inter2_time;
  float  env_hold3_level;
  float  env_decay_time;
  float  env_sustain_level;
  float  env_release;

protected:
  void onNanoDisplay() override;


private:
  Color fill_color_;

  DISTRHO_LEAK_DETECTOR(EG)
};

END_NAMESPACE_DISTRHO

#endif 
