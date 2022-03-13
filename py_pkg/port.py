from platform import system
from shlex import split
from os.path import sep as p_sep

IS_NOT_WINDOWS = system() != "Windows"

SCRIPT_EXT = "sh" if IS_NOT_WINDOWS else "bat"
cmd_split = lambda cmd: split(cmd, posix=IS_NOT_WINDOWS)
cmd_t_split = lambda cmd_t, **kwargs: cmd_split(cmd_t.substitute(**kwargs))
