#include "myRDMA.hpp"
#include "tcp.hpp"

#define port 40145
#define num_of_node 2
#define server_ip "192.168.1.100" //"pod-a.svc-k8s-rdma"

string node_domain[num_of_node] = {server_ip,"pod-b.svc-k8s-rdma"};
string node[num_of_node] = {server_ip, "192.168.1.107"};
string my_ip;

char send_buffer[num_of_node][buf_size];
char recv_buffer[num_of_node][buf_size];

bool is_server(string ip){
    if(ip == server_ip)
        return true;
    return false;
}

int main(int argc, char* argv[]){
    if(server_ip != node_domain[0]){
        cerr << "node[0] is not server_ip" << endl;
        exit(1);
    }
   
    TCP tcp;
    my_ip = argv[1];
    /*cout << "check my ip" << endl;
    my_ip = tcp.check_my_ip();
    cout << "finish! this pod's ip is " <<my_ip << endl;

    cout << "Changing domain to ip ..." << endl;
    for(int i = 0 ;i < num_of_node;i++){
        node[i]=tcp.domain_to_ip(node_domain[i]);
        cout << node_domain[i] << " ----> " << node[i] <<endl;
    }
    cout << "Success" << endl;*/

    myRDMA myrdma;
    
    while(1){
        myrdma.initialize_rdma_connection(my_ip.c_str(), node, num_of_node, port,send_buffer,recv_buffer);
        cerr << myrdma.check_connect() << endl;
        myrdma.create_rdma_info();
        myrdma.send_info_change_qp();

        cerr << "====================================================" << endl;
  
        string msg;
        string opcode = "send"; //send, send_with_imm, write, write_with_imm

        while(1){
            msg = "[ " + my_ip + " ] Hello k8s RDMA";
            myrdma.rdma_comm(opcode, msg);
            for(int i=0;i<num_of_node-1;i++){
                printf("recv_buffer[%d]: %s\n", i, recv_buffer[i]); 
            }
            sleep(2);
        }
        myrdma.exit_rdma();
        cerr << "Connection FAILED... Restarting..." << endl;
    }
    sleep(5);
    while(1){
        cerr << "Success RDMA communication" <<endl;
        sleep(1000);
    }
  
    return 0;
}
