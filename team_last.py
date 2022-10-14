import numpy  as np
import matplotlib
import matplotlib.pyplot as plt

data = np.loadtxt('Newmatrix.txt')
group = np.genfromtxt('NewtypeOfCluster.txt',dtype='str')
cluster = np.loadtxt('NewBuff.txt')

color_indices = []

y = data[:, 0]
x = data[:, 1]   

y1 = cluster[:, 0]
x1 = cluster[:, 1]   

for i in group:
    if  i =='0':
        color_indices.append(0)
    elif i =='1':
        color_indices.append(1)
    elif i =='2':
        color_indices.append(2)
    elif i =='3':
        color_indices.append(3)
    elif i =='4':
        color_indices.append(4)
    elif i =='5':
        color_indices.append(5)
    elif i =='6':
        color_indices.append(6)
    elif i =='7':
        color_indices.append(7)
    elif i =='8':
        color_indices.append(8)
    elif i =='9':
        color_indices.append(9)

colors = ["red","blue","green","black","pink","yellow","purple","orange","brown","gray"]

plt.scatter(x,y,c=color_indices, marker = '*', cmap=matplotlib.colors.ListedColormap(colors))
plt.scatter(x1,y1, marker = '.')
plt.title('900 examples')
plt.savefig('team_final.png')

