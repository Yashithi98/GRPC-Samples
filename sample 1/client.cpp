#include <string>
#include <stdlib.h>
#include <grpcpp/grpcpp.h>
#include "ex.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using ex::Test;
using ex::Request;
using ex::Reply;

class TestClient {
    public:
        TestClient(std::shared_ptr<Channel> channel) : stub_(Test::NewStub(channel)) {}

    int sendRequest(int a) {
        Request request;

        request.set_a(a);

        Reply reply;

        ClientContext context;

        Status status = stub_->sendRequest(&context, request, &reply);

        if(status.ok()){
		if(reply.result()==0){
			std::cout<<"Number generated "<<a<<" is even"<< std::endl;
			return 0;
		}else{
			std::cout<<"Number generated " <<a <<" is odd" <<std::endl;
			return 0;}
        
        } else {
            std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            return -1;
        }
    }

    private:
        std::unique_ptr<Test::Stub> stub_;
};

void Run() {
    std::string address("0.0.0.0:5000");
    TestClient client(
        grpc::CreateChannel(
            address, 
            grpc::InsecureChannelCredentials()
        )
    );

    int response;

    int a = rand();

    response = client.sendRequest(a);
    }

int main(int argc, char* argv[]){
    Run();

    return 0;
}
