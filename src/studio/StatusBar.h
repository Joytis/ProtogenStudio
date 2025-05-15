#pragma once

#include "protogen/ProtogenProject.h"

namespace Studio
{
    class StatusBar
    {
    public:
        enum class Status
        {
            Info,
            Warning,
            Error
        };

        bool Render(float deltaTime);
        
        void SetStatus(Status status, const char* message);

    private:
        static constexpr float MAX_MESSAGE_TIME = 4.0f;

        std::string _message = "";
        float _timeSinceLastMessage = 0.f;
        Status _status = Status::Info;
    };
}