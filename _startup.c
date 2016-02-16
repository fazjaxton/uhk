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
