CC=gcc
CFLAGS=-W -Wall
LDFLAGS=-L $(LIB) -lalgav
INCFLAGS=-I$(INC)
BIN=bin
LIB=lib
INC=include
OBJ=obj
SRC=src
LOG=log

ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG -g
endif

ifeq ($(VERBOSE),1)
CFLAGS += -DVERBOSE
endif

ifeq ($(GNUPLOT),1)
CFLAGS += -DGNUPLOT
endif

all: directories BRIANDAIS PLOTBRIANDAIS HYBRID PLOTHYBRID

directories: ${OBJ} ${BIN} ${LIB} ${LOG}

${OBJ}:
	mkdir -p ${OBJ}
${BIN}:
	mkdir -p ${BIN}
${LIB}:
	mkdir -p ${LIB}
${LOG}:
	mkdir -p ${LOG}

# =====
# OBJET
# =====
${OBJ}/tool.o: ${SRC}/tool.c
	${CC} -c -o $@ $< $(CFLAGS) ${INCFLAGS}

${OBJ}/BRDtree.o: ${SRC}/BRDtree.c
	${CC} -c -o $@ $< $(CFLAGS) ${INCFLAGS}

${OBJ}/THybrid.o: ${SRC}/THybrid.c
	${CC} -c -o $@ $< $(CFLAGS) ${INCFLAGS}

${OBJ}/mainTestBRD.o: ${SRC}/mainTestBRD.c
	${CC} -c -o $@ $< $(CFLAGS) ${INCFLAGS}

${OBJ}/mainTestTHybrid.o: ${SRC}/mainTestTHybrid.c
	${CC} -c -o $@ $< $(CFLAGS) ${INCFLAGS}

${OBJ}/plotBRDtree.o: ${SRC}/plotBRDtree.c
	${CC} -c -o $@ $< $(CFLAGS) ${INCFLAGS}

${OBJ}/plotTHybrid.o: ${SRC}/plotTHybrid.c
	${CC} -c -o $@ $< $(CFLAGS) ${INCFLAGS}

# ============
# BIBLIOTHEQUE
# ============
${LIB}/libalgav.a : ${OBJ}/tool.o ${OBJ}/BRDtree.o ${OBJ}/THybrid.o 
	ar -rs $@ $^

# ==========
# EXECUTABLE
# ==========
BRIANDAIS: ${LIB}/libalgav.a ${OBJ}/mainTestBRD.o
	${CC} -o ${BIN}/$@ $^ ${LDFLAGS}

HYBRID: ${LIB}/libalgav.a ${OBJ}/mainTestTHybrid.o
	${CC} -o ${BIN}/$@ $^ ${LDFLAGS}

PLOTBRIANDAIS: ${LIB}/libalgav.a ${OBJ}/plotBRDtree.o
	${CC} -o ${BIN}/$@ $^ ${LDFLAGS}

PLOTHYBRID: ${LIB}/libalgav.a ${OBJ}/plotTHybrid.o
	${CC} -o ${BIN}/$@ $^ ${LDFLAGS}

.PHONY: all proper clean cleanall runTESTBRD runTESTHYB runPLOTBRDFIL runPLOTBRDDIR runPLOTHYB plot

proper:
	rm -f ${INC}/*~ ${SRC}/*~ ${LOG}/*~ *~

clean: proper
	rm -f ${OBJ}/* ${BIN}/* ${LIB}/* ${LOG}/briandais.* ${LOG}/hybrid.*

cleanall: clean
	rm -rf ${OBJ} ${BIN} ${LIB}

runTESTBRD:
	@echo "+++++++++"
	@echo "BRIANDAIS"
	@echo "+++++++++"
	@echo ""
	@./$(BIN)/BRIANDAIS
	@echo

runTESTHYB:
	@echo "++++++"
	@echo "HYBRID"
	@echo "++++++"
	@echo ""
	@./$(BIN)/HYBRID
	@echo

runPLOTBRDFIL:
	@./$(BIN)/PLOTBRIANDAIS F test/dactylo > log/briandais.dat

runPLOTBRDDIR:
	@./$(BIN)/PLOTBRIANDAIS D test/shakespeare > log/briandais.dat

runPLOTHYB:
	@./$(BIN)/PLOTHYBRID test/dactylo > log/hybrid.dat

plot: runPLOTBRDFIL runPLOTHYB