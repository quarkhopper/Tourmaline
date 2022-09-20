/*
 * generator.cpp
 *
 *  Created on: Aug 30, 2022
 *      Author: quarkhopper
 */

#include <zmq.hpp>
#include <zmq_addon.hpp>
#include <array>
#include <iostream>
#include <string>
#include <messages.hpp>

int main (int   argc, char *argv[]) {

	PutPoint


	zmq::context_t ctx;
	zmq::socket_t sock1(ctx, zmq::socket_type::push);
	sock1.bind("tcp://127.0.0.1:*");
	const std::string last_endpoint =
		sock1.get(zmq::sockopt::last_endpoint);
	std::cout << "Binding: "
			  << last_endpoint << std::endl;

	std::array<zmq::const_buffer, 2> send_msgs = {
		zmq::str_buffer("<root_tag>Here is a whole bunch of text</root_tag>"),
		zmq::str_buffer("bar!")
	};
	if (!zmq::send_multipart(sock1, send_msgs)) //, zmq::send_flags::dontwait))
		return 1;

	return 0;
}


