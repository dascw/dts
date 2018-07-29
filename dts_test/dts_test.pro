TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -pthread
LIBS += -pthread

SOURCES += \
        main.cpp \
    ../unit_tests/enumerate_tests.cpp \
    ../unit_tests/utility_tests.cpp

HEADERS += \
    ../base_macro.h \
    ../basic.h \
    ../enumerate.h \
    ../enum_extend.h \
    ../googletest/googletest/include/gtest/internal/custom/gtest-port.h \
    ../googletest/googletest/include/gtest/internal/custom/gtest-printers.h \
    ../googletest/googletest/include/gtest/internal/custom/gtest.h \
    ../googletest/googletest/include/gtest/internal/gtest-death-test-internal.h \
    ../googletest/googletest/include/gtest/internal/gtest-filepath.h \
    ../googletest/googletest/include/gtest/internal/gtest-internal.h \
    ../googletest/googletest/include/gtest/internal/gtest-linked_ptr.h \
    ../googletest/googletest/include/gtest/internal/gtest-param-util-generated.h \
    ../googletest/googletest/include/gtest/internal/gtest-param-util.h \
    ../googletest/googletest/include/gtest/internal/gtest-port-arch.h \
    ../googletest/googletest/include/gtest/internal/gtest-port.h \
    ../googletest/googletest/include/gtest/internal/gtest-string.h \
    ../googletest/googletest/include/gtest/internal/gtest-tuple.h \
    ../googletest/googletest/include/gtest/internal/gtest-tuple.h.pump \
    ../googletest/googletest/include/gtest/internal/gtest-type-util.h \
    ../googletest/googletest/include/gtest/gtest-death-test.h \
    ../googletest/googletest/include/gtest/gtest-message.h \
    ../googletest/googletest/include/gtest/gtest-param-test.h \
    ../googletest/googletest/include/gtest/gtest-param-test.h.pump \
    ../googletest/googletest/include/gtest/gtest-printers.h \
    ../googletest/googletest/include/gtest/gtest-spi.h \
    ../googletest/googletest/include/gtest/gtest-test-part.h \
    ../googletest/googletest/include/gtest/gtest-typed-test.h \
    ../googletest/googletest/include/gtest/gtest.h \
    ../googletest/googletest/include/gtest/gtest_pred_impl.h \
    ../googletest/googletest/include/gtest/gtest_prod.h

DISTFILES += \
    ../googletest/googletest/include/gtest/internal/gtest-param-util-generated.h.pump \
    ../googletest/googletest/include/gtest/internal/gtest-type-util.h.pump

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../release/ -lgtest
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../debug/ -lgtest
else:unix: LIBS += -L$$PWD/../ -lgtest

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

INCLUDEPATH += $$PWD/../googletest/googletest/include/

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../release/libgtest.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../debug/libgtest.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../release/gtest.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../debug/gtest.lib
else:unix: PRE_TARGETDEPS += $$PWD/../libgtest.a
