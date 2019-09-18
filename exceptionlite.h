#ifndef EXCEPTION_LITE_H
#define EXCEPTION_LITE_H

/*Базовый набор*/
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
/*Для создания trace*/
#include <execinfo.h> // Для backtrace
#include <dlfcn.h>    // Для dladdr
#include <cxxabi.h>   // Для __cxa_demangle


using namespace std;

/*!
 * @brief Макрос для создания класса ExceptionLite с предварительным набором данными.
 */
#define ERROR(str_error) ExceptionLite(__FILE__, __PRETTY_FUNCTION__, __LINE__, str_error);

/*! \class ExceptionLite
 * @brief Класс для создания исключения
 */
class ExceptionLite {
public:
  /*!
   * @brief Конструктор
   * @param eFile     Имя файла в котором возникло исключение 
   * @param eFunction Имя функции в котором возникло исключение
   * @param eLine     Номер строки в файле в котором возникло исключение
   * @param error     Текс ошибки исключения
   */
  explicit ExceptionLite(const string &eFile, const string &eFunction, const int eLine, const string &error);
  /*!
   * @brief Получить имя файла в котором возникло исключение
   * @return string Имя файла
   */
  string file()     { return fileErr; };
  /*!
   * @brief Получить текст ошибки исключения
   * @return string Текс ошибки
   */
  string what()     { return whatErr; };
  /*!
   * @brief Получить имя функции в котором возникло исключение
   * @return string Имя функции
   */
  string function() { return functionErr; };
  /*!
   * @brief Получить номер строки в файле в котором возникло исключение
   * @return string Номер строки
   */
  string line()     { return to_string(lineErr); };
  /*!
   * @brief Получить trace
   * @return string trace
   */
  string trace()    { return traceErr; };
private:
  // Создание trace
  void saveTrace();   // Создание trace
  string fileErr;     // Имя файла
  string whatErr;     // Текс ошибки
  string functionErr; // Имя функции
  string traceErr;    // trace
  int lineErr;        // Номер строки
};

#endif // EXCEPTION_LITE_H
