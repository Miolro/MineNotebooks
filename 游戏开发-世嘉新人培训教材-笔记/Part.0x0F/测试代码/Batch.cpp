#include "Batch.h"
#include "IndexBuffer.h"
#include "VertextBuffer.h"
#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix44.h"
using namespace GameLib;


Batch::Batch(const VertextBuffer* vertextBuffer, const IndexBuffer* indexBuffer, const Texture* texture) :
	mVertextBuffer(vertextBuffer),
	mIndexBuffer(indexBuffer),
	mTexture(texture)
{
}

void Batch::draw(const Matrix44& matrix)const
{
	int tSize = mVertextBuffer->size();
	double* transformPoint = new double[tSize * 4];
	for (int i = 0; i < tSize; i++)
	{
		// 参考世界变换进行变化
		matrix.multiply(&transformPoint[i * 4], mVertextBuffer->getPosition(i));
	}
	int triangleNumber = mIndexBuffer->size() / 3;
	for (int i = 0; i < triangleNumber; i++)
	{
		unsigned i0 = mIndexBuffer->getIndexValue(i * 3 + 0);
		unsigned i1 = mIndexBuffer->getIndexValue(i * 3 + 1);
		unsigned i2 = mIndexBuffer->getIndexValue(i * 3 + 2);

		GameLib::Framework::instance().drawTriangle3DH(
			&transformPoint[i0 * 4],
			&transformPoint[i1 * 4],
			&transformPoint[i2 * 4], 0, 0, 0);
	}
}

