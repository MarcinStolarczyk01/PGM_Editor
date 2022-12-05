#pragma once
#include <iostream>
#include "image.h"
#include "editor.h"
#include <vector>

class Reposistory
{
private:
	vector<Image> images;
	Editor editor1;
	int chosen_image;//która fotka
	
public:
	Reposistory();
	int LoadImage();
	int SaveImage();
	void Menu();
	void AddImage();
	void Edit();
	void ShowLoadedImages();
	void SetActive();
	void DeleteImage();
	int FindInLibrary(string _name);
	string SameNamed(string _name, int _samenames);
	string GetNameOrQuit();
	string GetUsersName();
};