#include "CPlayer.h"
#include "CKey.h"
#include "CBullet.h"
#include "CTexture.h"
#define G  1
#define VJ0 18
#define ANICNT 30



//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
extern CTexture Texture;
extern int CountEnemy;
extern int CountItem;
extern int CountKeyBlock;
extern int CountKeyItem;

CPlayer*CPlayer::spInstance = 0;
CPlayer::CPlayer()
: mFx(1.0f), mFy(0.0f)
, FireCount(0)
, mVj(0)
, mJump(0)
, mGameover(false)
, mGameclear(false)
{
	mTag = EPLAYER;
	spInstance = this;
}

void CPlayer::Update() {
	if (mGameover){
		return;
	}
	if (mGameclear){
		return;
	}

	//static���\�b�h�͂ǂ�����ł��Ăׂ�
	if (CKey::Push('A')) {
		x -= 3;
		mFx = -1;
		mFy = 0;
		if (x - w < -400) {
			x = -400 + w;
		}
	}
	if (CKey::Push('D')) {
		x += 3;
		mFx = 1;
		mFy = 0;
		//if (x + w > 400) {
			//x = 400 - w;
		//}
	}
	//if (CKey::Push('W')) {
		//y += 3;
		//mFx = 0;
		//mFy = 1;
		//if (y + h > 300) {
		//y = 300 - h;
		//}
	//}
	if (CKey::Push('S')) {
		y -= 3;
		//mFx = 0;
		//mFy = -1;
		if (y - h < -300) {
			y = -300 + h;
		}
	}
	
	//�X�y�[�X�L�[�Œe����
	//0���傫���Ƃ�1���Z����
	if (FireCount > 0) {
		FireCount--;
	}
	//FireCont��0�ŁA���A�X�y�[�X�L�[�Œe����
	else if( CKey::Once(' ')) {
		CBullet *Bullet = new CBullet();
		//���ˈʒu�̐ݒ�
		Bullet->x = x;
		Bullet->y = y;
		//�ړ��̒l��ݒ�
		Bullet->mFx = mFx * 5;
		Bullet->mFy = mFy * 5;
		//�L���ɂ���
		Bullet->mEnabled = true;
		//�v���C���[�̒e��ݒ�
		Bullet->mTag = CRectangle::EPLAYERBULLET;
		FireCount = 10;
	}
	//�W�����v�\��
	if (mJump == 0 && CKey::Push('J')){
		mVj = VJ0;
		mJump++;
	}
	//���x�ɏd�͉����x�v�Z
	mVj -= G;
	y += mVj;
	if (y - h < -300){
		mGameover = true;
	}
	if (CountItem == 0){
		mGameclear = true;
	}

}

void CPlayer::Render() {
	if (mGameover){
		return;
	}
	//Texture.Load("player.tga");
mAniCnt++;
mAniCnt %= ANICNT;
//	CRectangle::Render(Texture, 146 - 16, 146 + 16, 146 + 16, 146 - 16);
if (mAniCnt < ANICNT / 2){
	if (mFx >= 0){
		CRectangle::Render(Texture, 130, 162, 162, 130);
	}
	else
	{
		CRectangle::Render(Texture, 162, 130, 162, 130);
	}
}
else
{
	if (mFx >= 0){
		CRectangle::Render(Texture, 162, 194, 162, 130);
	}
	else
	{
		CRectangle::Render(Texture, 194, 162, 162, 130);
	}
}	
}


void CPlayer::Collision(CRectangle *ri, CRectangle *ry) {
	if (ry->mTag == EBLOCK) {
		int mx, my;
		if (CRectangle::Collision(ry, &mx, &my)) {
			//abs(x) x�̐�Βl�����߂�
			//�ړ��ʂ����Ȃ����������ړ�������
			if (abs(mx) < abs(my)) {
				//Rect��x�����ړ�����
				x += mx;
			}
			else {
				//Rect��y�����ړ�����
				y += my;
				//���n
				mVj = 0;
				if (my>0){
					//�W�����v�\
					mJump = 0;
				}
			}
		}
	}
	else if (ry->mTag == EENEMY)
	{
		int mx, my;
		if (CRectangle::Collision(ry, &mx, &my)) {
			mGameover = true;

		}

	}
	else if (ry->mTag == EBULLETENEMY)
	{
		int mx, my;
		if (CRectangle::Collision(ry, &mx, &my)) {
			mGameover = true;

		}

	}

	else if (ry->mTag == EENEMYBULLET)
	{
		int mx, my;
		if (CRectangle::Collision(ry, &mx, &my)) {
			mGameover = true;

		}

	}
	else if (ry->mTag == EKEYENEMYBULLET)
	{
		int mx, my;
		if (CRectangle::Collision(ry, &mx, &my)) {
			mGameover = true;

		}

	}
	else if (ry->mTag == EKEYBLOCK){
		int mx, my;
		if (CRectangle::Collision(ry, &mx, &my)) {
			//abs(x) x�̐�Βl�����߂�
			//�ړ��ʂ����Ȃ����������ړ�������
			if (abs(mx) < abs(my)) {
				//Rect��x�����ړ�����
				x += mx;
			}
			else {
				//Rect��y�����ړ�����
				y += my;
			}
		}
	}
}
