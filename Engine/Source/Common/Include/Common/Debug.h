//
// Created by johnk on 9/4/2022.
//

#pragma once

#include <string>
#include <cstdint>
#include <source_location>

#define Assert(expression) Common::Debug::AssertImpl(expression, #expression, std::source_location::current().file_name(), std::source_location::current().line())
#define AssertWithReason(expression, reason) Common::Debug::AssertImpl(expression, #expression, std::source_location::current().file_name(), std::source_location::current().line(), reason)
#define Unimplement() Assert(false)
#define QuickFail() Assert(false)
#define QuickFailWithReason(reason) AssertWithReason(false, reason)

namespace Common {
    class Debug {
    public:
        static void AssertImpl(bool expression, const std::string& name, const std::string& file, uint32_t line, const std::string& reason = "");

        ~Debug();

    private:
        Debug();
    };
}
