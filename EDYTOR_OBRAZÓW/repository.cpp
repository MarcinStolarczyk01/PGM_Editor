#include "repository.h"
#include <fstream>
using namespace std;

Reposistory::Reposistory()
{
	chosen_image = -1;
}

int Reposistory::LoadImage()
{
	ifstream file;
	string name;
	name = GetNameOrQuit();
	if (name == "q") return 0;

		//mamy ju¿ nazwê pliku
		file.open(name);
		if (!file.good())
		{
			cout << "Ohh...We cant find such a file\n";
			file.close();
			system("pause");
			return 2;//b³¹d typu 2
		}
		else
		{
			int samenames = 1;
			do
			{
				string name_tmp = SameNamed(name, samenames);
				if (name_tmp == "negative")
				{
					break;
				}
				else
				{
					name = name_tmp;
					samenames++;
				}
			} while (1);
			string type;
			getline(file, type);
			if (type.compare("P2") != 0) //czy to dobry format?
			{
				cout << "WRONG FILE TYPE!" << endl;
				system("pause");
				return 1;//b³¹d typu 1
			}
			else //uda³o siê, wiêc czytaj z pliku
			{
				AddImage();
				images[images.size() - 1].name = name;
				file >> images[images.size() - 1].width >> images[images.size() - 1].length;
				file >> images[images.size() - 1].shading;
				for (int k = 0; k < images[images.size() - 1].length; k++)
				{
					vector<int> temp;
					for (int j = 0; j < images[images.size() - 1].width; j++)
					{
						int tmp_x = 0;
						file >> tmp_x;
						temp.push_back(tmp_x);
					}
					images[images.size() - 1].pixels.push_back(temp);
				}
			}
		}

		return 0;
}

string Reposistory::SameNamed(string _name, int _samenames)
{
	string name_tmp = _name;
	int pic_nr = FindInLibrary(_name), range = 0;
	if(_samenames > 1) range = 1 + _samenames;
	if (pic_nr != -1)
	{
		for (int i = _name.size(); i > _name.size() - 4 - range; i--)
		{
			name_tmp.pop_back();
		}
		name_tmp += "(";
		for (int i = 0; i < _samenames; i++)
		{
			name_tmp.push_back('.');
		}
		name_tmp += ").pgm";
		return name_tmp;
	}
	else return "negative";
}

void Reposistory::AddImage()
{
	Image PICTURE;
	images.push_back(PICTURE);
}

void Reposistory::ShowLoadedImages()
{
	for (int i = 0; i < images.size(); i++)
	{
		if (i == chosen_image) cout << images[i].GetName() << "*" << endl;
		else cout << images[i].GetName() << endl;
	}
}

int Reposistory::SaveImage()
{
	if (chosen_image < 0)
	{
		cout << "No active image or no images in library" << endl;
		system("pause");
		return 2; //tu powinno rzucaæ wyj¹tek
	}
	ofstream file1;
	file1.open(GetUsersName(), ios_base::out, ios_base::binary);
	if (!file1.good())
	{
		cout << "Ups...Saving Failed\n";
		file1.close();
		system("pause");
		return 2;//b³¹d typu 2
	}
	file1 << "P2\n";
	file1 << images[chosen_image].width << " " << images[chosen_image].length << "\n";
	file1 << images[chosen_image].shading << "\n";
	for (int k = 0; k < images[chosen_image].length; k++)
	{
		for (int j = 0; j < images[chosen_image].width; j++)
		{
			file1 << images[chosen_image].pixels[k][j] << " ";
		}
		file1 << "\n";
	}
	file1.close();
	return 0;
}

void Reposistory::SetActive()
{
	if (images.size() < 1) return;//tu powinno rzucaæ wyj¹tek
	else if (images.size() == 1)
	{
		chosen_image = 0;
		return;
	}
	string name = GetNameOrQuit();
	if (name != "q")
	{
		if (FindInLibrary(name) != -1) chosen_image = FindInLibrary(name);
		else
		{
			cout << "No such a file in the library!" << endl;
			system("pause");
		}
	}
}

int Reposistory::FindInLibrary(string _name)
{
	bool found = false;

	for (int image_NR = 0; image_NR < images.size(); image_NR++)
	{
		if (_name.compare(images[image_NR].GetName()) == 0)
		{
			found = true;
			return image_NR;
		}
	}
	return -1;
}

void Reposistory::Menu()
{
	char choice;
	while (1)
	{
		system("cls");
		cout << "Library: " << endl;
		ShowLoadedImages();
		cout << "\n____MENU____" << endl;
		cout << "1. Set active image" << endl;
		cout << "2. Load image" << endl;
		cout << "3. Edit" << endl;
		cout << "4. Save" << endl;
		cout << "5. Delete" << endl;//zbugowane
		cout << "6. Exit" << endl;
		//pomijanie komentzrzy i odszumianie
		cin >> choice;

		switch (choice)
		{

		case '1':
		{
			SetActive();
			break;
		}
		case '2':
		{
			LoadImage();
			break;
		}
		case '3':
		{
			Edit();
			break;
		}
		case '4':
		{
			SaveImage();
			break;
		}
		case '5':
		{
			DeleteImage();
			break;
		}
		case '6':
		{
			return;
		}
		default:
		{
			cout << "Choose the right option!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		}
	}
}

string Reposistory::GetUsersName()
{
	string tmp_name;
	while (1)
	{
		cout << "Save the image as: ";
		cin >> tmp_name;
		if (cin.fail() == true)
		{
			cout << "Try again" << endl;
			cin.clear();
			cin.ignore(256, '/n');
		}
		else return tmp_name;
	}
}

string Reposistory::GetNameOrQuit()
{
	string name;
	while (1)
	{
		cout << "Give the name or press '1' to exit:" << endl;
		cin >> name;
		if (name.compare("1") == 0) return "q";//pownien byæ wyj¹tek
		if (cin.fail() == true)
		{
			cout << "Try again" << endl;
			cin.clear();
			cin.ignore(256, '/n');
		}
		else return name;
	}
}

void Reposistory::DeleteImage()
{
	if (chosen_image == -1)
	{
		cout << "Set Image as 'active'" << endl;
		system("pause");
		return;
	}
	char answer;
	while (1)
	{
		system("cls");
		cout << "Are you sure you want to delete: " << images[chosen_image].GetName() << "?" << endl;
		cout << "y - YES" << endl;
		cout << "n - NO" << endl;
		cin >> answer;

		if (answer == 'n') return;
		else if (answer == 'y') break;
		else
		{
			cin.clear();
			cin.ignore(256, '\n');
		}
	}

	if (chosen_image != -1)
	{
		images.erase(images.begin() + chosen_image);
		chosen_image = -1;
	}
}

void Reposistory::Edit()
{
	if (chosen_image == -1)
	{
		cout << "Set Image as 'active'" << endl;
		system("pause");
		return; //tu powinno rzucaæ wyj¹tek
	}
	editor1.SetPicture(&images[chosen_image]);
	char choice;
	while (1)
	{
		system("cls");
		cout << "OPTIONS" << endl;
		cout << "1. Negative" << endl;
		cout << "2. Mirror reflection" << endl;
		cout << "3. Turn 90 degrees" << endl;
		cout << "4. Noise" << endl;
		cout << "5. Filtrer noise" << endl;
		cout << "6. Change proportions" << endl;
		cout << "7. Exit Editor" << endl;
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			editor1.Negative();
			break;
		}

		case '2':
		{
			editor1.Reverse();
			break;
		}
		case '3':
		{
			editor1.Turn90();
			break;
		}

		case '4':
		{
			int noiselvl;
			while (1)
			{
				cout << "Set noise level(in %)" << endl;
				cin >> noiselvl;
				if (cin.good() == false || noiselvl < 0 || noiselvl > 100)
				{
					cin.clear();
					cin.ignore(256, '\n');
				}
				else break;
			}
			editor1.Noise(noiselvl);
			break;
		}

		case '5':
		{
			editor1.Filter();
			break;
		}

		case '6':
		{
			char choice1;
			while (1)
			{
				cout << "1. 4 by 3" << endl;
				cout << "2. 16 by 9" << endl;
				cout << "3. Square" << endl;
				cout << "4. Exit" << endl;
				cin >> choice1;
				if (cin.fail() == true || (choice1 != '1' && choice1 != '2' && choice1 != '3' && choice1 != '4'))
				{
					cin.clear();
					cin.ignore(256, '\n');
				}
				else if (choice1 == '4') break;
				else 
				{
					editor1.ChangeProportions(choice1);
					break;
				}
			}
			break;
		}
		case '7':
		{
			return;
		}

		default:
		{
			cout << "Choose the right option!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			break;
		}
		}
	}
	system("cls");
}