cflags = -std=c11 -fplan9-extensions

CuStringDir = CuString
CuAllocDir = CuAlloc
CuStringLib = $(CuStringDir)/CutestString-cc65_dbg
CuAllocLib = $(CuAllocDir)/CuAllocDbg

incdirs = ../ /home/mc78/Dokumente/Programmieren/EigeneCProgramme/MCLib/
Iincdirs = $(addprefix -I, $(incdirs))
libdirs = ./ ../ ../CuString/ /home/mc78/Dokumente/Programmieren/EigeneCProgramme/MCLib/
Llibdirs = $(addprefix -L, $(libdirs))

libs = cutest_Dbg MCLib

sources = $(wildcard *.c)
objects = $(patsubst %.c, %.o, $(sources))
gccDbgDir=obj/gccDebug
gccRelDir=obj/gccRelease
targets = $(CuStringLib) $(CuAllocLib) gccDebug gccRelease UTest

# filter all %.c source-files whose filename begins with "test". These
# files are considered sources containing tests
# These files should not be linked into the libraries
testsources = main.c AllTests.c CuTestTest.c CuTestTest_shared.c CuTest_setup.c

testobjects = $(patsubst %.c, %.o, $(testsources))

$(gccDbgDir)/%.o: %.c
	gcc $(cflags) $(Iincdirs) -c -g -o $@ $<
$(gccRelDir)/%.o: %.c
	gcc $(cflags) $(Iincdirs) -c -O2 -o $@ $<

.PHONY $(CuStringLib)
$(CuStringLib):
	make -f $(CuStringDir)/makefile gccDebug

.PHONY $(CuAllocLib)
$(CuAllocLib):
	make -f $(CuAllocDir)/makefile gccDebug

gccDebug: $(addprefix $(gccDbgDir)/, $(filter-out $(testsources), $(objects)))
	@echo
	@echo "**** Compiling DEBUG ****"
	@echo "****"
	ar rcs libCuAllocDbg.a $(addprefix $(gccDbgDir)/, $(filter-out $(testsources), $(objects)))

gccRelease: $(addprefix $(gccRelDir)/, $(filter-out $(testsources), $(objects)))
	@echo
	@echo "**** Compiling RELEASE ****"
	@echo "****"
	ar rcs libCuAlloc.a $(addprefix $(gccRelDir)/, $(filter-out $(testsources), $(objects)))

UTest: $(addprefix $(gccDbgDir)/, $(testobjects))
	@echo
	@echo "**** Making TESTS ****"
	@echo "****"
	g++ -g $? $(Llibdirs) $(addprefix -l,$(libs))  -o CuAlloc_tests.exe

.PHONY: cleangccDebug
.PHONY: cleangccRelease
.PHONY: cleanUTest
cleangccDebug:
	/bin/rm -f $(addprefix $(gccDbgDir)/, $(filter-out $(testobjects), $(objects)))
cleangccRelease:
	/bin/rm -f $(addprefix $(gccRelDir)/, $(filter-out $(testobjects), $(objects)))
cleanUTest:
	/bin/rm -f $(addprefix $(gccDbgDir)/, $(testobjects))

all: $(targets)
