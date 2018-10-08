cflags = -std=gnu11 -fplan9-extensions

outputbasename = CuString
incdirs = ../ /home/mc78/Dokumente/Programmieren/EigeneCProgramme/MCLib/
Iincdirs = $(addprefix -I, $(incdirs))
libdirs = . .. ../CuAlloc /home/mc78/Dokumente/Programmieren/EigeneCProgramme/MCLib
Llibdirs = $(addprefix -L, $(libdirs))

libs = MCLib

sources = $(wildcard *.c)
objects = $(patsubst %.c, %.o, $(sources))
gccDbgDir=obj/gccDebug
gccRelDir=obj/gccRelease
gccUTestsDir=obj/gccUTests
gccTests2Dir=obj/gccTests2
targets = gccDebug gccRelease gccUTest
#gccTests2 #removed from targets because it prevents compilation of project


# filter all %.c source-files whose filename begins with "test". These
# files are considered sources containing tests
# These files should not be linked into the libraries
testsources = RunAllTests.c main.c
testsources2 = CuStringUnitTests.c

#$(filter $(wildcard test*.c *Test.c *Tests.c), $(sources)) main.c
testobjects = $(patsubst %.c, %.o, $(testsources))
testobjects2 = $(patsubst %.c, %.o, $(testsources2))

$(gccDbgDir)/%.o: %.c
	gcc $(cflags) $(Iincdirs) -c -g -o $@ $<
$(gccRelDir)/%.o: %.c
	gcc $(cflags) $(Iincdirs) -c -O2 -o $@ $<
$(gccUTestsDir)/%.o: %.c
	gcc $(cflags) $(Iincdirs) -c -g -DNDEBUG -o $@ $<
$(gccTests2Dir)/%.o: %.c
	gcc $(cflags) $(Iincdirs) -I/home/mc78/Dokumente/Programmieren/EigeneCPPProgramme/UnitTesting/minunit -c -g -DNDEBUG -o $@ $<

all: $(targets)

gccDebug: $(addprefix $(gccDbgDir)/, $(filter-out $(testobjects) $(testobjects2), $(objects)))
	@echo
	@echo "**** Compiling DEBUG ****"
	@echo "****"
	ar rcs lib$(outputbasename)Dbg.a $?

gccRelease: $(addprefix $(gccRelDir)/, $(filter-out $(testobjects) $(testobjects2), $(objects)))
	@echo
	@echo "**** Compiling RELEASE ****"
	@echo "****"
	ar rcs lib$(outputbasename).a $?

gccUTest: $(addprefix $(gccUTestsDir)/, $(filter-out $(testobjects2), $(objects)))
	@echo
	@echo "**** Making TESTS ****"
	@echo "****"
	g++ -g $(Llibdirs) -o $(outputbasename)_tests.exe $? -Wl,--start-group $(addprefix -l,$(libs)) ../libcutest.a ../CuAlloc/libCuAlloc.a -Wl,--end-group

gccTests2: $(addprefix $(gccTests2Dir)/, $(filter-out $(testobjects), $(objects)))
	@echo
	@echo "**** Making TESTS2 ****"
	@echo "****"
	g++ -g -o $(outputbasename)_tests2.exe $? $(Llibdirs) -Wl,--start-group $(addprefix -l,$(libs)) -Wl,--end-group



.PHONY: cleangccDebug
.PHONY: cleangccRelease
.PHONY: cleangccUTest
.PHONY: cleangccTests2
.PHONY:	cleanall

cleanall: cleangccDebug cleangccRelease cleangccUTest cleangccTests2

cleangccDebug:
	/bin/rm -f $(addprefix $(gccDbgDir)/, $(filter-out $(testobjects), $(objects)))
cleangccRelease:
	/bin/rm -f $(addprefix $(gccRelDir)/, $(filter-out $(testobjects), $(objects)))
cleangccUTest:
	/bin/rm -f $(addprefix $(gccUTestsDir)/, $(objects))
cleangccTests2:
	/bin/rm -f $(addprefix $(gccTests2Dir)/, $(objects))

