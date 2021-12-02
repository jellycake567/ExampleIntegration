#pragma once
#include <angelscript.h>
#include <string>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


void Print(std::string& msg);
void Print(int num);
void Print(float num);
void Print(bool value);
void PauseSystem();
void Quit();

//ImGui
void BeginWindow(std::string& windowName);
void EndWindow();
float CreateSliderFloat(const std::string label, float number, float min, float max);
bool CreateButton(float width, float height, const std::string& text);
bool CreateCheckbox(std::string& label, bool value);
bool BeginTabItem(std::string& label);
void EndTabItem();
bool BeginTabBar(std::string& string);
void EndTabBar();
void DisplayText(std::string& string);
int InputInt(std::string& string, int number);

