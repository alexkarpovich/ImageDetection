#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include "../headers/HopfieldNetwork.h"

using namespace std;

int IMAGE_WIDTH = 5;
int IMAGE_HEIGHT = 7;

//
// Reads files and fills data sets
//
void readFiles(string* filenames, int fileCount, int imageSize, double **& set) {
	for (int i = 0; i < fileCount; i++) {
		ifstream file(filenames[i].c_str());

		for (int k = 0; k < imageSize; k++) {
			if (!(file >> set[k][i])) {
				break;
			};

			if (set[k][i] == 0) {
				set[k][i] = -1;
			}
		}
	}

}

void printMatrix(double ** matrix, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
		}

		cout << endl;
	}
}

void printVector(double * vector, int m) {
	for (int i = 0; i < m; i++) {
		cout << vector[i] << " ";
	}

	cout << endl;
}

void readFile(string filename, int imageSize, double *& set) {
	ifstream file(filename.c_str());

	for (int k = 0; k < imageSize; k++) {
		if (!(file >> set[k])) {
			break;
		};

		if (set[k] == 0) {
			set[k] = -1;
		}
	}
}

int main() {
	string trainingFiles[] {
		"images/precise5x7/0.txt",
		"images/precise5x7/1.txt",
		"images/precise5x7/2.txt",
		"images/precise5x7/3.txt",
		"images/precise5x7/4.txt",
		"images/precise5x7/5.txt",
		"images/precise5x7/6.txt",
		"images/precise5x7/7.txt",
		"images/precise5x7/8.txt",
		"images/precise5x7/9.txt"
	};

	string testFile = "images/noised5x7/9.txt";

	int imageSize = IMAGE_WIDTH * IMAGE_HEIGHT;
	int trainingCount = sizeof(trainingFiles) / sizeof(string);

	double ** trainingSet = new double*[imageSize];
	for (int k = 0; k < imageSize; k++) {
		trainingSet[k] = new double[trainingCount];
	}

	double * testImage = new double[imageSize];

	readFiles(trainingFiles, trainingCount, imageSize, trainingSet);
	readFile(testFile, imageSize, testImage);

	HopfieldNetwork network(trainingSet, trainingCount, imageSize);
	network.training();
	double * result = network.process(testImage);

	cout << "- Detected image:" << endl;

	for (int i = 0, j = 0; i < imageSize; i++, j++) {
		if (j == IMAGE_WIDTH) {
			cout << endl;
			j = 0;
		}
		cout << (result[i] == 1 ? '#' : '-') << " ";

	}

	return 0;
}
