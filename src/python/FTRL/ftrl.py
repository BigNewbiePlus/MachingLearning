#!/user/bin/python
#coding:utf8

'''
Created on 2018/04/16
Author fangdenghui
Function: forward the regularized leader
Referebce : 算法介绍：https://blog.csdn.net/dengxing1234/article/details/73277251
            代码实现(java)：https://blog.csdn.net/luoyexuge/article/details/53837063
            代码实现(python): https://www.cnblogs.com/zhangchaoyang/articles/6854175.html
'''
print(__doc__)

import numpy as np

class LR(object):

    @staticmethod
    def fn(w, x):
        '''
        Desc 激活函数为sigmod函数
        '''
        return 1.0 / (1.0 + np.exp(-w.dot(x)))

    @staticmethod
    def loss(y, y_hat):
        '''
        Desc 损失函数为logloss
        '''
        return np.sum(np.nan_to_num(-y * np.log(y_hat) - (1 - y) * np.log(1 - y_hat)))

    @staticmethod
    def grad(y, y_hat, x):
        '''
        Desc 梯度
        '''
        return (y_hat - y) * x


class FTRL(object):
    def __init__(self, dim, l1, l2, alpha, beta, decisionFunc=LR):
        self.dim = dim
        self.decisionFunc = decisionFunc
        self.z = np.zeros(dim)
        self.n = np.zeros(dim)
        self.w = np.zeros(dim)
        self.l1 = l1
        self.l2 = l2
        self.alpha = alpha
        self.beta = beta

    def predict(self, x):
        return self.decisionFunc.fn(self.w, x)

    def update(self, x, y):
        '''
        Desc update paramers but not filter with x[i] == 0
        '''
        self.w = np.array([0 if np.abs(self.z[i]) <= self.l1 else
            (np.sign(self.z[i]) * self.l1 - self.z[i]) / (self.l2 + (self.beta + np.sqrt(self.n[i]))/ self.alpha) for i in xrange(self.dim)])
        y_hat = self.predict(x)
        g = self.decisionFunc.grad(y, y_hat, x)
        sigma = (np.sqrt(self.n + g * g) - np.sqrt(self.n)) / self.alpha
        self.z += g - sigma * self.w
        self.n += g * g
        return self.decisionFunc.loss(y, y_hat)

    def train(self, trainSet, verbos=False, max_itr=100000000, eta=0.001, epochs=100):
        itr = 0
        n = 0
        while True:
            for x, y in trainSet:
                loss = self.update(x, y)
                if verbos:
                    print 'itr=' + str(n) + '\tloss=' + str(loss)
                if loss < eta:
                    itr += 1
                else:
                    itr = 0
                if itr >= epochs:
                    print 'loss have less than', eta, ' continuously for ', itr, 'iterations'
                    return
                n += 1
                if n >= max_itr:
                    print 'reach max iteration ', max_itr
                    return

class Corpus(object):
    def __init__(self, file, d):
        self.d  = d
        self.file = file
    def __iter__(self):
        with open(self.file, 'r') as fr:
            for line in fr:
                arr = line.strip().split()
                if len(arr) >= self.d + 1:
                    yield (np.array([float(x) for x in arr[0:self.d]]), float(arr[self.d]))

if __name__ == '__main__':
    d = 4
    corpus = Corpus('../../../data/ftrl_train.txt', d=d)
    ftrl = FTRL(dim=d, l1=1.0, l2=1.0, alpha=0.1, beta=1.0)
    ftrl.train(corpus, verbos=False, max_itr=100000, eta=0.01, epochs=100)
    w = ftrl.w
    print w

    correct = 0
    wrong = 0
    for x, y in corpus:
        y_hat = 1.0 if ftrl.predict(x) > 0.5 else 0.0
        if y == y_hat:
            correct += 1
        else:
            wrong += 1
    print 'correct ratio:', 1.0 * correct / (correct + wrong)
