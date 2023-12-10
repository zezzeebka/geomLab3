#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <cmath>
#include "rfuncsprite.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "imgui-SFML.h"
#include "imgui.h"

#pragma once

void RenderUI(int &_normalType,std::function<void()> gradClear, std::function<void()> buttonCallback, std::function<void(char* buffer)> saveImage, char buffer[256]) {
    ImGui::Begin("Menu");
    if (ImGui::Button("Default"))
    {
        _normalType = 0;
        buttonCallback();
        gradClear();
    }
    if (ImGui::Button("Nx")) {
        _normalType = 1;
        buttonCallback();
        gradClear();
    }

    if (ImGui::Button("Ny")) {
        _normalType = 2;
        buttonCallback();
        gradClear();
    }

    if (ImGui::Button("Nz")) {
        _normalType = 3;
        buttonCallback();
        gradClear();
    }

    if (ImGui::Button("Nw")) {
        _normalType = 4;
        buttonCallback();
        gradClear();
    }
    if (ImGui::Button("Show All"))
    {
        _normalType = 5;
        buttonCallback();
        gradClear();
    }

    ImGui::InputText("Enter Filename", buffer, IM_ARRAYSIZE(buffer));
    if (ImGui::Button("Save"))
    {
        saveImage(buffer);
    }
    if (ImGui::Button("Clear grad"))
    {
        gradClear();
    }
    ImGui::End();
}





float ROr(float w1, float w2)
{
    return w1+w2+sqrt(w1*w1+w2*w2);
}
float RAnd(float w1, float w2)
{
    return w1+w2-sqrt(w1*w1+w2*w2);
}
float ROtr(float w1)
{
    return -w1;
}

int main() {
    char buffer[256] = "";
    int _normalType = 0;
    RFuncSprite rFuncSprite;
    rFuncSprite.Create(sf::Vector2u(300, 300));
    sf::FloatRect floatRect(-2, -2, 4, 4);
    auto myFunc = [](const sf::Vector2f& point) -> float
    {
        auto a = 1-(point.x)*(point.x)-point.y*point.y;
        auto b = 1-(point.x-1)*(point.x-1)-point.y*point.y;
        auto c = 1-(point.x)*(point.x)-(point.y+1)*(point.y+1);
        auto d = 1-(point.x)*(point.x)-(point.y-1)*(point.y-1);
        auto e = 1-(point.x+1)*(point.x+1)-point.y*point.y;
        //return ROr(a,ROr(b,ROr(c,ROr(d,e))));
        return a;
    };

    auto buttonCallback = [&]() {
        rFuncSprite.DrawRFunc(myFunc, floatRect, _normalType);
    };

    auto saveImage = [&](char* buffer)
    {
        rFuncSprite.getImage(_normalType).saveToFile(std::string(buffer) + ".png");
    };

    auto gradClear = [&]()
    {
        rFuncSprite.gradientClear();
    };


    rFuncSprite.DrawRFunc(myFunc, floatRect, _normalType);

    sf::RenderWindow window(sf::VideoMode(1280, 720), "ImGui + SFML = <3", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    //sf::CircleShape shape(300.f);
    //shape.setFillColor(sf::Color::Green);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            rFuncSprite.HandleEvent(event, window, _normalType);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        //RenderUI(_normalType, buttonCallback, saveImage);
        //ImGui::ShowDemoWindow();

        window.clear();
        rFuncSprite.render(window, _normalType);
        RenderUI(_normalType, gradClear, buttonCallback, saveImage, buffer);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
