/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolkova <tbolkova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 15:13:09 by tbolkova          #+#    #+#             */
/*   Updated: 2023/10/28 15:13:09 by tbolkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

#include "Header.h"
#include "request.hpp"
#include "response.hpp"

class cgi : public request {
private:
	std::string _response;
	std::string _cgiPath;
	std::string _query;
	std::string _fileExtension;

public:
	cgi();
	~cgi();

	bool cgiCheckLanguage() const;
	int cgiValidExtension(std::string url);
	int executeCgi();

	bool inputCheck();
	static void handleAlarmSignal(int signal);

    void cookieContent(const std::string& url, size_t pos);
};

#endif