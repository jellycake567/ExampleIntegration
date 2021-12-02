float volumeValue = 100.0f;
int menu = 1;
bool isFullscreen = false;
int resX = 1980;
int resY = 1080;
int fpsMax = 60;

void main()
{
	
	if (menu == 1)
	{
		ShowSceneByName("DisplayMainMenu()");
	}
	else if (menu == 2)
	{
		ShowSceneByName("DisplayOptionMenu()");
	}
	else if (menu == 3)
	{
		ShowSceneByName("DisplayCredits()");
	}
	else if (menu == 4)
	{
		Print("Fullscreen value: ");
		Print(isFullscreen);
		Print("\n");
		Print("Resolution (Width x Height): ");
		Print(resX);
		Print(" x ");
		Print(resY);
		Print("\n");
		Print("Fps cap: ");
		Print(fpsMax);
		Print("\n");
		Print("Volume value: ");
		Print(volumeValue);
		Print("\n");
		PauseSystem();
		Quit();
	}
	
	
	
}

void DisplayMainMenu()
{
	BeginWindow("Main Menu");
	if(CreateButton(200, 100, "Options"))
	{
		menu = 2;
	}
	
	if (CreateButton(200,100, "Credits"))
	{
		menu = 3;
	}
	if (CreateButton(200,100, "Quit"))
	{
		menu = 4;
	}
	
	
	EndWindow(); 
	
	
}

void DisplayOptionMenu()
{
	BeginWindow("Options");
	if(BeginTabBar("TabBar"))
	{
		if(BeginTabItem("Graphics"))
		{
			if(CreateCheckbox("Fullscreen", isFullscreen))
			{
				isFullscreen = !isFullscreen;
			}
			DisplayText("Resolution");
			resX = InputInt("width", resX);
			resY = InputInt("height", resY);
			DisplayText("Frame rate");
			fpsMax = InputInt("", fpsMax);
			EndTabItem();
		}
		if(BeginTabItem("Sound"))
		{
			DisplayText("Volume");
			volumeValue = CreateSliderFloat("Volume", volumeValue, 0.0f, 100.0f );
			EndTabItem();
		}
		EndTabBar();
	}
	if(CreateButton(200, 100, "ExtraBackButton"))
	{
		menu = 1;
	}
	if(CreateButton(200, 100, "Back"))
	{
		menu = 1;
	}

	EndWindow(); 

}
void DisplayCredits()
{

	BeginWindow("Main Menu");
	
	DisplayText("Programmer: Peter");
	
	if(CreateButton(200, 100, "Back"))
	{
		menu = 1;
	}
	
	
	EndWindow(); 

}



