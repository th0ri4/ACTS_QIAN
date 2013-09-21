AUTOMAKE_OPTIONS=foreign
INCLUDES=-I./include -I/usr/include/
bin_PROGRAMS=acts
acts_SOURCES=testTraderApi.cpp TraderSpi.cpp TraderSpi.h PgsqlConfig.cpp PgsqlConfig.h \
	     Log.cpp Log.h
acts_LDFLAGS=./lib/thosttraderapi.so -lpqxx -lpq
