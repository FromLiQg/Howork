# 文件说明
analysis.cpp 是分析主程序
in.txt 是分析数据
out.xls 是分析结果
outputIMG.py 是将分析结果可视化的文件
tmp.exe 是win10系统下可用的该分析程序的二进制文件
其他文件是tmp.exe辅助文件

# 使用说明
g++ analysis.cpp -o tmp 

执行上述命令后可得到可执行文件tmp
执行tmp
输入第几学段，即可获得第几学段的可视化分析结果

# 注意事项
python请先安装以下库
numpy
matplotlib
