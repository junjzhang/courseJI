'''
* This file is to generate different kind of data
** author: Junjie Zhang
'''
import numpy as np

# * funtion to genereate data with swiss roll shape
# ** parameter:
# *** beginCir: begin of the circle
# *** endCir: end of the circle
# *** numPoints: num of the data points
# *** a,b, parameters to adjust the radius
# *** noise: the weight on noise


def swissRoll(beginCir, endCir, numPoints, a=1.0, b=1.0, noise=0.0):
    theta = np.random.uniform(
        low=2 * beginCir*np.pi, high=2*endCir*np.pi, size=(1, numPoints))
    radius = a+b*theta
    xs = radius * np.cos(theta)
    ys = radius * np.sin(theta)
    zs = np.random.uniform(low=0, high=5, size=(1, numPoints))
    X = np.concatenate((ys, zs, xs))
    X += noise * np.random.randn(3, numPoints)
    X = X.T
    return X, np.squeeze(theta)

# * genereate data with S shape
# ** parameter:
# *** beginCir: begin of the circle
# *** endCir: end of the circle
# *** numPoints: num of the data points
# *** noise: the weight on noise


def sShape(beginCir, endCir, numPoints, noise=0.0):
    theta = np.random.uniform(
        low=2 * beginCir*np.pi, high=2*endCir*np.pi, size=(1, numPoints))
    xs = np.sin(theta)*theta**0.7
    ys = theta
    zs = np.random.uniform(low=0, high=10, size=(1, numPoints))
    X = np.concatenate((xs, zs, ys))
    X += noise * np.random.randn(3, numPoints)
    X = X.T
    return X, np.squeeze(theta)

# * genereate data with ball shape
# ** parameter:
# *** beginCir: begin of the ball
# *** endCir: end of the ball
# *** numPoints: num of the data points
# *** noise: the weight on noise


def ball(begin, end, numPoints, noise=0.0):
    R = 1
    theta = np.random.uniform(
        low=begin*np.pi, high=end*np.pi, size=(numPoints,))
    fai = np.arange(0, 2, 2/numPoints)*np.pi
    xs = np.array([R*(np.sin(theta)*np.cos(fai))])
    ys = np.array([R*(np.sin(theta)*np.sin(fai))])
    zs = np.array([R*np.cos(theta)])
    X = np.concatenate((xs, ys, zs))
    X += noise * np.random.randn(3, numPoints)
    X = X.T
    return X, theta
