#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import json
import os
import shutil
import sys
import traceback

from optparse import OptionParser

Parser = OptionParser(
    usage="%prog [options] name\ntype \"%prog -h\" for help",
    version="%prog 1.0"
)

Parser.add_option('-t', '--template', dest='template', type='string', default=None, help='Template folder.')
Parser.add_option('-d', '--dest',     dest='dest',     type='string', default=None, help='Destination folder.')

Options, Args = Parser.parse_args()

Out = dict()

def errorExit(i_msg):
    Out['error'] = i_msg
    Out['status'] = 'error'
    print(json.dumps({'copy': Out}, indent=4))
    sys.exit(1)

if Options.template is None:
    errorExit('Copy template is not specified.')

if Options.dest is None:
    errorExit('Copy destination is not specified.')

if not os.path.isdir(Options.template):
    errorExit('Input folder does not exit.')

if not os.path.isdir(Options.dest):
    errorExit('Destination folder does not exit.')

if len(Args) < 1:
    errorExit('New instance name(s) not specified.')

Out['copies'] = []
for name in Args:
    copy = dict()

    dest = os.path.join(Options.dest, name)
    copy['dest'] = dest
    if os.path.isdir(dest):
        copy['exist'] = True
    else:
        try:
            shutil.copytree(Options.template, dest)
        except PermissionError:
            copy['error'] = 'Permission denied: %s' % dest
        except:
            copy['error'] = '%s' % traceback.format_exc()

    Out['copies'].append(copy)

print(json.dumps({'copy': Out}, indent=4))

