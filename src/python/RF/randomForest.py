#!/usr/bin/python
# coding : utf-8

'''
created on 2018/01/15
@author: BigNewbie
功能: 随机森林, 根据特征判断是否是声纳信号
参考文献: 【机器学习实战】第7章 集成方法 ensemble method http://www.cnblogs.com/jiangzhonglian/p/7698312.html
'''

print(__doc__)

def loadDataSet(filename):
    '''
    加载声纳信号信息

    Args:
        filename 文件路径

    Returns:
        dataSet 数据集
    '''

    dataSet = []

    fr = open(filename)

    for line in fr.readlines():
        lineArr = []
        for feature in line.split(','):
            str_f = feature.strip()
            if str_f.isalpha(): # 如果是字母，说明是标签
                lineArr.append(str_f)
            else: # 非字符，浮点数，是特征
                lineArr.append(float(str_f))

        dataSet.append(lineArr)

    return dataSet

def cross_validation_split(dataSet, n_folds):
    '''
    交叉验证，将数据集分成n_folds份

    Args:
        dataSet 原始数据集
    '''

    fold_size = len(dataSet)//n_folds

    dataSet_copy = list(dataSet)

    dataSet_folds = list()

    for i in range(n_folds):
        fold = list()

        for j in range(fold_size):

            index = random.randrange(len(dataSet_copy))

            # 无放回取样
            #fold.append(dataSet_copy.pop(index))
            # 有放回取样
            fold.append(dataSet_copy[index])
        dataSet_folds.append(fold)

    return dataSet_folds

def split_dataSet(dataSet, index, value):
    '''
    切割数据集，根据特征下标index，取值value

    Args:
        dataSet 要切割的数据集
        index  特征维度下标
        value 特征index下取值value时切割
    '''

    left = dataSet[dataSet[:, index] <= value]
    right = dataSet[dataSet[:, index] > value]

    return left, right

def gini(groups, class_values):
    '''
    根据左右数据集，计算Gini指数

    Args:
        groups 分割的数据集，（left, right）左右数据集
        class_values 类别值

    Return:
        gini Gini指数
    '''

    gini = 0.0

    D = len(groups[0]) + len(groups[1])

    for class_value in class_values:
        for group in groups:
            size = len(group)

            if size == 0:
                continue

            proportion = [row[-1] for row in group].count(class_value) / size

            gini += float(size)/D * proportion * (1-proportion)

    return gini

def get_split()


