1. 进程是*具有独立功能的程序*关于*某个数据集合*上的**一次运行活动**
  
2. 进程与程序区别
	- 程序是静态概念(是指令的有序集合，“程序文件”)；
	  进程是动态概念(动态产生，动态消亡)；

	- 进程是一个程序的一次执行活动，
	  一个程序可以对应多个进程。
		
	- 进程是一个独立的活动单位；
	  进程是竞争系统资源的基本单位。

3. 进程状态
	OS把一个进程的执行过程，分为几个不同的阶段(状态):
		就绪态(Ready): 准备工作已经做好，只要有cpu就可以执行
		运行态(Running): cpu正在执行这个进程的指令
		阻塞态(Blocking,等待 waiting): 进程正在等待其他的外部事件
    - "就绪队列": Ready Queue
		所有处于“Ready ”状态的进程，都在一个“后备队列”
		
		"调度程序": 负责确定下一个进入“Running”状态的进程。
		
	- "调度策略": "调度算法"
		分时系统: 调度策略以“时间片轮转”为主要策略的系统
				“时间片轮转”：　分时。每个进程执行一段时间("时间片")
				如:	大部分桌面系统，如: linux, android, windows,
							macos, unix, ...

		实时系统：调度策略以“实时策略”为主要策略的系统
			"实时策略": 每次调度都取优先级最高的那个进程执行，
					直到这个进程执行完毕或它主动放弃cpu或其他更高
					优先级的进程抢占。
                    如: ucos, freeRTOS,....

4. linux进程地址空间布局
	“分段”　：分不同的逻辑区域
	linux对进程的数据进行分段管理，不同的属性的数据，存储
	在不同的“内存段”中。不同的“内存段(内存区域)”的属性及管理
	方法不一样。
	
	.text
		主要存放代码。
		只读并且共享，这段内存在程序运行期间(进程存活期间)，不会释放的。
		"代码段"  随程序持续性(随进程持续性)
	.data
		数据段。
		主要存放程序的已经初始化的全局变量和已经初始化的static变量。
		可读可写，这段内存在进程运行期间，一直存在。随进行持续性。
     - **全局变量和static变量生存期相同,作用域不同**,另外，在 C++ 中，需要一个数据对象为整个类而非某个对象服务,同时又力求不破坏类的封装性,即要求此成员隐藏在类的内部，对外不可见时，可将其定义为静态数据。
      [C/C++ 中 static 的用法全局变量与局部变量](https://www.runoob.com/w3cnote/cpp-static-usage.html#:~:text=%EF%BC%881%EF%BC%89%E5%85%A8%E5%B1%80%E5%8F%98%E9%87%8F%E5%92%8C%E5%85%A8%E5%B1%80%E9%9D%99%E6%80%81%E5%8F%98%E9%87%8F%E7%9A%84%E5%8C%BA%E5%88%AB%201%EF%BC%89%E5%85%A8%E5%B1%80%E5%8F%98%E9%87%8F%E6%98%AF%E4%B8%8D%E6%98%BE%E5%BC%8F%E7%94%A8%20static,%E4%BF%AE%E9%A5%B0%E7%9A%84%E5%85%A8%E5%B1%80%E5%8F%98%E9%87%8F%EF%BC%8C%E5%85%A8%E5%B1%80%E5%8F%98%E9%87%8F%E9%BB%98%E8%AE%A4%E6%98%AF%E6%9C%89%E5%A4%96%E9%83%A8%E9%93%BE%E6%8E%A5%E6%80%A7%E7%9A%84%EF%BC%8C%E4%BD%9C%E7%94%A8%E5%9F%9F%E6%98%AF%E6%95%B4%E4%B8%AA%E5%B7%A5%E7%A8%8B%EF%BC%8C%E5%9C%A8%E4%B8%80%E4%B8%AA%E6%96%87%E4%BB%B6%E5%86%85%E5%AE%9A%E4%B9%89%E7%9A%84%E5%85%A8%E5%B1%80%E5%8F%98%E9%87%8F%EF%BC%8C%E5%9C%A8%E5%8F%A6%E4%B8%80%E4%B8%AA%E6%96%87%E4%BB%B6%E4%B8%AD%EF%BC%8C%E9%80%9A%E8%BF%87%20extern%20%E5%85%A8%E5%B1%80%E5%8F%98%E9%87%8F%E5%90%8D%E7%9A%84%E5%A3%B0%E6%98%8E%EF%BC%8C%E5%B0%B1%E5%8F%AF%E4%BB%A5%E4%BD%BF%E7%94%A8%E5%85%A8%E5%B1%80%E5%8F%98%E9%87%8F%E3%80%82)
    .bss
		数据段。
		主要存放程序的没有初始化的全局变量和没有初始化的static变量。
		可读可写，这段内存在进程运行期间，一直存在。随进程持续性。
		.bss段，在进程初始化时，(可能)全部初始化为0.
		
	.rodata
		只读数据段。
		主要存放程序中的只读数据(如: 字符串常量)。
		只读。这段内存在进程运行期间，一直存在。随进程持续性。
		
	栈空间(stack)
		主要是存放局部变量(非static的局部变量)
		可读可写。这段空间，会自动释放(代码块执行完了，代码块中的局部变量
		的空间就会自动释放)。随代码块持续性。
		
		返回一个局部变量的地址，是有问题。就是这个原因。
		
	堆(heap)空间:　动态内存空间
		主要malloc/realloc/calloc动态分配的空间。
		可读可写的，这段内存在进行运行期间，一旦分配，就
		会一直存在，直到你手动free或进程消亡。
	  - 防止“内存泄漏” /"垃圾内存"

5.	linux下进程相关的API函数
	(1) 创建一个新进程
		fork
            进程里面包含什么东西?	
				系统数据
				用户数据
				指令
				
			fork这个函数在创建子进程时:
				copy了父进程的数据和指令 !!!!!
					父进程的变量，数据对象，
					标准IO缓冲区
					文件描述符
					……
				copy完了后，父子进程就独立。
				
			fork成功时，就会有两个进程在执行当前的代码!!!!!!
			所以为了区分是父进程，还是子进程，fork调用一次有两次返回
				一个父进程返回
				一个子进程返回
				
			通过fork的不同的返回值，来区分到底是父进程返回，还是子进程返回。
		
	- NAME
       fork - create a child process

	- SYNOPSIS
       #include <unistd.h>
       pid_t fork(void);
			- 返回值:
				如果失败返回-1,同时errno被设置。
				如果成功：
					父进程返回　子进程的pid(>0)
					子进程返回　0
					
				
			- fork的实现的伪代码：
			pid_t fork()
			{
				clone(); //克隆，一旦成功，就会有两个进程往下执行
						// 父进程，　子进程
						
				if (父进程)
				{
					return 子进程的pid(>0) ;
				}
				else if (子进程)
				{
					return 0;
				}
			}
			
