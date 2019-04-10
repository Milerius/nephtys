#!/usr/bin/env bash

function init() {
    root_dir=$PWD
    mkdir deploy_linux
    rm -rf appimage_build && mkdir appimage_build && cd appimage_build
    cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release -DAUTO_BUILD_APPIMAGE=ON ../
}

function deploy_client() {
    cd client
    make nephtys_client -j2
    cd ../
    cp ./bin/nephtys_client-*.AppImage ${root_dir}/deploy_linux/nephtys_client.AppImage
}

function deploy_server() {
    cd server
    make nephtys_server -j2
    cd ../
    cp ./bin/nephtys_server-*.AppImage ${root_dir}/deploy_linux/nephtys_server.AppImage
    cd ../
}

function clean() {
    rm -rf ${root_dir}/appimage_build
}

init
deploy_client
deploy_server
clean