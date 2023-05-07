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

/*
    Exit errors defined when setting up a socket.
*/

#pragma once

#define NO_ERROR_EXIT 0
// Socket errors
#define SOCK_CREATE_ERR 1
#define SOCK_SETSOCKOPT_ERR 2
#define SOCK_BIND_ERR 3
#define SOCK_LISTEN_ERR 4
#define SOCK_ACCEPT_ERR 5
// Epoll errors
#define EPOLL_CREATE_ERR 6
#define EPOLL_ADD_ERR 7