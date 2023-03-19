#pragma once
#include <iostream>
#include "image.h"
#include "editor.h"
#include <vector>

class Repository
{
private:
	vector<Image> images;
	Editor editor1;
	int chosen_image;//kt�ra fotka
	
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
	bool SkipComment(std::ifstream& _file);
	int FindInLibrary(string _name);
	string SameNamed(string _name, int _samenames);
	string GetNameOrQuit();
	string GetUsersName();
};