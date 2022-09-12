/*
 * messages.cpp
 *
 *  Created on: Sep 6, 2022
 *      Author: quarkhopper
 */

#include <string>
#include <memory>
#include <sstream>
#include <iostream>
#include <concepts>
#include <pugixml.hpp>
#include "messages.hpp"

using namespace torm;
using namespace std;
using namespace pugi;

void MessageBase::parseXML(string xml_ser) {
	this->doc.load_string(xml_ser.c_str());
	this->root = this->doc.root();
	this->messageType =
			static_cast<MessageType>(this->root.attribute("type").as_int());
}

string MessageBase::getXML() {
	MessageBase::encodeXML();
	stringstream ss;
	this->doc.save(ss);
	return ss.str();
}

void MessageBase::encodeXML() {
	this->root = this->doc.append_child("TourmalineMessage");
	xml_attribute message_type = this->root.append_attribute("type");
	message_type.set_value(to_string(this->messageType).c_str());
	this->encodeXML();
}

PutPointMessage::PutPointMessage() {
	this->messageType = MessageType::PutPoint;
}

void PutPointMessage::parseXML(string xml_ser) {
	MessageBase::parseXML(xml_ser);
	xml_node data_root = this->root.child("data");
	this->x = data_root.child("x").text().as_int();
	this->y = data_root.child("y").text().as_int();
	this->color = data_root.child("color").text().as_int();
}

void PutPointMessage::encodeXML() {
	xml_node data_root = this->root.append_child("data");
	data_root.append_child("x").text().set(to_string(this->x).c_str());
	data_root.append_child("y").text().set(to_string(this->y).c_str());
	data_root.append_child("color").text().set(to_string(this->color).c_str());
}

MessageBase* MessageFactory::createMessage(string xml_ser) {
	// TODO: actually parse the string here to get the type to use
	MessageBase mb;
	MessageBase* msg;
	mb.parseXML(xml_ser);
	switch (mb.messageType) {
	case MessageType::PutPoint:
		auto msg = make_unique<PutPointMessage>();
		msg->parseXML(xml_ser);
		break;
	}
	return msg;
}
