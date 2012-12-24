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

add_executable (wallet wallet-main.c wallet-util.c)
message("CMAKE_LINKER_FLAGS: ${CMAKE_LINKER_FLAGS}")

# バージョン番号
SET(serial "1.0.0")
# 共有ライブラリのバージョン番号
SET(soserial "1")
