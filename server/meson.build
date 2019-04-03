set_variable('exe_dir', include_directories('.'))

src = ['src/main.cpp']

extra_args = []

##! GCC
if meson.get_compiler('cpp').get_id() == 'gcc' and get_option('buildtype') == 'release'
    extra_args = ['-O2', '-DRELEASE', '-march=native', '-Wall', '-Wextra', '-Wfatal-errors']
endif

if meson.get_compiler('cpp').get_id() == 'gcc' and get_option('buildtype') == 'debug'
    extra_args = ['-O0', '-DDEBUG', '-Wall', '-Wextra', '-Wfatal-errors']
endif

exe_main = executable('nephtys_server',
    sources      : src,
    install_dir  : 'nephtys',
    install      : true,
    cpp_args     : extra_args
)