set_variable('exe_dir', include_directories('.'))

src = ['main.cpp']

extra_args = []

##! GCC
if meson.get_compiler('cpp').get_id() == 'gcc' and get_option('buildtype') == 'release'
    extra_args = ['-O2', '-DRELEASE', '-march=native', '-Wall', '-Wextra', '-Wfatal-errors']
endif

if meson.get_compiler('cpp').get_id() == 'gcc' and get_option('buildtype') == 'debug'
    extra_args = ['-O0', '-DDEBUG', '-Wall', '-Wextra', '-Wfatal-errors']
endif

##! Clang
if meson.get_compiler('cpp').get_id() == 'clang' and get_option('buildtype') == 'release'
    extra_args = ['-O2', '-DRELEASE', '-march=native', '-Wall', '-Wextra', '-Wfatal-errors']
endif

if meson.get_compiler('cpp').get_id() == 'clang' and get_option('buildtype') == 'debug'
    extra_args = ['-O0', '-DDEBUG', '-Wall', '-Wextra', '-Wfatal-errors']
endif

message(get_option('buildtype'))
message(extra_args)

exe_main = executable('nephtys_client',
    sources      : src,
    install_dir  : 'nephtys',
    install      : true,
    cpp_args     : extra_args
)