#include "Storage.hpp"
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <memory>
#include <string>
#include "Path.hpp"
#include "Meeting.hpp"
using std::cout;
using std::endl;
std::shared_ptr<Storage> Storage::m_instance = nullptr;
/**
*   default constructor
*/
Storage::Storage() {
  m_dirty = false;
  readFromFile();
}

/**
*   read file content into memory
*   @return if success, true will be returned
*/
bool Storage::readFromFile(void) {
  std::ifstream ifsu(Path::userPath);
  std::string tmp;
  if (!ifsu.is_open()) return false;
  while (!ifsu.eof())
  {
    std::string username, password, email, phone;
    getline(ifsu, username, '\"');
    if (ifsu.eof()) break;
    getline(ifsu, username, '\"');
    getline(ifsu, password, '\"');
    getline(ifsu, password, '\"');
    getline(ifsu, email, '\"');
    getline(ifsu, email, '\"');
    getline(ifsu, phone, '\"');
    getline(ifsu, phone, '\"');
    m_userList.push_back(User(username, password, email, phone));
  }

  std::ifstream ifsm(Path::meetingPath);
  if (!ifsm.is_open()) return false;
  std::string sponsor, startdate, enddate, title, participator;
  while (!ifsm.eof()) {
    getline(ifsm, sponsor, '\"');
    if (ifsm.eof()) break;
    getline(ifsm, sponsor, '\"');  
    getline(ifsm, participator, '\"');     
    getline(ifsm, participator, '\"'); 
    std::stringstream temp_is;
    temp_is << participator;
    std::vector<std::string> participators;
    while (!temp_is.eof()) {
      std::string t;
      getline(temp_is, t, '&');
      participators.push_back(t);
    }
    getline(ifsm, startdate, '\"'); 
    getline(ifsm, startdate, '\"');  
    getline(ifsm, enddate, '\"'); 
    getline(ifsm, enddate, '\"'); 
    getline(ifsm, title, '\"'); 
    getline(ifsm, title, '\"'); 
    Date s(startdate), e(enddate);
    m_meetingList.push_back(Meeting(sponsor, participators, s, e, title));
  }
}

/**
*   write file content from memory
*   @return if success, true will be returned
*/
bool Storage::writeToFile(void) {

  std::ofstream ofsu;
  ofsu.open(Path::userPath);
  for (auto it = m_userList.begin(); it != m_userList.end(); it++) {
    ofsu << "\"" << it->getName() << "\",";
    ofsu << "\"" << it->getPassword() << "\",";
    ofsu << "\"" << it->getEmail() << "\",";
    ofsu << "\"" << it->getPhone() << "\"\n";
  } 

  std::ofstream ofsm;
  ofsm.open(Path::meetingPath);
  for (auto it = m_meetingList.begin(); it != m_meetingList.end(); it++) {
    ofsm << "\"" << it->getSponsor() << "\",";
    std::vector<std::string> tmp = it->getParticipator();
    ofsm << "\"";
    for (auto itt = tmp.begin(); itt != tmp.end(); itt++) {
      ofsm << *itt;
      if (itt != tmp.end()-1) ofsm << "&";
    }
    ofsm << "\",";
    ofsm << "\"" << Date::dateToString(it->getStartDate()) << "\",";
    ofsm << "\"" << Date::dateToString(it->getEndDate()) << "\",";
    ofsm << "\"" << it->getTitle() << "\"\n";
  }

}

/**
* get Instance of storage
* @return the pointer of the instance
*/
std::shared_ptr<Storage> Storage::getInstance(void) {
  if (m_instance == nullptr) {
    m_instance = static_cast<std::shared_ptr<Storage> >(new Storage);
  } 
  return m_instance;
}

/**
*   destructor
*/
Storage::~Storage() {
  sync();
}

// CRUD for User & Meeting
// using C++11 Function Template and Lambda Expressions

/**
* create a user
* @param a user object
*/
void Storage::createUser(const User &t_user) {
  m_userList.push_back(t_user);
  m_dirty = true;
}

/**
* query users
* @param a lambda function as the filter
* @return a list of fitted users
*/
std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) const {
  std::list<User> res;
  // std::cout << "before query I have to tell you the num of users is " << m_userList.size() << std::endl;
  for (auto it = m_userList.begin(); it != m_userList.end(); it++) {
    if (filter(*it)) res.push_back(*it);
  }
  return res;
}

/**
* update users
* @param a lambda function as the filter
* @param a lambda function as the method to update the user
* @return the number of updated user9s
*/
int Storage::updateUser(std::function<bool(const User &)> filter,
               std::function<void(User &)> switcher) {
  int count = 0;
  for (auto it = m_userList.begin(); it != m_userList.end(); it++) {
    if (filter(*it)) {
      switcher(*it);
      count++;
    } 
  }
  m_dirty = true;
  return count;
}

/**
* delete users
* @param a lambda function as the filter
* @return the number of deleted users
*/
int Storage::deleteUser(std::function<bool(const User &)> filter) {
  int count = 0;
  for (auto it = m_userList.begin(); it != m_userList.end(); ) {
    if (filter(*it)) {
      it = m_userList.erase(it);
      count++;
    } else {
      it++;
    }
  }
  m_dirty = true;
  return count;
}

/**
* create a meeting
* @param a meeting object
*/
void Storage::createMeeting(const Meeting &t_meeting) {
  m_meetingList.push_back(t_meeting);
  m_dirty = true;
}

/**
* query meetings
* @param a lambda function as the filter
* @return a list of fitted meetings
*/
std::list<Meeting> Storage::queryMeeting(
    std::function<bool(const Meeting &)> filter) const {
  std::list<Meeting> res;
  for (auto it = m_meetingList.begin(); it != m_meetingList.end(); it++) {
    if (filter(*it)) {
      res.push_back(*it);
    }
  }
  return res;
}

/**
* update meetings
* @param a lambda function as the filter
* @param a lambda function as the method to update the meeting
* @return the number of updated meetings
*/
int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                  std::function<void(Meeting &)> switcher) {
  int count = 0;
  for (auto it = m_meetingList.begin(); it != m_meetingList.end(); it++) {
    if ( filter(*it) ) {
      switcher(*it);
      count++;
    }
  }
  m_dirty = true;
  return count;
}

/**
* delete meetings
* @param a lambda function as the filter
* @return the number of deleted meetings
*/
int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
  int count = 0;
  for (auto it = m_meetingList.begin(); it != m_meetingList.end(); ) {
    if (filter(*it)) {
      it = m_meetingList.erase(it);
      count++;
    } else {
      it++;
    }
  }
  m_dirty = true;
  return count;
}

/**
* sync with the file
*/
bool Storage::sync(void) {
  if (m_dirty) {
    writeToFile();
    m_dirty = false;
    return true;
  }
  return false;
}
