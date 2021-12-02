#pragma once
#include <angelscript.h>
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>
#include "Utilities.h"
#include "ExposedFunctions.h"

class AS
{
	bool keeprunning;

public:
	asIScriptEngine* engine;
	asIScriptModule* module;

	int r;
	AS();
	void Update();
	void Load();

	virtual void ExposeFunctions() { std::cout << "This is the parent function" << "\n"; }
	void ShowSceneByName(std::string& UIName);
};
void LoadScript(asIScriptEngine* enginePointer, const char* filename);

void ExecuteMain(asIScriptEngine* enginePointer);

void MessageCallback(const asSMessageInfo* msg, void* param);


