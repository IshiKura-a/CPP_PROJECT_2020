# How to modify the MVVM framework

## 添加数据成员

1. 在model中添加相应的数据成员声明，初始值，getter，setter（供view model调用，触发数据更新事件），setter for view model（model内部使用，不触发model向view的数据更新）；注册该数据成员更新事件并绑定view model的回调函数（notify，bindCallback）。

2. 在view model中添加相应的数据成员声明（类型为前端使用的类型，如QString），getter，setter（供view调用，将同步model中数据），model数据成员更新对应的回调事件（notified）；注册该数据成员更新事件并绑定view的回调函数（notify，bindCallback）。修改bindModel函数，在该函数内绑定model的数据变化事件。

3. 在view中添加相应的数据成员指针，getter pointer，setter pointer，data-getter setter，data-setter setter（绑定view model的getter，setter），view model数据成员更新对应的回调事件（notified）。在app中绑定view model的setter，getter。

## 在model中组合后端功能模块

1. 在model.h中添加该功能模块应当提供的功能的函数声明。

2. 在model.cpp中包含该功能模块的头文件，完成函数定义。

3. 以上操作在model中提供了后端的功能接口供view model操作。

## 添加view model功能函数

view model中的函数可以调用一个或多个model的函数。注意满足原子性。

1. 确认这个函数必须操作model，且无法通过调用已绑定的view model函数达到相同功能。

2. 在view model中添加相应的std::function，无参数的函数定义为WorkFunction，有参数的函数定义为WorkFunctionNoArg。

3. 在view model的bindFunction函数中添加该WorkFunction的具体代码。

## view绑定view model的功能函数

1. 在view中添加相应的std::function, 无参数的函数定义为WorkFunction，有参数的函数定义为WorkFunctionNoArg。建议使用与上一节第一步中同样的名字。

2. （可选）添加相应的类成员函数包装以上std::function。这一步不是必须的，但是由于WorkFunction的参数是std::any，增加一层包装可以使得view层明确这些功能函数的参数类型，提升代码可读性。

3. 添加相应的binder（std::function的setter），供初始化时绑定view model提供的函数指针。

4. 在app中添加代码，绑定对应的view model函数。
