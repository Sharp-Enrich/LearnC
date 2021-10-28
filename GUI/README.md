使用https://github.com/andlabs/libui/tree/alpha4.1


**配置libui库**
```
$ git clone git@github.com:andlabs/libui.git
$ cd libui
$ git checkout alpha4.1
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make tester        
$ make examples      
$ sudo cp out/libui.s* /usr/lib
$ sudo cp ../ui.h /usr/include
```

**编译**

```
$ gcc xxx.c -L /usr/lib -I /usr/include -l ui -o xxx
```

**API接口**

直接参考`ui.h`

**文档**

直接参考`example`