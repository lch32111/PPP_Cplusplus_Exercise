#ifndef __STORE_TEMPS_H__
#define __STORE_TEMPS_H__

#include "std_lib_facilities.h"
#include "ch10Source.h"

const char Open_Year_Parenthesis = '{';
const char End_Year_Parenthesis = '}';
const char Open_Month_Parenthesis = '{';
const char End_Month_Parenthesis = '}';
const char Open_Temperature_Parenthesis = '(';
const char End_Temperature_Parenthesis = ')';
const char newline = '\n';
const char tab = '\t';
const char space = ' ';

ostream& store_temp_inFile(ostream& os, const vector<Year>& y, const char mark);
ostream& store_year(ostream& os, const Year& y, const char mark);
ostream& store_month(ostream& os, const Month& m, const char mark);
ostream& store_day(ostream& os, const Day& d, const char mark);
string char_fileprint_representation(const char mark);
string int_fileprint_month(const int& i);
#endif
