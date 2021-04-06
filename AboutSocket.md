# socket()
```cpp
#include <sys/socket.h>
int socket(int domain, int type, int protocol)
```
# ifreq
```cpp
/**
<linux/if.h> is a bit different to the <net/if.h>, but functions similarly
linux/if.h is more related to linux's kernel while net/if.h is glibc's file which is more user space focused
*/
#include <net/if.h> 
struct ifreq {
    char ifr_name[IFNAMSIZ]; /* Interface name */
    union {
        struct sockaddr ifr_addr;
        struct sockaddr ifr_dstaddr;
        struct sockaddr ifr_broadaddr;
        struct sockaddr ifr_netmask;
        struct sockaddr ifr_hwaddr;
        short           ifr_flags;
        int             ifr_ifindex;
        int             ifr_metric;
        int             ifr_mtu;
        struct ifmap    ifr_map;
        char            ifr_slave[IFNAMSIZ];
        char            ifr_newname[IFNAMSIZ];
        char           *ifr_data;
    };
};
```
# ioctl()
```cpp
#include <sys/ioctl.h>
int ioctl(int fd, unsigned long request, ...);
/**
    sockfd: open file descriptor of socket
    SIOCGIFCONF: flags
    ifconf: struct ifconf
*/
ioctl(sockfd, SIOCGIFCONF, &ifconf);// obtain all interface info
/**
    sockfd: open file descriptor of socket
    SIOCGIFINDEX: flags
    ifreq: struct ifreq
*/
ioctl(sock, SIOCGIFINDEX, &ifreq);// obtain the ifindex of specified interface
```
# bind()
```cpp
#include <sys/socket.h>
int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
/**
    In AF_PACKET domain , the structure of sockaddr is as below;
    When send packets, it's enough to specify sll_family, sll_addr, sll_halen, sll_ifindex and
    sll_protocol. The other fields shall be set to zero
*/
struct sockaddr_ll {
    unsigned short sll_family;   // Always AF_PACKET 
    unsigned short sll_protocol; // ethernet protocol type defined in network byte order in linux/if_ether.h
    int            sll_ifindex;  // Interface number , 0 matches any interface when binding
    unsigned short sll_hatype;   // ARP hardware type 
    unsigned char  sll_pkttype;  // Packet type , only make senese when receiving
    unsigned char  sll_halen;    // Length of address 
    unsigned char  sll_addr[8];  // Physical-layer address 
};
```
# send() sendto() sendmsg() - send a message on a socket
```cpp
#include <sys/socket.h>
ssize_t send(int sockfd, const void *buf, size_t len, int flags);// only when the socket is in conneted state
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
    const struct sockaddr *dest_addr, socklen_t addrlen);// dest_addr and addrlen could be NULL and 0 in connection-mode or the socket is binded
ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
```
`send(fd,buf,len,0)` = `write(fd,buf,len)`  
`send(sockfd, buf, len, flags)` = `sendto(sockfd, buf, len, flags, NULL, 0)`  

-  so , when we bind the socket, can we use `send(sockfd, buf, len, flags)` instead of `sendto(sockfd, buf, len, flags, NULL, 0)`  ?
- when we hadn't binded the socket, can we use `sendto(sockfd, buf, len, flags, NULL, 0)`
- if we don't need the flags, could we just use write()?
- what is connected state? and what is connection mode?
- what about select()?