#include "VisualEntity.h"
#include "../Renderer.h"
#include "../Shader/VertexShader/VertexShader.h"
#include "../Shader/PixelShader/PixelShader.h"
#include "../../../Game/GameObject/GameObject.h"

VisualEntity::VisualEntity(const std::vector<std::shared_ptr<VisualEntityData>>& _entityData)
    : mEntityData(_entityData)
    , mOwnerObject(nullptr)
    , mbDestroy(false)
    , mbVisible(true)
{
    mDrawType.resize(2);
    mDrawType[0] = DrawType::Draw_SolidBack;
    mDrawType[1] = DrawType::Draw_SolidFront;
}

VisualEntity::VisualEntity(const std::shared_ptr<VisualEntityData>& _entityData)
    : mOwnerObject(nullptr)
    , mbDestroy(false)
    , mbVisible(true)
{
    mEntityData.push_back(_entityData);
    mDrawType.resize(2);
    mDrawType[0] = DrawType::Draw_SolidBack;
    mDrawType[1] = DrawType::Draw_SolidFront;
}

VisualEntity::VisualEntity()
    : mOwnerObject(nullptr)
    , mbDestroy(false)
    , mbVisible(true)
{
    mDrawType.resize(2);
    mDrawType[0] = DrawType::Draw_SolidBack;
    mDrawType[1] = DrawType::Draw_SolidFront;
}

VisualEntity::~VisualEntity()
{ 
    for (size_t shader_i = 0; shader_i < mVertexShader.size(); shader_i++)
    {
        mVertexShader[shader_i]->Uninit();
        mPixelShader[shader_i]->Uninit();
    }
   
}

void VisualEntity::Draw()
{
    if (!mbVisible)
    {
        return;
    }

    for (uint8_t i = 0; i < mEntityData.size(); i++)
    {   
        //　シェーダーの数だけ描画する
        for (size_t shader_i = 0; shader_i < mVertexShader.size(); shader_i++)
        {
            SetRasterizerState(shader_i);
            mVertexShader[shader_i]->UpdateBuffer(i);
            mPixelShader[shader_i]->UpdateBuffer(i);
            mVertexShader[shader_i]->BindShader();
            mPixelShader[shader_i]->BindShader();
            mEntityData[i]->Draw();
        } 
    }
}

void VisualEntity::DrawDropShadow()
{
    if (!mbVisible)
    {
        return;
    }

    for (uint8_t i = 0; i < mEntityData.size(); i++)
    {
        //　シェーダーの数だけ描画する
        for (size_t shader_i = 0; shader_i < mVertexShader.size(); shader_i++)
        {
            // TODO: アウトラインを描画すると影がおかしくなる
            // アウトライン表示用シェーダーで影を書くと正常
            // 通常描画用のシェーダーで書くと影がバグる
            if (mVertexShader[shader_i]->IsDropShadow())
            {
                continue;
            }

            SetRasterizerState(shader_i);
            mVertexShader[shader_i]->UpdateBuffer(i);
            mPixelShader[shader_i]->UpdateBuffer(i);
            mVertexShader[shader_i]->BindShader();
            mPixelShader[shader_i]->BindShader();
            mEntityData[i]->Draw();
        }
    }
}

void VisualEntity::SetRasterizerState(const size_t entity_i)
{
    Renderer& renderer = Renderer::GetInstance();

    if (mDrawType[entity_i] == DrawType::Draw_SolidBack)
    {
        renderer.SetRasterizerSolidBack();
    }
    else if (mDrawType[entity_i] == DrawType::Draw_SolidFront)
    {
        renderer.SetRasterizerSolidFront();
    }
    else if (mDrawType[entity_i] == DrawType::Draw_WireFrame)
    {
        renderer.SetRasterizerWireFrame();
    }
}

void VisualEntity::Copy(const std::shared_ptr<VisualEntity> _entity)
{
    mOwnerObject = nullptr;
    mDrawType = _entity->mDrawType;
    
    VisualEntityData::Description desc;
    for (std::shared_ptr<VisualEntityData> data : _entity->mEntityData)
    {
        desc = data->GetDescripstion();
        mEntityData.push_back(std::make_shared<VisualEntityData>(data));  
    }
}