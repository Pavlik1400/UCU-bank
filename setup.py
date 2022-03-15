from py_pkg import FETCH_SUBMODULES_CMD, INIT_VCPKG_CMD, DEPENDENCIES, INSTALL_PKG_CMD_T, TRIPLET, cmd_t_split, init_kafka
from subprocess import run


def main():
    run(FETCH_SUBMODULES_CMD)
    run(INIT_VCPKG_CMD)
    [run(cmd_t_split(INSTALL_PKG_CMD_T, pkg=pkg, trp=TRIPLET)) for pkg in DEPENDENCIES]

    init_kafka()


if __name__ == "__main__":
    main()
