#include <log_client.h>
#include <thread>
#include <vector>
#include <iostream>

using namespace std;
int main(int argc, char* argv[])
{
    LogClient client;
    client.init();
    vector<thread> threads;
    int num_threads = 1;
    if (argc > 1){
        cout << "argv[1] " << argv[1] << "\n";
        num_threads = stoi(argv[1]);
    }

    for(int i = 0; i<num_threads; ++i){
        cout << "Spawning thread " << i << "\n";
        threads.push_back(thread([&,i](){
                    for(int j = 0; j<100; ++j){
                    client.info(std::string("Message ") + std::to_string(i));
                    }
                    }));
    }
    for(int i = 0; i<num_threads; ++i){
        threads[i].join();
    }
    client.deinit();
    return 0;
}
