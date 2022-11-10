/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:13:31 by chduong           #+#    #+#             */
/*   Updated: 2022/11/10 02:31:28 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <cstdio>
# include <cerrno>
# include <csignal>
# include <cstdlib>

class Server {
	private:
		int					_hSocket;
		int					_hAccept;
		int					_port;
		int					_len;
		struct sockaddr_in	_addr;
		
	public:
		Server();
		~Server();
		
};

#endif