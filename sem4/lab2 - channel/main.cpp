#include "channel.hpp"
#include <thread>
#define var auto

using std::thread;

int32_t main() {
    BufferedChannel<int32_t> channel(10);
    var initialSend = thread(&BufferedChannel<int32_t>::send, &channel, 0);
    var initialRecieve = thread(&BufferedChannel<int32_t>::recieve, &channel);
    var close = thread(&BufferedChannel<int32_t>::close, &channel);
    var unverifiedRecieve = thread(&BufferedChannel<int32_t>::recieve, &channel);
    var runtimeError = thread(&BufferedChannel<int32_t>::send, &channel, 0);

    initialSend.join();
    close.join();
    initialRecieve.join();
    unverifiedRecieve.join();

    // runtimeError.join();
    return 0;
}
