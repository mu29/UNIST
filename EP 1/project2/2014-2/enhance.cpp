#include <iostream>
#include <cstdlib>
#include "BMPImage.h"

int main(int argc, char** argv)
{
	if (argc < 2)
		exit(0);

	string filename = argv[1];
	
	BMPImage* img = new BMPImage(filename);
	size_t position = filename.find(".");
	string name = filename.substr(0, position);

	BMPImage* bwImg = img->bw();
	bwImg->write(name + "-bw.bmp");

	BMPImage* gsImg = img->grayscale();
	gsImg->write(name + "-gs.bmp");
	
	BMPImage* fImg = img->flip();
	fImg->write(name + "-flipped.bmp");

	// Extra credit problems

	// 20%
	BMPImage* rsImg = img->resize(img->getWidth() / 2, img->getHeight() / 2);
	rsImg->write(name + "-rs.bmp");

	// 10%
	BMPImage* brighterImg = img->changeIntensity(10);
	brighterImg->write(name + "-brighter.bmp");

	// 30%
	BMPImage* contrastImg = img->changeContrast(10);
	contrastImg->write(name + "-highcontrast.bmp");

	delete img;
	delete bwImg;
	delete gsImg;
	delete fImg;
}
