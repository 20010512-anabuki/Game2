#ifndef CSCENE_H
#define CSCENE_H

/*
�V�[���̊��N���X
*/
class CScene {
public:
	//�V�[���̎��ʎq
	enum EScene {
		EGAME,	//�Q�[��
		EGAME2,	//�Q�[��2
		EGAME3,	//�Q�[��3
		ETITLE, 	//�^�C�g��
		EGAMEOVER,  //�Q�[���I�[�o�[
		EGAMECLEAR,  //�Q�[���N���A
	};
	//���̃V�[��
	EScene mScene;
	//virtual ���z�֐�
	//�|�����[�t�B�Y���̎���
	//=0 �������z�֐��̐ݒ�
	virtual void Init() = 0;	//�������z�֐� ����������
	virtual void Update() = 0; //�������z�֐� �X�V����
	//���̃V�[���̎擾
	virtual EScene GetNextScene() = 0;
	virtual ~CScene() {}	//�f�X�g���N�^�̒�`
};


#endif