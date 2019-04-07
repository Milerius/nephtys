#!/usr/bin/env bash

function build_doc() {
    cd docs
    make html
    cd -
}

build_doc