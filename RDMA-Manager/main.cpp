#define _CRT_SECURE_NO_WARNINGS
#include "myRDMA.hpp"
#include "tcp.hpp"
#include "time.h"
#include <regex>

#define port 40145
#define num_of_node 3
#define server_ip "192.168.0.100"

string node_domain[num_of_node];
string node[num_of_node] = {server_ip,"192.168.0.107","192.168.0.108"};
string my_ip;

char send_buffer[num_of_node][buf_size];
char recv_buffer[num_of_node][buf_size];

using namespace std;
bool is_server(string ip){
    if(ip == server_ip)
        return true;
    return false;
}

int main(int argc, char* argv[]){
    if(server_ip != node[0]){
        cerr << "node[0] is not server_ip" << endl;
        exit(1);
    }

    TCP tcp;

    cout << "check my ip" << endl;
    my_ip = argv[1];
    cout << "finish! this node's ip is " << my_ip << endl;

    /*cout << "Changing domain to ip ..." << endl;
    for(int i = 0 ;i < num_of_node;i++){
        node[i]=tcp.domain_to_ip(node_domain[i]);
        cout << node_domain[i] << " ----> " << node[i] <<endl;
    }
    cout << "Success" << endl;*/

    tcp.connect_tcp(my_ip.c_str(), node, num_of_node, port);

    map<string, string> read_rdma_info;
    for(int i=0;i<myrdma.connect_num;i++){
        read_rdma_info = tcp.read_rdma_info(myrdma.sock_idx[i]);
        cout << read_rdma_info.find("addr")->first << " " << read_rdma_info.find("addr")->second << endl;
        cout << read_rdma_info.find("len")->first << " " << read_rdma_info.find("len")->second << endl;
        cout << read_rdma_info.find("lkey")->first << " " << read_rdma_info.find("lkey")->second << endl;
        cout << read_rdma_info.find("rkey")->first << " " << read_rdma_info.find("rkey")->second << endl;
        cout << read_rdma_info.find("lid")->first << " " << read_rdma_info.find("lid")->second << endl;
        cout << read_rdma_info.find("qp_num")->first << " " << read_rdma_info.find("qp_num")->second << endl;
    }

    //myRDMA myrdma;
    
    //myrdma.initialize_rdma_connection(my_ip.c_str(), node, num_of_node, port,send_buffer,recv_buffer);
 
    //myrdma.create_rdma_info();
    //myrdma.send_info_change_qp();

    cerr << "====================================================" << endl;
    

    //myrdma.exit_rdma();
  
    return 0;
}
