#include "util.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <QtCore>

string replace_str(string str, const string to_replaced, const string newchars)     
{
	for(string::size_type pos(0); pos != string::npos; pos += newchars.length())   
	{
		pos = str.find(to_replaced,pos);
		if(pos!=string::npos)     
			str.replace(pos,to_replaced.length(),newchars);     
		else  
			break;  
	}     
	return   str;     
}

QStringList getFilesInPathByFilter(QString path, QStringList filters){
	QStringList allFiles;

	QDir dir(path);
	if (!dir.exists(path)){
		return allFiles;
	}
	QString directory = dir.absolutePath();
	QFileInfoList allentry = dir.entryInfoList(filters);
	auto it = allentry.begin();
	while (it != allentry.end()){
		QString filename = (*it).absoluteFilePath();
		allFiles << filename;
		++it;
	}

	QFileInfoList allDirEntry = dir.entryInfoList(QDir::AllDirs|QDir::NoDot|QDir::NoDotDot);
	auto it2 = allDirEntry.begin();
	while (it2 != allDirEntry.end()){
		QString subpath = (*it2).absoluteFilePath();
		allFiles << getFilesInPathByFilter(subpath,filters);
		++it2;
	}

	return allFiles;
}

void translateFile(QString filename){
	string strfile(qPrintable(filename));
	fstream new_in;
	new_in.open(strfile,ios_base::in);
	stringstream sstring;
	sstring << strfile ;
	sstring << ".bak";
	string file_back = sstring.str();
	fstream new_out;
	new_out.open(file_back,ios_base::out);
	translate(new_in,new_out);
	new_in.close();
	new_out.close();

	//remove old file
	QFile::remove(filename);
	//rename file
	QFile::rename(QString(file_back.c_str()),filename);
	return ;
}
string encrypt(string srt){
	QByteArray raw(srt.c_str());
	QByteArray base64 = raw.toBase64();
	return base64.data();
}

string stringAppend(string str1,string str2){
	str2 = replace_str(str2,"\\\n","");
	str2 = str2.substr(1,str2.size()-2);
	return str1.append(str2);
}