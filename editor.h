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
	void Noise(int _noise_lvl); //it changes random pixels to the lightest value (noised image can be filtered but a lot of data will be lost)
	void Filter();
	void ChangeProportions(char _choice);//formats like 1:1 16:9 and 4:3, the method cuts sides
	friend class Repository; //editor isn't free so we need to buy permission and "making friens" :)
};