# Agenda

## 如何运行
1. 使用make命令进行编译 
2. 使用make run进行运行 

btw, 可以使用make clean清除所有数据（包括编译文件）

## 如何使用

使用make run运行后，提供了比较完整的运行说明，有命令行界面！可以仔细看看

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
