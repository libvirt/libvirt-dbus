project(
    'libvirt-dbus', 'c',
    version: '1.4.0',
    license: 'LGPLv2+',
    meson_version: '>= 0.49.0',
    default_options: [
        'buildtype=debugoptimized',
        'c_std=gnu99',
    ],
)

prefix = get_option('prefix')
datadir = prefix / get_option('datadir')
sbindir = prefix / get_option('sbindir')

opt_dirs = [
    'dbus_interfaces',
    'dbus_services',
    'dbus_system_services',
    'dbus_system_policies',
    'polkit_rules',
]

foreach opt_dir : opt_dirs
    value = get_option(opt_dir)
    varname = '@0@_dir'.format(opt_dir)
    set_variable(varname, datadir / value)
endforeach

conf = configuration_data()
conf.set('MESON_VERSION', '0.49.0')
conf.set('PACKAGE', meson.project_name())
conf.set('VERSION', meson.project_version())
conf.set('build_root', meson.build_root())
conf.set('sbindir', sbindir)
conf.set('source_root', meson.source_root())


# Dependencies

glib2_version = '2.44.0'
libvirt_version = '3.0.0'
libvirt_glib_version = '0.0.7'

dep_gio_unix = dependency('gio-unix-2.0', version: '>=' + glib2_version)
dep_glib = dependency('glib-2.0', version: '>=' + glib2_version)
dep_libvirt = dependency('libvirt', version: '>=' + libvirt_version)
dep_libvirt_glib = dependency('libvirt-glib-1.0', version: '>=' + libvirt_glib_version)

conf.set('GLIB2_REQUIRED', glib2_version)
conf.set('LIBVIRT_REQUIRED', libvirt_version)
conf.set('LIBVIRT_GLIB_REQUIRED', libvirt_glib_version)

git = run_command('test', '-d', '.git').returncode() == 0


# Configure options

conf.set('SYSTEM_USER', get_option('system_user'))


# Compile flags

common_flags = [
    '-DVIRT_DBUS_INTERFACES_DIR="@0@"'.format(dbus_interfaces_dir),
]

cc_flags = [
    '-W',
    '-Waddress',
    '-Waggressive-loop-optimizations',
    '-Wall',
    '-Warray-bounds=2',
    '-Wattributes',
    '-Wbad-function-cast',
    '-Wbool-compare',
    '-Wbuiltin-macro-redefined',
    '-Wcast-align',
    '-Wchar-subscripts',
    '-Wclobbered',
    '-Wcomment',
    '-Wcomments',
    '-Wcoverage-mismatch',
    '-Wcpp',
    '-Wdate-time',
    '-Wdeprecated-declarations',
    '-Wdesignated-init',
    '-Wdiscarded-array-qualifiers',
    '-Wdiscarded-qualifiers',
    '-Wdiv-by-zero',
    '-Wdouble-promotion',
    '-Wduplicated-cond',
    '-Wempty-body',
    '-Wendif-labels',
    '-Wextra',
    '-Wformat',
    '-Wformat-contains-nul',
    '-Wformat-extra-args',
    '-Wformat-nonliteral',
    '-Wformat-security',
    '-Wformat-y2k',
    '-Wformat-zero-length',
    '-Wframe-address',
    '-Wframe-larger-than=1024',
    '-Wfree-nonheap-object',
    '-Whsa',
    '-Wignored-attributes',
    '-Wignored-qualifiers',
    '-Wimplicit',
    '-Wimplicit-function-declaration',
    '-Wimplicit-int',
    '-Wincompatible-pointer-types',
    '-Winit-self',
    '-Winline',
    '-Wint-conversion',
    '-Wint-to-pointer-cast',
    '-Winvalid-memory-model',
    '-Winvalid-pch',
    '-Wjump-misses-init',
    '-Wlogical-not-parentheses',
    '-Wlogical-op',
    '-Wmain',
    '-Wmaybe-uninitialized',
    '-Wmemset-transposed-args',
    '-Wmisleading-indentation',
    '-Wmissing-braces',
    '-Wmissing-declarations',
    '-Wmissing-field-initializers',
    '-Wmissing-include-dirs',
    '-Wmissing-parameter-type',
    '-Wmissing-prototypes',
    '-Wmultichar',
    '-Wnarrowing',
    '-Wnested-externs',
    '-Wno-cast-function-type',
    '-Wnonnull',
    '-Wnonnull-compare',
    '-Wnormalized=nfc',
    '-Wnull-dereference',
    '-Wodr',
    '-Wold-style-declaration',
    '-Wold-style-definition',
    '-Wopenmp-simd',
    '-Woverflow',
    '-Woverlength-strings',
    '-Woverride-init',
    '-Wpacked',
    '-Wpacked-bitfield-compat',
    '-Wparentheses',
    '-Wpointer-arith',
    '-Wpointer-sign',
    '-Wpointer-to-int-cast',
    '-Wpragmas',
    '-Wreturn-local-addr',
    '-Wreturn-type',
    '-Wscalar-storage-order',
    '-Wsequence-point',
    '-Wshadow',
    '-Wshift-count-negative',
    '-Wshift-count-overflow',
    '-Wshift-negative-value',
    '-Wshift-overflow=2',
    '-Wsizeof-array-argument',
    '-Wsizeof-pointer-memaccess',
    '-Wstack-protector',
    '-Wstrict-aliasing',
    '-Wstrict-prototypes',
    '-Wsuggest-attribute=const',
    '-Wsuggest-attribute=format',
    '-Wsuggest-attribute=noreturn',
    '-Wsuggest-attribute=pure',
    '-Wsuggest-final-methods',
    '-Wsuggest-final-types',
    '-Wswitch',
    '-Wswitch-bool',
    '-Wsync-nand',
    '-Wtautological-compare',
    '-Wtrampolines',
    '-Wtrigraphs',
    '-Wtype-limits',
    '-Wuninitialized',
    '-Wunknown-pragmas',
    '-Wunused',
    '-Wunused-but-set-parameter',
    '-Wunused-but-set-variable',
    '-Wunused-const-variable=2',
    '-Wunused-function',
    '-Wunused-label',
    '-Wunused-local-typedefs',
    '-Wunused-macros',
    '-Wunused-parameter',
    '-Wunused-result',
    '-Wunused-value',
    '-Wunused-variable',
    '-Wvarargs',
    '-Wvariadic-macros',
    '-Wvector-operation-performance',
    '-Wvla',
    '-Wvolatile-register-var',
    '-Wwrite-strings',
    '-fasynchronous-unwind-tables',
    '-fexceptions',
    '-fipa-pure-const',
    '-fno-common',
]
ld_flags = [
    '-Wl,-z,now',
    '-Wl,-z,relro',
]

if git
    cc_flags += ['-Werror']
endif

if host_machine.cpu_family() != 'aarch64'
    if host_machine.system() == 'linux'
        cc_flags += ['-fstack-protector-strong']
    endif
    if host_machine.system() == 'freebsd'
        cc_flags += ['-fstack-protector']
    endif
endif

if host_machine.system() not in ['cygwin', 'windows']
    cc_flags += ['-fPIE', '-DPIE']
    ld_flags += ['-pie']
endif

cc = meson.get_compiler('c')
common_flags += cc.get_supported_arguments(cc_flags)
link_flags = cc.get_supported_link_arguments(ld_flags)

add_project_arguments(common_flags, language: 'c')
add_project_link_arguments(link_flags, language: 'c')


# Generate run helper

configure_file(
    input: 'run.in',
    output: 'run',
    configuration: conf,
)
run_command('tools/fix-perm.sh', 'a+x', 'run')


# Generate dist files

if git
    configure_file(
        input: 'libvirt-dbus.spec.in',
        output: 'libvirt-dbus.spec',
        configuration: conf,
    )

    authors = run_command('tools/gen-authors.sh')
    configure_file(
        configuration: { 'contributorslist': authors.stdout() },
        input: 'AUTHORS.rst.in',
        output: 'AUTHORS.rst',
    )

    foreach file : [ 'libvirt-dbus.spec', 'AUTHORS.rst' ]
        meson.add_dist_script('tools/dist.sh', meson.build_root(), file)
    endforeach
endif


# Include sub-directories

subdir('data')
subdir('docs')
subdir('src')
subdir('tests')
