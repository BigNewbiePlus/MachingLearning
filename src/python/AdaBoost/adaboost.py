#!/usr/bin/python
#coding:utf-8

'''
created on 2018/01/16
@author BigNewbie
功能 adaboost = adaptive boosting, 自适应增强算法，实战示例：马疝气病预测
参考: 【机器学习实战】第7章 集成方法 ensemble method http://www.cnblogs.com/jiangzhonglian/p/7698312.html
        Adaboost 算法的原理与推导 http://blog.csdn.net/v_july_v/article/details/40718799
'''

print(__doc__)

import numpy as np

def loadSimpData():
    '''
    加载简单数据，用于测试

    Returns:
        dataArr 数据集
        labelArr 标签集
    '''

    dataArr = np.array([[1., 2.1], [2., 1.1], [1.3, 1.], [1., 1.], [2., 1.]])
    labelArr = [1.0, 1.0, -1.0, 1.0]

    return dataArr, labelArr

def loadDataSet(filename):
    '''
    加载数据集

    Args:
        filename 文件路径

    Returns:
        dataArr 数据集
        labelArr 数据标签
    '''

    dataArr = list()
    labelArr = list()

    fr = open(filename)

    for line in fr.readlines():
        lineArr = []
        features = line.strip().split('\t')
        for i in range(len(features)-1):
            lineArr.append(float(features[i]))
        dataArr.append(lineArr)
        labelArr.append(float(features[-1]))

    return dataArr, labelArr

def stumpClassify(dataMat, dim, threshVal, stumpKind):
    '''
    单层分类器分类

    Args:
        dataMat 数据矩阵
        dim 特征维度
        threshVal 特征阈值
        stumpKind 分类种类， lt为小于threshVal为-1，gt为大于threshVal为-1

    Returns:
        labels 预测标签
    '''

    m, n = np.shape(dataMat)

    labels = np.mat(np.ones((m, 1)))

    if stumpKind == 'lt':
        labels[dataMat[:, dim] < threshVal] = -1
    else:
        labels[dataMat[:, dim] > threshVal] = -1

    return labels

def buildStump(dataArr, labelArr, D):
    '''
    创建决策树,基于数据权值分布

    Args:
        dataMat 数据集
        labelArr 标签集
        D 数据权值分布

    Returns:
        b_stump 最好决策树
        b_error 最优误差率
        b_predicts 最优预测结果
    '''

    dataMat = np.mat(dataArr)
    labelMat = np.mat(labelArr).T

    m, n = np.shape(dataMat)

    b_stump = {}
    b_error = np.inf
    b_predicted = np.mat(np.zeros((m, 1)))


    # 数据特征值遍历步数
    numSteps = 10

    for i in range(n):

        rangeMin = dataMat[:, i].min()
        rangeMax = dataMat[:, i].max()

        stepSize = (rangeMax - rangeMin) / float(numSteps)

        for j in range(-1, numSteps + 1):
            # 遍历比较类型，大于和小于
            for stumpKind in ['lt', 'gt']:

                threshVal = rangeMin + j * stepSize

                predicted = stumpClassify(dataMat, i, threshVal, stumpKind)

                errArr = np.mat(np.zeros((m, 1)))

                errArr[predicted != labelMat] = 1

                weightedError = errArr.T * D

                if weightedError< b_error:
                    b_error = weightedError
                    b_predicted = predicted

                    b_stump['dim'] = i
                    b_stump['threshVal'] = threshVal
                    b_stump['stumpKind'] = stumpKind

    return b_stump, b_error, b_predicted

def adaBoost(dataArr, labelArr, numIter=40):
    '''
    adaptive boosting 算法

    Args:
        dataArr 数据集
        labelArr 数据标签
        numIter 迭代次数，每次挑选一个单层若分类器

    Returns:
        weekClassifyArr 弱分类器集合
        aggClassEst 预测结果
    '''

    m, n = np.shape(dataArr)
    weekClassifyArr = list()
    aggClassEst = np.mat(np.zeros((m, 1)))

    D = np.mat(np.ones((m, 1))) / float(m)

    for i in range(numIter):

        stump, error, predicted = buildStump(dataArr, labelArr, D)

        alpha = float(0.5 * np.log((1.0-error)/max(error, 1e-16)))

        stump['alpha'] = alpha

        weekClassifyArr.append(stump)

        expon = np.multiply(-1*alpha*np.mat(labelArr).T, predicted)

        D = np.multiply(np.exp(expon), D)

        D = D/D.sum()

        aggClassEst += alpha * predicted

        aggErrors = np.mat(np.zeros((m, 1)))

        aggErrors[np.sign(aggClassEst) != np.mat(labelArr).T] = 1

        errorSum = aggErrors.sum() / m

        if errorSum == 0.0:
            break

    return weekClassifyArr, aggClassEst

def adaClassify(dataArr, weekClassifyArr):
    '''
    对数据集使用adaboost训练好的分类器分类

    Args:
        dataArr 待分类数据
        weekClassifyArr 分类器集合

    Returns:
        labels 分类标签集合
    '''

    dataMat = np.mat(dataArr)

    m, n = np.shape(dataMat)

    adaClassEst = np.mat(np.zeros((m, 1)))

    for i in range(len(weekClassifyArr)):

        predicted = stumpClassify(dataMat, weekClassifyArr[i]['dim'], weekClassifyArr[i]['threshVal'], weekClassifyArr[i]['stumpKind'])
        adaClassEst += weekClassifyArr[i]['alpha'] * predicted


    return np.sign(adaClassEst)

def plotROC(predicted, actuals):
    '''
    根据预测值和真实值画出ROC曲线和求解AUC值

    Args:
        predicted adaboost预测值
        actuals 真实标签
    '''

    import matplotlib.pyplot as plt

    ySum = 0.0

    numPosClass = sum(np.array(actuals)==1.0)

    ySteps = 1.0/numPosClass

    xSteps = 1.0/(len(actuals) - numPosClass)

    sortIndexPredicted = predicted.argsort()

    fig = plt.figure()
    fig.clf()

    ax = plt.subplot(111)

    cur = (1,1)

    for index in sortIndexPredicted.tolist()[0]:
        if actuals[index] == 1.0:
            delX = 0
            delY = ySteps
        else:
            delX = xSteps
            delY = 0
            ySum += cur[1]

        ax.plot([cur[0], cur[0]-delX], [cur[1], cur[1]-delY], c='b')
        cur = (cur[0]-delX, cur[1]-delY)

    ax.plot([0, 1], [0, 1], 'b--')

    plt.xlabel('False positive rate')
    plt.ylabel('True positive rate')

    plt.title('ROC curve for Adaboost horse colic detection system')

    plt.axis([0,1, 0, 1])

    plt.show()

    print('The AUC is', ySum*xSteps)


if __name__ == '__main__':

    dataArr, labelArr = loadDataSet('../../../data/horseColicTraining2.txt')

    weakClassifyArr, aggClassEst = adaBoost(dataArr, labelArr, 40)

    print(weakClassifyArr, aggClassEst.T)

    plotROC(aggClassEst.T, labelArr)

    # 测试
    dataArrTest, labelArrTest = loadDataSet('../../../data/horseColicTest2.txt')

    m = np.shape(dataArrTest)[0]

    predicted = adaClassify(dataArrTest, weakClassifyArr)

    errors = np.mat(np.zeros((m,1)))

    errors[predicted!=np.mat(labelArrTest).T] = 1

    print('test num:%d,error num:%d, error rate:%.2lf'%(m, errors.sum(), errors.sum()/float(m)))




