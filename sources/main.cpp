#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include "../headers/HopfieldNetwork.h"

using namespace std;

int IMAGE_WIDTH = 8;
int IMAGE_HEIGHT = 8;

int main() {
	list<string> imageNames;

	imageNames.push_back("images/image1.txt");
	imageNames.push_back("images/image2.txt");
	imageNames.push_back("images/image3.txt");
	imageNames.push_back("images/image4.txt");


	int imageSize = IMAGE_WIDTH * IMAGE_HEIGHT;
	int imageCount = imageNames.size();

	double ** learningSet = new double*[imageCount];
	for (int k = 0; k < imageCount; k++) {
		learningSet[k] = new double[imageSize];
	}

	int j = 0;
	string line;
	list<string>::iterator i;

	for (i = imageNames.begin(); i != imageNames.end(); ++i){
		ifstream imageFile((*i).c_str());

		for (int k = 0; k < imageSize; k++) {
			if (!(imageFile >> learningSet[j][k])) {
				break;
			};
		}

		++j;
	}

	HopfieldNetwork network(learningSet, imageCount, imageSize);

	return 0;
}
