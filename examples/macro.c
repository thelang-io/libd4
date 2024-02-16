/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/macro.h>
#include <wchar.h>

int main (void) {
  #if defined(THE_OS_WINDOWS)
    wprintf(L"Hello from Windows!%lsPath separator: %ls%ls", THE_EOL, THE_PATH_SEP, THE_EOL);
  #elif defined(THE_OS_MACOS)
    wprintf(L"Hello from macOS!%lsPath separator: %ls%ls", THE_EOL, THE_PATH_SEP, THE_EOL);
  #elif defined(THE_OS_LINUX)
    wprintf(L"Hello from Linux!%lsPath separator: %ls%ls", THE_EOL, THE_PATH_SEP, THE_EOL);
  #endif

  return 0;
}
