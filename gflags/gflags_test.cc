// Copyright [2018] <Copyright fangdenghui>
#include<iostream>

#include<gflags/gflags.h>

/**
 * 定义命令行参数
 * host 默认127.0.0.1
 * port 默认12306
 */
DEFINE_string(host, "127.0.0.1", "the server host");
DEFINE_int32(port, 12306, "the server port");
DEFINE_bool(debug, false, "whether to debug");
int main(int argc, char** argv) {
    // 解析命令参数
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    // 访问变量，使用FlAGS_前缀
    std::cout << "The server host is: " << FLAGS_host
        << ", the server port is: " << FLAGS_port << std::endl;

    if (FLAGS_debug) {
        std::cout << "debug!"<< std::endl;
    } else {
        std::cout << "no debug!" << std::endl;
    }
    return 0;
}
