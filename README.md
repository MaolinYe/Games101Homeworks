# Games101Homeworks
Games101‘s Homeworks
## Assignment0 配置环境
安装eigen即可
## Assignment1 填写一个旋转矩阵和一个透视投影矩阵
### 配置环境
#### 下载MinGW
https://github.com/Vuniverse0/mingwInstaller/releases  
添加环境变量到path：C:\Users\Yezi\mingw64\bin
#### 下载cmake
https://cmake.org/download/
#### 下载opencv
https://opencv.org/releases/
#### 编译opencv
https://blog.csdn.net/Dylan_YQ/article/details/122677627
```
mingw32-make -j 16
mingw32-make install
```
### 一个旋转矩阵
get_model_matrix(float rotation_angle): 逐个元素地构建模型变换矩
阵并返回该矩阵。在此函数中，你只需要实现三维中绕 z 轴旋转的变换矩阵，
而不用处理平移与缩放。
#### 思路
直接写一个绕Z轴旋转的矩阵返回即可
### 一个透视投影矩阵
get_projection_matrix(float eye_fov, float aspect_ratio, float
zNear, float zFar): 使用给定的参数逐个元素地构建透视投影矩阵并返回
该矩阵。
#### 思路
先做透视投影，然后做正交投影，正交投影=平移+缩放  
平移到原点，缩放到一个标准正方体[-1,1]³中  
n 对应 zNear，f 对应 zFar，fovY 对应 eye_fov，aspect 对应 asoect_ratio  
![img.png](Assignment1/代码框架/img.png)
## Assignment2 光栅化三角形
### 判断点是否在三角形内
static bool insideTriangle(): 测试点是否在三角形内。
#### 思路
叉乘可以用来判断一个点是否在一个多边形内部，如P点，如果AP×AB和BP×BC和CP×CA的方向是一样的，那么这个P点就在三角形内部
### 光栅化三角形
rasterize_triangle()
#### 思路
先建立起一个矩形框框住三角形  
遍历矩形框内每个像素，判断该像素是否在三角形内  
如果在三角形内，插值计算深度，更新depth buffer  
渲染该像素
![img.png](Assignment2/代码框架/img.png)
三角形颠倒问题  
https://zhuanlan.zhihu.com/p/509902950
## Assignment3 加载三维模型+纹理映射
### 任务
1. 修改函数 rasterize_triangle(const Triangle& t) in rasterizer.cpp: 在此处实现与作业 2 类似的插值算法，实现法向量、颜色、纹理颜色的插值。
2. 修改函数 get_projection_matrix() in main.cpp: 将你自己在之前的实验中实现的投影矩阵填到此处，此时你可以运行./Rasterizer output.png normal 来观察法向量实现结果。
3. 修改函数 phong_fragment_shader() in main.cpp: 实现 Blinn-Phong 模型计算Fragment Color.
4. 修改函数 texture_fragment_shader() in main.cpp: 在实现 Blinn-Phong 的基础上，将纹理颜色视为公式中的 kd，实现 Texture Shading Fragment
   Shader.
5. 修改函数 bump_fragment_shader() in main.cpp: 在实现 Blinn-Phong 的基础上，仔细阅读该函数中的注释，实现 Bump mapping.
6. 修改函数 displacement_fragment_shader() in main.cpp: 在实现 Bump mapping 的基础上，实现 displacement mapping.
### 解决
#### 1. 修改函数 rasterize_triangle(const Triangle& t) in rasterizer.cpp: 在此处实现与作业 2 类似的插值算法，实现法向量、颜色、纹理颜色的插值。  
先把作业2的拉过来，增加对法向量、颜色、纹理颜色与底纹颜色 (Shading Colors) 的插值
对于牛牛倒过来的和之前一样，是因为课程推导中的n和f是坐标，相机是看向-z方向的，这里n和f是距离，感觉像是相机看向z方向的，用了一个对称矩阵将x和y方向镜像就对了
![img.png](Desktop/Games101Homeworks/Assignment3/Code/img.png)
#### 2. 修改函数 get_projection_matrix() in main.cpp: 将你自己在之前的实验中实现的投影矩阵填到此处，此时你可以运行./Rasterizer output.png normal 来观察法向量实现结果。  

#### 3. 修改函数 phong_fragment_shader() in main.cpp: 实现 Blinn-Phong 模型计算Fragment Color.  

#### 4. 修改函数 texture_fragment_shader() in main.cpp: 在实现 Blinn-Phong 的基础上，将纹理颜色视为公式中的 kd，实现 Texture Shading Fragment Shader.  

#### 5. 修改函数 bump_fragment_shader() in main.cpp: 在实现 Blinn-Phong 的基础上，仔细阅读该函数中的注释，实现 Bump mapping.  

#### 6. 修改函数 displacement_fragment_shader() in main.cpp: 在实现 Bump mapping 的基础上，实现 displacement mapping.  
