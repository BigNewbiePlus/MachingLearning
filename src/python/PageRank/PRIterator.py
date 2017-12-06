#coding:utf-8

'''
created on 2017/12/05
author@BigNewbie
功能: 基于迭代法求解网页PR值
参考文献: PageRank算法的复杂程度怎么样？https://www.zhihu.com/question/19555545?utm_campaign=rss&utm_medium=rss&utm_source=rss&utm_content=title
          PageRank算法--从原理到实现  http://blog.csdn.net/rubinorth/article/details/52215036
'''
print(__doc__)

from pygraph.classes.digraph import digraph

class PRIterator:
    __doc__ = '''计算一张地图的PR值'''

    def __init__(self, dg):
        self.damping_factor = 0.85 # 阻尼系数
        self.max_iterations = 100  # 最大迭代次数
        self.min_delta = 0.00001 # 确认迭代终止的误差值
        self.digraph = dg

    def page_rank(self):
        '''计算有向图PR值
        '''
        # 初始化一些参量
        digraph = self.digraph
        nodes = digraph.nodes()
        graph_size = len(nodes)

        if graph_size == 0:
            return {}

        # 将没有出链节点添加和其他所有节点(包括自己)连接边
        for node in nodes:
             if len(digraph.neighbors(node))==0:
                for linkNode in nodes:
                    digraph.add_edge((node, linkNode))

        # 初始化PR值
        PR = dict.fromkeys(nodes, 1/graph_size)
        damping_value = (1-self.damping_factor)/graph_size

        # 迭代
        for i in range(self.max_iterations):
            change = 0
            # 遍历每个节点，求解PR值
            for node in nodes:
                rank = 0
                for inciNode in digraph.incidents(node):
                    rank += self.damping_factor*PR[inciNode]/len(digraph.neighbors(inciNode))
                rank += damping_value
                change += abs(PR[node]-rank)
                PR[node]=rank

            # 判断是否终止
            if change <= self.min_delta:
                flag = True
                break
        if flag:
            print("finished in %d iterations."%i)
        else:
            print("finished out of iterations")

        return PR
def main():
    dg = digraph();

    dg.add_nodes(['A', 'B', 'C', 'D', 'E'])

    dg.add_edge(('A', 'B'))
    dg.add_edge(("A", "C"))
    dg.add_edge(("A", "D"))
    dg.add_edge(("B", "D"))
    dg.add_edge(("C", "E"))
    dg.add_edge(("D", "E"))
    dg.add_edge(("B", "E"))
    dg.add_edge(("E", "A"))

    pr = PRIterator(dg)
    PR = pr.page_rank()

    print("The final page rank is:\n", PR)

if __name__ == '__main__':
    main()
