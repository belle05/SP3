CC = gcc
OBJS = SPMiniMaxNode.o SPMiniMax.o SPFIARGame.o SPArrayList.o SPFIARParser.o SPMainAux.o main.o
EXEC = SPFIAR
GAME_TEST_OBJS = SPArrayList.o SPFIARGame.o SPFIARGameUnitTest.o
ARRAY_LIST_TEST_OBJS = SPArrayListUnitTestTest.o SPArrayList.o
PARSER_TEST_OBJS = SPFIARParser.o SPFIARParserUnitTest.o
MINMAXNode_TEST_OBJ = SPMiniMaxNode.o SPMiniMaxNodeUnitTest.o SPFIARGame.o SPArrayList.o
MINMAX_TEST_OBJ = SPMiniMaxNode.o SPMiniMax.o SPMiniMaxUnitTest.o SPFIARGame.o SPArrayList.o
MAINAUX_TEST_OBJS = SPMainAux.o SPArrayList.o SPFIARGame.o SPMiniMax.o SPMiniMaxNode.o
COMP_FLAG = -std=c99 -Wall -Wextra \
-Werror -pedantic-errors
UNIT_TESTS = SPFIARGameUnitTest SPArrayListUnitTest SPFIARParser SPMiniMaxUnitTest\
SPMiniMaxNodeUnitTest SPMainAuxUnitTest

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
SPFIARGameUnitTest: $(GAME_TEST_OBJS)
	$(CC) $(GAME_TEST_OBJS) -o $@
SPArrayListUnitTest: $(ARRAY_LIST_TEST_OBJS)
	$(CC) $(ARRAY_LIST_TEST_OBJS) -o $@
SPFIARParser: $(PARSER_TEST_OBJS)
	$(CC) $(PARSER_TEST_OBJS) -o $@
SPMiniMaxUnitTest: $(MINMAX_TEST_OBJ)
	$(CC) $(MINMAXNode_TEST_OBJ) -o $@
SPMiniMaxNodeUnitTest: $(MINMAXNode_TEST_OBJ)
	$(CC) $(MINMAXNode_TEST_OBJ) -o $@
SPMainAuxUnitTest: $(MAINAUX_TEST_OBJS)
	$(CC) $(MAINAUX_TEST_OBJS) -o $@
SPFIARGameUnitTest.o: SPFIARGameUnitTest.c unit_test_util.h SPArrayList.h SPFIARGame.h
	$(CC) $(COMP_FLAG) -c $*.c
SPArrayListUnitTest.o: SPArrayListUnitTest.c SPArrayList.h unit_test_util.h
	$(CC) $(COMP_FLAG) -c $*.c
SPFIARParserUnitTest.o: SPFIARParserUnitTest.c SPFIARParser.h unit_test_util.h
	$(CC) $(COMP_FLAG) -c $*.c
SPMiniMaxUnitTest.o: SPMiniMaxUnitTest.c SPMiniMax.h SPFIARGame.h SPMiniMaxNode.h unit_test_util
	$(CC) $(COMP_FLAG) -c $*.c
SPMiniMaxNodeUnitTest.o: SPMiniMaxNodeUnitTest.c SPMiniMaxNode.h unit_test_util SPFIARGame.h
	$(CC) $(COMP_FLAG) -c $*.c
SPArrayList.o: SPArrayList.h SPArrayList.c
	$(CC) $(COMP_FLAG) -c $*.c
SPFIARGame.o: SPFIARGame.c SPFIARGame.h SPArrayList.h
	$(CC) $(COMP_FLAG) -c $*.c
SPFIARParser.o: SPFIARParser.c SPFIARParser.h
	$(CC) $(COMP_FLAG) -c $*.c
SPMiniMaxNode.o: SPMiniMaxNode.c SPMiniMaxNode.h SPFIARGame.h
	$(CC) $(COMP_FLAG) -c $*.c 
SPMiniMax.o: SPMiniMax.c SPMiniMax.h SPMiniMaxNode.h SPFIARGame.h
	$(CC) $(COMP_FLAG) -c $*.c
SPMainAux.o: SPMainAux.c SPMainAux.h SPFIARGame.h SPMiniMax.h
	$(CC) $(COMP_FLAG) -c $*.c
main.o: main.c SPMainAux.h SPFIARGame.h SPMiniMax.h
	$(CC) $(COMP_FLAG) -c $*.c
clean:
	rm -f *.o $(EXEC) $(UNIT_TESTS)
