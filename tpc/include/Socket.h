#ifndef TPC__SOCKET_H
#define TPC__SOCKET_H

#include "Common.h"

#include <utility>
#include <netinet/in.h>

class InetAddress;

// RAII handle for socket fd

class Socket : noncopyable {
    public:
        explicit Socket(int sockfd);
        ~Socket(); // close sockfd_

        Socket(Socket&& rhs) : Socket(rhs.sockfd_) {
            rhs.sockfd_ = -1;
        }

        Socket& operator=(Socket&& rhs) {
            swap(rhs);
            return *this;
        }

        void swap(Socket& rhs) {
            std::swap(sockfd_, rhs.sockfd_);
        }

        int fd() const { return sockfd_; }

        // Sockets API
        void bindOrDie(const InetAddress& addr);
        void listenOrDie();
        
        // return 0 on success
        int connect(const InetAddress& addr);
        void shutdownWrite();

        void setReuseAddr(bool on);
        void setTcpNoDelay(bool on);

        InetAddress getLocalAddr() const;
        InetAddress getPeerAddr() const;

        int recv(void* buf, int len);
        int send(const void* buf, int len);

          // factory methods
        static Socket createTCP(sa_family_t family);  // AF_INET or AF_INET6
        static Socket createUDP(sa_family_t family);  // AF_INET or AF_INET6

    private:
        int sockfd_;
};

#endif