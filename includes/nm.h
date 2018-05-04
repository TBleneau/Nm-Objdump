/*
** EPITECH PROJECT, 2018
** nm.h
** File description:
** Created by Thomas BLENEAU
*/

#ifndef NM_H_
	#define NM_H_

	#include <elf.h>

	enum error_e {
		E_FD,
		E_FILE,
		E_DIR,
		E_FORMAT,
		E_MMAP,
		NO_SYM,
		E_ACCESS
	};

	typedef struct elf_info_s {
		union {
			Elf64_Ehdr *elfH_64;
			Elf32_Ehdr *elfH_32;
		};
	} elf_info_t;

	typedef struct elf_shdr_s {
		Elf64_Shdr *elfS_64;
		Elf32_Shdr *elfS_32;
	} elf_shdr_t;

	typedef struct elf_sym_s {
		char *_name;
		unsigned char symbol;
		Elf64_Addr value;
		struct elf_sym_s *next;
		struct elf_sym_s *prev;
	} elf_sym_t;

	int elf64_display(char const *const, char const *const, elf_sym_t **,
				int const);
	int elf32_display(char const *const, char const *const, elf_sym_t **,
				int const);
	int error_display(char const *const, char const *const,
				enum error_e);
	int error_file(char const *const, char const *const);
	int elf_exec(int const, char const *const, char const *const);
	elf_sym_t *elf64_sections(Elf64_Ehdr *, Elf64_Shdr *);
	elf_sym_t *elf64_symbols(Elf64_Sym *, size_t,
					char *, Elf64_Shdr *);
	elf_sym_t *elf32_sections(Elf32_Ehdr *, Elf32_Shdr *);
	elf_sym_t *elf32_symbols(Elf32_Sym *, size_t,
					char *, Elf32_Shdr *);
	int list_free_symbols(elf_sym_t **);
	char **tab_dup(int const, char **);
	void tab_free(char **);
	unsigned char elf64_types(Elf64_Sym, Elf64_Shdr *);
	unsigned char elf32_types(Elf32_Sym, Elf32_Shdr *);

#endif /* !NM_H_ */
