#coding:utf-8

'''
Created on 2017/11/14
author: fdh
FP—Growth: 韩家炜教授提出的基于FP-tree挖掘频繁项的算法，相对于Apriori只扫描
           2遍数据，效率更高， FP = Frequent Pattern
算法需要创建两个数据结构:
    1: FP-Tree
    2: Header Table

参考博客: http://www.cnblogs.com/jiangzhonglian/p/7778830.html
          https://www.cnblogs.com/datahunter/p/3903413.html#undefined

'''

print(__doc__)

class TreeNode:
    def __init__(self, name, count, parentNode):
        self.name = name
        self.count = count
        self.parent = parentNode
        self.nodelink = None
        self.children = {}

    def inc(self, count):
        self.count+=count


def loadDataSet():
    dataSet = [['a', 'b', 'c', 'd', 'e'],
               ['a', 'b', 'c', 'd', 'e'],
               ['z'],
               ['a', 'c', 'd'],
               ['a', 'b', 'z']]

    return dataSet

def initDataSet(dataSet):
    '''initDataSet(初始化数据，去除重复数据，使用计数)

    Args:
        dataSet 原始数据

    Return:
        dataSetCnt 去除重复数据，添加计数
    '''

    dataSetCnt = {}
    for trans in dataSetCnt:
        if dataSetCnt.has_key(frozenset(trans)):
            dataSetCnt[frozenset(trans)]+=1
        else:
            dataSetCnt[frozenset(trans)]=1

    return dataSetCnt

def buildTreeAndTable(dataSetCnt, minSupport=1):
    '''buildTreeAndTable(创建FP-Growth所需的树结构和表格)

    Args：
        dataSetCnt 计数数据集
        minSupport 最小支持度,用整数表示

    Return:
        FPTable 按支持度排序的链表
        FPTree 满足最小支持度的数据创建的树结构
    '''

    itemCnt={}
    for trans in dataSetCnt:
        for item in trans:
            itemCnt[item]=itemCnt.get(item,0)+dataSetCnt[trans]

    supportItem = {}
    for key in itemCnt:
        if itemCnt[key]>=





