# CppCurl branch

## 描述

CppCurl模块将提供包装好的http请求方法。接口中包含公式识别和Latex公式渲染请求的API。具体内容请参考CppCurl.h。

## 编译方法

1. 打开工程内的CppCurl.sln

2. 将CppCurlDll设置为启动项目。修改工程->属性->VC++目录，将libcurl的包含目录和库目录修改至自己的配置。libcurl的库目录中需要存在libcurl.lib。

3. 开始编译。注意**编译时选择x86或x64务必要和你的libcurl相匹配**。
    * 如果你是64位的libcurl，此时应该能正常通过编译并生成CppCurl.dll，CppCurl.lib。
    * 如果你是32位的libcurl，你需要将生成配置改为x86并手动修改一些工程属性。配置属性->常规->目标文件名改为CppCurl，C/C++->预处理器->预处理器定义中将CPPCURLDLL_EXPORTS改为CPPCURL_EXPORTS。
    * 如果你没有可以编译libcurl的环境，./libcurl_prebuilt/下提供了一份我编译好的64位的libcurl.dll和libcurl.lib。注意你仍然需要libcurl的头文件。

4. 该工程编译后会在.././CppCurl/x86(or x64)/Debug(or Release)/下生成CppCurl.dll, CppCurl.lib。注意生成的目录不是CppCurlDLL。

5. CppCurl.dll，CppCurl.lib和CppCurl.h现在可以用于动态链接。

## 测试方法

1. 将生成的CppCurl.lib放置在./CppCurl/目录下。

2. 将生成的CppCurl.dll放置在生成的exe同目录下。由于dll生成的目标路径是/CppCurl/...，因此这一步在这一测试程序中可以跳过。

3. 将libcurl.dll放置在生成的exe同目录下。

4. 开始编译CppCurlTest。

5. 如果编译正常，测试的结果应当是:
    * 工程目录下产生将渲染结果直接保存为文件的formula.png。
    * 工程目录下产生将渲染结果先存储为二进制数据，再手动存储为文件的formula_str.png。
    * 控制台打印一份由百度API返回的包含latex代码的json string。

## 当前进度

基本功能已完成。API key加密待实现。
