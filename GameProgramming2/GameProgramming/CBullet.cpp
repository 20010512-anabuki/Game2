#include "CBullet.h"
#include "CTexture.h"
#include"CPlayer.h"
//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture Texture;
extern int KeyItem;

//デフォルトコンストラクタ
CBullet::CBullet()
: mFx(0), mFy(0)
{
	mEnabled = false;
	w = 10;	//幅設定
	h = 10;	//高さ設定
}

//更新処理
void CBullet::Update() {
	if (CPlayer::spInstance->mGameover){
		return;
	}
	if (CPlayer::spInstance->mGameclear){
		return;
	}
	//有効な時
	if (mEnabled) {
		//移動
		x += mFx;
		y += mFy;
		//if (x > 1100 || x < -1100 || y > 300 || y < -300)
		//	mEnabled = false;
	}
}

//描画処理
void CBullet::Render() {
	//有効な時
	if (mEnabled) {
		//親の描画メソッドを呼ぶ
		CRectangle::Render(Texture, 192, 207, 112, 97);
	}
}

void CBullet::Collision(CRectangle *i, CRectangle *y) {
	//if (i->mEnabled && y->mEnabled) {
		if (y->mTag == EBLOCK) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}
		}
		//if (i->mTag == EENEMYBULLET && y->mTag == EPLAYER) {
			//if (i->Collision(*y)) {
				//mEnabled = false;
				//return;
			//}

		//}
		if (i->mTag == EPLAYERBULLET && y->mTag == EENEMY) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}
		}
		if (i->mTag == EPLAYERBULLET && y->mTag == EBULLETENEMY) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}
		}
		if (i->mTag == EPLAYERBULLET && y->mTag == EKEYBLOCK) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
		if (i->mTag == EPLAYERBULLET && y->mTag == EKEYENEMY) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
		if (i->mTag == EENEMYBULLET && y->mTag == EKEYBLOCK) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
		if (i->mTag ==  EKEYENEMYBULLET && y->mTag == EPLAYERBULLET) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
		if (i->mTag == EKEYENEMYBULLET && y->mTag == EKEYBLOCK) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}

	}
//}

