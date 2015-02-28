#include "BMPImage.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

// Default constructor. Do nothing.
BMPImage::BMPImage()
{
    
}

// Generates an empty image given image width: w and height: h
BMPImage::BMPImage(int w, int h)
{
    width = w;
    height = h;
    img = new RGB[width*height];
    dibHeader.imageWidth = width;
    dibHeader.imageHeight = height;
}

// Generates a duplicate image from the given existing image
BMPImage::BMPImage(BMPImage *existingImg)
{
    width = existingImg->getWidth();
    height = existingImg->getHeight();
    dibHeader = existingImg->dibHeader;
    totalSize = existingImg->getTotalSize();
    offBits = existingImg->getOffBits();
    img = new RGB[width*height];
    memcpy(img, existingImg->img, width*height*sizeof(RGB));
}

// Generates an image by reading in the data from the file
BMPImage::BMPImage(string imgFileName)
{
    read(imgFileName);
}

// Destructor. Free dynamically allocated memory
BMPImage::~BMPImage()
{
    delete[] img;
}

// Use this function to check whether you have read the header correctly.
void BMPImage::printHeader()
{
    cout << "size of dibHeader " << sizeof(dibHeader) << endl;
    cout << "DIB Header Size: " << dibHeader.DIBHeaderSize << endl;
    cout << "DIB Image Width: " << dibHeader.imageWidth << endl;
    cout << "DIB Image Height: " << dibHeader.imageHeight << endl;
    cout << "Planes: " << dibHeader.planes << endl;
    cout << "Bits per pixel: " << dibHeader.bitsPerPixel << endl;
    cout << "Compression: " << dibHeader.compression << endl;
    cout << "Image Size: " << dibHeader.imageSize << endl;
    cout << "x pixels per meter: " << dibHeader.xPixelsPerMeter << endl;
    cout << "y pixels per meter: " << dibHeader.yPixelsPerMeter << endl;
    cout << "Colors in color table: " << dibHeader.colorsInColorTable << endl;
    cout << "Important color count: " << dibHeader.importantColorCount << endl;
    cout << "Total Size: " << totalSize << endl;
    cout << "OffBits: " << offBits << endl << endl;
}

int BMPImage::checkRange(int val)
{
    return val < 0 ? 0 : val > 255 ? 255 : val;
}

void BMPImage::read(string imgFileName)
{
    ifstream rFile;
    rFile.open(imgFileName.c_str(), ios::binary);
    char signature[2];
    rFile.read(reinterpret_cast<char*>(signature), 2);
    
    /* 
     
        비트맵 이미지 구조
    
        2 : 비트맵이란걸 알려줌
        4 : 헤더를 포함한 파일의 전체 크기
        2 : 사용하지 않는 부분
        2 : 사용하지 않는 부분
        4 : 현재 위치로부터 실제 데이터가 존재하는 곳 까지의 거리
        4 : 비트맵 헤더의 크기 (일반적으로 40)
        4 : 이미지 너비 (long)
        4 : 이미지 높이 (long)
        2 : 이미지 장수 (항상 1)
        2 : 컬러 비트수 (2의 n승으로 표시. 256컬러는 8)
        4 : 압축 방식 (안된건 0인듯)
        4 : size of image
        4 : horizontal resolution in pixels per meter (long)
        4 : vertical resolution in pixels per meter (long)
        4 : number of colors in image
        4 : number of important colors in image
     
     */
    
    // 전체 크기를 읽자
    rFile.read((char*)&totalSize, sizeof(totalSize));

    // 사용하지 않는 부분 넘기고
    rFile.seekg(4, ios::cur);
    
    // 현재 위치로부터 얼마나 가야 실제 데이터 나오나
    rFile.read((char*)&offBits, 4);
    
    // DIB 헤더 크기
    rFile.read((char*)&dibHeader.DIBHeaderSize, 4);
    // 이미지 너비
    rFile.read((char*)&dibHeader.imageWidth, 4);
    // 이미지 높이
    rFile.read((char*)&dibHeader.imageHeight, 4);
    // 이미지 장수
    rFile.read((char*)&dibHeader.planes, 2);
    // 컬러 비트수
    rFile.read((char*)&dibHeader.bitsPerPixel, 2);
    // 압축 방식
    rFile.read((char*)&dibHeader.compression, 4);
    // 이미지 크기
    rFile.read((char*)&dibHeader.imageSize, 4);
    // 한 픽셀당 가로 미터
    rFile.read((char*)&dibHeader.xPixelsPerMeter, 4);
    // 한 픽셀당 세로 미터
    rFile.read((char*)&dibHeader.yPixelsPerMeter, 4);
    // 실제 사용되는 색
    rFile.read((char*)&dibHeader.colorsInColorTable, 4);
    // 중요하게 사용되는 색
    rFile.read((char*)&dibHeader.importantColorCount, 4);
    
    // go to the beginning of the pixel array using seekg
    rFile.seekg(offBits, ios::beg);
    
    // dynamically allocate the pixel array (using the pointer variable img), and read pixel data from the file into it.
    
    width = (int) dibHeader.imageWidth;
    height = (int) dibHeader.imageHeight;
    img = new RGB[width*height];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int crd = x + y * width;
            
            rFile.read((char*)&img[crd].b, 1);
            rFile.read((char*)&img[crd].g, 1);
            rFile.read((char*)&img[crd].r, 1);
        }
    }
    
    rFile.close();
}

// write the image to a BMP file
void BMPImage::write(string imgFileName)
{
    ofstream wFile;
    wFile.open(imgFileName.c_str(), ios::binary);
    
    char signature[2] = { 'B', 'M' };
    wFile.write(reinterpret_cast<char*>(signature), 2);
    
    // write image size
    wFile.write((char*)&totalSize, 4);
    
    // write reserved bytes (4 bytes)
    int tmp = 0;
    wFile.write((char*)&tmp, 4);

    // write the pixel array offset
    wFile.write((char*)&offBits, 4);
    
    // write the dibHeader
    wFile.write((char*)&dibHeader.DIBHeaderSize, 4);
    wFile.write((char*)&dibHeader.imageWidth, 4);
    wFile.write((char*)&dibHeader.imageHeight, 4);
    wFile.write((char*)&dibHeader.planes, 2);
    wFile.write((char*)&dibHeader.bitsPerPixel, 2);
    wFile.write((char*)&dibHeader.compression, 4);
    wFile.write((char*)&dibHeader.imageSize, 4);
    wFile.write((char*)&dibHeader.xPixelsPerMeter, 4);
    wFile.write((char*)&dibHeader.yPixelsPerMeter, 4);
    wFile.write((char*)&dibHeader.colorsInColorTable, 4);
    wFile.write((char*)&dibHeader.importantColorCount, 4);
    
    // write the actual pixel array
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int crd = x + y * width;
            
            wFile.write((char*)&img[crd].b, 1);
            wFile.write((char*)&img[crd].g, 1);
            wFile.write((char*)&img[crd].r, 1);
        }
    }
    
    wFile.close();
}

// generates a black & white image from the given image
BMPImage* BMPImage::bw()
{
    BMPImage* gsImg = new BMPImage(this);
    int bwColor;
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            RGB pixel = gsImg->getPixel(x, y);
            int crd = x + y * width;
            bwColor = pixel.r + pixel.g + pixel.b < 383 ? 0 : 255;
            
            gsImg->img[crd].r = bwColor;
            gsImg->img[crd].g = bwColor;
            gsImg->img[crd].b = bwColor;
        }
    }
    return gsImg;
}

// generates a grayscale image from the given image
BMPImage* BMPImage::grayscale()
{
    BMPImage* gsImg = new BMPImage(this);
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            RGB pixel = gsImg->getPixel(x, y);
            int gray = checkRange(0.299 * pixel.r + 0.587 * pixel.g + 0.114 * pixel.b);
            int crd = x + y * width;
            
            gsImg->img[crd].r = gray;
            gsImg->img[crd].g = gray;
            gsImg->img[crd].b = gray;
        }
    }
    return gsImg;
}

// generates a flipped image from the given image
BMPImage* BMPImage::flip()
{
    BMPImage* gsImg = new BMPImage(this);
    RGB temp;
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width / 2; x++) {
            RGB leftPixel = gsImg->getPixel(x, y);
            RGB rightPixel = gsImg->getPixel(width - 1 - x, y);
            temp = rightPixel;
            gsImg->setPixel(width - 1 - x, y, leftPixel);
            gsImg->setPixel(x, y, temp);
        }
    }
    
    return gsImg;
}

// generates a resized image from the given image
BMPImage* BMPImage::resize(int w, int h)
{
    BMPImage* rsImg = new BMPImage(w, h);
    float wRatio = (float) width / w;
    float hRatio = (float) height / h;
    rsImg->dibHeader.imageSize = w * h * 3;
    rsImg->offBits = 54;
    rsImg->totalSize = w * h * 3 + 54;
    rsImg->dibHeader.xPixelsPerMeter = dibHeader.xPixelsPerMeter;
    rsImg->dibHeader.yPixelsPerMeter = dibHeader.yPixelsPerMeter;
    
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            RGB pixel = getPixel(x * wRatio, y * hRatio);
            rsImg->setPixel(x, y, pixel);
        }
    }
    
    return rsImg;
}
// generates an image with enhanced inteisity, where the intensity is increased or decrased by the given degree.
BMPImage* BMPImage::changeIntensity(double ratio)
{
    BMPImage* newImg = new BMPImage(this);
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            RGB pixel = newImg->getPixel(x, y);
            int crd = x + y * width;
            
            newImg->img[crd].r = checkRange(pixel.r + ratio);
            newImg->img[crd].g = checkRange(pixel.g + ratio);
            newImg->img[crd].b = checkRange(pixel.b + ratio);
        }
    }
    
    return newImg;
}

// generates an image with enhanced constrast, where the contrast has been increased or decreased by the given degree.
BMPImage* BMPImage::changeContrast(double ratio)
{
    BMPImage* newImg = new BMPImage(this);
    float f = (259 * (ratio + 255)) / (255 * (259 - ratio));
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            RGB pixel = newImg->getPixel(x, y);
            int crd = x + y * width;
            
            newImg->img[crd].r = checkRange(f * (pixel.r - 128) + 128);
            newImg->img[crd].g = checkRange(f * (pixel.g - 128) + 128);
            newImg->img[crd].b = checkRange(f * (pixel.b - 128) + 128);
        }
    }
    return newImg;
}