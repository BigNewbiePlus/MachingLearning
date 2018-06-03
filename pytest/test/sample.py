#!/usr/bin/env python
#-*- coding=utf8 -*-

def func(x):
    return x+1

def test_answer():
    assert func(3) == 5

def test_inc():
    assert func(3) == 4
