# SPDX-License-Identifier: Apache-2.0
#
# Copyright 2025 Ledger SAS
# Copyright 2026 H2Lab Development Team

project('sample-c-app', 'c',
    meson_version: '>=1.4.0',
    version: '0.0.1',
    default_options: [
        'c_std=gnu11',
        'warning_level=3', 'optimization=s',
        'default_library=static', 'b_pie=false', 'b_staticpic=false',
        'dts=dts/default.dts',
        'dts-include-dirs=dts',
        'config=configs/defconfig',
    ],
)

libshield_dep = dependency('shield')
external_deps = [ libshield_dep ]

# Need clean handling at SDK generation, target specific compile args must be in
# cross-file (and other buildsystem cross toolchain like# file) and thus
# generated accordingly.
#
# As a workaround, retrieve Cflags from shield.pc manually w/ run_command
# ans set those flags as global c compile arguments.
#
# note: pkgconfig get variable from meson dep can only retrieve variable using
# pkg-config `--variable` option, i.e. almost everything except `Cflags` and
# `Libs`
target_cflags = run_command(
    'pkg-config', '--cflags', 'shield',
    capture: true,
    check: true,
    env: [ 'PKG_CONFIG_PATH=@0@'.format(get_option('pkg_config_path')[0]) ],
).stdout().strip().split()

add_global_arguments(target_cflags, language: [ 'c' ])

kconfig_file = meson.current_source_dir() / 'Kconfig'
kconfig_proj = subproject('kconfig', default_options: ['kconfig=@0@'.format(kconfig_file)])
kconfig_h = kconfig_proj.get_variable('kconfig_h')
kconfig_data = kconfig_proj.get_variable('kconfig_data')

package_metadata_proj = subproject('package-metadata')
package_metadata_dep = package_metadata_proj.get_variable('package_metadata_dep')
external_deps += [ package_metadata_dep ]

libecc_proj = subproject('libecc')
libecc_dep = libecc_proj.get_variable('libsign_dep')
external_deps += [ libecc_dep ]

sample_app_src = files()
subdir('src')

sample_app_elf = executable(
    meson.project_name(),
    name_suffix: 'elf',
    sources: sample_app_src,
    dependencies: [ external_deps ],
    link_language: 'c',
    install: true,
    c_args: '-DWITH_STDLIB',
)
