#!/usr/bin/env bash

# build downloaded projects one level above
cd ..
set -e
NUM_PROCS=24


function build_rapidjson {
    REPOSITORY="rapidjson"
    if [[ -e ${REPOSITORY} ]]; then
        rm -rf ${REPOSITORY}
        echo "Removing existing and downloading fresh repository ${REPOSITORY}"
    fi
    git clone https://github.com/Tencent/rapidjson.git
    mkdir -p rapidjson/build
    pushd rapidjson/build > /dev/null
    cmake -D BUILD_PYTHON=ON -DCMAKE_BUILD_TYPE=Debug ..  && make -j ${NUM_PROCS}
    popd > /dev/null
}

build_rapidjson