/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:16:52 by estruckm          #+#    #+#             */
/*   Updated: 2023/10/14 16:39:16 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_HPP
#define HEADER_HPP

#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

#include <sys/types.h>
#include <arpa/inet.h>
#include <poll.h>
#include <cstdlib>
#include <dirent.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERVER_PORT 8080
#define MAX_CLIENTS 10


#include "parsing.hpp"

#endif