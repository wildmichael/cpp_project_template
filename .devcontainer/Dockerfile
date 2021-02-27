# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.158.0/containers/cpp/.devcontainer/base.Dockerfile

# [Choice] Debian / Ubuntu version: debian-10, debian-9, ubuntu-20.04, ubuntu-18.04
ARG VARIANT="buster"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y upgrade --no-install-recommends \
    && apt-get -y install --no-install-recommends \
    clang-format \
    graphviz \
    doxygen \
    pkg-config \
    ninja-build \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

USER vscode

RUN git clone https://github.com/microsoft/vcpkg.git /home/vscode/vcpkg \
    && /home/vscode/vcpkg/bootstrap-vcpkg.sh

# HACK to remove /bin from the PATH. The /usr merge (see
# https://www.freedesktop.org/wiki/Software/systemd/TheCaseForTheUsrMerge/)
# makes /bin a symlink to /usr/bin. The CMake Tools when scanning for a kit
# seem to prefer /bin/clang, but then CMake seems to create wrong paths for the
# system headers in the dependency files which are relative to /bin and not
# /usr/bin, and things break badly, always causing full rebuilds.
ENV PATH="/usr/local/sbin:/usr/local/sbin:/usr/bin"
# Add vcpkg and the vcpkg-shipped cmake to the PATH
ENV PATH="/home/vscode/vcpkg:/home/vscode/vcpkg/downloads/tools/cmake-3.20.1-linux/cmake-3.20.1-linux-x86_64/bin:${PATH}"
