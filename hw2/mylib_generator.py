import os
import sys
import re

output = '''#include <stdarg.h>
#include <string.h>
#include <dlfcn.h>
#include <stdio.h>
#include <sys/types.h>
'''
command = "\
for var in `ltrace curl google.com 2>&1 | sort -V | sed 's/^\\([a-zA-Z0-9_]\\+\\)(.*/\\1/;tx;d;:x' | sed 's/\\(.*\\)64/\\1/' | uniq`;\
do \
    man $var |\
    sed \"s/^ \\+\\([a-zA-Z_]\\+[ *]\\+$var(.*);\\).*/\\1/;tx;d;:x\";man $var |\
    sed \"s/^ \\+\\(#include <.*>\\).*/aaaaa\\1/;tx;d;:x\"; \
done |\
sort |\
uniq |\
sed 's/\\(^aaaaa\\(#include.*\\)\\)\\|\
\\(.*\\)/\\2\\3/'\
"

all_data = os.popen(command).read();
for m in re.finditer('^#include.*$', all_data, re.MULTILINE):
    output += m.group(0) + '\n'

output += '''
void foo(int count, ...){
    int i;
    va_list vl;

    va_start(vl, count);
    for (i=0; i< count; i++){
        char *str = va_arg(vl, char*);
        int is_ptr = va_arg(vl, int);
        int is_str = va_arg(vl, int);
        void *raw_arg_value = va_arg(vl, void*);
        if (is_ptr)
            printf("%s = \\"%p\\"\\n", str,        raw_arg_value);
        else if (is_str)
            printf("%s = \\"%s\\"\\n", str, (char*)raw_arg_value);
        else
            printf("%s = %d\\n"      , str,   (int)raw_arg_value);
        fflush(stdout);
    }
    va_end(vl);
}
'''
def in_black_list(prototype):
    if 'return' in prototype\
    or 'sighandler_t' in prototype\
    or 'pathconf' in prototype\
    or 'printf' in prototype\
    or 'puts' in prototype\
    or 'fflush' in prototype\
    or 'malloc' in prototype\
    or 'calloc' in prototype\
    :
        return True
    return False

for m in re.finditer('^(.*);$', all_data, re.MULTILINE):
    prototype = m.group(1)
    if in_black_list(prototype):
        continue
    function_name = re.search('.* \*?([a-zA-Z_]+)\(.*', prototype).group(1)
    old_function_name = '__'+function_name
    foo_args = []
    delegate_args = []
    for m in re.finditer('(char \*)?(\*)?(\w+)(,|\))', prototype):
        arg = m.group(3)
        is_str = (m.group(1) != None)
        is_ptr = (m.group(2) != None)
        foo_args.append('"%s", %d, %d, %s' % (arg, 1 if is_ptr else 0, 1 if is_str else 0, arg))
        delegate_args.append(arg)

    if len(foo_args) != 0:
        call = 'foo(%d, %s);'%(len(foo_args), ', '.join(foo_args))
    else:
        call = 'foo(0);'

    output += prototype + '{\n' + \
'''\
    static %s;
    puts("----%s called----");
    fflush(stdout);
    if(%s == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            %s = dlsym(handle, "%s");
    }
    '''%(prototype.replace(function_name, '(*%s)'%old_function_name), function_name, old_function_name, old_function_name, function_name) +\
    call + '\n' + \
    '''
    if(%s != NULL)
        return %s
''' % (old_function_name, '%s(%s);'%(old_function_name, ', '.join(delegate_args))) +\
    '}\n'
print output
