#include "tekcos.h"
#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#endif

#ifdef __linux__
#define INVALID_SOCKET -1
#define SOCKET_ERROR   -1
#endif

// error code 
enum
{
    TK_SUCCESS = 0,

    TK_INITFAILED,            // init tekcos failed 

    TK_COULDNETCREATESOCKET,  // couldn't create socket. 
    TK_CONNECTFAILED,         // connect to remote server failed.
    TK_BINDSOCKETFAILED,      // couldn't bind socket to port 
    TK_LISTENSOCKETFAILED,    // couldn't listen to port
    TK_INVALIDSOCKET,         // invalid socket 
    TK_WRONGSOCKETTPYE,       // wrong socket type

    TK_INVALIDTARGET,         // cant sendto. 

    TK_UNKNOWN,               // unknown
};

// error code 
static int state = 0;

const char* tk_errmsg()
{
    int tmp = state;
    state = 0; 
    switch (tmp)
    {
    case TK_SUCCESS:              return "success";
    case TK_INITFAILED:           return "init tekcos failed";
    case TK_COULDNETCREATESOCKET: return "couldn't create socket";
    case TK_CONNECTFAILED:        return "connect to remote server failed";
    case TK_BINDSOCKETFAILED:     return "couldn't bind socket to port";
    case TK_LISTENSOCKETFAILED:   return "couldn't listen to port";
    case TK_INVALIDSOCKET:        return "invalid socket";
    case TK_WRONGSOCKETTPYE:      return "wrong socket type";
    case TK_INVALIDTARGET:        return "cant sendto";
    case TK_UNKNOWN:              return "unknown error";
    default:                      return "unknown error";
    }
}

#ifdef _WIN32
int tk_init()
{
    WORD version_wanted = MAKEWORD(1, 1);
    WSADATA wsaData;

    if (WSAStartup(version_wanted, &wsaData) != 0) {
        state = TK_INITFAILED; 
        return 0; 
    }
    return 1;
}
#endif

// socket type 
enum {
    SOCKET_TSERVER = 1, 
    SOCKET_TCLIENT = 2
};

uint32 tk_strtohl(const char* str)
{
    struct in_addr inaddr; 
    inet_pton(AF_INET, str, (void*)&inaddr);
    // host long 
    return ntohl(inaddr.s_addr);
}

const char* tk_hltostr(uint32 ip)
{
    struct in_addr addr; 
    addr.s_addr = htonl(ip);
    char* buffer = (char*)malloc(16);
    inet_ntop(AF_INET, &addr, buffer, 16);
    buffer[15] = '\0';
    return buffer;
} 

/********************************************/
/* TCP socket                               */
/********************************************/

tk_TCPsocket* tk_tcp_open(tk_IPaddress ip)
{
    tk_TCPsocket* sk;
    sk = (tk_TCPsocket*)malloc(sizeof(tk_TCPsocket));
    sk->id = socket(AF_INET, SOCK_STREAM, 0);
    if (sk->id == INVALID_SOCKET)
    {
        state = TK_COULDNETCREATESOCKET;
        goto error; 
    }
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_port = htons(ip.port);
    // 32bit address and 16bit port number. 
    addr.sin_family = AF_INET;

    if (ip.host != INADDR_NONE && (ip.host != INADDR_ANY))
    { // connet to an existed remote server. 
        addr.sin_addr.s_addr = htonl(ip.host);
        if (connect(sk->id, (const struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
        {
            state = TK_CONNECTFAILED; 
            goto error;
        }
        sk->type = SOCKET_TCLIENT; 
    }else
    { // create a listenning server.  
        addr.sin_addr.s_addr = htonl(INADDR_ANY);

        if (bind(sk->id, (const struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
        {
            state = TK_BINDSOCKETFAILED;
            goto error; 
        }
        if (listen(sk->id, 8) == SOCKET_ERROR)
        {
            state = TK_LISTENSOCKETFAILED; 
            goto error; 
        }
        sk->type = SOCKET_TSERVER;
    }

    sk->remote.host = ntohl(addr.sin_addr.s_addr);
    sk->remote.port = ntohs(addr.sin_port);

    return sk;
error:
    return 0;
}

int tk_tcp_close(tk_TCPsocket* sk)
{
    if (sk)
    {
        if (sk->id == INVALID_SOCKET)
            goto error;
#ifdef _WIN32
        closesocket(sk->id); 
#else
	close(sk->id);
#endif        
	free(sk);
        return 1;
    }
error:
    state = TK_INVALIDSOCKET; 
    return 0; 
}

int tk_tcp_send(tk_TCPsocket* client, const void* buffer, int bsize, int* sent)
{
    // byte poiter. 
    const char *data = (const char*)buffer;
    if (client->type != SOCKET_TCLIENT)
    {// only cliednt can send stuff. 
        state = TK_WRONGSOCKETTPYE;
        goto error; 
    }
    //send(sk->id, buffer, bsize, 0);
    int left = bsize;
    if(sent) *sent = 0;
    int len = 0;
    do {
        len = send(client->id, data, left, 0);
        if (len > 0) {
            if(sent) *sent += len;
            left -= len;
            data += len;
        }
    } while ((left > 0) && ((len > 0) || (errno == EINTR)));
    return 1;
error:
    return 0; 
}

int tk_tcp_recv(tk_TCPsocket* client, char* buffer, int bsize, int* len)
{
    *len = 0;
    if (client->type != SOCKET_TCLIENT)
    {// only client can be recieved
        state = TK_WRONGSOCKETTPYE;
        goto error; 
    }
    do
    {
        *len = recv(client->id, buffer, bsize, 0);
        if (*len == SOCKET_ERROR)
        {
            state = TK_UNKNOWN;
            goto error;
        }
    } while (*len == 0 || errno == EINTR); // if was suspended, recieve again. 
    buffer[*len] = '\0';
    return 1; 
error:
    return 0; 
}

tk_TCPsocket* tk_tcp_accept(tk_TCPsocket* server)
{
    tk_TCPsocket* csk = (tk_TCPsocket*) malloc(sizeof(tk_TCPsocket));
    if (server->type != SOCKET_TSERVER)
    {// only server can accept connection 
        state = TK_WRONGSOCKETTPYE; 
        goto error; 
    }
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    int addr_len = sizeof(addr);
    csk->id = accept(server->id, (struct sockaddr *)&addr, &addr_len);
    if (csk->id == INVALID_SOCKET)
    {
        state = TK_INVALIDSOCKET; 
        goto error; 
    }

    csk->remote.host = ntohl(addr.sin_addr.s_addr);
    csk->remote.port = ntohs(addr.sin_port);

    csk->type = SOCKET_TCLIENT; 

    return csk; 
error: 
    return 0; 
}

int tk_tcp_nonblocking(tk_TCPsocket* sk)
{
#if defined(__BEOS__) && defined(SO_NONBLOCK)
    {
        long b = 1;
        setsockopt(sk->id, SOL_SOCKET, SO_NONBLOCK, &b, sizeof(b));
    }
#elif defined(WIN32)
    {
        unsigned long mode = 1;
        ioctlsocket(sk->id, FIONBIO, &mode);
    }
#elif defined(__OS2__)
    {
        int dontblock = 1;
        ioctl(sk->id, FIONBIO, &dontblock);
    }
#endif
}

int tk_tcp_blocking(tk_TCPsocket* sk)
{
#if defined(__BEOS__) && defined(SO_NONBLOCK)
    {
        long b = 0;
        setsockopt(sk->id, SOL_SOCKET, SO_NONBLOCK, &b, sizeof(b));
    }
#elif defined(WIN32)
    {
        unsigned long mode = 0;
        ioctlsocket(sk->id, FIONBIO, &mode);
    }
#elif defined(__OS2__)
    {
        int dontblock = 0;
        ioctl(sk->id, FIONBIO, &dontblock);
    }
#endif
}

/***************************************************
* UDP socket
* 
* server
*   => Create a socket with socket() 
*   => Bind the socket to a address using bind() 
*   => Send and recieve data using sendto() and 
*      recvfrom()
*
* client: 
*   => Create a socket with socket() 
*   => Send and recieve data using sendto() and
*      recvfrom()
* 
***************************************************/

tk_UDPsocket* tk_udp_open(uint16 portnumber)
{
    tk_UDPsocket* sk; 
    sk = (tk_UDPsocket*)malloc(sizeof(tk_UDPsocket));
    sk->id = socket(AF_INET, SOCK_DGRAM, 0); 
    if (sk->id == INVALID_SOCKET)
    {
        state = TK_COULDNETCREATESOCKET; 
        goto error; 
    }
    if (portnumber <= 0)
    {// client, just return 
        return sk; 
    }
    else
    {// server, need to bind address to socket 
        struct sockaddr_in addr; 
        memset(&addr, 0, sizeof(addr)); 
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(portnumber);
        addr.sin_family = AF_INET;
        bind(sk->id, (const struct sockaddr*)&addr, sizeof(addr));
        return sk;
    }

error: 
    return 0; 
}

int tk_udp_sendto(tk_UDPsocket* sk, tk_UDPpack* pack)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET; 
    addr.sin_port = htons(pack->ip.port);
    addr.sin_addr.s_addr = htonl(pack->ip.host);
    int len = sizeof(addr);
    int n = sendto(sk->id, pack->data, pack->len, 0, (const struct sockaddr*)&addr, len);
    if (n < 0)
    {
        state = TK_INVALIDTARGET; 
        return 0; 
    }
    return 1; 
}

int tk_udp_recvfrom(tk_UDPsocket* sk, tk_UDPpack* pack)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    int addr_len = sizeof(addr); 
    pack->data = (char*)malloc(2048); 
    int n = recvfrom(sk->id, pack->data, 2048, 0, (struct sockaddr*)&addr, &addr_len);
    pack->ip.host = ntohl(addr.sin_addr.s_addr);
    pack->ip.port = ntohs(addr.sin_port);
    if (n < 0)
    {
        state = TK_INVALIDTARGET;
        return 0; 
    }
    pack->len = n;
    pack->data[n] = '\0';
    return 1; 
}

int tk_udp_close(tk_UDPsocket* sk)
{
    if (sk)
    {
        if (sk->id != INVALID_SOCKET)
        {
#ifdef _WIN32
            closesocket(sk->id);
#else
	    close(sk->id);
#endif
        }
        free(sk);
    }
}

int tk_freepack(tk_UDPpack* pack)
{
    free(pack->data); 
    free(pack);
}




