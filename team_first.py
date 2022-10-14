import numpy  as np1
import matplotlib
import matplotlib.pyplot as plt1

data = np1.loadtxt('matrix.txt')
group = np1.genfromtxt('typeOfCluster.txt',dtype='str')
cluster = np1.loadtxt('Buff.txt')

color_indices = []

yy = data[:, 0]
xx = data[:, 1]   

yy1 = cluster[:, 0]
xx1 = cluster[:, 1]   

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

plt1.scatter(xx,yy,c=color_indices, marker = '*', cmap=matplotlib.colors.ListedColormap(colors))
plt1.scatter(xx1,yy1, marker = '.')
plt1.title('900 examples')
plt1.savefig('team_start.png')
