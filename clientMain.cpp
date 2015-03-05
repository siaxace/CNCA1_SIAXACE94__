#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include "crypto.h"

using namespace std;

#define STR_SIZE 20480
const string adminPass = "1234";
const string adminName = "Admin";

void clear_buff(char *x,size_t s){
	for(int i=0;i<s;i++){
		x[i] = 0;
	}
}

int main(int argn, char** args){

	char input_buffer[STR_SIZE];
	clear_buff(input_buffer, STR_SIZE);
	string inputComm,origin,parse1,parse2,parse3;
	int temp;
	vector<string> participants;
	crypto ramznegar;
	map<string,compelete_kelid> keys;
	string capu=wholeAsciiFile(ca_pubkey_adr);

	while(cin>>inputComm)
	{
		//parsing input_buffer
		if(inputComm == "Connect")// don't forget to check reconnect!!
		{
			cin>>inputComm;
			if(inputComm!="Server")
				continue;
			int n, m;//return value of read/write calls
			int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			int fdCA = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
			cin>>temp>>inputComm;
			int port_no = temp;
			struct sockaddr_in serv_addr;
			struct sockaddr_in ca_addr;
			serv_addr.sin_family = AF_INET;
			serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
			serv_addr.sin_port = htons(port_no);
			ca_addr.sin_family = AF_INET;
			ca_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
			ca_addr.sin_port = htons(2021);
			int status2 = connect(fdCA, (struct sockaddr *)&ca_addr, sizeof(ca_addr));
			int status = connect(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
			
			if(status < 0 || status2 < 0 )
			{
				cerr<<"Conention failed\n";
				continue;
			}
			else cerr<<"Sucksexfully Connected\n";
			while(1)
			{
				//read command
				stringstream ss;
				getline(cin,inputComm);
				origin = inputComm;
				ss << inputComm;
				ss >> parse1; //ssn
				ss >>parse2>>parse3;
				if(parse1 == "Show" && parse2=="Log"){
					ss >> parse1 >> parse2;
					if( parse1 == adminName && parse2 == adminPass ){
						for(int i=0;i<participants.size();i++){
							cout<<participants[i]<<endl;
						}
					}
				} else if(parse1 == "Disconnect"){
					ss>>parse1;
					if(parse2 == adminName && parse1 == adminPass){
						cout<<"Disconnected"<<endl;
						break;
					}
				} else if(parse1=="Register")
				{
					cout<<"REGS"<<endl;
					string name,password,pu,pr, cer, rawcer;
					ss>> parse1 >> parse2;
					name = parse2;
					ss>> parse1 >> parse2;
					password = parse1;
					if( parse1 != parse2)
						cout<<"Passwords does not match"<<endl;
					else if( keys.find( name )!= keys.end()){
						cout<<"Name already existed"<<endl;
					} else {
						ramznegar.genKey(password,pr,pu);
						rawcer=name+"\n"+pu;
						int bytes_written = write(fdCA, rawcer.c_str(), rawcer.size());	
						if(bytes_written < 0){
							cout<<"Packet not sent"<<endl;
							continue;
						}
						char res_buff[STR_SIZE];
						clear_buff(res_buff, STR_SIZE);
						int read_status = read(fdCA, res_buff, STR_SIZE);
						cer = res_buff;
						if( !ramznegar.validSign(rawcer,cer,capu) ){
							cout<<"Could not have a valid sign"<<endl;
							continue;
						} else 
							keys[name] = compelete_kelid(password,pr,pu,cer);
						cerr<<"Registration done"<<endl;
					}
				}
				else if(parse1=="Show" && parse2=="Candidates")
				{
					
					//send command for server
					int bytes_written = write(fd, origin.c_str(), origin.size());
					if(bytes_written < 0){
						cerr<<"Packet not sent"<<endl;
						continue;
					}
					string reply;
					//get response from server
					char res_buff[STR_SIZE];
					clear_buff(res_buff, STR_SIZE);
					int read_status = read(fd, res_buff, STR_SIZE);
					reply = res_buff;
					cout<<res_buff<<endl;
				}
				else if(parse1=="Vote")
				{
					stringstream ss2;
					string s1,s2;
					ss2 << origin;
					ss2 >> s1 >> s2;
					if( keys.find( s2 )== keys.end()){
						cout<<"A registeration is required"<<endl;
						continue;	
					}
					stringstream ss;
					int bytes_written = write(fd, origin.c_str(), origin.size());
					if(bytes_written < 0){
						cerr<<"Packet not sent"<<endl;
						continue;
					}
					string reply;
					//get response from server
					char res_buff[STR_SIZE];
					clear_buff(res_buff, STR_SIZE);
					int read_status = read(fd, res_buff, STR_SIZE);
					reply = res_buff;
					ss << origin;
					ss >> parse1 >> parse2;
					if(reply=="0"){
						participants.push_back(parse2);
						cout<<"Your participation has been acknoledged"<<endl;
					} else 
						cout<<res_buff<<endl;
				}
				else
				{
					cerr<<"invalid command\n";
					cout<<parse1<<endl;
				}
			}
			close(fdCA);
			close(fd);
		} else {
			cout<<"A connection must be established\n";
		}
	}

	//free allocated memories
	return 0;
}
