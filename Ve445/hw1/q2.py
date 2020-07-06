# -*- coding: utf-8 -*-
import numpy as np
from sklearn import metrics
import matplotlib.pyplot as plt

def load_data():
    temp = np.loadtxt("Assign1_Q2.csv",skiprows=1,delimiter=",")
    temp = np.hstack((np.ones((temp.shape[0],1)),temp))
    train_index = np.random.choice(temp.shape[0],round(temp.shape[0]*0.7),replace = False)
    temp_train = temp[train_index]
    test_index = np.array(list(set(range(temp.shape[0]))-set(train_index)))
    temp_test = temp[test_index]
    data_test = temp_test[:,0:9]
    label_test = temp_test[:,9].reshape(data_test.shape[0],1)
    data_train = temp_train[:,0:9]
    label_train = temp_train[:,9].reshape(data_train.shape[0],1)
    return data_train,label_train,data_test,label_test

def sigmoid(x):
    return 1/(1+np.exp(-x))

def loss_gradient(x,y,theta):
    l1_term = 0.003/x.shape[0]*(theta>0).astype(np.float64)
    gradient = 1/x.shape[0]*x.T@(sigmoid(x@theta)-y)-l1_term
    return gradient
    
def predict(x,theta):
    temp = sigmoid(x@theta)>0.5
    return temp.astype(np.float64)

def plot(x,y):
    plt.figure(figsize=(16,10))
    plt.plot(x,y)
    plt.xlabel("learning rate")
    plt.ylabel("accuracy")
    plt.show()
    return

if __name__ == "__main__":
    X_train,Y_train,X_test,Y_test = load_data()
    theta = np.random.rand(X_train.shape[1],1)
    lr_array1 = 0.0001*1.2**np.array(range(0,38))
    lr_array2 = lr_array1[37]+0.01*np.array(range(1,40))
    lr_array = np.hstack((lr_array1,lr_array2)).reshape(1,77)
    accuracy_array = np.zeros((1,77))
    for jj in range(0,77):
        lr = lr_array[0,jj]
        for ii in range(0,100000):
            gradient = loss_gradient(X_train,Y_train,theta)
            theta = theta-lr*gradient
        prediction = predict(X_test,theta)
        accuracy_array[0,jj] = metrics.accuracy_score(prediction,Y_test)
    plot(lr_array[0,:],accuracy_array[0,:])
    