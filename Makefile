ROOT_MAJOR_VER := $(shell root-config --version | sed -E 's/^([0-9]*)\..*$\/\1/')
ROOT_CFLAGS=`root-config --cflags`
ROOT_LIBS=`root-config --libs` -lRMySQL
INCLUDE_PATH=-I/usr/include/mysql/server

CFLAGS=$(ROOT_CFLAGS) -fPIC -Wall -Wshadow

obj = vtbl.o \
	vtblFactory.o \
	tblFIR_Pyrometer_Info.o \
	tblL3_Array_TriggerInfo.o \
	tblL3_Telescope_TriggerInfo.o \
	tblRun_Info.o \
        tblWeather_Status.o \
	tbl2root.o
dictobj = vtblDict.o \
	vtblFactoryDict.o \
	tblFIR_Pyrometer_InfoDict.o \
	tblL3_Array_TriggerInfoDict.o \
	tblL3_Telescope_TriggerInfoDict.o \
	tblRun_InfoDict.o \
        tblWeather_StatusDict.o \
	tbl2rootDict.o
dictheader = vtblDict.h \
	vtblFactoryDict.h \
	tblFIR_Pyrometer_InfoDict.h \
	tblL3_Array_TriggerInfoDict.h \
	tblL3_Telescope_TriggerInfoDict.h \
	tblRun_InfoDict.h \
        tblWeather_StatusDict.h \
	tbl2rootDict.h
dictsource = vtblDict.C \
	vtblFactoryDict.C \
	tblFIR_Pyrometer_InfoDict.C \
	tblL3_Array_TriggerInfoDict.C \
	tblL3_Telescope_TriggerInfoDict.C \
	tblRun_InfoDict.C \
        tblWeather_StatusDict.C \
	tbl2rootDict.C
dictlinkdef = vtblLinkDef.h \
	vtblFactoryLinkDef.h \
	tblFIR_Pyrometer_InfoLinkDef.h \
	tblL3_Array_TriggerInfoLinkDef.h \
	tblL3_Telescope_TriggerInfoLinkDef.h \
	tblRun_InfoLinkDef.h \
        tblWeather_StatusLinkDef.h \
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
		*_C.so *_C.d *_cxx.so *_cxx.d
