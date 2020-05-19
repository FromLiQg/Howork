import numpy as np
import matplotlib.pyplot as plt

#中文不会乱码
from pylab import *
mpl.rcParams['font.sans-serif']=['SimHei']
#打开相关文件
file = open('out.xls')
#转换成numpy矩阵
a =file.read()
b =a.split('\n') 
for i in range(len(b)):
	b[i] = b[i].split()#使用空格分开
b = np.array(b)#转成numpy形的


size = len(b[0])
#年级
Grade = []
#班级
Class = []
#科目
Subject = []
#不及格
Fail = []
#80分+
High = []
#平均分
Average = []
#遍历，准备好数据
for i in range( len(b)-1 ):
	Grade.append(b[i][0])
	Class.append(b[i][1])
	Subject.append(b[i][2])
	Fail.append(b[i][3])
	High.append(b[i][4])
	Average.append(b[i][5])

total_width, n = 0.8, 3
width = total_width / n
#下面以每个班为单位输出柱状图
#不及格数据临时存储
h = []
#科目名称临时存储
x = []
#80分+临时存储
k = []
#平均分临时存储
l = []

#标记是否换班级了
tmp = Grade[0]
tmpClass = Class[0]

#遍历数据
for i in range(len(b)):
	if Grade[i]==tmp and Class[i]==tmpClass:
		h.append(Fail[i])
		x.append(Subject[i])
		k.append(High[i])
		l.append(Average[i])
	#换班，准备输出图
	if Grade[i]!=tmp or Class[i]!=tmpClass:
		h = list(map(int,h))
		k = list(map(int,k))
		l = list(map(float,l))
		#设置间距
		y = np.arange(len(h))
		y = y -(total_width - width) / 2
        #画图
		plt.barh(y,np.array(h),tick_label=x ,height = width,label='不及格')
		plt.barh(y +2* width,np.array(k),tick_label=x,height = width, label='80分+')
		plt.title(tmp+tmpClass + '班')
		plt.legend()
		#存图
		plt.savefig( tmp+tmpClass + '班.png',dpi=500,bbox_inches = 'tight')
		#清空内存中的图
		plt.clf()
		
		plt.barh(y +  width, np.array(l),tick_label=x,height = width,label=" ")
		plt.title(tmp+tmpClass + '班的平均分')
		plt.legend()
		#存图
		plt.savefig( tmp+tmpClass + '班平均分.png',dpi=500,bbox_inches = 'tight')
		plt.clf()
		
		#更新标记数据和临时数据
		tmp = Grade[i]
		tmpClass = Class[i]
		h = []
		k = []
		l = []
		x = []
		if i!=len(b):
		    h.append(Fail[i])
		    x.append(Subject[i])
		    k.append(High[i])
		    l.append(Average[i])