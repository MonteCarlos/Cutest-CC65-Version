cflags = -std=gnu11 -fplan9-extensions

outputbasename = CuString
incdirs = ../ /home/mc78/Dokumente/Programmieren/EigeneCProgramme/MCLib/
Iincdirs = $(addprefix -I, $(incdirs))
libdirs = ./ ../ ../CuAlloc/ /home/mc78/Dokumente/Programmieren/EigeneCProgramme/MCLib/
Llibdirs = $(addprefix -L, $(libdirs))

libs = cutest_Dbg CuAllocDbg MCLib

sources = $(wildcard *.c)
objects = $(patsubst %.c, %.o, $(sources))
gccDbgDir=obj/gccDebug
gccRelDir=obj/gccRelease
gccUTestsDir=obj/gccUTests
targets = gccDebug gccRelease gccUTest

# filter all %.c source-files whose filename begins with "test". These
# files are considered sources containing tests
# These files should not be linked into the libraries
testsources = RunAllTests.c main.c CuStringUnitTests.c
#$(filter $(wildcard test*.c *Test.c *Tests.c), $(sources)) main.c
testobjects = $(patsubst %.c, %.o, $(testsources))

$(gccDbgDir)/%.o: %.c
	gcc $(cflags) $(Iincdirs) -c -g -o $@ $<
$(gccRelDir)/%.o: %.c
	gcc $(cflags) $(Iincdirs) -c -O2 -o $@ $<
$(gccUTestsDir)/%.o: %.c
	gcc $(cflags) $(Iincdirs) -I/home/mc78/Dokumente/Programmieren/EigeneCPPProgramme/UnitTesting/minunit -c -g -DNDEBUG -o $@ $<

all: $(targets)

gccDebug: $(addprefix $(gccDbgDir)/, $(filter-out $(testobjects), $(objects)))
	@echo
	@echo "**** Compiling DEBUG ****"
	@echo "****"
	ar rcs lib$(outputbasename)Dbg.a $(addprefix $(gccDbgDir)/, $(filter-out $(testobjects), $(objects)))

gccRelease: $(addprefix $(gccRelDir)/, $(filter-out $(testobjects), $(objects)))
	@echo
	@echo "**** Compiling RELEASE ****"
	@echo "****"
	ar rcs lib$(outputbasename).a $(addprefix $(gccRelDir)/, $(filter-out $(testobjects), $(objects)))

gccUTest: $(addprefix $(gccUTestsDir)/, $(objects))
	@echo
	@echo "**** Making TESTS ****"
	@echo "****"
	g++ -g $? $(Llibdirs) $(addprefix -l,$(libs))  -o $(outputbasename)_tests.exe

.PHONY: cleangccDebug
.PHONY: cleangccRelease
.PHONY: cleangccUTest
cleangccDebug:
	/bin/rm -f $(addprefix $(gccDbgDir)/, $(filter-out $(testobjects), $(objects)))
cleangccRelease:
	/bin/rm -f $(addprefix $(gccRelDir)/, $(filter-out $(testobjects), $(objects)))
cleangccUTest:
	/bin/rm -f $(addprefix $(gccUTestsDir)/, $(objects))

