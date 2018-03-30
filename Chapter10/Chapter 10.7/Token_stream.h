#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include "Token.h"
#include "Roman_int.h"

const char number = '8';    // t.kind == number means that t is a number Token
const char quit = 'q';
const char print = '\n';
const string prompt = "> ";
const string result = "= ";    // used to indicate that what follows is a result
const char name = 'a';         // name token
const char let = 'T';          // declaration token
const char Usqrt = 'R';
const char Upow = 'P';
const char Uconst = 'C';
const char help = 'H';
const string declkey = "let";  // declaration keyword
const string sqrtkey = "sqrt";
const string powkey = "pow";
const string quitkey = "quit";
const string constantkey = "const";
const string helpkey = "help";

class Token_stream
{
public:
	Token_stream();   // make a Token_stream that reads from cin
	Token get();      // get a Token (get() is defined elsewhere)
	void putback(Token t);    // put a Token back
	void ignore(char c);      // discard characters up to and including a c
private:
	bool full;        // is there a Token in the buffer?
	Token buffer;     // here is where we keep a Token put back using putback()
};

#endif
