#include "log.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <cstdarg>
#include <filesystem>
#include <ctime>

Logger LoggerInstance("logs/latest.txt");

Logger::Logger(const std::string &filename) : level(LOG_DEBUG), quiet(false)
{
    std::filesystem::create_directories("logs");
    renameOldLogFile(filename);

    logFile.open(filename, std::ios::app);
    if (!logFile.is_open())
    {
        std::cerr << "Ошибка открытия файла журнала." << std::endl;
    }
}

Logger::~Logger()
{
    logFile.close();
}

void Logger::renameOldLogFile(const std::string &oldFilename)
{
    if (std::filesystem::exists(oldFilename))
    {
        // Получаем время последнего изменения файла
        auto ftime = std::filesystem::last_write_time(oldFilename);
        
        // Преобразуем системное время в time_t
        auto system_time = std::chrono::clock_cast<std::chrono::system_clock>(ftime);
        auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(system_time);
        std::time_t cftime = std::chrono::system_clock::to_time_t(seconds);

        // Конвертируем time_t в локальное время
        std::tm buf;
#ifdef _WIN32
        localtime_s(&buf, &cftime);
#else
        localtime_r(&cftime, &buf);
#endif

        // Форматируем дату в нужный формат (день.месяц.год)
        std::ostringstream date_oss;
        date_oss << std::put_time(&buf, "%d_%m_%Y");
        std::string date_str = date_oss.str();

        // Создаем папку для даты, если ее нет
        std::string date_dir = "logs/" + date_str;
        std::filesystem::create_directories(date_dir);

        // Ищем следующий доступный номер для этого дня
        int counter = 1;
        std::string newFilename;
        do {
            std::ostringstream filename_oss;
            filename_oss << date_dir << "/log_" << counter << ".txt";
            newFilename = filename_oss.str();
            counter++;
        } while (std::filesystem::exists(newFilename));

        // Переименовываем старый файл
        std::filesystem::rename(oldFilename, newFilename);
    }
}

std::string Logger::getCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm buf;

#ifdef _WIN32
    localtime_s(&buf, &in_time_t);
#else
    localtime_r(&in_time_t, &buf);
#endif

    std::ostringstream oss;
    oss << std::put_time(&buf, "[%Y-%m-%d %H:%M:%S]");
    return oss.str();
}

std::string Logger::levelToString(LogLevel level)
{
    switch (level)
    {
    case LOG_DEBUG:
        return "[DEBUG]";
    case LOG_INFO:
        return "[INFO] ";
    case LOG_WARN:
        return "[WARN] ";
    case LOG_ERROR:
        return "[ERROR]";
    case LOG_FATAL:
        return "[FATAL]";
    default:
        return "[UNKNOWN]";
    }
}

void Logger::log(LogLevel lvl, const char *file, int line, const char *fmt, ...)
{
    if (lvl < level || quiet)
        return;

    std::lock_guard<std::mutex> lock(mtx);

    std::string timeStr = getCurrentTime();

    // Форматирование вывода в консоль
    std::cerr << timeStr << " " << colorCodes[lvl]
              << std::left << levelToString(lvl)
              << COLOR_RESET << " ";
    //<< file << ":" << line << ": " ; //Debug

    va_list args;
    va_start(args, fmt);

    vfprintf(stderr, fmt, args);

    va_end(args);

    std::cerr << std::endl;

    // Запись в файл журнала
    if (logFile.is_open())
    {
        logFile << "" << timeStr << " "
                << levelToString(lvl) << ": ";

        va_start(args, fmt);

        char buffer[1024];
        vsnprintf(buffer, sizeof(buffer), fmt, args);

        va_end(args);

        logFile << buffer << std::endl;
        logFile.flush(); // Обеспечить немедленную запись в файл
    }
}
