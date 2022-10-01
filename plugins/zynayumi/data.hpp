#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include "Color.hpp"
#include "Geometry.hpp"
#include <unordered_map>
#include <array>

START_NAMESPACE_DISTRHO

// // cpc colors
// static const Color Black(0, 0, 0);
// static const Color Blue(0, 0, 128);
// static const Color BrightBlue(0, 0, 255);
// static const Color Red(128, 0, 0);
// static const Color Magenta(128, 0, 128);
// static const Color Mauve(128, 0, 255);
// static const Color BrightRed(255, 0, 0);
// static const Color Purple(255, 0, 128);
// static const Color BrightMagenta(255, 0, 255);
// static const Color Green(0, 128, 0);
// static const Color Cyan(0, 128, 128);
// static const Color SkyBlue(0, 128, 255);
// static const Color Yellow(128, 128, 0);
// static const Color White(128, 128, 128);
// static const Color PastelBlue(128, 128, 255);
// static const Color Orange(255, 128, 0);
// static const Color Pink(255, 128, 128);
// static const Color PastelMagenta(255, 128, 255);
// static const Color BrightGreen(0, 255, 0);
// static const Color SeaGreen(0, 255, 128);
// static const Color BrightCyan(0, 255, 255);
// static const Color Lime(128, 255, 0);
// static const Color PastelGreen(128, 255, 128);
// static const Color PastelCyan(128, 255, 255);
// static const Color BrightYellow(255, 255, 0);
// static const Color PastelYellow(255, 255, 128);
// static const Color BrightWhite(255, 255, 255);
static const Color floral_white(255, 252, 242);

static const Color pale_silver(204, 197, 185);

static const Color black_olive(64, 61, 57);
static const Color black_olive_1(170, 163, 153);
static const Color black_olive_2(120, 114, 107);
static const Color black_olive_3(31, 27, 22);
static const Color black_olive_4(35, 27, 17);

static const Color eerie_black(37, 36, 34);
static const Color eerie_black_1(154, 150, 140);
static const Color eerie_black_2(101, 98, 92);
static const Color eerie_black_3(23, 20, 16);
static const Color eerie_black_4(26, 21, 12);

static const Color flame(235, 94, 40);
static const Color flame_1(255, 159, 124);
static const Color flame_2(251, 127, 82);
static const Color flame_3(194, 62, 13);
static const Color flame_4(154, 42, 0);

static const Color saffron(235, 190, 40);
static const Color saffron_1(255, 225, 124);
static const Color saffron_2(251, 212, 82);
static const Color saffron_3(194, 153, 13);
static const Color saffron_4(154, 118, 0);

static const Color blue_pigment(55, 47, 164);
static const Color blue_pigment_1(116, 110, 198);
static const Color blue_pigment_2(81, 73, 175);
static const Color blue_pigment_3(35, 27, 135);
static const Color blue_pigment_4(21, 14, 107);

static const Color shamrock_green(28, 162, 101);
static const Color shamrock_green_1(95, 197, 151);
static const Color shamrock_green_2(57, 173, 120);
static const Color shamrock_green_3(9, 134, 77);
static const Color shamrock_green_4(0, 106, 58);
static const Color cadet_blue(74, 156, 160);
static const Color cadet_blue_1(175, 225, 227);
static const Color cadet_blue_2(119, 192, 196);
static const Color cadet_blue_3(47, 134, 138);
static const Color cadet_blue_4(23, 117, 121);

static const Color alex_grey(194, 194, 194);
static const Color white(255, 255, 255);

static const unsigned int UI_WIDTH = 1000;
static const unsigned int UI_HEIGHT = 790;

enum params
{
    EMUL_MODE,

    // Play mode
    PLAY_MODE,

    // Tone
    TONE_RESET,
    TONE_PHASE,
    TONE_TIME,
    TONE_DETUNE,
    TONE_TRANSPOSE,
    TONE_SPREAD,
    TONE_LEGACY_TUNING,

    // Noise
    NOISE_TIME,
    NOISE_PERIOD,

    // Noise Period Envelope
    NOISE_PERIOD_ENV_ATTACK,
    NOISE_PERIOD_ENV_TIME,

    // Envelope
    ENV_ATTACK_TIME,
    ENV_HOLD1_LEVEL,
    ENV_INTER1_TIME,
    ENV_HOLD2_LEVEL,
    ENV_INTER2_TIME,
    ENV_HOLD3_LEVEL,
    ENV_DECAY_TIME,
    ENV_SUSTAIN_LEVEL,
    ENV_RELEASE,

    // Pitch envelope
    PITCH_ENV_ATTACK_PITCH,
    PITCH_ENV_TIME,
    PITCH_ENV_SMOOTHNESS,

    // Ring modulation
    RINGMOD_WAVEFORM_LEVEL1,
    RINGMOD_WAVEFORM_LEVEL2,
    RINGMOD_WAVEFORM_LEVEL3,
    RINGMOD_WAVEFORM_LEVEL4,
    RINGMOD_WAVEFORM_LEVEL5,
    RINGMOD_WAVEFORM_LEVEL6,
    RINGMOD_WAVEFORM_LEVEL7,
    RINGMOD_WAVEFORM_LEVEL8,
    RINGMOD_WAVEFORM_LEVEL9,
    RINGMOD_WAVEFORM_LEVEL10,
    RINGMOD_WAVEFORM_LEVEL11,
    RINGMOD_WAVEFORM_LEVEL12,
    RINGMOD_WAVEFORM_LEVEL13,
    RINGMOD_WAVEFORM_LEVEL14,
    RINGMOD_WAVEFORM_LEVEL15,
    RINGMOD_WAVEFORM_LEVEL16,
    RINGMOD_RESET,
    RINGMOD_SYNC,
    RINGMOD_PHASE,
    RINGMOD_LOOP,
    RINGMOD_DETUNE,
    RINGMOD_TRANSPOSE,
    RINGMOD_FIXED_PITCH,
    RINGMOD_FIXED_VS_RELATIVE,
    RINGMOD_DEPTH,

    // Buzzer
    BUZZER_ENABLED,
    BUZZER_SHAPE,

    // Sequencer
    SEQ_TONE_PITCH_0,
    SEQ_TONE_PITCH_1,
    SEQ_TONE_PITCH_2,
    SEQ_TONE_PITCH_3,
    SEQ_TONE_PITCH_4,
    SEQ_TONE_PITCH_5,
    SEQ_TONE_PITCH_6,
    SEQ_TONE_PITCH_7,
    SEQ_TONE_PITCH_8,
    SEQ_TONE_PITCH_9,
    SEQ_TONE_PITCH_10,
    SEQ_TONE_PITCH_11,
    SEQ_TONE_PITCH_12,
    SEQ_TONE_PITCH_13,
    SEQ_TONE_PITCH_14,
    SEQ_TONE_PITCH_15,
    SEQ_NOISE_PERIOD_0,
    SEQ_NOISE_PERIOD_1,
    SEQ_NOISE_PERIOD_2,
    SEQ_NOISE_PERIOD_3,
    SEQ_NOISE_PERIOD_4,
    SEQ_NOISE_PERIOD_5,
    SEQ_NOISE_PERIOD_6,
    SEQ_NOISE_PERIOD_7,
    SEQ_NOISE_PERIOD_8,
    SEQ_NOISE_PERIOD_9,
    SEQ_NOISE_PERIOD_10,
    SEQ_NOISE_PERIOD_11,
    SEQ_NOISE_PERIOD_12,
    SEQ_NOISE_PERIOD_13,
    SEQ_NOISE_PERIOD_14,
    SEQ_NOISE_PERIOD_15,
    SEQ_RINGMOD_PITCH_0,
    SEQ_RINGMOD_PITCH_1,
    SEQ_RINGMOD_PITCH_2,
    SEQ_RINGMOD_PITCH_3,
    SEQ_RINGMOD_PITCH_4,
    SEQ_RINGMOD_PITCH_5,
    SEQ_RINGMOD_PITCH_6,
    SEQ_RINGMOD_PITCH_7,
    SEQ_RINGMOD_PITCH_8,
    SEQ_RINGMOD_PITCH_9,
    SEQ_RINGMOD_PITCH_10,
    SEQ_RINGMOD_PITCH_11,
    SEQ_RINGMOD_PITCH_12,
    SEQ_RINGMOD_PITCH_13,
    SEQ_RINGMOD_PITCH_14,
    SEQ_RINGMOD_PITCH_15,
    SEQ_RINGMOD_DEPTH_0,
    SEQ_RINGMOD_DEPTH_1,
    SEQ_RINGMOD_DEPTH_2,
    SEQ_RINGMOD_DEPTH_3,
    SEQ_RINGMOD_DEPTH_4,
    SEQ_RINGMOD_DEPTH_5,
    SEQ_RINGMOD_DEPTH_6,
    SEQ_RINGMOD_DEPTH_7,
    SEQ_RINGMOD_DEPTH_8,
    SEQ_RINGMOD_DEPTH_9,
    SEQ_RINGMOD_DEPTH_10,
    SEQ_RINGMOD_DEPTH_11,
    SEQ_RINGMOD_DEPTH_12,
    SEQ_RINGMOD_DEPTH_13,
    SEQ_RINGMOD_DEPTH_14,
    SEQ_RINGMOD_DEPTH_15,
    SEQ_LEVEL_0,
    SEQ_LEVEL_1,
    SEQ_LEVEL_2,
    SEQ_LEVEL_3,
    SEQ_LEVEL_4,
    SEQ_LEVEL_5,
    SEQ_LEVEL_6,
    SEQ_LEVEL_7,
    SEQ_LEVEL_8,
    SEQ_LEVEL_9,
    SEQ_LEVEL_10,
    SEQ_LEVEL_11,
    SEQ_LEVEL_12,
    SEQ_LEVEL_13,
    SEQ_LEVEL_14,
    SEQ_LEVEL_15,
    SEQ_TONE_ON_0,
    SEQ_TONE_ON_1,
    SEQ_TONE_ON_2,
    SEQ_TONE_ON_3,
    SEQ_TONE_ON_4,
    SEQ_TONE_ON_5,
    SEQ_TONE_ON_6,
    SEQ_TONE_ON_7,
    SEQ_TONE_ON_8,
    SEQ_TONE_ON_9,
    SEQ_TONE_ON_10,
    SEQ_TONE_ON_11,
    SEQ_TONE_ON_12,
    SEQ_TONE_ON_13,
    SEQ_TONE_ON_14,
    SEQ_TONE_ON_15,
    SEQ_NOISE_ON_0,
    SEQ_NOISE_ON_1,
    SEQ_NOISE_ON_2,
    SEQ_NOISE_ON_3,
    SEQ_NOISE_ON_4,
    SEQ_NOISE_ON_5,
    SEQ_NOISE_ON_6,
    SEQ_NOISE_ON_7,
    SEQ_NOISE_ON_8,
    SEQ_NOISE_ON_9,
    SEQ_NOISE_ON_10,
    SEQ_NOISE_ON_11,
    SEQ_NOISE_ON_12,
    SEQ_NOISE_ON_13,
    SEQ_NOISE_ON_14,
    SEQ_NOISE_ON_15,
    SEQ_TEMPO,
    SEQ_HOST_SYNC,
    SEQ_BEAT_DIVISOR,
    SEQ_BEAT_MULTIPLIER,
    SEQ_LOOP,
    SEQ_END,

    // Pitch LFO
    LFO_SHAPE,
    LFO_FREQ,
    LFO_DELAY,
    LFO_DEPTH,

    // Portamento time
    PORTAMENTO_TIME,
    PORTAMENTO_SMOOTHNESS,

    // Enabled YM Channel
    YM_CHANNEL_ENABLED_0,
    YM_CHANNEL_ENABLED_1,
    YM_CHANNEL_ENABLED_2,

    // Pan
    PAN_0,
    PAN_1,
    PAN_2,

    // Gain
    GAIN,

    // Control
    PITCH_WHEEL,
    VELOCITY_SENSITIVITY,
    RINGMOD_VELOCITY_SENSITIVITY,
    NOISE_PERIOD_PITCH_SENSITIVITY,
    MODULATION_SENSITIVITY,
    MIDI_CHANNEL_0,
    MIDI_CHANNEL_1,
    MIDI_CHANNEL_2,

    // Oversampling
    OVERSAMPLING,

    OUTPUT_LEFT,
    OUTPUT_RIGHT,

    // Number of Parameters
    PARAMETERS_COUNT,

    // Menu
    EMUL_MODE_MENU,
    PLAY_MODE_MENU,
    LFO_SHAPE_MENU,
    RINGMOD_LOOP_MENU,
    BUZZER_SHAPE_MENU,
};

// Parameter ranges
#define TONE_RESET_L 0.0f
#define TONE_RESET_U 1.0f
#define TONE_PHASE_L 0.0f
#define TONE_PHASE_U 1.0f
#define TONE_TIME_L 0.0f
#define TONE_TIME_L_ALT -1.0f // In case infinity isn't supported
#define TONE_TIME_U std::numeric_limits<float>::infinity()
#define TONE_TIME_U_ALT 10.0f // In case infinity isn't supported
#define TONE_DETUNE_L -0.5f
#define TONE_DETUNE_U 0.5f
#define TONE_TRANSPOSE_L -36
#define TONE_TRANSPOSE_U 36
#define TONE_SPREAD_L 0
#define TONE_SPREAD_U 0.5
#define TONE_LEGACY_TUNING_L 0
#define TONE_LEGACY_TUNING_U 1
#define NOISE_TIME_L 0.0f
#define NOISE_TIME_L_ALT -1.0f // In case infinity isn't supported
#define NOISE_TIME_U std::numeric_limits<float>::infinity()
#define NOISE_TIME_U_ALT 10.0f // In case infinity isn't supported
#define NOISE_PERIOD_L 1
#define NOISE_PERIOD_U 31
#define NOISE_PERIOD_ENV_ATTACK_L 1
#define NOISE_PERIOD_ENV_ATTACK_U 31
#define NOISE_PERIOD_ENV_TIME_L 0.0f
#define NOISE_PERIOD_ENV_TIME_U 10.0f
#define ENV_ATTACK_TIME_L 0.0f
#define ENV_ATTACK_TIME_U 10.0f
#define ENV_HOLD1_LEVEL_L 0
#define ENV_HOLD1_LEVEL_U 15 // MAX_LEVEL
#define ENV_INTER1_TIME_L 0.0f
#define ENV_INTER1_TIME_U 10.0f
#define ENV_HOLD2_LEVEL_L 0
#define ENV_HOLD2_LEVEL_U 15 // MAX_LEVEL
#define ENV_INTER2_TIME_L 0.0f
#define ENV_INTER2_TIME_U 10.0f
#define ENV_HOLD3_LEVEL_L 0
#define ENV_HOLD3_LEVEL_U 15 // MAX_LEVEL
#define ENV_DECAY_TIME_L 0.0f
#define ENV_DECAY_TIME_U 10.0f
#define ENV_SUSTAIN_LEVEL_L 0
#define ENV_SUSTAIN_LEVEL_U 15 // MAX_LEVEL
#define ENV_RELEASE_L 0.0f
#define ENV_RELEASE_U 10.0f
#define PITCH_ENV_ATTACK_PITCH_L -96.0f
#define PITCH_ENV_ATTACK_PITCH_U 96.0f
#define PITCH_ENV_TIME_L 0.0f
#define PITCH_ENV_TIME_U 10.0f
#define PITCH_ENV_SMOOTHNESS_L 0.0f
#define PITCH_ENV_SMOOTHNESS_U 1.0f
#define RINGMOD_WAVEFORM_LEVEL_L 0
#define RINGMOD_WAVEFORM_LEVEL_U 15 // MAX_LEVEL
#define RINGMOD_RESET_L 0.0f
#define RINGMOD_RESET_U 1.0f
#define RINGMOD_SYNC_L 0.0f
#define RINGMOD_SYNC_U 1.0f
#define RINGMOD_PHASE_L 0.0f
#define RINGMOD_PHASE_U 1.0f
#define RINGMOD_DETUNE_L -0.5f
#define RINGMOD_DETUNE_U 0.5f
#define RINGMOD_TRANSPOSE_L -36
#define RINGMOD_TRANSPOSE_U 36
#define RINGMOD_FIXED_PITCH_L 0.0f
#define RINGMOD_FIXED_PITCH_U 127.0f
#define RINGMOD_FIXED_VS_RELATIVE_L 0.0f
#define RINGMOD_FIXED_VS_RELATIVE_U 1.0f
#define RINGMOD_DEPTH_L 0
#define RINGMOD_DEPTH_U 15 // MAX_LEVEL
#define BUZZER_ENABLED_L 0.0f
#define BUZZER_ENABLED_U 1.0f
#define SEQ_TONE_PITCH_L -48
#define SEQ_TONE_PITCH_U 48
#define SEQ_NOISE_PERIOD_L -15
#define SEQ_NOISE_PERIOD_U 15
#define SEQ_RINGMOD_PITCH_L -48
#define SEQ_RINGMOD_PITCH_U 48
#define SEQ_RINGMOD_DEPTH_L 0
#define SEQ_RINGMOD_DEPTH_U 15 // MAX_LEVEL
#define SEQ_LEVEL_L 0
#define SEQ_LEVEL_U MAX_LEVEL
#define SEQ_TEMPO_L 30.0
#define SEQ_TEMPO_U 300.0
#define SEQ_HOST_SYNC_L 0
#define SEQ_HOST_SYNC_U 1
#define SEQ_BEAT_DIVISOR_L 1
#define SEQ_BEAT_DIVISOR_U 64
#define SEQ_BEAT_MULTIPLIER_L 1
#define SEQ_BEAT_MULTIPLIER_U 64
#define SEQ_LOOP_L 0
#define SEQ_LOOP_U 16
#define SEQ_END_L 0
#define SEQ_END_U 16
#define LFO_FREQ_L 0.0f
#define LFO_FREQ_U 20.0f
#define LFO_DELAY_L 0.0f
#define LFO_DELAY_U 10.0f
#define LFO_DEPTH_L 0.0f
#define LFO_DEPTH_U 12.0f
#define PORTAMENTO_TIME_L 0.0f
#define PORTAMENTO_TIME_U 2.0f
#define PORTAMENTO_SMOOTHNESS_L 0.0f
#define PORTAMENTO_SMOOTHNESS_U 1.0f
#define GAIN_L 0.0f
#define GAIN_U 2.0f
#define PAN_L 0.0f
#define PAN_U 1.0f
#define PITCH_WHEEL_L 1
#define PITCH_WHEEL_U 12
#define VELOCITY_SENSITIVITY_L 0.0f
#define VELOCITY_SENSITIVITY_U 1.0f
#define RINGMOD_VELOCITY_SENSITIVITY_L 0.0f
#define RINGMOD_VELOCITY_SENSITIVITY_U 1.0f
#define NOISE_PERIOD_PITCH_SENSITIVITY_L 0.0f
#define NOISE_PERIOD_PITCH_SENSITIVITY_U 1.0f
#define MODULATION_SENSITIVITY_L 0.0f
#define MODULATION_SENSITIVITY_U 12.0f
#define OVERSAMPLING_L 1
#define OVERSAMPLING_U 4

enum boxes
{
    TOP_BAR = PARAMETERS_COUNT,
    GLOBAL,
    TONE,
    SEQUENCER,
    ENVELOPE,
    LFO_PITCH_ENV,
    RINGMOD,
    BOXES_COUNT
};

struct Box
{
    boxes id;
    int x, y, w, h;
    int stroke_width;
    Color fill_color;
    Color stroke_color;
};

const Box boxData[]{
    {TOP_BAR, 0, 0, 1000, 42, 3, eerie_black, eerie_black},
    {GLOBAL, 0, 42, 1000, 140, 3, cadet_blue, Color(194, 194, 194)}, // TODO: or 194,194,194?
    {TONE, 0, 180, 315, 272, 3, flame, Color(194, 194, 194)},
    {LFO_PITCH_ENV, 0, 449, 315, 340, 3, shamrock_green, Color(194, 194, 194)},
    {ENVELOPE, 684, 180, 315, 272, 3, blue_pigment_1, Color(194, 194, 194)},
    {RINGMOD, 684, 449, 315, 340, 3, saffron_3, Color(194, 194, 194)},
    {SEQUENCER, 312, 180, 375, 609, 3, blue_pigment, Color(194, 194, 194)},
};

struct BoxLabel
{
    const char *label; // centered in box
    int x, y, w, h;    // background box
    int font_size;
};

const BoxLabel boxLabelData[]{
    {"SENSITIVITY", 471, 45, 95, 20, 20},
    {"PORTAMENTO", 705, 45, 109, 20, 20},
    {"TONE", 0, 183, 62, 27, 27},
    {"SEQUENCER", 314, 181, 123, 27, 27},
    {"ENVELOPE", 888, 181, 110, 27, 27},
    {"NOISE", 0, 316, 57, 24, 24},
    {"ENV", 156, 316, 44, 24, 24},
    {"LFO", 0, 452, 46, 27, 27},
    {"RING MOD", 687, 452, 123, 27, 27},
    {"PITCH ENV", 0, 572, 113, 27, 27},
    {"WAVEFORM", 795, 663, 102, 20, 20},
    {"BUZZER", 925, 663, 73, 20, 20},

};

struct Line
{
    int x, y, w, h;
};

const Line lineData[]{
    {470, 45, 3, 136},
    {705, 45, 3, 136},
    {850, 45, 3, 136},
    {0, 313, 314, 3},
    {155, 314, 3, 136},
    {0, 569, 313, 3},
    {687, 661, 312, 3},
};

struct KnobData
{
    const char *label;
    int x;
    int y;
    int w;
    int h;
    Color background_color;
    Color foreground_color;
    Color highlight_color;
    float margin;
    float default_value;
    float step_value;
    float min;
    float max;
    float real_min;
    float real_max;
    const char *format_str; // also include unit !
    bool using_log;
    bool is_centered;
};

const std::unordered_map<params, KnobData>
    knobData{
        // Global
        {VELOCITY_SENSITIVITY, {"VELOCITY", 492, 93, 41, 41, cadet_blue, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {NOISE_PERIOD_PITCH_SENSITIVITY, {"NOISE PER", 566, 93, 41, 41, cadet_blue, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {MODULATION_SENSITIVITY, {"PITCH", 643, 93, 41, 41, cadet_blue, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        //   {RINGMOD_VELOCITY_SENSITIVITY, {"RINGMOD", 528, 430,41,41, cadet_blue, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {PORTAMENTO_TIME, {"TIME", 729, 93, 41, 41, cadet_blue, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {PORTAMENTO_SMOOTHNESS, {"SMOOTH", 789, 93, 41, 41, cadet_blue, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {GAIN, {"GAIN", 868, 93, 41, 41, cadet_blue, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        // Tone
        {TONE_PHASE, {"PHASE", 16, 233, 41, 41, flame, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {TONE_TIME, {"TIME", 78, 233, 41, 41, flame, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {TONE_DETUNE, {"DETUNE", 139, 233, 41, 41, flame, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {TONE_TRANSPOSE, {"TRANSP", 200, 233, 41, 41, flame, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {TONE_SPREAD, {"SPREAD", 261, 233, 41, 41, flame, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        // Noise
        {NOISE_PERIOD, {"PERIOD", 22, 361, 41, 41, flame, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {NOISE_TIME, {"TIME", 93, 361, 41, 41, flame, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        // Noise Period Enve
        {NOISE_PERIOD_ENV_ATTACK, {"ATTACK", 179, 361, 41, 41, flame, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {NOISE_PERIOD_ENV_TIME, {"TIME", 253, 361, 41, 41, flame, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        // Envelope
        {ENV_ATTACK_TIME, {"ATTACK", 702, 233, 41, 41, blue_pigment_1, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {ENV_INTER1_TIME, {"TIME 1", 761, 233, 41, 41, blue_pigment_1, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {ENV_INTER2_TIME, {"TIME 2", 820, 233, 41, 41, blue_pigment_1, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {ENV_DECAY_TIME, {"DECAY", 879, 233, 41, 41, blue_pigment_1, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {ENV_RELEASE, {"RELEASE", 938, 233, 41, 41, blue_pigment_1, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {ENV_HOLD1_LEVEL, {"L1", 730, 303, 41, 41, blue_pigment_1, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {ENV_HOLD2_LEVEL, {"L2", 790, 303, 41, 41, blue_pigment_1, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {ENV_HOLD3_LEVEL, {"L3", 850, 303, 41, 41, blue_pigment_1, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {ENV_SUSTAIN_LEVEL, {"SUS", 907, 303, 41, 41, blue_pigment_1, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        // LFO
        {LFO_FREQ, {"FREQ", 48, 492, 41, 41, shamrock_green, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {LFO_DELAY, {"DELAY", 139, 492, 41, 41, shamrock_green, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {LFO_DEPTH, {"DEPTH", 228, 492, 41, 41, shamrock_green, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        // Pitch envelope
        {PITCH_ENV_ATTACK_PITCH, {"ATK PITCH", 48, 615, 41, 41, shamrock_green, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {PITCH_ENV_TIME, {"TIME", 139, 615, 41, 41, shamrock_green, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {PITCH_ENV_SMOOTHNESS, {"SMOOTH", 228, 615, 41, 41, shamrock_green, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        // Ring modulation
        {RINGMOD_PHASE, {"PHASE", 729, 519, 41, 41, saffron_3, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {RINGMOD_DETUNE, {"DETUNE", 823, 519, 41, 41, saffron_3, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {RINGMOD_TRANSPOSE, {"TRANS", 914, 519, 41, 41, saffron_3, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {RINGMOD_FIXED_PITCH, {"FIX PITCH", 729, 587, 41, 41, saffron_3, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {RINGMOD_DEPTH, {"DEPTH", 823, 587, 41, 41, saffron_3, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},
        {RINGMOD_FIXED_VS_RELATIVE, {"FIX - REL", 914, 587, 41, 41, saffron_3, alex_grey, floral_white, 3.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, "", false, false}},

    };

struct CheckBoxData
{
    const char *label;
    int x, y, w, h;
    Color active_color;
    Color highlight_color;
};

const std::unordered_map<params, CheckBoxData> checkBoxData{
    {YM_CHANNEL_ENABLED_0, {"VOICE 1", 80, 96, 14, 14, cadet_blue, saffron}},
    {YM_CHANNEL_ENABLED_1, {"VOICE 2", 80, 119, 14, 14, cadet_blue, saffron}},
    {YM_CHANNEL_ENABLED_2, {"VOICE 3", 80, 140, 14, 14, cadet_blue, saffron}},
    {TONE_RESET, {"RESET", 143, 193, 14, 14, flame, saffron}},
    {TONE_LEGACY_TUNING, {"LEGACY TUNING", 282, 193, 14, 14, flame, saffron}},
    {RINGMOD_RESET, {"RESET", 766, 490, 14, 14, saffron, saffron_1}},
    {RINGMOD_SYNC, {"SYNC", 841, 490, 14, 14, saffron, saffron_1}},

};

struct SliderData
{
    const char *label;
    int x, y, w, h;
    Color background_color;
    Color foreground_color;
    Color highlight_color;
};

const std::unordered_map<params, SliderData> sliderData{};

struct PannerData
{
    const char *label;
    int x, y, w, h;
    Color background_color;
    Color foreground_color;
    Color highlight_color;
};

const std::unordered_map<params, PannerData> pannerData{
    {PAN_0, {"PAN", 296, 96, 151, 14, alex_grey, cadet_blue, cadet_blue_1}},
    {PAN_1, {"PAN", 296, 118, 151, 14, alex_grey, cadet_blue, cadet_blue_1}},
    {PAN_2, {"PAN", 296, 141, 151, 14, alex_grey, cadet_blue, cadet_blue_1}},
};

struct SpinnerData
{
    const char *label;
    int x, y, w, h;
    Color background_color;
    Color foreground_color;
    Color text_color;
};

const std::unordered_map<params, SpinnerData> spinnerData{
    {PITCH_WHEEL, {"PITCH BEND", 410, 61, 37, 14, Color(255, 255, 255), shamrock_green, eerie_black}},
    {MIDI_CHANNEL_0, {"MIDI CH", 184, 96, 37, 14, Color(255, 255, 255), shamrock_green, eerie_black}},
    {MIDI_CHANNEL_1, {"MIDI CH", 184, 118, 37, 14, Color(255, 255, 255), shamrock_green, eerie_black}},
    {MIDI_CHANNEL_2, {"MIDI CH", 184, 141, 37, 14, Color(255, 255, 255), shamrock_green, eerie_black}},
};

struct DropDownData
{
    const char *label;
    const char *item;
    int x, y, w, h;
    Color background_color;
    Color foreground_color;
    Color text_color;
};

const std::unordered_map<params, DropDownData> dropDownData{

    {EMUL_MODE, {"CHIP", "YM-2149", 60, 61, 59, 14, white, cadet_blue, eerie_black}},
    {PLAY_MODE, {"PLAY MODE", "UnisonRandArp", 215, 61, 89, 14, white, cadet_blue, eerie_black}},
    {LFO_SHAPE, {"SHAPE", "PINGPONG", 238, 459, 66, 14, white, shamrock_green, eerie_black}},
    {RINGMOD_LOOP, {"LOOP", "Off", 908, 489, 66, 14, white, saffron, eerie_black}},
    // special case SHAPE label , because of BUZZER_ON switch
    {BUZZER_SHAPE, {" ", "DOWNSAW", 833, 731, 60, 14, white, saffron, eerie_black}},
};
struct MenuData
{
    int x, y, w, h;
    Color background_color;
    Color foreground_color;
    Color highlight_color;
    Color text_color;
};

const std::unordered_map<params, MenuData> menuData{
    {EMUL_MODE_MENU, {61, 76, 60, 14, white, cadet_blue, cadet_blue_1, eerie_black}},
    {PLAY_MODE_MENU, {215, 75, 60, 14, white, cadet_blue, cadet_blue_1, eerie_black}},
    {LFO_SHAPE_MENU, {238, 449 + 15, 50, 14, white, shamrock_green, shamrock_green_1, eerie_black}},
    {RINGMOD_LOOP_MENU, {909, 503, 60, 14, white, saffron_1, saffron_2, eerie_black}},
    {BUZZER_SHAPE_MENU, {833, 731 + 15, 60, 14, white, saffron_1, saffron_2, eerie_black}},
};

END_NAMESPACE_DISTRHO

#endif
