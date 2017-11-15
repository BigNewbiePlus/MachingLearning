# CMake generated Testfile for 
# Source directory: /home/fdh/nn/oclint/oclint-rules/test
# Build directory: /home/fdh/nn/oclint/oclint-rules/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(CanaryTest "/home/fdh/nn/oclint/oclint-rules/bin/CanaryTest")
subdirs("abstract")
subdirs("helper")
subdirs("custom")
