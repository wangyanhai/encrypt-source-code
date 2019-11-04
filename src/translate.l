%option noyywrap never-interactive stack 
%option prefix="translate"
%x se_beg_flag
%x se_string_token
%x se_end_flag
se_begin [^1-9a-zA-Z]+"RetSelf"{whitespace}*"("{whitespace}*
se_end   {whitespace}*")"
whitespace   [ \f\r\t\v]
character_string \"{character_representation}*\"
character_representation (\\\")|{common_character_respresentation}
common_character_respresentation [^\"]
hex_digit    [0-9]|[a-f]|[A-F]
se_string   {se_begin}({character_string}({whitespace}|{newline})*)+{se_end}
newline      \n
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QtCore>
using namespace std;
extern string replace_str(string str, const string to_replaced, const string newchars);
extern string encrypt(string srt);
extern string stringAppend(string str1,string str2);;
%}
%%
{se_string}	{ yyless(0); yy_push_state(se_beg_flag); }
<se_beg_flag>{se_begin} {	
		BEGIN se_string_token; 
		string out = replace_str(yytext,"RetSelf","DecryptFromAsc");
		yyout << out;
		all_string_token = "";		
		}
<se_string_token>{character_string} {
		//string encryptdata = encrypt(yytext);
		//yyout<< encryptdata.c_str();
		all_string_token = stringAppend(all_string_token, yytext);
		}
<se_string_token>({whitespace}|{newline})* {}
<se_string_token>{se_end} {
		string encryptdata = encrypt(all_string_token);
		yyout << "\"" << encryptdata << "\"";  
		yy_pop_state(); 
		yyout << yytext;
		}
{newline} { yyout<<"\n";}
. { yyout << yytext[0];}
%%

void translate(std::istream& new_in, std::ostream& new_out) {
  translateFlexLexer flexer;
  flexer.switch_streams(new_in,new_out);
  flexer.yylex();
}
