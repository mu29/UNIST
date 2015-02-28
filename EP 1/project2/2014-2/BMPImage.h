// Class that handles image
#include <string>

using namespace std;

// Structure to save R (red), B (blue), G (green) values of a pixel
struct RGB
{
    unsigned char b, g, r;
};

// Structure to store the DIB Header.
struct DIBHeader
{
    long DIBHeaderSize; // 헤더크기 (40)
    long imageWidth; // 비트맵 가로 크기
    long imageHeight; // 비트맵 세로 크기
    short planes; // 이미지 장수 (1)
    short bitsPerPixel; // 한 픽셀당 비트수
    long compression; // 압축
    long imageSize; // 이미지 자체 크기
    long xPixelsPerMeter; // 한 픽셀당 가로 미터
    long yPixelsPerMeter; // 한 픽셀당 세로 미터
    long colorsInColorTable; // 그림에서 실제 사용되는 색깔
    long importantColorCount; // 중요하게 사용되는 색깔 수
    
    DIBHeader()
    {
        DIBHeaderSize = 40;
        planes = 1;
        bitsPerPixel = 24;
        compression = 0;
        imageSize = 0;
        xPixelsPerMeter = 0;
        yPixelsPerMeter = 0;
        colorsInColorTable = 0;
        importantColorCount = 0;
    }
};

// Class for the BMP image.
// Has image width, height, file header, and the pixel array.
class BMPImage
{
private:
    RGB *img; // pointer to the array of RGB pixels
    int width; // width of the image
    int height; // height of the image
    int totalSize;
    int offBits;
    DIBHeader dibHeader; // DIB Header for BMP image file format
    
public:
    // set the pixel at the specified coordinate to the given value
    void setPixel(int x, int y, RGB val)
    {
        img[y * width + x] = val;
    }
    
    // get a pixel from the given coordinate
    RGB getPixel(int x, int y)
    {
        return img[y * width + x];
    }
    void printHeader(); // prints out the DIB Header
    int getWidth() { return width; } // get the image width
    int getHeight() { return height; } // get the image height
    int getTotalSize() { return totalSize; }
    int getOffBits() { return offBits; }
    
    /************************ Member functions to implement *******************************/
    
    int checkRange(int val);
    
    void read(string imgFileName); // reads a bmp image from the file
    
    void write(string imgFileName); // writes the current image to a bmp file
    
    BMPImage* bw(); // generates a black and white image out of the current image
    
    BMPImage* grayscale(); // generates a grayscale image out of the current image
    
    BMPImage* flip(); // generates a flipped image of the current image
    
    BMPImage* resize(int w, int h); // generates a resized image from the current image
    
    BMPImage* changeIntensity(double ratio); // generates an image with enhanced inteisity, where the intensity is increased or decrased by the given degree.
    
    BMPImage* changeContrast(double ratio); // generates an image with enhanced constrast, where the contrast has been increased or decreased by the given degree.
    
    /**************************************************************************************/
    
    BMPImage();
    BMPImage(int width, int height);
    BMPImage(BMPImage *existingImg);
    BMPImage(string imgFileName);
    ~BMPImage();
};