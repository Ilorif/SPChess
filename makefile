all: chessprog

CC = gcc
OBJS = SPMiniMaxNode.o SPMiniMax.o SPPiece.o SPGame.o SPArrayList.o SPParser.o \
 SPMainAux.o SPColorWin.o SPDifficulty.o SPMainWin.o SPplayersWin.o SPSlot.o \
 SPGameWin.o SPGUIManager.o chessprog.o
EXEC = chessprog
COMP_FLAG = -std=c99 -Wall -Wextra \
-Werror -pedantic-errors

SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@
SPArrayList.o: SPArrayList.h SPArrayList.c
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPParser.o: SPParser.c SPParser.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPGame.o: SPGame.c SPGame.h SPParser.h SPArrayList.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPPiece.o: SPPiece.c SPPiece.h SPGame.h SPParser.h SPArrayList.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPMiniMaxNode.o: SPMiniMaxNode.c SPMiniMaxNode.h SPPiece.h SPGame.h \
 SPParser.h SPArrayList.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPMiniMax.o: SPMiniMax.c SPMiniMax.h SPGame.h SPParser.h SPArrayList.h \
 SPMiniMaxNode.h SPPiece.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPMainAux.o:  SPMainAux.c SPMainAux.h SPGame.h SPParser.h SPArrayList.h \
 SPMiniMax.h SPMiniMaxNode.h SPPiece.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPColorWin.o: SPColorWin.c SPColorWin.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPDifficulty.o: SPDifficulty.c SPDifficulty.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPMainWin.o: SPMainWin.c SPMainWin.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPSlot.o: SPSlot.c SPSlot.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPplayersWin.o: SPplayersWin.c SPplayersWin.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPGameWin.o: SPGameWin.c SPGameWin.h SPGame.h SPParser.h SPArrayList.h \
 SPPiece.h SPMainAux.h SPMiniMax.h SPMiniMaxNode.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPGUIManager.o:  SPGUIManager.c SPGUIManager.h SPGameWin.h SPGame.h \
 SPParser.h SPArrayList.h SPPiece.h SPMainAux.h SPMiniMax.h \
 SPMiniMaxNode.h SPMainWin.h SPSlot.h SPplayersWin.h SPColorWin.h \
 SPDifficulty.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
chessprog.o: chessprog.c SPGame.h SPParser.h SPArrayList.h SPMainAux.h \
 SPMiniMax.h SPMiniMaxNode.h SPPiece.h SPGUIManager.h SPGameWin.h \
 SPMainWin.h SPSlot.h SPplayersWin.h SPColorWin.h SPDifficulty.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
clean:
	rm -f *.o $(EXEC)
