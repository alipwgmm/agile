#ifndef AGILE_LOGGING_HH
#define AGILE_LOGGING_HH

#include "AGILe/AGILe.hh"

namespace AGILe {


  class Log {
  public:

    /// Log priority levels.
    enum Level {
      TRACE = 0, DEBUG = 10, INFO = 20, WARN = 30, WARNING = 30, ERROR = 40, CRITICAL = 50, ALWAYS = 50
    };

    /// Typedef for a collection of named logs.
    typedef std::map<const std::string, Log*> LogMap;

    /// Typedef for a collection of named log levels.
    typedef std::map<const std::string, int> LevelMap;

    /// Typedef for a collection of shell color codes, accessed by log level.
    typedef std::map<int, std::string> ColorCodes;

  private:
    /// A static std::map of existing logs: we don't make more loggers than necessary.
    static LogMap existingLogs;

    /// A static std::map of default log levels.
    static LevelMap defaultLevels;

    /// A static std::map of shell color codes for the log levels.
    static ColorCodes colorCodes;

    /// Shell color code for the end of the log levels.
    static std::string endColorCode;

    /// Show timestamp?
    static bool showTimestamp;

    /// Show log level?
    static bool showLogLevel;

    /// Show logger name?
    static bool showLoggerName;

    /// Use shell colour escape codes?
    static bool useShellColors;

  public:
    /// Set the log levels
    static void setLevel(const std::string& name, int level);
    static void setLevels(LevelMap& logLevels);

    static void setShowTimestamp(const bool showTime=true) {
      showTimestamp = showTime;
    }

    static void setShowLevel(const bool showLevel=true) {
      showLogLevel = showLevel;
    }

    static void setShowLoggerName(const bool showName=true) {
      showLoggerName = showName;
    }

    static void setUseColors(const bool useColors=true) {
      useShellColors = useColors;
    }

  protected:
    /// @name Hidden constructors etc.
    //@{
    /// Constructor 1
    Log(const std::string& name);

    /// Constructor 2
    Log(const std::string& name, int level);

    /// Copy constructor
    //Log(const Log&);

    /// Copy assignment operator
    //Log& operator=(const Log&);
    //@}

    static std::string getColorCode(int level);

  public:
    /// Get a logger with the given name. The level will be taken from the
    /// "requestedLevels" static std::map or will be INFO by default.
    static Log& getLog(const std::string& name);

  public:
    /// Get the priority level of this logger.
    int getLevel() const {
      return _level;
    }

    /// Set the priority level of this logger.
    Log& setLevel(int level) {
      _level = level;
      return *this;
    }

    /// Get a log level enum from a string.
    static Level getLevelFromName(const std::string& level);

    /// Get the string representation of a log level.
    static std::string getLevelName(int level);

    /// Get the name of this logger.
    std::string getName() const {
      return _name;
    }

    /// Set the name of this logger.
    Log& setName(const std::string& name) {
      _name = name;
      return *this;
    }

    /// Will this log level produce output on this logger at the moment?
    bool isActive(int level) const {
      return (level >= _level);
    }

    /// @name Explicit log methods
    //@{
    void trace(const std::string& message) { log(TRACE, message); }

    void debug(const std::string& message) { log(DEBUG, message); }

    void info(const std::string& message) { log(INFO, message); }

    void warn(const std::string& message) { log(WARN, message); }

    void error(const std::string& message) { log(ERROR, message); }

    void always(const std::string& message) { log(ALWAYS, message); }
    //@}

  private:
    /// This logger's name
    std::string _name;

    /// Threshold level for this logger.
    int _level;

  protected:
    /// Write a message at a particular level.
    void log(int level, const std::string& message);

    /// Turn a message string into the current log format.
    std::string formatMessage(int level, const std::string& message);

  public:

    /// A null output stream, used for piping discarded output to nowhere.
    /// @todo Hide this...
    std::ostream* const _nostream;

    /// The streaming operator can use Log's internals.
    friend std::ostream& operator<<(Log& log, int level);

  };

  /// Streaming output to a logger must have a Log::Level/int as its first argument.
  std::ostream& operator<<(Log& log, int level);

}


#endif
