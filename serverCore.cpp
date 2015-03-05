#include "serverCore.h"

ServerCoreClerk::ServerCoreClerk(){
	voteS = false;
}

int hourDigitalToInt(string t){
	if(t.size()==4){
		return t[0]-48;
	} else if(t.size()==5){
		return (t[0]-48)*10+t[1]-48;
	}
	return -1;
}

int minDigitalToInt(string t){
	if(t.size()==4){
		return (t[2]-48)*10+(t[3]-48);
	} else if(t.size()==5){
		return (t[3]-48)*10+(t[4]-48);
	}
	return -1;
}

void ServerCoreClerk::doServerCommand(){
	cerr<<"server command entered.\n";
	string comm,comm2;
	int temp,temp2,temp3,temp4;
	cin>>comm;
	if(comm == "Add"){
		cin>>comm;
		if(comm=="Candidate"){
			cin>>comm>>temp;
			addCandidate(comm,temp);
		}
	} else if( comm == "Show" ){
		cin>>comm>>comm2;
		if(comm == "All" && comm2 == "Results"){
			allResults();
		}
	} else if( comm == "Set" ){
		cin>>comm>>comm2;
		if(comm == "Voting" && comm2 == "Time"){
			cin>>comm>>comm2;
			temp = hourDigitalToInt(comm);
			temp2 = minDigitalToInt(comm);
			temp3 = hourDigitalToInt(comm2);
			temp4 = minDigitalToInt(comm2);
			setVotingTime(temp,temp2,temp3,temp4);
		}
	} else if(comm == "Extend"){
		cin>>comm>>comm2;
		if(comm == "Voting" && comm2 == "Time"){
			cin>>comm;
			temp = hourDigitalToInt(comm);
			temp2 = minDigitalToInt(comm);
			extendVotingTime(temp,temp2);			
		}
	}
}
string ServerCoreClerk::doClientCommand(string command){
	stringstream ss;
	string streams;
	int temp;
	ss << command;
	ss >> streams;
	if ( streams == "Show"){
		ss >> streams;
		if(streams=="Candidates"){
			return candidateNames();	
		}
	} else if( streams == "Vote"){
		cerr<<"Voting procedure"<<endl;
		ss >> streams >> temp;
		return voteFor(streams,temp);
	} 
}

string ServerCoreClerk::candidateNames(){
	string result="Candidate Names = \n";
	for(map<int,string>::iterator it = code2Name_Candidate.begin();it!=code2Name_Candidate.end(); ++it){
		stringstream ss;
		ss<<it->first;
		result+=ss.str()+"	";
		result += it->second;
		result += "\n";
	}
	return result;
}

string ServerCoreClerk::voteFor(string uname,int ccode){
	if(!voteS)
		return "Initial voting Time has not been set\n";
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
	cout<<"All Results: \n";
	for(map<int,int>::iterator it = votes.begin(); it!=votes.end(); ++it)
		cout<<it->first<<"       "<< code2Name_Candidate[it->first] << "        "<< it->second<<endl;
}

void ServerCoreClerk::setVotingTime(int shour, int smin, int ehour, int emin){
	voteS = true;
	cout<<"SVT: "<<shour<<" "<<smin<<" "<<ehour<<" "<<emin<<endl;
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
