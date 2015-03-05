#include "crypto.h"

compelete_kelid::compelete_kelid(string pph, string ppr, string ppu, string pc)
{
	ph=pph;
	pr=ppr;
	pu=ppu;
	cert=pc;
}

compelete_kelid::compelete_kelid(void)
{
	ph=pr=pu=cert="";
}

string wholeAsciiFile(const string &url)
{
	ifstream t(url.c_str());
	return string((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
}

void write2File_entire(const string &url, const string &s)
{
	ofstream out(url.c_str());
	out<<s;
	out.close();
}

void deleteFile(const string &url)
{
	mySystem((string)"rm -f "+url);
}

void convert2Bin(const string &url)
{
	mySystem((string)"xxd -r "+url+" > "+tempAscii_Bin_adr);
	deleteFile(url);
	mySystem((string)"mv "+tempAscii_Bin_adr+" "+url);
}

void convert2Ascii(const string &url)
{
	mySystem((string)"xxd "+url+" > "+tempAscii_Bin_adr);
	deleteFile(url);
	mySystem((string)"mv "+tempAscii_Bin_adr+" "+url);
}

crypto::crypto(void)
{
}

crypto::~crypto(void)
{
}

void crypto::genKey(const string &ph, string &pr, string &pu) const
{
	mySystem((string)"openssl genrsa -aes256 -passout pass:"+ph+" -out "+prkey_adr+" 1024");
	mySystem((string)"openssl rsa -in "+
			prkey_adr+" -passin pass:"+ph+" -out "+pukey_adr+" -outform PEM -pubout");
	convert2Ascii(prkey_adr);
	convert2Ascii(pukey_adr);
	pr=wholeAsciiFile(prkey_adr);
	pu=wholeAsciiFile(pukey_adr);
	deleteFile(prkey_adr);
	deleteFile(pukey_adr);
}

void crypto::encrypt(string &toBCoded, const string &pu) const
{
	write2File_entire(pukey_adr, pu);
	write2File_entire(tempAsciiPlain_adr,toBCoded);
	convert2Bin(pukey_adr);
	mySystem("openssl rsautl -encrypt -inkey "+
			pukey_adr+" -pubin -in "+tempAsciiPlain_adr+" -out "+tempCipher_adr);
	convert2Ascii(tempCipher_adr);
	toBCoded=wholeAsciiFile(tempCipher_adr);
	deleteFile(pukey_adr);
	deleteFile(tempAsciiPlain_adr);
	deleteFile(tempCipher_adr);
}

bool crypto::decrypt(string &toBDecoded, const string &pr, const string &ph) const
{
	int commandresult;
	write2File_entire(prkey_adr,pr);
	write2File_entire(tempCipher_adr, toBDecoded);
	convert2Bin(tempCipher_adr);
	convert2Bin(prkey_adr);
	commandresult=mySystem("openssl rsautl -decrypt -passin pass:"
			+ph+" -inkey "+prkey_adr+" -in "+tempCipher_adr+" -out "+tempAsciiPlain_adr);
	if(commandresult==0)
		toBDecoded=wholeAsciiFile(tempAsciiPlain_adr);
	deleteFile(tempCipher_adr);
	deleteFile(prkey_adr);
	deleteFile(tempAsciiPlain_adr);
	return commandresult==0;
}

string crypto::signedOf(const string &message, const string &pr, const string &ph) const
{
	string result;
	write2File_entire(tempAsciiPlain_adr, message);
	write2File_entire(prkey_adr, pr);
	convert2Bin(prkey_adr);
	mySystem("openssl dgst -sha256 -sign "
			+prkey_adr+" -passin pass:"+ph+" -out "+tempCipher_adr+" "+tempAsciiPlain_adr);
	convert2Ascii(tempCipher_adr);
	result=wholeAsciiFile(tempCipher_adr);
	deleteFile(prkey_adr);
	deleteFile(tempAsciiPlain_adr);
	deleteFile(tempCipher_adr);
	return result;
}

bool crypto::validSign(const string &message, const string &signedMessage, const string &pu) const
{
	int commandresult;
	write2File_entire(tempAsciiPlain_adr, message);
	write2File_entire(pukey_adr, pu);
	write2File_entire(tempCipher_adr, signedMessage);
	convert2Bin(pukey_adr);
	convert2Bin(tempCipher_adr);
	commandresult=mySystem("openssl dgst -sha256 -verify "
			+pukey_adr+" -signature "+tempCipher_adr+" "+tempAsciiPlain_adr);
	deleteFile(pukey_adr);
	deleteFile(tempCipher_adr);
	deleteFile(tempAsciiPlain_adr);
	return (commandresult==0);
}

int mySystem(const string &s)
{
	return system(s.c_str());
}
