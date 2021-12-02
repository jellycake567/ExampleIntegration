#include "ExposedFunctions.h"
#include <fstream>
#include <sstream>



void Print(int num)
{
    std::stringstream stream;
    stream << num;
    

    printf("%s", stream.str().c_str());
}

void Print(float num)
{
    std::stringstream stream;
    stream << num;


    printf("%s", stream.str().c_str());
}



void Print(std::string& msg)
{
    printf("%s", msg.c_str());
}

void Print(bool value)
{
    std::stringstream stream;
    stream << value;


    printf("%s", stream.str().c_str());
}


void BeginWindow(std::string& windowName)
{
    ImGui::Begin(windowName.c_str());

}

void EndWindow()
{
    ImGui::End();
}

void PauseSystem()
{
    system("pause");
}


void Quit()
{
    exit(0);
}


bool CreateButton(float width, float height, const std::string& text)
{
    bool* closingWidget = NULL;
    ImVec2 buttonSize = { width, height };
   
    bool result = ImGui::Button(text.c_str(), buttonSize);

    return result;
}

float CreateSliderFloat(const std::string label, float number, float min, float max)
{
    //float* floatPointer = &number;
    ImGui::SliderFloat(label.c_str(), &number, min, max);
    return number;
}


bool CreateCheckbox(std::string& label, bool value)
{
    return ImGui::Checkbox(label.c_str(), &value);
}

bool BeginTabItem(std::string& label)
{
    return ImGui::BeginTabItem(label.c_str());
}

void EndTabItem()
{
    ImGui::EndTabItem();
}

bool BeginTabBar(std::string& string)
{
    //ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    return ImGui::BeginTabBar(string.c_str(), ImGuiTabBarFlags_None);
}

void EndTabBar()
{
    ImGui::EndTabBar();
}

void DisplayText(std::string& string)
{
    ImGui::Text(string.c_str());
}

int InputInt(std::string& string, int number)
{
    ImGui::InputInt(string.c_str(), &number);
    return number;
}

