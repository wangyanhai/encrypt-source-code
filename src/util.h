#ifndef __TRANSLATE_UTIL_FILE__
#define __TRANSLATE_UTIL_FILE__
#include <string>
#include <vector>
#include <QtCore>
#include <QStringList>
using namespace std;

string replace_str(string str, const string to_replaced, const string newchars);
string encrypt(string srt);
QStringList getFilesInPathByFilter(QString path, QStringList filters);
string stringAppend(string str1,string str2);

//this function is thread-safe.
void translate(std::istream& new_in, std::ostream& new_out);
void translateFile(QString filename);
#endif