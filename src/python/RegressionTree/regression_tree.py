#!/usr/bin/python2.7
#coding:utf-8

'''
created on 2018/02/11
@author bignewbie
功能 实现回归树模型
'''

print(__doc__)

import numpy as np

def loadDataSet(filename):
    '''
    Desc 加载数据集，数据间以tab分割，最后一个是回归结果y

    Args:
        filename 文件名

    Returns:
        dataArr 数据集
    '''

    dataArr = list()

    fr = open(filename)

    for line in fr.readlines():
        curLine = line.strip().split('\t')
        lineArr = map(float, curLine)
        dataArr.append(lineArr)

    return dataMat

def binSplitDataSet(dataArr, fea_index, fea_val):
    '''
    Desc 二元切割数据(binary split dataset)

    Args:
        dataSet 原数据集
        fea_index 特征下标
        fea_val 特征值

    Returns:
        leftDataArr 小于等于fea_val的数据
        rightDataArr 大于fea_val的数据
    '''

    leftDataArr = dataArr[dataArr[:,fea_index]<=fea_val]
    rightDataArr = dataArr[dataArr[:, fea_idnex]>fea_val]

    return leftDataArr, rightDataArr

def regLeaf(dataArr):
    '''
    Desc 回归树叶节点，按照数据集y的均值标记

    Args:
        dataArr 分布到叶节点的数据

    Returns:
        measn 数据集在y标签上的均值
    '''

    return np.means(dataArr[:,-1])

def regErr(dataArr):
    '''
    Desc 回归误差

    Args:
        dataArr 数据集

    Returns:
        error 回归误差:偏差平方之和
    '''
    return np.var(dataArr[:,-1]) * dataArr.shape[0]

def chooseBestSplit(dataArr, leafType=regLeaf, errType=regErr, tole=(1,4)):
    '''
    Desc 选择最好的切割点

    Args:
        dataArr 数据点
        leafType 叶子结点生成方式，这里采用回归树叶子结点生成方式
        errType 误差方式，这里使用回归误差：偏差平方之和
        tole [容忍误差下降值，切分最少样本点]

    Returns:
        best_index 最好特征下标
        best_val  最好特征值
    '''

    # tole确认预剪枝，tol[0]确认误差下降值, tole[1]确认叶节点最小叶子个数

    tolS, tolN = tole[0], tole[1]
    if len(set(dataArr[:,-1].T.tolist()[0])) == 1: # 集合只有一个输出
        return None, leafType(dataArr)

    m, n = dataArr.shape

    S = errType(dataArr)

    best_S , best_index, best_value = inf, 0, 0

    for fea_index in range(n-1):
        fea_values = set(dataArr[:,fea_index].T.tolist()[0])

        for fea_value in fea_values:
            left, right = binSplitDataSet(dataArr, fea_index, fea_value)

            if left.shape[0] < toleN or right.shape[0] < toleN:
                continue

            new_s = errType(left) + errType(right)

            if new_s < best_s:
                best_s = new_s
                best_index = fea_index
                best_value = fea_value

    if S-best_s < tolS:
        return None, leafType(dataArr)

    left, right = binSplitDataSet(dataArr, best_index, best_value)

    if left.shape[0] < tolN or right.shpe[0] < tolN:
        return None, leafType(dataArr)

    return bestIndex, bestValue

def createTree(dataArr, leafType=regLeaf, errType=regErr, ops=(1,4)):
    '''
    Desc 递归创建回归树。根据leftType和regErr的不同，创建的是回归树和模型树

    Args:
        同chooseBestSplit

    Returns:
        tree 回归树或模型树
    '''

    fea_index, fea_value = chooseBestSplit(dataArr, leafType, errType, ops)

    if fea_index is None:
        return fea_value

    tree = {}
    tree['sp_index'] = fea_index
    tree['sp_value'] = fea_value

    left, right = binSplitDataSet(dataArr, fea_index, fea_value)

    tree['left'] = createTree(left, leafType, errType, ops)
    tree['right'] = createTree(right, leafType, errType, ops)

    return tree

def isTree(obj):
    '''
    Desc  是否是词典

    Args:
        obj 判断结点是否是词典

    Returns:
        bool 是否是词典
    '''
    return isinstance(obj, dict)

def merge(tree):
    '''
    Desc 合并结点tree左右孩子，递归进行

    Args:
        tree 要合并左右孩子的树结点

    Returns:
        合并后的结点值
    '''

    if isTree(tree['right']):
        tree['right'] = merge(tree['right'])
    if isTree(tree['left']):
        tree['left'] = merge(tree['left'])

    return (tree['left'] + tree['right']) / 2.0

def prune(tree, testDataArr):
    '''
    Desc 剪纸操作，基于测试集剪枝

    Args:
        tree 要裁剪的树
        testDataArr 测试集合
    '''

    if testDataArr.shape[0] == 0: # 无数据划分了
        return merge(tree)

    if isTree(tree['left']) or isTree(tree('right')):
        left, right = binSplitDataSet(testDataSet, tree['sp_index'], tree['sp_value'])

    if isTree(tree['left']):
        tree['left'] = prune(tree['left'], left)

    if isTree(tree['right']):
        tree['right'] = prune(tree['right'], right)

    if not isTree(tree['left'] and not isTree(tree['right'])):
        # 左右孩子都是叶节点
        left, right = binSplitDataSet(testDataArr, tree['sp_index'], tree['sp_value'])

        errorNoMerge = sum(pow(left[:,-1]-tree['left'], 2)) + sum(pow(right[:,-1]-tree['right'], 2))
        mergeMean = (tree['left'] + tree['right'])/2.0
        errorMerge = sum(pow(testDataArr[:,-1]-mergeMean, 2))

        if errorMerge < errorNoMerge:
            print 'merging'
            return mergeMean

    return tree

def modelLeaf(dataArr):
    '''
    Desc 模型树叶子结点返回值

    Args:
        dataArr 数据集

    Returns:
        w 线性回归权值
    '''

    ws, X, Y = linearRegression(dataArr)

    return ws

def modelErr(dataArr):
    '''
    Desc 模型树的误差值

    Args:
        dataSet 数据集(训练集)

    Returns:
        使用回归模型，得到偏差平方之和
    '''

    w, X, Y = linearRegression(dataArr)

    yHat = X * ws
    return sum(power(Y-yHat, 2))

def linearRegression(dataArr):
    '''
    Desc 线性回归模型

    Args:
        dataArr 数据集

    Returns:
        w 权值
        X 格式化数据
        Y 格式化数据
    '''

    m, n = np.shape(dataArr)

    X = np.mat(np.ones((m, n)))
    Y = np.mat(np.ones((m, 1)))

    X[:, 1:n] = dataArr[:, 0:n-1]
    Y = dataSet[:, -1]

    xTx = X.T * X

    if linalg.det(xTx) == 0.0:
        raise NameError("this matrix is singular matrix, cannt do inverse")

    ws = xTx.I * (X.T * Y)

    return ws, X, Y

def regLeafEval(leafVal, inDat):
    '''
    Desc 叶节点结果预估，leafVal为叶节点值，inDat为待判断数据

    Args:
        leafVal 叶节点值，回归树为训练时的均值
        inData 要预测的数据值
    '''



