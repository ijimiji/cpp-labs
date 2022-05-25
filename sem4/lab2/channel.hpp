#pragma once
#include <cinttypes>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <iostream>

#define fn auto
#define var auto

template <class T> class BufferedChannel {
  private:
    int32_t size;
    int32_t capacity;
    std::mutex mutex;
    std::queue<T> buffer;
    std::condition_variable cv;
    bool empty = true;
    bool full = false;
    bool open = true;

  public:
    BufferedChannel(int32_t capacity) : capacity(capacity) { size = 0; }

    void send(T value) {
        std::unique_lock<std::mutex> locker(mutex);
        if (!open) {
            throw std::runtime_error("[BufferedChannel ERROR] attempt to send "
                                     "value to a closed channel");
        }
        cv.wait(locker, [this] { return not full; });
        buffer.push(value);
        std::cout << "Pushed " << value << " to buffer\n";
        ++size;
        empty = false;
        if (size == capacity)
            full = true;
        cv.notify_one();
        locker.unlock();
    }

    std::pair<T, bool> recieve() {
        std::unique_lock<std::mutex> locker(mutex);
        bool verified = true;
        T temp;

        if (open) {
            cv.wait(locker, [this] { return not empty; });
            temp = buffer.front();
            full = false;
            cv.notify_one();
        } else {
            if (empty) {
                verified = false;
            } else {
                temp = buffer.front();
            }
        }

        --size;
        if (size == 0) {
            empty = true;
        }

        std::cout << "Recieved " << (verified ? "verified " : "unverified ")
                  << temp << " from buffer\n";
        locker.unlock();

        return {verified, temp};
    }

    void close() {
        std::unique_lock<std::mutex> locker(mutex);
        open = false;
        locker.unlock();
    }
};
