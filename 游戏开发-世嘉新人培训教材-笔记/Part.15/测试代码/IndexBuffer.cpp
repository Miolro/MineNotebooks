#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(int iSize)
{
    mSize = iSize;
    mIndexValue = new unsigned[iSize];
}

void IndexBuffer::setIndex(int index, unsigned indexValue)const
{
    mIndexValue[index] = indexValue;
}

unsigned IndexBuffer::getIndexValue(int index)const
{
    return mIndexValue[index];
}

int IndexBuffer::size()const
{
    return mSize;
}
