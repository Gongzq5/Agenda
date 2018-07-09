#include "Date.hpp"
#include <iostream>
using namespace std;
using std::string;
using std::to_string;
/**
* @brief default constructor
*/
bool IS_NUM(char a) {
 if (a <= '9' && a >= '0') return true;
 return false;
}
bool valid_string(const string& dateString) {
 if (dateString.length() != 16) return false;

 if (!IS_NUM(dateString[0])) return false; 
 if (!IS_NUM(dateString[1])) return false;
 if (!IS_NUM(dateString[2])) return false;
 if (!IS_NUM(dateString[3])) return false;

 if (dateString[4] != '-') return false;

 if (!IS_NUM(dateString[5])) return false;
 if (!IS_NUM(dateString[6])) return false;

 if (dateString[7] != '-') return false;

 if (!IS_NUM(dateString[8])) return false;
 if (!IS_NUM(dateString[9])) return false;

 if (dateString[10] != '/') return false;

 if (!IS_NUM(dateString[11])) return false; 
 if (!IS_NUM(dateString[12])) return false;

 if (dateString[13] != ':') return false;

 if (!IS_NUM(dateString[14])) return false;
 if (!IS_NUM(dateString[15])) return false;

 return true;
}
Date::Date() {
 m_minute = m_hour = m_day = m_month = m_year = 0;
}

/**
* @brief constructor with arguments
*/
Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute) {
 m_year = t_year;
 m_month = t_month;
 m_day = t_day;
 m_hour = t_hour;
 m_minute = t_minute;
}

/**
* @brief constructor with a string
*/
Date::Date(const std::string &dateString) {
 if(!valid_string(dateString)) {
  m_minute = m_hour = m_day = m_month = m_year = 0;
  return ;
 }
 int num;
 int i = 0;
 for (num = 0; i < dateString.length(); i++) {
  if (dateString[i] == '-') break;
  else num = num * 10 + dateString[i] - '0';
 }
 m_year = num;
 i++;
 for (num = 0; i < dateString.length(); i++) {
  if (dateString[i] == '-') break;
  else num = num * 10 + dateString[i] - '0';
 }
 m_month = num;
 i++;
 for (num = 0; i < dateString.length(); i++) {
  if (dateString[i] == '/') break;
  else num = num * 10 + dateString[i] - '0';
 }
 m_day = num;
 i++;
 for (num = 0; i < dateString.length(); i++) {
  if (dateString[i] == ':') break;
  else num = num * 10 + dateString[i] - '0';
 }
 m_hour = num;
 i++;
 for (num = 0; i < dateString.length(); i++) {
  num = num * 10 + dateString[i] - '0';
 }
 m_minute = num;
}
/**
* @brief return the year of a Date
* @return   a integer indicate the year of a date
*/
int Date::getYear(void) const {
 return m_year;
}

/**
* @brief set the year of a date
* @param a integer indicate the new year of a date
*/
void Date::setYear(const int t_year) {
 m_year = t_year;
}

/**
* @brief return the month of a Date
* @return   a integer indicate the month of a date
*/
int Date::getMonth(void) const {
 return m_month;
}

/**
* @brief set the month of a date
* @param a integer indicate the new month of a date
*/
void Date::setMonth(const int t_month) {
 m_month = t_month;
}

/**
* @brief return the day of a Date
* @return   a integer indicate the day of a date
*/
int Date::getDay(void) const {
 return m_day;
}

/**
* @brief set the day of a date
* @param a integer indicate the new day of a date
*/
void Date::setDay(const int t_day) {
 m_day = t_day;
}

/**
* @brief return the hour of a Date
* @return   a integer indicate the hour of a date
*/
int Date::getHour(void) const {
 return m_hour;
}

/**
* @brief set the hour of a date
* @param a integer indicate the new hour of a date
*/
void Date::setHour(const int t_hour) {
 m_hour = t_hour;
}

/**
* @brief return the minute of a Date
* @return   a integer indicate the minute of a date
*/
int Date::getMinute(void) const {
 return m_minute;
}

/**
* @brief set the minute of a date
* @param a integer indicate the new minute of a date
*/
void Date::setMinute(const int t_minute) {
 m_minute = t_minute;
}

/**
*   @brief check whether the date is valid or not
*   @return the bool indicate valid or not
*/
bool Date::isValid(const Date &t_date) {
 const int dayofmonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
 if (t_date.m_year < 1000 || t_date.m_year > 9999) return false;
 if (t_date.m_month <= 0 || t_date.m_month > 12) return false;
 if (t_date.m_month == 2) {
  if ((t_date.m_year % 4 == 0 
   && t_date.m_year % 100 != 0 )
   || t_date.m_year % 400 == 0) {
   if (t_date.m_day > 29 || t_date.m_day < 1) return false; 
  } else {
   if (t_date.m_day > 28 || t_date.m_day < 1) return false;
  }
 } else {
  if (t_date.m_day > dayofmonth[t_date.m_month-1] || 
   t_date.m_day < 1) 
   return false;
 }
 if (t_date.m_hour < 0 || t_date.m_hour >= 24) return false;
 if (t_date.m_minute < 0 || t_date.m_minute >= 60) return false;
 return true; 
}

/**
* @brief convert a string to date, if the format is not correct return
* 0000-00-00/00:00
* @return a date
*/
Date Date::stringToDate(const std::string &t_dateString) {
 Date tmp;
 if (!valid_string(t_dateString)) return tmp;
 // cout << "is valid string in stringToDate func \n";
 int num;
 int i = 0;
 for (num = 0; i < t_dateString.length(); i++) {
  if (t_dateString[i] == '-') break;
  else num = num * 10 + t_dateString[i] - '0';
 }
 tmp.m_year = num;
 i++;
 for (num = 0; i < t_dateString.length(); i++) {
  if (t_dateString[i] == '-') break;
  else num = num * 10 + t_dateString[i] - '0';
 }
 tmp.m_month = num;
 i++;
 for (num = 0; i < t_dateString.length(); i++) {
  if (t_dateString[i] == '/') break;
  else num = num * 10 + t_dateString[i] - '0';
 }
 tmp.m_day = num;
 i++;
 for (num = 0; i < t_dateString.length(); i++) {
  if (t_dateString[i] == ':') break;
  else num = num * 10 + t_dateString[i] - '0';
 }
 tmp.m_hour = num;
 i++;
 for (num = 0; i < t_dateString.length(); i++) {
  num = num * 10 + t_dateString[i] - '0';
 }
 tmp.m_minute = num;
 return tmp;
}

/**
* @brief convert a date to string, if the date is invalid return
* 0000-00-00/00:00
*/
std::string Date::dateToString(const Date &t_date) {
 if (!isValid(t_date)) return "0000-00-00/00:00";
 string res;
 res = to_string(t_date.m_year) + '-'; 
 if (t_date.m_month < 10) res += '0';
 res = res + to_string(t_date.m_month) + '-';
 if (t_date.m_day < 10) res += '0';
 res = res + to_string(t_date.m_day) + '/';
 if (t_date.m_hour < 10) res += '0';
 res = res + to_string(t_date.m_hour) + ':';
 if (t_date.m_minute < 10) res += '0';
 res = res + to_string(t_date.m_minute);
 return res;
}

/**
*  @brief overload the assign operator
*/
Date& Date::operator=(const Date &t_date) {
 m_year = t_date.m_year;
 m_month = t_date.m_month;
 m_day = t_date.m_day;
 m_hour = t_date.m_hour;
 m_minute = t_date.m_minute;
 return *this;
}

/**
* @brief check whether the CurrentDate is equal to the t_date
*/
bool Date::operator==(const Date &t_date) const {
 if (m_year != t_date.m_year) return false;
 if (m_month != t_date.m_month) return false;
 if (m_day != t_date.m_day) return false;
 if (m_hour != t_date.m_hour) return false;
 if (m_minute != t_date.m_minute) return false;
 return true;
}

/**
* @brief check whether the CurrentDate is  greater than the t_date
*/
bool Date::operator>(const Date &t_date) const {
 if (m_year > t_date.m_year) return true;
 else if (m_year < t_date.m_year) return false;
 if (m_month > t_date.m_month) return true;
 else if (m_month < t_date.m_month) return false;
 if (m_day > t_date.m_day) return true;
 else if (m_day < t_date.m_day) return false;
 if (m_hour > t_date.m_hour) return true;
 else if (m_hour < t_date.m_hour) return false;
 if (m_minute > t_date.m_minute) return true;
 else if (m_minute < t_date.m_minute) return false;
 return false;
}

/**
* @brief check whether the CurrentDate is  less than the t_date
*/
bool Date::operator<(const Date &t_date) const {
 if (m_year < t_date.m_year) return true;
 else if (m_year > t_date.m_year) return false;
 if (m_month < t_date.m_month) return true;
 else if (m_month > t_date.m_month) return false;
 if (m_day < t_date.m_day) return true;
 else if (m_day > t_date.m_day) return false;
 if (m_hour < t_date.m_hour) return true;
 else if (m_hour > t_date.m_hour) return false;
 if (m_minute < t_date.m_minute) return true;
 else if (m_minute > t_date.m_minute) return false;
 return false;
}

/**
* @brief check whether the CurrentDate is  greater or equal than the t_date
*/
bool Date::operator>=(const Date &t_date) const {
 if (m_year > t_date.m_year) return true;
 else if (m_year < t_date.m_year) return false;
 if (m_month > t_date.m_month) return true;
 else if (m_month < t_date.m_month) return false;
 if (m_day > t_date.m_day) return true;
 else if (m_day < t_date.m_day) return false;
 if (m_hour > t_date.m_hour) return true;
 else if (m_hour < t_date.m_hour) return false;
 if (m_minute > t_date.m_minute) return true;
 else if (m_minute < t_date.m_minute) return false;
 return true;
}

/**
* @brief check whether the CurrentDate is  less than or equal to the t_date
*/
bool Date::operator<=(const Date &t_date) const {
 if (m_year < t_date.m_year) return true;
 else if (m_year > t_date.m_year) return false;
 if (m_month < t_date.m_month) return true;
 else if (m_month > t_date.m_month) return false;
 if (m_day < t_date.m_day) return true;
 else if (m_day > t_date.m_day) return false;
 if (m_hour < t_date.m_hour) return true;
 else if (m_hour > t_date.m_hour) return false;
 if (m_minute < t_date.m_minute) return true;
 else if (m_minute > t_date.m_minute) return false;
 return true;
}