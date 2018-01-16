#!/usr/bin/python
# coding:utf-8

'''
created on 2018/01/15
@author: BigNewbie
功能: 随机森林算法,项目实战：根据特征判断是否是声纳信号
参考文献: 【机器学习实战】第7章 集成方法 ensemble method http://www.cnblogs.com/jiangzhonglian/p/7698312.html
'''

print(__doc__)

import random

def loadDataSet(filename):
    '''
    加载声纳信号数据

    Args:
        filename 文件路径

    Returns:
        dataSet 数据集
    '''

    dataSet = list()

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

    folds = list()

    for i in range(n_folds):
        fold = list()

        while len(fold)<fold_size:

            index = random.randrange(len(dataSet_copy))

            # 无放回取样
            #fold.append(dataSet_copy.pop(index))
            # 有放回取样
            fold.append(dataSet_copy[index])
        folds.append(fold)

    return folds

def split_dataSet(dataSet, index, value):
    '''
    切割数据集，根据特征下标index，取值value

    Args:
        dataSet 要切割的数据集
        index  特征维度下标
        value 特征index下取值value时切割
    '''

    left, right = list(), list()

    for row in dataSet:
        if row[index] < value:
            left.append(row)
        else:
            right.append(row)

    return left, right

def cal_gini(groups, class_values):
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

    for group in groups:
        size = len(group)

        if size == 0:
            continue

        actual = [row[-1] for row in group]

        for class_value in class_values:

            proportion = actual.count(class_value) / float(size)

            gini += float(size)/D * proportion * (1-proportion)

    return gini

def best_split(dataSet, n_features):
    '''
    对数据集dataSet进行切割，随机选择n_features个特征

    Args:
        dataSet 待分割树节点数据
        n_features 每个节点允许选择的特征个数

    Returns:
        index，value, groups 特征下标，特征取值，分割后的数据集
    '''

    class_values = list(set(row[-1] for row in dataSet))

    b_index, b_value, b_gini, b_groups = 9999, 9999, 9999, None

    features = list()

    while len(features) < n_features:
        index = random.randrange(len(dataSet[0])-1)
        if index not in features:
            features.append(index)

    # 遍历每一维度
    for index in features:
        for row in dataSet:
            groups = split_dataSet(dataSet, index, row[index])
            gini = cal_gini(groups, class_values)

            if gini < b_gini: # 计算Gini指数并更新
                b_index, b_value, b_gini, b_groups = index, row[index], gini, groups

    return {'index':b_index, 'value':b_value, 'gini':b_gini, 'groups':b_groups}

def leaf(group):
    '''
    创建叶子节点

    Args:
        group 叶子节点数据集

    Returns:
        label 叶子节点所属label
    '''

    labels = [row[-1] for row in group]
    return max(set(labels), key=labels.count)

# 创建决策树某个分枝
def branch(node, max_depth, min_size, n_features, depth):
    '''
    创建决策树某个分枝

    Args:
        node 要分枝的节点，为辞典，内容为{'index':index, 'value':value, 'gini': gini, 'groups':groups}
        max_depth 决策树最大深度
        min_size 叶节点最小值
        n_features 可选择的最多特征数
        depth 现阶段树的深度
    '''

    left, right = node['groups']

    del(node['groups'])

    if len(left)==0 or len(right)==0:
        node['left'] = node['right'] = leaf(left+right)
        return

    if depth >= max_depth:
        node['left'], node['right'] = leaf(left), leaf(right)
        return

    if len(left) <= min_size:
        node['left'] = leaf(left)
    else:
        node['left'] = best_split(left, n_features)
        branch(node['left'], max_depth, min_size, n_features, depth+1)

    if len(right) <= min_size:
        node['right'] = leaf(right)
    else:
        node['right'] = best_split(right, n_features)
        branch(node['right'], max_depth, min_size, n_features, depth+1)

# 创建树
def build_tree(dataSet, max_depth, min_size, n_features):
    '''
    创建决策树

    Args:
        dataSet 数据集
        max_depth 最大深度
        min_size 叶子节点最大数据量
        n_features 特征数

    Returns:
        tree 创建的决策树
    '''
    root = best_split(dataSet, n_features)
    branch(root, max_depth, min_size, n_features, 1)

    return root

# 预测
def predict(tree, row):
    '''
    预测数据row结果

    Args:
        tree 决策树
        row 待预测数据

    Returns:
        label 预测结果
    '''

    if row[tree['index']] < tree['value']:
        if isinstance(tree['left'], dict):
            return predict(tree['left'], row)
        else:
            return tree['left']
    else:
        if isinstance(tree['right'], dict):
            return predict(tree['right'], row)
        else:
            return tree['right']



def bagging_predict(trees, row):
    '''
    投票预测，按照投票数最多的类别作为预测标签

    Args:
        trees 多颗决策树
        row 待预测数据

    Returns:
        label 多人投票结果
    '''

    predictions = [predict(tree, row) for tree in trees]
    return max(set(predictions), key=predictions.count)

# 创建一个数据集子集，该函数用于设置创建一颗决策树所用数据集
def subsample(dataSet, ratio):
    '''
    抽样，按照ration百分比

    Args:
        dataSet 原数据集
        ratio 百分比

    Returns:
        samples 子数据集
    '''
    samples = list()

    n_samples = int(len(dataSet) * ratio)

    for i in range(n_samples):
        index = random.randrange(len(dataSet))
        samples.append(dataSet[index])

    return samples

def random_forest(train, test, max_depth, min_size, sample_ratio, n_features, n_trees):
    '''
    随机森林算法，使用训练数据集train训练n_trees个决策树，使用test数据集测试

    Args:
        train 训练数据集
        test  测试数据集
        max_depth 最大深度
        min_size 最小叶子节点
        n_features 每个节点可用特征个数
        n_trees 树的个数

    Returns:
        predictions 测试数据集对应的预测标签
    '''

    trees = list()
    for i in range(n_trees):
        samples = subsample(train, sample_ratio)
        tree = build_tree(samples, max_depth, min_size, n_features)
        trees.append(tree)

    predictions = [bagging_predict(trees, row) for row in test]
    return predictions

def accuracy_metric(predicted, actual):
    '''
    正确率评估

    Args:
        predicted 预测值
        actual 真实值

    Returns:
        accuracy 正确率
    '''

    correct = 0
    for i in range(len(predicted)):
        if predicted[i] == actual[i]:
            correct+=1

    return float(correct) / len(actual) * 100.0

def evaluate_algorithm(dataSet, algorithm, n_folds, *args):
    '''
    评估算法性能，返回算法得分

    Args:
        dataSet 数据集
        algorithm 算法
        n_folds 数据fold数
        *args 其他数据

    Returns:
        scores 该算法得分
    '''

    scores = list()

    folds = cross_validation_split(dataSet, n_folds)
    for fold in folds:
        train = list(folds)
        train.remove(fold)

        train = sum(train, [])
        test = list()

        for row in fold:
            row_copy = list(row)
            row_copy[-1] = None
            test.append(row_copy)

        predicted = algorithm(train, test, *args)

        actual = [row[-1] for row in fold]

        score = accuracy_metric(predicted, actual)

        scores.append(score)

    return scores

if __name__ == '__main__':
    dataSet = loadDataSet('../../../data/sonar-all-data.txt')

    n_folds = 5
    max_depth = 20
    min_size = 1
    sample_ratio = 1.0
    n_features = 15
    for n_trees in [1, 10, 20, 30, 40, 50]:
        scores = evaluate_algorithm(dataSet, random_forest, n_folds, max_depth, min_size, sample_ratio, n_features, n_trees)

        random.seed(1)

        print('random:', random.random())
        print('Trees:', n_trees)
        print('scores：%s'%scores)
        print('mean Accuracy:%.3lf%%'%(sum(scores)/float(len(scores))))

