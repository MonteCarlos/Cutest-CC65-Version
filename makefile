cflags = -std=c11 -fplan9-extensions

CuStringDir = CuString
CuAllocDir = CuAlloc
CuStringLib = $(CuStringDir)/libCutestString-cc65.a
CuAllocLib = $(CuAllocDir)/libCuAlloc.a
CuStringDbgLib = $(CuStringDir)/libCutestString-cc65_dbg.a
CuAllocDbgLib = $(CuAllocDir)/libCuAllocDbg.a

incdirs = ../ /home/mc78/Dokumente/Programmieren/EigeneCProgramme/MCLib/
Iincdirs = $(addprefix -I, $(incdirs))
libdirs = CuString/ CuAlloc/ /home/mc78/Dokumente/Programmieren/EigeneCProgramme/MCLib/
Llibdirs = $(addprefix -L, $(libdirs))

libs = CuString CuAlloc MCLib

sources = $(wildcard *.c)
objects = $(patsubst %.c, %.o, $(sources))
gccDbgDir=obj/gccDebug
gccRelDir=obj/gccRelease
gccUTestsDir=obj/gccUTests
targets = $(CuStringLib) $(CuAllocLib) gccDebug gccRelease gccUTests

# filter all %.c source-files whose filename begins with "test". These
# files are considered sources containing tests
# These files should not be linked into the libraries
testsources = main.c AllTests.c CuTestTest.c CuTestTest_shared.c CuTest_setup.c

testobjects = $(patsubst %.c, %.o, $(testsources))

$(gccDbgDir) $(gccRelDir) $(gccUTestsDir):
	mkdir $@

$(gccDbgDir)/%.o: %.c
	gcc $(cflags) $(Iincdirs) -c -g -o $@ $<
$(gccRelDir)/%.o: %.c
	gcc $(cflags) $(Iincdirs) -c -O2 -o $@ $<
$(gccUTestsDir)/%.o: %.c
	gcc $(cflags) $(Iincdirs) -c -g -DNDEBUG -o $@ $<

.PHONY: $(CuStringLib)
$(CuStringLib):
	$(MAKE) -C $(CuStringDir)

.PHONY: $(CuAllocLib)
$(CuAllocLib):
	$(MAKE) -C $(CuAllocDir)

all: $(targets)


gccDebug: $(gccDbgDir) $(addprefix $(gccDbgDir)/, $(filter-out $(testobjects), $(objects)))
	@echo
	@echo "**** Compiling DEBUG ****"
	@echo "****"
	ar rcs libCuTestDbg.a $(filter-out $<, $?)

gccRelease: $(gccRelDir) $(addprefix $(gccRelDir)/, $(filter-out $(testobjects), $(objects)))
	@echo
	@echo "**** Compiling RELEASE ****"
	@echo "****"
	ar rcs libCuTest.a $(filter-out $<, $?)

gccUTests: $(gccUTestsDir) $(addprefix $(gccUTestsDir)/, $(objects))
	@echo
	@echo "**** Making TESTS ****"
	@echo "****"
	g++ -g $(filter-out $<, $?) $(Llibdirs) $(addprefix -l,$(libs))  -o CuTest_UTests.exe

.PHONY: cleangccDebug
.PHONY: cleangccRelease
.PHONY: cleanUTests
.PHONY: cleanAll

cleanAll: cleangccDebug cleangccRelease cleanUTests
cleangccDebug:
	/bin/rm -f $(addprefix $(gccDbgDir)/, $(filter-out $(testobjects), $(objects)))
cleangccRelease:
	/bin/rm -f $(addprefix $(gccRelDir)/, $(filter-out $(testobjects), $(objects)))
cleanUTests:
	/bin/rm -f $(addprefix $(gccUTestsDir)/, $(testobjects))

