#!/usr/bin/env bash

export VERSION=$(tail -n 1 VERSION.md)

function init() {
    root_dir=$(pwd)
    mkdir deploy_linux
    rm -rf appimage_build && mkdir appimage_build && cd appimage_build
    conan install ../
    cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release -DAUTO_BUILD_APPIMAGE=ON ../
}

function deploy_client() {
    cd client
    make nephtys_client -j2
    cd ../
    cp ./bin/nephtys_client-*.AppImage ${root_dir}/deploy_linux/
}

function deploy_server() {
    cd server
    make nephtys_server -j2
    cd ../
    cp ./bin/nephtys_server-*.AppImage ${root_dir}/deploy_linux/
    cd ../
}

function clean() {
    rm -rf ${root_dir}/appimage_build
}

init
deploy_client
deploy_server
clean
