#ifndef CMODELX_H
#define CMODELX_H
#include<vector>
#include"CMatrix.h"
#include"CVector.h"
class CModelX;

#define MODEL_FILE "sample.blend.x"
//�̈�J�����}�N����
#define SAFE_DELETE_ARRAY(a){if(a)delete[]a;a=0;}
#define ARRY_SIZE(a)(sizeof(a)/sizeof(a[0]))

class CMesh{
public:
	int mVertexNum; //���_��
	CVector*mpVertex; //���_�f�[�^
	int mFaceNum; //�ʐ�
	int *mpVertexIndex; //�ʂ��\�����钸�_�ԍ�
	int mNormalNum; //�@����
	CVector *mpNormal;
	//�R���X�g���N�^
	CMesh()
		:mVertexNum(0)
		, mpVertex(0)
	    ,mFaceNum(0)
	    ,mpVertexIndex(nullptr)
		,mNormalNum(0)
		, mpNormal(nullptr)
	{}
	//�f�X�g���N�^
	~CMesh(){
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
	}
	void Init(CModelX*model);
	void CMesh::Render(){
		//���_�f�[�^�Ɩ@���f�[�^�̔z���L��
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		//���_�f�[�^�Ɩ@���f�[�^�̏ꏊ���w��
		glVertexPointer(3,GL_FLOAT,0,mpVertex);
		glNormalPointer(GL_FLOAT,0,mpNormal);

		//���_�̃C���f�b�N�X�̏ꏊ���w�肵�Đ}�`��`��
		glDrawElements(GL_TRIANGLES, 3 * mFaceNum, 
			GL_UNSIGNED_INT, mpVertexIndex);

		//���_�f�[�^�A�@���f�[�^�̔z�񖳌�
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
};


class CModelXFrame{
public:
	std::vector<CModelXFrame*>mChild;
	CMatrix mTransformMatrix;
	char* mpName;
	int mIndex;
	//Mesh�f�[�^
	CMesh mMesh;
	//�R���X�g���N�^
	CModelXFrame(CModelX*model);
	//�f�X�g���N�^
	~CModelXFrame(){
		std::vector<CModelXFrame*>::iterator itr;
		for (itr = mChild.begin(); itr != mChild.end(); itr++){
			delete *itr;
		}
		SAFE_DELETE_ARRAY(mpName);
	}
	void CModelXFrame::Render(){
		if (mMesh.mFaceNum != 0)
			mMesh.Render();
	}
};


class CModelX{
public:
	char*mpPointer;
	char mToken[1024];

	std::vector<CModelXFrame*>mFrame;
	CModelX() :mpPointer(0)
	{}
	~CModelX(){
		if (mFrame.size() > 0){
			delete mFrame[0];
		}
	}
	void Load(char*file);
	void GetToken();
	//���������_�f�[�^�̎擾
	float GetFloatToken();
	void SkipNode();
	//�����f�[�^�̎擾
	int CModelX::GetIntToken(){
		GetToken();
		return atoi(mToken);
	}
	void CModelX::Render(){
		for (int i = 0; i < mFrame.size(); i++){
			mFrame[i]->Render();
		}
	}
};

#endif