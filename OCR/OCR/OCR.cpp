#include "OCR.h"


OCR::OCR(int imgSubX, int imgSubY, int nbChar, const float error)
{
	this->divX = imgSubX;
	this->divY = imgSubY;
	this->desired_error = error;
	ImgC = new ImgConverter(50, 50, (50 / imgSubX), (50 / imgSubY));
	folder = FOLDER;
	trainFile = TRAINFILE;


	this->numInput = divX * divY;
	this->numOutput = nbChar;
	this->numLayers = 2;
	this->numNeuronsHidden = nbChar;

	neuralNetwork = fann_create_standard(numLayers, numInput,
		numNeuronsHidden, numOutput);

	fann_set_activation_function_hidden(neuralNetwork, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(neuralNetwork, FANN_SIGMOID_SYMMETRIC);

}


OCR::~OCR()
{
}

void OCR::CreateDataFile(std::string newFolder, std::string file)
{
	std::fstream dataFile;
	std::fstream Log;
	std::vector<char*> names;
	
	WIN32_FIND_DATA fd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	TCHAR szDir[64];
	float * temp = new float(divX * divY);
	int i = 0;

	if (trainFile.size() != 0)
		trainFile = file;
	if (newFolder.size() != 0)
		folder = newFolder;
	Log.open("Log.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	Log << "------------------------NEW DATAFILE CREATION--------------------" << std::endl;
	dataFile.open(trainFile, std::fstream::in | std::fstream::out | std::fstream::app);
//	sprintf((char*)szDir, "%s/*.*", folder.c_str());
	Log << "searching training files in folder " << folder.c_str() << " ..." << std::endl;
	StringCchCopy(szDir, MAX_PATH, /*(STRSAFE_LPWSTR)*/folder.c_str());
	StringCchCat(szDir, 64, TEXT("\\*"));
	hFind = FindFirstFile(szDir, &fd);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		Log << "Impossible to find the first file of folder " << folder.c_str() << std::endl;
		return;
	}
	while (::FindNextFile(hFind, &fd));
	{
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				i++;
				Log << i << std::endl;
				names.push_back((char*)fd.cFileName);
			}
	}
	::FindClose(hFind);
	Log << "found " << i << " files." << std::endl;
	Log << "Compiling training files infos in " << trainFile.c_str() << " ..." << std::endl;
	dataFile << names.size() << " " << this->numInput << " " << this->numOutput << std::endl;

	for (auto it = std::begin(names); it != std::end(names); ++it)
	{
		std::cout << "writing to file" << std::endl;
		this->ImgC->Greyscale(*it);
		temp = this->ImgC->parse(*it);
		dataFile << temp << std::endl;
		dataFile << "0" << std::endl;

	}
	Log.close();
	dataFile.close();
}

void OCR::Train()
{
	int max_epochs = 500000;
	int epochs_between_reports = 1000;

	//fann_train_on_data(neuralNetwork, &data, max_epochs,
		//epochs_between_reports, desired_error);
	fann_save(neuralNetwork, "xor_float.net");

	fann_destroy(neuralNetwork);
}

void OCR::ImageAnalizer()
{
	//letter k exemple
	new float[divX*divY] {
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 1, 0, 0, 0,
		0, 0, 1, 1, 0, 0, 0, 0,
		0, 0, 1, 1, 1, 0, 0, 0,
		0, 0, 1, 0, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
	};
}
