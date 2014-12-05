CC=gcc
CFLAGS=-W -Wall
LDFLAGS=-L$(LIB) -lrt -lpthread -ltrie
INCFLAGS=-I$(INC)
BIN=bin
LIB=lib
INC=include
OBJ=obj
SRC=src

ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG -g
endif

ifeq ($(VERBOSE),1)
CFLAGS += -DVERBOSE
endif

all: directories TRIE

directories: ${OBJ} ${BIN} ${LIB}

${OBJ}:
	mkdir -p ${OBJ}
${BIN}:
	mkdir -p ${BIN}
${LIB}:
	mkdir -p ${LIB}

# =====
# OBJET
# =====
${OBJ}/trie.o: ${SRC}/trie.c
	${CC} -c -o $@ $< $(CFLAGS) ${INCFLAGS}

${OBJ}/main.o: ${SRC}/main.c
	${CC} -c -o $@ $< $(CFLAGS) ${INCFLAGS}

# ============
# BIBLIOTHEQUE
# ============
${LIB}/libtrie.a : ${OBJ}/trie.o
	ar -rs $@ $^

# ==========
# EXECUTABLE
# ==========
TRIE: ${LIB}/libtrie.a ${OBJ}/main.o
	${CC} -o ${BIN}/$@ $^ ${LDFLAGS}

.PHONY: all proper clean cleanall runTRIE

proper:
	rm -f ${INC}/*~ ${SRC}/*~ *~ ic1

clean: proper
	rm -f ${OBJ}/* ${BIN}/* ${LIB}/*

cleanall: clean
	rm -rf ${OBJ} ${BIN} ${LIB}

run:
	./$(BIN)/TRIE
