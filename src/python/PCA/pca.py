#coding:utf-8

'''
时间: 2017/11/12
参考:
    PCA原理: http://www.360doc.com/content/13/1124/02/9482_331688889.shtml
    机器学习算法笔记系列之深入理解主成分分析PCA-原理篇: http://blog.csdn.net/shizhixin/article/details/51181379
    代码参考: http://www.cnblogs.com/jiangzhonglian/p/7808862.html

实现算法 PCA
实现功能 展示降维后数据和原数据前二维坐标图
         展示特征值从大到小变化时方差变化情况
'''
import numpy as np
import matplotlib.pyplot as plt


def loadDataSet(filepath, delim='\t'):
    fopen = open(filepath)
    stringArr = [line.strip().split(delim) for line in fopen.readlines()]
    dateArr = [map(float, line) for line in stringArr]
    return np.mat(dateArr)

def replaceNanWithMean(dataMat):
    numFeat = np.shape(dataMat)[1]
    for i in range(numFeat):
        nanIndex = np.isnan(dataMat[,i])
        meanVal = np.mean(dataMat[,i][~nanIndex])
        dataMat[,i][nanIndex] = meanVal

def pca(dataMat, topFeats=999):
    meanVal = np.mean(dataMat, axis=0) #计算均值
    meanRM = dataMat-meanVal #减去均值
    covMat = np.cov(meanRM) #获取协方差矩阵
    eigVal, eigVec = np.linalg.eig(covMat)#获取特征值和特征向量

    eigInd = np.argsort(eigVal) #对特征值从小到达排序

    eigenInd = eigenInd[:-(topFeats+1):-1] # 找出前topFeats特征向量下标

    # 获取topFeats前特征向量,即转化矩阵
    convMat = eigenVec[:eigenInd]
    # 获取降维数据
    convData = meanRM*convMat

    reconData = convData*convMat.T+meanVals
    return convDara, reconData


def show_picture(dataMat, convData, reconData):
    #画出三个数据的两维数据，包括原始数据，转置数据，重构数据
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.scatter(daraMat[:0], dataMat[:1], marker='^', s=90)
    ax.scatter(convData[:0], convData[:1], marker='o', s=50, c='red')
    ax.scatter(reconData[:0], reconData[:1], marker='*', s=30, c='green')
    plt.show()


def analysis_data(dataMat):
    #统计PCA方差变化情况
    meanVals = np.mean(dataMat, axis=0)
    meanRM = dataMat-meanVals
    covMat = np.cov(meanaRM)
    eigVal, eigVec = np.linalg.eig(covMat)
    eigInd = np.argsort(eigVal)
    eigInd = eigInd[:-(topFeats+1):-1]
    cov_total = np.sum(eigVal)

    cov_sum = 0
    for i in range(len(eigInd)):
        cov_cur = eigVal[eigInd[i]]
        cov_sum += cov_cur

        print("主成分:%d, 方差占比:%.2f%%,累计方差占比A：%.2f%%"%(i+1，cov_cur*100/cov_total, cov_sum*100/cov_total))

def main():
    dataMat = loadDataSet('../../../data/PCA/secom.data', ' ')
    replaceNanWithMean(dataMat)
    analysis_data(dataMat)
    covData, reconData = pca(dataMat)
    show_picture(dataMat, convData, reconData)


if __name__ == '__main__':
    main()


