#ifndef AGENDAUI_H
#define AGENDAUI_H

#include <iostream>
#include <string>
#include "Storage.hpp"
#include "AgendaService.hpp"
#include "User.hpp"
#include "Meeting.hpp"
#include "Date.hpp"

using std::cout;
using std::cin;
using std::endl;

class AgendaUI {
 public:
  AgendaUI() {
    m_userName = m_userPassword = "";
  }
  void OperationLoop(void) {
  	while (true) {
      cout << "\n-------------------Agenda-------------------\n";
      cout << "Action: \n";
      cout << "l\t : log in by username and password.\n";
      cout << "r\t : regist a user.\n";
      cout << "q\t : quit agenda.\n";
      cout << "Agenda\t:~$ ";
  		std::string command;
      cin >> command;
  		if      (command == "q") break;
      else if (command == "l") userLogIn();
      else if (command == "r") userRegister();
      else {cout << "Disallowed request.\n";}
  	}
  }

 private:
  /**
   * constructor
   */
  void startAgenda(void) {

  }

  /**
   * catch user's operation
   * @return the operation
   */
  std::string getOperation() {
    cout << "\n-------------------Agenda-------------------\n"
         << "Action :\n"
         << "o\t- log out Agenda\n"
         << "dc\t- delete Agenda account\n"
         << "lu\t- list all Agenda users\n"
         << "cm\t- create a meeting\n"
         << "amp\t- add meeting particpator\n"
         << "rmp\t- remove meeting particpator\n"
         << "rqm\t- request to quit meeting\n"
         << "la\t- list all meetings\n"
         << "las\t- list all sponsor meetings\n"
         << "lap\t- list all particpator meetings\n"
         << "qm\t- query meeting by title\n"
         << "qt\t- query meeting by time interval\n"
         << "dm\t- delete meeting by title\n"
         << "da\t- delete all meetings\n"
         << "--------------------------------------------\n"
         << "\nAgenda@" << m_userName << ":~# ";
  	std::string command;
  	std::cin >> command;
  	return command;
  }

  /**
   * execute the operation
   * @return if the operationloop continue
   */
  bool executeOperation(const std::string &t_operation) {
    if (t_operation == "o") {
      return false;
    } 
    else if (t_operation == "dc") {
      deleteUser();
      return false;
    } 
    else if (t_operation == "lu") {
      listAllUsers();
      return true;
    }
    else if (t_operation == "cm") {
      createMeeting();
      return true;
    }
    else if (t_operation == "amp") {
      addMeetingParticipator();
      return true;
    }
    else if (t_operation == "rmp") {
      removeMeetingParticipator();
      return true;
    }
    else if (t_operation == "rqm") {
      quitMeeting();
      return true;
    }
    else if (t_operation == "la") {
      listAllMeetings();
      return true;
    }
    else if (t_operation == "las") {
      listAllSponsorMeetings();
      return true;
    }
    else if (t_operation == "lap") {
      listAllParticipateMeetings();
      return true;
    }
    else if (t_operation == "qm") {
      queryMeetingByTitle();
      return true;
    }
    else if (t_operation == "qt") {
      queryMeetingByTimeInterval();
      return true;
    }
    else if (t_operation == "dm") {
      deleteMeetingByTitle();
      return true;
    }
    else if (t_operation == "da") {
      deleteAllMeetings();
      return true;
    }
    else {
      cout << "Cannot recognize your command, please input again!\n";
      return true;
    }
    return false;
  }

  /**
   * user Login
   */
  void userLogIn(void) {
  	std::string userName, passWord;
  	cout << "[log in] [username] [password]\n";
    cout << "[log in] ";
  	cin >> userName >> passWord;
    try {
      m_agendaService.userLogIn(userName, passWord);
  	  cout << "[log in] ";
      cout << "succeed!\n";
      m_userName = userName;
      m_userPassword = passWord;
      while (executeOperation(getOperation()));
    } catch (std::string w_info) {
      cout << "[log in] " << w_info << endl;
    }

  }

  /**
   * user regist
   */
  void userRegister(void) {
  	std::string userName, passWord, email, phone;
  	cout << "[register] [user name] [password] [email] [phone]\n";
    cout << "[register] ";
  	cin >> userName >> passWord >> email >> phone;
  	try {
      m_agendaService.userRegister(userName, passWord, email, phone);
      cout << "[user register] succeed!\n";
      // m_userName = userName;
      // m_userPassword = passWord;
      while (executeOperation(getOperation()));
    } catch (std::string w_info) {
      cout << "[register] " << w_info << endl;
    }
  }

  /**
   * user logout
   */
  void userLogOut(void) {
    cout << "[log out] succeed!\n";
    m_userName = m_userPassword = "";
  }

  /**
   * quit the Agenda
   */
  void quitAgenda(void) {
    cout << "[quit] succeed!\n";
  }

  /**
   * delete a user from storage
   */
  void deleteUser(void) {
    m_agendaService.deleteUser(m_userName, m_userPassword);
    cout << "[delete agenda account] succeed!\n";
    m_userName = m_userPassword = "";
  }

  /**
   * list all users from storage
   */
  void listAllUsers(void) {
    std::list<User> tmp(m_agendaService.listAllUsers());
    cout << "[list all users]\n";
    cout << "name\temail\tphone\n";
    for (auto it : tmp) {
      cout << it.getName() << '\t';
      cout << it.getEmail() << '\t';
      cout << it.getPhone() << '\n';
    }
  }

  /**
   * user create a meeting with someone else
   */
  void createMeeting(void) {
    int number = 0;
    std::vector<std::string> participators;
    cout << "[create meeting] " << "[the number of participators]\n";
    cout << "[create meeting] ";
    cin >> number;
    for (int i=1; i<=number; i++) {
      cout << "[create meeting] " << "[please enter the participator " << i << " ]\n";
      cout << "[create meeting] ";
      std::string tmp;
      cin >> tmp;
      participators.push_back(tmp);
    }
    cout << "[create meeting] " << "[title] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n";
    cout << "[create meeting] ";
    std::string title, s_date, e_date;
    cin >> title >> s_date >> e_date;
    try {
      m_agendaService.createMeeting(m_userName, title, s_date, e_date, participators);
      cout << "[create meeting] " << "succeed!\n";
    } catch (std::string w_info) {
      cout << "[create meeting] " << w_info << endl;
    }
  }

  /**
   * sponsor add a participator to the meeting
   */
  void addMeetingParticipator(void) {
    std::string title, particpator;
    try {
      cout << "[add particpator] [meeting title] [particpator username]\n"
           << "[add particpator] "; 
      cin >> title >> particpator;
      m_agendaService.addMeetingParticipator(m_userName, title, particpator);
      cout << "[add particpator] succeed!\n";
    } catch (std::string w_info) {
      cout << "[add particpator] " << w_info << endl;
    }
  }

  /**
   * sponsor add a participator to the meeting
   */
  void removeMeetingParticipator(void) {
    while (true) {
      cout << "[remove particpator] [meeting title] [particpator username]\n"
           << "[remove particpator] ";
      std::string title, username;
      cin >> title >> username;
      try {
        m_agendaService.removeMeetingParticipator(m_userName, title, username);
        cout << "[remove particpator] succeed!" << endl;
        return ;
      } catch (std::string w_info) {
        cout << "[remove particpator] " << w_info << endl;
        std::string w_command;
        cout << "Input again, please input \"r\"!\nDo other operation, please press any key.";
        cin >> w_command;
        if (w_command == "r") continue;
        else return ; 
      }
    }
  }

  /**
   * user quit from meeting
   */
  void quitMeeting(void) {
    cout << "[quit meeting] [meeting title]\n"
         << "[quit meeting] ";
    std::string title;
    cin >> title;
    try {
      m_agendaService.quitMeeting(m_userName, title);
      cout << "[quit meeting] succeed!\n";
      return;
    } catch (std::string w_info) {
      cout << "[quit meeting] " << w_info << endl;
    }
  }

  /**
   * list all meetings from storage
   */
  void listAllMeetings(void) {
    cout << "[list all meetings]\n";
    std::list<Meeting> tmp = m_agendaService.listAllMeetings(m_userName);
    printMeetings(tmp);
  }

  /**
   * list all meetings that this user sponsored
   */
  void listAllSponsorMeetings(void) {
    cout << "[list all sponsor meetings]\n\n";
    std::list<Meeting> tmp = m_agendaService.listAllSponsorMeetings(m_userName);
    printMeetings(tmp);
  }

  /**
   * list all meetings that this user take part in
   */
  void listAllParticipateMeetings(void) {
    cout << "[list all particpator meetings]\n\n";
    std::list<Meeting> tmp = m_agendaService.listAllParticipateMeetings(m_userName);
    printMeetings(tmp);
  }

  /**
   * search meetings by title from storage
   */
  void queryMeetingByTitle(void) {
    cout << "[query meeting] [title]\n"
         << "[query meeting] ";
    std::string title;
    cin >> title;
    std::list<Meeting> tmp = m_agendaService.meetingQuery(m_userName, title);
    printMeetings(tmp);
  }

  /**
   * search meetings by timeinterval from storage
   */
  void queryMeetingByTimeInterval(void) {
    cout << "[query meeting] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n"
         << "[query meeting] ";
    std::string s_date, e_date;
    cin >> s_date >> e_date;
    std::list<Meeting> tmp = m_agendaService.meetingQuery(m_userName, s_date, e_date);
    printMeetings(tmp);
  }

  /**
   * delete meetings by title from storage
   */
  void deleteMeetingByTitle(void) {
    cout << "[delete meeting] [title]\n"
         << "[delete meeting] ";
    std::string title;
    cin >> title;
    try {
      m_agendaService.deleteMeeting(m_userName, title);
      cout << "[delete meeting] succeed!\n";
    } catch (std::string w_info) {
      cout << "[delete meeting] " << w_info << endl;
    }
  }

  /**
   * delete all meetings that this user sponsored
   */
  void deleteAllMeetings(void) {
    m_agendaService.deleteAllMeetings(m_userName);
    cout << "[delete meeting] succeed!\n";
  }

  /**
   * show the meetings in the screen
   */
  void printMeetings(const std::list<Meeting> &t_meetings) {
    cout << "title\t\tsponsor\tstart time\t\tend time\t\tparticipators\n";
    for (auto it : t_meetings) {
      cout << it.getTitle() << '\t';
      cout << it.getSponsor() << '\t';
      cout << Date::dateToString(it.getStartDate()) << '\t';
      cout << Date::dateToString(it.getEndDate()) << '\t';
      std::vector<std::string> t_partic = it.getParticipator();
      cout << *t_partic.begin();
      for (auto partic = t_partic.begin()+1; partic != t_partic.end(); partic++) {
        cout << ',' << *partic;
      }
      cout << endl;
    }
    cout << endl;
  }
  // dates
  std::string m_userName;
  std::string m_userPassword;
  AgendaService m_agendaService;
};

#endif