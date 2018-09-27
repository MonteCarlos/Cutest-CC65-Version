cflags = -std=c11 -fplan9-extensions

incdirs = ../ /home/mc78/Dokumente/Programmieren/EigeneCProgramme/MCLib/
Iincdirs = $(addprefix -I, $(incdirs))
libdirs = ../ ../CuString/ /home/mc78/Dokumente/Programmieren/EigeneCProgramme/MCLib/
Llibdirs = $(addprefix -L, $(libdirs))

libs = cutest_Dbg CutestString-cc65_dbg MCLib

sources = $(wildcard *.c)
objects = $(patsubst %.c, %.o, $(sources))
gccDbgDir=obj/gccDebug
gccRelDir=obj/gccRelease
targets = gccDebug gccRelease UTest 

# filter all %.c source-files whose filename begins with "test". These
# files are considered sources containing tests
# These files should not be linked into the libraries
testsources = $(filter $(wildcard test*.c), $(sources)) main.c
testobjects = $(patsubst %.c, %.o, $(testsources)) 

%.o: %.c
	gcc $(cflags) $(Iincdirs) -c -g -o $(gccDbgDir)/$@ $< 
	gcc $(cflags) $(Iincdirs) -c -O2 -o $(gccRelDir)/$@ $<
	
gccDebug: $(addprefix $(gccDbgDir)/, $(filter-out $(testobjects), $(objects)))
	@echo 
	@echo "**** Compiling DEBUG ****"
	@echo "****"
	ar rcs libCuAllocDbg.a $? 
	
gccRelease: $(addprefix $(gccRelDir)/, $(objects))	
	@echo 
	@echo "**** Compiling RELEASE ****"
	@echo "****"
	ar rcs libCuAlloc.a $? 
	
UTest: $(addprefix $(gccDbgDir)/, $(objects))
	@echo 
	@echo "**** Making TESTS ****"
	@echo "****"
	g++ $? $(Llibdirs) $(addprefix -l,$(libs))  -o CuAlloc_tests.exe
	
all: $(targets)
