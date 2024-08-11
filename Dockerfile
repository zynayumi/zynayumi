FROM archlinux
RUN pacman -Syyu --noconfirm
RUN pacman -S --noconfirm git
RUN pacman -S --noconfirm gcc
RUN pacman -S --noconfirm make
RUN pacman -S --noconfirm cmake
RUN pacman -S --noconfirm boost
RUN pacman -S --noconfirm pkgconf
RUN git clone --recurse-submodules https://github.com/zynayumi/zynayumi
WORKDIR zynayumi
RUN ./build.sh
