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
#include "gtk/gtk.h"
#include "messages.hpp"
#include "connection_manager.hpp"

using namespace std;

int main(int argc, char *argv[]) {
	const std::string endpoint = "tcp://127.0.0.1:" + std::string(argv[1]);
	std::cout << "Starting server on " << endpoint << std::endl;
	sock.connect(endpoint);

	auto listener = std::async(std::launch::async, MessageHandler::listen);
	listener.get();

//	GtkWidget *window;
//	gtk_init (&argc, &argv);
//	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
//	gtk_window_set_title (GTK_WINDOW (window), "Visualizer");
//	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
//	gtk_widget_show (window);
//	gtk_main ();

	return 0;
}

