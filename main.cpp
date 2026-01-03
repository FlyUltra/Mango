#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32")
#endif


#include <iostream>
#include <thread>
#include <chrono>

#include "mson/parser/MsonParser.h"
#include "mson/value/MsonValue.h"
#include "mson/encoder/MsonBinaryEncoder.h"

#include "mucp/server/MucpServer.h"
#include "mucp/client/MucpClient.h"
#include "mucp/type/MucpType.h"

int main() {

#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        std::cout << "WSAStartup failed\n";
        return 1;
    }
#endif

    // ===============================
    //         SERVER THREAD
    // ===============================
    std::thread serverThread([]() {
        MucpServer server(5555);

        server.start([](MucpTcpSocket&, const MucpPacket& pkt) {
            std::cout << "\n=== MUCP SERVER RECEIVED ===\n";
            std::cout << "Type: " << (int)pkt.header.type << "\n";
            std::cout << "RequestId: " << pkt.header.requestId << "\n";
            std::cout << "Payload size: " << pkt.payload.size() << "\n";

            std::cout << "Payload bytes: ";
            for (uint8_t b : pkt.payload) {
                std::cout << (int)b << " ";
            }
            std::cout << "\n===========================\n";
        });
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // ===============================
    //             CLIENT
    // ===============================
    std::string input = R"(
        {@name:"Filip" @message:"super message" @age:19 @premium:true}
    )";

    MsonParser parser(input);
    MsonValue root = parser.parse();
    const MsonObject& obj = root.asObject();

    auto payload = MsonBinaryEncoder::encode(obj);

    MucpClient client;
    if (!client.connectTo("127.0.0.1", 5555)) {
        std::cout << "Client: connect failed\n";
        serverThread.join();
        return 1;
    }

    MucpPacket pkt;
    pkt.header.type = MucpType::Command;
    pkt.header.requestId = 1;
    pkt.payload = payload;

    client.send(pkt);

    std::cout << "\nMUCP CLIENT SENT PACKET\n";
    std::cout << "Payload bytes: " << payload.size() << "\n";

    // ===============================
    //            CLEANUP
    // ===============================
    serverThread.join();
    return 0;

#ifdef _WIN32
    WSACleanup();
#endif
    return 0;

}
