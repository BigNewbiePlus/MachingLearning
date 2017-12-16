#!/usr/bin/python
# -*- coding:utf-8 -*-

'''
created on 2017/12/16
@author BigNewbie
实现logistic回归模型，包括简单预测+ 疝气病预测病马死亡情况+三种梯度上升+权值随迭代变化情况
参考文献 【机器学习实战】第5章 Logistic回归 http://www.cnblogs.com/jiangzhonglian/p/7680649.html#undefined
'''

print(__doc__)


def loadDataSet(filename):
    '''loadDataSet(加载数据3列，前两列为特征，最后一列为标签，空格间隔)

    Args:
        filename 文件名

    Returns:
        dataMat, labelMat 数据和标签
    '''

    fr = open(filename)

    dataMat = []
    labelMat = []
    for line in fr.readlines():
        dataList = line.strip().split()
        dataMat.append([1, float(dataList[0]), float(dataList[1])])
        labelMat.append([int(dataList[2])])

    return np.mat(dataMat), np.mat(labelMat)


def sigmoid(x):
    # sigmoid函数
    return 1 / (1 + np.exp(-x))

def gradAscent(dataMat, dataLabel):
    '''gradAscent(正常梯度上升算法, 基于全局数据更新权值，代价函数为交叉熵
                 公式为：
                        CrossEntropy = y * logy_ + (1-y)*log(1-y_),
                        y_ = sigmoid(z)
                        z = Xw )

    Args:
        dataMat 数据矩阵
        dataLabel 数据标签
        max_iterations 最大迭代次数

    Returns:
        weights 最终权值
        iter_weights 随迭代过程变化的权值记录，用于查看权值变化过程
    '''

    m, n =  np.shape(dataMat)

    alpha = 0.001
    max_iter = 500
    weights = np.ones(n, 1)

    iter_weights = []

    for i in range(max_iter):
        # 交叉熵crossEntropy对w求导为 xT(y-y_)
        y_ = sigmoid(dataMat*weightw)
        weights += appha * dataMat.transpose() * (dataLabel - y_)
        iter_weights.append(weights)

    return weights, iter_weights

def stocGradAscent0(dataMat, dataLabel):
    '''
    Desc:
        随机梯度上升。相较梯度上升整个数据集更新，随机梯度上身每次更新一个数据

    Args:
        同上
    Returns:
        同上
    '''

    m, n = np.shape(dataMat)

    alpha = 0.01
    weights = np.ones(n, 1)

    iter_weights = []

    for i in range(m):
        y_ = sigmoid(dataMat[i])

