project('nephtys',
    'cpp',
    version : '0.0.1',
    license : 'MIT',
    default_options : ['warning_level=3', 'cpp_std=c++17']
)

subdir('client')
if host_machine.system() == 'linux'
    subdir('server')
endif
