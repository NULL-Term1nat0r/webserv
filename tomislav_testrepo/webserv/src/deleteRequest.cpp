/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deleteRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:17:32 by estruckm          #+#    #+#             */
/*   Updated: 2023/10/24 20:25:26 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/deleteRequest.hpp"

deleteRequest::deleteRequest(std::vector<uint8_t> &deleteRequest) : request(deleteRequest){
	std::cout << "deleteRequest constructor called\n";
}
deleteRequest::deleteRequest(){}

deleteRequest::~deleteRequest() {}