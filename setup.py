from py_pkg import FETCH_SUBMODULES_CMD, INIT_VCPKG_CMD, cmd_t_split, init_kafka
from subprocess import run


def main():
    run(FETCH_SUBMODULES_CMD)
    run(INIT_VCPKG_CMD)
    init_kafka()


if __name__ == "__main__":
    main()
