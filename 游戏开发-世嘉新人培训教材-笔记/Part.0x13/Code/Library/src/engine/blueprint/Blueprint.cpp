#include "engine/blueprint/Blueprint.h"
#include "engine/blueprint/IndexBuffer.h"
#include "engine/blueprint/VertexBuffer.h"
#include "engine/blueprint/Texture.h"
#include "engine/blueprint/Batch.h"
#include "base/xml/Document.h"
#include "base/xml/Element.h"
#include "base/xml/Attribute.h"
namespace engine
{
    namespace blueprint
    {
        Blueprint::Blueprint(base::xml::Document& doc) :
            mVertexBuffer(0),
            mIndexBuffer(0),
            mTexturte(0)
        {
            create(doc);
        }

        Blueprint::Blueprint(const char* filename) :
            mVertexBuffer(0),
            mIndexBuffer(0),
            mTexturte(0)
        {
            base::xml::Document doc(filename);
            create(doc);
        }

        const VertexBuffer* Blueprint::vertexBuffer(const char* key)const
        {
            for (int i = 0; i < mVertexBufferSize; i++)
            {
                if (*mVertexBuffer[i]->name() == key)
                {
                    return mVertexBuffer[i];
                }
            }
            return nullptr;
        }

        const IndexBuffer* Blueprint::indexBuffer(const char* key)const
        {
            for (int i = 0; i < mIndexBufferSize; i++)
            {
                if (*mIndexBuffer[i]->name() == key)
                {
                    return mIndexBuffer[i];
                }
            }
            return nullptr;
        }

        const Texture* Blueprint::texture(const char* key)const
        {
            for (int i = 0; i < mTexturteSize; i++)
            {
                if (*mTexturte[i]->name() == key)
                {
                    return mTexturte[i];
                }
            }
            return nullptr;
        }

        const Batch* Blueprint::batch(const char* key)const
        {
            for (int i = 0; i < mBatchSize; i++)
            {
                if (*mBatch[i]->name() == key)
                {
                    return mBatch[i];
                }
            }
            return nullptr;
        }

        void Blueprint::create(base::xml::Document& doc)
        {
            int vertexBufferNum = 0;
            int indexBufferNum = 0;
            int textureNum = 0;
            int batchNum = 0;
            // 解析数量
            const base::xml::Element* root = doc.root();
            int chileSize = root->childrenNum();
            for (int i = 0; i < chileSize; i++)
            {
                const base::xml::Element* ele = root->children(i);
                const std::string* name = ele->name();
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
            mVertexBufferSize = vertexBufferNum;
            mIndexBufferSize = indexBufferNum;
            mTexturteSize = textureNum;
            mBatchSize = batchNum;

            int indexVertex = 0;
            int indexBuffer = 0;
            int indexTexture = 0;
            int indexBatch = 0;

            // 生成对应数量的对象
            mVertexBuffer = new VertexBuffer * [vertexBufferNum];
            mIndexBuffer = new IndexBuffer * [indexBufferNum];
            mTexturte = new Texture * [textureNum];
            mBatch = new Batch * [batchNum];

            for (int i = 0; i < root->childrenNum(); i++)
            {
                const base::xml::Element ele = *(root->children(i));
                const std::string* name = ele.name();
                if (*name == "VertexBuffer")
                {
                    --vertexBufferNum;
                    mVertexBuffer[vertexBufferNum] = new VertexBuffer(ele);

                }
                else if (*name == "IndexBuffer")
                {
                    --indexBufferNum;
                    mIndexBuffer[indexBufferNum] = new IndexBuffer(ele);

                }
                else if (*name == "Texture")
                {
                    --textureNum;
                    mTexturte[textureNum] = new Texture(ele);

                }
                else if (*name == "Batch")
                {
                    --batchNum;
                    mBatch[batchNum] = new Batch(ele, *this);
                }
            }
        }
    }
}