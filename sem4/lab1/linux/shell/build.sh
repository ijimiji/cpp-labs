#!/bin/sh
export ROOT=$PWD

build_number(){
    echo "[BUIDLING NUMBER 0/2]"
    echo "[BUIDLING NUMBER 1/2]"
    g++ -c Number/Number.cpp -o build/Number.o
    echo "[BUIDLING NUMBER 2/2]"
    ar rvs build/Number.a build/Number.o
    echo "[BUIDLING NUMBER DONE]"
}

build_vector(){
    echo "[BUIDLING VECTOR]"
    g++ -c -INumber Vector/Vector.cpp -o build/Vector.o
    g++ -shared -o build/libVector.so build/Vector.o build/Number.a
    echo "[BUIDLING VECTOR DONE]"
}
build_app(){
    echo "[BUIDLING APP]"
    g++ -INumber -IVector -Lbuild/ -lVector App/main.cpp -o build/main
    echo "[BUIDLING APP DONE]"
}

build(){
    [ -d build ] || mkdir build
    build_number && build_vector && build_app
}

clean(){
    echo "[CLEANING BUILD FILES]"
    rm -rf build
    echo "[CLEANING BUILD FILES DONE]"
}

run(){
    echo "RUNNING APP..."
    [ -f build/main ] && ./build/main || echo "ERROR: executable main not found!"
}

for command in "$@"; do
    if command -v $command > /dev/null; then
        $command
    else 
        echo "$command not found"
    fi
done