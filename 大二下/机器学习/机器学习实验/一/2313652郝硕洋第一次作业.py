import numpy
#date load
data = numpy.loadtxt('./house_price.txt', delimiter=',')

#slice

print(data.shape, data.ndim)
m = data.shape[0]
n = data.shape[1]
print(m, n)
X = data[:, 0:2] # q取[0，2）这个区间的列，不包括2.
print(X.shape)
Y = data[:, 2]
print(Y.shape)
print(Y)
y = data[:, [2]]
print(y.shape)

#output data

print("First 10 examples from the datase(', m ,'): ")
for i in range(10):
	print('x = (', X[i, 0], ',', X[i, 1], '); y = ', y[i, 0])

print(y)
index_2d = y < 200000
# print(index_2d.shape)
#这里假如不进行转换，当使用二维布尔数组 index_2d 时
#NumPy 会尝试用它的形状 (47, 1) 去匹配 X 的维度 (47, m) 导致冲突
index_1d = (y < 200000).ravel()
print(index_1d.shape)
cheapHouse = X[index_1d,:]
print(cheapHouse)

#creat array

a = numpy.empty(2)
a = numpy.zeros(5)
a = numpy.ones(10)
a = numpy.random.random(5)

#转置
a = numpy.array([1,2,3])
b = a.T
#当数组的维度小于2时 ndarray.T不会进行任何操作
print(b)
a = numpy.array([[1,2,3],
				[4,5,6]])
b = a.T
print(b)

a = numpy.array([ [[1,2],[3,4]],
				  [[5,6],[7,8]],
				  [[9,10],[11,12]]
				  ])
print(a.shape)
print(a)
b = a.transpose(1,0,2)
print(b.shape)
print(b)
print(a[1,0,0],b[0,1,0])
#默认顺序是0123··· transpose里的顺序代表新坐标轴顺序 比如原来5为(1,0,0)
#执行完之后变为(0,1,0) 本质是坐标轴的变换

#拼接
arr1 = numpy.array([1, 2, 3])
arr2 = numpy.array([4, 5, 6])

# 垂直堆叠
av = numpy.vstack((arr1, arr2))
print(av)
ah = numpy.hstack((arr1, arr2))
print(ah)
#还有一个stack通用堆叠
#展开 为一维！！
a = numpy.array([ [[1,2],[3,4]],
				  [[5,6],[7,8]],
				  [[9,10],[11,12]]
				  ])
b = a.flatten()
print(b)
print(b.shape)

#最后一个可以写成-1
a = numpy.array([ [[1,2],[3,4]],
				  [[5,6],[7,8]],
				  [[9,10],[11,12]]
				  ])
b = a.reshape((2,6))
b = a.reshape((2,-1))
print(b)
a = numpy.array([1, 2, 3])
b = numpy.array([4, 5, 6])
#标量点积
result = numpy.dot(a, b)
print(result)
a = numpy.array([[1,2],
				[3,4]])
b = numpy.array([[1,0],
				[0,-1]])
#矩阵乘法
re = numpy.dot(a,b)
re = a @ b
print(re)
#求逆矩阵 linear algebra 线性代数模块
ans = numpy.linalg.inv(re)
#求行列式determinant 结果是numpy.float64
print(numpy.linalg.det(re),type(numpy.linalg.det(re)))
print(ans)