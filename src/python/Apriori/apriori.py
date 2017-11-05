#!/usr/bin/python
# coding: utf-8


'''
创建于2017/11/5，
@author: BigNewbie
学习博客园：http://www.cnblogs.com/jiangzhonglian/p/7766194.html#undefined
'''

print(__doc__)
from numpy import *

# 加载数据
def loadDataSet():
    return [[1,3,4], [2,3,5], [1,2,3,5],[2,5]]

# 创建C1数据集, C表示候选集合，1表示序列下标
def createC1(dataSet):
    '''createC1(创建初始单元素候选集合)

    Args:
        dataSet 原始数据集，交易数据

    Returns:
        frozenset 最小单元素集合的frozenset集，可用于map键值
    '''


    C1=[]
    for transaction in dataSet:
        for item in transaction:
            if not [item] in C1:
                C1.append([item])

    # 排序
    C1.sort()
    return map(frozenset, C1)

def scanD(dataSet, Ck, minSupport):
    '''scanD(计算候选数据集 Ck 在原数据集 dataSet 中支持度>=minSupport的数据集合)

    Args：
        dataSet 原始数据集合
        Ck 候选数据集
        minSupport 最小支持度

    Returns：
        retList 满足最小支持度的数据集
        supportData 数据集->支持度 映射词典
    '''

    # 每个集合数量　[1,2]->5, [2,3,4]->10
    ssCnt={}
    for transaction in dataSet:
        for can in Ck:
            if can.issubset(transaction):
                if ssCnt.has_key(can):
                    ssCnt[can]+=1
                else:
                    ssCnt[can]=1

    # 计算交易数据个数
    numItems = float(len(dataSet))

    retList=[]
    supportData = {}

    for key in ssCnt:
        # 计算支持度
        support = ssCnt[key]/numItems
        if support>=minSupport:
            supportData[key]=support
            retList.append(key)

    return retList, supportData

# 输入候选集Ck与单个元素个数k， 返回可能的候选集合
def aprioriGen(Ck, k):
    '''aprioriGen(根据候选子集Ck和要生成的超集单个大小k，返回所有可能集合
       例如：Ck={0},{1},{2}, k=2, 其中k=len(Ck[0])+1, 可生成的集合为{0,1},{0,2},{1,2}。
       Ck={0,1},{0,2},k=3, 生成集合为 {0,1,2})

    Args:
        Ck 初始集合，每个元素大小k-1， 两两组合生成k大小集合
        k 要生成的超集单个元素大小

    Returns：
        retList 两两元素合并列表
    '''

    retList = []
    lenCk = len(Ck)

    for i in range(lenCk):
        for j in range(i+1, lenCk):
            L1 = list(Ck[i])[0:k-2]
            L2 = list(Ck[j])[0:k-2]
            L1.sort()
            L2.sort()

            if L1==L2:
                retList.append(Ck[i]|Ck[j])

    return retList

# 生成满足最低支持度的频繁集合
def apriori(dataSet, minSupport):
    '''apriori(从数据集dataSet中生成满足最低支持度的频繁集合)

    Args:
        dataSet 原始数据集
        minSupport 最低支持度

    Returns：
        L 频繁项集的全集
        supportData 带有支持度的词典
    '''

    C1 = createC1(dataSet)
    D = map(set, dataSet)

    L1, supportData = scanD(D, C1, minSupport)

    L=[L1]
    k=2

    while len(L[k-2])>0:
        # 产生新的候选集
        Ck = aprioriGen(L[k-2], k)
        # 从候选集找出满足支持度的子集
        Lk, Sk = scanD(D, Ck, minSupport)

        # 更新数据集
        supportData.update(Sk)

        if len(Lk)==0:
            break
        L.append(Lk)
        k+=1

    return L, supportData

# 计算数据集中可信度>=minConf的集合
def calConf(freqSet, H, supportData, relations, minConf):
    '''calConf(计算元素freqSet中，元素间可信度。例如：{1,2}/{1}, {1,3}/3)

    Args:
        freqSet 频繁项集的元素，例如：frozenset({1,2,3})
        H 推导结果元素集合，如{frozenset({1}), frozenset({2})}
        supportData 所有频繁项集元素的支持度
        relations 关联关系，单个元素是三元组
        minConf: 最小可信度

    Returns：
        prunH 裁剪后的推导结果集合
    '''

    prunH = []

    for conseq in H:
        conf = supportData[freqSet-conseq]/supportData[conseq]
        if conf >=  minConf:
            relations.append((freqSet-conseq, conseq, conf))
            prunH.append(conseq)

    # 如果新裁剪的推导项集合不为空且当前频繁项集合元素大小> 推导项+1
    # 例如 freqSet:[1,2,3], prunH={frozenset({1})}, 则递归，否则退出
    if len(prunH)>0 and len(freqSet)> len(prunH[0])+1:
        Htmp = aprioriGen(prunH, len(prunH[0])+1)
        calConf(freqSet, Htmp, supportData, relations, minConf)

    return prunH

# 生成关联规则
def genRules(L, supportData, minConf):
    '''genRules(从生成的频繁项集合生成关联规则)

    Args：
        L 生成的频繁项集合
        supportData 保存有支持度的频繁项词典
        minConf 关联规则最小可信度

    Returns:
        bigRuleList 关联规则集合，每个规则三元组(A,B,置信度) A->B

    '''


    bigRuleList = []

    for i in range(1, len(L)):
        for freqSet in L[i]:
            H = [frozenset([item]) for item in freqSet]
            calConf(freqSet, H, supportData, bigRuleList, minConf)

    return bigRuleList


def testApriori():
    dataSet = loadDataSet()
    print 'dataSet',dataSet

    # Apriori算法生成频繁项集和支持度
    L1, supportData = apriori(dataSet, minSupport=0.7)
    print ''
    print 'L(0.7)', L1
    print 'supportData', supportData

    L2, supportData2 = apriori(dataSet, minSupport=0.5)
    print ''
    print 'L(0.5)', L2
    print 'supportData', supportData2
    print ''


def testGenRules():

    dataSet = loadDataSet()
    print 'dataSet',dataSet
    print ''
    # Apriori算法生成频繁项集和支持度
    L1, supportData = apriori(dataSet, minSupport=0.7)

    print 'L(0.7)', L1
    print 'supportData', supportData

    print ''
    rules = genRules(L1, supportData, minConf=0.5)
    print 'rules', rules

def main():
    print('测试Apriori算法')
    testApriori()

    print ''

    print('测试关联规则生成')
    testGenRules()

if __name__ == '__main__':
    main()

