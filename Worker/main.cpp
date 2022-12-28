#define _CRT_SECURE_NO_WARNINGS
#include "myRDMA.hpp"
#include "tcp.hpp"
#include "time.h"
#include <regex>

#define port 40145
#define num_of_node 3
#define server_ip "192.168.0.106"

string node_domain[num_of_node];
string node[num_of_node] = {server_ip,"192.168.0.107","192.168.0.108"};
string my_ip;

char send_buffer[num_of_node][buf_size];
char recv_buffer[num_of_node][buf_size];

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
    cout << "finish! this pod's ip is " << my_ip << endl;

    /*cout << "Changing domain to ip ..." << endl;
    for(int i = 0 ;i < num_of_node;i++){
        node[i]=tcp.domain_to_ip(node_domain[i]);
        cout << node_domain[i] << " ----> " << node[i] <<endl;
    }
    cout << "Success" << endl;*/

    tcp.connect_tcp(my_ip.c_str(), node, num_of_node, port);

    myRDMA myrdma;
    
    myrdma.set_buffer(send_buffer,recv_buffer,num_of_node-1)
    //myrdma.initialize_rdma_connection(my_ip.c_str(), node, num_of_node, port,send_buffer,recv_buffer);
 
    myrdma.create_rdma_info();
    myrdma.send_info_change_qp();

    cerr << "====================================================" << endl;
    

    myrdma.exit_rdma();
  
    return 0;
}
