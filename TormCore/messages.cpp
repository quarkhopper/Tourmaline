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

MessageBase::MessageBase(const MessageBase &old_msg) {
	this->messageType = old_msg.messageType;
}

void MessageBase::parseXML(string xml_ser) {
	this->doc.load_string(xml_ser.c_str());
	this->root = this->doc.root().first_child();
	this->messageType =
			static_cast<MessageType>(this->root.attribute("type").as_int());
}

string MessageBase::getXML() {
	this->doc.reset();
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

PutPointMessage::PutPointMessage(const PutPointMessage &old_msg) {
	this->messageType = MessageType::PutPoint;
	this->xml_ser = old_msg.xml_ser;
	this->doc.load_string(this->xml_ser.c_str());
	this->root = this->doc.root().first_child();
	this->x = old_msg.x;
	this->y = old_msg.y;
	this->color = old_msg.color;
}

void PutPointMessage::parseXML(string xml_ser) {
	/*******************************************
	 * Set members with an XML serialized string.
	 * This call begins by calling the base class
	 * definition to parse base Message members.
	 */
	this->xml_ser = xml_ser;
	MessageBase::parseXML(xml_ser);
	xml_node data_root = this->root.child("data");
	this->x = data_root.child("x").text().as_int();
	this->y = data_root.child("y").text().as_int();
	this->color = data_root.child("color").text().as_int();
}

void PutPointMessage::encodeXML() {
	/********************
	 * Encode the particulars of a PutPointMessage into XML
	 */
	xml_node data_root = this->root.append_child("data");
	data_root.append_child("x").text().set(to_string(this->x).c_str());
	data_root.append_child("y").text().set(to_string(this->y).c_str());
	data_root.append_child("color").text().set(to_string(this->color).c_str());
}

MessageType MessageFactory::getMessageType(string xml_ser) {
	MessageBase mb;
	mb.parseXML(xml_ser);
	return mb.messageType;
}
