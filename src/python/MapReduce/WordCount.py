#coding:utf-8

'''
created on 2017/12/03
author@BigNewbie
参考学习: MapReduce实现词频统计 https://www.cnblogs.com/rubinorth/p/5780531.html#undefined
          Write your first MapReduce program in 20 minutes  http://michaelnielsen.org/blog/write-your-first-mapreduce-program-in-20-minutes/
实现功能: 使用MapReduce统计词频
'''

print(__doc__)

import string
from itertools import groupby

class MapReduce():
    __doc__ = '''提供MapReduce功能'''

    @staticmethod
    def map_reduce(key_value, mapper, reducer):
        """map_reduce(读取key_value，使用自定义mapper和reducer对key_value进行词频统计)

        Args:
            key_value: 键值对，key使用文件名标记,value为文件对应的内容
            mapper: 自定义map方法
            reducer: 自定义reduce方法

        Returns:
            使用mapper和reducer处理后的词频
        """

        intermediate = []
        for key, value in key_value.items():
            intermediate.extend(mapper(key,value))

        groups={}
        for key, group in groupby(sorted(intermediate, key=lambda x:x[0]), key=lambda x:x[0]):
            groups[key] = [y for x, y in group]

        return [reducer(key, value) for key, value in groups.items()]

class WordCount():
    __doc__ = '''提高词频统计，自定义mapper和reducer'''

    def mapper(self, key, value):
        """mapper(自定义mapper函数，统计文件key中文本value内单词，每个单词记为(word, 1))

        Args:
            key 关键字，本处使用文件名区分
            value 文件内文本内容

        Returns:
            返回统计的词频列表，每个单词单独返回，不合并。如This cut dog. 返回[('this',1), ('cute',1), ('dog',1)]
        """

        return [(word,1) for word in self.rm_punc(value.lower()).split()]

    def reducer(self, key, values):
        """reducer(自创建reducer方法，将同词词频合并)

        Args:
            key 单个词
            values 单词出现的个数列表

        Returns:
            合并后的词频
        """
        return (key, sum(values))

    def rm_punc(self, content):
        """rm_prun(去除文本内标点符号)

        Args:
            待去除标点的文本

        Returns:
            返回去除标点后的文本
        """

        return content.translate(None, string.punctuation)


def main():
    filenames = ['../../../data/MapReduce/a.txt', '../../../data/MapReduce/b.txt', '../../../data/MapReduce/c.txt']
    key_value = {}
    for filename in filenames:
        f = open(filename)
        key_value[filename]=f.read()
        f.close()

    wc = WordCount()

    print(MapReduce.map_reduce(key_value, wc.mapper, wc.reducer))

if __name__ == '__main__':
    main()

