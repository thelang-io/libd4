/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "../include/d4/macro.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

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

#include "../include/d4/safe.h"
#include "../include/d4/ssl.h"
#include "../src/string.h"

#if !defined(D4_OS_WINDOWS)
  #define INVALID_SOCKET (-1)
  #define SOCKET_ERROR (-1)
#endif

static d4_str_t request (char *hostname, const char *request, size_t request_len) {
  struct addrinfo *addr = NULL;
  struct addrinfo hints;

  #if defined(D4_OS_WINDOWS)
    SOCKET fd;
  #else
    int fd;
  #endif

  SSL_CTX *ctx = NULL;
  SSL *ssl = NULL;
  char *buf = NULL;
  int read_bytes = 0;
  wchar_t *wide_buf;
  d4_str_t result;

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

  if (getaddrinfo(hostname, "443", &hints, &addr) != 0) {
    fwprintf(stderr, L"Failed to get address info.\n");
    goto L1;
  }

  fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);

  if (fd == INVALID_SOCKET) {
    fwprintf(stderr, L"Failed to create socket.\n");
    goto L2;
  }

  if (connect(fd, addr->ai_addr, addr->ai_addrlen) == SOCKET_ERROR) {
    fwprintf(stderr, L"Failed to connect.\n");
    goto L3;
  }

  ctx = SSL_CTX_new(TLS_client_method());

  if (ctx == NULL) {
    fwprintf(stderr, L"Failed to create SSL context.\n");
    goto L3;
  }

  ssl = SSL_new(ctx);
  SSL_set_fd(ssl, (int) fd);
  SSL_set_tlsext_host_name(ssl, hostname);

  if (SSL_connect(ssl) != 1) {
    fwprintf(stderr, L"Failed to connect to socket with SSL.\n");
    goto L4;
  }

  SSL_write(ssl, request, (int) request_len);
  SSL_shutdown(ssl);

  buf = d4_safe_alloc(1024);

  if ((read_bytes = SSL_read(ssl, buf, 1024)) < 0) {
    fwprintf(stderr, L"Failed to read from socket with SSL.\n");
    d4_safe_free(buf);
    buf = NULL;
    goto L4;
  }

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

  if (buf == NULL) {
    return d4_str_empty_val;
  }

  wide_buf = d4_safe_alloc((read_bytes + 1) * sizeof(wchar_t));

  for (int i = 0; i < read_bytes; i++) {
    wide_buf[i] = (wchar_t) buf[i];
  }

  wide_buf[read_bytes] = L'\0';
  result = d4_str_alloc(L"%ls", wide_buf);

  d4_safe_free(buf);
  d4_safe_free(wide_buf);

  return result;
}

static d4_str_t request_data (const d4_str_t response) {
  size_t data_start = 0;
  size_t data_check_end = response.len > 4 ? response.len - 3 : 0;

  for (size_t i = 0; i < data_check_end; i++) {
    if (
      response.data[i] == L'\r' &&
      response.data[i + 1] == L'\n' &&
      response.data[i + 2] == L'\r' &&
      response.data[i + 3] == L'\n'
    ) {
      data_start = i + 4;
    }
  }

  return d4_str_alloc(&response.data[data_start]);
}

static void test_ssl (void) {
  char template[] =
    "POST /echo HTTP/1.1\r\n"
    "Host: ci.thelang.io\r\n"
    "Content-Type: application/x-www-form-urlencoded\r\n"
    "Content-Length: 27\r\n"
    "\r\n"
    "field1=value1&field2=value2\r\n";

  d4_str_t a = request("ci.thelang.io", template, sizeof(template) / sizeof(template[0]));
  d4_str_t s = request_data(a);
  d4_str_t s_cmp = d4_str_alloc(L"field1=value1&field2=value2");

  assert(((void) "SSL works", d4_str_eq(s, s_cmp)));

  d4_str_free(a);
  d4_str_free(s);
  d4_str_free(s_cmp);
}

int main (void) {
  test_ssl();
}
