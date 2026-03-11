#include "Logger.h"

// ---------------- Static Member ----------------
bool Logger::active = true;

// ---------------- Konstruktor ----------------
Logger::Logger() {}

// ---------------- TempLogger Implementation ----------------
Logger::TempLogger::TempLogger(const Logger& logger, const std::string& tp)
    : base(logger), tempPrefix(tp.empty() ? "" : "[" + tp + "]") {}

void Logger::TempLogger::info(const std::string& msg) const {
    if (base.active)
        std::cout << base.prefix << tempPrefix << GREEN << " [INFO]" << RESET << " " << msg << std::endl;
}

void Logger::TempLogger::warn(const std::string& msg) const {
    if (base.active)
        std::cout << base.prefix << tempPrefix << YELLOW << " [WARN]" << RESET << " " << msg << std::endl;
}

void Logger::TempLogger::error(const std::string& msg) const {
    if (base.active)
        std::cout << base.prefix << tempPrefix << RED << " [ERROR]" << RESET << " " << msg << std::endl;
}

// ---------------- Logger Singleton ----------------
Logger& Logger::get() {
    static Logger instance;
    return instance;
}

// ---------------- Logger Methoden ----------------
void Logger::changePrefix(const std::string& p) {
    prefix = "[" + p + "]";
}

void Logger::info(const std::string& msg) const {
    TempLogger(*this).info(msg);
}

void Logger::warn(const std::string& msg) const {
    TempLogger(*this).warn(msg);
}

void Logger::error(const std::string& msg) const {
    TempLogger(*this).error(msg);
}

Logger::TempLogger Logger::tprefix(const std::string& tp) const {
    return TempLogger(*this, tp);
}
