#!/usr/bin/python
# coding:utf-8

'''
created on 2017/12/31
@author BigNewbie
参考文献:   支持向量机通俗导论（理解SVM的三层境界）http://blog.csdn.net/v_july_v/article/details/7624837
            【机器学习实战】第6章 支持向量机 http://www.cnblogs.com/jiangzhonglian/p/7690033.html
功能：使用sklearn SVM模块
'''
print(__doc__)

import numpy as np
import matplotlib.pyplot as plt
from sklearn import svm
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

def plot_SVM(dataArr, labelArr, w, b, svVe):
    '''
    画出二维数据下SVM超平面和分割直线

    Args:
        dataMat 数据集
        labelMat 数据标签
        w 权值
        b 超平面偏移值
        svVe 支持向量
    '''

    dataMat = np.mat(dataArr)
    labelMat = np.mat(labelArr)

    fig = plt.figure()
    ax = fig.add_subplot(111)


    x = np.arange(-1.0, 10.0, 0.1)

    k = -w[0]/w[1]

    y = k*x + -b / w[1]

    sv1 = svVe[0]
    yy_up = k*x + sv1[1] - k*sv1[0]
    sv2 = svVe[-1]
    yy_down = k*x + sv2[1] - k*sv2[0]

    ax.plot(x, y, 'k-')
    ax.plot(x, yy_up, 'k--')
    ax.plot(x, yy_down, 'k--')

    ax.scatter(svVe[:,0], svVe[:,1], s=80, facecolors='none')

    ax.scatter(dataMat[:,0].flatten().A[0], dataMat[:,1].flatten().A[0], c='y')

    plt.show()

if __name__ == '__main__':

    dataArr, labelArr = loadDataSet('../../../data/SVM/testSet.txt')

    dataMat = np.mat(dataArr)

    clf = svm.SVC(kernel='linear')
    clf.fit(dataMat, labelArr)

    w = clf.coef_[0]
    b = clf.intercept_[0]
    svVe = clf.support_vectors_

    plot_SVM(dataArr, labelArr, w, b, svVe)

