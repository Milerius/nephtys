#!/usr/bin/env bash

function build_doc() {
    cd ${TRAVIS_BUILD_DIR}/docs
    make html
    cd -
}

doctest_upload_name="Doctest [travis-ci ${TRAVIS_OS_NAME}-${CC}-${BUILD_TYPE}"
if [[ "${TRAVIS_OS_NAME}" == "osx" ]]; then doctest_upload_name="Doctest [travis-ci ${TRAVIS_OS_NAME}-${CLANG_VERSION}-${BUILD_TYPE}"; fi

function build() {
    mkdir cmake-build-${BUILD_TYPE}
    cd cmake-build-${BUILD_TYPE}
    cmd='cmake'
    options="${DEPS_DIR}/cmake/bin/cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DCMAKE_CXX_COMPILER=${CXX} -DCMAKE_C_COMPILER=${CC}"
    if [[ "${CODE_COVERAGE}" == "ON" ]] && [[ "${BUILD_TYPE}" == "Debug" ]]; then
        options+=' -DNEPHTYS_COVERAGE=ON'
    elif [[ "${ASAN}" == "ON" ]] && [[ "${BUILD_TYPE}" == "Debug" ]]; then
        options+=' -DUSE_ASAN=ON'
        doctest_upload_name+='-ASAN'
    elif [[ "${TSAN}" == "ON" ]] && [[ "${BUILD_TYPE}" == "Debug" ]]; then
        options+=' -DUSE_TSAN=ON'
        doctest_upload_name+='-TSAN'
    elif [[ "${UBSAN}" == "ON" ]] && [[ "${BUILD_TYPE}" == "Debug" ]]; then
        options+=' -DUSE_UBSAN=ON'
        doctest_upload_name+='-UBSAN'
        if [[ "${TRAVIS_OS_NAME}" == "linux" ]]; then options+=' -DCMAKE_EXE_LINKER_FLAGS=-fuse-ld=gold'; fi
    elif [[ "${NINJA}" == "ON" ]]; then
        options+=' -GNinja'
        doctest_upload_name+='-Ninja'
    fi

    if [[ "${TRAVIS_OS_NAME}" == "osx" ]]; then
        conan install --build sfml ../;
     else
        conan install ../
     fi
    echo "result -> ${cmd} ${options} ../"
    ${cmd} ${options} ../
    if [[ -n ${NINJA} ]]; then
        ninja
    else
        make VERBOSE=1 -j2;
    fi
}

function run_test() {
    cd ${TRAVIS_BUILD_DIR}/cmake-build-${BUILD_TYPE}/bin
    for i in *-test; do ./${i} --reporters=xml --out=${i}-result.xml -s || true; done
}

function run_coverage() {
     cd ${TRAVIS_BUILD_DIR}/cmake-build-${BUILD_TYPE}
     lcov -d . -c -o coverage.info
     lcov -r coverage.info "/usr*" -o coverage.info
     lcov -r coverage.info "$HOME/.conan/*" -o coverage.info
     lcov -r coverage.info "${TRAVIS_BUILD_DIR}/*.test.*" -o coverage.info
     lcov -r coverage.info "${TRAVIS_BUILD_DIR}/vendor/noesisgui/include/*" -o coverage.info
     lcov -r coverage.info "${TRAVIS_BUILD_DIR}/vendor/loguru/*" -o coverage.info
     lcov -l coverage.info
      if [[ "${TRAVIS_OS_NAME}" == "osx" ]]; then
            CODECOV_TOKEN="aeb91d0a-b56c-48ae-b728-123dcf850a34"
            bash <(curl -s https://codecov.io/bash) -f coverage.info || echo "Codecov did not collect coverage reports"
      else
           coveralls-lcov coverage.info
      fi
}

function upload_test() {
    cd ${TRAVIS_BUILD_DIR}/cmake-build-${BUILD_TYPE}/bin
    doctest_upload_name+=']'
    curl https://report.ci/upload.py --output upload.py && python upload.py -n "${doctest_upload_name}"
}

if [[ "${NEPHTYS_BUILD_DOCUMENTATION}" == "ON" ]]; then build_doc; fi
if [[ "${WILL_COMPILE_CODE}" == "ON" ]]; then build; fi
if [[ "${WILL_COMPILE_CODE}" == "ON" ]]; then run_test; fi
if [[ "${CODE_COVERAGE}" == "ON" ]]; then run_coverage; fi
if [[ "${WILL_COMPILE_CODE}" == "ON" ]]; then upload_test; fi
