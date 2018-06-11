#!/usr/bin/env python
# -*- coding:utf8 -*-

import sys, time

class ShowProcess(object):
    """
    显示处理进度的类
    调用该类相关函数实现进度显示
    """

    cur_step = 0 # 当前进度
    max_steps = 50 # 最大步数
    max_arrows = 50 # 进度条长度
    infoDone = 'done'

    # 初始化函数
    def __init__(self, max_steps, infoDone = 'Done'):
        self.max_steps = max_steps
        self.cur_step = 0
        self.infoDone = infoDone

    # 显示进度, 根据cur_step显示
    # 显示效果为[>>>>>>>>>>>        ]50%
    def show_process(self, cur_step=None):
        if cur_step is not None:
            self.cur_step = cur_step
        else:
            self.cur_step += 1

        num_arrow = int(self.cur_step * self.max_arrows / self.max_steps)
        num_line = self.max_arrows - num_arrow
        percent = self.cur_step * 100.0 / self.max_steps
        process_bar = '[' + '>' * num_arrow + '-' * num_line + ']' + '%.2f'%percent + '%' + '\r' # 带输出的字符串，'\r'表示不换行回到最左边
        sys.stdout.write(process_bar)
        sys.stdout.flush()

        if self.cur_step >= self.max_steps:
            self.close()

    def close(self):
        print('')
        print(self.infoDone)
        self.cur_step = 0

if __name__ == '__main__':
    max_steps = 1000
    process_bar = ShowProcess(max_steps, 'OK')
    for i in range(max_steps):
        process_bar.show_process()
        time.sleep(0.01)
