/**
 * @file SceneSwap.cpp
 * @date 4-Aug-2019
 */

#include "orx.h"

/*
 * This is a basic code template to quickly and easily get started with a project or tutorial.
 */


/** Update function
 */
void orxFASTCALL Update(const orxCLOCK_INFO *_pstInfo, void *_pContext)
{
    orxConfig_PushSection("Main");
    for(orxS32 i = 0, iCount = orxConfig_GetListCount("Transitions"); i < iCount; i++)
    {
        const orxSTRING zTransition = orxConfig_GetListString("Transitions", i);
        if(orxInput_HasBeenActivated(zTransition))
        {
            orxObject_CreateFromConfig(zTransition);
            break;
        }
    }
    orxConfig_PopSection();
}

/** Init function, it is called when all orx's modules have been initialized
 */
orxSTATUS orxFASTCALL Init()
{
    // Display a small hint in console
    orxLOG("\n* This template project creates a viewport/camera couple and an object"
    "\n* You can play with the config parameters in ../data/config/SceneSwap.ini"
    "\n* After changing them, relaunch the executable to see the changes.");

    // Create the viewport
    orxViewport_CreateFromConfig("Viewport");

    // Registers update function
    orxClock_Register(orxClock_FindFirst(orx2F(-1.0f), orxCLOCK_TYPE_CORE), &Update, orxNULL, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL);

    // Done!
    return orxSTATUS_SUCCESS;
}

/** Run function, it is called every clock cycle
 */
orxSTATUS orxFASTCALL Run()
{
    orxSTATUS eResult = orxSTATUS_SUCCESS;

    // Should quit?
    if(orxInput_IsActive("Quit"))
    {
        // Update result
        eResult = orxSTATUS_FAILURE;
    }

    // Done!
    return eResult;
}

/** Exit function, it is called before exiting from orx
 */
void orxFASTCALL Exit()
{
    // Let Orx clean all our mess automatically. :)
}

/** Bootstrap function, it is called before config is initialized, allowing for early resource storage definitions
 */
orxSTATUS orxFASTCALL Bootstrap()
{
    // Add a config storage to find the initial config file
    orxResource_AddStorage(orxCONFIG_KZ_RESOURCE_GROUP, "../data/config", orxFALSE);

    // Return orxSTATUS_FAILURE to prevent orx from loading the default config file
    return orxSTATUS_SUCCESS;
}

/** Main function
 */
int main(int argc, char **argv)
{
    // Set the bootstrap function to provide at least one resource storage before loading any config files
    orxConfig_SetBootstrap(Bootstrap);

    // Execute our game
    orx_Execute(argc, argv, Init, Run, Exit);

    // Done!
    return EXIT_SUCCESS;
}
