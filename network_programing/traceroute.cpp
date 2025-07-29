#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdlib.h>
#include <netdb.h>

/* IP Header */
struct ipheader {
    unsigned char iph_ihl : 4, iph_ver : 4;           // IP Header length & Version.
    unsigned char iph_tos;                            // Type of service
    unsigned short int iph_len;                       // IP Packet length (Both data and header)
    unsigned short int iph_ident;                     // Identification
    unsigned short int iph_flag : 3, iph_offset : 13; // Flags and Fragmentation offset
    unsigned char iph_ttl;                            // Time to Live
    unsigned char iph_protocol;                       // Type of the upper-level protocol
    unsigned short int iph_chksum;                    // IP datagram checksum
    struct in_addr iph_sourceip;                      // IP Source address (In network byte order)
    struct in_addr iph_destip;                        // IP Destination address (In network byte order)
};

/* ICMP Header */
struct icmpheader {
    unsigned char icmp_type;        // ICMP message type
    unsigned char icmp_code;        // Error code
    unsigned short int icmp_chksum; // Checksum for ICMP Header and data
    unsigned short int icmp_id;     // Used in echo request/reply to identify request
    unsigned short int icmp_seq;    // Identifies the sequence of echo messages,
                                    // if more than one is sent.
};

#define ICMP_ECHO_REPLY     0
#define ICMP_ECHO_REQUEST   8
#define ICMP_TIME_EXCEEDED  11
#define MAX_HOPS            30
#define MAX_RETRY           3
#define PACKET_LEN          1500

void traceroute(char* dest) {
    // raw sockets require root priviliges
    if (getuid() != 0) {
        perror("requires root privilige");
        exit(-1);
    }

    
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(-1);
    }

    sockaddr_in addr;
    memset(&addr, 0, sizeof(sockaddr_in));
    addr.sin_family = AF_INET;
    hostent* getip = gethostbyname(dest);
    if (getip == NULL) {
        perror("failed gethostbyname");
        exit(-1);
    }
    memcpy((char*)(&addr.sin_addr), getip->h_addr, getip->h_length);

    printf("traceroute to %s (%s), %d hops max, %ld bytes packets\n", dest, inet_ntoa(addr.sin_addr), MAX_HOPS, sizeof(ipheader) + sizeof(icmpheader));
    
    char send_buf[PACKET_LEN], recv_buf[PACKET_LEN];
    /**
     * Prepare packet
     * a. outgoing packets only contain the icmpheader with type = ICMP_ECHO_REQUEST, code = 0
     * b. ID in the icmpheader should be set to current process id to identify received ICMP packets
     * c. checksum can be set to 0 for this test
     * d. write/copy the header to the send_buf  
     * 
    */
    icmpheader* icmp = (icmpheader*) send_buf;
    icmp->icmp_type = ICMP_ECHO_REQUEST;
    icmp->icmp_code = 0;
    icmp->icmp_id = getpid();
    icmp->icmp_chksum = 0;

    for (int ttl = 1; ttl <= MAX_HOPS; ) {
        printf("%2d ", ttl);
        icmp->icmp_seq = ttl;

        // set ttl to outgoing packets
        if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, (const char*)&ttl, sizeof(ttl)) < 0) {
            perror("setsockopt failed");
            exit(-1);
        }

        int retry = 0;
        while (1) {
            // ensure we send one icmpheader in the packet
            int sent = sendto(sockfd, send_buf, sizeof(struct icmpheader), 0, (struct sockaddr* )&addr, sizeof(addr));
            if(sent < 0){
                perror("Sendto error");
            }
            // wait to check if there is data available to receive; need to retry if timeout
            struct timeval tv;
            fd_set rfd;

            tv.tv_sec = 1;
            tv.tv_usec = 0;
            FD_ZERO(&rfd);
            FD_SET(sockfd, &rfd);
            int ret = select(sockfd + 1, &rfd, NULL, NULL, &tv);

            /** TOOD: 4
             * Check if data available to read or timeout
             * a. if ret == 0: timeout --> retry upto MAX_RETRY
             * b. if ret > 0: data available, use recvfrom(...) to read data to recv_buf and process --> see TODO 5 below
             */
            if (ret == 0) {
                retry++;
                printf("* ");
            }
            else if (ret > 0) {
                /*
                 * b. ensure data is received in recv_buf
                 */
                socklen_t addr_length = sizeof(addr);
                int recieve_bytes = recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&addr, &addr_length);
                if(recieve_bytes < 0){
                    perror("recv from error");
                    continue;
                }
                
                // split the recv buf to ip header and icmp header
                struct ipheader* iphead = (struct ipheader*)recv_buf;
                int iphead_len = iphead->iph_ihl * 4;
                struct icmpheader* icmphead = (struct icmpheader*)(recv_buf + iphead_len);
                
                if(icmphead->icmp_type == ICMP_TIME_EXCEEDED && recieve_bytes >= 2 * (sizeof(ipheader) + sizeof(icmpheader))){
                    // orginal ipheader and orginal icmpheader
                    struct ipheader* origin_iphead = (struct ipheader*)(recv_buf + iphead_len + sizeof(struct icmpheader));
                    struct icmpheader* origin_icmpheader = (struct icmpheader*)((char*)origin_iphead + origin_iphead->iph_ihl*4);

                    if(origin_icmpheader->icmp_seq == ttl && origin_icmpheader->icmp_id == getpid()){
                        printf("%s\n", inet_ntoa(addr.sin_addr));
                        ttl++;
                        break;
                    }
                }
                else if(icmphead->icmp_type == ICMP_ECHO_REPLY && icmphead->icmp_id == getpid()){
                    printf("%s\n", inet_ntoa(addr.sin_addr));
                    return;
                }
            }
            else {
                perror("select failed");
                exit(-1);
            }
            fflush(stdout);

            
            // Check if timed out for MAX_RETRY times; increment ttl to move on to processing next hop
            
            if(retry == MAX_RETRY){
                printf("\n");
                ttl++;
                break;
            }
        }
    }
    close(sockfd);
}

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("Usage: traceroute <destination hostname>\n");
        exit(-1);
    }
    
    char* dest = argv[1];
    traceroute(dest);

    return 0;
}