#pragma once
#include <string>
#include <string_view>
#include <format>
#include <source_location>
#include <chrono>
#include <cwctype>
#include <algorithm>
#include <ranges>

namespace Utils::Logger
{
    enum class ELogType
    {
        Default,
        Trace,
        Debug,
        Info,
        Notice,
        Warning,
        Error,
        Critical,
        Fatal
    };

    struct LogMessage
    {
        std::string_view fmt;
        std::source_location location;

        template <size_t N>
        consteval LogMessage(
            const char(&s)[N],
            const std::source_location& loc = std::source_location::current()
        ) noexcept
            : fmt(s, N - 1), location(loc) {
        }

        LogMessage(
            std::string_view s,
            const std::source_location& loc = std::source_location::current()
        ) noexcept
            : fmt(s), location(loc) {
        }
    };

    constexpr std::string_view GetLogPrefix(ELogType type) noexcept
    {
        switch (type)
        {
        case ELogType::Default:  return "🌵";
        case ELogType::Trace:    return "👀";
        case ELogType::Debug:    return "🦠";
        case ELogType::Info:     return "📖";
        case ELogType::Notice:   return "🔍";
        case ELogType::Warning:  return "📫";
        case ELogType::Error:    return "📮";
        case ELogType::Critical: return "⚡";
        case ELogType::Fatal:    return "🔥";
        }
    }

    constexpr std::string_view ExtractFileName(std::string_view path) noexcept
    {
        const auto lastSlash = path.find_last_of("\\/");
        std::string_view fileName = (lastSlash != std::string_view::npos)
            ? path.substr(lastSlash + 1)
            : path;

        const auto lastDot = fileName.find_last_of('.');
        if (lastDot != std::string_view::npos)
        {
            fileName = fileName.substr(0, lastDot);
        }

        return fileName;
    }

    template <typename... Args>
    void TLog(ELogType logType, LogMessage msg, Args&&... args)
    {
        const std::string userMessage = std::vformat(msg.fmt, std::make_format_args(args...));

        const auto now = std::chrono::system_clock::now();
        const auto zonedNow = std::chrono::zoned_time{ std::chrono::current_zone(), now };
        const auto localSeconds = std::chrono::floor<std::chrono::seconds>(zonedNow.get_local_time());

        std::string fullLog = std::format("{} ¦ {} ¦ {} ¦ {:%H:%M:%S} ¦ {}\n",
            GetLogPrefix(logType),
            ExtractFileName(msg.location.file_name()),
            msg.location.line(),
            localSeconds,
            userMessage
        );

        std::ranges::transform(fullLog, fullLog.begin(), [](char c) -> char {
            return static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
            });

        if (fullLog.empty()) return;

        const int wideCharCount = ::MultiByteToWideChar(
            CP_UTF8,
            0,
            fullLog.data(),
            static_cast<int>(fullLog.size()),
            nullptr,
            0
        );

        if (wideCharCount > 0)
        {
            std::wstring wideBuffer(wideCharCount, L'\0');
            ::MultiByteToWideChar(
                CP_UTF8,
                0,
                fullLog.data(),
                static_cast<int>(fullLog.size()),
                wideBuffer.data(),
                wideCharCount
            );

            ::OutputDebugStringW(wideBuffer.c_str());
        }
    }
}