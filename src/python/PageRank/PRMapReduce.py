#coding:utf-8

'''
created on 2017/12/06
author@BigNewbie
功能: 基于MapReduce求解网页PR值
参考文献: PageRank算法的复杂程度怎么样？https://www.zhihu.com/question/19555545?utm_campaign=rss&utm_medium=rss&utm_source=rss&utm_content=title
          PageRank算法--从原理到实现  http://blog.csdn.net/rubinorth/article/details/52215036

'''
print(__doc__)

from pygraph.classes.digraph import digraph
from itertools import groupby

class MapReduce():
    __doc__ = '''提供MapReduce功能'''

    @staticmethod
    def map_reduce(key_value, mapper, reducer):
        '''map_reduce(使用自定义mapper和reducer方法对key_value进行MapReduce)

        Args:
            key_value 键值对，需要处理的原始数据
            mapper 自定义map方法
            reducer 自定义reduce方法

        Returns:
            返回归约数据
        '''
        intermediate = [] # 存放所有(intermediate_key, intermediate_value)
        for key,value in key_value.items():
            intermediate.extend(mapper(key, value))

        # 存放集合结果
        groups = {}
        for key, group in groupby(sorted(intermediate, key=lambda x:x[0]), key=lambda x:x[0]):
            groups[key] = [y for x,y in group]

        return [reducer(key, groups[key]) for key in groups]

class PRMapReduce():
    __doc__ = '基于PageRank实现map和reduce操作'

    def __init__(self, dg):
        self.dampling_factor = 0.85 # 阻尼系数
        self.max_iterations = 100 # 最大迭代次数
        self.min_delta = 0.00001 # 迭代终止的最小误差
        self.digraph = dg
        self.num_of_page = len(dg.nodes())

        self.graph={}
        for node in dg.nodes():
            self.graph[node] = [1.0 / self.num_of_page, len(dg.neighbors(node)), [neighbor for neighbor in dg.neighbors(node)]]

    def ip_mapper(self, key, value):
        '''ip_mapper(获取无输出网页key和PR值)

        key: 网页IP，这里使用1代指无输出链接网页
        value: 3元组(PR值, num_of_neigh, neigh_list)
        '''
        if value[1]==0:
            return [1, value[0]]
        else:
            return []

    def ip_reducer(self, key, values):
        '''ip_reducer(将单个网页对应的PR值合并)
        '''

        return sum(values)

    def pr_mapper(self, key, value):
        '''pr_mapper(将正常网页PR值分离)

        key: 正常网页ip
        value: 3元组(PR值, num_of_neigh, neigh_list)
        '''
        if value[1]==0:
            return []
        return [(key, 0)] + [(neighbor, value[0]/value[1]) for neighbor in value[2]]

    def pr_reducer(self, key, values, pr):
        '''pr_reducer(合并网页PR值)

        Args:
            key 网页关键字
            values 各个其他网页投给该网页的pr值
            dg 封闭网页总pr值
        '''

        return (key, self.dampling_factor * sum(values) +
               self.dampling_factor * pr / self.num_of_page +
               (1 - self.dampling_factor) / self.num_of_page)

    def page_rank(self):
        '''page_rank(调度map和reduce实现分布式mapreduce操作)
        '''

        flag = False
        iteration = 0
        for i in range(self.max_iterations):
            iteration += 1
            # 先获取闭塞网页pr值
            dangling_list = MapReduce.map_reduce(self.graph, self.ip_mapper, self.ip_reducer)

            if dangling_list:
                dp = dangling_list[0]
            else:
                dp = 0

            new_pr = MapReduce.map_reduce(self.graph, self.pr_mapper, lambda x,y:self.pr_reducer(x,y,dp))

            change = sum([abs(new_pr[i][1] - self.graph[new_pr[i][0]][0]) for i in range(self.num_of_page)])

            for i in range(self.num_of_page):
                self.graph[new_pr[i][0]][0] = new_pr[i][1]

            print("Change:"+str(change))
            if change <= self.min_delta:
                flag = True
                break;

        if flag:
            print("finished in %d iterations"%(iteration+1))
        else:
            print("finished out of 100 iterations")

        return self.graph

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

    pr = PRMapReduce(dg)
    PR = pr.page_rank()

    print("The final page rank is:\n")
    for key,value in PR.items():
        print(key + " : ", value[0])

if __name__ == '__main__':
    main()

