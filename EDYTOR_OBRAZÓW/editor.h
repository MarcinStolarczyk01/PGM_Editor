#pragma once
#include <vector>
#include "image.h"
using namespace std;
class Editor
{
private:
	Image* picture;
public:
	Editor();
	void SetPicture(Image* _picture);
	void Negative();
	void Reverse();
	void Turn90();
	void Noise(int _noiselvl);
	void Filter();
	void ChangeProportions(int _choice);
};