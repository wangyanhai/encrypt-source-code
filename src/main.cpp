#include <stdio.h>
#include <QApplication>
#include <fstream>
#include <iostream>
#include <sstream>
#include "util.h"
#include <QDir>
#include "translate.h"
using namespace std;

int main(int argc, char* argv[]){
	QApplication a(argc, argv);
	
	if (argc != 2){
		printf("usage:\n\ttranslate <path>\n");
		return 0;
	}

	//test code
	//fstream  afile;
	//afile.open(argv[1], ios::in);
	//translate(afile, cout);
	//end - test code
	QTime t;
	t.start();
	QStringList filters;
	filters << "*.cpp" << "*.h";
	QString path = argv[1];
	QStringList allFiles = getFilesInPathByFilter(path, filters);
	CTranslateManager manager;
	auto it = allFiles.begin();
	while (it != allFiles.end()){
		//cout << qPrintable(*it) << endl;
		QString filename = (*it);
		manager.translateFile(filename);
		++it;
	}

	if (manager.waitForFinished(-1)){
		printf("finished,%d files have been translated! elapse %d ms\n",allFiles.size(),t.elapsed());
	}
	return 0;	
}