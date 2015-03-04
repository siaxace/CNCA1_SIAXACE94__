#include "../include/core/serverCore.h"

void ServerCoreClerk::doClientCommand(string uname , string command){
	stringstream ss;
	string streams;
	int temp;
	ss << command;
	ss >> streams;
	if(streams == "Register"){
		//TODO
	} else if ( streams == "Show"){
		ss << command;
		ss >> streams;
		if(streams=="Candidates"){
			allResults();	
		} else if (streams == "Log"){
			//TODO
		}
	} else if( streams == "vote"){
		ss << command << command;
		ss >> streams >> temp;
		cout<< voteFor(streams,temp) << endl;
	} 
}

string ServerCoreClerk::candidateNames(){
	string result="";
	for(map<int,string>::iterator it = code2Name_Candidate.begin();it!=code2Name_Candidate.end(); ++it){
		result += it->second;
		result += "\n";
	}
	return result;
}

string ServerCoreClerk::voteFor(string uname,int ccode){
	//ex1 time pass
	//ex2 double
	//ex3 invalid code
	time_t now = time(0);
	if( difftime(now,startTime) < 0 )
		return "Please try again later";
	if( difftime(endTime,now) <0 )
		return "The Election is over";
	if( find(contributedClients.begin(),contributedClients.end(), uname ) != contributedClients.end() )
		return "Clients are to vote once...";
	if( code2Name_Candidate.find(ccode) == code2Name_Candidate.end() )
		return "No such Candidate exists";
	contributedClients.push_back(uname);
	++votes[ccode];
	return "Sucksexfully voted";
}

void ServerCoreClerk::allResults(){
	for(map<int,int>::iterator it = votes.begin(); it!=votes.end(); ++it)
		cout<<it->first<<"       "<< code2Name_Candidate[it->first] << "        "<< it->second<<endl;
}

void ServerCoreClerk::setVotingTime(int shour, int smin, int ehour, int emin){
	struct tm* tms;
	struct tm* tme;
	time_t now = time(0);
	tms = localtime(&now);
	tms->tm_hour = shour;
	tms->tm_min = smin;
	startTime = mktime(tms);
	tme = localtime(&now);
	tme->tm_hour = ehour;
	tme->tm_min = emin;
	endTime = mktime(tme);
}

void ServerCoreClerk::extendVotingTime(int ehour, int emin){
	struct tm* tme;
	time_t now = time(0);
	tme = localtime(&now);
	tme->tm_hour = ehour;
	tme->tm_min = emin;
	endTime = mktime(tme);
}

void ServerCoreClerk::addCandidate(string cname, int ccode){
	if(code2Name_Candidate.find(ccode) != code2Name_Candidate.end()){
		cout<<"Error. A Candidate with the specified code already existed\n";
		return;
	}
	votes[ccode] = 0;
	code2Name_Candidate[ccode] = cname;
}
