#!/usr/bin/env bash

function conan_setup_linux_clang() {
         cd /tmp
         git clone https://github.com/bincrafters/conan-sfml.git
         cd conan-sfml
         conan create . bincrafters/stable
         cd ${TRAVIS_BUILD_DIR}
}

function conan_setup_linux() {
     # profile conan
     conan profile new default --detect
     conan profile update settings.compiler=${DEFAULT_COMPILER} default
     conan profile update settings.compiler.version=${CONAN_COMPILER_VERSION} default
     conan profile update settings.compiler.libcxx=libstdc++11 default
     if [[ "${DEFAULT_COMPILER}" == "clang" ]]; then conan_setup_linux_clang; fi
}

function conan_setup() {
      ${PIP} install conan
      conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
      conan remote add skypjack https://api.bintray.com/conan/skypjack/conan
      conan remote add conan-doom_strong_types https://api.bintray.com/conan/milerius/doom_strong_types
      if [[ "${TRAVIS_OS_NAME}" == "linux" ]]; then conan_setup_linux; fi
}

function last_cmake_linux() {
          DEPS_DIR="${TRAVIS_BUILD_DIR}/deps"
          mkdir ${DEPS_DIR} && cd ${DEPS_DIR}
          CMAKE_URL="https://cmake.org/files/v3.14/cmake-3.14.0-Linux-x86_64.tar.gz"
          mkdir cmake && travis_retry wget --no-check-certificate --quiet -O - ${CMAKE_URL} | tar --strip-components=1 -xz -C cmake
          export PATH=${DEPS_DIR}/cmake/bin:${PATH}
          cd -
}

function coverage_setup() {
    gem install coveralls-lcov
    if [[ "${TRAVIS_OS_NAME}" == "linux" ]]; then
       sudo update-alternatives --install /usr/bin/gcov gcov /usr/bin/${COVERAGE_TOOL} 100
       cd /tmp
       curl -sL https://github.com/linux-test-project/lcov/releases/download/v1.14/lcov-1.14.tar.gz | tar xz
       sudo make -C lcov-1.14 install
       cd -
    elif [[ "${TRAVIS_OS_NAME}" == "osx" ]]; then
       brew install lcov
    fi
}

function setup_osx() {
    export PATH="/usr/local/opt/llvm/bin:$PATH"
    sudo installer -pkg /Library/Developer/CommandLineTools/Packages/macOS_SDK_headers_for_macOS_10.14.pkg -target /
}

if [[ "${TRAVIS_OS_NAME}" == "osx" ]]; then setup_osx || travis_terminate 1; fi
if [[ "${WILL_COMPILE_CODE}" == "ON" ]]; then conan_setup || travis_terminate 1; fi
if [[ "${WILL_COMPILE_CODE}" == "ON" ]] && [[ "${TRAVIS_OS_NAME}" == "linux" ]] && [[ "${DEFAULT_COMPILER}" == "gcc" ]] ; then sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/${CXX} 100; fi
if [[ "${TRAVIS_OS_NAME}" == "linux" ]] && [[ "${WILL_COMPILE_CODE}" == "ON" ]]; then last_cmake_linux; fi
if [[ "${NEPHTYS_BUILD_DOCUMENTATION}" == "ON" ]]; then ${PIP} install sphinx breathe || travis_terminate 1; fi
if [[ -n "${CODE_COVERAGE}" ]]; then coverage_setup || travis_terminate 1; fi