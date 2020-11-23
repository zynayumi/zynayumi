Zynayumi
========

TODO

Requirements
------------

- https://www.boost.org

Install
-------

1. Clone the zynayumi repository and its submodules::

     git clone --recurse-submodules https://github.com/zynayumi/zynayumi

   For the rest, if you're using a GNU/Linux system (or perhaps OSX?) you
   can run the following script to build::

     ./build.sh

   then to install::
   
     sudo ./install.sh

   likewise if you wish to uninstall::

     sudo ./uninstall.sh

   Otherwise, follow the remaining instructions below, you may need to
   modify them a bit to suits your operating system.

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
