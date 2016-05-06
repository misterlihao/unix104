inc_files := init.inc wait_for_command.inc process_command.inc
plugin_src := $(shell ls plugin)
plugin_obj := $(plugin_src:%.c=%.o)
plugin_name := $(plugin_src:%.c=%)

.PHONY: all
all: $(inc_files)

$(inc_files): plugin/$(plugin_src)
	sed -rn "/$(^:plugin/%.cpp=%)_$(@:%.inc=%).*;/ p" $^ > $@

clean:
	rm -rf $(inc_files)
	rm -rf $(plugin_obj)
