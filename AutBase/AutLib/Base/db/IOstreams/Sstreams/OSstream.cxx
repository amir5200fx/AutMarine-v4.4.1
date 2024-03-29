#include <OSstream.hxx>

#include <token.hxx>
#include <error.hxx>

AutLib::Ostream& AutLib::OSstream::write(const token&)
{
	return *this;
}


AutLib::Ostream& AutLib::OSstream::write(const char c)
{
	os_ << c;
	if (c == token::NL)
	{
		lineNumber_++;
	}
	setState(os_.rdstate());
	return *this;
}


AutLib::Ostream& AutLib::OSstream::write(const char* str)
{
	lineNumber_ += (label)string(str).count(token::NL);
	os_ << str;
	setState(os_.rdstate());
	return *this;
}


AutLib::Ostream& AutLib::OSstream::write(const word& str)
{
	os_ << str;
	setState(os_.rdstate());
	return *this;
}


AutLib::Ostream& AutLib::OSstream::write(const string& str)
{
	os_ << token::BEGIN_STRING;

	int backslash = 0;
	for (string::const_iterator iter = str.begin(); iter != str.end(); ++iter)
	{
		char c = *iter;

		if (c == '\\')
		{
			backslash++;
			// suppress output until we know if other characters follow
			continue;
		}
		else if (c == token::NL)
		{
			lineNumber_++;
			backslash++;    // backslash escape for newline
		}
		else if (c == token::END_STRING)
		{
			backslash++;    // backslash escape for quote
		}

		// output pending backslashes
		while (backslash)
		{
			os_ << '\\';
			backslash--;
		}

		os_ << c;
	}

	// silently drop any trailing backslashes
	// they would otherwise appear like an escaped end-quote

	os_ << token::END_STRING;

	setState(os_.rdstate());
	return *this;
}


AutLib::Ostream& AutLib::OSstream::writeQuoted
(
	const std::string& str,
	const bool quoted
)
{
	if (quoted)
	{
		os_ << token::BEGIN_STRING;

		int backslash = 0;
		for
			(
				string::const_iterator iter = str.begin();
				iter != str.end();
				++iter
				)
		{
			char c = *iter;

			if (c == '\\')
			{
				backslash++;
				// suppress output until we know if other characters follow
				continue;
			}
			else if (c == token::NL)
			{
				lineNumber_++;
				backslash++;    // backslash escape for newline
			}
			else if (c == token::END_STRING)
			{
				backslash++;    // backslash escape for quote
			}

			// output pending backslashes
			while (backslash)
			{
				os_ << '\\';
				backslash--;
			}

			os_ << c;
		}

		// silently drop any trailing backslashes
		// they would otherwise appear like an escaped end-quote
		os_ << token::END_STRING;
	}
	else
	{
		// output unquoted string, only advance line number on newline
		lineNumber_ += (label)string(str).count(token::NL);
		os_ << str;
	}

	setState(os_.rdstate());
	return *this;
}


AutLib::Ostream& AutLib::OSstream::write(const label val)
{
	os_ << val;
	setState(os_.rdstate());
	return *this;
}


AutLib::Ostream& AutLib::OSstream::write(const floatScalar val)
{
	os_ << val;
	setState(os_.rdstate());
	return *this;
}


AutLib::Ostream& AutLib::OSstream::write(const doubleScalar val)
{
	os_ << val;
	setState(os_.rdstate());
	return *this;
}


AutLib::Ostream& AutLib::OSstream::write(const longDoubleScalar val)
{
	os_ << val;
	setState(os_.rdstate());
	return *this;
}


AutLib::Ostream& AutLib::OSstream::write(const char* buf, std::streamsize count)
{
	if (format() != BINARY)
	{
		FatalIOErrorIn("Ostream::write(const char*, std::streamsize)", *this)
			<< "stream format not binary"
			<< abort(FatalIOError);
	}

	os_ << token::BEGIN_LIST;
	os_.write(buf, count);
	os_ << token::END_LIST;

	setState(os_.rdstate());

	return *this;
}


void AutLib::OSstream::indent()
{
	for (unsigned short i = 0; i < indentLevel_*indentSize_; i++)
	{
		os_ << ' ';
	}
}


void AutLib::OSstream::flush()
{
	os_.flush();
}


// Add carriage return and flush stream
void AutLib::OSstream::endl()
{
	write('\n');
	os_.flush();
}


// Get flags of output stream
std::ios_base::fmtflags AutLib::OSstream::flags() const
{
	return os_.flags();
}


// Set flags of output stream
std::ios_base::fmtflags AutLib::OSstream::flags(const ios_base::fmtflags f)
{
	return os_.flags(f);
}

// Get width of output field
int AutLib::OSstream::width() const
{
	return (int)os_.width();
}

// Set width of output field (and return old width)
int AutLib::OSstream::width(const int w)
{
	return (int)os_.width(w);
}

// Get precision of output field
int AutLib::OSstream::precision() const
{
	return (int)os_.precision();
}

// Set precision of output field (and return old precision)
int AutLib::OSstream::precision(const int p)
{
	return (int)os_.precision(p);
}