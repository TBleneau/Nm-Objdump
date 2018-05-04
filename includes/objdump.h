/*
** EPITECH PROJECT, 2018
** objdump.h
** File description:
** Created by Thomas BLENEAU
*/

#ifndef OBJDUMP_H_
	#define OBJDUMP_H_

	#include <elf.h>

	enum error_e {
		E_USAGE,
		E_OPTIONS,
		E_FD,
		E_FILE,
		E_DIR,
		E_FORMAT,
		E_MMAP,
		E_CALLOC,
		NO_SYM,
		E_ACCESS
	};

	static const size_t SECT_CONTENT = 16;
	static const size_t FORMAT_CONTENT = 4;

	typedef struct elf_Ehdr_s {
		union {
			Elf64_Ehdr *elfH_64;
			Elf32_Ehdr *elfH_32;
		};
		Elf64_Shdr *elfS_64;
		Elf32_Shdr *elfS_32;
	} elf_Ehdr_t;

	typedef struct obj_opt_s {
		char *name;
		struct obj_opt_s *next;
		struct obj_opt_s *prev;
	} obj_opt_t;

	typedef struct flags_s {
		char *name;
		ssize_t value;
		struct flags_s *next;
		struct flags_s *prev;
	} flags_t;

	int error_display(char const *const, char const *const,
				enum error_e);
	int error_file(char const *const, char const *const);
	int parse_options(int const, char **);
	int elf_exec(char const *const, char const *const);
	char **tab_dup(int const, char **);
	char **single_dup(int const, char *);
	void tab_free(char **);
	int elf64_header(elf_Ehdr_t const *const, char const *const);
	int elf64_header_flags(flags_t **, elf_Ehdr_t const *const);
	int elf64_flags_free(flags_t **);
	int elf64_sections(elf_Ehdr_t const *const);
	int elf64_content_value(size_t *, size_t const,
				unsigned char const *const);
	unsigned char *elf64_content_init(elf_Ehdr_t const *const,
						size_t const, size_t const);
	int elf64_content_update(unsigned char *, unsigned char const *const,
				size_t const, size_t const);
	int elf32_header(elf_Ehdr_t const *const, char const *const);
	int elf32_header_flags(flags_t **, elf_Ehdr_t const *const);
	int elf32_flags_free(flags_t **);
	int elf32_sections(elf_Ehdr_t const *const);
	int elf32_content_value(size_t *, size_t const,
				unsigned char const *const);
	unsigned char *elf32_content_init(elf_Ehdr_t const *const,
						size_t const, size_t const);
	int elf32_content_update(unsigned char *, unsigned char const *const,
				size_t const, size_t const);

#endif /* !OBJDUMP_H_ */
