#include <sstream>
#include "GameLib/Framework.h"
#include "GameLib/Math.h"
#include "Document.h"
#include "VertextBuffer.h"
#include "IndexBuffer.h"
#include "Batch.h"
#include "Model.h"
#include "Camera.h"
#include "Matrix44.h"
using namespace GameLib;
using namespace std;

Document* document;
bool init = false;

VertextBuffer** vertexBuffer;
IndexBuffer** indexBuffer;
Texture* texture;
Batch* batch;
Model* model;
Camera* camera;
Matrix44 worldMatrix;
int gCount;
namespace GameLib {

	void Framework::update() {
		setFrameRate(60);
		if (!init)
		{
			//Pad::create(); //初始化
			//gVertextBuffer = new VertextBuffer(8);
			//gIndexBuffer = new IndexBuffer(36);
			//// 顶点坐标
			//for (int i = 0; i < 8; i++)
			//{
			//	gVertextBuffer->setPosition(i, pointPosition[i]);
			//	gVertextBuffer->setUVPosition(i, uvPosition[i]);
			//}
			//// 三角形组索引坐标
			//for (int i = 0; i < 12; i++)
			//{
			//	gIndexBuffer->setIndex(i * 3 + 0, gIndices[i * 3 + 0]);
			//	gIndexBuffer->setIndex(i * 3 + 1, gIndices[i * 3 + 1]);
			//	gIndexBuffer->setIndex(i * 3 + 2, gIndices[i * 3 + 2]);
			//}

			document = new Document("data.txt");
			const Element* rootNode = document->root();
			int nodeSize = rootNode->size();

			int vertexBufferNum = 0;
			int indexBufferNum = 0;
			int textureNum = 0;
			int batchNum = 0;

			for (int i = 0; i < nodeSize; i++)
			{
				const Element* child = rootNode->child(i);
				const string* name = child->name();
				if (*name == "VertexBuffer")
				{
					vertexBufferNum++;
				}
				else if (*name == "IndexBuffer")
				{
					indexBufferNum++;
				}
				else if (*name == "Texture")
				{
					textureNum++;
				}
				else if (*name == "Batch")
				{
					batchNum++;
				}
			}
			vertexBuffer = new VertextBuffer * [vertexBufferNum];
			indexBuffer = new IndexBuffer * [indexBufferNum];
			for (int i = 0; i < nodeSize; i++)
			{
				const Element* child = rootNode->child(i);
				const string* name = child->name();
				if (*name == "VertexBuffer")
				{
					vertexBuffer[--vertexBufferNum] = new VertextBuffer(child);
				}
				else	if (*name == "IndexBuffer")
				{
					indexBuffer[--indexBufferNum] = new IndexBuffer(child);
				}
			}
			batch = new Batch(vertexBuffer[0], indexBuffer[0], texture);
			model = new Model(batch);
			camera = new Camera();
			init = !init;
		}

		camera->setPosition(Vector3(
			sin(gCount) * 20.0,
			20.0,
			cos(gCount) * 20.0));
		camera->createPerspectiveViewMatrix(&worldMatrix);
		model->draw(worldMatrix);
		gCount++;
	}
}