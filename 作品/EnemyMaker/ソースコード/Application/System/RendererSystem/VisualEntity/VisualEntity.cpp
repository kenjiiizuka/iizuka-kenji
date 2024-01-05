//---------- INCLUDES ----------
#include "VisualEntity.h"
#include "../Renderer.h"
#include "../Shader/VertexShader/VertexShader.h"
#include "../Shader/PixelShader/PixelShader.h"
#include "../Shader/GeometryShader/GeometryShader.h"
#include "../../../Game/GameObject/GameObject.h"

VisualEntity::VisualEntity(const std::vector<std::shared_ptr<VisualEntityData>>& _entityData)
    : mEntityData(_entityData)
    , mOwnerObject(nullptr)
    , mbDestroy(false)
    , mbVisible(true)
{
    mDrawType.resize(2);
    mDrawType[0] = CullType::Draw_SolidBack;
    mDrawType[1] = CullType::Draw_SolidFront;
}

VisualEntity::VisualEntity(const std::shared_ptr<VisualEntityData>& _entityData)
    : mOwnerObject(nullptr)
    , mbDestroy(false)
    , mbVisible(true)
{
    mEntityData.push_back(_entityData);
    mDrawType.resize(2);
    mDrawType[0] = CullType::Draw_SolidBack;
    mDrawType[1] = CullType::Draw_SolidFront;
}

VisualEntity::VisualEntity()
    : mOwnerObject(nullptr)
    , mbDestroy(false)
    , mbVisible(true)
{
    mDrawType.resize(2);
    mDrawType[0] = CullType::Draw_SolidBack;
    mDrawType[1] = CullType::Draw_SolidFront;
}

VisualEntity::~VisualEntity()
{ 
    // �V�F�[�_�[�̏I������
    for (size_t shader_i = 0; shader_i < mVertexShader.size(); shader_i++)
    {
        mVertexShader[shader_i]->Uninit();
        mPixelShader[shader_i]->Uninit();
    }

    for (std::shared_ptr<GeometryShader>& geom : mGeometryShader)
    {
        geom->Uninit();
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
        //�@�V�F�[�_�[�̐������`�悷��
        for (size_t shader_i = 0; shader_i < mVertexShader.size(); shader_i++)
        {
            SetRasterizerState(shader_i);
            mVertexShader[shader_i]->UpdateBuffer(i);
            mPixelShader[shader_i]->UpdateBuffer(i);
            mVertexShader[shader_i]->BindShader();
            mPixelShader[shader_i]->BindShader();
            SetupGeometryShader(shader_i);
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

    // �e�`�掞�ɃW�I���g���V�F�[�_�[�͎g�p���Ȃ�
    GeometryShader::Deallocate();

    // �ʂ�Ԃ��ŕ`��
    Renderer::GetInstance().SetRasterizerSolidBack();

    for (uint8_t i = 0; i < mEntityData.size(); i++)
    {
        //�@�V�F�[�_�[�̐������`�悷��
        for (size_t shader_i = 0; shader_i < mVertexShader.size(); shader_i++)
        {
            if (!mVertexShader[shader_i]->IsDropShadow())
            {
                continue;
            }

       
            mVertexShader[shader_i]->UpdateBuffer(i); 
            mVertexShader[shader_i]->BindShader();

            // �e�������ݗp�̃V�F�[�_�[���g�����߂�0��
            mPixelShader[0]->UpdateBuffer(i);
            mPixelShader[0]->BindShader();
            mEntityData[i]->Draw();
        }
    }
}

void VisualEntity::SetRasterizerState(const size_t entity_i)
{
    Renderer& renderer = Renderer::GetInstance();

    if (mDrawType[entity_i] == CullType::Draw_SolidBack)
    {
        renderer.SetRasterizerSolidBack();
    }
    else if (mDrawType[entity_i] == CullType::Draw_SolidFront)
    {
        renderer.SetRasterizerSolidFront();
    }
    else if (mDrawType[entity_i] == CullType::Draw_WireFrame)
    {
        renderer.SetRasterizerWireFrame();
    }
}

void VisualEntity::SetupGeometryShader(const size_t shader_i)
{
    // �z��O�Q�ƃ`�F�b�N
    if (shader_i >= mGeometryShader.size())
    {
        // ���蓖�ĉ���
        GeometryShader::Deallocate();
        return;
    }

    mGeometryShader[shader_i]->UpdateBuffer(shader_i);
    mGeometryShader[shader_i]->BindShader();
}

void VisualEntity::Copy(const std::shared_ptr<VisualEntity> _entity)
{
    mOwnerObject = nullptr;
    mDrawType = _entity->mDrawType;
    
    VisualEntityData::Description desc;
    for (std::shared_ptr<VisualEntityData> data : _entity->mEntityData)
    {
        desc = data->GetDescription();
        mEntityData.push_back(std::make_shared<VisualEntityData>(data));  
    }
}