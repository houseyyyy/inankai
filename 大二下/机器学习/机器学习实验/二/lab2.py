#助教您好，在测试时ex1data2.txt时，需要修改第七行，并且把37行去掉注释
#同时注释掉65 - 120行
#测试预测在53-63行

import numpy as np
import matplotlib.pyplot as plt
data = np.loadtxt('./ex1data1.txt', delimiter=',')
m = data.shape[0]
n = data.shape[1]
sita = np.zeros(n)
cost_history = []
x = data[:,0:-1]
x0 = np.ones((m,1))
x = np.hstack((x0,x))

y = data[:,-1]

def gradi(sita,x,y,j):
	res = 0.0
	for i in range(0,m):
		res = res + (( (sita @ x[i]) - y[i] ) * x[i][j]) / m
	return res
def meanNormalization(x):
	#axis = 0,列 axis = 1行，返回列表
	#这里注意不要归一话x0,会导致方差是0,divide 0
	ave = x[:,1:].mean(axis = 0)
	#分列求标准差,方差是var
	va = np.std(x[:,1:],axis = 0,ddof = 1)
	x[:,1:] = (x[:,1:] - ave) / va
	return ave,va;
	#N(0,1)
def computeCost(x,y,sita):
	res = 0.0
	for i in range(0,m):
		res = res + ((sita @ x[i]) - y[i]) ** 2 / 2  / m
	return res
#mu,sima = meanNormalization(x)
count = 1500
alpha = 0.01
while count != 0:
	count = count - 1
	for j in range(0,n):
		gra = gradi(sita,x,y,j)
		sita[j] = sita[j] - alpha * gra
	current_cost = computeCost(x, y, sita)
	cost_history.append(current_cost)

#normal equation
sitaEqu = np.linalg.inv(x.T @ x) @ x.T @ y
print("ex1data:\ngradient descent result",sita)
print("normal equation result",sitaEqu)

#测试1
#注意补x_0
# test1 = np.array([ [1.0,5.0],[1.0,25.0] ])
# print("ex1data1:\ngradient descent prediction:",test1 @ sita)
# print("normal equation prediction:",test1 @ sitaEqu)

#测试2
# test2 = np.array([1.0,1650.0,3.0])
# test2[1:] = (test2[1:] - mu) / sima
# print("ex1data2:\ngradient descent prediction:",test2 @ sita)
# print("normal equation prediction:",test2 @ sitaEqu)

#画样本分步

print("the initial cost function value = ",computeCost(x,y,sita))
plt.xlabel('Population of City in 10000s')
plt.ylabel('Profit in $10000s')
plt.plot(x[:,1:], y, 'xr')
plt.show()

#画预测结果

plt.xlabel('Population of City in 10000s')
plt.ylabel('Profit in $10000s')
x0 = 5.0
y0 = sita[0] + x0*sita[1]
x1 = 25.0
y1 = sita[0] + x1*sita[1]
plt.plot((x0, x1), (y0, y1))
plt.plot(data[:,0], y, "ob")
plt.show()

#画代价函数

w0_vals = np.linspace(-100, 100, 100)
w1_vals = np.linspace(-5, 10, 100)
cost_vals = np.zeros((len(w0_vals), len(w1_vals)))
for i in range(len(w0_vals)):
    for j in range(len(w1_vals)):
    	#这里基本都是cv的,只需要改一下X和 第三个参数
        cost_vals[i, j] = computeCost(x, y, np.array([w0_vals[i],w1_vals[j]]))
cost_vals = cost_vals.T
w0_vals_m, w1_vals_m = np.meshgrid(w0_vals, w1_vals)
fig = plt.figure()
ax = plt.axes(projection = '3d')
ax.plot_surface(w0_vals_m, w1_vals_m, cost_vals, cmap='rainbow')
ax.set_xlabel('w_0')
ax.set_ylabel('w_1')
ax.set_zlabel('cost')
plt.show()

#画等高线

theta0_val = np.linspace(-10, 10, 100)
theta1_val = np.linspace(-1, 4, 100)
cost_val = np.zeros((len(theta0_val), len(theta1_val)))
for i in range(len(theta0_val)):
    for j in range(len(theta1_val)):
    	#这里同样需要改第三个参数
        theta_val = np.array([theta0_val[i], theta1_val[j]])
        cost_val[i, j] = computeCost(x, y, theta_val)
cost_val = cost_val.T
plt.contour(theta0_val, theta1_val, cost_val, np.logspace(-2, 3, 20))
plt.xlabel('theta_0')
plt.ylabel('theta_1')
#这里theta_mat就是我的sitaEqu
plt.plot(sitaEqu[0], sitaEqu[1], 'rx')
plt.show()

#画J和迭代次数
plt.figure()
plt.plot(range(len(cost_history)), cost_history, 'b-')
plt.xlabel('Iterations')
plt.ylabel('Cost')
plt.title('Cost Function vs. Iterations')
plt.show()