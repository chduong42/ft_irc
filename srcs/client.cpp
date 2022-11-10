/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 03:55:27 by chduong           #+#    #+#             */
/*   Updated: 2022/11/10 04:44:31 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

static struct sockaddr TcpFormatAdress( char * host, u_short port )
{
    struct sockaddr_in addr;
    struct sockaddr addrRet;
    struct hostent *lphost ;
    u_long IP;

    memset((char*)&addr, 0, sizeof(addr));
    /*	Soit on fournit une adresse IP, soit on fournit un nom	*/
    if ((IP = inet_addr(host)) == (u_long)INADDR_NONE)
    {
        if ((lphost  = gethostbyname(host))==NULL)
        {
            memset( (char * )&addrRet, 0, sizeof(addrRet) );
            return  addrRet;
        }
        addr.sin_family = lphost->h_addrtype;
    }
    else
    {
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = IP;
    }

    /*  Port destination    */    
    addr.sin_port = htons((u_short)port );    

    memcpy( (char *)&addrRet, (char *)&addr, sizeof(addrRet) );
    return addrRet;
}

int main()
{
    int hSocket;
    struct sockaddr_in addr;
    struct sockaddr addrConnect;
    int nPort = 1234;
    char * pszHost = "127.0.0.1";

	hSocket = socket( PF_INET, SOCK_STREAM, 0 );
   /*  Liaison avec le port local (ici 0)  */
    addr.sin_family = AF_INET ;
    addr.sin_addr.s_addr = htonl (INADDR_ANY);
    addr.sin_port = htons ((unsigned short)0 ); // 0, cad qu'on laisse le système choisir un port
    if ( bind( hSocket, (struct sockaddr *)&addr, sizeof(addr)) == -1 )
    {
        printf( "socket() error (%d)\n", -1 );
        return -1;
    }
    /*	Soit on fournit une adresse IP, soit on fournit un nom	*/
    addrConnect = TcpFormatAdress( pszHost, (u_short)nPort );
    /*  Mode bloquant  */
    if (connect( hSocket, &addrConnect, sizeof(addrConnect) ) == -1 )
    {
        printf( "connect() error (%d)\n", -1 );
        return -1;
    }
    printf( "connect() error (%d)\n", -1 );
}