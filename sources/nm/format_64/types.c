/*
** EPITECH PROJECT, 2018
** types.c
** File description:
** Created by Thomas BLENEAU
*/

#include <elf.h>
#include <sys/mman.h>
#include "nm.h"

static unsigned char elf64_type_sections(size_t flags)
{
	unsigned char type = 'N';

	type = (flags == (SHF_ALLOC | SHF_MERGE))
		? 'R' : 'N';
	if (type == 'N') {
		type = (flags == (SHF_ALLOC | SHF_WRITE)) ? 'D' : 'N';
		if (type == 'N')
			type = (flags == (SHF_ALLOC | SHF_EXECINSTR))
				? 'T' : 'N';
	}
	return (type);
}

static unsigned char elf64_type_flags(Elf64_Sym symbol, Elf64_Shdr *elf_S)
{
	unsigned char type = '?';
	size_t flags = elf_S[symbol.st_shndx].sh_flags;
	size_t sect_type = elf_S[symbol.st_shndx].sh_type;

	if (sect_type == SHT_NOBITS)
		type = (flags == (SHF_ALLOC | SHF_WRITE)) ? 'B' : '?';
	if (sect_type == SHT_PROGBITS)
		type = elf64_type_sections(flags);
	if (flags == SHF_ALLOC)
		type = 'R';
	if (type == '?' && (sect_type == SHT_INIT_ARRAY
				|| sect_type == SHT_FINI_ARRAY))
		type = 'T';
	if (type == '?' && sect_type == SHT_DYNAMIC)
		type = 'D';
	return (type);
}

static unsigned char elf64_type_index(Elf64_Sym symbol, Elf64_Shdr *elf_S)
{
	unsigned char type = '?';

	switch (symbol.st_shndx) {
	case SHN_UNDEF:
		type = 'U';
		break;
	case SHN_ABS:
		type = 'A';
		break;
	case SHN_COMMON:
		type = 'C';
		break;
	case SHT_DYNAMIC:
		type = 'D';
		break;
	default:
		type = elf64_type_flags(symbol, elf_S);
		break;
	}
	return (type);
}

static unsigned char elf64_type_weak(Elf64_Sym symbol)
{
	if (ELF64_ST_TYPE(symbol.st_info) == STT_OBJECT)
		return ((symbol.st_shndx == SHN_UNDEF) ? 'v' : 'V');
	return ((symbol.st_shndx == SHN_UNDEF) ? 'w' : 'W');
}

unsigned char elf64_types(Elf64_Sym symbol, Elf64_Shdr *elf_S)
{
	unsigned char type = '?';
	size_t elf_bind = ELF64_ST_BIND(symbol.st_info);

	switch (elf_bind) {
	case STB_GNU_UNIQUE:
		type = 'u';
		break;
	case STB_WEAK:
		type = elf64_type_weak(symbol);
		break;
	default:
		type = elf64_type_index(symbol, elf_S);
		break;
	}
	return ((elf_bind == STB_LOCAL && type != '?') ? type += 32 : type);
}
