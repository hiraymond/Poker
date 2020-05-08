#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <bits/stdc++.h>
#include "RecordOutput.h"
#include "RecordInput.h"
#define SPADE "\xE2\x99\xA0"
#define CLUB "\xE2\x99\xA3"
#define HEART "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"
using namespace std;

void RecordInput(double &money, double &pool){
	ifstream fin;
	fin.open("record.txt");

	if (fin.fail()){
    cout << "Error" << endl;
    exit(1);
  }

	string tempS;
	getline(fin, tempS);
	money = stod(tempS);
	getline(fin, tempS);
	pool = stod(tempS);
	fin.close();
}
