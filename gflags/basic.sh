#!/bin/bash

if [ ! -d './bin' ];then
    mkdir './bin'
fi

g++ gflags_test.cc -o bin/gflags_test -lgflags -lpthread

./bin/gflags_test -debug # 不带任何参数
./bin/gflags_test -host 10.8.121.12 #host
./bin/gflags_test --host localhost --port 8080 # 使用 --
./bin/gflags_test --host=localhost -port=9090 # =使用 =
./bin/gflags_test --help # 查看参数帮助说明
./bin/gflags_test --flagfile server.flags # 查看参数帮助说明
