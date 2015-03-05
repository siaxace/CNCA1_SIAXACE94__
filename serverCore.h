#ifndef __SIAMOZ__serverCore
#define __SIAMOZ__serverCore

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;

class ServerCoreClerk {
	public:
		ServerCoreClerk();
		string doClientCommand(string command);
		void doServerCommand();
	private:
		time_t startTime,endTime;
		map<int,int> votes;
		map<int,string> code2Name_Candidate;
		vector<string> contributedClients;
		string candidateNames();
		string voteFor(string uname,int ccode);
		void allResults();
		void setVotingTime(int shour, int smin, int ehour, int emin);
		void extendVotingTime(int ehour, int emin);
		void addCandidate(string cname, int ccode);
};



#endif
