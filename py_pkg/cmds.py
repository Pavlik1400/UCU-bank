from .port import cmd_split, join_path, SCRIPT_EXT
from string import Template

FETCH_SUBMODULES_CMD = cmd_split("git submodule update --init")
INIT_VCPKG_CMD = cmd_split(f"{join_path('vcpkg', 'bootstrap-vcpkg')}.{SCRIPT_EXT} -disableMetrics")
INSTALL_PKG_CMD_T = Template(f"{join_path('vcpkg', 'vcpkg')} --triplet {'${trp}'} install {'${pkg}'}")
CMAKE_CONFIGURE_CMD_T = Template("cmake --preset ${prs}")
CMAKE_BUILD_CMD_T = Template("cmake --build --preset ${prs}")