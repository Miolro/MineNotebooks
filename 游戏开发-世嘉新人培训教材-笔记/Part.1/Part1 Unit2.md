<style>
   
    .tip{
        color:#ff9000
    }

    .understanding{
        color:#84C9EF      
    }
    .default{
        color:#88ACBC 
    }

</style>


<a id='第一章'></a>

# 第一章

<a id='1.1.3_主循环'></a>

## 1.1.3 主循环


<font class="tip">主要的内容：获取输入，反馈输入，显示结果</font>
<details>
<summary>主循环</summary>

```C++
    while(true){
        getInput();
        updateGame();
        draw();
    }
```
</details>

## 1.1.4 编写逻辑处理

<details>
<summary>编写逻辑处理</summary>
<font>问题1：绘制场景</font> 

\#######\#  
\#.. p $~~~~~~$\#  
\#oo $~~~~~~$\#   
\#$~~~~~~~~~~~$\#  
\#######\# 

</details>

## 1.2.1 包含头文件

## 1.2.2 场景数据常量

<details>
<summary>编写逻辑处理</summary>

```C++
    // "# 表示墙壁"
    // "空位表示空间"
    // "."表示目的地
    // "o"表示箱子
    // "p"表示玩家

    const char map[] = "########\n#.. p  #\n#oo    #\n#      #\n########";
    // 如果需要换行那么需要使用\(反斜杠)来换行
    // 下面是书中的示例
    const char [] = "\
    ########\n\
    #.. p  #\n\
    #oo    #\n\
    #      #\n\
    ########";

```

效果都是差不多的

注意const修饰的变量是不可被修改的

```C++
    const int value = 8；
    value = 1;
    //此时显示左值为可修改的值
```

<font class="tip">`const`可以防止不必要的错误操作</font>\
<font class="tip">当这个值在赋值后直到程序结束都不会去修改这个值时建议都加上这个`const`标记</font>
</details>

## 1.2.3 枚举类型

枚举类型:\
<font class="tip">`enum`表示枚举</font>\
<font class="tip">建议多用并且建议使用大写表示</font>
<details>
<summary>枚举类型</summary>

```C++
    enum Object
    {
        OBJ_SPACE,
        OBJ_WALL,
        OBJ_GOAL,
        OBJ_BLOCK,
        OBJ_BLOCK_ON_GOAL,
        OBJ_MAN,
        OBJ_MAN_ON_GOAL,

        OBJ_UNKONWN
    };

```

</details>

## 1.2.4 函数原型

<font class="tip">开发过程中尽量去像这样封装函数</font>
<details>
<summary>函数原型</summary>

```C++
    void initialize(Object* state, int w, int h, const char* stageData);
    void draw(const Object* state, int w, int h);
    void update(Object* state ,char input,int w,int h);
    bool checkClear(const Object* state, int w, int h);
```
</details>

## 1.2.5 main函数

<font class="tip">把枚举类型当作对象类名处理</font>\
<font class="tip">枚举实际上是用于列举的类型所以可以使用`new`生成</font>\
<font class="tip">也可以当作传入值和返回值</font>

<font class="tip">二维(多维?)数组无法通过`new`来创建</font>\
<font class="understanding">不管几维数组在内存中存储的形式都类似卡带都是一维只是改变索引方式来变更维度</font>\

<details>
<summary>创建一个空地图</summary>

```C++
	// 创建状态数组
	Object* state = new Object[stateMapWidth * stateMapHeight];
```
</details>

<font class="tip">虽然已经程序退出前不执行`delete`也没什么关系，但是这是一个很好的习惯，需要养成及时释放空间的习惯</font>\
<font class="tip">通过`new`创建的数组释放时必须使用`delete[]`</font>

<details>
<summary>内存释放</summary>

```C++
    // 内存释放
	delete[] state;
	state = 0;
```
</details>

## 1.2.6 初始化场景

<details>
<summary>初始化场景</summary>

```C++

    void initialize(Object* state, int w, int h, const char* stageData) {
        const char* stageDataCpy = stageData;
        int x = 0;
        int y = 0;

        while (*stageDataCpy != '\0')
        {
            Object instantiateObj;
            //= OBJ_UNKONWN; //初始化为未知数据
            switch (*stageDataCpy)
            {
            // 将地图的内存信息转为枚举对象
            case ' ':instantiateObj = OBJ_SPACE; break;
            case '#':instantiateObj = OBJ_WALL; break;
            case '.':instantiateObj = OBJ_GOAL; break;
            case 'o':instantiateObj = OBJ_BLOCK; break;
            case 'O':instantiateObj = OBJ_BLOCK_ON_GOAL; break;
            case 'p':instantiateObj = OBJ_MAN; break;
            case 'P':instantiateObj = OBJ_MAN_ON_GOAL; break;
            case '\n':instantiateObj = OBJ_UNKONWN; y++; x = 0; break;
            default:instantiateObj = OBJ_UNKONWN; break;
            }
            // 将除了位置对象的枚举对象信息写入到场景中
            if (instantiateObj != OBJ_UNKONWN) {
                state[x + (4 * y)] = instantiateObj;
                x++;
            }
            // 移动指针指向下一格地图内存的数据
            stageDataCpy++;
        }
    }

```
</details>

## 1.2.7 绘制



<font class="understanding">`绘制过程:下面是个人理解部分`</font>\
<font class="understanding">

首先作者绘制地图也就是代码中的`stageData[]`\
遍历地图`(stageData[])`字符映射枚举中的对象\
将映射对象`(OBJ_*)`保存到场景`(state[])`内存中\
然后将场景的内存绘制`draw()`出来\
然后玩家操作的是场景而不是去操作作者写的地图

在枚举中的对象相当于注册的实体\
每个实体都有他对应的id也就是`枚举的标号`

在draw中绘制图像实际可以理解为把物品id`(实体中注册的对象)`转为可视化的图像`(cout)`
</font>

<details>
<summary>绘制</summary>

```C++
    void draw(const Object* state, int w, int h) {
	// 场景对应的下标和字符表
	const char font[] = { ' ','#','.','o','O','p','P' };
	// 遍历场景
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			Object entity = state[x + (w * y)];
			cout << font[entity];
		}
		cout << '\n';
	}
}

```
</details>

## 1.2.8 更新

<details>
<summary>更新</summary>

<font class="tip">输入部分很好理解做一个输入分类来控制移动方式</font>

```C++

	int movX = 0;
	int movY = 0;
	switch (input)
	{
	case 'w':movY = -1;
	case 's':movY = 1;
	case 'a':movX = -1;
	case 'd':movX = 1;
	}

```

<font class="tip">获取玩家位置</font>

```C++

	/*寻找玩家的位置*/
	int plarX = 1;
	int plarY = 1;
	int findPlarFlag = 0;
	for (plarY; plarY < h - 1; plarY++)
	{
		for (plarX; plarX < w - 1; plarX++)
		{
			char stateEntity = state[plarX + (plarY * w - 1)];
			if (stateEntity == OBJ_MAN || stateEntity == OBJ_MAN_ON_GOAL) {
				findPlarFlag = 1;
				break;
			}
		}
		if (findPlarFlag) {
			break;
		}
		plarX = 1;
	}
	cout << "x:" << plarX << "y:" << plarY << endl;

```
<font class="understanding">优化  虽然效果相同 但是语句更短  嵌套更少  上面是我写的  下面是笔者写的</font>

```C++
	int pIndex = 0;
	for (pIndex; pIndex < (w * h); pIndex++) {
		if (state[pIndex]==OBJ_MAN||state[pIndex]==OBJ_MAN_ON_GOAL) {
			break;
		}
	}
	// 已经获得p在场景数组中的位置
	 int plarX = pIndex % w; // 一行余数表示x
	 int plarY = pIndex / w; // 一共几行表示y

	 cout << "x:" << plarX << "y:" << plarY << endl;
```

<font class="tip">如果提前将玩家位置保存在某个变量中此处就不用做这样的处理，而且运行起来更快</font>\
<font class="tip">也许会存在保存的值和计算后的值不一样，为了省事可以怎么做，只要不影响速度，重新获取一次数据可以保持数据的精准`（书上的意思是这样的）`</font>

<font class="tip">提到函数的封装</font>\
<font class="understanding">不管过程只管结果 也方便理解代码意思</font>

```C++
    bool checkPlar(Object* state, int index) {
	return state[index] == OBJ_MAN || state[index] == OBJ_MAN_ON_GOAL;
}

	if (checkPlar(state,pIndex)) {
		break;
	}
```

<font class="tip">范围约束</font>

```C++
	int temporaryX = plarX + movX;
	int temporaryY = plarY + movY;
	// 玩家不可以在界外运动  限制移动范围
	if (outRange(temporaryX, temporaryY, w, h)) {
		return;
	}

```

<font class="tip">推动箱子</font>\
<font class="tip">约束箱子运动方式</font>

```C++
	// 获取目标的实体
	int targetPosition = temporaryX + (temporaryY * w);
	Object targetPositionEntity = state[targetPosition];

	// 可移动区域判断
	if (targetPositionEntity == OBJ_SPACE || targetPositionEntity == OBJ_GOAL)
	{
		state[targetPosition] = state[targetPosition] == OBJ_GOAL ? OBJ_MAN_ON_GOAL : OBJ_MAN;
		state[plarPosition] = state[plarPosition] == OBJ_MAN ? OBJ_SPACE : OBJ_GOAL;
	}
	// 不可移动的区域 和箱子区域
	else
	{	//推动的方块 检测目标方块 方块如果是一个墙那么直接不执行下面的语句返回
		int nextTargetPosition = targetPosition + movX + (movY * w);
		// 无法同时推动两个方块
		if (state[nextTargetPosition] == OBJ_WALL || state[nextTargetPosition] == OBJ_BLOCK || state[nextTargetPosition] == OBJ_BLOCK_ON_GOAL) {
			return;
		}
		if (state[targetPosition] == OBJ_BLOCK || state[targetPosition] == OBJ_BLOCK_ON_GOAL) {
			// 检查一下个方块是什么  是空位那么移动方块然后移动人物  消除旧人物
			if (state[nextTargetPosition] == OBJ_SPACE) {
				state[nextTargetPosition] = OBJ_BLOCK;
			}
			// 检查一下个方块是什么  是终点那么移动方块变换方块的值(id)然后移动人物  消除旧人物  允许方块推入终点
			if (state[nextTargetPosition] == OBJ_GOAL) {
				state[nextTargetPosition] = OBJ_BLOCK_ON_GOAL;
			}
			// 提取除公用部分 写入目标的信息  提取擦除玩家的信息
			state[targetPosition] = state[targetPosition] == OBJ_BLOCK_ON_GOAL ? OBJ_MAN_ON_GOAL : OBJ_MAN;
			state[plarPosition] = state[plarPosition] == OBJ_MAN_ON_GOAL ? OBJ_GOAL : OBJ_SPACE;
		}

	}

```

<font class="tip">三目运算符</font>

```C++
	state[plarPosition] = state[plarPosition] == OBJ_MAN_ON_GOAL ? OBJ_GOAL : OBJ_SPACE;
    // 等价于
    if(state[plarPosition] == OBJ_MAN_ON_GOAL)
    {
       state[plarPosition] = OBJ_GOAL ;
    }else{
       state[plarPosition] =  OBJ_SPACE;
    }
```
</details>

## 1.2.9 通关检测

<details>
<summary>通关检测</summary>
<font class="tip">当全部箱子归为表示过关</font>

```C++

    bool checkClear(const Object* state, int w, int h) {
	// 逻辑就是遍历state[] 查看是否还有OBJ_GOAL存在在地图上
	// 书上的意思是去判断OBJ_BLOCK是否还存在于地图上  逻辑其实都差不多
	for (int index = 0; index < w * h; index++)
	{
		if (state[index] == OBJ_GOAL) {
			return false;
		}
	}
	cout << "YOU WIN!" << endl;
	return true;
}

```
</details>

## 完整代码

<font class="tip">主程序</font>
FileName:ConsoleApplication.cpp\
<font class="understanding">场景大小的创建</font>\
<font class="understanding">地图的初始化</font>\
<font class="understanding">主循环</font>\
<font class="understanding">基本逻辑信息</font>\
<font class="understanding">内存展示</font>

<details>
<summary>主程序/主循环</summary>

```c++
    #include "ConsoleApplication1.h"

    const int stateMapWidth = 8;
    const int stateMapHeight = 5;
    int main() {
        // 创建状态数组
        Object* state = new Object[stateMapWidth * stateMapHeight];
        // 初始化场景
        initialize(state, stateMapWidth, stateMapHeight, stageData);
        // 主循环
        while (true) {
            draw(state, stateMapWidth, stateMapHeight);
            // 通关检测
            if (checkClear(state, stateMapWidth, stateMapHeight)) {
                break;
            }
            cout << "a:left s:right w:up z:down,What will you do?" << endl;
            char inputKey;
            cin >> inputKey;
            update(state, inputKey, stateMapWidth, stateMapHeight);
        }
        // 胜利输出

        delete[] state;
        state = 0;

        return 0;
    }
```
</details>

<font class="tip">函数头文件</font>
FileName:ConsoleApplication1.h\
<font class="understanding">头文件中包含实体ID`(Object)`</font>\
<font class="understanding">地图信息`(地图场景)`</font>\
<font class="understanding">函数原型</font>

<details>
<summary>FileName:HeaderImpl.cpp</summary>

```C++
    #include<iostream>

    using namespace std;

    enum Object
    {
        OBJ_SPACE,
        OBJ_WALL,
        OBJ_GOAL,
        OBJ_BLOCK,
        OBJ_BLOCK_ON_GOAL,
        OBJ_MAN,
        OBJ_MAN_ON_GOAL,

        OBJ_UNKONWN
    };

    const char stageData[] = "\
    ########\n\
    #.. p  #\n\
    #oo    #\n\
    #      #\n\
    ########";

    void initialize(Object* state, int w, int h, const char* stageData);
    void draw(const Object* state, int w, int h);
    void update(Object* state, char input, int w, int h);
    bool checkClear(const Object* state, int w, int h);

    bool checkPlar(Object* state,int index);
    bool outRange(int playX, int playY, int mapWidth, int mapHeight);

```
</details>

<font class="tip">头文件函数实现</font>
FileName:HeaderImpl.cpp\
<font class="understanding">实现函数</font>\
<font class="understanding">方块的推动行为的代码是纯手写的可能和书上不太一样会有点BUG</font>

<details>
<summary>FileName:HeaderImpl.cpp</summary>

```C++
    #include "ConsoleApplication1.h"

    void initialize(Object* state, int w, int h, const char* stageData) {
        const char* stageDataCpy = stageData; //???
        int x = 0;
        int y = 0;

        while (*stageDataCpy != '\0')
        {
            Object instantiateObj;
            //= OBJ_UNKONWN; //初始化为未知数据
            switch (*stageDataCpy)
            {
            case ' ':instantiateObj = OBJ_SPACE; break;
            case '#':instantiateObj = OBJ_WALL; break;
            case '.':instantiateObj = OBJ_GOAL; break;
            case 'o':instantiateObj = OBJ_BLOCK; break;
            case 'O':instantiateObj = OBJ_BLOCK_ON_GOAL; break;
            case 'p':instantiateObj = OBJ_MAN; break;
            case 'P':instantiateObj = OBJ_MAN_ON_GOAL; break;
            case '\n':instantiateObj = OBJ_UNKONWN; y++; x = 0; break;
            default:instantiateObj = OBJ_UNKONWN; break;
            }
            if (instantiateObj != OBJ_UNKONWN) {
                state[x + (w * y)] = instantiateObj;
                x++;
            }

            stageDataCpy++;
        }
    }
    void draw(const Object* state, int w, int h) {
        // 场景对应的下标和字符表
        const char font[] = { ' ','#','.','o','O','p','P' };
        // 遍历场景
        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                Object entity = state[x + (w * y)];
                cout << font[entity];
            }
            cout << '\n';
        }
    }
    void update(Object* state, char input, int w, int h) {
        int movX = 0;
        int movY = 0;
        switch (input)
        {
        case 'w':movY = -1; break;
        case 's':movY = 1; break;
        case 'a':movX = -1; break;
        case 'd':movX = 1; break;
        }

        int plarPosition = 0;
        for (plarPosition; plarPosition < (w * h); plarPosition++) {
            if (checkPlar(state, plarPosition)) {
                break;
            }
        }
        // 已经获得p在场景数组中的位置
        int plarX = plarPosition % w; // 一行余数表示x
        int plarY = plarPosition / w; // 一共几行表示y

        cout << "x:" << plarX << "y:" << plarY << endl;

        // 移动
        int temporaryX = plarX + movX;
        int temporaryY = plarY + movY;
        // 玩家不可以在界外运动  限制移动范围
        if (outRange(temporaryX, temporaryY, w, h)) {
            return;
        }
        // 获取目标的实体
        int targetPosition = temporaryX + (temporaryY * w);
        Object targetPositionEntity = state[targetPosition];

        // 可移动区域判断
        if (targetPositionEntity == OBJ_SPACE || targetPositionEntity == OBJ_GOAL)
        {
            state[targetPosition] = state[targetPosition] == OBJ_GOAL ? OBJ_MAN_ON_GOAL : OBJ_MAN;
            state[plarPosition] = state[plarPosition] == OBJ_MAN ? OBJ_SPACE : OBJ_GOAL;
        }
        // 不可移动的区域 和箱子区域
        else
        {	//推动的方块 检测目标方块 方块如果是一个墙那么直接不执行下面的语句返回
            int nextTargetPosition = targetPosition + movX + (movY * w);
            // 无法同时推动两个方块
            if (state[nextTargetPosition] == OBJ_WALL || state[nextTargetPosition] == OBJ_BLOCK || state[nextTargetPosition] == OBJ_BLOCK_ON_GOAL) {
                return;
            }
            if (state[targetPosition] == OBJ_BLOCK || state[targetPosition] == OBJ_BLOCK_ON_GOAL) {
                // 检查一下个方块是什么  是空位那么移动方块然后移动人物  消除旧人物
                if (state[nextTargetPosition] == OBJ_SPACE) {
                    state[nextTargetPosition] = OBJ_BLOCK;
                }
                // 检查一下个方块是什么  是终点那么移动方块变换方块的值(id)然后移动人物  消除旧人物  允许方块推入终点
                if (state[nextTargetPosition] == OBJ_GOAL) {
                    state[nextTargetPosition] = OBJ_BLOCK_ON_GOAL;
                }
                // 提取除公用部分 写入目标的信息  提取擦除玩家的信息
                state[targetPosition] = state[targetPosition] == OBJ_BLOCK_ON_GOAL ? OBJ_MAN_ON_GOAL : OBJ_MAN;
                state[plarPosition] = state[plarPosition] == OBJ_MAN_ON_GOAL ? OBJ_GOAL : OBJ_SPACE;
            }

        }
    }
    bool checkClear(const Object* state, int w, int h) {
        // 逻辑就是遍历state[] 查看是否还有OBJ_GOAL存在在地图上
        // 书上的意思是去判断OBJ_BLOCK是否还存在于地图上  逻辑其实都差不多
        for (int index = 0; index < w * h; index++)
        {
            if (state[index] == OBJ_GOAL) {
                return false;
            }
        }
        cout << "YOU WIN!" << endl;
        return true;
    }


    bool checkPlar(Object* state, int index) {
        return state[index] == OBJ_MAN || state[index] == OBJ_MAN_ON_GOAL;
    }
    bool outRange(int playX, int playY, int mapWidth, int mapHeight) {
        return playX < 0 || playY < 0 || playX >= mapWidth || playY >= mapHeight;
    }
```
</details>