src_include = include_directories('../src')

test_exec = executable(
    'test_util',
    [
        'test_util.c',
    ],
    dependencies: [
        dep_gio_unix,
        dep_glib,
        dep_libvirt,
        dep_libvirt_glib
    ],
    link_with: [
        lib_util,
    ],
    include_directories: src_include,
)

test('test_util', test_exec, suite: 'unit')

python_tests = [
    'test_connect.py',
    'test_domain.py',
    'test_snapshot.py',
    'test_interface.py',
    'test_network.py',
    'test_nodedev.py',
    'test_storage.py',
]

python_env = [
    'abs_top_builddir=' + meson.build_root(),
    'VIRT_DBUS_INTERFACES_DIR=' + meson.source_root() + '/data'
]

foreach name : python_tests
    prog = find_program(name)
    test(name, prog, env: python_env, suite: 'unit')
endforeach

flake8 = find_program('flake8', 'flake8-3', required: false)
if flake8.found()
    test(
        'flake8', flake8,
        args: [
            '--show-source',
            '--ignore=E501', # E501: (line too long) warning is ignored.
            meson.source_root(),
        ],
        suite: 'style',
    )
endif
