/*
    Pablo Rodríguez <Nimeavles> 2023-2024

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to
   deal in the Software without restriction, including without limitation the
   rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
   sell copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
   IN THE SOFTWARE.
*/

#include "./core/errors.h"
#include "./utils/json_parser.h"
#include <netinet/in.h>
#include <sys/socket.h>

#define IP4 0

typedef u_int8_t u8;
typedef struct sockaddr_in sockaddr_in;

typedef struct server_socket_state {
  u_int port, socket, client_socket;
  sockaddr_in address;
} server_socket_state;

typedef struct client_socket_state {
  sockaddr_in address;
} client_socket_state;

server_socket_state server_state;
client_socket_state client_state;

/*
    Create the socket where the connections will arrive.
*/

static int open_server_socket() {
  const int opt = 1;

  if ((server_state.socket = socket(AF_INET, SOCK_STREAM, IP4)) < 0)
    return SOCK_CREATE_ERR;

  if (setsockopt(server_state.socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                 &opt, sizeof(opt)) < 0)
    return SOCK_SETSOCKOPT_ERR;

  server_state.port = 80;

  server_state.address.sin_family = AF_INET;
  server_state.address.sin_addr.s_addr = INADDR_ANY;
  server_state.address.sin_port = htons(server_state.port);

  if (bind(server_state.socket, (struct sockaddr *)&server_state.address,
           sizeof(server_state.address)) < 0)
    return SOCK_BIND_ERR;

  if (listen(server_state.socket, 50) < 0)
    return SOCK_LISTEN_ERR;

  if ((server_state.client_socket =
           accept(server_state.socket, (struct sockaddr *)&client_state.address,
                  (socklen_t *)sizeof(client_state.address))) < 0)
    return SOCK_ACCEPT_ERR;

  return NO_ERROR_EXIT;
}

int main(int argc, char *argv[]) {
  config_data data_from_config_file;
  read_json_config_file(argv[argc - 1], &data_from_config_file);
}