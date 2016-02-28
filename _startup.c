/**
 * Copyright 2016  Kevin Smith <thirdwiggin@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

int main(void);

void _cstartup(void)
{
    extern int __bss_start__[], __bss_end__[];
    extern int __data_start__[], __data_end__[];
    extern int __etext[];

    int *s, *d;

    /* Initialize data section */
    for (d = __data_start__, s = __etext;
         d < __data_end__;
         s++, d++) {
        *d = *s;
    }

    /* Zero BSS section */
    for (d = __bss_start__; d < __bss_end__; d++) {
        *d = 0;
    }

    main();

    while (1);
}
