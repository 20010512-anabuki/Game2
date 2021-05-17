#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CText.h"
#include"CRes.h"
#include"CKey.h"

CMatrix Matrix;

CSceneGame::~CSceneGame() {

}


void CSceneGame::Init() {
	//3D���f���t�@�C���̓ǂݍ���
	CRes::sModelX.Load(MODEL_FILE);
	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
}


void CSceneGame::Update() {
	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	e = CVector(1.0f, 2.0f, 10.0f);
	//�����_�����߂�
	c = CVector();
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f);

	Camera.Set(e, c, u);
	Camera.Render();
	if (CKey::Push('K')){
		Matrix = Matrix*CMatrix().RotateX(1);
	}
	if (CKey::Push('L')){
		Matrix = Matrix*CMatrix().RotateY(1);
	}
	if (CKey::Push('I')){
		Matrix = Matrix*CMatrix().RotateX(1);
	}
	if (CKey::Push('J')){
		Matrix = Matrix*CMatrix().RotateY(1);
	}

	glMultMatrixf(Matrix.mF);
	CRes::sModelX.Render();

	//�J�����̐ݒ�
	Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);




	//2D�`��J�n
	Start2D(0, 800, 0, 600);

	CText::DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�`��I��
	End2D();

	return;
}

