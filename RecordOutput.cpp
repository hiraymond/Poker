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

void RecordOutput(double money){
	ofstream fout;
	fout.open("record.txt");

	if (fout.fail()){
    cout << "Error" << endl;
    exit(1);
  }

	fout << money << endl;
	fout.close();
}
