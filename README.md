# CPP PROJECT 2020

## Description

This is a course project for ZJU C++ summer course. This project is implemented with MVVM(Model-View-ViewModel) design as the whole framework and Qt for its GUI.

## File Structure

Source code in `./code`.

* Solution file is in `./code/Project`.

* MVVM framework implementation is divided into `./code/model`, `./code/viewmodel` and `./code/view`. The initialization code of the framework is in `./code/app`. See also `./code/readme.md` about how to modify current MVVM framework or combine new module.

* Some used headers are in `./code/include`, used static libraries in `./code/lib` and used dynamic libraries in `./code/bin`. We haven't added all third-party codes into our project. For now, libcurl and rapidjson are still needed as external dependencies.

* Common used codes are in `./code/common`. Currently, `def.h` is about some widely used macro defines, and `notifiable.h` implements the notification part in MVVM framework. `common.h` is not used right now.

* The algorithm level implementation is in `./code/module`. It contains all modules we used in this project, and their document(if exists) as well.

Documents in `./doc`.

## Build

1. Open `./code/Project/Project.sln`.

2. Open Project Property, VC++ path. Adjust [libcurl](https://curl.haxx.se/libcurl/) and [rapidjson](https://github.com/Tencent/rapidjson) include and library path to your environment. A prebuilt(in win10 x64) libcurl.lib and libcurl.dll are provided in ./code/lib and ./code/bin if you are unable to compile libcurl, but you still need libcurl.h in your include path.

3. Open Qt Project Settings, adjust Qt Installation to your settings.

4. Build. There're 6 projects in the solution right now:
    * CppCurl is a wrapper for libcurl and is used by the other 3 projects.
    * CppCurlTest is a unit test project for CppCurl.
    * JsonParserTest is a unit test project for module JsonParser which parse the return value of image recognition API.
    * XMLParseTest is a unit test project for module XMLParser with parse the return value of formula calculation API.
    * latex_parser is not implemented and should not be used in any circumstances. It is designed as a local formula parsing and calculating module using `boost::spirit`.
    * Project is the main program.

    If you want to build the final application, you should at least build CppCurl and Project. It is highly recommended to run all unit tests too.
