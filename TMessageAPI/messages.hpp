/*
 * messages.hpp
 *
 *  Created on: Sep 6, 2022
 *      Author: quarkhopper
 *
 *
 */

#include <pugixml.hpp>
#include <string>
#include <map>
#include <typeinfo>

#ifndef MESSAGES_HPP_
#define MESSAGES_HPP_

namespace torm {

enum MessageType {
	PutPoint
};

class IMessage {
public:
	virtual void encodeXML() = 0;
	virtual void parseXML(std::string xml_ser) = 0;
	virtual ~IMessage() {
	}
	;
};

// Base class for all API messages
class MessageBase: public IMessage {
public:
	MessageBase(const MessageBase&);
	MessageBase()=default;
	MessageType messageType = MessageType::PutPoint;
	std::string xml_ser;
	pugi::xml_document doc;
	pugi::xml_node root;
	std::string getXML();
	void encodeXML();
	void parseXML(std::string xml_ser);
};

// API Message to set a pixel color on the canvas
class PutPointMessage: public MessageBase {
public:
	PutPointMessage(const PutPointMessage&);
	PutPointMessage();
	void encodeXML();
	void parseXML(std::string xml_ser);
	int x = 0;
	int y = 0;
	int color = 0;
};

class MessageFactory {
public:
	template<class T>
	static T createMessage(std::string xml_ser);
};
}

#endif /* MESSAGES_HPP_ */
