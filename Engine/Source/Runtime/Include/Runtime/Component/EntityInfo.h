//
// Created by johnk on 2022/11/18.
//

#pragma once

#include <string>

#include <Runtime/ECS.h>

namespace Runtime {
    class EClass(editorHide) EntityInfoComponent : public Component {
    public:
        EClassBody(EntityInfoComponent)

        ECtor()
        EntityInfoComponent();

        EFunc()
        const std::string& GetName() const;

        EFunc()
        void SetName(std::string inName);

    private:
        EProperty()
        std::string name;
    };
}
