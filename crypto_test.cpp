#include "crypto.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]);
int test1(void);
int test2(void);
int test3(void);
int test4(void);
int test5(void);

int main(int argc, char *argv[])
{
	bool result=0;
	if(test1())
		return 1;
	if(test2())
		return 2;
	if(test3())
		return 3;
	if(test4())
		return 4;
	if(test5())
		return 5;
	return 0;
}

int test1(void)
{
	crypto c;
	string ph="salam", pr, pu, message="too many secrets";
	string retrived=message;
	c.genKey(ph, pr, pu);
	c.encrypt(retrived, pu);
	if(retrived==message)
	{
		cerr<<"encryption error\n";
		return 1;
	}
	if(!c.decrypt(retrived, pr, ph))
	{
		cerr<<"decryption error\n";
		return 2;
	}
	return ((retrived==message)?0:3);
}

int test2(void)
{
	crypto c;
	string ph="salam", pr, pu, message="too many secrets";
	string retrived=message;
	c.genKey(ph, pr, pu);
	c.encrypt(retrived, pu);
	if(retrived==message)
	{
		cerr<<"encryption error\n";
		return 1;
	}
	if(!c.decrypt(retrived, pr, ph+"a"))
		return 0;
	cerr<<"wrong pass phrase error\n";
	return 2;
}

int test3(void)
{
	crypto c;
	string ph="salam", pr, pu, message="too many secrets";
	string _signed;
	c.genKey(ph, pr, pu);
	_signed = c.signedOf(message, pr, ph);
	return c.validSign(message, _signed, pu)?0:1;
}

int test4(void)
{
	crypto c;
	string ph="salam", pr, pu, message="too many secrets", other="other";
	string _signed;
	c.genKey(ph, pr, pu);
	_signed = c.signedOf(message, pr, ph);
	return c.validSign(other, _signed, pu)?1:0;
}

int test5(void)
{
	return 0;
}
