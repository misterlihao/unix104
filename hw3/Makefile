CPPFLAGS += -g -std=c++11 -I.
plugins := $(shell ls plugin)
# XXX: maybe using make --directory will be better
plugin_src := $(plugins:%=plugin/%/impl.cpp)
plugin_hdr := $(plugins:%=plugin/%/header.h)
plugin_evnt := $(plugins:%=plugin/%/evnt.inc)
plugin_clbk := $(plugins:%=plugin/%/clbk.inc)
plugin_obj := $(plugins:%=plugin/%/impl.o)

generated_files := plugin_headers.h events.h register_event.inc register_callback.inc

.PHONY: all
all: a.out
a.out: main.o $(plugin_obj)
	$(CXX)  $(CPPFLAGS) -o $@ $^

main.o: $(generated_files)

##### generate plugin related files #####
plugin_headers.h: $(plugin_hdr)
	@rm -f $@
	@$(foreach hdr, $(plugin_hdr), echo '#include "$(hdr)"' >> $@;)
	@echo GENERATE $@

events.h: $(plugin_evnt)
	@sed -rn "s:.*:int const \0 = :p;=" $^ | sed -r "N;s/\n([0-9]+)/\1;/" > $@
	@echo GENERATE $@

register_event.inc: $(plugin_evnt)
	@sed -rn "s:^(.*)$$:register_event_or_crash\(\1\);:p" $^ > $@
	@echo GENERATE $@

register_callback.inc: $(plugin_clbk)
	@sed -rn "s:^(.*)$$:register_callback\(\1\);:p" $^ > $@
	@echo GENERATE $@


clean:
	rm -f $(generated_files)
	rm -f *.o
	rm -f a.out
