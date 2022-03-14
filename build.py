from py_pkg import CONFIG_PRESETS, BUILD_PRESETS, CMAKE_BUILD_CMD_T, CMAKE_CONFIGURE_CMD_T, cmd_t_split
from typing import Optional
from argparse import ArgumentParser
from subprocess import run
from string import Template
from shutil import rmtree


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
    parser.add_argument("build_name", type=str)
    parser.add_argument("--clean", "-c", action="store_true")
    args = parser.parse_args()

    conf_name = BUILD_PRESETS[args.build_name]["configurePreset"]
    conf = CONFIG_PRESETS[conf_name]

    if args.clean:
        binary_dir = Template(prs_filter(CONFIG_PRESETS, conf, "binaryDir")).substitute(sourceDir=".", presetName=conf_name)
        output_dir = Template(prs_filter(CONFIG_PRESETS, conf, "cacheVariables", "CMAKE_RUNTIME_OUTPUT_DIRECTORY")).substitute(sourceDir=".")
        rmtree(output_dir, ignore_errors=True)
        rmtree(binary_dir, ignore_errors=True)
    
    run(cmd_t_split(CMAKE_CONFIGURE_CMD_T, prs=conf_name))
    run(cmd_t_split(CMAKE_BUILD_CMD_T, prs=args.build_name))
    

if __name__ == "__main__":
    main()
