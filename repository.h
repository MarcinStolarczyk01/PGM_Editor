#pragma once
#include <iostream>
#include <vector>
#include "image.h"
#include "editor.h"


class Repository
{
private:
	vector<Image> images; //library of images
	Editor* my_editor; //
	int chosen_image; //posision of 'active' Image in images vector
	
public:
	Repository();
	~Repository();
	int LoadImage();
	int SaveImage();
	void Menu();
	void AddImage();
	void Edit();
	void ShowLoadedImages();
	void SetActive();
	void DeleteImage();
	void FilePathToName(string* _name_with_path);
	bool SkipComment(std::ifstream& _file, int* _current_posision);
	int FindInLibrary(string _name);
	string SameNamed(string _name, int _samenames);
	string GetNameOrQuit();
	string GetPictureName();
};