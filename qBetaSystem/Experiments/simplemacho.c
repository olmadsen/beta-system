// macho_arm64_min.c
// Generates a tiny ARM64 Mach-O object file: myobj.o

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>

int main(void) {
    FILE *f = fopen("myobj.o", "wb");
    if (!f) return 1;

    // --------------------
    // ARM64 machine code
    // ret
    // --------------------
    uint32_t text[] = { 0xD65F03C0 }; // ret

    // --------------------
    // String table
    // --------------------
    const char strtab[] = "\0_myfunc";
    uint32_t strtab_size = sizeof(strtab);

    // --------------------
    // Symbol table entry
    // --------------------
    struct nlist_64 sym = {
        .n_un.n_strx = 1,
        .n_type = N_SECT | N_EXT,
        .n_sect = 1,
        .n_desc = 0,
        .n_value = 0
    };

    // --------------------
    // Mach-O header
    // --------------------
    struct mach_header_64 mh = {
        .magic = MH_MAGIC_64,
        .cputype = CPU_TYPE_ARM64,
        .cpusubtype = CPU_SUBTYPE_ARM64_ALL,
        .filetype = MH_OBJECT,
        .ncmds = 2,
        .sizeofcmds =
            sizeof(struct segment_command_64) +
            sizeof(struct section_64) +
            sizeof(struct symtab_command),
        .flags = MH_SUBSECTIONS_VIA_SYMBOLS
    };

    // --------------------
    // Segment + section
    // --------------------
    struct segment_command_64 seg = {
        .cmd = LC_SEGMENT_64,
        .cmdsize = sizeof(seg) + sizeof(struct section_64),
        .vmaddr = 0,
        .vmsize = sizeof(text),
        .fileoff = 0,
        .filesize = sizeof(text),
        .maxprot = VM_PROT_READ | VM_PROT_EXECUTE,
        .initprot = VM_PROT_READ | VM_PROT_EXECUTE,
        .nsects = 1
