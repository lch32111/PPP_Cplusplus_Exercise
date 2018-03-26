#include "Token_stream.h"

Token_stream::Token_stream()
	:full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
	if (full) error("putback() into a full buffer");
	buffer = t;       // copy t to buffer
	full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{
	if (full)  // do we already have a Token ready?
	{      	  // remove token from buffer
		full = false;
		return buffer;
	}

	char ch;
	cin.get(ch);
	while (isspace(ch))
	{
		if (ch == '\n') return Token(print);
		cin.get(ch); // note that cin.get doesn't skip whitespcae
	}
	// cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

	switch (ch)
	{
	case '{':
	case '}':
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '!':
	case '=':
	case ',':
		return Token(ch);        // let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case'8': case '9':
	{
		cin.putback(ch);         // put digit back into the input stream
		double val;
		cin >> val;              // read a floating-point number
		return Token(number, val);
	}
	default:
		if (isalpha(ch))
		{
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch)) || ch == '_') s += ch;
			cin.putback(ch);
			if (s == declkey) return Token(let);
			else if (s == sqrtkey) return Token(Usqrt);
			else if (s == powkey) return Token(Upow);
			else if (s == quitkey) return Token(quit);
			else if (s == constantkey) return Token(Uconst);
			else if (s == helpkey) return Token(help);
			return Token{ name,s };
		}
		error("Bad token!!\n");
	}
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
// c represents the kind of Token
{
	// first look in buffer:
	if (full && c == buffer.kind)
	{
		full = false;
		return;
	}
	full = false;

	// now search input;
	char ch = 0;
	while (cin.get(ch))
		if (ch == c) return;
}