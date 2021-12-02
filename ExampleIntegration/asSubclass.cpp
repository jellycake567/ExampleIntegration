#pragma once
#include "asSubclass.h"

asSubclass::asSubclass() : AS()
{
	ExposeFunctions();
}

void asSubclass::ExposeFunctions()
{

	r = engine->RegisterGlobalFunction("void Print(const string &in)", asFUNCTIONPR(Print, (std::string&), void), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void Print(int)", asFUNCTIONPR(Print, (int), void), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void Print(float)", asFUNCTIONPR(Print, (float), void), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void Print(bool)", asFUNCTIONPR(Print, (bool), void), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void PauseSystem()", asFUNCTION(PauseSystem), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void Quit()", asFUNCTION(Quit), asCALL_CDECL, this); assert(r >= 0);

	//ImGui
	r = engine->RegisterGlobalFunction("void BeginWindow(const string &in)", asFUNCTION(BeginWindow), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void EndWindow()", asFUNCTION(EndWindow), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("bool CreateButton(float, float, const string &in)", asFUNCTION(CreateButton), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("float CreateSliderFloat(const string &in, float, float, float)", asFUNCTION(CreateSliderFloat), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("bool CreateCheckbox(const string &in, bool)", asFUNCTION(CreateCheckbox), asCALL_CDECL); assert(r >= 0);

	r = engine->RegisterGlobalFunction("bool BeginTabItem(const string &in)", asFUNCTION(BeginTabItem), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void EndTabItem()", asFUNCTION(EndTabItem), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("bool BeginTabBar(const string &in)", asFUNCTION(BeginTabBar), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void EndTabBar()", asFUNCTION(EndTabBar), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void DisplayText(const string &in)", asFUNCTION(DisplayText), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("int InputInt(const string &in, int)", asFUNCTION(InputInt), asCALL_CDECL, this); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void ShowSceneByName(const string &in)", asMETHOD(AS, ShowSceneByName), asCALL_THISCALL_ASGLOBAL, this); assert(r >= 0);


}