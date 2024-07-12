#include <sstream>
#include "GameLib/Framework.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Keyboard.h"
#include "GameLib/Math.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix34.h"
#include "Matrix44.h"
#include "GameLib/Math.h"
#include "Robo.h"
#include "Stage.h"
#include "Pad.h"
#include <iostream>
#include "VertextBuffer.h"
#include "IndexBuffer.h"
#include "Batch.h"
#include "Camera.h"
#include "Model.h"
using namespace GameLib;
using namespace std;

const Vector3 pointPosition[8] = {  // 顶点位置
	Vector3(-0.5, 2.0, -0.5),
	Vector3(0.5, 2.0, -0.5),
	Vector3(-0.5, 2.0, 0.5),
	Vector3(0.5, 2.0, 0.5),
	Vector3(-0.5, 0.0, -0.5),
	Vector3(0.5, 0.0, -0.5),
	Vector3(-0.5, 0.0, 0.5),
	Vector3(0.5, 0.0, 0.5),
};

const Vector2 uvPosition[8] = {
	Vector2(0.0,0.0),
	Vector2(0.0,0.0),
	Vector2(0.0,0.0),
	Vector2(0.0,0.0),
	Vector2(0.0,0.0),
	Vector2(0.0,0.0),
	Vector2(0.0,0.0),
	Vector2(0.0,0.0),
};
//三角形顶点索引
const unsigned gIndices[36] = {
	4,5,6,  // 地面三角形组 -y
	7,5,6,

	0,1,2, // 顶部
	3,1,2,

	2,0,6, // 左边
	4,0,6,

	3,1,7, // 右边
	5,1,7,

	2,3,6, // 后边
	7,3,6,

	0,1,4, // 前边
	5,1,4,
};

VertextBuffer* gVertextBuffer;
IndexBuffer* gIndexBuffer;
Texture* gTexture;
Batch* gBatch;
Camera* gCamera;
Matrix44 worldMatrix;
Model* gModel;
int gCount;
bool init = false;
namespace GameLib {

	void Framework::update() {
		setFrameRate(60);
		if (!init)
		{
			Pad::create(); //初始化
			gVertextBuffer = new VertextBuffer(8);
			gIndexBuffer = new IndexBuffer(36);
			// 顶点坐标
			for (int i = 0; i < 8; i++)
			{
				gVertextBuffer->setPosition(i, pointPosition[i]);
				gVertextBuffer->setUVPosition(i, uvPosition[i]);
			}
			// 三角形组索引坐标
			for (int i = 0; i < 12; i++)
			{
				gIndexBuffer->setIndex(i * 3 + 0, gIndices[i * 3 + 0]);
				gIndexBuffer->setIndex(i * 3 + 1, gIndices[i * 3 + 1]);
				gIndexBuffer->setIndex(i * 3 + 2, gIndices[i * 3 + 2]);
			}
			gBatch = new Batch(gVertextBuffer, gIndexBuffer, gTexture);
			gModel = new Model(gBatch);
			gCamera = new Camera();

			init = !init;
		}
		gCamera->setPosition(Vector3(
			sin(gCount) * 8.0,
			8.0,
			cos(gCount) * 8.0));
		gCamera->createPerspectiveViewMatrix(&worldMatrix);
		gModel->draw(worldMatrix);
		gCount++;
	}
}