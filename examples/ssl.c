/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "../include/d4/macro.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#if defined(D4_OS_WINDOWS)
  #include <winsock2.h>
  #include <ws2tcpip.h>
  #include <windows.h>
#else
  #include <netdb.h>
  #include <netinet/in.h>
  #include <sys/socket.h>
  #include <unistd.h>
#endif

#include "../include/d4/ssl.h"

#if !defined(D4_OS_WINDOWS)
  #define INVALID_SOCKET (-1)
  #define SOCKET_ERROR (-1)
#endif

int main (void) {
  char *port = "443";
  char *hostname = "thelang.io";
  const char *template = "GET / HTTP/1.1\r\n\r\n";

  bool failed = false;
  struct addrinfo *addr = NULL;
  struct addrinfo hints;

  #if defined(D4_OS_WINDOWS)
    SOCKET fd;
  #else
    int fd;
  #endif

  SSL_CTX *ctx = NULL;
  SSL *ssl = NULL;

  #if defined(D4_OS_WINDOWS)
    WSADATA w;

    if (WSAStartup(MAKEWORD(2, 2), &w) != 0) {
      fwprintf(stderr, L"Failed to start WSA.\n");
      goto L1;
    }
  #endif

  SSL_library_init();

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  if (getaddrinfo(hostname, port, &hints, &addr) != 0) {
    failed = true;
    fwprintf(stderr, L"Failed to get address info.\n");
    goto L1;
  }

  fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);

  if (fd == INVALID_SOCKET) {
    failed = true;
    fwprintf(stderr, L"Failed to create socket.\n");
    goto L2;
  }

  if (connect(fd, addr->ai_addr, addr->ai_addrlen) == SOCKET_ERROR) {
    failed = true;
    fwprintf(stderr, L"Failed to connect.\n");
    goto L3;
  }

  if (strcmp(port, "443") == 0) {
    ctx = SSL_CTX_new(TLS_client_method());

    if (ctx == NULL) {
      failed = true;
      fwprintf(stderr, L"Failed to create SSL context.\n");
      goto L3;
    }

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, (int) fd);
    SSL_set_tlsext_host_name(ssl, hostname);

    if (SSL_connect(ssl) != 1) {
      failed = true;
      fwprintf(stderr, L"Failed to connect to socket with SSL.\n");
      goto L4;
    }
  }

  SSL_write(ssl, template, (int) strlen(template));
  SSL_shutdown(ssl);

L4:
  SSL_free(ssl);
  SSL_CTX_free(ctx);
L3:
  #if defined(D4_OS_WINDOWS)
    closesocket(fd);
  #else
    close(fd);
  #endif
L2:
  freeaddrinfo(addr);
L1:

  return failed ? 1 : 0;
}
