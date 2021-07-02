#include"CDamageBlock.h"
#include"CTexture.h"
#include"CPlayer.h"

extern CTexture Texture;

extern int Score;
extern int CountKeyItem;
extern int KeyItem;
extern int CountKeyBlock;

CDamageBlock::CDamageBlock()
:mFx(1.0f)
, mFy(0.0f)
{
	mTag = EKEYBLOCK;
	w = 50;
	h = 50;
}
void CDamageBlock::Update(){
	if (!mEnabled) return;
	if (CPlayer::spInstance->mGameover){
		Score = 0;
	}
	if (CPlayer::spInstance->mGameclear){
		Score = 0;
	}
}
void CDamageBlock::Render(){
	if (mEnabled){
		CRectangle::Render(Texture, 226 - 1, 239 + 1, 15 + 1, 33 - 1);
	}
}
bool CDamageBlock::Collision(CRectangle &r){
	if (!mEnabled) return false;
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EPLAYER:
			if (KeyItem > 0){

				mEnabled = false;
				Score += 200;
				CountKeyBlock--;
				KeyItem--;
				break;
			}
		}
		return true;
	}
	return false;
}
void CDamageBlock::Collision(CRectangle *i, CRectangle *y){
	Collision(*y);
}