# 第17章 编写高性能代码

## 二分法查询一般在32次找到
```c++
	const int n = 2500 * 10000;
	int* a = new int[n];
	//生成适当排序的数据
	for (int i = 0; i < n; ++i) {
		a[i] = i * 5;
	}


	//二分发查询 0-2500 * 10000-1的范围
	int headPosition = 0;
	int tailPosition = n - 1; // 因为需要把0计入
	int targetNum = 7287490;  // 目标数字
    /*
        这里可以补上是否超出头位置和尾的位置判断  比较头尾的位置是否在这个范围里面
    */
	int loopCount = 0;  // 循环次数
    while (headPosition < tailPosition)
    {
        int middlePosition = (headPosition + tailPosition) / 2;  // 对比中间这个数值是应该取中间位置的左边还是右边
        cout << loopCount << "\t" << headPosition << "-" << tailPosition << "\tmiddle=" << middlePosition << "\trange=" << tailPosition - headPosition << endl;
        if (targetNum < a[middlePosition]) {
            tailPosition = middlePosition - 1;  // (忽略的位置) Middle (指向的位置)
        }
        else if (a[middlePosition] < targetNum) {
            headPosition = middlePosition + 1;  // (指向的位置)Middle(忽略的位置)
        }
        else {
            headPosition = tailPosition = middlePosition;
        }
        loopCount++;
    }
    if (a[headPosition] == targetNum)
    {
        cout << "Find! " << a[headPosition] << endl;
    }
    else
    {
        cout << "NOT Find! " << endl;
    }
    delete[] a;
    return 0;
```