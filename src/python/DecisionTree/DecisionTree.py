# coding:utf-8

'''
created on 2017/12/10
@author BigNewbie
实现功能 基于离散数据构建决策树，并基于是否是鱼和预测隐形眼镜两个数据做分类
参考文献 http://www.cnblogs.com/jiangzhonglian/p/7640280.html
'''

print(__doc__)

import DecisionTreePlot as dtPlot
import math
import collections

def createFishData():
    '''createFishData(创建关于是否是鱼的数据集，选择两个特征: no surfacing 和 flippers)
    '''

    dataSet = [[1, 1, 'yes'],
               [1, 1, 'yes'],
               [1, 0, 'no'],
               [0, 1, 'no']]

    # 特征标签
    featLabels = ['no surfacing', 'flippers']

    return dataSet, featLabels

def calcShanonEnt(dataSet):
    '''calcShanonEnt(计算数据集香农熵, 最后一列为类别标签)
    '''

    # 数据集大小
    m = len(dataSet)
    entropy = 0.0

    classCnt = {}
    for sample in dataSet:
        if sample[-1] not in classCnt.keys():
            classCnt[sample[-1]] = 1
        else:
            classCnt[sample[-1]] += 1

    for key,cnt in classCnt.items():
        p = cnt / m
        entropy -= p * math.log(p, 2)

    return entropy


def splitDataSet(dataSet, index, value):
    '''splitDataSet(基于index列值value对数据集切割，决策树的分枝过程)

    Args:
        dataSet 原始数据
        index 列，即要切割的特征
        value 特征值，维度index取值value时切割

    Returns:
        返回切割的数据集
    '''

    retDataSet = []
    for sample in dataSet:
        if sample[index] == value:
            retDataSet.append(sample[0:index]+sample[index+1:])

    return retDataSet

def chooseBestFeat(dataSet):
    '''chooseBestFeat(选择当前数据最好的切割特征，并返回维度值)

    Args:
        数据集
    '''
    baseEntropy = calcShanonEnt(dataSet)
    bestInfoGain , bestFeat = 0.0, -1

    featNum = len(dataSet[0]) - 1
    for i in range(featNum):
        curFeatEntropy = 0.0
        curFeatValues = [sample[i] for sample in dataSet]
        uniqueFeatValues = set(curFeatValues)

        for value in uniqueFeatValues:
            subDataSet = splitDataSet(dataSet, i, value)
            prob = len(subDataSet) / len(dataSet)
            curFeatEntropy += prob * calcShanonEnt(subDataSet)

        if baseEntropy - curFeatEntropy > bestInfoGain:
            bestInfoGain = baseEntropy - curFeatEntropy
            bestFeat = i

    return bestFeat

def majorCnt(classList):
    '''majorCnt(统计类列表中最多类)

    Args:
        classList 类列表
    '''

    return collections.Counter(classList).most_common(1)[0]

def createTree(dataSet, featLabels):
    '''createTree(创建决策树)

    Args:
        dataSet 原始数据
        featLabels 特征标签
    '''

    classList = [sample[-1] for sample in dataSet]
    if classList.count(classList[0]) == len(classList):
        return classList[0]

    if len(dataSet[0]) == 1:
        return majorCnt(classList)

    # 选择最好的特征维度
    bestFeatIndex = chooseBestFeat(dataSet)
    featLabel = featLabels[bestFeatIndex]
    dt = {featLabel:{}}

    featValues  = [sample[bestFeatIndex] for sample in dataSet]

    uniqueFeatValues = set(featValues)

    subFeatLabels = featLabels[:bestFeatIndex] + featLabels[bestFeatIndex+1:]
    for value in uniqueFeatValues:
        # 子特征标签复制
        dt[featLabel][value] = createTree(splitDataSet(dataSet, bestFeatIndex, value), subFeatLabels)
    return dt

def classify(dt, featLabels, testVec):
    '''classify(对测试用例分类)

    Args:
        dt 决策树
        featLabels 特征标签集
        testVec 要分类的测试用例

    Returns:
        所属类别
    '''

    splitFeatLabel = list(dt.keys())[0]

    secondDict = dt[splitFeatLabel]

    featIndex = featLabels.index(splitFeatLabel)

    print(featIndex)
    print(testVec)
    print(len(testVec), type(testVec))
    value = testVec[featIndex]
    print(value)
    if type(secondDict[value]) is dict:
        return classify(secondDict[value], featLabels, testVec)
    else:
        return secondDict[value]

def storeTree(dt, filename):
    import pickle

    with open(filename, 'w') as fw:
        pickle.dump(dt, fw)

def grabTree(filename):
    import pickle
    fr = open(filename)
    return pickle.load(fr)

def fishTest():
    dataSet, featLabels = createFishData()

    dt = createTree(dataSet, featLabels)

    print("predict label:%s"%classify(dt, featLabels, [1,1]))
    print("real label:yes")

    dtPlot.createPlot(dt)

def contactLensesTest():
    ''' 隐形眼镜测试
    '''

    fr = open('../../../data/DecisionTree/lenses.txt')

    dataSet = [line.strip().split('\t') for line in fr.readlines()]

    featLabels = ['age', 'prescript', 'astigmatic', 'tearRate']

    dt = createTree(dataSet, featLabels)

    print("predict label:%s"%classify(dt, featLabels, ['presbyopic', 'myope', 'no', 'reduced']))
    print("real label:%s"%("no lenses"))
    dtPlot.createPlot(dt)

#fishTest()
contactLensesTest()
