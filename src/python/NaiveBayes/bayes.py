#!/usr/bin/env python
# -*- coding:utf-8 -*-

'''
created on 2017/12/14
@author: BigNewbie
实现功能: 基本的朴素贝叶斯分类器实现 + 屏蔽留言版侮辱性言论、基于贝叶斯垃圾邮件过滤、基于RSS从个人广告获取区域词汇倾向三个项目实现
参考文献:   python正则表达式re: https://docs.python.org/2/library/re.html
            feedparser - Parse Atom and RSS feed in python : https://github.com/kurtmckee/feedparser
            理解朴素贝叶斯中的拉普拉斯平滑 https://zhuanlan.zhihu.com/p/26329951?utm_medium=social&utm_source=qq
            什么是RSS源: https://baike.baidu.com/item/rss%E6%BA%90/6365025?fr=aladdin
            你必读的RSS源有哪些？ https://www.zhihu.com/question/19580096
            【机器学习实战】第4章 基于概率论的分类方法：朴素贝叶斯 http://www.cnblogs.com/jiangzhonglian/p/7660738.html
'''

print(__doc__)

import numpy as np
import re
import feedparser

def createBoardMessage():
    '''loadDataSet(自创留言版言论数据集)

    Returns:
        postingList 留言版数据集
        labelList 留言版言论类别。0代表正常言论，1代表侮辱性言论
    '''

    postingList = [['my', 'dog', 'has', 'flea', 'problems', 'help', 'please'], #[0,0,1,1,1......]
                   ['maybe', 'not', 'take', 'him', 'to', 'dog', 'park', 'stupid'],
                   ['my', 'dalmation', 'is', 'so', 'cute', 'I', 'love', 'him'],
                   ['stop', 'posting', 'stupid', 'worthless', 'gar e'],
                   ['mr', 'licks', 'ate', 'my', 'steak', 'how', 'to', 'stop', 'him'],
                   ['quit', 'buying', 'worthless', 'dog', 'food', 'stupid']]

    labelList = [0, 1, 0, 1, 0, 1]

    return postingList, labelList

def createVocabList(dataSet):
    '''createVocabList(创建词汇列表)

    Args:
        dataSet 原数据集

    Returns:
        vocabList 词汇列表
    '''

    vocabList = set([])

    for document in dataSet:
        vocabList = vocabList | set(document)

    return list(vocabList)


def wordOfSet2Vec(vocabList, document):
    '''setOfWords2Vec(词集向量生成)

    Args:
        vocabList 词汇列表
        document 一篇待转化为词汇向量的文章

    Returns:
        docVec 文档向量
    '''

    docVec = [0]*len(vocabList)
    for word in document:
        if word in vocabList:
            docVec[vocabList.index(word)] = 1
        else:
            print("%s donnt occur in vocab list"%(word))

    return docVec

def _trainNB0(trainMatrix, trainLabel):
    '''_trainNB0(原始贝叶斯训练模型)

    Args:
        trainMatrix 训练数据集
        trainLabel 数据集标签

    Returns:
        pAbuse: 正样例概率P(c=1) = 正样例个数/所有样本
        P0Vec: 负样例条件下各词语出现概率 [P(w1|c=0), P(w2|c=0), ..., P(wn|c=0)]
        P1Vec: 正样例条件下各词语出现概率 [P(w1|c=1), P(w2|c=1), ..., P(wn|c=1)]
    '''

    numTrainDocs = len(trainMatrix)
    numWords = len(trainMatrix[0])

    pAbuse = sum(trainLabel) / float(numTrainDocs)

    P0Num = np.zeros(numWords)
    P1Num = np.zeros(numWords)

    P0Denom = 0
    P1Denom = 0

    for i in range(numTrainDocs):
        if trainLabel[i] == 1:
            P1Num += trainMatrix[i]
            P1Denom += 1
        else:
            P0Num += trainMatrix[i]
            P0Denom += 1

    P0Vec = P0Num / float(P0Denom)
    P1Vec = P1Num / float(P1Denom)
    return pAbuse, P0Vec, P1Vec

def trainNB0(trainMatrix, trainLabel):
    '''trainNB0(优化的分类模型：加入拉普拉斯平滑和概率值取对数解决连续小数相乘导致概率趋于0的问题)

    Args:
        trainMatrix 训练数据集
        trainLabel 训练数据集标签

    Returns:
        pAbuse: 正样本概率值, P(c=1) = (C(c=1) + 1 ) / (N + K)
        P0Vec : 正样例条件下各词对数概率 [log(P(w1|c=0)), log(P(w2|c=1)), ... , log(P(wn|c=0))]
        P1Vec : 负样例条件下各词对数概率 [log(P(w1|c=1)), log(P(w2|c=0)), ... , log(P(wn|c=1))]
    '''

    numTrainDocs = len(trainMatrix)
    numWords = len(trainMatrix[0])

    pAbuse = (sum(trainLabel) + 1) / float(numTrainDocs + 2)

    P0Num = np.ones(numWords)
    P1Num = np.ones(numWords)

    P0Denom = 2
    P1Denom = 2

    for i in range(numTrainDocs):
        if trainLabel[i] == 1:
            P1Num += trainMatrix[i]
            P1Denom += 1
        else:
            P0Num += trainMatrix[i]
            P0Denom += 1

    P0Vec = P0Num / float(P0Denom)
    P1Vec = P1Num / float(P1Denom)
    return pAbuse, P0Vec, P1Vec

def classifyNB(vec2classify, pAbuse, P0Vec, P1Vec):
    '''classifyNB(对待分类的词向量vec2classify分类)

    Args:
        pAbuse 正样例概率值, 拉普拉斯平滑取1时为P(c=1) = (Cnt(c=1) + 1) / (N  + K) ,其中 Cnt(c=1)正样例个数, N为样本总个数，K为类别个数，这里为2
        P0Vec 负样例条件下各个词取值1的概率, 即 [P(w1=1|c=0), P(w2=1|c=0), ..., P(wn=1|c=0)]
        P1Vec 负样例条件下各词取值为1的概率, 即 [P(w1=1|c=1), P(w2=1|c=1), ..., P(wn=1|c=1)]
    '''

    P0 = 0.0
    P1 = 0.0
    numWords = len(vec2classify)
    for i in range(numWords):
        # 单词出现wi=1，此时需要求P(wi=1|c=1)和P(wi=1|c=0)概率
        if vec2classify[i] == 1:
            P0 += np.log(P0Vec[i])
            P1 += np.log(P1Vec[i])
        else: # 单词未出现wi=0, 此时需要求P(wi=0|c=1)=1-P(wi=1|c=1) 和 p(wi=0|c=1) = 1-p(wi=1|c=0)
            P0 += np.log(1-P0Vec[i])
            P1 += np.log(1-P1Vec[i])

    P0 +=  np.log(1-pAbuse)
    P1 += np.log(pAbuse)

    if P0>P1:
        return 0
    return 1

def bagOfWords2Vec(vocabList, document):
    '''bagOfWords2Vec(转化为词袋向量)

    Args:
        vocabList 词汇列表
        document 文档列表

    Returns:
        docVec 文档向量
    '''

    numWords = len(vocabList)

    docVec = [0] * numWords

    for word in document:
        if word in vocabList:
            docVec[vocabList.index(word)] += 1

    return docVec

# --------------------------------------------------------------------------
# 基于自创留言版数据屏蔽侮辱性留言

def abuseTest():
    '''abuseTest(基于自创数据+贝叶斯分类器，进行侮辱性词汇留言版屏蔽)
    '''

    listOfPosts, listOfLabel = createBoardMessage()

    vocabList = createVocabList(listOfPosts)

    trainMatrix = []

    for document in listOfPosts:
        trainMatrix.append(wordOfSet2Vec(vocabList, document))

    pAbuse, P0Vec, P1Vec = trainNB0(trainMatrix, listOfLabel)

    # 测试数据
    testEntry = ['love', 'my', 'dalmation']
    testVec = wordOfSet2Vec(vocabList, testEntry)
    print(testEntry, "classifid as : ", classifyNB(testVec, pAbuse, P0Vec, P1Vec))

    testEntry = ['stupied', 'garbage']
    testVec = wordOfSet2Vec(vocabList, testEntry)
    print(testEntry, "classifid as : ", classifyNB(testVec, pAbuse, P0Vec, P1Vec))


# ----------------------------------------------------------
# 项目案例2：使用朴素贝叶斯过滤垃圾邮件

# 切分文本
def textParse(text):
    '''textParse(将文本文件切分为单词列表)

    Args:
        text 一个原始邮件正文

    Returns:
        document 去除标点符号的切分文本
    '''

    listOfTokens = re.split('\W*', text)
    return [token.lower() for token in listOfTokens if len(token)> 2]

def spamTest():
    '''spamTest(使用测试集+朴素贝叶斯对邮件)
    '''

    docList = []
    labelList = []

    for i in range(1, 26):
        # 读取25个垃圾邮件
        bigString = open('../../../data/NaiveBayes/email/spam/%d.txt'%i).read()
        print(bigString)
        #wordList = textParse(open('../../../data/NaiveBayes/email/spam/%d.txt'%i).read())
        #docList.append(wordList)
        #labelList.append(1)
        # 读取25个正常邮件
        #wordList = textParse(open('../../../data/NaiveBayes/email/ham/%d.txt'%i).read())
        #docList.append(wordList)
        #labelList.append(0)

    # 创建词汇
    vocabList = createVocabList(docList)

    randIndex = np.shuffle(np.range(50))
    testIndex = randIndex[:10]
    trainIndex = randIndex[10:]

    trainMatrix = []
    trainLabel = []
    for index in trainIndex:
        trainMatrix.append(wordOfSet2Vec(vocabList, docList[index]))
        trainLabel.append(labelList[index])

    pAbuse, P0Vec, P1Vec = trainNB0(trainMatrix, trainLabel)

    error_num = 0
    test_num = len(testIndex)

    for index in testIndex:
        docVec = wordOfSet2Vec(vocabList, docList[index])
        if classifyNB(docVec, pAbuse, P0Vec, P1Vec) != labelList[index]:
            error_num += 1

    print('the error count is: %d'%error_num)
    print("test number:%d"%test_num)
    print("test error :%lf"%float(error_num)/test_num)


# -------------------------------------------------------------------------------------------
# 项目案例3： 使用朴素贝叶斯从个人广告中获取区域倾向

def adRSSTest():
    '''loadDataFromRSS(从RSS源获取个人广告内容, RSS源分别为http://newyork.craigslist.org/stp/index.rss
                        和 http://sfbay.craigslist.org/stp/index.rss)
    '''

    ny_feed1 = feedparser.parse('http://newyork.craigslist.org/stp/index.rss')
    sf_feed0 = feedparser.parse('http://sfbay.craigslist.org/stp/index.rss')

    docList = []
    labelList = []

    minLen = min(len(ny_feed1['entries']), len(sf_feed0['entries']))

    for i in range(minLen):
        wordList = textParse(ny_feed1['entries'][i]['summary'])
        docList.append(wordList)
        labelList.append(1)

        wordList = textParse(sf_feed0['entries'][i]['summary'])
        docList.append(wordList)
        labelList.append(0)

    vocabList = createVocabList(docList)

    randIndex = np.shuffle(np.range(len(docList)))

    testIndex = randIndex[0:20]
    trainIndex = randIdnex[20:]

    trainMatrix = []
    trainLabel = []
    for index in trainIndex:
        wordVec = wordOfSet2Vec(vocabList, docList[index])
        trainMatrix.append(wordVec)
        trainLabel.append(labelList[index])

    pAbuse, P0Vec, P1Vec = trainNB0(trainMatrix, trainlabel)

    error_num = 0
    test_num = len(testIndex)

    for index in testIndex:
        wordVec = wordOfSet2Vec(vocabList, docList[index])
        if classifyNB(wordVec, pAbuse, P0Vec, P1Vec) == labelList[index]:
            error_num += 0


    print('the error count is: %d'%error_num)
    print("test number:%d"%test_num)
    print("test error :%lf"%float(error_num)/test_num)


# 测试
abuseTest()
spamTest()
adRSSTest()
