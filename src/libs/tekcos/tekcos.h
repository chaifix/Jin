#ifndef _TEKCOS_H
#define _TEKCOS_H

#if defined(_WIN32)
#include <WS2tcpip.h>
#include <winsock.h>
#else 
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#endif

#define TK_VERSION "0.1.0"

typedef unsigned int uint32;
typedef unsigned short uint16;

#ifdef _WIN32
// neccessary for windows 
int tk_init();
#endif
// Under AF_INET domain, we use 32bit host + 16bit port to 
// locate a proccess.  
typedef struct 
{
    uint32 host; // 32bit ip 
    uint16 port; // 16 bit port
} tk_IPaddress;

uint32 tk_strtohl(const char* str); // string to host long(32 bits)
const char* tk_hltostr(uint32 ip);  // host long to string
#define tk_htons htons              // host to network short(16 bits)
#define tk_ntohl ntohl              // network to host long(32bits) 

/*
* TCP socket
* type = SOCK_STREAM
* protocol = IPPROTO_TCP
*/

#ifdef __linux__
typedef unsigned int SOCKET; 
#endif
// TCP socket structrue. 
typedef struct
{
    SOCKET id;           // socket id
    int type;            // socket type 
    tk_IPaddress remote; // remote ip 
    tk_IPaddress local;  // local ip 
} tk_TCPsocket;

// create a tcp socket. if ip.host is INADDR_NONE or
// INADDR_ANY, creeate a listenning server socket, 
// otherwise, connect to a remote server with given 
// ip address. 
tk_TCPsocket* tk_tcp_open(tk_IPaddress ip);

int tk_tcp_close(tk_TCPsocket* sk); 

int tk_tcp_send(tk_TCPsocket* client, const void* buffer, int bsize, int* len);

int tk_tcp_recv(tk_TCPsocket* client, char* buffer, int bsize, int* len);

tk_TCPsocket* tk_tcp_accept(tk_TCPsocket* server); 

int tk_tcp_nonblocking(tk_TCPsocket* sk);

int tk_tcp_blocking(tk_TCPsocket* sk);

/*
* UDP socket 
* type = SOCK_DGRAM
* protocol = IPPTOTO_UDP
*/ 

// UDP socket structure. 
typedef struct
{
    SOCKET id;           // socket id
} tk_UDPsocket;

typedef struct
{
    tk_IPaddress ip;      // recvfrom or sendto ip addreass
    int len;              // length of data  
    char* data;           // data 
}tk_UDPpack;

tk_UDPsocket* tk_udp_open(uint16 portnumber);

int tk_udp_close(tk_UDPsocket* sk);

int tk_udp_sendto(tk_UDPsocket* sk, tk_UDPpack* pack);

int tk_udp_recvfrom(tk_UDPsocket* sk, tk_UDPpack* pack);

int tk_freepack(tk_UDPpack* pack); 

// Get error message if some errors occured.
const char* tk_errmsg(); 

#endif
