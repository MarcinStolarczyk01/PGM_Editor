#include "editor.h"
#include <math.h>
#include <time.h>
using namespace std;

Editor::Editor(){
	picture = nullptr;
	srand(time(NULL));
}

void Editor::SetPicture(Image* _picture){
	picture = _picture;
	}

void Editor::Negative(){
	vector<vector<int>> pix_tmp;
	pix_tmp = picture->GetPixels();

	for (int i = 0; i < picture->GetLenght(); ++i){
		for (int j = 0; j < picture->GetWidth(); ++j){
			pix_tmp[i][j] = picture->GetShading() - pix_tmp[i][j];
		}
	}
	picture->SetPixels(pix_tmp);
}

void Editor::Reverse(){
	vector<vector<int>> pix_tmp;
	pix_tmp = picture->GetPixels();

	for (int i = 0; i < picture->GetLenght(); ++i){
		for (int j = 0; j < picture->GetWidth()/2; ++j){
			int tmp_value = pix_tmp[i][j];
			pix_tmp[i][j] = pix_tmp[i][picture->GetWidth() -1 - j];
			pix_tmp[i][picture->GetWidth() -1 - j] = tmp_value;
		}
	}
	picture->SetPixels(pix_tmp);
}

void Editor::Turn90(){
	vector<vector<int>> pix_original = picture->GetPixels();
	vector<vector<int>> pix_tmp;
	pix_tmp.reserve(picture->GetWidth());

	for (int i = 0; i < picture->GetWidth(); ++i){
		vector<int> tmp;
		tmp.reserve(picture->GetLenght());
		for (int j = picture->GetLenght() - 1; j >= 0; --j){
			tmp.push_back(pix_original[j][i]);
		}
		pix_tmp.push_back(tmp);
	}
	int tmp_width = picture->GetWidth();
	picture->SetWidth(picture->GetLenght());
	picture->SetLenght(tmp_width);
	picture->SetPixels(pix_tmp);
}

void Editor::Noise(int _noise_lvl){
	vector<vector<int>> pix_tmp = picture->GetPixels();
	int lenght, width, shading_tmp;
	int resolution = picture->GetLenght() * picture->GetWidth();
	int max_i = round(_noise_lvl*resolution/100);
	
	for (int i = 0; i < max_i; ++i){
		lenght = rand() % (picture->GetLenght() - 1);
		width = rand() % (picture->GetWidth() - 1);
		shading_tmp = round(0.2*picture->GetShading());
		pix_tmp[lenght][width] += rand() % shading_tmp;
		if (pix_tmp[lenght][width] > picture->GetShading()) pix_tmp[lenght][width] = picture->GetShading();
	}
	picture->SetPixels(pix_tmp);
}

void Editor::Filter(){
	vector<vector<int >> pix_tmp = picture->GetPixels();
	int window_lenght = 3, window_width = 3, value_tmp = 0;
	for (int i = 0; i < picture->GetLenght() - window_lenght; ++i){
		for (int j = 0; j < picture->GetWidth() - window_width; ++j){
			pix_tmp[i+1][j+1] = (pix_tmp[i][j] + pix_tmp[i][j + 1] + pix_tmp[i][j + 2] + pix_tmp[i + 1][j] + pix_tmp[i + 1][j + 1] + pix_tmp[i + 1][j + 2] + pix_tmp[i + 2][j] + pix_tmp[i + 2][j + 1] + pix_tmp[i + 2][j + 2]) / 9;
		}
	}
	picture->SetPixels(pix_tmp);
}

void Editor::ChangeProportions(char _choice){
	vector<vector<int>> pix_tmp;
	vector<vector<int>> pix_original = picture->GetPixels();
	int lenght = 0, width = 0;
	int start_lenght = 0, start_width = 0;

	switch(_choice){

	case '1':{		//4by3
		if (abs((picture->GetLenght() / 3) - (picture->GetWidth() / 4)) < 2){
			throw logic_error("The Image is already 4 by 3.");
		}
		
		if (picture->GetLenght() / 3 > picture->GetWidth() / 4){
			lenght = (picture->GetWidth() / 4) * 3;
			width = picture->GetWidth();
			start_lenght = (picture->GetLenght() - lenght) / 2;
			start_width = 0;
		}
	else if (picture->GetLenght() / 3 < picture->GetWidth() / 4){
			lenght = picture->GetLenght();
			width = (picture->GetLenght() / 3) * 4;
			start_lenght = 0;
			start_width = (picture->GetWidth() - width) / 2;
		}
		break;
	}

	case '2':{//16by9
		if (abs((picture->GetLenght() / 9) - (picture->GetWidth() / 16)) < 2){
			throw logic_error("The Image is already 16 by 9.");
		}

		if (picture->GetLenght() / 9 > picture->GetWidth() / 16){
			lenght = (picture->GetWidth() / 16) * 9;
			width = picture->GetWidth();
			start_lenght = (picture->GetLenght() - lenght) / 2;
			start_width = 0;
		}
		else if (picture->GetLenght() / 9 < picture->GetWidth() / 16){
			lenght = picture->GetLenght();
			width = (picture->GetLenght() / 9) * 16;
			start_lenght = 0;
			start_width = (picture->GetWidth() - width) / 2;
		}
		break;
	}

	case '3':{//square
	
		if (abs((picture->GetLenght()) - (picture->GetWidth())) < 2){
			throw logic_error("The Image is already 1 by 1.\n");
		}

		if (picture->GetLenght() > picture->GetWidth()){
			lenght = picture->GetWidth();
			width = picture->GetWidth();
			start_lenght = (picture->GetLenght() - lenght) / 2;
			start_width = 0;
		}
		else if (picture->GetLenght() < picture->GetWidth()){
			lenght = picture->GetLenght();
			width = picture->GetLenght();
			start_lenght = 0;
			start_width = (picture->GetWidth() - width) / 2;
		}
		break;
	}

	default:{return;}
	}
		
	for (int i = 0; i < lenght; ++i){
		vector<int> row_tmp;
		for (int j = 0; j < width; ++j){
			row_tmp.push_back(pix_original[start_lenght + i][start_width + j]);
		}
		pix_tmp.push_back(row_tmp);
	}

	picture->SetPixels(pix_tmp);
	picture->SetLenght(lenght);
	picture->SetWidth(width);
}
	