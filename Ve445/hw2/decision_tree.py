import numpy as np
import pandas as pd
from sklearn.tree import export_graphviz
from sklearn.tree import DecisionTreeClassifier
import pydot




dtr = pd.read_csv('train_d.csv')
dts = pd.read_csv('test_d.csv')
dtr[dtr == "H"] = 0
dtr[dtr == "R"] = 1
dtr[dtr == "J"] = 2
dtr[dtr == "E"] = 0
dtr[dtr == "C"] = 1
dtr[dtr == "-"] = 0
dtr[dtr == "+"] = 1
dts[dts == "H"] = 0
dts[dts == "R"] = 1
dts[dts == "J"] = 2
dts[dts == "E"] = 0
dts[dts == "C"] = 1
dts[dts == "-"] = 0
dts[dts == "+"] = 1

X_train = dtr[['TYPE','PRICE']].values.astype(np.float)  
y_train = dtr['CATEGORY'].values.astype(np.float) 
X_test = dts[['TYPE','PRICE']].values.astype(np.float)   #提取要分类的特征。一般可以通过最大熵原理进行特征选择
y_test = dts['CATEGORY'].values.astype(np.float)
sum

tree = DecisionTreeClassifier()
tree.fit(X_train,y_train)
print('Train score:{:.3f}'.format(tree.score(X_train,y_train)))
print('Test score:{:.3f}'.format(tree.score(X_test,y_test)))

export_graphviz(tree,out_file="tree.dot",class_names=['buy','not buy'],feature_names=['TYPE','PRICE'],impurity=False,filled=True)
###展示可视化图
(graph,) = pydot.graph_from_dot_file('tree.dot')
graph.write_png('good.png')