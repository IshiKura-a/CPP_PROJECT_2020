# CppCurl branch

## 描述

CppCurl模块将提供包装好的http请求方法

## 编译方法

打开sln后，将CppCurlDll设置为启动项目，注意修改工程属性，将libcurl的包含目录和库目录修改至自己的配置。libcurl的库目录中需要存在libcurl.lib，本工程生成目录下需要有libcurl.dll。

工程根目录下提供了一份我编译好的libcurl.dll。

该工程编译后会在相应目录生成CppCurl.dll, CppCurl.lib

请将CppCurl.dll放置在将要调用该库的应用程序的相同目录下，将CppCurl.lib添加到其他工程的依赖项，并注意包含CppCurl.h

例如在本例中，./CppCurl/下的CppCurl.lib需要手动放置（此处我已提前放置了编译好的lib）。

## 测试方法

sln下的CppCurl工程提供了一个简单的测试程序CppCurlTest。

注意在进行CppCurlDll的编译后，手动将生成目录的.lib和.dll放置到相应的文件夹中。

如果编译正常，您将会获得一份包含latex代码的json string。

## 当前进度

基本功能已完成。API key加密待实现。
