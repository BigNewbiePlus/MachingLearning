#coding:utf-8

'''
时间: 2017/11/12
参考:
    PCA原理: http:#www.360doc.com/content/13/1124/02/9482_331688889.shtml
    机器学习算法笔记系列之深入理解主成分分析PCA-原理篇: http:#blog.csdn.net/shizhixin/article/details/51181379
    代码参考: http:#www.cnblogs.com/jiangzhonglian/p/7808862.html

实现算法 PCA
实现功能 展示降维后数据和原数据前二维坐标图
         展示特征值从大到小变化时方差变化情况
'''
#print(__doc__)

import numpy as np
import matplotlib.pyplot as plt


def loadDataSet(filepath, delim='\t'):
    fopen = open(filepath)
    stringArr = [line.strip().split(delim) for line in fopen.readlines()]
    dataArr = [[float(word) for word in line ] for line in stringArr]
    return np.mat(dataArr)

def replaceNanWithMean(dataMat):
    numSamp = np.shape(dataMat)[0]
    numFeat = np.shape(dataMat)[1]
    for i in range(numFeat):
        nanIndex = np.isnan(dataMat[:,i].A.reshape(numSamp))
        meanVal = np.mean(dataMat[~nanIndex,i])
        dataMat[nanIndex,i] = meanVal

def pca(dataMat, topNFeats=999):
    #print("原始矩阵:", dataMat)
    meanVal = np.mean(dataMat, axis=0) #计算均值
    meanRM = dataMat-meanVal #减去均值
    covMat = np.cov(meanRM, rowvar=False) #获取协方差矩阵
    eigVal, eigVec = np.linalg.eig(covMat)#获取特征值和特征向量

    #print("eigVal:", eigVal)
    #print("eigVec:", eigVec)

    eigInd = np.argsort(eigVal) #对特征值从小到达排序

    eigInd = eigInd[:-(topNFeats+1):-1] # 找出前topNFeats特征向量下标

    #print("eigInd:", eigInd)
    # 获取topNFeats前特征向量,即转化矩阵
    convMat = eigVec[:,eigInd]
    #print("转制矩阵",convMat)
    # 获取降维数据
    convDataMat = meanRM*convMat
    #print("转制数据矩阵", convDataMat)
    reconDataMat = convDataMat*convMat.T+meanVal
    #print("重构数据矩阵", reconDataMat)
    return convDataMat, reconDataMat

def show_picture(dataMat, convDataMat, reconDataMat):
    #画出三个数据的两维数据，包括原始数据，转置数据，重构数据
    #print("降维矩阵:", convDataMat)
    #print("重构矩阵:", reconDataMat)
    numSamp = np.shape(dataMat)[0]
    fig = plt.figure()
    ax = fig.add_subplot(221)
    ax.scatter(dataMat[:,0].A.reshape(numSamp), dataMat[:,1].A.reshape(numSamp), marker='^', s=90)
    ax = fig.add_subplot(222)
    ax.scatter(convDataMat[:,0].A.reshape(numSamp), convDataMat[:,1].A.reshape(numSamp), marker='o', s=50, c='red')
    ax = fig.add_subplot(223)
    ax.scatter(reconDataMat[:,0].A.reshape(numSamp), reconDataMat[:,1].A.reshape(numSamp)+1, marker='*', s=30, c='green')
    plt.show()


def analysis_data(dataMat):
    #统计PCA方差变化情况
    #print("原始数据矩阵")
    #print(dataMat)

    meanVal = np.mean(dataMat, axis=0)
    #print("均值",meanVal)
    meanRM = dataMat-meanVal
    #print("均值矩阵",meanRM)
    covMat = np.cov(meanRM, rowvar=False)
    #print("协方差矩阵",covMat)
    eigVal, eigVec = np.linalg.eig(covMat)
    #print("特征值",eigVal)
    #print("特征向量",eigVec)
    eigInd = np.argsort(eigVal)
    #print("特征值排序下标",eigInd)
    topNFeats = 20
    eigInd = eigInd[:-(topNFeats+1):-1]
    #print("前20特征排序下标",eigInd)
    cov_total = np.sum(eigVal)
    #print("协方差总和",cov_total)

    cov_sum = 0
    for i in range(len(eigInd)):
        cov_cur = eigVal[eigInd[i]]
        cov_sum += cov_cur

        print("主成分:%d, 方差占比:%.2f%%,累计方差占比A:%.2f%%"%(i+1, cov_cur*100/cov_total, cov_sum*100/cov_total))

def main():
    #半导体数据
    dataMat = loadDataSet('../../../data/PCA/secom.data', ' ')

    #伪造数据
    #dataMat = np.mat([[1,np.nan,3,4],[np.nan,4,5,6], [5,6,7, np.nan]])
    replaceNanWithMean(dataMat)
    analysis_data(dataMat)
    convDataMat, reconDataMat = pca(dataMat, topNFeats=20)
    show_picture(dataMat, convDataMat, reconDataMat)


if __name__ == '__main__':
    main()


