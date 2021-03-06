#include "../inc/TE/logger.hpp"

#include <ctime>
#include <cstring>

namespace ta::utils {


void ConsoleLogger::vLog(LogLevelFlag lvl, const char* file, int line, std::string& message) {
    if (lvl >= mLogLevel) {
        fprintf(stdout, "[%7s] %35s:%d\t%s\n",
                LOG_LEVEL_NAMES[static_cast<int>(lvl)],
                file,
                line,
                message.c_str());
    }
}

void ConsoleLogger::vFlush() {}


void OnScreenLogger::vLog(LogLevelFlag lvl, const char* file, int line, std::string& message) {
    this->lines.push_back(message);
}

void OnScreenLogger::vFlush() {
    this->lines.clear();
}

std::list<string> OnScreenLogger::getLogs() {
    return this->lines;
}


void FileLogger::vInitialize(void) {
    FILE* fp = getLogFile();
    if (fp != nullptr) {
        fprintf(fp, "FileLogger initialized");
        fclose(fp);
    }
}

void FileLogger::vDestroy(void) {
    writePendingLogsIntoFileAndSwap();
}

void FileLogger::vLog(LogLevelFlag lvl, const char* file, int line, std::string& message) {
    if (lvl >= mLogLevel) {
        if (currentAmount < maxBulkEntry - 1) {
            appendLogEntry(lvl, file, line, message);
        } else {
            writePendingLogsIntoFileAndSwap();
            appendLogEntry(lvl, file, line, message);
        }
    }
}

void FileLogger::vFlush() {
    writePendingLogsIntoFileAndSwap();
}

void FileLogger::writePendingLogsIntoFileAndSwap() {
    FILE* fp = getLogFile();
    if (fp != nullptr) {
        // write all entries from previous vector in file
        for (auto& currentEntrie : currentEntries) {
            int lvl = static_cast<int>(currentEntrie->lvl);
            fprintf(
                    fp,
                    "[%7s] %35s:%d\t%s\n",
                    LOG_LEVEL_NAMES[lvl],
                    currentEntrie->file,
                    currentEntrie->line,
                    currentEntrie->message);
        }
        fclose(fp);
    } else {
        throw std::runtime_error("Enable to open output log file");
    }
    // switch stack
    pDBSAllocator->swapBuffer();
    pDBSAllocator->clear();
    // switch vector
    auto temp = pendingEntries;
    pendingEntries = currentEntries;
    currentEntries = temp;

    pendingEntries.clear();
    currentAmount = 0;
}

void FileLogger::appendLogEntry(LogLevelFlag lvl, const char* file, int line, std::string& message) {
    logEntry_t* entry = pDBSAllocator->alloc<logEntry_t>();
    entry->lvl = lvl;
    entry->line = line;
    strcpy(entry->file, file);
    strcpy(entry->message, message.c_str());
    currentEntries.push_back(entry);
    currentAmount++;
}

std::string FileLogger::getDateTimeNow() {
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%d-%m-%Y_%I-%M-%S", timeinfo);
    std::string dateAsString(buffer);

    return dateAsString;
}

FILE* FileLogger::getLogFile() {
    FILE* fp;
    std::string dateAsString = this->getDateTimeNow();
    std::string folder(this->folder);
    if (folder.at(folder.size() - 1) != '/') {
        folder = folder.append("/");
    }
    std::string filename = folder.append(baseName)
            .append("-")
            .append(dateAsString)
            .append(".txt");

    fopen_s(&fp, filename.c_str(), "a+");
    return fp;
}


void LoggerService::vInit(LoggerServiceConf args) {
    LogLevelFlag logLevelFlag = args.get_logLevel();
    LogChannelFlag logChannelFlag = args.get_logChannel();
    if (args.get_fileLogEnabled()) {
        this->pFileLogger = new FileLogger(logLevelFlag,
                                           logChannelFlag,
                                           args.get_fileLogFolder().c_str(),
                                           args.get_fileLogBaseName().c_str());
    }
    if (args.get_consoleLogEnabled()) {
        this->pConsoleLogger = new ConsoleLogger(logLevelFlag, logChannelFlag);
    }

    this->pOnScreenLogger = new OnScreenLogger();
}

void LoggerService::vUpdate(const sf::Time& time) {}

void LoggerService::vDestroy() {
    if (this->pConsoleLogger != nullptr) {
        this->pConsoleLogger->vDestroy();
    }
    if (this->pFileLogger != nullptr) {
        this->pFileLogger->vDestroy();
    }
}

void LoggerService::logInto(ILogger* logger,
                            LogLevelFlag lvl,
                            LogChannelFlag logChannel,
                            const char* file,
                            int line,
                            std::string& message) {

    int index = 0;
    int indexLastSlash = -1;
    while (file[index] != '\0') {
        if (file[index] == '/' || file[index] == '\\') {
            indexLastSlash = index;
        }
        index++;
    }
    if (indexLastSlash != -1) {
        std::string filename{file};
        if (logger->isChannelAllowed(logChannel)) {
            logger->vLog(lvl, filename.substr(indexLastSlash + 1).c_str(), line, message);
        }
    } else {
        if (logger->isChannelAllowed(logChannel)) {
            logger->vLog(lvl, file, line, message);
        }
    }
}


void LoggerService::log(LogLevelFlag lvl,
                        LogChannelFlag logChannel,
                        const char* file,
                        int line,
                        std::string& message) {

    if(logChannel == LogChannelFlag::ON_SCREEN) {
        this->pOnScreenLogger->vLog(lvl, "", 0, message);
        return;
    };

    if (this->pConsoleLogger != nullptr) {
        this->logInto(this->pConsoleLogger, lvl, logChannel, file, line, message);
    }
    if (this->pFileLogger != nullptr) {
        this->logInto(this->pFileLogger, lvl, logChannel, file, line, message);
    }

}

void LoggerService::flush() {
    if (this->pConsoleLogger != nullptr) {
        this->pConsoleLogger->vFlush();
    }
    if (this->pFileLogger != nullptr) {
        this->pFileLogger->vFlush();
    }
}

void LoggerService::render(sf::RenderTexture& target) {
    sf::Font font;
    if (!font.loadFromFile("cour.ttf")) {
        REP_FATAL("fail to load font from memory", LogChannelFlag::DEFAULT)
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(11);
    text.setFillColor(sf::Color::White);

    if(pOnScreenLogger != nullptr) {
        int count = 0;
        for(auto& line : this->pOnScreenLogger->getLogs()) {
            text.setString(line);
            text.setPosition(5, count*10 + 5);
            target.draw(text);
            count++;
        }
    }
    this->pOnScreenLogger->vFlush();
}

}
