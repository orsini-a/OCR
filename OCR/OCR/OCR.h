#pragma once
#include "common.h"
#include "ImgConverter.h"

class OCR
{
	std::string folder; // folder with images
	std::string trainFile;
	std::list<std::string> files;
	std::string data; // generated datafile
	ImgConverter *ImgC;

	// NN infos
	int divX;
	int divY;
	unsigned int maxEpoch;
	unsigned int epochs_between_reports;
	float desired_error;
	struct fann *neuralNetwork;
	unsigned int numInput;
	unsigned int numOutput;
	unsigned int numLayers;
	unsigned int numNeuronsHidden;

	void Train();
	void Recon();
	void ImageAnalizer(); //fill the input float** depending on an image

public:
	OCR(int imgSubX, int imgSubY, int nbChar, const float error);
	~OCR();
	void CreateDataFile(std::string Folder, std::string file);
};

