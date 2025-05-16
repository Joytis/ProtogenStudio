#pragma once

#include "protogen/ProtogenProject.h"
#include "protogen/Protogen.h"
#include "protogen/Grid.h"

namespace Studio::ProtoWindows
{
    void RenderProjectSettingsWindow(Proto::ProjectSettings& settings);

    void RenderProtogenPanelsWindow(const Proto::Protogen& protogen);

}