/*
  Pablo Rodríguez <Nimeavles> 2023-2024

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "server.hpp"
#include "../errors.hpp"
#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>

#define MAX_EVENTS 10
#define POLLING_TIMEOUT 3000

server_socket_state server_state;
client_socket_state client_state;
config_data *server_config;

/*
    Create the socket where the connections will arrive.
*/

static int create_server_socket() {
  static constexpr int opt = 1;

  if ((server_state.socket = socket(AF_INET, SOCK_STREAM, IP4)) < 0) {
    close(server_state.socket);
    return SOCK_CREATE_ERR;
  }

  if (setsockopt(server_state.socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                 &opt, sizeof(opt)) < 0) {
    close(server_state.socket);
    return SOCK_SETSOCKOPT_ERR;
  }

  server_state.port = server_config->port;

  server_state.address.sin_family = AF_INET;
  server_state.address.sin_addr.s_addr = INADDR_ANY;
  server_state.address.sin_port = htons(server_state.port);

  if (bind(server_state.socket, (struct sockaddr *)&server_state.address,
           sizeof(server_state.address)) < 0) {
    close(server_state.socket);
    return SOCK_BIND_ERR;
  }

  if (listen(server_state.socket, 50) < 0) {
    close(server_state.socket);
    return SOCK_LISTEN_ERR;
  }

  return NO_ERROR_EXIT;
}

int handle_multiple_connections(config_data *config_file_info) {
  // Make global the config of the server
  server_config = config_file_info;

  int epoll_fd, err;
  struct epoll_event event, events[MAX_EVENTS];

  // Create an epoll instance
  if ((epoll_fd = epoll_create1(EPOLL_CLOEXEC)) < 0) {
    close(epoll_fd);
    return EPOLL_CREATE_ERR;
  }

  // Set up the server socket where connections will arrive
  if ((err = create_server_socket()) != 0) {
    close(epoll_fd);
    return err;
  };

  // Set up epoll event for polling the server socket
  event.data.fd = server_state.socket;
  event.events = EPOLLIN;

  if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_state.socket, &event) < 0) {
    close(epoll_fd);
    return EPOLL_ADD_ERR;
  }

  std::cout << "Listening for connections on port: " << server_config->port
            << std::endl;

  // Polling connections
  while (true) {
    int events_queued =
        epoll_wait(epoll_fd, events, MAX_EVENTS, POLLING_TIMEOUT);

    if (events_queued == 0) {
      continue;
    }

    for (int i = 0; i < events_queued; i++) {
      int fd = events[i].data.fd;

      if (fd == server_state.socket) {

        if ((server_state.client_socket = accept(
                 server_state.socket, (struct sockaddr *)&client_state.address,
                 (socklen_t *)sizeof(client_state.address))) < 0) {
          close(server_state.socket);
          return SOCK_ACCEPT_ERR;
        }

        if (server_state.client_socket < 0) {
          close(server_state.client_socket);
          return SOCK_CREATE_ERR;
        }

        event.data.fd = fd;
        event.events = EPOLLIN;

        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_state.client_socket,
                      &event) < 0) {
          close(server_state.client_socket);
        }
        continue;
      } else {
        /* TODO: create a prefork working model and implement it here*/
      }
    }
  }

  return NO_ERROR_EXIT;
}