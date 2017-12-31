#!/usr/bin/python
# coding:utf-8

'''
created on 2017/12/31
@author BigNewbie
参考文献:   支持向量机通俗导论（理解SVM的三层境界）http://blog.csdn.net/v_july_v/article/details/7624837
            【机器学习实战】第6章 支持向量机 http://www.cnblogs.com/jiangzhonglian/p/7690033.html
'''
print(__doc__)

import numpy as np
import matplotlib.pyplot as plt

def loadDataSet(filename):
    '''
    读取文件，前2行为特征值，最后一行为标签

    Args:
        filename 文件路径

    Returns:
        dataArr 数据集
        labelArr 标签集
    '''

    dataArr = []
    labelArr = []

    fr = open(filename)
    for line in fr.readlines():
        splits = line.strip().split('\t')
        dataArr.append([float(splits[0]), float(splits[1])])
        labelArr.append(float(splits[2]))

    return dataArr, labelArr

def selectJrand(i, m):
    '''
    从[1,m]数据中随机生成一个不是i的数

    Args:
        i 第一个alpha下标
        m 所有alphaa个数

    Returns:
        j 要返回的第二个alpha的下标
    '''

    j = i
    while j==i:
        j = int(np.random.uniform(1, m))

    return j

def clipAlpha(aj, L, H):
    '''
    对aj裁剪，使其L<=aj<=H

    Args:
        aj 要裁剪的alphaJ
        L aj最小值
        H aj最大值

    Returns:
        aj 裁剪后的aj
    '''

    if aj <= L:
        aj = L
    elif aj >= H :
        aj = H

    return aj

def smoSimple(dataArr, labelArr, C, toler, maxIter):
    '''
    简单的smo算法

    Args:
        dataArr 数据集
        labelArr 数据标签
        C 对松弛因子的惩罚系数
        toler 对误差的容忍度
        maxIter 最大迭代次数

    Returns:
        alphas 各数据实例对应的alpha值
        b  wTx+b对应的b值
    '''

    dataMat = np.mat(dataArr)
    labelMat = np.mat(labelArr).transpose()

    m, n = np.shape(dataMat)

    alphas = np.mat(np.zeros((m, 1)))
    b = 0

    iter = 0

    while iter < maxIter:

        alphaPairsChanged = 0
        for i in range(m):

            fxi = np.multiply(alphas, labelMat).T * (dataMat * dataMat[i,:].T) + b
            Ei = fxi - labelMat[i]

            # 满足KKT条件，由于0<=alpha<=C不检测边界值
            # yi*f(xi) >= 1 and alpha = 0
            # yi*f(xi) == 1 and 0<alpha<C
            # yi*f(xi) <= 1 and alpha = C

            # 不满足KKT
            if (labelMat[i]*Ei < -toler and alphas[i]<C) or (labelMat[i]*Ei > toler and alphas[i]>0):

                j = selectJrand(i, m)

                fxj = np.multiply(alphas, labelMat).T * (dataMat * dataMat[j,:].T) + b

                Ej = fxj - labelMat[j]

                alphaIold = np.copy(alphas[i])
                alphaJold = np.copy(alphas[j])

                if labelMat[i] != labelMat[j]:
                    L = max(0, alphas[j]-alphas[i])
                    H = min(C, C + alphas[j]-alphas[i])
                else:
                    L = max(0, alphas[j]+alphas[i] - C)
                    H = min(C, alphas[j]+alphas[i])

                eta = 2*dataMat[i,:] * dataMat[j,:].T - dataMat[i,:] * dataMat[i,:].T - dataMat[j,:]*dataMat[j,:].T

                alphas[j] -= labelMat[j] * (Ei-Ej) / eta

                alphas[j] = clipAlpha(alphas[j], L, H)

                if abs(alphas[j] - alphaJold)< 0.00001:
                    print('j not moving enough')
                    continue

                alphas[i] += labelMat[i]*labelMat[j]*(alphaJold-alphas[j])

                b1 = b - Ei + labelMat[i]*(alphaIold-alphas[i])*(dataMat[i,:]*dataMat[i,:].T) + labelMat[j] * (alphaJold-alphas[j])*(dataMat[j,:]*dataMat[i,:].T)
                b2 = b - Ej + labelMat[i]*(alphaIold-alphas[i])*(dataMat[i,:]*dataMat[j,:].T) + labelMat[j] * (alphaJold-alphas[j])*(dataMat[j,:]*dataMat[j,:].T)

                if alphas[i] >0 and alphas[i]<C:
                    b = b1
                elif alphas[j] >0 and alphas[j]<C:
                    b = b2
                else:
                    b = (b1+b2)/2

                alphaPairsChanged += 1
                print("iter:%d, i:%d, pairs changed:%d"%(iter, i, alphaPairsChanged))

        if alphaPairsChanged == 0:
            iter += 1
        else:
            iter = 0
        print("iter num:%d"%iter)

    return alphas, b

def calWs(alphas, dataArr, labelArr):
    '''
    根据alphas值计算w

    Args:
        alphas 各数据的阿尔法值
        dataMat 数据集
        labelMat 数据标签

    Returns:
        ws 权值
    '''

    dataMat = np.mat(dataArr)
    labelMat = np.mat(labelArr).transpose()

    m, n = np.shape(dataMat)

    ws = np.zeros((n, 1))

    for i in range(m):
        ws += np.multiply(alphas[i] * labelMat[i], dataMat[i,:].T)

    return ws

def plot_SVM(dataArr, labelArr, alphas, ws, b):
    '''
    画出二维数据下SVM超平面和分割直线

    Args:
        dataMat 数据集
        labelMat 数据标签
        alphas 阿尔法值
        ws 权值
        b 超平面偏移值
    '''

    dataMat = np.mat(dataArr)
    labelMat = np.mat(labelArr)

    fig = plt.figure()
    ax = fig.add_subplot(111)

    b = b[0,0]

    ax.scatter(dataMat[:,0].flatten().A[0], dataMat[:,1].flatten().A[0])

    x = np.arange(-1.0, 10.0, 0.1)

    k = -ws[0,0]/ws[1,0]

    y = k*x + -b / ws[1,0]

    ax.plot(x, y)

    for i in range(np.shape(labelMat)[1]):
        if labelMat[0, i ] > 0 :
            ax.plot(dataMat[i, 0], dataMat[i, 1], 'cx')
        else:
            ax.plot(dataMat[i, 0], dataMat[i, 1], 'kp')

    yy_up = None
    yy_down = None
    for i in range(100):
        if alphas[i] >0 and labelMat[0, i]>0:
            ax.plot(dataMat[i,0], dataMat[i,1], 'ro')
            if yy_up is None:
                yy_up = k*x + (dataMat[i, 1]-dataMat[i, 0]*k)
        elif alphas[i]>0 and labelMat[0, i]<0:
            ax.plot(dataMat[i,0], dataMat[i,1], 'go')
            if yy_down is None:
                yy_down = k*x + (dataMat[i,1]-dataMat[i,0]*k)

    ax.plot(x, yy_up, 'k--')
    ax.plot(x, yy_down, 'k--')


    plt.show()

if __name__ == '__main__':

    dataArr, labelArr = loadDataSet('../../../data/SVM/testSet.txt')

    alphas, b = smoSimple(dataArr, labelArr, 0.6, 0.001, 40)


    ws = calWs(alphas, dataArr, labelArr)

    plot_SVM(dataArr, labelArr, alphas, ws, b)

