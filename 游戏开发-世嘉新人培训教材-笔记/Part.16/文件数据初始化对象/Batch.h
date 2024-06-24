#pragma once
#include "GameLib/Framework.h"
class VertextBuffer;
class IndexBuffer;
class Matrix44;
class Batch
{
public:
	Batch(const VertextBuffer* vertextBuffer, const IndexBuffer* indexBuffer, const GameLib::Texture* texture);
	void draw(const Matrix44& matrix) const;
private:
	const VertextBuffer* mVertextBuffer;
	const IndexBuffer* mIndexBuffer;
	const GameLib::Texture* mTexture;
};

