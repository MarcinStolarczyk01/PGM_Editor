#pragma once
#include <iostream>
#include <vector>
#include "image.h"
#include "editor.h"


class Repository
{
private:
	vector<Image> images; //library of images
	Editor editor1; //
	int chosen_image; //posision of 'active' Image in images vector
	
public:
	Repository();
	int LoadImage();
	int SaveImage();
	void Menu();
	void AddImage();
	void Edit();
	void ShowLoadedImages();
	void SetActive();
	void DeleteImage();
	bool SkipComment(std::ifstream& _file, int* _current_posision);
	int FindInLibrary(string _name);
	string SameNamed(string _name, int _samenames);
	string GetNameOrQuit();
	string GetPictureName();
};