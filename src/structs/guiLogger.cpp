#include "okapi/api/util/logging.hpp"
#include <memory>
#include <mutex>
#include <cstdio>
#include "main.h"
#include <string>
#include <vector>
/**
I have a lot of explaning to do
We create a custom logger that overwrites literally everything we know and love in the logger to write to the screen
*/

class GuiLogger : okapi::Logger {

  public:

  GuiLogger() noexcept: GuiLogger(nullptr, nullptr, LogLevel::off) {}


  GuiLogger(std::unique_ptr<okapi::AbstractTimer> itimer,
         std::string_view ifileName,
         const LogLevel &ilevel) noexcept: GuiLogger(std::move(itimer), nullptr, ilevel) {}

  GuiLogger(std::unique_ptr<okapi::AbstractTimer> itimer, FILE *ifile, const LogLevel &ilevel) noexcept: timer(std::move(itimer)), logLevel(ilevel), logfile(nullptr) {};

  ~GuiLogger() {
    //TODO: send disconnected message to console

  };

  constexpr bool isDebugLevelEnabled() const noexcept {
    return toUnderlyingType(logLevel) >= toUnderlyingType(LogLevel::debug);
  }

  template <typename T> void debug(T ilazyMessage) noexcept {
    if (isDebugLevelEnabled() && pros::lcd::is_initialized() && timer) {
      std::scoped_lock lock(logfileMutex);
      fprintf(logfile,
              "%ld (%s) DEBUG: %s\n",
              static_cast<long>(timer->millis().convert(okapi::millisecond)),
              CrossplatformThread::getName().c_str(),
              ilazyMessage().c_str());
    }
  }

  constexpr bool isInfoLevelEnabled() const noexcept {
    return toUnderlyingType(logLevel) >= toUnderlyingType(LogLevel::info);
  }

  template <typename T> void info(T ilazyMessage) noexcept {
    if (isInfoLevelEnabled() && logfile && timer) {
      std::scoped_lock lock(logfileMutex);
      fprintf(logfile,
              "%ld (%s) INFO: %s\n",
              static_cast<long>(timer->millis().convert(okapi::millisecond)),
              CrossplatformThread::getName().c_str(),
              ilazyMessage().c_str());
    }
  }

  constexpr bool isWarnLevelEnabled() const noexcept {
    return toUnderlyingType(logLevel) >= toUnderlyingType(LogLevel::warn);
  }

  template <typename T> void warn(T ilazyMessage) noexcept {
    if (isWarnLevelEnabled() && logfile && timer) {
      std::scoped_lock lock(logfileMutex);
      fprintf(logfile,
              "%ld (%s) WARN: %s\n",
              static_cast<long>(timer->millis().convert(okapi::millisecond)),
              CrossplatformThread::getName().c_str(),
              ilazyMessage().c_str());
    }
  }

  constexpr bool isErrorLevelEnabled() const noexcept {
    return toUnderlyingType(logLevel) >= toUnderlyingType(LogLevel::error);
  }

  template <typename T> void error(T ilazyMessage) noexcept {
    if (isErrorLevelEnabled() && logfile && timer) {
      std::scoped_lock lock(logfileMutex);
      fprintf(logfile,
              "%ld (%s) ERROR: %s\n",
              static_cast<long>(timer->millis().convert(okapi::millisecond)),
              CrossplatformThread::getName().c_str(),
              ilazyMessage().c_str());
    }
  }

  /**
   * Closes the connection to the log file.
   */
  constexpr void close() noexcept {
    if (logfile) {
      fclose(logfile);
      logfile = nullptr;
    }
  }

  private:

  const std::unique_ptr<okapi::AbstractTimer> timer;
  const LogLevel logLevel;
  std::vector<std::string> bufferFrnt = std::vector<std::string>(8);
  std::vector<std::string> bufferBck = std::vector<std::string>(8);
  FILE *logfile;
  CrossplatformMutex logfileMutex;

  void reprintBuffer() {

  }

  static bool isSerialStream(std::string_view filename);
};