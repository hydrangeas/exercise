# CMAKEバージョン
cmake_minimum_required (VERSION 2.6)
# リリースビルド用オプション
SET(CMAKE_C_FLAGS_RELEASE "-Wall -O3")
# デバッグビルド用オプション
SET(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
# ビルドのタイプはリリース
SET(CMAKE_BUILD_TYPE Release)

# プロジェクト名
project (wallet)

set (SOURCES wallet-util.c)

# Executable wallet binaries
add_executable (wallet wallet-main.c ${SOURCES})

enable_testing ()

add_executable (wallet-test wallet-test.c ${SOURCES})

set_target_properties (wallet-test PROPERTIES LINK_FLAGS -Wl,-lcunit)

add_test (wallet-test ${EXECUTABLE_OUTPUT_PATH}/test)


# バージョン番号
#SET(serial "1.0.0")
# 共有ライブラリのバージョン番号
#SET(soserial "1")

