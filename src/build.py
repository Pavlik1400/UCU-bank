import os

os.chdir("src")
from py_pkg import CONFIG_PRESETS, BUILD_PRESETS, CMAKE_BUILD_CMD_T, CMAKE_CONFIGURE_CMD_T, cmd_t_split, join_path
from typing import Optional
from argparse import ArgumentParser
from subprocess import run
from string import Template
from shutil import rmtree, move
from os.path import exists


COMPILE_COMMANDS = "compile_commands.json"  


def get_prs_by_name(prss: list, name: str) -> dict:
    return [prs for prs in prss if prs["name"] == name][0]


def get_field(prs: dict, *field: str) -> Optional[str]:
    cur = prs
    for f in field:
        if not (isinstance(cur, dict) and f in cur):
            return None
        cur = cur[f]
    return cur


def prs_filter(prss: dict, beg: dict, *field: str) -> dict:
    cur = beg
    while (get_field(cur, *field) is None):
        cur = prss[cur["inherits"]]
    return get_field(cur, *field)


def main():
    parser = ArgumentParser()
    parser.add_argument("build_name", type=str, help="name of build - available are: dev-posix, dev-win")
    parser.add_argument("--clean", "-c", action="store_true")
    args = parser.parse_args()

    conf_name = BUILD_PRESETS[args.build_name]["configurePreset"]
    conf = CONFIG_PRESETS[conf_name]

    binary_dir = Template(prs_filter(CONFIG_PRESETS, conf, "binaryDir")).substitute(sourceDir=".",
                                                                                    presetName=conf_name)
    if args.clean:
        output_dir = Template(
            prs_filter(CONFIG_PRESETS, conf, "cacheVariables", "CMAKE_RUNTIME_OUTPUT_DIRECTORY")).substitute(
            sourceDir=".")
        rmtree(output_dir, ignore_errors=True)
        rmtree(binary_dir, ignore_errors=True)

    run(cmd_t_split(CMAKE_CONFIGURE_CMD_T, prs=conf_name))
    run(cmd_t_split(CMAKE_BUILD_CMD_T, prs=args.build_name))

    os.chdir("..")
    compile_commands = join_path(binary_dir, COMPILE_COMMANDS)
    if exists(compile_commands):
        if exists(COMPILE_COMMANDS):
            os.remove(COMPILE_COMMANDS)
        move(compile_commands, ".", )

if __name__ == "__main__":
    main()
