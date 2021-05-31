#ifndef CMAP_H
#define CMAP_H

#include "CRectangle.h"

extern CTexture Texture;

class CMap : public CRectangle {
public:
	void Render() {
		if (mEnabled) {
			if (mTag==EBLOCK)
			CRectangle::Render(Texture, 48, 95, 191, 144);
			else if (mTag == E0)
				CRectangle::Render(Texture, 48, 95, 1, 40);//îwåi
		}
	}
};

#endif
