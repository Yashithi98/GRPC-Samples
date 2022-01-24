#include <string>

#include <grpcpp/grpcpp.h>
#include "ex.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using ex::Test;
using ex::Request;
using ex::Reply;

class ServiceImplementation final : public Test::Service {
    Status sendRequest(
        ServerContext* context, 
        const Request* request, 
        Reply* reply
    ) override {
        int a = request->a();

        if(a%2==0){
            reply->set_result(0);
        }
        else{
            reply->set_result(1);
        }
        return Status::OK;
    } 
};

void Run() {
    std::string address("0.0.0.0:5000");
    ServiceImplementation service;

    ServerBuilder builder;

    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on port: " << address << std::endl;

    server->Wait();
}

int main(int argc, char** argv) {
    Run();

    return 0;
}
