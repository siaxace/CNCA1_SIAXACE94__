#ifndef __siamoz__crypto
#define __siamoz__crypto

#include <iostream>
#include <fstream>
#include <streambuf>
#include <cstdlib>
#include <string>
using namespace std;

const string prkey_adr="siamoz_private_key.pem";
const string pukey_adr="siamoz_public_key.pem";
const string tempCipher_adr="siamoz_cipher.dat";
const string tempAsciiPlain_adr="siamoz_askii_plain.txt";
const string tempAscii_Bin_adr="siamoz_convertingAscii.dat";

class crypto
{
	//pr:	private key
	//pu:	public key
	//ph:	passphrase
	public:
		crypto(void);
		~crypto(void);

		void genKey(const string &ph, string &pr, string &pu) const;

		void encrypt(string &toBCoded, const string &pu) const;
		bool decrypt(string &toBDecoded, const string &pr, const string &ph) const; //returns false if cannot

		string signedOf(const string &message, const string &pr, const string &ph) const;
		bool validSign(const string &message, const string &signedMessage, const string &pu) const;

		bool getShowLog(void) const;
		void setShowLog(bool b);

	protected:


		string shellCommand_suffix(void) const;

		bool showLog;
};

string wholeAsciiFile(const string &url) const;
void write2File_entire(const string &url, const string &s) const;
void deleteFile(const string &url) const;
void convert2Bin(const string &url) const;
void convert2Ascii(const string &url) const;

int mySystem(const string &s);

#endif
