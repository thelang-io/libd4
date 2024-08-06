/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <d4/macro.h>
#include <wchar.h>

int main (void) {
  #if defined(D4_OS_WINDOWS)
    wprintf(L"Hello from Windows!%lsPath separator: %ls%ls", D4_EOL, D4_PATH_SEP, D4_EOL);
  #elif defined(D4_OS_MACOS)
    wprintf(L"Hello from macOS!%lsPath separator: %ls%ls", D4_EOL, D4_PATH_SEP, D4_EOL);
  #elif defined(D4_OS_LINUX)
    wprintf(L"Hello from Linux!%lsPath separator: %ls%ls", D4_EOL, D4_PATH_SEP, D4_EOL);
  #endif

  return 0;
}
