#!/usr/bin/env bash

# Current directory
__THIS_DIR=$(pwd)


# Downloads the 1.8.0 to disc
function dl {
    printf "\n  Downloading Google Test Archive\n\n"
    curl -LO https://github.com/google/googletest/archive/release-1.8.0.tar.gz
    tar xf release-1.8.0.tar.gz
}

# Unpack and Build
function build {
    printf "\n  Building GTest and Gmock\n\n"
    cd googletest-release-1.8.0
    sudo mkdir build 
    cd $_
    cmake -Dgtest_build_samples=OFF -Dgtest_build_tests=OFF ../
    make
}

# Install header files and library
function install {
    printf "\n  Installing GTest and Gmock\n\n"

    USR_LOCAL_INC="/usr/local/include"
    GTEST_DIR="/usr/local/Cellar/gtest/"
    GMOCK_DIR="/usr/local/Cellar/gmock/"

    sudo mkdir $GTEST_DIR

    sudo cp googlemock/gtest/*.a $GTEST_DIR
    sudo  cp -r ../googletest/include/gtest/  $GTEST_DIR
    sudo ln -snf $GTEST_DIR $USR_LOCAL_INC/gtest
    sudo ln -snf $USR_LOCAL_INC/gtest/libgtest.a /usr/local/lib/libgtest.a
    ln -snf $USR_LOCAL_INC/gtest/libgtest_main.a /usr/local/lib/libgtest_main.a

    sudo mkdir $GMOCK_DIR
    sudo cp googlemock/*.a   $GMOCK_DIR
    sudo cp -r ../googlemock/include/gmock/  $GMOCK_DIR
    sudo ln -snf $GMOCK_DIR $USR_LOCAL_INC/gmock
    sudo ln -snf $USR_LOCAL_INC/gmock/libgmock.a /usr/local/lib/libgmock.a
    sudo ln -snf $USR_LOCAL_INC/gmock/libgmock_main.a /usr/local/lib/libgmock_main.a
}

# Final Clean up.
function cleanup {
    printf "\n  Running Cleanup\n\n"

    sudo cd $__THIS_DIR
    sudo rm -rf $(pwd)/googletest-release-1.8.0
    sudo unlink $(pwd)/release-1.8.0.tar.gz
}

dl && build && install && cleanup 
