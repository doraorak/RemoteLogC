## INFO

RemoteLogC is a modified version of RemoteLog (https://github.com/Muirey03/RemoteLog) by Muirey03 that allows it to be used from .c files.
As a result, support for NSObjects is dropped.

This is mostly useful when you don't have access to your `printf` outputs, like ios applications without xcode.
## Usage

RemoteLogC supports most of the format specifiers of `printf` so it should be very easy to migrate to.

- Copy `RemoteLogC.h` to `$THEOS/include`
- Change the ip addresses in the `RemoteLogC.h` file to match your computer's ip address
- Include the header in any source files you want to use it in:
```
#include <RemoteLogC.h>
```
- Replace calls to `printf` with calls to `RLogC`:
```
RLogC("Test log: %(format specifier)", someVariable);
```
- Run the python server on your computer and watch the logs coming in :)
