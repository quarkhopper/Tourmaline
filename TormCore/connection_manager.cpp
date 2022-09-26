/*
 * connection_manager.cpp
 *
 *  Created on: Sep 6, 2022
 *      Author: quarkhopper
 */

#include "connection_manager.hpp"

#include <utility>
#include <vector>

using namespace torm;
using namespace zmq;
using namespace std;

ConnectionManager::ConnectionManager(TormRoll roll, string endpoint) {
	auto stype =
			roll == TormRoll::Canvas ?
					zmq::socket_type::rep : zmq::socket_type::req;
	this->m_context = context_t();
	this->m_socket = socket_t(this->m_context, stype);
	this->m_socket.connect(endpoint);
//	this->m_callbacks = vector<MessageType, msg_callback>();
	this->m_active = false;
}

void ConnectionManager::receive() {
	/* call MessageType Message::getMessageType(std::string xml_ser); */
	/* get the callback in this->m_callbacks and call it if there is one */
//
//	try {
//		const auto ret = recv_multipart(*this->m_socket,
//				back_inserter(ConnectionManager::m_messages));
//		if (!ret)
//			throw(runtime_error("recv_multipart returned abnormally."));
//	} catch (const exception &e) {
//		cout << "Exception occurred while trying to get messages: " << e.what()
//				<< endl;
//	}
}

void ConnectionManager::start() {
	this->m_active = true;
	while (this->m_active) {
		this->receive();
	}
}

void ConnectionManager::stop() {
	this->m_active = false;
}

void ConnectionManager::registerCallback(MessageType mtype,
		msg_callback mcallback) {
	this->m_callbacks.emplace(mtype, mcallback);
}
