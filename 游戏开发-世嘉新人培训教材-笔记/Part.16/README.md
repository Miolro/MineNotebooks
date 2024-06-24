# 第 16 章 伪 XML 解析

```XML
<VertexBuffer name="vb">
	<Vertex position="-10, -10, 0" uv="0, 0"></Vertex>
	<Vertex position="-10, 10, 0" uv="0, 1"></Vertex>
	<Vertex position="10, -10, 0" uv="1, 0"></Vertex>
	<Vertex position="10, 10, 0" uv="1, 1"></Vertex>
</VertexBuffer>
<IndexBuffer name="ib">
	<Triangle indices="0, 1, 2"></Triangle>
	<Triangle indices="3, 1, 2"></Triangle>
</IndexBuffer>
<Texture name="texture" filename="grid.tga"></Texture>
<Batch
	name="batch"
	vertexBuffer="vb"
	indexBuffer="ib"
	texture="texture"
	blend="opaque">
</Batch>
```

```XML
主要结构:
<节点 属性="属性值">
    <子节点 属性="属性值">

    </子节点>
</节点>
```

代码解析

- 第一步读文件前面写的 File 能直接用
- 第二步确定循环范围
  - 思路获取到字节开始的地址然后加上字节长度可以得到开始和结束的范围
  
  ```C++
    const char* begin = file.getData();
    const char* end = file.getData() + file.getSize();
  ```

  - 循环结构
  
  ```C++
    while(begin<end){begin++;}
  ```
  
- 第三步解析开始 (递归起点)
  - 从结构上入手我们有节点和子节点所以我们Element构造时候需要传入父节点
  
    ```C++
        new Element(父节点,开始的指针,结束的指针)
    ```
  - XML只有一个根节点在根节点上分支出子节点
  - 这边需要有一个节点作为开头根节点起头启动递归
  
    ```C++
        Tag tag("<ROOT>");
    ```

- 第四步启动 设置好节点信息
  - 开始以begin和end指针作为循环范围
  - Element的循环主要是寻找标签开头位置
  
    ```C++
        if (**begin == '<')
    ```
  - 找到位置之后解析标签
- TAG(临时变量解析用)
  - 内部属性:标签开头还是结束(主要作用是否应该在这个节点下面创建子节点如果节点解析结束`TAG_END`那么跳出这个递归创建一个节点)
    ```C++
    enum TagType
	{
		TAG_BEGIN,
		TAG_END
	};
    TagType mType;
    ```
  - 节点名称
  - 属性名称
- TAG的解析过程
  - 找到标签开头(解析到后面碰到了空格那么转为属性读取)
  - 获取标签头名称
  - 获取属性名称
  - 获取属性值
  - 循环上面两个属性值和属性名称获取
  - 结束头的分析
  - 返回到外层Element获取下一个节点开头
  - 如果节点开头是/那么跳出递归创建一个Element添加到这个子节点里
  - 如果开头不是/那么循环上面的第一步(找到开头)

**\*详细看代码流程注释**

字符解析转储为其他类型



```C++
const int Element::getDoubleList(double* out, int size)const
{
	int retSize = 0;
	istringstream iss(mValue);
	for (int i = 0; i < size; i++)
	{
		iss >> out[i];
		if (iss.fail())
		{
			break;
		}
		retSize++;
		iss.ignore(mValue.size(), ',');
	}
	return retSize;
}
```