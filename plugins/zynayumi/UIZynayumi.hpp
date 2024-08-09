

#ifndef UI_HPP_INCLUDED
#define UI_HPP_INCLUDED

// #include "nanosvg.h"
// #include "nanosvgrast.h"

#include "Artwork.hpp"
#include "DistrhoUI.hpp"
#include "NanoVG.hpp"
#include "Window.hpp"
#include "data.hpp"
#include <fmt/color.h>
#include <fmt/core.h>
#include <memory>
#include <vector>

// #include "TextButton.hpp"
#include "CheckBox.hpp"
#include "DropDown.hpp"
#include "EG.hpp"
#include "Fonts.hpp"
#include "Knob.hpp"
#include "Menu.hpp"
#include "Panner.hpp"
#include "PopUp.hpp"
// #include "SVGImage.hpp"
#include "SeqSlider.hpp"
#include "SeqSpinner.hpp"
#include "Slider.hpp"
#include "Spinner.hpp"
#include "Switch.hpp"
#include "TextSpinner.hpp"
#include "Waveform.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------------------------------------------
class UIZynayumi : public UI,
                   public Knob::Callback,
                   public DropDown::Callback,
                   public Menu::Callback,
                   public Slider::Callback,
                   public CheckBox::Callback,
                   public Panner::Callback,
                   public Spinner::Callback,
                   public Waveform::Callback,
                   public Switch::Callback,
                   public TextSpinner::Callback,
                   public SeqSpinner::Callback,
                   public SeqSlider::Callback {
public:
  UIZynayumi();

protected:
  void parameterChanged(uint32_t index, float value) override;
  void onNanoDisplay() override;

  bool onMouse(const MouseEvent &ev) override;
  bool onScroll(const ScrollEvent &) override;
  bool onMotion(const MotionEvent &) override;
  void programLoaded(uint32_t index);
  void onDropDownClicked(DropDown *dropdown) override;
  void knobDragStarted(Knob *knob) override;
  void knobDragFinished(Knob *knob, float value) override;
  void knobValueChanged(Knob *knob, float value) override;
  void onSliderValueChanged(Slider *slider, float value) override;
  void onMenuClicked(Menu *menu, uint id, std::string item);
  void onCheckBoxClicked(CheckBox *checkbox, bool is_checked);
  void onPannerValueChanged(Panner *panner, float value) override;
  void onSpinnerValueChanged(Spinner *spinner, uint value);
  void onWaveformValueChanged(Waveform *wavefor, int value);
  void onSwitchClicked(Switch *sw, bool left_right);
  void onTextSpinnerValueChanged(TextSpinner *ts, int value);
  void onSeqSpinnerValueChanged(SeqSpinner *sq, uint value);
  void onSeqSliderValueChanged(SeqSlider *sq, int value);
  void drawSequencer();
  void drawVolumeMeters();

private:
  float normalize(const float &value, const float &min, const float &max) {
    return (value - min) / (max - min);
  }

  float denormalize(const float value, const float &min, const float &max) {
    return value * (max - min) + min;
  }

  struct Label {
    const char *label;
    int font_size;
    int x;
    int y;
    int align;
  };

  // FontIds;
  FontId robotoCondensed;
  FontId robotoCondensedBold;
  FontId robotoRegular;
  FontId robotoMono;
  // widgets
  std::unordered_map<params, Label> labels;
  std::unordered_map<params, std::unique_ptr<Knob>> Knobs;
  std::unordered_map<params, std::unique_ptr<CheckBox>> CheckBoxes;
  std::unordered_map<params, std::unique_ptr<Slider>> Sliders;
  std::unordered_map<params, std::unique_ptr<Panner>> Panners;
  std::unordered_map<params, std::unique_ptr<Spinner>> Spinners;
  std::unordered_map<params, std::unique_ptr<DropDown>> DropDowns;
  std::unordered_map<params, std::shared_ptr<Menu>> Menus;
  std::unique_ptr<EG> Envelope;
  std::shared_ptr<Waveform> Waveforms[16];
  std::unique_ptr<Switch> rm_bz;

  // sequencer
  std::unique_ptr<TextSpinner> SeqTonePitch[16];
  std::unique_ptr<TextSpinner> SeqNoisePeriod[16];
  std::unique_ptr<TextSpinner> SeqRingmodPitch[16];
  std::unique_ptr<TextSpinner> SeqRingmodDepth[16];
  std::unique_ptr<TextSpinner> SeqLevel[16];
  std::unique_ptr<CheckBox> SeqToneOn[16];
  std::unique_ptr<CheckBox> SeqNoiseOn[16];
  std::unique_ptr<CheckBox> seq_host_sync;
  std::unique_ptr<SeqSpinner> seq_tempo, seq_beat_multiplier, seq_beat_divisor;
  std::unique_ptr<SeqSlider> seq_end, seq_loop;

  // images
//  std::unique_ptr<SVGImage> zynayumi_logo;

  // variables
  int seq_tone_pitch[16];
  int seq_noise_period[16];
  int seq_ringmod_pitch[16];
  int seq_ringmod_depth[16];
  int seq_level[16];
  float amplitude_left, loudness_left;
  float amplitude_right, loudness_right;

#define VERY_SMALL_FLOAT 1.0e-30F

  DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIZynayumi)
};

END_NAMESPACE_DISTRHO

#endif
