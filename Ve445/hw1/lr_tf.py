#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Oct  3 23:09:22 2019

@author: zhangjunjie
"""

import tensorflow as tf
import numpy as np
# Import MNIST data(下载数据)

def load_data():
    temp = np.loadtxt("Assign1_Q2.csv",skiprows=1,delimiter=",")
    train_index = np.random.choice(temp.shape[0],round(temp.shape[0]*0.7),replace = False)
    temp_train = temp[train_index]
    test_index = np.array(list(set(range(temp.shape[0]))-set(train_index)))
    temp_test = temp[test_index]
    data_test = temp_test[:,0:8]
    label_test = temp_test[:,8].reshape(data_test.shape[0],1)
    data_train = temp_train[:,0:8]
    label_train = temp_train[:,8].reshape(data_train.shape[0],1)
    return data_train,label_train,data_test,label_test

# 参数：学习率，训练次数，
learning_rate = 0.01
training_epochs = 10000
display_step = 1

# tf Graph Input
x = tf.placeholder(tf.float32, [None, 8]) # mnist data image of shape 28*28=784
y = tf.placeholder(tf.float32, [None, 1]) # 0-9 digits recognition => 10 classes

# Set model weights
W = tf.Variable(tf.zeros([8, 1]))
b = tf.Variable(tf.zeros([1]))

# softmax模型
pred = tf.nn.sigmoid(tf.matmul(x, W) + b) 

# Minimize error using cross entropy（损失函数用cross entropy）
cost = tf.reduce_mean(-tf.reduce_sum(y*tf.log(pred)+(1-y)*tf.log(1-pred), reduction_indices=1))
# Gradient Descent（梯度下降优化）
optimizer = tf.train.GradientDescentOptimizer(learning_rate).minimize(cost)

# Initializing the variables
init = tf.global_variables_initializer()

# Launch the graph
with tf.Session() as sess:
    sess.run(init)
    x_train,y_train,x_test,y_test = load_data()
    # Training cycle
    for epoch in range(training_epochs):
        _, c = sess.run([optimizer, cost], feed_dict={x: x_train,y: y_train})

    print("Optimization Finished!")

    # Test model
    correct_prediction = tf.equal(tf.cast(tf.greater(pred,0.5),tf.float32), y)
    # Calculate accuracy
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
    print("Accuracy:", accuracy.eval({x: x_test, y: y_test}))