#!/usr/bin/env bash

function init() {
    root_dir=$PWD
    mkdir deploy_linux
    rm -rf appimage_build
    mkdir appimage_build
    cd appimage_build
    conan install ../
    cmake .. -DCMAKE_INSTALL_PREFIX=/usr
    wget https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
    chmod +x linuxdeploy-x86_64.AppImage
    export PATH=$PATH:$PWD
}

function deploy_client() {
    cd client
    make nephtys_client -j2
    make install DESTDIR=AppDir
    linuxdeploy-x86_64.AppImage --appdir AppDir --output appimage
    cp ./*.AppImage ${root_dir}/deploy_linux/nephtys_client.AppImage
}

function clean() {
    rm -rf ${root_dir}/appimage_build
}

init
deploy_client
clean