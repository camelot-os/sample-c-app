# SPDX-License-Identifier: Apache-2.0
#
# Copyright 2025 Ledger SAS

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

kconfig_file = meson.current_source_dir() / 'Kconfig'
kconfig_proj = subproject('kconfig', default_options: ['kconfig=@0@'.format(kconfig_file)])
kconfig_h = kconfig_proj.get_variable('kconfig_h')
kconfig_data = kconfig_proj.get_variable('kconfig_data')

package_metadata_proj = subproject('package-metadata')
package_metadata_dep = package_metadata_proj.get_variable('package_metadata_dep')
external_deps = [ package_metadata_dep ]

libshield_dep = dependency('shield')
external_deps += [ libshield_dep ]

sample_app_src = files()
subdir('src')

sample_app_elf = executable(
    meson.project_name(),
    name_suffix: 'elf',
    sources: sample_app_src,
    dependencies: [ external_deps ],
    link_language: 'c',
    install: true,
)
