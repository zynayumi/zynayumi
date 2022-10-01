#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = zynayumi

# --------------------------------------------------------------
# Files to build

FILES_DSP = \
	PluginZynayumi.cpp

FILES_UI = \
	UIZynayumi.cpp \
	widgets/src/TextButton.cpp \
	widgets/src/ScrollBar.cpp \
	widgets/src/Knob.cpp \
	widgets/src/DropDown.cpp \
	widgets/src/Menu.cpp \
	widgets/src/Slider.cpp \
	widgets/src/HBox.cpp \
	widgets/src/VBox.cpp \
	widgets/src/PopUp.cpp \
	widgets/src/CheckBox.cpp \
	widgets/src/Panner.cpp \
	widgets/src/Spinner.cpp \
	widgets/src/EG.cpp \
	widgets/src/Waveform.cpp \
	widgets/src/Switch.cpp \
	widgets/src/TextSpinner.cpp \
	widgets/src/SeqSpinner.cpp \
	widgets/src/SeqSlider.cpp \
	SVGImage.cpp \
	Artwork.cpp \
	Fonts.cpp
	
# --------------------------------------------------------------
# Do some magic

include ../../dpf/Makefile.plugins.mk

# --------------------------------------------------------------
# Extra flags

LINK_FLAGS += -lpthread -L../../libzynayumi/build/src/zynayumi -lzynayumi \
	$(shell $(PKG_CONFIG) --libs fmt) 
BASE_FLAGS += -I. -I./widgets -I../../nanosvg/src/

# --------------------------------------------------------------
# Enable all possible plugin types

ifeq ($(HAVE_JACK),true)
TARGETS += jack
endif

TARGETS += dssi_dsp
ifeq ($(HAVE_DGL),true)
ifeq ($(HAVE_LIBLO),true)
TARGETS += dssi_ui
endif
endif

ifeq ($(HAVE_DGL),true)
TARGETS += lv2_sep
else
TARGETS += lv2_dsp
endif

TARGETS += vst

all: $(TARGETS)

# --------------------------------------------------------------
