#!/usr/bin/env python3
import datetime
import sys
import re
import os


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
    '37': "fssWHITE",  # white
}

start_field = ""


def main():
    symbols = {}
    symbol_count = 0

    escaped = False
    word_end = False
    escape = ''
    x = 1
    y = 0
    s_x = 0
    s_y = 0
    string = ''
    variable = False
    variable_name = ''

    dirname, fname = os.path.split(sys.argv[1])
    fname_no_ext = os.path.splitext(fname)[0]

    h_fname = "{}.h".format(fname_no_ext)
    c_full_fname = "{}.c".format(os.path.join(dirname, fname_no_ext))
    h_full_fname = "{}.h".format(os.path.join(dirname, fname_no_ext))

    with open(sys.argv[1], "r", encoding='latin-1') as f:
        with open(c_full_fname, 'w') as c_file:

            content = f.read()

            # Remove ANSI SAUCE record
            if 'SAUCE' in content[-129:]:
                content = content[:-129]

            current_color = '37'
            background_color = '0'

            c_file.write("""/* DO NOT EDIT {c_full_fname} - generated on: {date} */
#include "fss.h"
#include "{h_fname}"

void show() {{
""".format(date=datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                c_full_fname=c_full_fname, h_fname=h_fname))

            for byte in content:
                if escaped:
                    if byte != "m" and byte != "[":
                        escape = escape + byte
                    elif byte == "m":
                        escaped = False
                        for ansi_escape in escape.split(';'):
                            if ansi_escape not in ['0', '1'] and int(ansi_escape) < 40:
                                current_color = ansi_escape
                            elif int(ansi_escape) >= 40:
                                background_color = str(int(ansi_escape) - 10)
                                variable = True
                            elif ansi_escape == '1':
                                current_color = '37'
                            elif ansi_escape == '0':
                                current_color = '37'
                                variable = False
                                variable_name = ''
                        escape = ''
                        continue
                else:
                    if ord(byte) == ord('\x1b'):
                        if word_end:
                            word_end = False
                            if variable:
                                print("Initial = \'{}\'".format(string))
                                symbol_count = symbol_count + 1
                                variable_name = "f{count:05d}".format(
                                    count=symbol_count)
                                symbols[variable_name] = string
                            writeline(c_file, variable_name, string,
                                      current_color, background_color, s_x, s_y)
                            background_color = '0'
                            string = ''
                        escaped = True
                        continue
                    elif byte == "\n":
                        x = x + 1
                        y = 0
                        word_end = False
                        if string != "":
                            writeline(c_file, variable_name, string,
                                      current_color, background_color, s_x, s_y)
                        string = ''
                        continue
                    elif byte == "\r":
                        continue
                    elif byte != " " and not word_end:
                        s_x = x
                        s_y = y
                        word_end = True
                        string = string + byte
                    elif byte != " " and word_end:
                        string = string + byte
                    elif variable and word_end:
                        string = string + byte
                    elif word_end and byte == " " and not variable:
                        word_end = False
                        writeline(c_file, variable_name, string,
                                  current_color, background_color, s_x, s_y)
                        background_color = '0'
                        string = ''
                        variable_name = ''
                    y += 1

            if start_field != "":
                c_file.write('fssSetCursor("{s}")\n'.format(s=start_field))

            c_file.write('}\n')

        with open(h_full_fname, 'w') as h_file:
            h_file.write("""#ifndef __{fname}_H__
#define __{fname}_H__\n\n""".format(fname=fname_no_ext.upper()))
            for k, v in symbols.items():
                h_file.write('#define {k} "{k}" /* {v} */\n'.format(k=k, v=v))
            h_file.write("\n#endif")


def writeline(output, variable_name, process_string, current_color, bg_color, s_x=0, s_y=0):
    background = ANSI_DICT[bg_color]

    if variable_name != "":
        line = "  fssFld({row:>3}, {column:>3}, {color:10} ".format(
               row=s_x,
               column=s_y,
               len=len(process_string),
               color=ANSI_DICT[current_color])
    else:
        line = '  fssTxt({row:>3}, {column:>3}, {color:10} '.format(
               row=s_x,
               column=s_y,
               color=ANSI_DICT[current_color])

    if background in ['fssRED', 'fssGREEN', 'fssPINK']:
        line += '| fssUSCORE '

    if background == 'fssRED':
        # Mark and insert field and insert the cursor
        line += ','
        start_field = variable_name
    elif background in ['fssGREEN', 'fssPINK']:
        # Mark and insert field
        line += ','
    else:
        line += '| fssPROT   ,'

    if background not in ['fssPINK', 'fssTURQ']:
        process_string = process_string.replace("'", "\"")
        process_string = process_string.replace("_", " ")
        if variable_name != "":
            initial = ' {v}, "{s}", {len});\n'.format(
                s=process_string,
                v=variable_name,
                len=len(process_string))
        else:
            initial = ' "{s}");\n'.format(
                s=process_string)
        line += initial
    else:
        line = line[:-2].rstrip()[:-1]

    # if background in ['fssRED', 'fssGREEN', 'fssPINK']:
    #    line += '  // ({row},{column}),LEN = 1\n'.format(
    #        row = s_x,
    #        column = (s_y + len(process_string) + 1))

    output.write(line)


if __name__ == "__main__":
    main()
