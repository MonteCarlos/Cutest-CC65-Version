cflags = -std=c11 -fplan9-extensions

incdirs = ../ /home/mc78/Dokumente/Programmieren/EigeneCProgramme/MCLib/
Iincdirs = $(addprefix -I, $(incdirs))
libdirs = . .. ../CuString /home/mc78/Dokumente/Programmieren/EigeneCProgramme/MCLib
Llibdirs = $(addprefix -L, $(libdirs))

libs = MCLib
libs2 = ../libcutest.a ../CuString/libCuString.a

sources = $(wildcard *.c)
objects = $(patsubst %.c, %.o, $(sources))
gccDbgDir=obj/gccDebug
gccRelDir=obj/gccRelease
gccUTestsDir=obj/gccUTests
targets = gccDebug gccRelease UTest

# filter all %.c source-files whose filename begins with "test". These
# files are considered sources containing tests
# These files should not be linked into the libraries
testsources = $(filter $(wildcard test*.c), $(sources))
testobjects = $(patsubst %.c, %.o, $(testsources))

$(gccDbgDir) $(gccRelDir) $(gccUTestsDir):
	mkdir $@

$(gccDbgDir)/%.o: %.c
	gcc $(cflags) $(Iincdirs) -c -g -o $@ $<
$(gccRelDir)/%.o: %.c
	gcc $(cflags) $(Iincdirs) -c -O2 -o $@ $<
$(gccUTestsDir)/%.o: %.c
	gcc $(cflags) $(Iincdirs) -c -g -DNDEBUG -o $@ $<


all: $(targets)

gccDebug: $(gccDbgDir) $(addprefix $(gccDbgDir)/, $(filter-out $(testsources), $(objects)))
	@echo
	@echo "**** Compiling DEBUG ****"
	@echo "****"
	ar rcs libCuAllocDbg.a $(filter-out $(gccDbgDir), $?)

gccRelease: $(gccRelDir) $(addprefix $(gccRelDir)/, $(filter-out $(testsources), $(objects)))
	@echo
	@echo "**** Compiling RELEASE ****"
	@echo "****"
	ar rcs libCuAlloc.a $(filter-out $(gccRelDir), $?)

UTest: $(gccUTestsDir) $(addprefix $(gccUTestsDir)/, $(objects))
	@echo
	@echo "**** Making TESTS ****"
	@echo "****"
	g++ -g $(Llibdirs) -Wl,--start-group $(filter-out $(gccUTestsDir), $?) $(addprefix -l,$(libs)) $(libs2) -Wl,--end-group -o CuAlloc_tests.exe

.PHONY: cleangccDebug
.PHONY: cleangccRelease
.PHONY: cleanUTest
cleangccDebug:
	/bin/rm -f $(addprefix $(gccDbgDir)/, $(filter-out $(testobjects), $(objects)))
cleangccRelease:
	/bin/rm -f $(addprefix $(gccRelDir)/, $(filter-out $(testobjects), $(objects)))
cleanUTest:
	/bin/rm -f $(addprefix $(gccDbgDir)/, $(testobjects))
