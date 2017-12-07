#coding:utf-8

'''
created on 2017/12/06
author@BigNewBie
完成功能: 基于KNN 约会人员分类+手写体识别
参考博客: 【机器学习实战】第2章 K-近邻算法(k-NearestNeighbor，KNN) http://www.cnblogs.com/jiangzhonglian/p/7560781.html
'''

print(__doc__)

import numpy as np
import os
import collections

def datingfile2matrix(filepath):
    '''datingfile2matrix(读取约会数据)

    Args:
        filepath 约会数据信息

    Returns:
        data,label 约会数据和标签
    '''
    f = open(filepath)
    m = len(f.readlines())

    # 分别存储约会数据和类别
    mat_data = np.zeros((m,3))
    label = np.zeros(m)

    print(f.readlines())
    index = 0
    for line in f.readlines():
        res = line.strip().split('\t')
        print(res)
        mat_data[index,:] = res[0:3]
        label[index] = int(res[-1])
        index += 1
    print(mat_data)
    return mat_data, label

def norm_matrix(data_mat):
    '''norm_matrix(对二维矩阵正则化，列为特征)

    Args:
        data_mat 二维矩阵

    Returns:
        norm_mat 正则化矩阵
        min_vec 最小值向量
        range_vec 变化范围向量
    '''

    # 数据大小
    m = data_mat.shape[0]

    min_vec = data_mat.min(0)
    max_vec = data_mat.max(0)
    range_vec = max_vec - min_vec

    norm_mat = (data_mat - np.tile(min_vec, (m, 1))) / np.tile(range_vec, (m, 1))

    return norm_mat, min_vec, range_vec

def knn_classify(inp, data, label, k):
    '''knn_classify(基于knn对inp数据进行分类，样例数据为data,label)

    Args:
        inp 需要分类的数据
        data 标准数据
        label 标准数据标签
        k KNN算法中k的取值
    '''

    # m记录样例数据个数
    m = data.shape[0]
    diff = data - np.tile(inp, (m, 1))
    dist = np.mean(diff**2, axis=1)

    # 获取距离排序下标
    sort_index = np.argsort(dist)[0:k]

    k_label = label[sort_index]

    return collections.Counter(k_label).most_common(k)[0][0]

def knnDatingTest():
    '''knn_dating_test(使用knn对约会数据进行测试)
    '''
    # 读取数据
    data_mat, label = datingfile2matrix('../../../data/KNN/datingTestSet2.txt')
    norm_mat, min_vec, range_vec = norm_matrix(data_mat)
    # 获取数据个数和测试个数
    rate = 0.1
    m = data_mat.shape[0]
    test_num = int(m*rate)

    error_num = 0
    for i in range(test_num):
        pre_y = knn_classify(norm_mat[i,:], norm_mat[test_num:,:], label[test_num:], 3)
        if pre_y != label[i]:
            error_num += 1
    print("KNN Dating Test error number:%d"%error_num)
    print("KNN Dating Test total error rate:%f"%(error_num/test_num))

def imgfile2vec(filepath):
    '''imgfile2vec(读取图片文本文件32*32格式，转化为1024向量)

    Args:
        filepath 手写数字文本文件，命名标准为 digit_sequence.txt

    Returns:
        返回1024维向量
    '''
    img_vec = np.zeros(1024)

    f = open(filepath)
    for i in range(32):
        line = f.readline()
        for j in range(32):
            img_vec[i*32+j] = int(line[j])

    return img_vec

def knnHandWritingDigitTest():
    '''knnHandWritingDigitTest(knn手写体识别测试，其中测试和训练数据均为集合)
    '''

    # 获取所有训练手写体文件列表
    trainingDir = "../../../data/KNN/trainingDigits/"
    trainingFileList = os.listdir(trainingDir)

    # 获取数据大小
    m = len(trainingFileList)

    train_data_mat = np.zeros((m, 1024))
    train_label = np.zeros(m)

    index = 0
    for trainingfile in trainingFileList:
        train_data_mat[index, :] = imgfile2vec(trainingDir+trainingfile)
        train_label[index] = int(trainingfile.split('_')[0])
        index += 1


    # 测试
    testDir = "../../../data/KNN/testDigits/"
    testFileList = os.listdir(testDir)
    error_num = 0
    test_num = len(testFileList)

    for testfile in testFileList:
        test_data = imgfile2vec(testDir+testfile)
        test_label = int(testfile.split("_")[0])

        pred_label = knn_classify(test_data, train_data_mat, train_label, 3)

        if pred_label!=test_label:
            error_num += 1
    print("handwriting digit test error number:%d"%error_num)
    print("handwriting digit test error rate:%f"%(error_num/test_num))

if __name__ == '__main__':
    knnDatingTest()
    knnHandWritingDigitTest()

