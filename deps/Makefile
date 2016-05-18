alenka: 
	cd Alenka && \
	export REDIS_FLAGS="-I../deps/redis3m/include/ -DDATADICT_REDIS_SIMPLE=1" && \
	export REDIS_LIBS="../deps/redis3m/libredis3m.a -lhiredis -lboost_regex" && \
	export REDIS_OBJ="datadict_redis_ha.o datadict_redis_simple.o" && \
	export HDFS_FLAGS=-DFILESYSTEM_HDFS=1 && \
	export HDFS_LIBS=-lhdfs && \
	export HDFS_OBJ=filesystem_hdfs.o && \
	$(MAKE) libalenka.so

.PHONY: alenka