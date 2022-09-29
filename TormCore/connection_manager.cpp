/*
 * connection_manager.cpp
 *
 *  Created on: Sep 6, 2022
 *      Author: quarkhopper
 */

#include "connection_manager.hpp"

#include <optional>
#include <utility>

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
	this->m_callbacks = unordered_map<MessageType, msg_callback>();
	this->m_active = false;
}

void ConnectionManager::receive() {
	message_t msg;
	auto ret = this->m_socket.recv(msg);
	if (*ret == 0) {
		return;
	}
	string xml_ser = msg.to_string();
	MessageType msg_type = MessageFactory::getMessageType(xml_ser);
	if (this->m_callbacks.find(msg_type) != this->m_callbacks.end()) {
		this->m_callbacks[msg_type](&msg);
	}
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
