cmake_minimum_required(VERSION 3.31)
project(Mango)

set(CMAKE_CXX_STANDARD 26)


add_executable(Mango main.cpp
        mson/type/MsonType.cpp
        mson/type/MsonType.h
        mson/value/MsonValue.cpp
        mson/value/MsonValue.h
        mson/parser/MsonParser.cpp
        mson/parser/MsonParser.h
        mson/object/MsonObject.cpp
        mson/object/MsonObject.h
        mson/Mson.cpp
        mson/Mson.h
        mson/encoder/MsonBinaryEncoder.cpp
        mson/encoder/MsonBinaryEncoder.h
        mucp/type/MucpType.cpp
        mucp/header/MucpHeader.cpp
        mucp/header/MucpHeader.h
        mucp/type/MucpType.h
        mucp/packet/MucpPacket.cpp
        mucp/packet/MucpPacket.h
        mucp/codec/MucpCodec.cpp
        mucp/codec/MucpCodec.h
        mucp/tcp/MucpTcpSocket.cpp
        mucp/tcp/MucpTcpSocket.h
        mucp/server/MucpServer.cpp
        mucp/server/MucpServer.h
        mucp/client/MucpClient.cpp
        mucp/client/MucpClient.h
)

if (WIN32)
    target_link_libraries(Mango ws2_32)
endif()
