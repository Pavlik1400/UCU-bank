from .port import cmd_split, p_sep, SCRIPT_EXT
from string import Template

FETCH_SUBMODULES_CMD = cmd_split("git submodule update --init")
VCPKG_ROOT = f".{p_sep}vcpkg{p_sep}"
INIT_VCPKG_CMD = cmd_split(f"{VCPKG_ROOT}bootstrap-vcpkg.{SCRIPT_EXT} -disableMetrics")
INSTALL_PKG_CMD_T = Template(f"{VCPKG_ROOT}vcpkg install {'${pkg}'}")