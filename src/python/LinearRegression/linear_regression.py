#!/usr/bin/python
#coding:utf-8

'''
created on 2018/01/29
@author fangdenghui
实现功能 线性回归、lwlr和岭回归
参考文献 第8章 预测数值型数据：回归 http://www.cnblogs.com/jiangzhonglian/p/7736096.html
'''

print(__doc__)

import numpy as np
import matplotlib.pyplot as plt

def loadDataSet(filename):
    '''
    Description 加载数据，数据间以\t分割，最后一个为标签

    Args:
        filename 文件路径

    Returns:
        dataArr 数据集
        labelArr 数据标签集
    '''

    feat_n = len(open(filename).readline().split('\t')) - 1

    dataArr, labelArr = list(), list()

    fr = open(filename)

    for line in fr.readlines():
        lineArr = list()

        words = line.strip().split('\t')

        for i in range(feat_n):
            lineArr.append(float(words[i]))

        dataArr.append(lineArr)
        labelArr.append(float(words[-1]))

    return np.array(dataArr), np.array(labelArr)

def standRegression(dataArr, labelArr):
    '''
    Description 标准正则表达式

    Args:
        dataArr 数据集
        labelArr 数据标签

    Returns:
        w 权值
    '''

    dataMat = np.mat(dataArr)
    labelMat = np.mat(labelArr).T

    xTx = dataMat.T * dataMat

    if np.linalg.det(xTx) == 0.0:
        print 'this matrix is singular, cannt do inverse'
        return

    w = xTx.I * (dataMat.T*labelMat)

    return w

def lwlr(testPoint, dataArr, labelArr, k=1.0):
    '''
    Description 局部权值回归

    Args:
        testPoint 测试数据
        dataArr 数据集
        labelArr 数据标签
        k 核参数，即标准差

    Returns：
        testPoint * w 数据点和权值相乘获得的预测值
    '''

    dataMat = np.mat(dataArr)
    labelMat = np.mat(labelArr).T

    m = np.shape(dataMat)[0]

    W = np.mat(np.eye((m)))

    for i in range(m):

        diff = testPoint - dataMat[i,:]

        W[i, i] = np.exp(diff*diff.T/(-2.0*k**2))

    xTx = dataMat.T*(W * dataMat)

    if np.linalg.det(xTx) == 0.0:
        print('This matrix is singular , cannt do inverse')
        return

    w = xTx.I * (dataMat.T * (W*labelMat))

    return testPoint * w

def lwlrTest(testArr, dataArr, labelArr, k=1.0):
    '''
    Description lwlr测试

    Args:
        testArr 测试数据
        dataArr 样本集
        labelArr 样本标签
        k 控制局部权值标准差

    Returns
        ys 测试结果
    '''

    m = np.shape(testArr)[0]

    ys = np.zeros(m)

    for i in range(m):
        ys[i] = lwlr(testArr[i], dataArr, labelArr, k)

    return  ys

def rssErrors(actuals, predicts):
    '''
    Description MSE(Mean Square Error) 最小均方差

    Args:
        actuals 正式值
        predicts 预测值

    Returns:
        mse 均方差
    '''

    return ((actuals-predicts)**2).sum()

def ridgeRegression(dataMat, labelMat, lam=0.2):
    '''
    Description 系数lam下的岭回归

    Args:
        dataArr 数据集
        labelArr  标签集
        lam 系数

    Returns：
        w 岭回归权值
    '''

    m, n = np.shape(dataMat)

    xTx = dataMat.T * dataMat

    denom = xTx + np.eye(n)*lam

    if np.linalg.det(denom) == 0.0:
        print 'this matrix is singular, cannt do inverse'
        return

    w = denom.I * (dataMat.T * labelMat)

    return w

def ridgeTest(dataArr, labelArr):
    '''
    Description 岭回归测试
    '''

    dataMat = np.mat(dataArr)
    labelMat = np.mat(labelArr).T

    numTest = 30

    wMat = np.zeros((numTest, np.shape(dataMat)[1]))
    for i in range(numTest):
        ws = ridgeRegression(dataMat, labelMat, np.exp(i-10))
        wMat[i,:] = ws.T

    return wMat

def regression1():
    '''
    Description 回归测试1，用于测试简单的回归方程
    '''

    dataArr, labelArr = loadDataSet('../../../data/linear_regression.txt')

    w = standRegression(dataArr, labelArr)

    dataMat = np.mat(dataArr)
    labelMat = np.mat(labelArr)

    fig = plt.figure()

    ax = fig.add_subplot(111)

    ax.scatter(dataMat[:,1].flatten().A[0], labelArr, s=2, c='r')

    xCopy = dataMat.copy()
    xCopy.sort(0)

    ys = xCopy * w

    ax.plot(xCopy[:,1], ys)

    plt.show()

def regression2():
    '''
    Description 使用lwlr测试
    '''

    dataArr, labelArr = loadDataSet('../../../data/linear_regression.txt')

    ys = lwlrTest(dataArr, dataArr, labelArr, 0.003)

    dataMat = np.mat(dataArr)
    labelMat = np.mat(labelArr)

    fig = plt.figure()

    ax = fig.add_subplot(111)

    xs = dataMat[:,1].flatten().A[0]

    ax.scatter(xs, labelArr, s=2, c='r')

    index = np.argsort(xs)

    ax.plot(xs[index], ys[index])

    plt.show()


def regression3():
    '''
    Description 岭回归测试
    '''

    dataArr, labelArr = loadDataSet('../../../data/abalone.txt')

    ridgeWeights = ridgeTest(dataArr, labelArr)

    fig = plt.figure()

    ax = fig.add_subplot(111)

    ax.plot(ridgeWeights)

    plt.show()

if __name__ == '__main__':
    #regression1()
    #regression2()
    regression3()

