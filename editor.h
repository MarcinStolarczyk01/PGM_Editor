#pragma once
#include <vector>
#include "image.h"

class Editor
{
private:
	Image* picture;
protected:
	Editor();
	void SetPicture(Image* _picture);
	void Negative();
	void Reverse();
	void Turn90();
	void Noise(int _noise_lvl);
	void Filter();
	void ChangeProportions(char _choice);
	friend class Repository;
};