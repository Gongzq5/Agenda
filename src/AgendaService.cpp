#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <set>
#include "Storage.hpp"
#include "AgendaService.hpp"
#include "User.hpp"
#include "Meeting.hpp"
#include "Date.hpp"
using std::cout;
using std::cin;
using std::string;
using std::endl;
  /**
   * constructor
   */
  AgendaService::AgendaService() {
    startAgenda();
  }

  /**
   * destructor
   */
  AgendaService::~AgendaService() {
    quitAgenda();
  }

  /**
   * check if the userName match password
   * @param userName the userName want to login
   * @param password the password user enter
   * @return if success, true will be returned
   */
  bool AgendaService::userLogIn(const std::string &userName, const std::string &password) {
    std::list<User> tmp = m_storage->queryUser([userName, password](const User & p)->bool{
                                      if (p.getName() == userName && p.getPassword() == password)
                                        return true;
                                      else return false;});
    if (tmp.empty()) {
      return false;
    }
    return true;
  }

  /**
   * regist a user
   * @param userName new user's userName
   * @param password new user's password
   * @param email new user's email
   * @param phone new user's phone
   * @return if success, true will be returned
   */
  bool AgendaService::userRegister(const std::string &userName, const std::string &password,
                    const std::string &email, const std::string &phone) {
    for(auto i : userName) {
      if (!(('a' <= i && i <= 'z') || ('A' <= i && i <= 'Z') || (i == '_') || ('0' <= i && i <= '9'))) 
        return false;
    }
    for (auto i : password) {
      if (!(('a' <= i && i <= 'z') || ('A' <= i && i <= 'Z') || (i == '_') || ('0' <= i && i <= '9'))) 
        return false;
    }
    std::list<User> tmp = m_storage->queryUser([userName](const User & p)->bool{
                                      if (p.getName() == userName)
                                        return true;
                                      else return false;});
    if (!tmp.empty()) {
      return false;
    }
    m_storage->createUser(User(userName, password, email, phone));
    return true;
  }

  /**
   * delete a user
   * @param userName user's userName
   * @param password user's password
   * @return if success, true will be returned
   */
  bool AgendaService::deleteUser(const std::string &userName, const std::string &password) {
    std::list<User> tmp = m_storage->queryUser([userName, password](const User & p)-> bool{
                                      if (p.getName() == userName && 
                                        p.getPassword() == password)
                                        return true;
                                      else return false;});
    if (tmp.empty()) {
      // tmp is empty means there is no such a user
      return false;
    } else {
      // have this user, we need to delete the meeting whose sponser
      // besides that we have to delete the particpator
      m_storage->deleteMeeting([=](const Meeting& p)-> bool {
                                if (p.getSponsor() == userName) return true;
                                return false;
                                });
      std::vector<std::string> t;
      m_storage->updateMeeting([=](const Meeting& p)-> bool {
                                if (p.isParticipator(userName)) return true;
                                return false;
                              }, [&](Meeting& p) {
                                p.removeParticipator(userName);
                                if (p.getParticipator().size() == 0) {
                                  t.push_back(p.getTitle());
                                }
                              });
      if (!t.empty()) {
        for (auto it : t){
          m_storage->deleteMeeting([=](const Meeting& p)-> bool{if (p.getSponsor() == it) 
                                                            return true;
                                                          return false;});
        }
      }
      m_storage->deleteUser([userName](const User & p)-> bool{
                              if (p.getName() == userName) return true;
                              else return false;
                            });
      return true;
    }
  }

  /**
   * list all users from storage
   * @return a user list result
   */
  std::list<User> AgendaService::listAllUsers(void) const {
    std::list<User> tmp = m_storage->queryUser([](const User&){return true;});
    return tmp;
  }

  /**
   * create a meeting
   * @param userName the sponsor's userName
   * @param title the meeting's title
   * @param participator the meeting's participator
   * @param startData the meeting's start date
   * @param endData the meeting's end date
   * @return if success, true will be returned
   */
  bool AgendaService::createMeeting(const std::string &userName, const std::string &title,
                     const std::string &startDate, const std::string &endDate,
                     const std::vector<std::string> &participator) {
    //creat a meeting at a time point is not allowed
    if (!(Date::isValid(Date::stringToDate(startDate)) || !Date::isValid(Date::stringToDate(endDate)))) {
      return false;
    }
    if (startDate >= endDate) {
      return false;
    }
    if (participator.empty()) {
      return false;
    }
    std::set<std::string> judge_muti;
    for (auto it : participator) {
      std::list<User> tmpu = m_storage->queryUser([=](const User& p)-> bool{
                                  if (p.getName() == it) return true;
                                  return false;
                                });
      if (tmpu.empty()) {
        return false;
      }
      judge_muti.insert(it);
      std::list<Meeting> tmp = m_storage->queryMeeting([=](const Meeting& p)-> bool{
                                          if (p.getSponsor() == it ||
                                              p.isParticipator(it))
                                            return true;
                                          return false;
                                        });
      for (auto itt : tmp) {
        if (!((itt.getStartDate() >= endDate) || (itt.getEndDate() <= startDate)))
        return false;
      }
    }
    if (judge_muti.size() != participator.size()) {
      return false;
    }
    //the title should be unique
    std::list<Meeting> tmp1 = m_storage->queryMeeting([=](const Meeting& p)-> bool{
                                                      if (p.getTitle() == title) 
                                                        return true;
                                                      else return false;});
    if (!tmp1.empty()) {
      return false;
    }
    //time should not conflict
    std::list<Meeting> tmp2 = m_storage->queryMeeting([=](const Meeting& p)-> bool{
                                                      if (p.getSponsor() == userName) 
                                                        return true;
                                                      else return false;});
    std::list<Meeting> tmp3 = m_storage->queryMeeting([=](const Meeting& p)-> bool{
                                                      if (p.isParticipator(userName))
                                                        return true;
                                                      return false;});
    for (auto it : tmp2) {
      if (!((it.getStartDate() >= endDate) || (it.getEndDate() <= startDate)))
        return false;
    }
    for (auto it : tmp3) {
      if (!((it.getStartDate() >= endDate) || (it.getEndDate() <= startDate)))
        return false;
    }
    Meeting ameeting(userName, participator, startDate, endDate, title);
    m_storage->createMeeting(ameeting);
    return true;
  }

  /**
   * add a participator to a meeting
   * @param userName the sponsor's userName
   * @param title the meeting's title
   * @param participator the meeting's participator
   * @return if success, true will be returned
   */
  bool AgendaService::addMeetingParticipator(const std::string &userName,
                              const std::string &title,
                              const std::string &participator) {
    std::list<Meeting> tmp = m_storage->queryMeeting([=](const Meeting& p)-> bool{
                                          if (p.getTitle() == title)
                                            return true;
                                          return false;
                                        });
    if (tmp.empty()) {
      return false;
    }
    if (userName != tmp.begin()->getSponsor()) {
      return false;
    }
    Date startDate = tmp.begin()->getStartDate();
    Date endDate = tmp.begin()->getStartDate();
    std::list<User> tmpu = m_storage->queryUser([=](const User& p)-> bool{
                                if (p.getName() == participator) return true;
                                return false;
                              });
    if (tmpu.empty()) {
      return false;
    }
    //disallow the time of the particpator conflict with the meeting
    tmp = m_storage->queryMeeting([=](const Meeting& p)-> bool{
                                          if (p.getSponsor() == participator ||
                                              p.isParticipator(participator))
                                            return true;
                                          return false;
                                        });
    for (auto it : tmp) {
      if (!((it.getStartDate() >= endDate) || (it.getEndDate() <= startDate)))
        return false;
    }
    m_storage->updateMeeting([=](const Meeting& p)-> bool{
                            if (p.getTitle() == title) return true;
                            return false;
                            }, [=](Meeting& p)-> void{
                              p.addParticipator(participator);
                            });
    return true;
  }

  /**
   * remove a participator from a meeting
   * @param userName the sponsor's userName
   * @param title the meeting's title
   * @param participator the meeting's participator
   * @return if success, true will be returned
   */
  bool AgendaService::removeMeetingParticipator(const std::string &userName,
                                 const std::string &title,
                                 const std::string &participator) {
    std::list<Meeting> tmp = m_storage->queryMeeting([&](const Meeting& p)-> bool {
                                if (p.getSponsor() == userName &&
                                  p.getTitle() == title) return true;
                                  return false; });
    if (tmp.empty()) {
      return false;
    }
    bool is_zero = false;
    m_storage->updateMeeting([&](const Meeting& p)-> bool {
                            if (p.getSponsor() == userName &&
                              p.getTitle() == title) return true;
                            return false;}, [&](Meeting& p)-> bool{
                              p.removeParticipator(participator);
                              if (p.getParticipator().size() == 0) {
                                is_zero = true;
                              }
                            });
    if (is_zero) {
      m_storage->deleteMeeting([&](const Meeting& p)-> bool {
                                if (p.getSponsor() == userName &&
                                  p.getTitle() == title) return true;
                                  return false; });
    }
    return true;
  }

  /**
   * quit from a meeting
   * @param userName the current userName. need to be the participator (a sponsor can not quit his/her meeting)
   * @param title the meeting's title
   * @return if success, true will be returned
   */
  bool AgendaService::quitMeeting(const std::string &userName, const std::string &title) {
    std::list<Meeting> tmp = m_storage->queryMeeting([&](const Meeting& p)-> bool {
      if (p.isParticipator(userName) && p.getTitle() == title) return true;
      return false;
    });
    if (tmp.empty()) {
      return false;
    }
    bool d = false;
    m_storage->updateMeeting([&](const Meeting& p)-> bool {
                            if (p.getTitle() == title) return true;
                            return false;}, [&](Meeting& p)-> bool{
                              p.removeParticipator(userName);
                              if (p.getParticipator().empty()) {d = true;}
                            });
    if (d) {
      m_storage->deleteMeeting([&](const Meeting& p)-> bool {
                            if (p.getTitle() == title) return true;
                            return false;  
                            });
    }
    return true;
  }

  /**
   * search a meeting by userName and title
   * @param userName as a sponsor OR a participator
   * @param title the meeting's title
   * @return a meeting list result
   */
  std::list<Meeting> AgendaService::meetingQuery(const std::string &userName,
                                  const std::string &title) const {
    std::list<Meeting> tmp = m_storage->queryMeeting([&](const Meeting& p)-> bool{
                                                    if ((p.getTitle() == title) && 
                                                      ((p.getSponsor() == userName) ||
                                                      p.isParticipator(userName)))
                                                      return true;
                                                    return false;});
    return tmp;
  }
  /**
   * search a meeting by userName, time interval
   * @param userName as a sponsor OR a participator
   * @param startDate time interval's start date
   * @param endDate time interval's end date
   * @return a meeting list result
   */
  std::list<Meeting> AgendaService::meetingQuery(const std::string &userName,
                                  const std::string &startDate,
                                  const std::string &endDate) const {
    auto filter = [&](const Meeting& p)-> bool {
      if (((p.getStartDate() >= startDate && p.getStartDate() <= endDate)
          || (p.getEndDate() <= endDate && p.getEndDate() >= startDate)
        || (p.getStartDate() <= startDate && p.getEndDate() >= endDate))
        && (p.getSponsor() == userName || p.isParticipator(userName))) 
        return true;
      return false;
    };
    std::list<Meeting> tmp = m_storage->queryMeeting(filter);
    return tmp;
  }

  /**
   * list all meetings the user take part in
   * @param userName user's userName
   * @return a meeting list result
   */
  std::list<Meeting> AgendaService::listAllMeetings(const std::string &userName) const {
    std::list<Meeting> tmp = m_storage->queryMeeting([&](const Meeting& p)-> bool{
                                                    if (p.getSponsor() == userName ||
                                                      p.isParticipator(userName)) return true;
                                                      return false;
                                                    });
    return tmp;  
  }

  /**
   * list all meetings the user sponsor
   * @param userName user's userName
   * @return a meeting list result
   */
  std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string &userName) const {
    std::list<Meeting> tmp = m_storage->queryMeeting([&](const Meeting& p)-> bool{
                                                      if (p.getSponsor() == userName) return true;
                                                      return false;});
    return tmp;
  }

  /**
   * list all meetings the user take part in and sponsor by other
   * @param userName user's userName
   * @return a meeting list result
   */
  std::list<Meeting> AgendaService::listAllParticipateMeetings(
      const std::string &userName) const {
    std::list<Meeting> tmp = m_storage->queryMeeting([&](const Meeting& p)-> bool {
                                              return (p.isParticipator(userName));});
    return tmp;
  }

  /**
   * delete a meeting by title and its sponsor
   * @param userName sponsor's userName
   * @param title meeting's title
   * @return if success, true will be returned
   */
  bool AgendaService::deleteMeeting(const std::string &userName, const std::string &title) {
    std::list<Meeting> tmp = m_storage->queryMeeting([=](const Meeting& p)-> bool {
                                                     if (p.getTitle() == title) return true;
                                                     return false; 
                                                    });
    if (tmp.empty()) {
      return false;
    }
    if (tmp.begin()->getSponsor() != userName) {
      return false;
    }
    int count = m_storage->deleteMeeting([&](const Meeting& p)-> bool {
                                              if (p.getSponsor() == userName && 
                                                p.getTitle() == title)
                                                return true;
                                              return false;});
    if (count == 0) { return false;}
    return true;
  }

  /**
   * delete all meetings by sponsor
   * @param userName sponsor's userName
   * @return if success, true will be returned
   */
  bool AgendaService::deleteAllMeetings(const std::string &userName) {
    m_storage->deleteMeeting([&](const Meeting& p)-> bool{
                            if (p.getSponsor() == userName) return true;
                            return false;});
    return true;
  }

  /**
   * start Agenda service and connect to storage
   */
  void AgendaService::startAgenda(void) {
    m_storage = Storage::getInstance();
  }

  /**
   * quit Agenda service
   */
  void AgendaService::quitAgenda(void) {
    m_storage->sync();
  }
