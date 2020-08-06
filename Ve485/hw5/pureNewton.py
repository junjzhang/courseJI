import matplotlib.pyplot as plt
from matplotlib.pyplot import MultipleLocator
import math


def update(x, firstGradient, secondGradient):
    decentDir = -secondGradient**(-1)*firstGradient
    newtonDecrement = -firstGradient*decentDir
    return x+decentDir, newtonDecrement


def q1Fun(x):
    e = math.e
    f = math.log(e**x+e ** (-x))
    firstGradient = (e**(x)-e**(-x))/(e**x+e ** (-x))
    secondGradient = 4/(e**x+e ** (-x))
    return f, firstGradient, secondGradient


def q1Domain(x):
    return True


def q2Fun(x):
    f = -math.log(x)+x
    firstGradient = -1/x+1
    secondGradient = 1/(x**2)
    return f, firstGradient, secondGradient


def q2Domain(x):
    return x >= 0


def plot(fun, flag):
    xSeq = []
    fSeq = []
    fPriSeq = []
    if flag:
        for x in range(-150, 150):
            xSeq.append(x*0.04)
            f, fPri = fun(x*0.04)[0:2]
            fSeq.append(f)
            fPriSeq.append(fPri)
    else:
        for x in range(1, 300):
            xSeq.append(x*0.04)
            f, fPri = fun(x*0.04)[0:2]
            fSeq.append(f)
            fPriSeq.append(fPri)
    plt.figure(figsize=(12, 8))
    plt.plot(xSeq, fSeq, color="indianred", label=r"$f(x)$")
    plt.plot(xSeq, fPriSeq, color="lightslategrey", label=r"$f'(x)$")
    plt.xlabel(r"$x$", fontsize=12)
    plt.legend(fontsize=12)
    plt.show()


def info(x, k, inDomain, f, optimalF):
    print("***iteration %d***" % k)
    if inDomain:
        print("x_%d is %f" % (k, x))
        print("f(x_%d) - f(x*) = %f" % (k, f - optimalF))
    else:
        print("x_%d is out of the domain" % k)


def newtonDecent(x, fun, domain, optimalF, stopStep=100):
    iter = 0
    fSeq = []
    fPriSeq = []
    newtonDecrement = 1
    inDomain = True
    while (newtonDecrement > 1e-6 and iter < stopStep and inDomain):
        f, firstGradient, secondGradient = fun(x)
        info(x, iter, inDomain, f, optimalF)
        fSeq.append(f)
        fPriSeq.append(firstGradient)
        x, newtonDecrement = update(x, firstGradient, secondGradient)
        inDomain = domain(x)
        iter += 1
    if (inDomain):
        f, firstGradient, secondGradient = fun(x)
        info(x, iter, inDomain, f, optimalF)
        fSeq.append(f)
        fPriSeq.append(firstGradient)
    else:
        info(x, iter, inDomain, f, optimalF)


if __name__ == '__main__':
    # Q1
    plot(q1Fun, q1Domain(-1))
    # Q1 when x_0 = 1
    q1OptimalF = q1Fun(0)[0]
    newtonDecent(1.0, q1Fun, q1Domain, q1OptimalF)
    # Q1 when x_0 = 1.1
    q1OptimalF = q1Fun(0)[0]
    newtonDecent(1.1, q1Fun, q1Domain, q1OptimalF)
    # Q2 when x_0 = 3
    plot(q2Fun, q2Domain(-1))
    q2OptimalF = q2Fun(1)[0]
    newtonDecent(3, q2Fun, q2Domain, q2OptimalF)
