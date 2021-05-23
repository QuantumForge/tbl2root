ROOT_MAJOR_VER := $(shell root-config --version | sed -E 's/^([0-9]*)\..*$\/\1/')
ROOT_CFLAGS=`root-config --cflags`
ROOT_LIBS=`root-config --libs` -lRMySQL
INCLUDE_PATH=-I/usr/include/mysql/server

CFLAGS=$(ROOT_CFLAGS) -fPIC -Wall -Wshadow

obj = vtbl.o \
	vtblFactory.o \
	tblL3_Array_TriggerInfo.o \
	tblL3_Telescope_TriggerInfo.o \
	tblRun_Info.o \
	tbl2root.o
dictobj = vtblDict.o \
	vtblFactoryDict.o \
	tblL3_Array_TriggerInfoDict.o \
	tblL3_Telescope_TriggerInfoDict.o \
	tblRun_InfoDict.o \
	tbl2rootDict.o
dictheader = vtblDict.h \
	vtblFactoryDict.h \
	tblL3_Array_TriggerInfoDict.h \
	tblL3_Telescope_TriggerInfoDict.h \
	tblRun_InfoDict.h \
	tbl2rootDict.h
dictsource = vtblDict.C \
	vtblFactoryDict.C \
	tblL3_Array_TriggerInfoDict.C \
	tblL3_Telescope_TriggerInfoDict.C \
	tblRun_InfoDict.C \
	tbl2rootDict.C
dictlinkdef = vtblLinkDef.h \
	vtblFectoryLinkDef.h \
	tblL3_Array_TriggerInfoLinkDef.h \
	tblL3_Telescope_TriggerInfoLinkDef.h \
	tblRun_InfoLinkDef.h \
	tbl2rootLinkDef.h

shobj = libvtbl.so
mapobj = 
binary = #mkTreeForPartNum

DEFAULT_TARGET = $(shobj) $(binary)
DICT_GENERATOR = rootcling

all:$(DEFAULT_TARGET)

.PHONY: all clean clean-obj

$(obj): %.o: %.cxx %.h
	$(CXX) -c $(INCLUDE_PATH) $(CFLAGS) $<

$(dictobj): %Dict.o: %LinkDef.h %.o
	$(DICT_GENERATOR) -f $(*)Dict.C -multiDict -s $(shobj) $(INCLUDE_PATH) \
		$(*).h $(*)LinkDef.h
	$(CXX) -c $(*)Dict.C $(INCLUDE_PATH) $(CFLAGS)
$(shobj): $(obj) $(dictobj)
	$(CXX) -shared $^ -o $@ -Wl,-soname,$@ $(ROOT_LIBS)

clean: clean-obj
	rm -f $(shobj) $(binary) $(mapobj)
clean-obj:
	rm -f $(obj) $(dictobj) $(dictheader) $(dictsource) \
		*_rdict.pcm *_C.so *_C.d *_cxx.so *_cxx.d
