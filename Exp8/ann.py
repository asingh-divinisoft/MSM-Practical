import numpy as np
import matplotlib.pyplot as plt

def sig(x):
	return 1/(1 + np.exp(-x))

def error(w1=0.2, w2=-0.5, v1=0.1, v2=0.4, v3=-0.2, v4=0.2, i1=0.4, i2=-0.7):
	ip = [i1, i2]
	targ = [0.1]

	v = [
		[v1, v2],
		[v3, v4]
		]
	w = [
		[w1, w2]
		]

	ip = np.array(ip)
	targ = np.array(targ)
	v = np.array(v)
	w = np.array(w)

	out = sig(w.dot(sig(v.T.dot(ip))))

	error = np.square((targ - out))/2
	return error

fig, ax = plt.subplots(figsize=(8, 6))

x = np.arange(-10, 10, 0.1)
y = []
for i in x: y.append(error(v1=i))
ax.plot(x, y)

y = []
for i in x: y.append(error(v1=i, i1=0.3, i2=-0.5))
ax.plot(x, y)


y = []
for i in x: y.append(error(v1=i, i1=0.6, i2=0.1))
ax.plot(x, y)

# y = []
# for i in x: y.append(error(w2=i))
# ax.plot(x, y)

# y = []
# for i in x: y.append(error(v1=i))
# ax.plot(x, y)

# y = []
# for i in x: y.append(error(v2=i))
# ax.plot(x, y)

# y = []
# for i in x: y.append(error(v3=i))
# ax.plot(x, y)

# y = []
# for i in x: y.append(error(v4=i))
# ax.plot(x, y)

plt.show()