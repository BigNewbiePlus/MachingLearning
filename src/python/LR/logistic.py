#!/usr/bin/python
# -*- coding:utf-8 -*-

'''
created on 2017/12/16
@author BigNewbie
功能：实现logistic回归模型，包括简单预测 + 疝气病预测病马死亡情况 + 三种梯度上升 + 权值随迭代变化情况
参考文献：【机器学习实战】第5章 Logistic回归 http://www.cnblogs.com/jiangzhonglian/p/7680649.html#undefined
'''

print(__doc__)

import numpy as np
import matplotlib.pyplot as plt
import copy
import random

def loadMatData(filename, delim=' '):
    '''loadMatData(加载数据3列，前两列为特征，最后一列为标签，空格间隔)

    Args:
        filename 文件名

    Returns:
        dataMat, labelMat 数据和标签
    '''

    fr = open(filename)

    dataMat = []
    labelMat = []
    for line in fr.readlines():
        dataList = line.strip().split(delim)
        dataMat.append([float(dataList[i-1]) if i!=0 else 1 for i in range(len(dataList))])
        labelMat.append(int(float(dataList[-1])))

    return np.array(dataMat), np.array(labelMat)


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
    weights = np.ones(n)

    iter_weights = []

    for i in range(m):
        y_ = sigmoid(dataMat[i]*weights)
        weights += alpha * dataMatp[i] * (dataLabel[i] - y_)
        iter_weights.append(weights)

    return weights, iter_weights

def stocGradAscent1(dataMat, dataLabel, numIter=150):
    '''
    Decs:
        随机梯度上升法。相对0，添加了随机生成 + 学习速率变化策略

    Args:
        同上
    '''

    m, n = np.shape(dataMat)

    weights = np.ones(n)
    iter_weights = []

    for i in range(numIter):
        dataIndex = [index for index in range(m)]

        for j in range(m):
            alpha = 4/(1.0 + i + j) + 0.0001

            randIndex = int(random.uniform(0, len(dataIndex)))

            y_ = sigmoid(sum(dataMat[dataIndex[randIndex]]*weights))
            weights += alpha * dataMat[dataIndex[randIndex]] * (dataLabel[dataIndex[randIndex]] - y_)
            iter_weights.append([weights[index] if index!=n else alpha for index in range(n+1)])
            dataIndex.pop(randIndex)
    return weights, iter_weights

def plotBestFit(dataMat, labelMat, weights):
    '''
    Desc:
        显示简单数据分布和回归曲线

    Args:
        dataMat 三维特征矩阵
        labelMat 标签
        weights 全值，求超平面
    '''

    m = np.shape(dataMat)[0]
    xcord1 = []; ycord1 = []
    xcord2 = []; ycord2 = []

    for i in range(m):
        if labelMat[i] == 1:
            xcord1.append(dataMat[i,1]); ycord1.append(dataMat[i, 2])
        else:
            xcord2.append(dataMat[i, 1]); ycord2.append(dataMat[i, 2])

    fig = plt.figure()
    ax = fig.add_subplot(111)

    ax.scatter(xcord1, ycord1, s=30, c='red', marker='s')
    ax.scatter(xcord2, ycord2, s=30, c='green')

    x = np.arange(-3.0, 3.0, 0.1)
    y = -(weights[0] + weights[1]*x)/weights[2]
    ax.plot(x, y)

    plt.xlabel('X') ; plt.ylabel('Y')
    plt.show()

def plotWeightsIter(iter_weights):
    '''
    Desc:
        画出权值变量的迭代情况

    Args:
        iter_weights 迭代过程中权值更新情况
    '''

    fig = plt.figure()
    iter_num = len(iter_weights)
    weight_num  = len(iter_weights[0])
    rows = int(np.sqrt(weight_num)); cols = rows
    if rows*cols<weight_num: cols+=1
    if rows*cols<weight_num: rows+=1

    xcords = [i for i in range(iter_num)]

    for feat_index in range(weight_num):
        ax = fig.add_subplot(rows, cols, feat_index+1)
        ycords = [iter_weights[i][feat_index] for i in range(iter_num)]
        feat_label = 'weight{i}'.format(i=feat_index+1)
        if feat_index == weight_num-1: feat_label = 'alpha'
        ax.plot(xcords, ycords)
        ax.set_xlabel("Iterations")
        ax.set_ylabel("weights")
        ax.set_title(feat_label)
    #plt.xlabel('Iteration')
    #$plt.ylabel('weights')
    plt.show()

def simpleTest():
    '''
    Desc:
        简单测试2维特征数据
    '''

    dataMat, labelMat = loadMatData('../../../data/LR/TestSet.txt', delim='\t')

    weights, iter_weights = stocGradAscent1(dataMat, labelMat, numIter=500)

    plotBestFit(dataMat, labelMat, weights)
    plotWeightsIter(iter_weights)

def classifyLR(vec2classify, weights):
    prob = sigmoid(sum(vec2classify * weights))

    if prob>0.5:
        return 1
    return 0

def colicTest():
    '''
    Decs:
        疝气病预测兵马死亡情况测试
    '''

    trainData, trainLabel = loadMatData('../../../data/LR/HorseColicTraining.txt', delim='\t')
    testData, testLabel = loadMatData('../../../data/LR/HorseColicTest.txt', delim='\t')

    weights, iter_weights = stocGradAscent1(trainData, trainLabel, numIter=500)

    error_num = 0
    test_num = len(testData)

    for i in range(test_num):
        if classifyLR(testData[i], weights) != testLabel[i]:
            error_num += 1

    print('error num: %d, test num: %d, error rate: %lf'%(error_num, test_num, error_num/test_num))
    plotWeightsIter(iter_weights)
#simpleTest()
colicTest()
