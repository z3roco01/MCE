#include "stdafx.h"
#include "Minecraft.h"
#include "GameMode.h"
#include "..\Minecraft.World\net.minecraft.world.entity.player.h"
#include "..\Minecraft.World\net.minecraft.world.level.h"
#include "..\Minecraft.World\net.minecraft.world.level.storage.h"
#include "Input.h"
#include "..\Minecraft.Client\LocalPlayer.h"
#include "Options.h"
#ifdef _WINDOWS64
#include "Windows64\Keybinds.h"
#include "Windows64\KeyboardMouseInput.h"
#endif

Input::Input()
{
	xa = 0;
	ya = 0;
	wasJumping = false;
	jumping = false;
	sneaking = false;
	sneakingToggle = false;

	lReset = false;
    rReset = false;
}

void Input::tick(LocalPlayer *player)
{
	// 4J Stu -  Assume that we only need one input class, even though the java has subclasses for keyboard/controller
	// This function is based on the ControllerInput class in the Java, and will probably need changed
	//OutputDebugString("INPUT: Beginning input tick\n");

	Minecraft *pMinecraft=Minecraft::GetInstance();
	int iPad=player->GetXboxPad();

	// 4J-PB minecraft movement seems to be the wrong way round, so invert x!
	if( pMinecraft->localgameModes[iPad]->isInputAllowed(MINECRAFT_ACTION_LEFT) || pMinecraft->localgameModes[iPad]->isInputAllowed(MINECRAFT_ACTION_RIGHT) )
		xa = -InputManager.GetJoypadStick_LX(iPad);
	else
		xa = 0.0f;
	
	if( pMinecraft->localgameModes[iPad]->isInputAllowed(MINECRAFT_ACTION_FORWARD) || pMinecraft->localgameModes[iPad]->isInputAllowed(MINECRAFT_ACTION_BACKWARD) )
		ya = InputManager.GetJoypadStick_LY(iPad);
	else
		ya = 0.0f;

#ifdef _WINDOWS64
	// allow movement with keyboard, only for player 1
	if(iPad == 0)
	{
		// keep track of keyboard acceleration, later do proper math to it and controller acceleration
		float kbXa = 0.0f, kbYa = 0.0f;
		if(g_KMInput.IsKeyDown(KB_ACTION_FORWARD)) kbYa += 1.0f;
		if(g_KMInput.IsKeyDown(KB_ACTION_BACKWARD)) kbYa -= 1.0f;
		// as above, minecraft movement is "the wrong way round, so invert x!"
		if(g_KMInput.IsKeyDown(KB_ACTION_LEFT)) kbXa += 1.0f;
		if(g_KMInput.IsKeyDown(KB_ACTION_RIGHT)) kbXa -= 1.0f;

		// normalize movement when going diagonal
		// values will only be -1 or 1, so can cheat by multiplying by 0.7071...., which will make sqrt(x^2, y^2) = 1
		if(kbXa != 0.0f && kbYa != 0.0f) 
		{
			kbXa *= 0.7071f;
			kbYa *= 0.7071f;
		}

		// TODO: Allow controller and keyboard movement...
		// temporarily fully override controller movement
		xa = kbXa;
		ya = kbYa;
	}
#endif

#ifndef _CONTENT_PACKAGE
	if (app.GetFreezePlayers())
	{
		xa = ya = 0.0f;
		player->abilities.flying = true;
	}
#endif
	
    if (!lReset)
    {
        if (xa*xa+ya*ya==0.0f)
        {
            lReset = true;
        }
        xa = ya = 0.0f;
    }

	// 4J - in flying mode, don't actually toggle sneaking
	if(!player->abilities.flying)
	{
		if((player->ullButtonsPressed&(1LL<<MINECRAFT_ACTION_SNEAK_TOGGLE)) && pMinecraft->localgameModes[iPad]->isInputAllowed(MINECRAFT_ACTION_SNEAK_TOGGLE))
		{
			sneakingToggle=!sneakingToggle;
		}

#ifdef _WINDOWS64
		// handle sneaking on keyboard, intergrating into gamepad sneaking
		if(iPad == 0 && g_KMInput.IsKeyDown(KB_ACTION_SNEAK)) sneaking = true;
		else sneaking = sneakingToggle;
#else
		// if not on windows, bypass keyboard sneaking totally
		sneaking = sneakingToggle
#endif
	}

	if(sneaking)
	{
		xa*=0.3f;
		ya*=0.3f;
	}

    float turnSpeed = 50.0f;

	float tx = 0.0f;
	float ty = 0.0f;
	if( pMinecraft->localgameModes[iPad]->isInputAllowed(MINECRAFT_ACTION_LOOK_LEFT) || pMinecraft->localgameModes[iPad]->isInputAllowed(MINECRAFT_ACTION_LOOK_RIGHT) )
		tx = InputManager.GetJoypadStick_RX(iPad)*(((float)app.GetGameSettings(iPad,eGameSetting_Sensitivity_InGame))/100.0f); // apply sensitivity to look
	if( pMinecraft->localgameModes[iPad]->isInputAllowed(MINECRAFT_ACTION_LOOK_UP) || pMinecraft->localgameModes[iPad]->isInputAllowed(MINECRAFT_ACTION_LOOK_DOWN) )
		ty = InputManager.GetJoypadStick_RY(iPad)*(((float)app.GetGameSettings(iPad,eGameSetting_Sensitivity_InGame))/100.0f); // apply sensitivity to look
	
#ifndef _CONTENT_PACKAGE
	if (app.GetFreezePlayers())	tx = ty = 0.0f;
#endif

	// 4J: WESTY : Invert look Y if required.
	if ( app.GetGameSettings(iPad,eGameSetting_ControlInvertLook) )
	{
		ty = -ty;
	}

    if (!rReset)
    {
        if (tx*tx+ty*ty==0.0f)
        {
            rReset = true;
        }
        tx = ty = 0.0f;
    }
	player->interpolateTurn(tx * abs(tx) * turnSpeed, ty * abs(ty) * turnSpeed);
        
    //jumping = controller.isButtonPressed(0);

	
	unsigned int jump = InputManager.GetValue(iPad, MINECRAFT_ACTION_JUMP);
	if( jump > 0 && pMinecraft->localgameModes[iPad]->isInputAllowed(MINECRAFT_ACTION_JUMP) )
		jumping = true;
	else
 		jumping = false;

#ifdef _WINDOWS64
	if(iPad == 0 && g_KMInput.IsKeyDown(KB_ACTION_JUMP))
		jumping = true;
#endif

#ifndef _CONTENT_PACKAGE
	if (app.GetFreezePlayers())	jumping = false;
#endif

	//OutputDebugString("INPUT: End input tick\n");
}