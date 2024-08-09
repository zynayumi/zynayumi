#include "UIZynayumi.hpp"

#define NANOSVG_IMPLEMENTATION
#define NANOSVGRAST_IMPLEMENTATION

#define LABEL_MARGIN 10

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------------

UIZynayumi::UIZynayumi() : UI(UI_WIDTH, UI_HEIGHT) {
  robotoCondensed = createFontFromMemory(
      "RobotoCondensed",
      reinterpret_cast<const uchar *>(Fonts::RobotoCondensed_RegularData),
      Fonts::RobotoCondensed_RegularDataSize, false);
  robotoCondensedBold = createFontFromMemory(
      "RobotoCondensedBold",
      reinterpret_cast<const uchar *>(Fonts::RobotoCondensed_BoldData),
      Fonts::RobotoCondensed_BoldDataSize, false);
  robotoRegular = createFontFromMemory(
      "RobotoRegular",
      reinterpret_cast<const uchar *>(Fonts::Roboto_RegularData),
      Fonts::Roboto_RegularDataSize, false);
  robotoMono = createFontFromMemory(
      "RobotoMono",
      reinterpret_cast<const uchar *>(Fonts::RobotoMono_RegularData),
      Fonts::RobotoMono_RegularDataSize, false);

  for (auto &&i : knobData) {
    Knobs[i.first].reset(new Knob(this));
    Knobs[i.first]->setId(i.first);
    Knobs[i.first]->setAbsolutePos(i.second.x, i.second.y);
    Knobs[i.first]->setSize(i.second.w, i.second.h);
    Knobs[i.first]->background_color = i.second.background_color;
    Knobs[i.first]->foreground_color = i.second.foreground_color;
    Knobs[i.first]->highlight_color = i.second.highlight_color;
    Knobs[i.first]->margin = i.second.margin;
    Knobs[i.first]->setCallback(this);
  }
  // get and position labels for knobs
  int labelAlign = ALIGN_CENTER | ALIGN_TOP;
  for (auto &&i : knobData) {
    auto l = i.second.label;
    auto lx = i.second.x + (i.second.w / 2);
    auto ly = i.second.y + i.second.h;

    labels[i.first] = {l, 15, lx, ly,
                       labelAlign}; // TODO: fix hardcoded fontsize
  }
  for (auto &&i : checkBoxData) {
    auto &cb = i.second;
    auto &id = i.first;
    CheckBoxes[id].reset(new CheckBox(this));
    CheckBoxes[id]->setId(i.first);
    CheckBoxes[id]->setAbsolutePos(cb.x, cb.y);
    CheckBoxes[id]->setSize(cb.w, cb.h);
    CheckBoxes[id]->active_color = cb.active_color;
    CheckBoxes[id]->highlight_color = cb.highlight_color;
  }
  // get and position labels for checkboxs
  Rectangle<float> bounds;
  fontSize(15);
  fontFace("RobotoCondensed");
  labelAlign = ALIGN_LEFT | ALIGN_BASELINE;
  for (auto &&i : checkBoxData) {
    auto &cb = i.second;
    auto &id = i.first;
    auto l = cb.label;
    // measure width of labl
    textBounds(0, 0, l, nullptr, bounds);
    auto lw = bounds.getWidth(); // no margin ?
    int lx = cb.x - lw - LABEL_MARGIN;
    int ly = cb.y + cb.h - 2; // 1 pixel higher looks better
    labels[id] = {l, 15, lx, ly,
                  labelAlign}; // TODO: font size hard coded MAGIC NUMBER
  }
  // sliders
  for (auto &&i : sliderData) {
    auto &id = i.first;
    auto &s = i.second;
    Sliders[id].reset(new Slider(this));
    Sliders[id]->setId(id);
    Sliders[id]->setAbsolutePos(s.x, s.y);
    Sliders[id]->setSize(s.w, s.h);
    Sliders[id]->background_color = s.background_color;
    Sliders[id]->foreground_color = s.foreground_color;
    Sliders[id]->highlight_color = s.highlight_color;
    Sliders[id]->default_value = 0.5f;
  }
  // get and position slider labels
  labelAlign = ALIGN_CENTER | ALIGN_TOP;
  for (auto &&i : sliderData) {
    auto l = i.second.label;
    auto lx = i.second.x + (i.second.w / 2);
    auto ly = i.second.y + i.second.h;
    labels[i.first] = {l, 15, lx, ly, labelAlign};
  }

  // panners
  for (auto &&i : pannerData) {
    auto &id = i.first;
    auto &panner = i.second;
    Panners[id].reset(new Panner(this));
    Panners[id]->setId(id);
    Panners[id]->setCallback(this);
    Panners[id]->setAbsolutePos(panner.x, panner.y);
    Panners[id]->setSize(panner.w, panner.h);
    Panners[id]->setHandle(Size<int>(9, panner.h));
    Panners[id]->background_color = panner.background_color;
    Panners[id]->foreground_color = panner.foreground_color;
    Panners[id]->highlight_color = panner.highlight_color;
  }

  // get and position panner labels
  labelAlign = ALIGN_LEFT | ALIGN_BASELINE;
  for (auto &&i : pannerData) {
    auto &pn = i.second;
    auto &id = i.first;
    auto l = pn.label;
    // measure width of labl
    textBounds(0, 0, l, nullptr, bounds);
    auto lw = bounds.getWidth(); // no margin ?
    int lx = pn.x - lw - LABEL_MARGIN;
    int ly = pn.y + pn.h - 2; // 1 pixel higher looks better
    labels[id] = {l, 15, lx, ly,
                  labelAlign}; // TODO: font size hard coded MAGIC NUMBER
  }
  // spinners
  for (auto &&i : spinnerData) {
    auto &id = i.first;
    auto &s = i.second;
    Spinners[id].reset(new Spinner(this));
    Spinners[id]->setId(id);
    Spinners[id]->setAbsolutePos(s.x, s.y);
    Spinners[id]->setSize(s.w, s.h);
    Spinners[id]->background_color = s.background_color;
    Spinners[id]->foreground_color = s.foreground_color;
    Spinners[id]->text_color = s.text_color;
    Spinners[id]->setFont(
        "RobotoCondensed",
        reinterpret_cast<const uchar *>(Fonts::RobotoCondensed_RegularData),
        Fonts::RobotoCondensed_RegularDataSize);
    Spinners[id]->font_size = 15;
    Spinners[id]->callback = this;
  }
  Spinners[MIDI_CHANNEL_0]->addItems({"ANY", "1", "2", "3", "4", "5", "6", "7",
                                      "8", "9", "10", "11", "12", "13", "14",
                                      "15", "16"});
  Spinners[MIDI_CHANNEL_1]->addItems({"ANY", "1", "2", "3", "4", "5", "6", "7",
                                      "8", "9", "10", "11", "12", "13", "14",
                                      "15", "16"});
  Spinners[MIDI_CHANNEL_2]->addItems({"ANY", "1", "2", "3", "4", "5", "6", "7",
                                      "8", "9", "10", "11", "12", "13", "14",
                                      "15", "16"});
  Spinners[PITCH_WHEEL]->addItems<int>(1, 12, 1);

  // get and position spinner labels
  labelAlign = ALIGN_LEFT | ALIGN_BASELINE;
  for (auto &&i : spinnerData) {
    auto &spinner = i.second;
    auto &id = i.first;
    auto l = spinner.label;
    // measure width of labl
    textBounds(0, 0, l, nullptr, bounds);
    auto lw = bounds.getWidth(); // no margin ?
    int lx = spinner.x - lw - LABEL_MARGIN;
    int ly = spinner.y + spinner.h - 2; // 1 pixel higher looks better
    labels[id] = {l, 15, lx, ly,
                  labelAlign}; // TODO: font size hard coded MAGIC NUMBER
  }

  for (auto &&i : dropDownData) {
    auto &id = i.first;
    auto &s = i.second;
    DropDowns[id].reset(new DropDown(this));
    DropDowns[id]->setCallback(this);
    DropDowns[id]->setId(id);
    DropDowns[id]->setAbsolutePos(s.x, s.y);
    DropDowns[id]->setSize(s.w, s.h);
    DropDowns[id]->background_color = s.background_color;
    DropDowns[id]->foreground_color = s.foreground_color;
    DropDowns[id]->text_color = s.text_color;
    DropDowns[id]->setFont(
        "RobotoCondensed",
        reinterpret_cast<const uchar *>(Fonts::RobotoCondensed_RegularData),
        Fonts::RobotoCondensed_RegularDataSize);
    DropDowns[id]->font_size = 13; // TODO : hardcoded
    DropDowns[id]->item = s.item;
  }

  // hide BUZZER_SHAPE
  DropDowns[BUZZER_SHAPE]->setVisible(false);

  // get and position dropdown labels
  labelAlign = ALIGN_LEFT | ALIGN_BASELINE;
  fontFaceId(robotoCondensed);
  fontSize(15);
  for (auto &&i : dropDownData) {
    auto &dropdown = i.second;
    auto &id = i.first;
    auto l = dropdown.label;
    // measure width of labl
    textBounds(0, 0, l, nullptr, bounds);
    auto lw = bounds.getWidth(); // no margin ?
    int lx = dropdown.x - lw - LABEL_MARGIN;
    int ly = dropdown.y + dropdown.h - 2; // 1 pixel higher looks better
    labels[id] = {l, 15, lx, ly,
                  labelAlign}; // TODO: font size hard coded MAGIC NUMBER
  }

  for (auto &&i : menuData) {
    auto &id = i.first;
    auto &s = i.second;
    Menus[id] = std::make_shared<Menu>(this);
    Menus[id]->setCallback(this);
    Menus[id]->setId(id);
    Menus[id]->setAbsolutePos(s.x, s.y);
    /* Menus[id]->setSize(s.w, s.h); */
    /* addItems resizes the menu */
    Menus[id]->setFont(
        "RobotoCondensed",
        reinterpret_cast<const uchar *>(Fonts::RobotoCondensed_RegularData),
        Fonts::RobotoCondensed_RegularDataSize);
    Menus[id]->font_size = 12;
    Menus[id]->foreground_color = s.foreground_color;
    Menus[id]->background_color = s.background_color;
    Menus[id]->highlight_color = s.highlight_color;
    Menus[id]->text_color = s.text_color;
  }
  Menus[EMUL_MODE_MENU]->addItems({"YM2149", "AY-3-8910"});
  Menus[PLAY_MODE_MENU]->addItems({"Mono", "MonoUpArp", "MonoDownArp",
                                   "MonoRandArp", "Unison", "UnisonUpArp",
                                   "UnisonDownArp", "UnisonRandArp", "Poly"});
  Menus[LFO_SHAPE_MENU]->addItems(
      {"Sine", "Triangle", "DownSaw", "UpSaw", "Square", "Rand"});
  Menus[RINGMOD_LOOP_MENU]->addItems({"OFF", "FORWARD", "PINGPONG"});
  Menus[BUZZER_SHAPE_MENU]->addItems({"DOWNSAW", "UPSAW"});

  DropDowns[RINGMOD_LOOP]->setMenu(Menus[RINGMOD_LOOP_MENU]);
  DropDowns[EMUL_MODE]->setMenu(Menus[EMUL_MODE_MENU]);
  DropDowns[PLAY_MODE]->setMenu(Menus[PLAY_MODE_MENU]);
  DropDowns[LFO_SHAPE]->setMenu(Menus[LFO_SHAPE_MENU]);
  DropDowns[BUZZER_SHAPE]->setMenu(Menus[BUZZER_SHAPE_MENU]);

  Envelope.reset(new EG(this));
  Envelope->setId(1234);
  Envelope->setSize(277, 53);
  Envelope->setAbsolutePos(704, 379);
  Envelope->foreground_color = blue_pigment_1;
  Envelope->background_color = blue_pigment_1;
  Envelope->env_attack_time = 1.f;
  Envelope->env_hold1_level = 15.f;
  Envelope->env_inter1_time = 3.f;
  Envelope->env_hold2_level = 10.f;
  Envelope->env_inter2_time = 5.f;
  Envelope->env_hold3_level = 5.f;
  Envelope->env_decay_time = 4.f;
  Envelope->env_sustain_level = 15.f;
  Envelope->env_release = 5.f;

  for (int i = 0; i < 16; i++) {
    Waveforms[i].reset(new Waveform(this));
    Waveforms[i]->setId(RINGMOD_WAVEFORM_LEVEL1 + i);
    Waveforms[i]->setCallback(this);
    Waveforms[i]->setSize(15, 80);
    Waveforms[i]->setAbsolutePos(708 + (i * 17), 696);
    Waveforms[i]->foreground_color = saffron_3;
    Waveforms[i]->background_color = saffron_4;
  }

  rm_bz.reset(new Switch(this));
  rm_bz->setId(BUZZER_ENABLED);
  rm_bz->setSize(23, 16);
  rm_bz->setAbsolutePos(900, 665);
  rm_bz->foreground_color = saffron_3;
  rm_bz->left_right = true;
  rm_bz->setCallback(this);

  const int X_START = 386;
  const int X_DIST = 45;
  for (int i = 0; i < 16; i++) {
    SeqTonePitch[i].reset(new TextSpinner(this));
    SeqTonePitch[i]->setId(SEQ_TONE_PITCH_0 + i);
    SeqTonePitch[i]->callback = this;
    SeqTonePitch[i]->min = -48;
    SeqTonePitch[i]->max = 48;
    SeqTonePitch[i]->setSize(30, 16);
    SeqTonePitch[i]->setAbsolutePos(X_START + 0 * X_DIST,
                                    310 + i * 28); // TODO define constant
    SeqTonePitch[i]->value = 0;

    SeqNoisePeriod[i].reset(new TextSpinner(this));
    SeqNoisePeriod[i]->setId(SEQ_NOISE_PERIOD_0 + i);
    SeqNoisePeriod[i]->callback = this;
    SeqNoisePeriod[i]->min = -15;
    SeqNoisePeriod[i]->max = 15;
    SeqNoisePeriod[i]->setSize(30, 16);
    SeqNoisePeriod[i]->setAbsolutePos(X_START + 1 * X_DIST,
                                      310 + i * 28); // TODO define constant
    SeqNoisePeriod[i]->value = 0;

    SeqRingmodPitch[i].reset(new TextSpinner(this));
    SeqRingmodPitch[i]->setId(SEQ_RINGMOD_PITCH_0 + i);
    SeqRingmodPitch[i]->callback = this;
    SeqRingmodPitch[i]->min = -48;
    SeqRingmodPitch[i]->max = 48;
    SeqRingmodPitch[i]->setSize(30, 16);
    SeqRingmodPitch[i]->setAbsolutePos(X_START + 2 * X_DIST,
                                       310 + i * 28); // TODO define constant
    SeqRingmodPitch[i]->value = 0;

    SeqRingmodDepth[i].reset(new TextSpinner(this));
    SeqRingmodDepth[i]->setId(SEQ_RINGMOD_DEPTH_0 + i);
    SeqRingmodDepth[i]->callback = this;
    SeqRingmodDepth[i]->min = 0;
    SeqRingmodDepth[i]->max = 15;
    SeqRingmodDepth[i]->setSize(30, 16);
    SeqRingmodDepth[i]->setAbsolutePos(X_START + 3 * X_DIST,
                                       310 + i * 28); // TODO define constant
    SeqRingmodDepth[i]->value = 0;

    SeqLevel[i].reset(new TextSpinner(this));
    SeqLevel[i]->setId(SEQ_LEVEL_0 + i);
    SeqLevel[i]->callback = this;
    SeqLevel[i]->min = 0;
    SeqLevel[i]->max = 15;
    SeqLevel[i]->setSize(30, 16);
    SeqLevel[i]->setAbsolutePos(X_START + 4 * X_DIST - 8,
                                310 + i * 28); // TODO define constant
    SeqLevel[i]->value = 0;

    SeqToneOn[i].reset(new CheckBox(this));
    SeqToneOn[i]->setId(SEQ_TONE_ON_0 + i);
    SeqToneOn[i]->callback = this;
    SeqToneOn[i]->setSize(14, 14);
    SeqToneOn[i]->active_color = saffron_1;
    SeqToneOn[i]->border_color = saffron_1;
    SeqToneOn[i]->setAbsolutePos(
        X_START + 5 * X_DIST - 16,
        314 + i * 28); // TODO define constantSeqToneOn[i].reset(new
                       // CheckBox(this));

    SeqNoiseOn[i].reset(new CheckBox(this));
    SeqNoiseOn[i]->setId(SEQ_NOISE_ON_0 + i);
    SeqNoiseOn[i]->callback = this;
    SeqNoiseOn[i]->setSize(14, 14);
    SeqNoiseOn[i]->active_color = saffron_1;
    SeqNoiseOn[i]->border_color = saffron_1;
    SeqNoiseOn[i]->setAbsolutePos(X_START + 6 * X_DIST - 24,
                                  314 + i * 28); // TODO define constant
  }

  seq_tempo.reset(new SeqSpinner(this));
  seq_tempo->setId(SEQ_TEMPO);
  seq_tempo->setSize(45, 12);
  seq_tempo->setAbsolutePos(412, 246);
  seq_tempo->callback = this;
  seq_tempo->foreground_color = saffron_1;
  seq_tempo->text_color = saffron_1;
  seq_tempo->font_size = 20;
  seq_tempo->setFont(
      "RobotoMono",
      reinterpret_cast<const uchar *>(Fonts::RobotoMono_RegularData),
      Fonts::RobotoMono_RegularDataSize);
  seq_tempo->addItems(30, 300, 1);

  seq_beat_multiplier.reset(new SeqSpinner(this));
  seq_beat_multiplier->setId(SEQ_BEAT_MULTIPLIER);
  seq_beat_multiplier->setSize(45, 12);
  seq_beat_multiplier->setAbsolutePos(600, 224);
  seq_beat_multiplier->callback = this;
  seq_beat_multiplier->foreground_color = saffron_1;
  seq_beat_multiplier->text_color = saffron_1;
  seq_beat_multiplier->font_size = 20;
  seq_beat_multiplier->setFont(
      "RobotoMono",
      reinterpret_cast<const uchar *>(Fonts::RobotoMono_RegularData),
      Fonts::RobotoMono_RegularDataSize);
  seq_beat_multiplier->addItems(1, 64, 1);

  seq_beat_divisor.reset(new SeqSpinner(this));
  seq_beat_divisor->setId(SEQ_BEAT_DIVISOR);
  seq_beat_divisor->setSize(45, 12);
  seq_beat_divisor->setAbsolutePos(600, 246);
  seq_beat_divisor->callback = this;
  seq_beat_divisor->foreground_color = saffron_1;
  seq_beat_divisor->text_color = saffron_1;
  seq_beat_divisor->font_size = 20;
  seq_beat_divisor->setFont(
      "RobotoMono",
      reinterpret_cast<const uchar *>(Fonts::RobotoMono_RegularData),
      Fonts::RobotoMono_RegularDataSize);
  seq_beat_divisor->addItems(1, 64, 1);

  seq_host_sync.reset(new CheckBox(this));
  seq_host_sync->setId(SEQ_HOST_SYNC);
  seq_host_sync->setSize(14, 14);
  seq_host_sync->setAbsolutePos(444, 223);
  seq_host_sync->border_color = saffron_1;
  seq_host_sync->active_color = saffron_1;

  seq_end.reset(new SeqSlider(this));
  seq_end->setId(SEQ_END);
  seq_end->setCallback(this);
  seq_end->setAbsolutePos(325, 310);
  seq_end->setSize(17, 440);
  const auto r = saffron_1.red;
  const auto g = saffron_1.green;
  const auto b = saffron_1.blue;
  seq_end->background_color = Color(r, g, b, .33f);
  seq_end->foreground_color = saffron_1;

  seq_loop.reset(new SeqSlider(this));
  seq_loop->setId(SEQ_LOOP);
  seq_loop->setCallback(this);
  seq_loop->left_right = false; // right hand side
  seq_loop->setAbsolutePos(657, 310);
  seq_loop->setSize(17, 440);
  seq_loop->background_color = Color(r, g, b, .33f);
  seq_loop->foreground_color = saffron_1;

  // zynayumi_logo.reset(new SVGImage(this, artwork::zynayumi_logo, 1.0f));

  amplitude_left = 0.0f;
  amplitude_right = 0.0f;
  loudness_left = -60.f;
  loudness_right = -60.f;
}

void UIZynayumi::parameterChanged(uint32_t index, float value) {
  // printf("UIZynayumi::parameterChanged( %i , %f)\n", index, value);
  switch (index) {
  case OUTPUT_LEFT:
    amplitude_left = value;
    if (amplitude_left) {
      loudness_left = 20 * log10(amplitude_left);
    } else {
      loudness_left = -60.f;
    }
    loudness_left = std::max(-60.f, loudness_left);
    repaint();
    break;
  case OUTPUT_RIGHT:
    amplitude_right = value;
    if (amplitude_right) {
      loudness_right = 20 * log10(amplitude_right);
    } else {
      loudness_right = -60.f;
    }
    loudness_right = std::max(-60.f, loudness_right);
    repaint();
    break;

  case EMUL_MODE:
    DropDowns[EMUL_MODE]->setValue(value);
    break;
  case PLAY_MODE:
    DropDowns[PLAY_MODE]->setValue(value);
    break;
  case TONE_RESET:
    CheckBoxes[TONE_RESET]->isActive = value;
    break;
  case TONE_PHASE:
    Knobs[TONE_PHASE]->setValue(value);
    break;
  case TONE_TIME:
    Knobs[TONE_TIME]->setValue(normalize(value, 0, 100));
    break;
  case TONE_DETUNE:
    Knobs[TONE_DETUNE]->setValue(
        normalize(value, TONE_DETUNE_L, TONE_DETUNE_U));
    break;
  case TONE_TRANSPOSE:
    Knobs[TONE_TRANSPOSE]->setValue(
        normalize(value, TONE_TRANSPOSE_L, TONE_TRANSPOSE_U));
    break;
  case TONE_SPREAD:
    Knobs[TONE_SPREAD]->setValue(
        normalize(value, TONE_SPREAD_L, TONE_SPREAD_U));
    break;
  case TONE_LEGACY_TUNING:
    CheckBoxes[TONE_LEGACY_TUNING]->isActive = value;
    break;
  case NOISE_TIME:
    Knobs[NOISE_TIME]->setValue(normalize(value, 0, 100));
    break;
  case NOISE_PERIOD:
    Knobs[NOISE_PERIOD]->setValue(
        normalize(value, NOISE_PERIOD_L, NOISE_PERIOD_U));
    break;
  case NOISE_PERIOD_ENV_ATTACK:
    Knobs[NOISE_PERIOD_ENV_ATTACK]->setValue(
        normalize(value, NOISE_PERIOD_ENV_ATTACK_L, NOISE_PERIOD_ENV_ATTACK_U));
    break;
  case NOISE_PERIOD_ENV_TIME:
    Knobs[NOISE_PERIOD_ENV_TIME]->setValue(
        normalize(value, NOISE_PERIOD_ENV_TIME_L, NOISE_PERIOD_ENV_TIME_U));
    break;
  case ENV_ATTACK_TIME:
    Knobs[ENV_ATTACK_TIME]->setValue(
        normalize(value, ENV_ATTACK_TIME_L, ENV_ATTACK_TIME_U));
    Envelope->env_attack_time = value;
    break;
  case ENV_HOLD1_LEVEL:
    Knobs[ENV_HOLD1_LEVEL]->setValue(
        normalize(value, ENV_HOLD1_LEVEL_L, ENV_HOLD1_LEVEL_U));
    Envelope->env_hold1_level = value;
    break;
  case ENV_INTER1_TIME:
    Knobs[ENV_INTER1_TIME]->setValue(
        normalize(value, ENV_INTER1_TIME_L, ENV_INTER1_TIME_U));
    Envelope->env_inter1_time = value;
    break;
  case ENV_HOLD2_LEVEL:
    Knobs[ENV_HOLD2_LEVEL]->setValue(
        normalize(value, ENV_HOLD2_LEVEL_L, ENV_HOLD2_LEVEL_U));
    Envelope->env_hold2_level = value;
    break;
  case ENV_INTER2_TIME:
    Knobs[ENV_INTER2_TIME]->setValue(
        normalize(value, ENV_INTER2_TIME_L, ENV_INTER2_TIME_U));
    Envelope->env_inter2_time = value;
    break;
  case ENV_HOLD3_LEVEL:
    Knobs[ENV_HOLD3_LEVEL]->setValue(
        normalize(value, ENV_HOLD3_LEVEL_L, ENV_HOLD3_LEVEL_U));
    Envelope->env_hold3_level = value;
    break;
  case ENV_DECAY_TIME:
    Knobs[ENV_DECAY_TIME]->setValue(
        normalize(value, ENV_DECAY_TIME_L, ENV_DECAY_TIME_U));
    Envelope->env_decay_time = value;
    break;
  case ENV_SUSTAIN_LEVEL:
    Knobs[ENV_SUSTAIN_LEVEL]->setValue(
        normalize(value, ENV_SUSTAIN_LEVEL_L, ENV_SUSTAIN_LEVEL_U));
    Envelope->env_sustain_level = value;
    break;
  case ENV_RELEASE:
    Knobs[ENV_RELEASE]->setValue(
        normalize(value, ENV_RELEASE_L, ENV_RELEASE_U));
    Envelope->env_release = value;
    break;
  case PITCH_ENV_ATTACK_PITCH:
    Knobs[PITCH_ENV_ATTACK_PITCH]->setValue(
        normalize(value, PITCH_ENV_ATTACK_PITCH_L, PITCH_ENV_ATTACK_PITCH_U));
    break;
  case PITCH_ENV_TIME:
    Knobs[PITCH_ENV_TIME]->setValue(
        normalize(value, PITCH_ENV_TIME_L, PITCH_ENV_TIME_U));
    break;
  case PITCH_ENV_SMOOTHNESS:
    Knobs[PITCH_ENV_SMOOTHNESS]->setValue(
        normalize(value, PITCH_ENV_SMOOTHNESS_L, PITCH_ENV_SMOOTHNESS_U));
    break;
  case RINGMOD_WAVEFORM_LEVEL1 ... RINGMOD_WAVEFORM_LEVEL16:
    Waveforms[index - RINGMOD_WAVEFORM_LEVEL1]->setValue(value);
    break;

  case RINGMOD_RESET:
    CheckBoxes[RINGMOD_RESET]->isActive = value;
    break;
  case RINGMOD_SYNC:
    CheckBoxes[RINGMOD_SYNC]->isActive = value;
    break;
  case RINGMOD_PHASE:
    Knobs[RINGMOD_PHASE]->setValue(value);
    break;
  case RINGMOD_LOOP:
    DropDowns[RINGMOD_LOOP]->setValue(value);
    break;
  case RINGMOD_DETUNE:
    Knobs[RINGMOD_DETUNE]->setValue(
        normalize(value, RINGMOD_DETUNE_L, RINGMOD_DETUNE_U));
    break;
  case RINGMOD_TRANSPOSE:
    Knobs[RINGMOD_TRANSPOSE]->setValue(
        normalize(value, RINGMOD_TRANSPOSE_L, RINGMOD_TRANSPOSE_U));
    break;
  case RINGMOD_FIXED_PITCH:
    Knobs[RINGMOD_FIXED_PITCH]->setValue(
        normalize(value, RINGMOD_FIXED_PITCH_L, RINGMOD_FIXED_PITCH_U));
    break;
  case RINGMOD_FIXED_VS_RELATIVE:
    Knobs[RINGMOD_FIXED_VS_RELATIVE]->setValue(value);
    break;
  case RINGMOD_DEPTH:
    Knobs[RINGMOD_DEPTH]->setValue(
        normalize(value, RINGMOD_DEPTH_L, RINGMOD_DEPTH_U));
    break;
  case BUZZER_ENABLED:
    rm_bz->left_right = value;
    if (rm_bz->left_right == true) {
      DropDowns[BUZZER_SHAPE]->setVisible(false);
      for (auto &w : Waveforms) {
        w->setVisible(true);
      }
    } else {
      DropDowns[BUZZER_SHAPE]->setVisible(true);
      for (auto &w : Waveforms)
        w->setVisible(false);
    }
    break;
  case BUZZER_SHAPE:
    DropDowns[BUZZER_SHAPE]->setValue(value);
    break;
  case SEQ_TONE_PITCH_0 ... SEQ_TONE_PITCH_15: {
    const uint id = index - SEQ_TONE_PITCH_0;
    seq_tone_pitch[id] = value;
    SeqTonePitch[id]->value = value;
    break;
  }
  case SEQ_NOISE_PERIOD_0 ... SEQ_NOISE_PERIOD_15: {
    const uint id = index - SEQ_NOISE_PERIOD_0;
    seq_noise_period[id] = value;
    SeqNoisePeriod[id]->value = value;
    break;
  }
  case SEQ_RINGMOD_PITCH_0 ... SEQ_RINGMOD_PITCH_15: {
    const uint id = index - SEQ_RINGMOD_PITCH_0;
    seq_ringmod_pitch[id] = value;
    SeqRingmodPitch[id]->value = value;
    break;
  }
  case SEQ_RINGMOD_DEPTH_0 ... SEQ_RINGMOD_DEPTH_15: {
    const uint id = index - SEQ_RINGMOD_DEPTH_0;
    seq_ringmod_depth[id] = value;
    SeqRingmodDepth[id]->value = value;
    break;
  }
  case SEQ_LEVEL_0 ... SEQ_LEVEL_15: {
    const uint id = index - SEQ_LEVEL_0;
    seq_level[id] = value;
    SeqLevel[id]->value = value;
    break;
  }
  case SEQ_TONE_ON_0 ... SEQ_TONE_ON_15: {
    const uint id = index - SEQ_TONE_ON_0;
    SeqToneOn[id]->isActive = value;
    break;
  }
  case SEQ_NOISE_ON_0 ... SEQ_NOISE_ON_15: {
    const uint id = index - SEQ_NOISE_ON_0;
    SeqNoiseOn[id]->isActive = value;
    break;
  }
  case SEQ_TEMPO:
    seq_tempo->setValue(value);
    break;
  case SEQ_HOST_SYNC:
    seq_host_sync->isActive = value;
    break;
  case SEQ_BEAT_DIVISOR:
    seq_beat_divisor->setValue(value);
    break;
  case SEQ_BEAT_MULTIPLIER:
    seq_beat_multiplier->setValue(value);
    break;
  case SEQ_LOOP:
    seq_loop->setValue(value);
    break;
  case SEQ_END:
    seq_end->setValue(value);
    break;
  case LFO_SHAPE:
    DropDowns[LFO_SHAPE]->setValue(value);
    break;
  case LFO_FREQ:
    Knobs[LFO_FREQ]->setValue(normalize(value, LFO_FREQ_L, LFO_FREQ_U));
    break;
  case LFO_DELAY:
    Knobs[LFO_DELAY]->setValue(normalize(value, LFO_DELAY_L, LFO_DELAY_U));
    break;
  case LFO_DEPTH:
    Knobs[LFO_DEPTH]->setValue(normalize(value, LFO_DEPTH_L, LFO_DEPTH_U));
    break;
  case PORTAMENTO_TIME:
    Knobs[PORTAMENTO_TIME]->setValue(
        normalize(value, PORTAMENTO_TIME_L, PORTAMENTO_TIME_U));
    break;
  case PORTAMENTO_SMOOTHNESS:
    Knobs[PORTAMENTO_SMOOTHNESS]->setValue(value);
    break;
  case YM_CHANNEL_ENABLED_0:
    CheckBoxes[YM_CHANNEL_ENABLED_0]->isActive = value; // todo : is this safe ?
    break;
  case YM_CHANNEL_ENABLED_1:
    CheckBoxes[YM_CHANNEL_ENABLED_1]->isActive = value; // todo : is this safe ?
    break;
  case YM_CHANNEL_ENABLED_2:
    CheckBoxes[YM_CHANNEL_ENABLED_2]->isActive = value; // todo : is this safe ?
    break;
  case PAN_0:
    Panners[PAN_0]->setValue(value);
    break;
  case PAN_1:
    Panners[PAN_1]->setValue(value);
    break;
  case PAN_2:
    Panners[PAN_2]->setValue(value);
    break;
  case GAIN:
    Knobs[GAIN]->setValue(normalize(value, GAIN_L, GAIN_U));
    break;
  case PITCH_WHEEL:
    Spinners[PITCH_WHEEL]->setValue(value);
    break;
  case VELOCITY_SENSITIVITY:
    Knobs[VELOCITY_SENSITIVITY]->setValue(value);
    break;
    // todo : implement RINGMOD_VELOCITY_SENSITIVITY
  // case RINGMOD_VELOCITY_SENSITIVITY:
  //     Knobs[RINGMOD_VELOCITY_SENSITIVITY]->setValue(value);
  //     break;
  case NOISE_PERIOD_PITCH_SENSITIVITY:
    Knobs[NOISE_PERIOD_PITCH_SENSITIVITY]->setValue(value);
    break;
  case MODULATION_SENSITIVITY:
    Knobs[MODULATION_SENSITIVITY]->setValue(
        normalize(value, MODULATION_SENSITIVITY_L, MODULATION_SENSITIVITY_U));
    break;
  case MIDI_CHANNEL_0:
    Spinners[MIDI_CHANNEL_0]->setValue(value);
    break;
  case MIDI_CHANNEL_1:
    Spinners[MIDI_CHANNEL_1]->setValue(value);
    break;
  case MIDI_CHANNEL_2:
    Spinners[MIDI_CHANNEL_2]->setValue(value);
    break;
  case OVERSAMPLING:
    break;

  default:
    break;
    repaint();
  }
}

void UIZynayumi::programLoaded(uint32_t) {
  // do stuff
}

void UIZynayumi::onNanoDisplay() {
  float width = getWidth();
  float height = getHeight();
  // background
  beginPath();
  fillColor(0, 0, 0);
  rect(0.0f, 0.0f, width, height);
  fill();
  closePath();

  // boxes
  for (auto &&b : boxData) {
    const auto halfStrokeWidth = b.stroke_width / 2;
    Paint back = linearGradient(b.x, b.y, b.x, b.y + b.h * .75f, b.fill_color,
                                Color(0.0f, 0.0f, 0.0f, 0.0f));
    fillPaint(back);
    strokeColor(b.stroke_color);
    strokeWidth(b.stroke_width);
    beginPath();
    rect(b.x, b.y, b.w, b.h);
    fill();

    closePath();
    beginPath();
    rect(b.x + halfStrokeWidth, b.y + halfStrokeWidth, b.w - b.stroke_width,
         b.h - b.stroke_width);
    stroke();
    closePath();
  }
  // lines
  fillColor(alex_grey);
  for (auto &&line : lineData) {
    beginPath();
    rect(line.x, line.y, line.w, line.h);
    fill();
    closePath();
  }

  // labels
  fontFaceId(robotoCondensedBold);
  for (auto &&i : boxLabelData) {
    const auto x = i.x;
    const auto y = i.y;
    const auto w = i.w;
    const auto h = i.h;
    const auto cx = x + w / 2;
    const auto cy = y + h / 2;
    //  box
    beginPath();
    fillColor(194, 194, 194);
    rect(x, y, w, h);
    fill();
    closePath();
    beginPath();
    fillColor(0, 0, 0);
    textAlign(ALIGN_CENTER | ALIGN_MIDDLE);
    fontSize(i.font_size);
    text(cx, cy, i.label, nullptr);
    closePath();
  }

  fontFaceId(robotoCondensed);
  fillColor(floral_white);
  beginPath();
  for (auto &&i : labels) {
    const auto x = i.second.x;
    const auto y = i.second.y;
    const auto l = i.second.label;
    fontSize(i.second.font_size);
    textAlign(i.second.align);
    text(x, y, l, nullptr);
  }
  closePath();
  //
  if (rm_bz->left_right == false) {
    beginPath();
    text(800, 731, "SHAPE", nullptr);
    closePath();
  }

  // switch background
  fillColor(alex_grey);
  beginPath();
  rect(897, 664, 28, 19);
  fill();
  closePath();

  drawVolumeMeters();
  drawSequencer();
  // images
  // zynayumi_logo->drawAt(10, 10);
}

void UIZynayumi::drawVolumeMeters() {
  // volume meter
  // back
  fillColor(alex_grey);
  // left
  beginPath();
  rect(938, 64, 17, 98);
  fill();
  closePath();
  // right
  beginPath();
  rect(961, 64, 17, 98);
  fill();
  closePath();

  // value
  int volume_height = 98 - (abs(loudness_left) / 60.f) * 98;
  int value_y = 64 + 98 - volume_height;

  fillColor(cadet_blue);
  beginPath();
  rect(938, value_y, 17, volume_height);
  fill();
  closePath();
  // right
  volume_height = 98 - (abs(loudness_right) / 60.f) * 98;
  value_y = 64 + 98 - volume_height;
  beginPath();
  rect(961, value_y, 17, volume_height);
  fill();
  closePath();
}

void UIZynayumi::drawSequencer() {
  fontFaceId(robotoMono);
  fontSize(20);
  textAlign(ALIGN_TOP | ALIGN_LEFT);
  fillColor(saffron_1);

  char buffer[64];
  beginPath();
  text(339 + 11, 224 - 5, "HOST SYNC", nullptr);
  closePath();
  beginPath();
  text(339 + 11, 246 - 5, "TEMPO", nullptr);
  closePath();
  beginPath();
  text(513, 224 - 5, "BEAT MULT", nullptr);
  closePath();
  beginPath();
  text(513, 246 - 5, "BEAT DIV", nullptr);
  closePath();
  beginPath();
  text(350, 290, "     TP   NP   RP  RD  LV  TN  NS", nullptr);
  closePath();

  fillColor(saffron_1);
  for (int i = 0; i < 16; i++) {
    sprintf(buffer, "%02i:", i + 1);
    beginPath();
    text(350, 310 + i * 28, buffer, nullptr);
    closePath();
  }

  for (int i = 0; i < 16; i++) {
    const uint x = SeqTonePitch[i]->getAbsoluteX();
    const uint y = SeqTonePitch[i]->getAbsoluteY();

    sprintf(buffer, "%+03d", seq_tone_pitch[i]);
    beginPath();
    text(x, y, buffer, nullptr);
    closePath();
  }

  for (int i = 0; i < 16; i++) {
    const uint x = SeqNoisePeriod[i]->getAbsoluteX();
    const uint y = SeqNoisePeriod[i]->getAbsoluteY();
    sprintf(buffer, "%+03d", seq_noise_period[i]);
    beginPath();
    text(x, y, buffer, nullptr);
    closePath();
  }

  for (int i = 0; i < 16; i++) {
    const uint x = SeqRingmodPitch[i]->getAbsoluteX();
    const uint y = SeqRingmodPitch[i]->getAbsoluteY();
    sprintf(buffer, "%+03d", seq_ringmod_pitch[i]);
    beginPath();
    text(x, y, buffer, nullptr);
    closePath();
  }

  for (int i = 0; i < 16; i++) {
    const uint x = SeqRingmodDepth[i]->getAbsoluteX();
    const uint y = SeqRingmodDepth[i]->getAbsoluteY();
    sprintf(buffer, "%02d", seq_ringmod_depth[i]);
    beginPath();
    text(x, y, buffer, nullptr);
    closePath();
  }

  for (int i = 0; i < 16; i++) {
    const uint x = SeqLevel[i]->getAbsoluteX();
    const uint y = SeqLevel[i]->getAbsoluteY();
    sprintf(buffer, "%02d", seq_level[i]);
    beginPath();
    text(x, y, buffer, nullptr);
    closePath();
  }
}

bool UIZynayumi::onMouse(const MouseEvent &) { return false; }

bool UIZynayumi::onScroll(const ScrollEvent &) { return false; }

bool UIZynayumi::onMotion(const MotionEvent &ev) {
  // printf("mouse x/y %i,%i \n", ev.pos.getX(), ev.pos.getY());
  return false;
}

void UIZynayumi::onDropDownClicked(DropDown *dd) {
  const uint id = dd->getId();
  switch (id) {
  case EMUL_MODE:
    Menus[EMUL_MODE_MENU]->show();
    break;
  case PLAY_MODE:
    Menus[PLAY_MODE_MENU]->show();
    break;
  case LFO_SHAPE:
    Menus[LFO_SHAPE_MENU]->show();
    break;
  case RINGMOD_LOOP:
    Menus[RINGMOD_LOOP_MENU]->show();
    break;
  case BUZZER_SHAPE:
    Menus[BUZZER_SHAPE_MENU]->show();
    break;

  default:
    break;
  }
}

void UIZynayumi::knobDragStarted(Knob *) {}
void UIZynayumi::knobDragFinished(Knob *, float) {}
void UIZynayumi::knobValueChanged(Knob *knob, float value) {
  const int id = knob->getId();
  switch (id) {
  case VELOCITY_SENSITIVITY:
    setParameterValue(VELOCITY_SENSITIVITY, value);
    break;
  case NOISE_PERIOD_PITCH_SENSITIVITY:
    setParameterValue(NOISE_PERIOD_PITCH_SENSITIVITY, value);
    break;
  case MODULATION_SENSITIVITY:
    value *= MODULATION_SENSITIVITY_U;
    setParameterValue(MODULATION_SENSITIVITY, value);
    break;
  case PORTAMENTO_TIME:
    value *= PORTAMENTO_TIME_U;
    setParameterValue(PORTAMENTO_TIME, value);
    break;
  case PORTAMENTO_SMOOTHNESS:
    setParameterValue(PORTAMENTO_SMOOTHNESS, value);
    break;
  case GAIN:
    value *= GAIN_U;
    setParameterValue(GAIN, value);
    break;
  case TONE_PHASE:
    setParameterValue(TONE_PHASE, value);
    break;
  case TONE_TIME:
    value *= 100; // max value == inf but that's converted to 100%
    setParameterValue(TONE_TIME, value);
    break;
  case TONE_DETUNE:
    value = denormalize(value, TONE_DETUNE_L, TONE_DETUNE_U);
    setParameterValue(TONE_DETUNE, value);
    break;
  case TONE_TRANSPOSE:
    value = denormalize(value, TONE_TRANSPOSE_L, TONE_TRANSPOSE_U);
    setParameterValue(TONE_TRANSPOSE, value);
    break;
  case TONE_SPREAD:
    value = value * 0.5;
    setParameterValue(TONE_SPREAD, value);
    break;
  case NOISE_PERIOD:
    value = denormalize(value, NOISE_PERIOD_L, NOISE_PERIOD_U);
    setParameterValue(NOISE_PERIOD, value);
    break;
  case NOISE_TIME:
    value *= 100; // max value == inf but that's converted to 100%
    setParameterValue(NOISE_TIME, value);
    break;
  case NOISE_PERIOD_ENV_ATTACK:
    value = denormalize(value, NOISE_PERIOD_ENV_ATTACK_L,
                        NOISE_PERIOD_ENV_ATTACK_U);
    setParameterValue(NOISE_PERIOD_ENV_ATTACK, value);
    break;
  case NOISE_PERIOD_ENV_TIME:
    value *= NOISE_PERIOD_ENV_TIME_U;
    setParameterValue(NOISE_PERIOD_ENV_TIME, value);
    break;
  case ENV_ATTACK_TIME:
    Envelope->env_attack_time = value * 10.f;
    value *= ENV_ATTACK_TIME_U;
    setParameterValue(ENV_ATTACK_TIME, value);
    repaint();
    break;
  case ENV_INTER1_TIME:
    Envelope->env_inter1_time = value * 10.f;
    value *= ENV_INTER1_TIME_U;
    setParameterValue(ENV_INTER1_TIME, value);
    repaint();
    break;
  case ENV_INTER2_TIME:
    Envelope->env_inter2_time = value * 10.f;
    value *= ENV_INTER2_TIME_U;
    setParameterValue(ENV_INTER2_TIME, value);
    repaint();
    break;
  case ENV_DECAY_TIME:
    Envelope->env_decay_time = value * 10.f;
    value *= ENV_DECAY_TIME_U;
    setParameterValue(ENV_DECAY_TIME, value);
    repaint();
    break;
  case ENV_RELEASE:
    Envelope->env_release = value * 10.f;
    value *= ENV_RELEASE_U;
    setParameterValue(ENV_RELEASE, value);
    repaint();
    break;
  case ENV_HOLD1_LEVEL:
    Envelope->env_hold1_level = value * 15.f;
    value *= ENV_HOLD1_LEVEL_U;
    setParameterValue(ENV_HOLD1_LEVEL_U, value);
    repaint();
    break;
  case ENV_HOLD2_LEVEL:
    Envelope->env_hold2_level = value * 15.f;
    value *= ENV_HOLD2_LEVEL_U;
    setParameterValue(ENV_HOLD2_LEVEL, value);
    repaint();
    break;
  case ENV_HOLD3_LEVEL:
    Envelope->env_hold3_level = value * 15.f;
    value *= ENV_HOLD3_LEVEL_U;
    setParameterValue(ENV_HOLD3_LEVEL, value);
    repaint();
    break;
  case ENV_SUSTAIN_LEVEL:
    Envelope->env_sustain_level = value * 15.f;
    value *= ENV_SUSTAIN_LEVEL_U;
    setParameterValue(ENV_SUSTAIN_LEVEL, value);
    repaint();
    break;
  case LFO_FREQ:
    value *= LFO_FREQ_U;
    setParameterValue(LFO_FREQ, value);
    break;
  case LFO_DELAY:
    value *= LFO_DELAY_U;
    setParameterValue(LFO_DELAY, value);
    break;
  case LFO_DEPTH:
    value *= LFO_DEPTH_U;
    setParameterValue(LFO_DEPTH, value);
    break;
  case PITCH_ENV_ATTACK_PITCH:
    value =
        denormalize(value, PITCH_ENV_ATTACK_PITCH_L, PITCH_ENV_ATTACK_PITCH_U);
    setParameterValue(PITCH_ENV_ATTACK_PITCH, value);
    break;
  case PITCH_ENV_TIME:
    value *= PITCH_ENV_TIME_U;
    setParameterValue(PITCH_ENV_TIME, value);
    break;
  case PITCH_ENV_SMOOTHNESS:
    setParameterValue(PITCH_ENV_SMOOTHNESS, value);
    break;
  case RINGMOD_PHASE:
    setParameterValue(RINGMOD_PHASE, value);
    break;
  case RINGMOD_DETUNE:
    value = denormalize(value, RINGMOD_DETUNE_L, RINGMOD_DETUNE_U);
    setParameterValue(RINGMOD_DETUNE, value);
    break;
  case RINGMOD_TRANSPOSE:
    value = denormalize(value, RINGMOD_TRANSPOSE_L, RINGMOD_TRANSPOSE_U);
    setParameterValue(RINGMOD_TRANSPOSE, value);
    break;
  case RINGMOD_FIXED_PITCH:
    value *= RINGMOD_FIXED_PITCH_U;
    setParameterValue(RINGMOD_FIXED_PITCH, value);
    break;
  case RINGMOD_DEPTH:
    value *= RINGMOD_DEPTH_U;
    setParameterValue(RINGMOD_DEPTH, value);
    break;
  case RINGMOD_FIXED_VS_RELATIVE:
    setParameterValue(RINGMOD_FIXED_VS_RELATIVE, value);
    break;

  default:
    break;
  }
}

void UIZynayumi::onSliderValueChanged(Slider *slider, float value) {
  printf("onSliderValueChanged(%i, %f)\n", slider->getId(), value);
}

void UIZynayumi::onSeqSliderValueChanged(SeqSlider *seqslider, int value) {
  const uint id = seqslider->getId();
  // printf("onSeqSliderValueChanged(%i, %f)\n", id, value);
  setParameterValue(id, value);
}

void UIZynayumi::onWaveformValueChanged(Waveform *waveform, int value) {
  const uint id = waveform->getId();
  setParameterValue(id, value);
  printf("waveform %i\n", value);
}

void UIZynayumi::onPannerValueChanged(Panner *panner, float value) {
  const uint id = panner->getId();
  setParameterValue(id, value);
}

void UIZynayumi::onMenuClicked(Menu *mn, uint iItem, std::string sItem) {
  const auto id = mn->getId();
  switch (id) {
  case RINGMOD_LOOP_MENU:
    DropDowns[RINGMOD_LOOP]->item = sItem;
    setParameterValue(RINGMOD_LOOP, iItem);
    break;
  case BUZZER_SHAPE_MENU:
    DropDowns[BUZZER_SHAPE]->item = sItem;
    setParameterValue(BUZZER_SHAPE, iItem);
    break;
  case PLAY_MODE_MENU:
    DropDowns[PLAY_MODE]->item = sItem;
    setParameterValue(PLAY_MODE, iItem);
    break;
  case EMUL_MODE_MENU:
    DropDowns[EMUL_MODE]->item = sItem;
    setParameterValue(EMUL_MODE, iItem);
    break;

  default:
    break;
  }
  mn->hide();
  // todo : should this repaint() ?
}

void UIZynayumi::onCheckBoxClicked(CheckBox *cb, bool isChecked) {
  uint id = cb->getId();
  switch (id) {
  case YM_CHANNEL_ENABLED_0:
    setParameterValue(YM_CHANNEL_ENABLED_0, (float)isChecked);
    break;
  case YM_CHANNEL_ENABLED_1:
    setParameterValue(YM_CHANNEL_ENABLED_1, (float)isChecked);
    break;
  case YM_CHANNEL_ENABLED_2:
    setParameterValue(YM_CHANNEL_ENABLED_2, (float)isChecked);
    break;
  case TONE_RESET:
    setParameterValue(TONE_RESET, (float)isChecked);
    break;
  case TONE_LEGACY_TUNING:
    setParameterValue(TONE_LEGACY_TUNING, (float)isChecked);
    break;
  case RINGMOD_RESET:
    setParameterValue(RINGMOD_RESET, (float)isChecked);
    break;
  case RINGMOD_SYNC:
    setParameterValue(RINGMOD_SYNC, (float)isChecked);
    break;

  default:
    printf("onCheckBoxClicked(%i, %i)\n", id, isChecked);
    break;
  }
}

void UIZynayumi::onSpinnerValueChanged(Spinner *sp, uint value) {
  const uint id = sp->getId();
  switch (id) {
  case PITCH_WHEEL:
    setParameterValue(PITCH_WHEEL, value);
    break;
  case MIDI_CHANNEL_0:
    setParameterValue(MIDI_CHANNEL_0, value);
    break;
  case MIDI_CHANNEL_1:
    setParameterValue(MIDI_CHANNEL_1, value);
    break;
  case MIDI_CHANNEL_2:
    setParameterValue(MIDI_CHANNEL_2, value);
    break;
  default:
    printf("onSpinnerValueChanged(%i, %i)\n", id, value);
    break;
  }
}

void UIZynayumi::onSwitchClicked(Switch *sw, bool lr) {
  uint id = sw->getId();
  printf("switch %i\t lr:%i\n", id, lr);
  switch (id) {
  case BUZZER_ENABLED: {
    if (lr) {
      DropDowns[BUZZER_SHAPE]->setVisible(false);
      for (auto &w : Waveforms)
        w->setVisible(true);
    } else {
      DropDowns[BUZZER_SHAPE]->setVisible(true);
      for (auto &w : Waveforms)
        w->setVisible(false);
    }
    break;
  }
  default:
    break;
  }
}

void UIZynayumi::onTextSpinnerValueChanged(TextSpinner *ts, int value) {
  uint id = ts->getId();
  printf("onTextSpinnerValueChanged(%i,%i)\n", id, value);

  switch (id) {
  case SEQ_TONE_PITCH_0 ... SEQ_TONE_PITCH_15: // TODO :: range bases case
                                               // switch
  {
    const int index = id - SEQ_TONE_PITCH_0;
    seq_tone_pitch[index] = value;
    repaint();
    break;
  }
  case SEQ_NOISE_PERIOD_0 ... SEQ_NOISE_PERIOD_15: // TODO :: range bases case
                                                   // switch
  {
    const int index = id - SEQ_NOISE_PERIOD_0;
    seq_noise_period[index] = value;
    repaint();
    break;
  }

  case SEQ_RINGMOD_PITCH_0 ... SEQ_RINGMOD_PITCH_15: // TODO :: range bases case
                                                     // switch
  {
    const int index = id - SEQ_RINGMOD_PITCH_0;
    seq_ringmod_pitch[index] = value;
    repaint();
    break;
  }
  case SEQ_RINGMOD_DEPTH_0 ... SEQ_RINGMOD_DEPTH_15: // TODO :: range bases case
                                                     // switch
  {
    const int index = id - SEQ_RINGMOD_DEPTH_0;
    seq_ringmod_depth[index] = value;
    repaint();
    break;
  }
  case SEQ_LEVEL_0 ... SEQ_LEVEL_15: // TODO :: range bases case switch
  {
    const int index = id - SEQ_LEVEL_0;
    seq_level[index] = value;
    repaint();
    break;
  }

  default:
    break;
  }
  setParameterValue(id, value);
}

void UIZynayumi::onSeqSpinnerValueChanged(SeqSpinner *sp, uint value) {
  // do stuff
}

UI *createUI() { return new UIZynayumi(); }

// -----------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
