L2UIUnpack_CPPFLAGS = -std=c++11 \
    -pedantic \
    -Wall \
    -fexceptions \
    $(XML_CPPFLAGS) \
    $(AM_CPPFLAGS)

L2UIUnpack_LDADD = $(XML_LIBS)

bin_PROGRAMS = L2UIUnpack
L2UIUnpack_SOURCES = Attribute.cpp \
    Attribute.h \
    ct26.cpp \
    ct26.h \
    DumpElement.cpp \
    DumpSchema.cpp \
    Element.cpp \
    Element.h \
    ElementBase.h \
    main.cpp \
    Schema.h
