#ifndef LOG_H
#define LOG_H

#include <string>
#include <fstream>
#include <mutex>

// Уровни логирования
enum LogLevel
{
  LOG_DEBUG,
  LOG_INFO,
  LOG_WARN,
  LOG_ERROR,
  LOG_FATAL
};

class Logger
{
public:
  explicit Logger(const std::string &filename);
  ~Logger();

  void setLevel(LogLevel lvl)
  {
    level = lvl;
  }

  void setQuiet(bool enable)
  {
    quiet = enable;
  }
  void log(LogLevel lvl, const char *file, int line, const char *fmt, ...);

private:
  void renameOldLogFile(const std::string &oldFilename);
  std::string getCurrentTime();
  std::string levelToString(LogLevel level);

  LogLevel level;
  bool quiet;
  std::mutex mtx;        // Мьютекс для потокобезопасности
  std::ofstream logFile; // Файл журнала

  const char *colorCodes[6] = {
      "\033[38;2;0;188;101m",  // DEBUG
      "\033[38;2;0;156;232m",  // INFO
      "\033[38;2;255;184;66m", // WARN
      "\033[38;2;255;112;0m",  // ERROR
      "\033[38;2;222;51;0m",   // FATAL
  };

  const char *COLOR_RESET = "\033[0m";
};

#define log_debug(...) LoggerInstance.log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)  LoggerInstance.log(LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...)  LoggerInstance.log(LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) LoggerInstance.log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...) LoggerInstance.log(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

extern Logger LoggerInstance;

#endif // LOG_H
