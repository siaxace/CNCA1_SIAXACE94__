#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
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
	string inputComm,origin,parse1,parse2;
	int temp;
	vector<string> participants;

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
			int status = connect(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
			//int status2 = connect(fdCA, (struct sockaddr *)&ca_addr, sizeof(ca_addr));
			
			if(status < 0 )
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
				ss >> parse1>>parse2;
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
					int bytes_written = write(fdCA, origin.c_str(), origin.size());
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
