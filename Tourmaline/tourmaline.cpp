/*
 * tourmaline.cpp
 *
 *  Created on: Aug 30, 2022
 *      Author: quarkhopper
 */

#include <zmq.hpp>
#include <zmq_addon.hpp>
#include <future>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>
#include <gtk-3.0/gtk/gtk.h>
#include "messages.hpp"

static std::vector<zmq::message_t> msgs;
static zmq::socket_t sock;

class MessageHandler {
public:
	void operator()() {
		msgs.clear();
		try
		{
			const auto ret = zmq::recv_multipart(
					sock, std::back_inserter(msgs));
			if (!ret)
			throw(std::runtime_error("recv_multipart returned abnormally."));
		}
		catch (const std::exception& e) {
			std::cout << "Exception occurred which trying to get messages: " << e.what() << std::endl;
		}
	}
};

int main(int argc, char *argv[]) {
	zmq::context_t ctx;
	sock = zmq::socket_t (ctx, zmq::socket_type::pull);
	const std::string endpoint = "tcp://127.0.0.1:" + std::string(argv[1]);
	std::cout << "Attempting connection on " << endpoint << std::endl;
	sock.connect(endpoint);
	auto handle = std::async(std::launch::async, MessageHandler());
	handle.get();

	for (int i = 0; i < msgs.size(); i++)
		std::cout << "Message: " << msgs[i].to_string() << std::endl;

	GtkWidget *window;
	gtk_init (&argc, &argv);
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Visualizer");
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	gtk_widget_show (window);
	gtk_main ();

	return 0;
}

