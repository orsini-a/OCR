#include "ImgConverter.h"


ImgConverter::ImgConverter(int x, int y, int imgSubX, int imgSubY)
{
	folder = "";
	sizeX = x;
	sizeY = y;
	divX = imgSubX;
	divY = imgSubY;
	temp = new char[16];
	temp = "temp.bmp";
}


ImgConverter::~ImgConverter()
{
}

void ImgConverter::Greyscale(char *CurrentImg)
{
		Input.ReadFromFile(CurrentImg);
		// convert each pixel to grayscale using RGB->YUV
		for (int j = 0; j < Input.TellHeight(); j++)
		{
			for (int i = 0; i < Input.TellWidth(); i++)
			{
				int Temp = (int)floor(0.299*Input(i, j)->Red +
					0.587*Input(i, j)->Green +
					0.114*Input(i, j)->Blue);
				ebmpBYTE TempBYTE = (ebmpBYTE)Temp;
				Input(i, j)->Red = TempBYTE;
				Input(i, j)->Green = TempBYTE;
				Input(i, j)->Blue = TempBYTE;
			}
		}
		// Create a grayscale color table if necessary
		if (Input.TellBitDepth() < 16)
		{
			CreateGrayscaleColorTable(Input);
		}
		// write the output file
		Input.WriteToFile(temp);
}

float *ImgConverter::parse(char * CurrentImg)
{
	int i = 0;
	int x = 0;
	int y = 0;
	int decalX = 0;
	int decalY = 0;
	float temp;

	temp = 0;
	Input.ReadFromFile(CurrentImg);
	float * ret = new float[sizeX*sizeY];
	while (decalX < sizeX)
	{
		while (x < divX)
		{
			while (decalY < sizeY)
			{
				while (y < divY)
				{
					temp = 0.0f + (int)Input(x + decalX, y + decalY);
					y++;
				}
			}
			decalY = decalY + y;
			y = 0;
			x++;
		}
		decalX = decalX + x;
		x = 0;
		y = 0;
		ret[i + 1] = temp/(x*y);
		temp = 0;
	}
	return ret;
}