# CppCurl branch

## 描述

CppCurl模块将提供包装好的http请求方法。接口中包含发送公式识别请求，Latex公式渲染请求和公式计算请求的API。其中token已经被加密。具体内容请参考CppCurl.h。

本模块已完成重构，将全局函数用静态类包装，并使用工厂方法隐藏了内部实现使用的函数。重构后头文件将不会暴露该库的内部结构。

## 模块接口

参考`CppCurl.h`.
