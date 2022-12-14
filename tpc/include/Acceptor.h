#ifndef TPC__ACCEPTOR_H
#define TPC__ACCEPTOR_H

#include "Common.h"
#include "Socket.h"
#include "TcpStream.h"

#include <climits>
#include <memory>

class InetAddress;

class TcpStream;

typedef std::unique_ptr<TcpStream> TcpStreamPtr;

class Acceptor : noncopyable {
    public:
        explicit Acceptor(const InetAddress& listenAddr);

        ~Acceptor() = default;
        Acceptor(Acceptor&&) = default;
        Acceptor& operator=(Acceptor&&) = default;

        // thread safe
        TcpStreamPtr accept();
        Socket acceptSocketOrDie();

    private:    
        Socket listenSock_;
};

#endif