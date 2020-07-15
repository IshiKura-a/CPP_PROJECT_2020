# CPP_PROJECT_2020

## File Structure

Source code in ./code . See also ./code/readme.md about how to modify current MVVM framework.

Documents in ./doc .

## Build

1. Open ./code/Project/Project.sln.

2. Open Project Property, VC++ path. Adjust [libcurl](https://curl.haxx.se/libcurl/) and [rapidjson](https://github.com/Tencent/rapidjson) include and library path to your environment. Copy your libcurl.dll to ./code/bin. A prebuilt(in win10 x64) libcurl.lib and libcurl.dll are provided in ./code/lib and ./code/bin if you are unable to compile libcurl, but you still need libcurl.h in your include path.

3. Open Qt Project Settings, adjust Qt Installation to your settings.

4. Build. There're 4 projects in the solution right now. CppCurl is a wrapper for libcurl and is used by the other 3 projects. CppCurlTest is a unit test project for CppCurl. JsonParserTest is a unit test project for module JsonParser which parse the return value of image recognition API. Project is the main program.
