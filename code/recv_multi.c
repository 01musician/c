#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef int Sint32;
typedef int SOCKET_T;
typedef char Sint8;
typedef unsigned int Uint32;
typedef struct sockaddr_in          ST_SkAddrIn;        /**<\brief INET域SOCK地址               */
typedef struct sockaddr             ST_SkAddr;          /**<\brief 通用SOCK地址                 */
typedef struct ip_mreq              ST_SkAddrMu;        /**<\brief 多播SOCK地址                 */
typedef struct in_addr              ST_In;              /**<\brief IP结构                       */

typedef struct sockaddr_in          ST_SkAddrIn;        /**<\brief INET域SOCK地址               */
typedef struct sockaddr             ST_SkAddr;          /**<\brief 通用SOCK地址                 */
typedef struct ip_mreq              ST_SkAddrMu;        /**<\brief 多播SOCK地址                 */
typedef struct in_addr              ST_In;              /**<\brief IP结构                       */

/**
  \brief      记录运行日志

  若记录文件已打开，输出日志至文件；
  若记录文件未打开，输出日志至标准出错。
  \param[in]  scLevel 日志级别，R/r表示运行日志，
  A/a表示告警日志，
  其他表示错误日志
  \param[in]  pszLog  日志内容，带结束符的字符串
  \return     无
  */
void Z_Log(Sint8  scLevel, Sint8* pszLog)
{
        time_t     TimeVal;
        struct tm  stTimeVal;
        Sint8      szTimeStr[32];


        /** 获取系统时间 */
        time(&TimeVal);
        localtime_r(&TimeVal, &stTimeVal);
        strftime(szTimeStr, sizeof(szTimeStr), "%F %T", &stTimeVal);
        szTimeStr[sizeof(szTimeStr)-1] = 0;

        /** 分类记录日志 */
        if((scLevel == 'R') || (scLevel == 'r'))
        {
                fprintf(stdout, "[RUN %s] %s\n", szTimeStr, pszLog);
#ifdef DEBUG
                fprintf(stderr, "[RUN %s] %s\n", szTimeStr, pszLog);
#endif
        }
        else if((scLevel == 'A') || (scLevel == 'a'))
        {
                fprintf(stdout, "[ALM %s] %s\n", szTimeStr, pszLog);
#ifdef DEBUG
                fprintf(stderr, "[ALM %s] %s\n", szTimeStr, pszLog);
#endif
        }
        else
        {
                fprintf(stdout, "[ERR %s] %s\n", szTimeStr, pszLog);
#ifdef DEBUG
                fprintf(stderr, "[ERR %s] %s\n", szTimeStr, pszLog);
#endif
        }
        fflush(stdout);


        return;
}

int 
main(char **argv, int argc)
{
	Sint32      siRet;
        SOCKET_T    Sk;
        Sint8       scTTL;
        ST_In       stIn;
        ST_SkAddrIn stSkAddrIn;
        ST_SkAddrMu stSkAddrMu;
	Sint8 	    *pszMIP = "225.88.88.88";
	Uint32      uiPort = 8888;


        /** 创建SOCK */
        Sk = socket(AF_INET, SOCK_DGRAM, 0);
        if(Sk < 0)
        {
                Z_Log('E', "create socket error");
                return -1;
        }

	/** 设置接收缓存长度 */
	Sint32 scReuse = 1;
        siRet = setsockopt(Sk, SOL_SOCKET, SO_REUSEADDR,
                        &scReuse, sizeof(scReuse));
        if(siRet < 0)
        {
                Z_Log('E', "set reuse addr socket error");
                return -1;
        }

        /** 绑定地址 */
        memset(&stSkAddrIn, 0, sizeof(stSkAddrIn));
        stSkAddrIn.sin_family = AF_INET;
	stSkAddrIn.sin_addr.s_addr = htonl(INADDR_ANY);
        stSkAddrIn.sin_port = htons(uiPort);
        siRet = bind(Sk, (ST_SkAddr*)&stSkAddrIn, sizeof(stSkAddrIn));
        if(siRet < 0)
        {
                Z_Log('E', "bind socket error");
                return -1;
        }

        /** 设置接收缓存长度 */
	Sint32 siRcvBufLen = 64*1024;
        siRet = setsockopt(Sk, SOL_SOCKET, SO_RCVBUF,
                        &siRcvBufLen, sizeof(siRcvBufLen));
        if(siRet < 0)
        {
                Z_Log('E', "set receive buffer length of socket error");
                return -1;
        }

        /** 设置发送缓存长度 */
	Sint32 siSndBufLen = 64*1024;
        siRet = setsockopt(Sk, SOL_SOCKET, SO_SNDBUF,
                        &siSndBufLen, sizeof(siSndBufLen));
        if(siRet < 0)
        {
                Z_Log('E', "set send buffer length of socket error");
                return -1;
        }

        /** 设置组播TTL */
        scTTL = 8;
        siRet = setsockopt(Sk, IPPROTO_IP, IP_MULTICAST_TTL,
                        &scTTL, sizeof(scTTL));
        if(siRet < 0)
        {
                Z_Log('E', "set multicast ttl error");
                return -1;
        }

     
        /** 加入组播 */
	stSkAddrMu.imr_multiaddr.s_addr = inet_addr(pszMIP);
	stSkAddrMu.imr_interface.s_addr = htonl(INADDR_ANY);
	siRet = setsockopt(Sk, IPPROTO_IP, IP_ADD_MEMBERSHIP,
			&stSkAddrMu, sizeof(stSkAddrMu));
	if(siRet < 0)
	{
		Z_Log('E', "join multicast group error");
		return -1;
	}

	char buf[1024];
	siRet = recv(Sk, buf, sizeof(buf), 0);
	if (siRet < 0)
	{
		Z_Log('E', "recv from multi address error");
		return -1;
	}

	printf("receive %d bytes code from %s \n", siRet, pszMIP);

        return 0;
}

