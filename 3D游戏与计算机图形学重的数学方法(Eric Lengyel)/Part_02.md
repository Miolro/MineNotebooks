# 第二章 向量

向量是所有 3D 游戏引擎的`重要基础`，被用来表示`空间中的点`，如游戏中的`物体位置`或者`三角网格的顶点`，向量还可以表示`空间中的方向`(挖坑第四章中介绍)

## 2.1 向量的性质

尽管向量有更抽象的定义，书中用实数 n 元组来表示向量，其中 n 一般表示为 2，3，4。。。 一个 n 维向量可以表示为

$$
V = <V_1,V_2,\cdots,V_n>
$$

$$其中V_i表示向量V的分量，i为V的下标$$
向量 V 也可以表示仅有一列的 n 行矩阵

$$
V=
\begin {bmatrix}
V_1\\
V_2\\
{\vdots}\\
V_n\\
\end {bmatrix}
$$

向量转置

$$ V^t = \begin{bmatrix} V_1,V_2,{\cdots},V_n\end{bmatrix} $$

向量乘法（允许降向量乘以一个标量变成一个新的向量）

$$aV = Va = \begin{bmatrix} aV_1,aV_2,{\cdots},aV_n \end{bmatrix} $$

当 a=-1 时简化符号-V 表示向量 V 的反向量

$$P+Q =\begin{bmatrix}P_1+Q_1,P_2,Q_2,{\cdots},P_n+Q_n\end{bmatrix}$$

向量乘法和加法适配交换律和结合律

向量的绝对值

$$|V|=\sqrt{\sum_{i=1}^{n}V_i^2}$$ 

类似取绝对值

$|X| = \sqrt{a^2} 自成负负得正后开方$


## 2.2 内积

两个向量的内积也被称为向量的点积或者标量积（可以计算两个向量的方向差）

内积公式

$$P*Q = \sum_{i=1}^nP_iQ_i$$

意为把每个向量分量依次相乘三维可以表示

$$P*Q=\begin{bmatrix}P_1Q_1+P_2Q_2+{\cdots},P_nQ_n\end{bmatrix}$$
$$P*Q=\begin{bmatrix}P_xQ_x+P_yQ_y+,P_zQ_z\end{bmatrix}$$

也可以写做矩阵

$$P^T*Q=\begin{bmatrix}P_xP_y,P_z\end{bmatrix}\begin{bmatrix}Q_x\\Q_y\\Q_z\end{bmatrix}$$

以下是内积常用的公式（求向量角度）

$$P*Q=||P||*||Q||{cos\theta}$$

知道$cos{\theta}就可以知道两个向量的夹角$
$$用余弦定理打开(Q+P)^2 = Q^2+P^2-2abCos{\theta}$$
$$||P-Q||^2 = |P|^2 - 2|P||Q|cos{\theta} + |Q|^2$$
$$(P-Q)^2 = {\sum_{i=0}^{n}}P^2+{\sum_{i=0}^{n}}Q^2-2|P||Q|cos{\theta}$$
$$({\sum_{i=0}^{n}}P-{\sum_{i=0}^{n}}Q)({\sum_{i=0}^{n}}P-{\sum_{i=0}^{n}}Q) = {\sum_{i=0}^{n}}P^2+{\sum_{i=0}^{n}}Q^2-2|P||Q|cos{\theta}$$
$${\sum_{i=0}^{n}}P^2+{\sum_{i=0}^{n}}Q^2-2({\sum_{i=0}^{n}}P^2+{\sum_{i=0}^{n}}Q^2)={\sum_{i=0}^{n}}P^2+{\sum_{i=0}^{n}}Q^2-2|P||Q|cos{\theta}$$
$$-2({\sum_{i=0}^{n}}P^2+{\sum_{i=0}^{n}}Q^2)=-2|P||Q|cos{\theta}$$
$${\sum_{i=0}^{n}}P^2+{\sum_{i=0}^{n}}Q^2=|P||Q|cos{\theta}$$
$$变式：cos{\theta} ={\frac{P*Q}{|P||Q|}} $$
$$变式：(x-y)^2 = x^2 - 2xy + y^2$$
当$P*Q=0时垂直因为90°时候cos{\theta}为0$

关于内积正负特性

$P*Q>0时同向$
$P*Q<0时异向$