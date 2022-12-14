#ifndef TPC__TCPSTREAM_H
#define TPC__TCPSTREAM_H

#include "Common.h"
#include "InetAddress.h"
#include "Socket.h"

#include <memory>

class TcpStream;
typedef std::unique_ptr<TcpStream> TcpStreamPtr;

// A blocking TCP stream

class TcpStream : noncopyable {
    public:
        explicit TcpStream(Socket&& socket);
        ~TcpStream() = default;
        TcpStream(TcpStream&&) = default;

        static TcpStreamPtr connect(const InetAddress& serverAddr);
        static TcpStreamPtr connect(const InetAddress& serverAddr, const InetAddress& localAddr);

        // NOT thread safe
        int receiveAll(void* buf, int len); // read len bytes, unless error happens
        int receiveSome(void* buf, int len); // read len or less bytes

        int sendAll(const void* buf, int len); // send len bytes, unless error happens
        int sendSome(const void* buf, int len); // send len or less bytes

        // thread safe
        InetAddress getLocalAddr() const {return sock_.getLocalAddr();}
        InetAddress getPeerAddr() const {return sock_.getPeerAddr();}

        void setTcpNoDelay(bool on);
        void shutdownWrite();

        int fd() { return sock_.fd();}

    private:
        static TcpStreamPtr connectInternal(const InetAddress& serverAddr, const InetAddress* localAddr);
        Socket sock_;
};

#endif