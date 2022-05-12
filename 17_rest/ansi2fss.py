#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import datetime
import sys
import re
import os

start_field = ""


def main():

    with open(sys.argv[2], "r", encoding='latin-1') as f:

        dirname, fname = os.path.split(sys.argv[2])
        fname_no_ext = os.path.splitext(fname)[0]
        c_full_fname = "{}.c".format(os.path.join(dirname, fname_no_ext))
        with open(c_full_fname, 'w') as c_file:

            h_fname = "{}.h".format(fname_no_ext)
            function_name = sys.argv[1]

            row = 1
            column = 0
            start_row = 0
            start_column = 0

            token = ''
            is_token_end = False

            texts = []
            fields = []
            field_count = 0
            is_field = False
            field_name = ''

            escape = ''
            is_escaped = False

            # Escaped sequence
            # color(_)     => \x1B[1;_m
            # setYX(_,_)   => \x1B[_;_H
            # clear screen => \x1B[2J

            foreground_color = '37'  # white
            background_color = '0'  # black

            content = f.read()
            if 'SAUCE' in content[-129:]:
                content = content[:-129]  # Remove ANSI SAUCE record

            for character in content:
                if is_escaped:
                    if character != "m" and character != "[":
                        # not color
                        escape = escape + character
                    elif character == "m":
                        # color
                        is_escaped = False
                        for escape_color in escape.split(';'):
                            if escape_color not in ['0', '1'] and int(escape_color) < 40:
                                foreground_color = escape_color
                            elif int(escape_color) >= 40:
                                background_color = str(int(escape_color) - 10)
                                is_field = True
                            elif escape_color == '1':
                                foreground_color = '37'  # white
                            elif escape_color == '0':
                                foreground_color = '37'  # white
                                is_field = False
                                field_name = ''
                        escape = ''
                        continue
                else:
                    if ord(character) == ord('\x1b'):
                        # ANSI escape code = [ = 0x1B = 27
                        if is_token_end:
                            is_token_end = False
                            if is_field:
                                # new field
                                field_count = field_count + 1
                                field_name = "F{field_count:05d}".format(
                                    field_count=field_count,
                                    function_name=function_name.upper())
                                fields.append({
                                    'start_row': start_row,
                                    'start_column': start_column,
                                    'foreground_color': foreground_color,
                                    'background_color': background_color,
                                    'field_name': field_name,
                                    'token': len(token) * ' '})
                            else:
                                if token != "":
                                    texts.append({
                                        'start_row': start_row,
                                        'start_column': start_column,
                                        'foreground_color': foreground_color,
                                        'background_color': background_color,
                                        'token': token})
                            background_color = '0'  # black
                            token = ''
                        is_escaped = True
                        continue
                    elif character == "\n":
                        # new line
                        row = row + 1
                        column = 0
                        is_token_end = False
                        if token != "":
                            texts.append({
                                'start_row': start_row,
                                'start_column': start_column,
                                'foreground_color': foreground_color,
                                'background_color': background_color,
                                'token': token})
                        token = ''
                        continue
                    elif character == "\r":
                        # Drop
                        continue
                    elif not is_token_end and character != " ":
                        start_row = row
                        start_column = column
                        is_token_end = True
                        token = token + character
                    elif is_token_end and character != " ":
                        token = token + character
                    elif is_token_end and is_field:
                        token = token + character
                    elif is_token_end and character == " " and not is_field:
                        is_token_end = False

                        texts.append({
                            'start_row': start_row,
                            'start_column': start_column,
                            'foreground_color': foreground_color,
                            'background_color': background_color,
                            'token': token})
                        background_color = '0'
                        token = ''
                        field_name = ''
                    column += 1

            c_file.write("""/* DO NOT EDIT {c_full_fname}. Generated on {date} */
#include "../../08_fss/fss.h"
#include "../../08_fss/aux.h"
#include "{h_fname}"
""".format(date=datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                c_full_fname=c_full_fname,
                h_fname=h_fname))
            c_file.write("""
static FieldRow fields[] = {
""")
            for field in fields:
                writeline(c_file, field)

            c_file.write("""  { 0, 0, 0 , 0, 0, 0 }
};\n
static TextRow texts[] = {
""")
            for text in texts:
                writeline(c_file, text)

            c_file.write("""  { 0, 0, 0 , 0 }
};\n""")

            c_file.write("""
void {function_name}(void) {{
  int i;

  for (i = 0; i < {lt}; i++) {{
    TextRow t = texts[i];
    fssTxt(t.row, t.col, t.attr, t.msg);
  }}

  for (i = 0; i < {lf}; i++){{
    FieldRow f = fields[i];
    fssFld(f.row, f.col, f.attr, f.value, f.len, f.msg);
  }}
""".format(function_name=function_name,
                lf=len(fields),
                lt=len(texts)))
            if start_field != "":
                c_file.write('  fssSetCursor("{s}");\n'.format(s=start_field))
            c_file.write('}\n')

        h_full_fname = "{}.h".format(os.path.join(dirname, fname_no_ext))

        with open(h_full_fname, 'w') as h_file:
            h_file.write("""#ifndef __{fname}_H__
#define __{fname}_H__\n
extern void {function_name}(void);\n""".format(fname=fname_no_ext.upper(),
                                               function_name=function_name))
            for k in range(0, len(fields)):
                h_file.write('\n#define F{function_name}_{k:05} "F{k:05}" /* {v} */'.format(
                    k=k+1,
                    v=fields[k]['token'],
                    function_name=function_name.upper()))
            h_file.write("\n#endif\n")


ANSI_DICT = {
    '0': 'REMOVE ATTRIBUTES',
    '1': 'BOLD',
    '30': 'NEUTRAL',
    '31': "fssRED",
    '32': "fssGREEN",
    '33': "fssYELLOW",
    '34': "fssBLUE",
    '35': "fssPINK",  # magenta
    '36': "fssTURQ",  # cyan
    '37': "fssWHITE"  # white
}


def writeline(output, d):
    global start_field

    background_color = d['background_color']
    if 'field_name' in d:
        field_name = d['field_name']
    else:
        field_name = ''
    foreground_color = d['foreground_color']
    start_column = d['start_column']
    start_row = d['start_row']
    token = d['token']

    background = ANSI_DICT[background_color]

    if field_name != "":
        result = "  {{ {row}, {column}, {color} ".format(
            row=start_row,
            column=start_column,
            len=len(token),
            color=ANSI_DICT[foreground_color])
    else:
        result = '  {{ {row}, {column}, {color} '.format(
            row=start_row,
            column=start_column,
            color=ANSI_DICT[foreground_color])

    if background in ['fssRED', 'fssGREEN', 'fssPINK']:
        result += '| fssUSCORE '

    if background == 'fssRED':
        # Mark and insert field and insert the cursor
        start_field = field_name
        result += ','
    elif background in ['fssGREEN', 'fssPINK']:
        # Mark and insert field
        result += ','
    else:
        result += '| fssPROT ,'

    if background not in ['fssPINK', 'fssTURQ']:
        token = token.replace("'", "\"")
        token = token.replace("_", " ")
        if field_name != "":
            initial = ' "{field_name}", {length}, "{token}" }}, \n'.format(
                token=token,
                field_name=field_name,
                length=len(token))
        else:
            initial = ' "{token}" }}, \n'.format(
                token=token)
        result += initial
    else:
        result = result[:-2].rstrip()[:-1]

    output.write(result)


if __name__ == "__main__":
    if len(sys.argv) == 3:
        main()
    else:
        print("""+------------------------------------------------------------+
| ANSI to C Full Screen Interface FSS                        |
| Use https://github.com/blocktronics/moebius to draw screen |
| Usage: ./ansi2fss.py function_name /path/to/screen.ans     |
+------------------------------------------------------------+""")
