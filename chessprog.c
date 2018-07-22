/*
 ============================================================================
 Name        : chessprog.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_video.h>

#include "SPGame.h"
#include "SPParser.h"
#include "SPMainAux.h"
#include "SPGUIManager.h"

int main(int argc, char *argv[]) {
	(void)argc;
	if (argv[1]==NULL || !strcmp(argv[1],"-c")) {
		SPCommand cmd;
		SPGame* game = spGameCreate();
		if (game == NULL) return 0;
		cmd = spSettingState(game);
		while (1) {
			switch (cmd.cmd) {
				case SP_QUIT:
					printf("Exiting...\n");
					spGameDestroy(game);
					return 0;
				case SP_RESET:
					cmd = spSettingState(game);
					printf("Restarting...\n");
					break;
				case SP_START:
					if (game->mode==1) cmd = spGameState1Mode(game);
					else  cmd = spGameState2Mode(game);
					break;
				case SP_EXIT:
					spGameDestroy(game);
					return 0;
				default:
					break;
			}
		}
	}
	if (!strcmp(argv[1],"-g")) {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) { //SDL2 INIT
				printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
				return 1;
			}
			SPGuiManager* manager = spManagerCreate();
			if (manager == NULL ) {
				SDL_Quit();
				return 0;
			}
			SDL_Event event;
				while (1) {
					SDL_WaitEvent(&event);
					if (spManagerHandleEvent(manager, &event) == SP_MANAGER_QUTT) {
						break;
					}
					spManagerDraw(manager);
				}
				spManagerDestroy(manager);
				SDL_Quit();
	}
	return 0;
}
