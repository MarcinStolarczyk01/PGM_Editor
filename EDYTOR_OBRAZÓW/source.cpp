#include <iostream>
#include "repository.h"
using namespace std;
int main()
{
 /*  Reposistory repos1;
   repos1.Menu();*/

	int array[4] = { 0, 1, 2, 100};
	vector<int> wektor(array,array + 4);

	vector<int>::iterator found = find(wektor.begin(), wektor.end(), 100);
	
	cout << *found << endl;
	return 0;
}


