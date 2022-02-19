# Windows系统下Ubuntu wsl的简单使用指南

## Ubuntu wsl是什么？

* 一个可以简单安装的Ubuntu控制台终端

* 简单来说，是一个无需安装虚拟机就可以使用linux系统的应用程序



## 安装步骤

### 启动Windows功能

右击左下角的Windows图标，选择`Windows PowerShell(管理员) `，打开

输入以下指令：

```c++
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
```

### 从Microsoft Store商店下载

打开开始菜单中的Microsoft Store，搜索Ubuntu 18.04 LTS并下载安装

### 创建用户名与密码

打开刚刚下载的应用程序

等待几分钟，之后输入自定义的用户名和密码（这个会被多次使用，建议不要复杂）

PS：Linux下输入密码光标不会动，即不会变成“************”，这是正常的

### 文件夹路径

想在Ubuntu内运行程序，建议直接从根目录`/mnt/c`访问电脑C盘（可以`cd /mnt`进入该目录）

也可以将文件复制至Ubuntu能够访问的地方

`C:/Users/*Username*/AppData/Local/Packages/CanonicalGroupLimited.UbuntuonWindows_79rhkp1fndgsc/LocalState/rootfs`

（其中Username是你电脑的用户名）

将文件复制进这个根目录下的`/mnt`文件夹内即可使用



## 使用指南

### 换源

Ubuntu默认使用的不是中国的软件源，可能会造成下载速度缓慢与安装包破损等问题

在windows下打开文件资源管理器，进入上文的文件夹路径，进入根目录`roofts/`下的`etc/apt/`

先备份一份` sources.list `，防止换源失败 

用记事本打开`sources.list`文件，**删除全部内容**并将以下内容复制粘贴进去（源1与源2任选一个即可）

##### 源1 SJTU

```c++
deb http://mirror.sjtu.edu.cn/ubuntu/ focal main restricted
deb http://mirror.sjtu.edu.cn/ubuntu/ focal-updates main restricted
deb http://mirror.sjtu.edu.cn/ubuntu/ focal universe
deb http://mirror.sjtu.edu.cn/ubuntu/ focal-updates universe
deb http://mirror.sjtu.edu.cn/ubuntu/ focal multiverse
deb http://mirror.sjtu.edu.cn/ubuntu/ focal-updates multiverse
deb http://mirror.sjtu.edu.cn/ubuntu/ focal-backports main restricted universe multiverse
deb http://mirror.sjtu.edu.cn/ubuntu/ focal-security main restricted
deb http://mirror.sjtu.edu.cn/ubuntu/ focal-security universe
deb http://mirror.sjtu.edu.cn/ubuntu/ focal-security multiverse
```

##### 源2 aliyun

```c++
deb http://mirrors.aliyun.com/ubuntu/ bionic main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-security main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-security main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-updates main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-updates main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-backports main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-backports main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-proposed main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-proposed main restricted universe multiverse
```

**注意：粘贴进去的内容是与系统版本有关的！！！**如上源1中出现了focal字样 意味着这是一个ubuntu 20系列的源；例2中出现了bionic字样 意味着这是一个ubuntu 18系列的源。请对使用系统版本对应的源，也就是说，如果你想在ubuntu18.04中使用sjtu源，**你需要把源1中的focal都换成bionic**

*查看系统版本，请在ubuntu命令行中输入`lsb_release -a`*

`Ctrl+s`保存，在命令行中**按顺序**输入以下指令

如果遇到`Do you want to continue? [Y/n]`的提示，输入字母`y`（大小写均可）再`Enter`即可

```c++
sudo apt update
sudo apt upgrade
```

### 一些常用指令

注意Ubuntu的命令行

一些语法的解释

```c++
sudo//指用管理员权限运行后面的语句
apt//包管理
```

可运行的语句

```c++
sudo apt install *filename*//安装某个包（名称为filename）
cd foldername//进入某个文件夹,可以Tab补全
cd ..//退回上层文件夹
ls//显示当前目录下所有文件的名字
chmod +x filename//若运行filename时显示Permission denied，执行此命令可以开启权限,仅限可执行文件
cd /mnt//有些情况可能需要先进入/mnt目录
```

极不推荐的行为

```c++
sudo -s//进入root账户，十分不推荐，以及请注意root和普通是两个用户，安装的包是相互独立的
```



### 一些预备步骤

按照顺序，在命令行中输入以下指令即可（安装一些常用包）

```c++
sudo apt update
sudo apt upgrade
sudo apt install g++
sudo apt install valgrind
sudo apt install ubuntu-make
```

备注：若是root用户可不加sudo，但是不推荐

### 安利

Linux下的文本编辑软件  vim

```c++
sudo apt install vim
vim filename//打开文件
:q//退出
:q!//强制退出
:wq//保存退出
i//进入编辑模式
esc(指键盘的按键)//退出编辑模式
  
//vim还有很多强大的功能，甚至可以coding，
//你已经对vim和Google有了一定了解，来把我们刚刚学到的知识运用到实践中吧！
//试试看！
```





## 三个应用实例

### Linux下的编译

##### 编译常用选项：

###### 无选项编译链接

作用：将test.c预处理、汇编、编译并链接形成可执行文件。这里未指定输出文件，默认输出为a.out。

```
g++ test.cpp
```

`-o`:

将源文件预处理、汇编、编译并链接形成可执行文件test。-o选项用来指定输出文件的文件名。（该开关后需要紧跟输出文件名）

```
-o file_name
```

`-std`：

设置编译标准，如以c++14的标准编译

```
-std=c++14
```

`-O`：

开启优化（1~3）

```
-O2
```

###### 举例：

```
 g++ test.cpp -o test -std=c++14 -O2
```

以O2优化编译test.cpp生成可执行文件test，各开关的出现顺序无影响

##### 多文件一起编译

- 方法一：同上，在g++后增加需要编译的源文件

  ```
  g++ test.cpp test.h -o test -std=c++14 -O2
  ```

- 方法二：分别编译各个源文件，之后对编译后输出的目标文件链接。

  ```C++
  g++ -c testfun.cpp //将testfun.c编译成testfun.o
  g++ -c test.cpp //将test.c编译成test.o
  g++ testfun.o test.o -o test //将testfun.o和test.o链接成test
  ```

##### Cmake

使用clion编程的同学对Cmakelists一定很熟悉，在需要编译的工程文件夹下填写CMakeLists.txt（或者从clion中copy）

通过

```
cmake CMakeLists.txt
```

获得Makefile文件，再通过

```
make
```

获得这个project用make编译后的可执行文件（名字可在CMakeLists.txt中的project一栏中修改）

若linux环境中的编译器版本过低，也可修改CMakeLists.txt中的 version参数

add_executable()需要填上所有需要编译的源文件

##### makefile

//你已经对编译运行有了一定了解，来把我们刚刚学到的知识运用到实践中吧！
//试试看！
/doge
//其实make就好了，不要自己写（除非你很巨

###### makefile 编写规则：

（1）以“＃”开始的行为注释
（2）文件依赖关系为：
  target:components
  rule

### Valgrind检测内存泄露

通过`cd`命令进入需要测试的程序所在的文件夹。

编译程序获得可执行文件（比如名为`test`）

```
valgrind --tool=memcheck --leak-check=full ./test
```

备注：其他的开关如有需要可在文末提供的参考网站或其他网站上学习

#### 以matrix为例检测内存泄露

进入matrix所在文件夹

- 步骤一：cmake（只需进行一遍，确保CMAKElists.txt的完整性，生成Makefile，CMakeLists.txt修改后需要重新cmake）

```
cmake CMakeLists.txt
```

- 步骤二：make(根据Makefile编译可执行文件，当源码修改后需要重新make)

```
make
```

- 步骤三：valgrind

```
valgrind --tool=memcheck --leak-check=full ./MatrixOOP
```

部分反馈信息

（有泄漏）

```
==94== LEAK SUMMARY:
==94==    definitely lost: 300 bytes in 10 blocks
==94==    indirectly lost: 0 bytes in 0 blocks
==94==      possibly lost: 0 bytes in 0 blocks
==94==    still reachable: 0 bytes in 0 blocks
==94==         suppressed: 0 bytes in 0 blocks
```

（无泄漏）

```
==25490== 
==25490== HEAP SUMMARY:
==25490==     in use at exit: 0 bytes in 0 blocks
==25490==   total heap usage: 704 allocs, 704 frees, 119,484 bytes allocated
==25490== 
==25490== All heap blocks were freed -- no leaks are possible
==25490== 
==25490== For lists of detected and suppressed errors, rerun with: -s
==25490== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

```

根据反馈开启~~快乐的debug之旅~~



#### 可能的问题

##### 控制台被禁用

​	右击wsl窗口上框条，点击属性，在“选项”栏中找到“使用旧版控制台”，取消勾选。

#### 参考

valgrind：https://zhuanlan.zhihu.com/p/56538645

linux下的编译：https://blog.csdn.net/yinjiabin/article/details/7731817





*Written by:*

*Libro RainyMemory Sirius Walotta*

*感谢cong258258的订正*

**按字典序排列*

