#include "VisualEntityData.h"
#include "../Renderer.h"
#include "../../../Utility/Debug.h"
#include "../../../Game/Component/SkeletalMeshComponent/SkeletalMeshComponent.h"

VisualEntityData::VisualEntityData(const Description& _desc)
    : mIndexBuffer(nullptr)
    , mVertexBuffer(nullptr)
    , mDesc(_desc)
{
    HRESULT hr = E_FAIL;
    hr = CreateVertexBuffer(_desc.mpVertex.get(), _desc.mVertexTypeByteSize, _desc.mVertexCount, _desc.mbAbleMap);
    if (mDesc.mbUseIndex)
    {
        hr = CreateIndexBuffer(_desc.mpIndex.get(), _desc.mIndexTypeByteSize, _desc.mIndexCount);
    }
}

VisualEntityData::VisualEntityData(const std::shared_ptr<VisualEntityData>& _entity)
    : mIndexBuffer(nullptr)
    , mVertexBuffer(nullptr)
    , mMaterial(_entity->mMaterial)
{
    mDesc = _entity->mDesc;
    HRESULT hr = E_FAIL;
    hr = CreateVertexBuffer(mDesc.mpVertex.get(), mDesc.mVertexTypeByteSize, mDesc.mVertexCount, mDesc.mbAbleMap);
    if (mDesc.mbUseIndex)
    {
        hr = CreateIndexBuffer(mDesc.mpIndex.get(), mDesc.mIndexTypeByteSize, mDesc.mIndexCount);
    }
}

VisualEntityData::~VisualEntityData()
{
    SAFE_RELEASE(mVertexBuffer)
    SAFE_RELEASE(mIndexBuffer)
}

void VisualEntityData::Draw()
{
    ID3D11DeviceContext* context = Renderer::GetInstance().GetDeviceContext();
    UINT offset = 0;

    UINT stride = mDesc.mVertexTypeByteSize;
    context->IASetPrimitiveTopology(mDesc.mTopology);
    context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
    if (mDesc.mbUseIndex)
    {
        // 描画 
        DXGI_FORMAT format{};
        switch (mDesc.mIndexTypeByteSize)
        {
        case 4:
            format = DXGI_FORMAT_R32_UINT;
            break;
        case 2:
            format = DXGI_FORMAT_R16_UINT;
            break;
        }
        context->IASetIndexBuffer(mIndexBuffer, format, 0);
        context->DrawIndexed(mDesc.mIndexCount, 0, 0);
    }
    else
    {
        context->Draw(mDesc.mVertexCount, 0);
    } 
}

HRESULT VisualEntityData::CreateVertexBuffer(const void* _pVertexData, uint32_t _size, uint32_t _count, bool _isWrite)
{
    D3D11_BUFFER_DESC bufDesc{};
    bufDesc.ByteWidth = _size * _count;
    bufDesc.Usage = D3D11_USAGE_DEFAULT;
    bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    if (_isWrite)
    {
        bufDesc.Usage = D3D11_USAGE_DYNAMIC;
        bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    }
    // バッファの初期値を設定
    D3D11_SUBRESOURCE_DATA subDate{};
    subDate.pSysMem = _pVertexData;

    // 頂点バッファの作成
    return Renderer::GetInstance().GetDevice()->CreateBuffer(&bufDesc, &subDate, &mVertexBuffer);
}

HRESULT VisualEntityData::CreateIndexBuffer(const void* _pIndexData, uint32_t _size, uint32_t _count)
{
    D3D11_BUFFER_DESC bufDesc{};
    bufDesc.ByteWidth = _size * _count;
    bufDesc.Usage = D3D11_USAGE_DEFAULT;
    bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    // バッファの初期データ
    D3D11_SUBRESOURCE_DATA subData{};
    subData.pSysMem = _pIndexData;

    //インデックスバッファの作成
    return Renderer::GetInstance().GetDevice()->CreateBuffer(&bufDesc, &subData, &mIndexBuffer);
}

HRESULT VisualEntityData::ReMakeVertexBuffer(void* _pVertexData, uint32_t _size, uint32_t _count, bool _isWrite)
{ 
    mDesc.mpVertex.reset();
    mDesc.mVertexTypeByteSize = _size;
    mDesc.mVertexCount = _count; 
    std::shared_ptr<void> newVertexData(
        _pVertexData,
        //[](void* _data) {delete[] static_cast<SkeletalMesh::VertexWeight*>(_data); }
        [](void* _data) {delete[] (_data); }
    );
    mDesc.mpVertex = newVertexData;

    mVertexBuffer->Release(); 
    HRESULT hr = CreateVertexBuffer(_pVertexData, _size, _count, _isWrite); 
    return hr;
}

HRESULT VisualEntityData::ReMakeVertexBuffer(std::function<void(const Description&, Description*)> _reDesc)
{
    Description desc;
    _reDesc(mDesc, &desc);   
    HRESULT hr = CreateVertexBuffer(desc.mpVertex.get(), desc.mVertexTypeByteSize, desc.mVertexCount, desc.mbAbleMap);
    hr = CreateIndexBuffer(desc.mpIndex.get(), desc.mIndexTypeByteSize, desc.mIndexCount);
    return hr;
}

HRESULT VisualEntityData::MapVertexBuffer(void* _vertexData)
{
    if (!mDesc.mbAbleMap)
    {
        Cout("この頂点データはMapすることができません");
        return E_FAIL;
    }
 
    HRESULT hr;
    ID3D11Device* device = Renderer::GetInstance().GetDevice();
    ID3D11DeviceContext* context = Renderer::GetInstance().GetDeviceContext();
    D3D11_MAPPED_SUBRESOURCE mapResource;

    // MapしてデータをmapResourceにコピーする
    hr = context->Map(mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);
    if (SUCCEEDED(hr))
    {
        rsize_t size = mDesc.mVertexCount * mDesc.mVertexTypeByteSize;
        memcpy_s(mapResource.pData, size, _vertexData, size);
        context->Unmap(mVertexBuffer, 0);
    }
    return hr;
}

void VisualEntityData::SetMaterial(Material _material)
{
    mMaterial = _material;
}

VisualEntityData::Material::Material()
    : mDiffuse(1,1,1,1)
    , mAmbient(0.3f, 0.3f, 0.3f,0.3f)
    , mShininess(1.0f)
    , TextureEnable(false)
    , mDummy()
{
}

VisualEntityData::Description::Description()
    : mpVertex(nullptr)
    , mpIndex(nullptr)
    , mbAbleMap(false)
    , mbUseIndex(false)
    , mVertexCount(0)
    , mVertexTypeByteSize(0)
    , mIndexCount(0)
    , mIndexTypeByteSize(0)
    , mTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
}

VisualEntityData::Description::Description(const Description& _desc)
    : mTopology(_desc.mTopology)
    , mbAbleMap(_desc.mbAbleMap)
    , mIndexCount(_desc.mIndexCount)
    , mIndexTypeByteSize(_desc.mIndexTypeByteSize)
    , mVertexCount(_desc.mVertexCount)
    , mVertexTypeByteSize(_desc.mVertexTypeByteSize)
    , mbUseIndex(_desc.mbUseIndex)
    , mpIndex(_desc.mpIndex)
    , mpVertex(_desc.mpVertex)
{
}
