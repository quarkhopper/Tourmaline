/*
 * connection_manager.hpp
 *
 *  Created on: Sep 6, 2022
 *      Author: quarkhopper
 */

#ifndef CONNECTIONMANAGER_HPP_
#define CONNECTIONMANAGER_HPP_

#include <zmq.hpp>
#include <functional>
#include <string>
#include <unordered_map>

#include "messages.hpp"

namespace torm {

typedef std::function<void(zmq::message_t)> msg_callback;

enum TormRoll {
	Canvas, Generator
};

class ConnectionManager {
private:
	void receive();
	zmq::socket_t m_socket;
	zmq::context_t m_context;
	bool m_active;
	std::unordered_map<MessageType, msg_callback> m_callbacks;
public:
	ConnectionManager(TormRoll, std::string);
	void start();
	void stop();
	void registerCallback(MessageType, msg_callback);
};
}

#endif /* CONNECTIONMANAGER_HPP_ */
