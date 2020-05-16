#include <iostream>
#include <time.h>
#include <cmath>
#include <fstream>
#include <vector>
#include "matplotlibcpp.h"

#define TIMEPOINTS 256
#define NUM 14
#define FREQU 2000

using namespace std;

namespace plt = matplotlibcpp;

float generator (int);
void getValuesX(float*, int = 2000);     //get one signsl point based on sum of NUM=14 harmonic signals
float analysisExpectedValue(float*);  //avarage value of signal points
float analysisVariance(float*, float);  //variance of signal points
void printValueX(float*);
void storeTXT(float*); //store sigmnai into 1.txt file (", ")
void task(double*, float*); //execution time of generating signals with points 1-2000

int main(){
srand (time(NULL));
float valueX [2000] = {0};
float* pValueX = & valueX[0];

double time[2000] = {0};
double* ptime = &time[0];

//task(ptime,pValueX);
getValuesX(pValueX);

// vector <double> u(2000);
// for(int i = 0 ; i < 2000; i++)
//   u[i] = time[i];
//
// plt::xkcd();
// plt::plot(u);
// plt::show();
// srand (time(NULL));

//getValuesX(pValueX);
// //printValueX(pValueX);

float expectedValue = analysisExpectedValue(pValueX);
cout << "Expected value: " << expectedValue << endl;

float variance = analysisVariance(pValueX, expectedValue);
cout << "Variance: " << variance << endl;

float tmp = sqrt (variance);
cout <<"Sigma: " << sqrt(variance) << endl;
//printValueX(pValueX);
//storeTXT(pValueX);

vector <double> u(256);
for(int i = 0 ; i < TIMEPOINTS; i++)
  u[i] = valueX[i];

plt::xkcd();
plt::plot(u);
plt::show();
return 0;
}

float generator (int t){
  float result = 0;
  for(int i = 0; i < NUM; i++)
    result += rand() * sin(FREQU * t + rand() * 6.28);
  return result;
}

void getValuesX(float* pValueX, int n){
  for (int i = 0; i < n; i++)
    *(pValueX + i) = generator(i);
}


float analysisExpectedValue(float* pValueX){
  float expectedValue = 0;
  for (int i = 0; i < TIMEPOINTS; i++)
      expectedValue += *(pValueX + i);
  expectedValue /= TIMEPOINTS;
  return expectedValue;
}


float analysisVariance(float* pValueX, float expectedValue){
  float variance = 0;
  float tmp;
  for (int i = 0; i < TIMEPOINTS; i++){
    tmp = *(pValueX + i) - expectedValue;
    variance += tmp * tmp;
  }
  variance /= TIMEPOINTS;
  return variance;
}


void printValueX (float* pValueX){
  for(int i = 0; i < TIMEPOINTS; i++)
    cout << *(pValueX + i) << endl;
}


void storeTXT(float* pValueX){
ofstream file ("1.txt", ios::out);
for (int i = 0; i < TIMEPOINTS; i++)
  file << *(pValueX + i)<< ", ";
file.close();

}

void task (double* time, float* parray){
  for (int i = 0; i < 2000; i++){
    clock_t start = clock();
    getValuesX(parray, i);
    clock_t end = clock();
    *(time + i) = (double)(end - start)/CLOCKS_PER_SEC;
  }
}
