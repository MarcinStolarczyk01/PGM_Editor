#include "image.h"

Image::Image() : width(0), length(0), shading(0), name("NO_DATA"){}

void Image::SetWidth(int _width){
	width = _width;
}

void Image::SetLenght(int _length){
	length = _length;
}

void Image::SetShading(int _shading){
	shading = _shading;
}

void Image::SetPixels(vector<vector<int> >pix_tmp){
	pixels = pix_tmp;
}

vector<vector<int>> Image::GetPixels(){
	return pixels;
}

int Image::GetLenght(){return length;}

int Image::GetWidth(){return width;}

int Image::GetShading(){return shading;}

string Image::GetName(){return name;}