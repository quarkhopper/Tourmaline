#include <iostream>
#include <string>
#include "messages.hpp"

using namespace std;
using namespace torm;

int main() {
	PutPointMessage msg_tx;
	msg_tx.x = 1;
	msg_tx.y = 2;
	msg_tx.color = 3;

	string xml_ser = msg_tx.getXML();
	cout << "TX: " << xml_ser << endl;

	auto msg_rx = MessageFactory::createMessage<PutPointMessage>(xml_ser);
	cout << "RX:"  << msg_rx->getXML() << endl;
}

