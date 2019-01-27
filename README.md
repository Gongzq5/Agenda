# Agenda

## Agenda是什么

Agenda是一个会议管理系统，提供了会议管理的能力，包括创建会议，参与会议，退出会议，查询会议的功能（查询等提供了多种方式）。

这是大一的初级实训的项目，基本是个玩具啦，也不是很完善，放在这里作为纪念啦；虽然现在看来不怎么样，但是当时真是很痛苦，特别是被matrix制裁的时候，简直要砸电脑啊。

虽然挺简单，但是确实学会了不少东西，比如C++11的新特性，了解了很多（比如第一次接触到了lambda，还有auto什么的）；还有makefile的使用，虽然现在看来用处不是很大（也不常用，后来就忘了嘛，只能是吸收思想了）；然后学了一些项目组织的方式（各种文件夹，src，build，include，data...），这可能是最大的收获。

## 如何运行

注意！！要在Linux下运行（实训的系统好像是Ubuntu 12），我在Win10的Ubuntu子系统下运行也是没有问题的，但是Windows环境下`make`是会出现一些错误的（大概是参数问题，改`makefile`就可以了，应该不难）。

1. 使用`make`命令进行编译 
2. 使用`make run`进行运行 

btw, 可以使用`make clean`清除所有数据（包括编译文件）

## 如何使用

使用`make run`运行后，提供了比较完整的运行说明，有命令行界面！可以仔细看看

示例： 

```
-------------------Agenda-------------------
Action:
l        : log in by username and password.
r        : regist a user.
q        : quit agenda.
Agenda  :~$ l
[log in] [username] [password]
[log in] HelloU 123
[log in] succeed!

-------------------Agenda-------------------
Action :
o       - log out Agenda
dc      - delete Agenda account
lu      - list all Agenda users
cm      - create a meeting
amp     - add meeting particpator
rmp     - remove meeting particpator
rqm     - request to quit meeting
la      - list all meetings
las     - list all sponsor meetings
lap     - list all particpator meetings
qm      - query meeting by title
qt      - query meeting by time interval
dm      - delete meeting by title
da      - delete all meetings
--------------------------------------------

Agenda@HelloU:~# cm
[create meeting] [the number of participators]
[create meeting] 2
[create meeting] [please enter the participator 1 ]
[create meeting] HelloU
[create meeting] [please enter the participator 2 ]
[create meeting] HelloAgenda
[create meeting] [title] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]
[create meeting] GoodMeet 2018-01-22/10:22 2018-01-28/10:10
[create meeting] succeed!

-------------------Agenda-------------------
Action :
o       - log out Agenda
dc      - delete Agenda account
lu      - list all Agenda users
cm      - create a meeting
amp     - add meeting particpator
rmp     - remove meeting particpator
rqm     - request to quit meeting
la      - list all meetings
las     - list all sponsor meetings
lap     - list all particpator meetings
qm      - query meeting by title
qt      - query meeting by time interval
dm      - delete meeting by title
da      - delete all meetings
--------------------------------------------

Agenda@HelloU:~# la
[list all meetings]
title           sponsor start time              end time                participators
GoodMeet        HelloU  2018-01-22/10:22        2018-01-28/10:10        HelloU,HelloAgenda


-------------------Agenda-------------------
Action :
o       - log out Agenda
dc      - delete Agenda account
lu      - list all Agenda users
cm      - create a meeting
amp     - add meeting particpator
rmp     - remove meeting particpator
rqm     - request to quit meeting
la      - list all meetings
las     - list all sponsor meetings
lap     - list all particpator meetings
qm      - query meeting by title
qt      - query meeting by time interval
dm      - delete meeting by title
da      - delete all meetings
--------------------------------------------

Agenda@HelloU:~# qm
[query meeting] [title]
[query meeting] GoodMeet
title           sponsor start time              end time                participators
GoodMeet        HelloU  2018-01-22/10:22        2018-01-28/10:10        HelloU,HelloAgenda


-------------------Agenda-------------------
Action :
o       - log out Agenda
dc      - delete Agenda account
lu      - list all Agenda users
cm      - create a meeting
amp     - add meeting particpator
rmp     - remove meeting particpator
rqm     - request to quit meeting
la      - list all meetings
las     - list all sponsor meetings
lap     - list all particpator meetings
qm      - query meeting by title
qt      - query meeting by time interval
dm      - delete meeting by title
da      - delete all meetings
--------------------------------------------

Agenda@HelloU:~# o

-------------------Agenda-------------------
Action:
l        : log in by username and password.
r        : regist a user.
q        : quit agenda.
Agenda  :~$ q
```
