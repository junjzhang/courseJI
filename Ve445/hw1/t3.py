#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct 12 19:55:28 2019

@author: bz
"""

from sklearn import datasets,svm,metrics
import numpy as np
import sklearn.model_selection as ms
import time
#import seaborn as sns
#import matplotlib.pyplot as plt
from SVM import *


#def show_data():
#    iris = sns.load_dataset("iris")
#    sns.set(style="ticks",color_codes = True)
#    g = sns.pairplot(iris)
#    sns.pairplot(iris,hue = "species",palette = "bright")
#    plt.show()
#    return

#def plot_result(x,t,model):
#    plt.figure(figsize=(8,5))
#    plt.plot(x,y[0,])
#    x = np.array(range(5))+5
#    y = -model.b-model.w[0]/model.w[1]*x
#    plt.scatter(x_test[y_test==1,0],x_test[y_test==1,1])
#    plt.scatter(x_test[y_test==-1,0],x_test[y_test==-1,1])
#    plt.show()
    
#data_prepare
iris = datasets.load_iris()

x_train, x_test, y_train, y_test = ms.train_test_split(iris.data, iris.target, random_state = 1, train_size = 0.6)
X_train = np.array([[x[0],x[1]] for x in x_train])
X_test =  np.array([[x[0],x[1]] for x in x_test])
Y1_train = np.array([1 if y==0 else -1 for y in y_train])
Y1_test =  np.array([1 if y==0 else -1 for y in y_test])
#Y2_train = np.array([1 if y==1 else -1 for y in y_train])
#Y3_train = np.array([1 if y==2 else -1 for y in y_train])

#train

#s2 = KernelSVM(X_train,Y1_train)
##s2 = SVM(X_train,Y2_train)
##s3 = SVM(X_train,Y3_train)
#start2 = time.clock()
#s2.training(kernel = "Polynomial", parameter = 2)
#elapsed = (time.clock()-start2)
#print("Time:",elapsed)
#print(s2.testing(X_test,Y1_test))

s1 = KernelSVM(X_train,Y1_train)
#s2 = SVM(X_train,Y2_train)
#s3 = SVM(X_train,Y3_train)
start = time.clock()
s1.training(kernel = "Laplace", parameter = 0.5)
elapsed = (time.clock()-start)
print("Time:",elapsed)
print(s1.testing(X_test,Y1_test))

#model1 = svm.SVC(kernel='poly', degree = 2, coef0 = 0, tol = 0.00000000000001)
#start2 = time.clock()
#model1.fit(X_train,Y1_train)
#elapsed = (time.clock()-start2)
#pd = model1.predict(X_test)
#print("ac:",metrics.accuracy_score(pd,Y1_test))
#print("time:",elapsed)

#s2.training()
#s3.training()
#predict = np.zeros((X_test.shape[0],1))
#predict[s1.predict(X_test)==1] = 0
#predict[s2.predict(X_test)==1] = 1
#predict[s1.predict(X_test)==1] = 2
#ac = np.sum((predict == y_test.reshape(x_test.shape[0],1)).astype(float))/x_test.shape[0]
#print(ac)

#print(test_s.testing(x_test,y_test))