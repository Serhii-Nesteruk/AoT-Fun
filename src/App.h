#pragma once

#include "GameTemplate2D.h"

class App : public GameTemplate2D {
public:
    App() = default;
    ~App() override = default;

protected:
    void WorldObjectsInit();
    void SetupSystems();

    void OnInit() override;
    void OnUpdate(float) override;
    void OnRender() override;
    void OnShutdown() override;

private:
    std::unique_ptr<Texture2D> _texture;
};