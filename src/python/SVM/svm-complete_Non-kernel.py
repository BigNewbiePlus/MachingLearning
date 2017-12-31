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

class OptStruct:
    '''
    SVM数据结构
    '''
    def __init__(self, dataMat, labelMat, C, toler):
        self.dataMat = dataMat
        self.labelMat = labelMat
        self.C = C
        self.toler = toler
        self.m = np.shape(self.dataMat)
        self.alphas = np.mat(np.zeros((self.m,1)))
        self.b = 0
        self.eCache = np.mat(np.zeros((self.m, 2)))


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

def calEk(os,k):
    '''
    计算Ek

    Args:
        os 参数
        k  下标

    Returns:
        Ek 预测值和实际值的差值，f(xk)-yk
    '''

    yxk = np.multiply(os.alphas, os.labelMat).T * (os.dataMat * os.dataMat[k,:].T)
    Ek = yxk - os.labelMat[k]
    return Ek

def selectJ(os, i, Ei):
    '''
    选择对应j

    Args:
        i 第一个违背kkt数据下标
        Ei 预测值和真实值的差值
        os svm信息

    Returns:
        j 第二个数据下标
        Ej 预测结果和真实值差值
    '''

    maxJ = -1
    maxEj = 0
    maxDelE = 0

    os.eCache[i] = [1, Ei]

    validEcacheList = np.nonzero(os.eCache[:,0])[0]

    if len(validEcacheList) > 1:
        for j in validEcacheList:
            if j==i:
                continue

            Ej = calEk(os, j)
            if abs(Ei-Ej)>maxDelE:
                maxJ = j
                maxEj = Ej
                maxDelE = abs(Ei-Ej)
        return maxJ, maxEj
    else:
        j = selectJrand(i, os.m)
        Ej = calEk(os, j)
        return j, Ej

def updateEk(os, k):
    '''
    更新Ek

    Args:
        os svm数据
        k 下标
    '''

    Ek = calEk(os, k)
    os.eCache[k] = [1, Ek]

def innerL(os, i):
    '''
    内循环i

    Args:
        os 数据结构
        i 第一个违背kkt下标

    Returns:
        更新次数，1或0
    '''

    Ei = calEk(os, i)

    # 满足KKT条件，由于0<=alpha<=C不检测边界值
    # yi*f(xi) >= 1 and alpha = 0
    # yi*f(xi) == 1 and 0<alpha<C
    # yi*f(xi) <= 1 and alpha = C

    # 不满足KKT
    if (os.labelMat[i]*Ei < -toler and os.alphas[i]<C) or (os.labelMat[i]*Ei > toler and os.alphas[i]>0):
        j, Ej = selectJ(os, i, Ei)

        alphaIold = np.copy(os.alphas[i])
        alphaJold = np.copy(os.alphas[j])

        if os.labelMat[i] != os.labelMat[j]:
            L = max(0, os.alphas[j]-os.alphas[i])
            H = min(C, C + os.alphas[j]-os.alphas[i])
        else:
            L = max(0, os.alphas[j]+os.alphas[i] - C)
            H = min(C, os.alphas[j]+os.alphas[i])

        eta = 2*os.dataMat[i,:] * os.dataMat[j,:].T - os.dataMat[i,:] * os.dataMat[i,:].T - os.dataMat[j,:]*os.dataMat[j,:].T

        os.alphas[j] -= os.labelMat[j] * (Ei-Ej) / eta

        os.alphas[j] = clipAlpha(os.alphas[j], L, H)
        updateEk(os, j)

        if abs(os.alphas[j] - alphaJold)< 0.00001:
            print('j not moving enough')
            return 0

        os.alphas[i] += os.labelMat[i]*os.labelMat[j]*(alphaJold-os.alphas[j])
        updateEk(os, i)

        b1 = os.b - Ei + os.labelMat[i]*(alphaIold-os.alphas[i])*(os.dataMat[i,:]*os.dataMat[i,:].T) + os.labelMat[j] * (alphaJold-os.alphas[j])*(os.dataMat[j,:]*os.dataMat[i,:].T)
        b2 = os.b - Ej + os.labelMat[i]*(alphaIold-os.alphas[i])*(os.dataMat[i,:]*os.dataMat[j,:].T) + os.labelMat[j] * (alphaJold-os.alphas[j])*(os.dataMat[j,:]*os.dataMat[j,:].T)


        if os.alphas[i] >0 and os.alphas[i]<C:
            os.b = b1
        elif os.alphas[j] >0 and os.alphas[j]<C:
            os.b = b2
        else:
            os.b = (b1+b2)/2
        return 1
    return 0

def smoP(dataArr, labelArr, C, toler, maxIter):
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

    os = OptStruct(dataMat, labelMat, C, toler)

    iter = 0
    alphaPairChanged = 0
    entireSet = True

    while iter < maxIter and (alphaPairChanged>0 or entireSet):

        alphaPairsChanged = 0

        if entireSet:
            for i in range(os.m):
                alphaPairsChanged += innerL(os, i)
                print("fullset, iter:%d, i:%d, pairs changed %d"%(iter, i, alphaPairsChanged))
            iter += 1

        else:
            # 遍历所有alpha非边界值
            nonboundIs = np.nonzero((os.alphas>0)&(os.alphas<C))[0]
            for i in nonboundIs:
                alphaPairsChanged += innerL(os, i)
            iter += 1

        if entireSet:
            entireSet = False
        elif alphaPairsChanged==0:
            entireSet = True

        print("iteration number:%d"%iter)

    return os.alphas, os.b

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

    alphas, b = smoP(dataArr, labelArr, 0.6, 0.001, 40)


    ws = calWs(alphas, dataArr, labelArr)

    plot_SVM(dataArr, labelArr, alphas, ws, b)

