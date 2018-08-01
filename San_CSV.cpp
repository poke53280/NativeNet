

#include "stdafx.h"
#include "San_CSV.h"


#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include <vector>
#include <sstream>

std::vector<std::string> split(const std::string& s, char delimiter)
{
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter))
  {
    tokens.push_back(token);
  }
  return tokens;

}

static const int N_COL = 4992;
static const int N_ROW = 4459;


float get_value(float * fValue, int iRow, int iCol) {

  const int value_location = iRow * N_COL + iCol;

  return fValue[value_location];

}


San_CSV::San_CSV()
{
  static const char* zFile = "C:\\santander_3_data\\train.csv";

  std::ifstream in;

  in.open(zFile);

  assert(in.is_open());

  std::string header;

  std::getline(in, header);

  std::string line;


  std::vector<std::string> lcID;

  int iLine = 0;

  

  float * fValue = new float[N_ROW * N_COL];

 
  while (std::getline(in, line))
  {

    std::vector<std::string> t = split(line, ',');

    lcID.push_back(t[0]);


    for (int idx = 1; idx < t.size(); idx++) {
      float f = std::stof(t[idx]);

      const int value_location = iLine * N_COL + (idx - 1);

      fValue[value_location] = f;


      AI_NOP;
    }

    iLine++;

  }

  
  in.close();

  float f0 = get_value(fValue, 0, 0);

  float f1 = get_value(fValue, 133, 90);

  float f4 = get_value(fValue, 170, 90);

  float f2 = get_value(fValue, 193, 90);

  float r0 = get_value(fValue, 204, 90);




  delete[] fValue;

  fValue = nullptr;


  // ...
}
