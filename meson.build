project(
  'sabbah', 'cpp',
  version : '0.1',
  default_options : [
    'warning_level=3',
    'cpp_std=c++23'
  ]
)

inc_dir = include_directories('include')

exe = executable(
  'sabbah',
  'src/main.cpp',
  'src/token.cpp',
  'src/error.cpp',
  include_directories: inc_dir,
  install : true
)

test('basic', exe)
