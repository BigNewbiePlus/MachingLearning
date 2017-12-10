# coding:utf-8

'''
created on 2017/12/10
@author BigNewbie
实现功能 对构建的决策树图形化
参考文献 https://github.com/apachecn/MachineLearning/blob/master/src/python/3.DecisionTree/decisionTreePlot.py

'''
print(__doc__)

import matplotlib.pyplot as plt

# 定义文本框和箭头样式【sawtooth 波浪方框 round4 矩形方框 fc表示字体颜色深浅，0.1～0.9颜色依次变浅】
dtNode = dict(boxstyle="sawtooth", fc="0.8")
dtLeaf = dict(boxstyle='round4', fc="0.8")
arrow = dict(arrowstyle='<-')


def getTreeLeafNum(dt):
    '''getTreeLeftNum(获取决策树叶子节点个树，以此设置画图时根结点间距)

    Args:
        dt 决策树

    Returns:
        返回决策树叶节点个数
    '''

    leafNum = 0

    featLabel = list(dt.keys())[0]
    secondDict = dt[featLabel]

    for key in secondDict:
        if type(secondDict[key]) is dict:
            leafNum += getTreeLeafNum(secondDict[key])
        else:
            leafNum += 1

    return leafNum


def getTreeDepth(dt):
    '''getTreeDepth(获取决策树深度，便于设置纵向间距)

    Args:
        dt 决策树
    '''

    maxDepth = 0

    featLabel = list(dt.keys())[0]
    secondDict = dt[featLabel]

    for key in secondDict:
        if type(secondDict[key]) is dict:
            depth = getTreeDepth(secondDict[key]) + 1
        else:
            depth = 1

        if depth > maxDepth:
            maxDepth = depth

    return maxDepth

def textPlot(arrowText, curPt, parenPt):
    '''textPlot(画文本标签，parenPt父节点坐标, curPt当前节点坐标，text要在两个节点间标记的文本)

    Args:
        text 要显示的文本
        parenPt 父节点
        curPt 当前节点
    '''

    xMid = (parenPt[0] + curPt[0]) / 2.0
    yMid = (parenPt[1] + curPt[1]) / 2.0
    createPlot.ax1.text(xMid, yMid, arrowText, va='center', ha='center', rotation=30)

def nodePlot(nodeLabel, curPt, parenPt, nodeType):
    '''nodePlot(plot决策树节点)

    Args:
        nodeLabel 节点标签
        curPt 当前节点
        parenPt 父节点
    '''

    createPlot.ax1.annotate(nodeLabel, xy=parenPt, xycoords='axes fraction', xytext=curPt, textcoords='axes fraction', va='center', ha='center', bbox=nodeType, arrowprops=arrow)

def treePlot(dt, parenPt, arrowText):
    '''treePlot(plot决策树)
    '''

    featLabel = list(dt.keys())[0]
    secondDict = dt[featLabel]

    leftNum = getTreeLeafNum(dt)

    centerPt = (treePlot.xoff + (1.0+leftNum)/2/treePlot.totalW, treePlot.yoff)

    textPlot(arrowText, centerPt, parenPt)
    nodePlot(featLabel, centerPt, parenPt, dtNode)

    treePlot.yoff = treePlot.yoff - 1.0/treePlot.totalD

    for key in secondDict:
        if type(secondDict[key]) is dict:
            treePlot(secondDict[key], centerPt, key)
        else:
            treePlot.xoff = treePlot.xoff + 1.0/treePlot.totalW
            textPlot(key, (treePlot.xoff, treePlot.yoff), centerPt)
            nodePlot(secondDict[key], (treePlot.xoff, treePlot.yoff), centerPt, dtLeaf)

    treePlot.yoff = treePlot.yoff + 1.0/treePlot.totalD

def createPlot(dt):
    '''createPlot(plot决策树，包含画布的创建和参数初始化过程，为treePlot做准备)
    '''

    # 创建画布
    fig = plt.figure(1, facecolor='green')
    fig.clf()

    axprops = dict(xticks=[], yticks=[])

    createPlot.ax1 = plt.subplot(111, frameon=False, **axprops)

    # plotTree参数初始化
    treePlot.totalW = getTreeLeafNum(dt)
    treePlot.totalD = getTreeDepth(dt)

    treePlot.xoff = -0.5 / treePlot.totalW
    treePlot.yoff = 1.0

    treePlot(dt, (0.5, 1.0), '')

    plt.show()

# 测试数据
def retrieveDT(i):
    listOfTrees = [
        {'no sufacing':{0:'no', 1:{'flippers': {0:'yes', 1:'no'}}}},
        {'no sufacing':{0:'no', 1:{'flippers': {0:{'head':{0:'no', 1:'yes'}}, 1:'no'}}}},
    ]

    return listOfTrees[i]

#dt = retrieveDT(0)
#createPlot(dt)
