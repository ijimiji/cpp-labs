#include <sstream>
#include <stdint.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <functional>

using std::vector;
using std::wstring;
using std::wcout;
using std::function;;

class Pipe {
  public:
    Pipe(wstring input, wstring output, wstring name,
         function<vector<int32_t>(vector<int32_t>)> f) {
        HANDLE pipe;
        wcout << "Creating an instance of a named pipe " << name << "\n";

        vector<int32_t> inputData;
        vector<int32_t> outputData;

        // Read input
        {
            wcout << name << " connecting to pipe " << input << "\n";
            HANDLE pipe =
                CreateFileW((L"\\\\.\\pipe\\" + input).c_str(), GENERIC_READ,
                            FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (pipe == INVALID_HANDLE_VALUE) {
                wcout << name << " failed to connect to pipe " << input << "\n";
                return;
            }
            wcout << name << " reading data from pipe " << input << "\n";
            wchar_t buffer[128];
            DWORD numBytesRead = 0;
            BOOL result = ReadFile(pipe, buffer, 127 * sizeof(wchar_t),
                                   &numBytesRead, NULL);
            if (result) {
                buffer[numBytesRead / sizeof(wchar_t)] = '\0';
                wcout << "Number of bytes read: " << numBytesRead << "\n";
                wcout << "Message: " << buffer << "\n";
            } else {
                wcout << "Failed to read data from the pipe."
                      << "\n";
            }
            CloseHandle(pipe);

            std::wistringstream ws(buffer);
            int32_t temp;
            while (ws >> temp) {
                inputData.push_back(temp);
            }

            wcout << "Done."
                  << "\n";
        }

        outputData = f(inputData);
        if (output == L"stdout"){
            wcout << outputData[0] << "\n";
        } else {
            // Write output
            wcout << "Creating an instance of a named pipe..."
                  << "\n";
            // Create a pipe to send data
            HANDLE pipe = CreateNamedPipeW(
                (L"\\\\.\\pipe\\" + output).c_str(), // name of the pipe
                PIPE_ACCESS_OUTBOUND,                // 1-way pipe -- send only
                PIPE_TYPE_BYTE, // send data as a byte stream
                1,              // only allow 1 instance of this pipe
                0,              // no outbound buffer
                0,              // no inbound buffer
                0,              // use default wait time
                NULL            // use default security attributes
            );
            if (pipe == NULL || pipe == INVALID_HANDLE_VALUE) {
                wcout << "Failed to create outbound pipe instance.";
                // look up error code here using GetLastError()
                return;
            }
            wcout << "Waiting for a client to connect to the pipe..."
                  << "\n";
            // This call blocks until a client process connects to the pipe
            BOOL result = ConnectNamedPipe(pipe, NULL);
            if (!result) {
                wcout << "Failed to make connection on named pipe."
                      << "\n";
                CloseHandle(pipe);
                return;
            }
            wcout << "Sending data to pipe..."
                  << "\n";

            wstring data;
            for (auto number : outputData) {
                data += (std::to_wstring(number) + L" ");
            }

            DWORD numBytesWritten = 0;
            result = WriteFile(
                pipe,         // handle to our outbound pipe
                data.c_str(), // data to send
                wcslen(data.c_str()) *
                    sizeof(wchar_t), // length of data to send (bytes)
                &numBytesWritten,    // will store actual amount of data sent
                NULL                 // not using overlapped IO
            );
            if (result) {
                wcout << "Number of bytes sent: " << numBytesWritten << "\n";
            } else {
                wcout << "Failed to send data."
                      << "\n";
                // look up error code here using GetLastError()
            }
            // Close the pipe (automatically disconnects client too)
            CloseHandle(pipe);
            wcout << "Done."
                  << "\n";
        }
    }
};