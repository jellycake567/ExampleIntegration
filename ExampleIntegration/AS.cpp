#include "AS.h"

AS::AS()
{
	keeprunning = true;
	engine = asCreateScriptEngine();
	RegisterStdString(engine);
   
}

void AS::Load()
{
	LoadScript(engine, "test.as");
}

void AS::Update()
{
	ExecuteMain(engine);
}


void MessageCallback(const asSMessageInfo* msg, void* param)
{
    const char* type = "ERR ";
    if (msg->type == asMSGTYPE_WARNING)
        type = "WARN";
    else if (msg->type == asMSGTYPE_INFORMATION)
        type = "INFO";
    printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}


void LoadScript(asIScriptEngine* enginePointer, const char* filename)
{
    // The CScriptBuilder helper is an add-on that loads the file,
// performs a pre-processing pass if necessary, and then tells
// the engine to build a script module.
    CScriptBuilder builder;
    int r = builder.StartNewModule(enginePointer, "MyModule");
    if (r < 0)
    {
        // If the code fails here it is usually because there
        // is no more memory to allocate the module
        printf("Unrecoverable error while starting a new module.\n");
        return;
    }
    r = builder.AddSectionFromFile(filename);
    if (r < 0)
    {
        // The builder wasn't able to load the file. Maybe the file
        // has been removed, or the wrong name was given, or some
        // preprocessing commands are incorrectly written.
        printf("Please correct the errors in the script and try again.\n");
        return;
    }
    r = builder.BuildModule();
    if (r < 0)
    {
        // An error occurred. Instruct the script writer to fix the 
        // compilation errors that were listed in the output stream.
        printf("Please correct the errors in the script and try again.\n");
        return;
    }
}

void ExecuteMain(asIScriptEngine* enginePointer)
{

    // Find the function that is to be called. 
    asIScriptModule* mod = enginePointer->GetModule("MyModule");
    asIScriptFunction* func = mod->GetFunctionByDecl("void main()");
    if (func == 0)
    {
        // The function couldn't be found. Instruct the script writer
        // to include the expected function in the script.
        printf("void main() could not be found\n");
        return;
    }

    // Create our context, prepare it, and then execute
    asIScriptContext* ctx = enginePointer->CreateContext();
    ctx->Prepare(func);
    int r = ctx->Execute();
    if (r != asEXECUTION_FINISHED)
    {
        // The execution didn't complete as expected. Determine what happened.
        if (r == asEXECUTION_EXCEPTION)
        {
            // An exception occurred, let the script writer know what happened so it can be corrected.
            printf("An exception '%s' occurred. Please correct the code and try again.\n", ctx->GetExceptionString());
        }
    }

    // Clean up
    ctx->Release();

}

void AS::ShowSceneByName(std::string& UIName)
{
    std::string declaredFunction = "void " + UIName;

    // Find the function that is to be called. 
    module = engine->GetModule("MyModule");
    asIScriptFunction* func = module->GetFunctionByDecl(declaredFunction.c_str());
    if (func == 0)
    {
        // The function couldn't be found. Instruct the script writer
        // to include the expected function in the script.
        printf("Check the UI name is spelt correctly\n");
        return;
    }

    // Create our context, prepare it, and then execute
    asIScriptContext* ctx = engine->CreateContext();
    ctx->Prepare(func);
    int r = ctx->Execute();
    if (r != asEXECUTION_FINISHED)
    {
        // The execution didn't complete as expected. Determine what happened.
        if (r == asEXECUTION_EXCEPTION)
        {
            // An exception occurred, let the script writer know what happened so it can be corrected.
            printf("An exception '%s' occurred. Please correct the code and try again.\n", ctx->GetExceptionString());
        }
    }

    // Clean up
    ctx->Release();

}


//lib will consist of headers + lib file
//note for making this modular:
//separate the project to Angelscript stuff that other people will use and dont have example code in the lib file