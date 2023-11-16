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

class cgiRequest : public request {
private:
	std::string _cgiPath;
	std::string _skriptName;
	std::string _tempFile;
	std::string _workingDirectory;
	int _fileDescriptor;
	std::string _query;
	std::string _execExtension;
	std::string _execPath;
	std::string _cgiFilePath;
	int	_errorCode;
	bool fileIsReady;
	bool _isError;
	bool _alarmSignal;	// boolean to check if alarm was activated.

public:
	explicit cgiRequest(std::vector<uint8_t> &requestContainer);
	cgiRequest();
	~cgiRequest();
	static bool _errorSignal;
	bool cgiCheckLanguage() const;
	bool cgiValidExtension(std::string url);
	bool createTemporaryFile();
	bool executeCgi();

	bool inputCheck();
	static void handleAlarmSignal(int signal);

	void getErrorHtmlContent(int _errorCode);

	std::string getFilePath();
};

#endif