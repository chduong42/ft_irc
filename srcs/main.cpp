/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:03:13 by chduong           #+#    #+#             */
/*   Updated: 2022/10/28 19:21:49 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

 int	main(int argc, char **argv)
{
	if (argc > 1)
	{
		std::cout << "Usage: ./ircserv <port> <password>" << std::endl;
		exit(EXIT_FAILURE);
	}
	while (42)
		pause();
	return (0);
}