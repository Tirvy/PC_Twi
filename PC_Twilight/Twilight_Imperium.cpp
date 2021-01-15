// Twilight_Imperium.cpp: главный файл проекта.

#define _CRT_SECURE_NO_WARNINGS // fopen problems with compiling under vs08.
//#define NO_HOST

#include "StdAfx.h"
 
using namespace std; 

#include "TextPaths.cpp"
#include "OuterTools\\ini_strings.cpp"

#include "Defines.cpp" // Defines
#include "nt_lib.cpp" // Ernest's functions
#include "Classes.cpp" // all the classes/structs to work with
#include "GameGlobalCreations.cpp" // Games global settings etc.

#include "headers\\Phases.h"
#include "CheatMachine.cpp"

#include "OuterTools\\GameInitiation.cpp"
#include "Graphics.cpp" // Game Graphics

#include "PhaseBuildGalaxy.cpp"// Game Logic
#include "PhasePreGame.cpp" 
#include "PhaseStrategy.cpp"
#include "PhaseAction.cpp"
#include "PhaseStatus.cpp"
#include "PhaseEndGame.cpp"

#include "Panda\\Handlers.cpp"

int main(int argc, char** argv){
	char c;
	bool stop = false;
	MenuArea Menu;
	LaunchPanda(argc, argv);
	_MapGraphics.init(&_Framework,_Window);


	try{
		Despair();//игровая часть должна начинаться с отчаяния, Zoldn
		Menu.start();
		while (_GameStats.CurPhase == gpt_pregame)
			taskMgr->poll();
		GenericAsyncTask* lol = new GenericAsyncTask("reado", &spinCameraTask, (void*) NULL);
		taskMgr->add(lol);
		_ChatArea.DrawChatAreaBack();
		_InfoArea.DrawBack();
		_MapArea.DrawBack();
		_StatusArea.DrawBack();
		_ActionArea.DrawActionAreaBack();
		BuildGalaxy();
		bool firstafterstart = true;
		while (true){
			if (!firstafterstart || (_GameStats.CurPhase == gpt_strategy)){
				StrategyPhase();
				firstafterstart = false;
			}
			if (!firstafterstart || (_GameStats.CurPhase == gpt_action)){
				ActionPhase(firstafterstart);
				firstafterstart = false;
			}
			if (!firstafterstart || (_GameStats.CurPhase == gpt_status)){
				StatusPhase();
				firstafterstart = false;
			}
		}

		/*InitIniFile();
		InitNewGame();
		CreateBasicGalaxy();
		LoadGalaxy();
		Despair();
		PreGame();
		_ChatArea.DrawChatAreaBack(0);
		_InfoArea.DrawBack();
		DrawMapArea();
		_StatusArea.DrawBack();
		_ActionArea.DrawActionAreaBack(0);
		StrategyPhase();
		ActionPhase();
		StatusPhase();*/
	}
	catch (endofgame& ext){
		EndOfGame();
	}
	catch (throwable& ext){
		std::cout<<std::endl<<"error::"<<ext.str1<<"::"<<ext.str2<<"::"<<ext.elem1<<"::"<<ext.elem2<<std::endl;
		cin>>c;
	}
	_Framework.close_framework();
	return (0);
}