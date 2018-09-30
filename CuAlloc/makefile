cflags = -std=c11 -fplan9-extensions

incdirs = ../ /home/mc78/Dokumente/Programmieren/EigeneCProgramme/MCLib/
Iincdirs = $(addprefix -I, $(incdirs))
libdirs = ./ ../ ../CuString/ /home/mc78/Dokumente/Programmieren/EigeneCProgramme/MCLib/
Llibdirs = $(addprefix -L, $(libdirs))

libs = cutest_Dbg CutestString-cc65_dbg CuAllocDbg MCLib

sources = $(wildcard *.c)
objects = $(patsubst %.c, %.o, $(sources))
gccDbgDir=obj/gccDebug
gccRelDir=obj/gccRelease
gccUTestDir=obj/gccUTests
targets = gccDebug gccRelease gccUTest

# filter all %.c source-files whose filename begins with "test". These
# files are considered sources containing tests
# These files should not be linked into the libraries
testsources = $(filter $(wildcard test*.c), $(sources))
testobjects = $(patsubst %.c, %.o, $(testsources))

$(gccDbgDir)/%.o: %.c
	gcc $(cflags) $(Iincdirs) -c -g -o $@ $<
$(gccRelDir)/%.o: %.c
	gcc $(cflags) $(Iincdirs) -c -O2 -o $@ $<
$(gccUTestDir)/%.o: %.c
	gcc $(cflags) $(Iincdirs) -c -g -DNDEBUG -o $@ $<

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

gccUTest: $(addprefix $(gccUTestDir)/, $(objects))
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
cleangccUTest:
	/bin/rm -f $(addprefix $(gccUTestDir)/, $(objects))

all: $(targets)
