from pipes import Template
from platform import system
from shlex import split
from os.path import join as join_path

OS_NAME = system().lower()
IS_NOT_WINDOWS = OS_NAME != "windows"

SCRIPT_EXT = "sh" if IS_NOT_WINDOWS else "bat"

def cmd_split(cmd: str):
    return split(cmd, posix=IS_NOT_WINDOWS)

def cmd_t_split(cmd_t: Template, **kwargs):
    return cmd_split(cmd_t.substitute(**kwargs))
