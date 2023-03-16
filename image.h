#pragma once
#include <iostream>
#include <string>
#include <vector>

using std::vector, std::string;
class Image
{
protected:
	string name;
	int width;
	int length;
	int shading;
	vector<vector<int>> pixels;

public:
	friend class Reposistory;
	Image();
	void SetWidth(int _width);
	void SetLenght(int _length);
	void SetShading(int _shading);
	void SetPixels(vector<vector<int>> pix_tmp);
	int GetLenght();
	int GetWidth();
	int GetShading();
	string GetName();
	vector<vector<int>> GetPixels();
};