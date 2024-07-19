#pragma once
namespace base
{
    namespace xml
    {
        class Document;
    }
}
using namespace base::xml;
namespace engine
{
    namespace blueprint
    {
        
        class VertexBuffer;
        class IndexBuffer;
        class Texture;
        class Batch;
        class Blueprint
        {
        public:
            // 传入解析后的document做为蓝图
            Blueprint(Document& doc);
            // 传入xml文件做为蓝图
            Blueprint(const char* filename);

            const VertexBuffer* vertexBuffer(const char* key)const;
            const IndexBuffer* indexBuffer(const char* key)const;
            const Texture* texture(const char* key)const;
            const Batch* batch(const char* key)const;

            void create(Document& doc);
        private:
            VertexBuffer** mVertexBuffer;
            IndexBuffer** mIndexBuffer;
            Texture** mTexturte;
            Batch** mBatch;

            int mVertexBufferSize;
            int mIndexBufferSize;
            int mTexturteSize;
            int mBatchSize;

        };
    }
}
