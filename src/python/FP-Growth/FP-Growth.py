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
        self.nextlink = None
        self.children = {}

    def inc(self, count):
        self.count+=count
    def disp(self, depth=1):
        """disp(以文本形式展示树结构)

        """
        print ' '*depth, self.name,' ', self.count
        for child in self.children.values():
            child.disp(depth+1)

def loadDataSet():
    dataSet = [['f', 'a', 'c', 'd', 'g', 'i', 'm', 'p'],
               ['a', 'b', 'c', 'f', 'l', 'm', 'o'],
               ['b', 'f', 'h', 'j', 'o'],
               ['b', 'c', 'k', 's', 'p'],
               ['a', 'f', 'c', 'e', 'l', 'p', 'm', 'n']]

    return dataSet

def calDataSetCnt(dataSet):
    '''initDataSet(初始化数据，去除重复数据，使用计数)

    Args:
        dataSet 原始数据

    Return:
        dataSetCnt 去除重复数据，添加计数
    '''

    dataSetCnt = {}
    for trans in dataSet:
        if dataSetCnt.has_key(frozenset(trans)):
            dataSetCnt[frozenset(trans)]+=1
        else:
            dataSetCnt[frozenset(trans)]=1

    return dataSetCnt

def updateTable(treeNode, item, FPHeaderTable):
    headNode = FPHeaderTable[item][1]
    if headNode is None:
        FPHeaderTable[item][1]=treeNode
    else:
        while headNode.nextlink:
            headNode = headNode.nextlink
        headNode.nextlink= treeNode

def updateTreeAndTable(orderItem, cnt, FPHeaderTable, FPTree):
    '''updateTreeAndTable(将排好序的单项条目添加到FP树和表格中)

    Args:
        orderItem 当个排序条目
        FPHeaderTable FP头表格
        FPTree FP树

    '''

    treeNode = FPTree
    #递归调用树节点
    for item in orderItem:
        if treeNode.children.has_key(item):
            treeNode.children[item].count+=cnt
        else:
            treeNode.children[item] = TreeNode(item, cnt, treeNode)
            updateTable(treeNode.children[item], item, FPHeaderTable)
        treeNode = treeNode.children[item]

def buildTreeAndTable(dataSetCnt, minSupport=1):
    '''buildTreeAndTable(创建FP-Growth所需的树结构和表格)

    Args：
        dataSetCnt 计数数据集
        minSupport 最小支持度,用整数表示

    Return:
        FPHeaderTable 按支持度排序的链表
        FPTree 满足最小支持度的数据创建的树结构
    '''

    #创建FP表格
    FPHeaderTable={}
    for trans,cnt in dataSetCnt.items():
        for item in trans:
            FPHeaderTable[item]=FPHeaderTable.get(item,0)+cnt

    #print '过滤前：',FPHeaderTable

    #过滤掉低频数据
    FPHeaderTable = {k:[v,None] for k,v in FPHeaderTable.items() if v>=minSupport}

   # print 'FPTable:',FPHeaderTable
    freqItemSet = set(FPHeaderTable.keys())
   # print '频繁集合',freqItemSet
    if len(freqItemSet)==0:
        return None, None

    #FP树
    FPTree = TreeNode("NULL", 1, None)

    #第二遍数据遍历
    for trans,cnt in dataSetCnt.items():
        localD = {}
        for item in trans:
            if item in freqItemSet:
                localD[item] = FPHeaderTable[item][0]

        #print 'localD', localD.keys()

        #存在可用数据
        if len(localD)>0:
            orderItem = [k for k,v in sorted(localD.items(), key=lambda x:x[1], reverse=True)]
         #   print 'orderItem cnt:',cnt,' items:', orderItem
            updateTreeAndTable(orderItem, cnt, FPHeaderTable, FPTree)

    return FPTree, FPHeaderTable


def findPrefixPath(treeNode):
    dataSetCnt= {}
    headNode=treeNode
    while headNode:
        endNode = headNode.parent
        newTrans = []
        count = headNode.count
        while endNode.parent:
            newTrans.insert(0, endNode.name)
            endNode = endNode.parent
        dataSetCnt[frozenset(newTrans)]=count
        headNode= headNode.nextlink
    return dataSetCnt

def FP_Growth(dataSetCnt, minSupport, prelist):
    '''FP_Growth(挖掘频繁项集)

    Args:
        FPTable FP表
        FPTree  FP树

    Return 打印出挖掘的频繁项集
    '''

    FPTree, FPTable = buildTreeAndTable(dataSetCnt, minSupport)
    if FPTable is None:
        return

    #print 'tree view:'
    #FPTree.disp()

    orderFPTable = [v[1] for k,v in sorted(FPTable.items(), key=lambda x:x[1][0])]
    #print 'orderFPTable', [v.name for v in orderFPTable]
#    print '******************************'
    for tableNode in orderFPTable:
        print tableNode.name, prelist
    if len(orderFPTable):
        print prelist
 #   print '****************************'

    for tableNode in orderFPTable:
  #      print '遍历元素',tableNode.name
        newDataSetCnt = findPrefixPath(tableNode)
   #     print '元素',tableNode.name,'前数据', newDataSetCnt
        newPrelist = [v for v in prelist]
        newPrelist.append(tableNode.name)

        FP_Growth(newDataSetCnt, minSupport, newPrelist)

def main():
    dataSet = loadDataSet();
    dataSetCnt = calDataSetCnt(dataSet)
    prelist= []
    FP_Growth(dataSetCnt, 3, prelist)

if __name__ == '__main__':
    main()

