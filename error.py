import numpy  as np
import matplotlib
import matplotlib.pyplot as plt
data = np.loadtxt('iter_distance.txt')

color_indices = []

x = data[:, 0]
y = data[:, 1]   

colors = ["red","blue","green","black","pink","yellow"]

plt.plot(x,y,linestyle='solid',label="error")
plt.legend(loc="upper right")
plt.title('900 examples error Value')
plt.xlabel('iterations')
plt.ylabel('Error_Value')
plt.savefig('set_error.png')
