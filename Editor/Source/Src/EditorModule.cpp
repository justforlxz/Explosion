//
// Created by johnk on 2024/8/21.
//

#include <Editor/EditorEngine.h>
#include <Editor/EditorModule.h>

namespace Editor {
    void EditorModule::OnUnload()
    {
        Runtime::EngineHolder::Unload();
        engine.Reset();
    }

    ::Core::ModuleType EditorModule::Type() const
    {
        return ::Core::ModuleType::mStatic;
    }

    Runtime::Engine* EditorModule::CreateEngine(const Runtime::EngineInitParams& inParams)
    {
        Assert(engine == nullptr);
        engine = new EditorEngine(inParams);
        return engine.Get();
    }
}

IMPLEMENT_STATIC_MODULE(Editor, "Editor", Editor::EditorModule)