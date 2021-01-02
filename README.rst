Zynayumi
========

Synth based on ayumi, the highly precise emulator of AY-8910 and
YM2149 http://sovietov.com/app/ayumi/ayumi.html.

Features
--------

- [X] Amplitude envelope
- [X] Tone and noise pitch envelope
- [X] Portamento
- [X] Vibrato
- [X] Ring Modulation (SID-like and more)
- [X] Buzzer
- [X] 16-step sequencer for arpegio and other modulation
- [X] MIDI controls assigned to parameters (Modulation, Portamento
      Time, Volume, Pan, Expression and Sustain)
- [X] VST, DSSI, LV2
- [ ] GUI

Demo Songs
----------

* [Monstrosity by A-Lin](https://lbry.tv/@ngeiswei:d/A-Lin---Monstrosity---2020-06-09:f)
* [Hudros Chiphony by A-Lin](https://lbry.tv/@ngeiswei:d/hudros-chiphony_2020-09-02---normalized:1)

If you make a song with Zynayumi let me know so I can include it.

Requirements
------------

- Boost (version 1.54 minimum) http://www.boost.org/

Install
-------

1. Clone the zynayumi repository and its submodules::

     git clone --recurse-submodules https://github.com/zynayumi/zynayumi
     cd zynayumi

   For the rest, if you're using a GNU/Linux system (or perhaps OSX?) you
   can run the following script to build::

     ./build.sh

   then to install::
   
     sudo ./install.sh

   likewise if you wish to uninstall::

     sudo ./uninstall.sh

   Otherwise, follow the remaining instructions below, you may need to
   modify them a bit to suit your operating system.

2. Build libzynayumi::

     cd libzynayumi
     mkdir build
     cd build
     cmake ..
     make -j
     cd ../..

3. Build zynayumi::

     make -j

4. Copy the plugins and executable in the ``bin`` folder to the
   desired destination.

Specification
-------------

For the detail specification of all available parameters, see
https://github.com/zynayumi/libzynayumi

TODO
----

- [ ] Add a GUI

Author(s)
---------

- Nil Geisweiller
