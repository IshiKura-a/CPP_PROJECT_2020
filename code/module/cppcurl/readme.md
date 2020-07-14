# CppCurl branch

## 描述

CppCurl模块将提供包装好的http请求方法。接口中包含发送公式识别请求和Latex公式渲染请求的API。其中token已经被加密。具体内容请参考CppCurl.h。

本模块已完成重构，将全局函数用静态类包装，并使用工厂方法隐藏了内部实现使用的函数。重构后头文件将不会暴露该库的内部结构。

## 编译方法

1. 打开工程内的CppCurl.sln

2. 将CppCurlDll设置为启动项目。修改工程->属性->VC++目录，将libcurl的包含目录和库目录修改至自己的配置。将rapidjson的包含目录修改至自己的配置。libcurl的库目录中需要存在libcurl.lib。将你的libcurl.dll覆盖./CppCurl/prebuilt/下的libcurl.dll。

3. 开始编译。注意**编译时选择的x86或x64务必要和你的libcurl相匹配**。
    * 如果你是64位的libcurl，此时应该能正常通过编译并生成CppCurl.dll，CppCurl.lib。
    * 如果你是32位的libcurl，你需要将生成配置改为x86并手动修改一些工程属性。请对照x64的配置属性修改。
    * 如果你没有可以编译libcurl的环境，./CppCurl/prebuilt/下提供了一份我编译好的64位的libcurl.dll和libcurl.lib。注意你仍然需要libcurl的头文件。

4. 该工程编译后会在.././CppCurl/x86(or x64)/Debug(or Release)/下生成CppCurl.dll, CppCurl.lib。注意生成的目录不是CppCurlDLL。

5. CppCurl.dll，CppCurl.lib和CppCurl.h现在可以用于动态链接。

## 测试方法

1. 编译CppCurlTest。

2. 如果编译正常，测试的结果应当是:
    * exe的同目录下产生直接写入的渲染结果formula.png。
    * exe的同目录下产生先写入buffer，再写成文件的渲染结果formula_buffer.png。这两份图片应是完全一致的。
    * 控制台分别打印由百度API和mathpix API返回的包含latex代码的json string。

## 当前进度

已完成
