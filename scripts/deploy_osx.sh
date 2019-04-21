#!/usr/bin/env bash

function init() {
    root_dir=$(pwd)
    mkdir deploy_osx
    cd /tmp && rm -rf release_osx && mkdir release_osx && cd release_osx
    conan install ${root_dir}/.conan/osx
    cmake -DCMAKE_BUILD_TYPE=Release ${root_dir}
}

function deploy_launcher() {
    cpack -G OSXX11
    cp *.dmg ${root_dir}/deploy_osx
}

init
deploy_launcher
cd ${root_dir}
