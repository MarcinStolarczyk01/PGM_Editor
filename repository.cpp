#include <fstream>
#include <algorithm>
#include "repository.h"

using namespace std;

Repository::Repository(){
	chosen_image = -1;
	images.reserve(20);
	my_editor = new Editor();
}

Repository::~Repository(){
	delete my_editor;
}

int Repository::LoadImage(){
	ifstream file;
	string name;
	name = GetNameOrQuit(); //geting file name from user by console, if users quited retured				// string is 'q'
	if (name == "q") return 0;//user quited so return to menu
		
		file.open(name);
		if (!file.good()){
			file.close();
			throw logic_error("Error while opening the file. No such a file or perrmision is denied.");//to złap
		}
		//if the file was opened succesfuly: 
		else{	
			string file_type;
			try{
				file>>file_type;
			}
			catch (ifstream::failure& e){
				file.close();
				cout<<"INFO: Can't load the file! Wrong type or file is damaged."<<e.what();
			}			
			if (file_type.compare("P2") != 0){ 					//checking if .pgm format is "P2"
				file.close();
				throw logic_error("Incorrect file type!");
			}
			else{	//file opened and type is correct so make new Image and read data into it
				AddImage();
				//cut file's path
				FilePathToName(&name);	//cutting off file path like ../../image.pgm to just a name image.pgm
				//same names?
				int same_named = 1;
			do{
				string name_tmp = SameNamed(name, same_named);	//this loop checks if files don't have the same name
				if (name_tmp == "negative") break;				//if they do it changes them by adding (.)
				else{
					name = name_tmp;
					same_named++;
				}
			} while (1);
				file >> images[images.size() - 1].width >> images[images.size() - 1].length;
				if(!file.good()){
					int current_posision = 2;									//saving information about pisision if the file
					do{
						bool iscomment = SkipComment(file, &current_posision);	//2nd line can have comment inside
						if(!iscomment){
							file.close();
							images.pop_back();
							throw logic_error("Incorrect data in file!");		//error detected or com without '#'
						}
					else file >> images[images.size() - 1].width >> images[images.size() - 1].length;	//read diamentions again
					} while(!file.good());
				}
				file >> images[images.size() - 1].shading;
				images[images.size() - 1].pixels.reserve(images[images.size() - 1].length);	//reserving capacity for vector so we r sure that it wont realocate becouse of overflowing
				for (int k = 0; k < images[images.size() - 1].length; ++k){	//writing pixels data into 2 diamention vector
					vector<int> temp;
					temp.reserve(images[images.size() - 1].width);
					for (int j = 0; j < images[images.size() - 1].width; ++j){
						int tmp_x = 0;
						file >> tmp_x;
						temp.push_back(tmp_x);
					}
					images[images.size() - 1].pixels.push_back(temp);
				}
				file.close();
				images[images.size() - 1].name = name;
			}
		}
		return 0;
}

string Repository::SameNamed(string _name, int _same_named){
	string name_tmp = _name;
	int pic_nr = FindInLibrary(_name), range = 0;

	if(_same_named > 1) range = 1 + _same_named;

	if (pic_nr != -1){
		for (int i = _name.size(); i > _name.size() - 4 - range; --i){
			name_tmp.pop_back();
		}
		name_tmp += "(";
		name_tmp += to_string(_same_named);
		name_tmp += ").pgm";
		return name_tmp;
	}
	else return "negative";
}

void Repository::AddImage(){
	Image PICTURE;
	images.push_back(PICTURE);
}

bool Repository::SkipComment(std::ifstream& _file, int* _current_posision){
	_file.clear();			//reseting flags in order to read pionter posision in the file
	int helpfulint = 0;		
	string sign, bufor;	
	_file.seekg(*_current_posision, std::ios::beg);	//seting posision to place where it was before reading filed
	_file>>sign;
	if(_file.bad()){	//checking some critical errors
		return false;
	}
	else if(sign[0] == '#'){	//if comment is begining with # skip it
			getline(_file, bufor);
			*_current_posision = _file.tellg();
		}
	else return false;			//but if it is not give feedback about damaged file
	return true;
}

void Repository::FilePathToName(string* _name_with_path){
	string name;
	int coto = _name_with_path->size();//do usuniecia
	for(int i = _name_with_path->size() - 1; i >= 0; --i){
		if((*_name_with_path)[i] != '/'){
			name.push_back((*_name_with_path)[i]);
		}
		else{
			reverse(name.begin(), name.end());
			*_name_with_path = name;
		}
	}
}

void Repository::ShowLoadedImages(){
	for (int i = 0; i < images.size(); i++){
		if (i == chosen_image) cout << images[i].GetName() << "*" << endl;
		else cout << images[i].GetName() << endl;
	}
}

int Repository::SaveImage(){
	if (chosen_image < 0){
		throw logic_error("No active image or no images in library.");
	}
	ofstream file;
	file.open(GetPictureName());
	if (!file.good()){
		file.close();
		throw logic_error("Unexpected error while saving: we can't create a file.");
	}
	file << "P2\n";
	file << images[chosen_image].width << " " << images[chosen_image].length << "\n";
	file << images[chosen_image].shading << "\n";
	for (int k = 0; k < images[chosen_image].length; ++k){
		for (int j = 0; j < images[chosen_image].width; ++j){
			file << images[chosen_image].pixels[k][j] << " ";
		}
		file << "\n";
	}
	file.close();
	return 0;
}

void Repository::SetActive(){
	if (images.size() < 1){
		throw logic_error("The Library is empty! Image must be loaded.");
	}
	else if (images.size() == 1){
		chosen_image = 0;
		return;
	}
	else{
		string name = GetNameOrQuit();
		if (name != "q" && name != "Q"){
			if (FindInLibrary(name) != -1) chosen_image = FindInLibrary(name);
			else{
				throw logic_error("No such a image in the Library.");
			}
		}
	}
}

string Repository::GetNameOrQuit(){
	string name;
	while (1){
		cout << "Give the name or press 'q' to exit:" << endl;
		try{
			cin >> name;
			break;
		}
		catch(exception &){
			cout << "INFO: Try again" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (name.compare("q") == 0 || name.compare("Q") == 0) return "q";
		else break;
	}
	return name;
}

int Repository::FindInLibrary(string _name){
	for (int image_NR = 0; image_NR < images.size(); ++image_NR){
		if (_name.compare(images[image_NR].GetName()) == 0){
			return image_NR;
		}
	}
	return -1;
}

void Repository::Menu(){
	char choice;

	while (1){
		cout << "\n\nLibrary: " << endl;
		ShowLoadedImages();
		cout << "\n|--------MENU---------|\n"; 
		cout << "| 1. Set active image |\n";
		cout << "| 2. Load image       |\n";
		cout << "| 3. Edit             |\n"; 
		cout << "| 4. Save             |\n"; 
		cout << "| 5. Delete           |\n";
		cout << "|---------------------|\n"; 
		cout << "| Q - Exit            |\n";
		cout << "|---------------------|\n: ";
		cin >> choice;

		switch (choice){

		case '1':
			try{
				SetActive();
				break;
			}
			catch (logic_error & e){
				cout<<"INFO: "<<e.what();
			}
			break;
		
		case '2':
			try{
				LoadImage();
				break;
			}
			catch(logic_error & e){cout<<"INFO: "<<e.what();}
			catch(...){cout<<"INFO: Unknown exception thrown.";}
			break;

		case '3':
			try{
				Edit();
				break;
			}
			catch (logic_error & e){cout<<"INFO: "<<e.what();}
			break;
		
		case '4':
			try{
			SaveImage();
			break;
			}
			catch (logic_error & e){cout<<"INFO: "<<e.what();}
			break;

		case '5':
			DeleteImage();
			break;
		
		case 'Q':
		case 'q':
		{
			do{
				char choice2;
				cout<<"INFO: Are you sure? All unsaved images will be lost."<<endl;
				cout << "y - YES" << endl;
				cout << "n - NO" << endl;
				cin>>choice2;
				if(choice2 == 'y' || choice2 == 'Y') return;
				else if(choice2 != 'n' && choice2 != 'N') break; 
				else{
					cin.clear();
					cin.ignore(256, '\n');
				}
			}while(1);
			break;
		}
		default:{
			cout << "INFO: Choose right option!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		}
	}
}

string Repository::GetPictureName(){
	string tmp_name;
	while (1){
		cout << "Save the image as: ";
		cin >> tmp_name;
		if (!cin.good()){
			cout << "Try again..." << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		else return tmp_name;
	}
}

void Repository::DeleteImage(){
	if (chosen_image == -1){
		cout << "INFO: Set Image in 'active' mode." << endl;
		return;
	}

	char answer;
	while (1){
		cout << "Are you sure you want to delete: " << images[chosen_image].GetName() << "?" << endl;
		cout << "y - YES" << endl;
		cout << "n - NO" << endl;
		cin >> answer;

		if (answer == 'n' || answer == 'N') return;
		else if (answer == 'y' || answer == 'Y') break;
		else{
			cin.clear();
			cin.ignore(256, '\n');
		}
	}
	if (chosen_image != -1){							
		images.erase(images.begin() + chosen_image);
		chosen_image = -1;								//so now no image is active 
	}
}

void Repository::Edit(){	//secoud menu just for editing images, it has few simple options
	if (chosen_image == -1){
		throw logic_error("To edit the image set it in 'active' mode.");
	}
	if (images.size() == 0){
		throw logic_error("Library is empty. Load a image to modify it.");
	}
	my_editor->SetPicture(&images[chosen_image]);

	char choice;
	while (1){
		cout << "\n\n\n\nEDITE OPTIONS" << endl;
		cout << "1. Negative" << endl;
		cout << "2. Mirror reflection" << endl;
		cout << "3. Turn 90 degrees" << endl;
		cout << "4. Noise" << endl;
		cout << "5. Filtrer noise" << endl;
		cout << "6. Change proportions" << endl;
		cout << "\n7. Exit Editor" << endl;
		cin >> choice;
		switch (choice){
		case '1':{
			my_editor->Negative();
			break;
		}

		case '2':{
			my_editor->Reverse();
			break;
		}

		case '3':{
			my_editor->Turn90();
			break;
		}

		case '4':{
			int noise_lvl;
			while (1){
				cout << "Set noise level(in %): " << endl;
				cin >> noise_lvl;
				if (!cin.good() || noise_lvl < 0 || noise_lvl > 100){
					cin.clear();
					cin.ignore(256, '\n');
					cout<<"INFO: Noise lvl should in 0 - 100 range."<<endl;
				}
				else {
					my_editor->Noise(noise_lvl);
					break;
				}
			}
			break;
		}

		case '5':{
			my_editor->Filter();
			break;
		}

		case '6':{
			char choice1;
			while (1){
				cout << "1. 4 by 3" << endl;
				cout << "2. 16 by 9" << endl;
				cout << "3. Square" << endl;
				cout << "4. Exit" << endl;
				cin >> choice1;
				if (cin.fail() == true || (choice1 != '1' && choice1 != '2' && choice1 != '3' && choice1 != '4')){
					cin.clear();
					cin.ignore(256, '\n');
				}
				else if (choice1 == '4') break;
				else {
					try{
					my_editor->ChangeProportions(choice1);
					break;
					}
					catch (logic_error & e){cout<<"INFO: "<<e.what();}
				}
			}
			break;
		}

		case '7':{
			return;
		}

		default:{
			cout << "INFO: Choose a right option!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			break;
		}
		}
	}
}
