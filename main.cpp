#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<string>
#include "bitmap.h"

using namespace std;
void ReadFile();
bool ValidatesPic(string);
bool ValidatesSize(string);
vector < vector < Pixel > >  AveragePixel(vector<Bitmap>);

bool firstImageDeclared = false;
unsigned int OriginalRow = 0;
unsigned int OriginalCol = 0;

int main()
{
  ReadFile();
  return 0;
//filename goes into FileMatrix function
//compare all images to see if they meet parameters: if not end program
//call on  AveragePic function 
//save file as "composite-grojas4.bmp"
}
//create function defintion
void  ReadFile()
{
  vector <Bitmap> pictures;
  int fileCount =0;
  string FileName;
  Bitmap image;
  do
  {
    cout << " Enter a BMP file. \n Do not exceed 10 images." << endl;
    cout << "You are on image " << fileCount << endl;
    cin >> FileName;
    if(FileName=="done" || FileName=="Done")
      break;
  
    if (ValidatesPic(FileName) && ValidatesSize(FileName))
    {
      fileCount ++;
      image.open(FileName);
      pictures.push_back(image);
    }
  }
  while(fileCount < 10);
  vector < vector <Pixel> > finalPicture = AveragePixel(pictures);
  Bitmap finalImage;
  finalImage.fromPixelMatrix(finalPicture);
  finalImage.save("composite-grojas4.bmp");

}
bool ValidatesPic(string FileName)
{
  Bitmap image;
  image.open(FileName);
  return image.isImage();

}
//check if its bmp with bool 
bool ValidatesSize(string FileName)
{
  Bitmap image;
  image.open(FileName);
  vector<vector<Pixel> > bmp;
  bmp= image.toPixelMatrix();
  if (firstImageDeclared)
  return (bmp.size() == OriginalRow && bmp[0].size() == OriginalCol);

  OriginalRow = bmp.size();
  OriginalCol = bmp[0].size();
  firstImageDeclared= true;

  return true;
}

//check if picture meets parameters of width and length with a bool
//create function definition for AveragePic
vector < vector<Pixel> >  AveragePixel(vector<Bitmap> pictures)
{
  vector < vector <Pixel> > finalImage;
  finalImage =  pictures[0].toPixelMatrix();
  for (int i = 0; i < finalImage.size();i++)
    for(int j = 0; j < finalImage[0].size();j++)
    {
      finalImage[i][j].red = 0;
      finalImage[i][j].green = 0;
      finalImage[i][j].blue = 0;
    }
  Pixel rgb;
   rgb.red=0;
  rgb.blue=0;
  rgb.green=0;
  for(unsigned int i = 0; i < pictures.size(); i++)
  {
   vector< vector <Pixel > > tempImage =  pictures[i].toPixelMatrix();

   cout << "Image " << i+1 <<  " out of " << pictures.size() << endl;
   for(int row=0; row<tempImage.size(); row++)
   {
     for(int col=0; col<tempImage[0].size(); col++)
     {
       finalImage[row][col].red += tempImage[row][col].red;
       finalImage[row][col].green +=  tempImage[row][col].green;
       finalImage[row][col].blue += tempImage[row][col].blue;
     
     }
   }
  }
  for(int row=0; row<finalImage.size(); row++)
  {
    for(int col=0;col<finalImage[0].size();col++)
    {
      finalImage[row][col].red= finalImage[row][col].red/pictures.size();
      finalImage[row][col].green= finalImage[row][col].green/pictures.size();
      finalImage[row][col].blue /= pictures.size(); 
    }
  }
  return finalImage;

}




//for inside a for loop add individual RGB pixels until toltal then divide by the number of pictures lastly cout progress "image 10 of 25 done" 
