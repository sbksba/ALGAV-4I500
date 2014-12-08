CC=gcc
CFLAGS=-W -Wall
LDFLAGS=-L $(LIB) -lalgav -lrt -lpthread
INCFLAGS=-I$(INC)
BIN=bin
LIB=lib
INC=include
OBJ=obj
SRC=src
DATA=data
IMG=images

ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG -g
endif

ifeq ($(VERBOSE),1)
CFLAGS += -DVERBOSE
endif

ifeq ($(GNUPLOT),1)
CFLAGS += -DGNUPLOT
endif

all: directories BRIANDAIS PLOTBRIANDAIS HYBRID PLOTHYBRID TIMEADD TIMEDEL THREAD COMPARE

directories: ${OBJ} ${BIN} ${LIB} ${DATA} ${IMG}

${OBJ}:
	mkdir -p ${OBJ}
${BIN}:
	mkdir -p ${BIN}
${LIB}:
	mkdir -p ${LIB}
${DATA}:
	mkdir -p ${DATA}
${IMG}:
	mkdir -p ${IMG}

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

${OBJ}/mainTimeAdd.o: ${SRC}/mainTimeAdd.c
	${CC} -c -o $@ $< $(CFLAGS) ${INCFLAGS}

${OBJ}/mainTimeDel.o: ${SRC}/mainTimeDel.c
	${CC} -c -o $@ $< $(CFLAGS) ${INCFLAGS}

${OBJ}/mainThreadBRD.o: ${SRC}/mainThreadBRD.c
	${CC} -c -o $@ $< $(CFLAGS) ${INCFLAGS}

${OBJ}/comparaison.o: ${SRC}/comparaison.c
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

TIMEADD: ${LIB}/libalgav.a ${OBJ}/mainTimeAdd.o
	${CC} -o ${BIN}/$@ $^ ${LDFLAGS}

TIMEDEL: ${LIB}/libalgav.a ${OBJ}/mainTimeDel.o
	${CC} -o ${BIN}/$@ $^ ${LDFLAGS}

THREAD: ${LIB}/libalgav.a ${OBJ}/mainThreadBRD.o
	${CC} -o ${BIN}/$@ $^ ${LDFLAGS}

COMPARE: ${LIB}/libalgav.a ${OBJ}/comparaison.o
	${CC} -o ${BIN}/$@ $^ ${LDFLAGS}

.PHONY: all proper clean cleanall runTESTBRD runTESTHYB runPLOTBRDFIL runPLOTBRDDIR runPLOTHYBFIL runPLOTHYBDIR runTIMEADD runTIMEDEL runTHREAD plotF plotD timeAdd timeDel graph cmp

proper:
	rm -f ${INC}/*~ ${SRC}/*~ ${LOG}/*~ *~

clean: proper
	rm -f ${OBJ}/* ${BIN}/* ${LIB}/* ${DATA}/* ${IMG}/*

cleanall: clean
	rm -rf ${OBJ} ${BIN} ${LIB} ${DATA} ${IMG}

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
	@./$(BIN)/PLOTBRIANDAIS F test/dactylo > ${DATA}/briandais.dat

runPLOTBRDDIR:
	@./$(BIN)/PLOTBRIANDAIS D test/shakespeare > ${DATA}/briandais.dat

runPLOTHYBFIL:
	@./$(BIN)/PLOTHYBRID F test/dactylo > ${DATA}/hybrid.dat

runPLOTHYBDIR:
	@./$(BIN)/PLOTHYBRID D test/shakespeare > ${DATA}/hybrid.dat

runTIMEADD:
	@./$(BIN)/TIMEADD > ${DATA}/timeAdd.dat

runTIMEDEL:
	@./$(BIN)/TIMEDEL > ${DATA}/timeDel.dat

runTHREAD:
	@./$(BIN)/THREAD > ${DATA}/thread.dat

plotF: runPLOTBRDFIL runPLOTHYBFIL
plotD: runPLOTBRDDIR runPLOTHYBDIR
timeAdd: runTIMEADD
timeDel: runTIMEDEL
graph: plotF timeAdd timeDel runTHREAD
	@./graph.sh
cmp:
	@./$(BIN)/COMPARE
