#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * closes_file - Closes a file.
 * @fil: ELF file.
 * Return: none.
 */
void closes_file(int b)
{
	if (close(b) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Cannot close fd %d\n", b);
		exit(98);
	}
}
/**
 * check_file - Checks if file is ELF.
 * @rem: Remaining file content.
 * Return: none.
 */
void check_file(unsigned char *rem)
{
	int k;

	for (k = 0; k < 4; k++)
		if (rem[k] != 127 && rem[k] != 'E' &&
		    rem[k] != 'L' && rem[k] != 'F')
			dprintf(STDERR_FILENO, "Error: Not ELF file\n"),
				exit(98);
}
/**
 * print_magic - Prints magic of ELF file.
 * @magic: ELF magic numbers.
 * Return: none.
 */
void print_magic(unsigned char *magic)
{
	int k;

	printf("ELF Header:\n");
	printf("  Magic:   ");
	for (k = 0; k < EI_NIDENT; k++)
	{
		printf("%02x", magic[k]);
		k == EI_NIDENT - 1 ? printf("\n") : printf(" ");
	}
}
/**
 * print_class - Printf ELF class.
 * @class: ELF file.
 * Return: none.
 */
void print_class(unsigned char *class)
{
	printf("  Class:                             ");
	switch (class[EI_CLASS])
	{
	case ELFCLASSNONE:
		printf("none\n");
		break;
	case ELFCLASS32:
		printf("ELF32\n");
		break;
	case ELFCLASS64:
		printf("ELF64\n");
		break;
	default:
		printf("<unknown: %x>\n", class[EI_CLASS]);
	}
}
/**
 * print_data - Print ELF data file.
 * @data: ELF file.
 * Return: none.
 */
void print_data(unsigned char *data)
{
	printf("  Data:                              ");

	switch (data[EI_DATA])
	{
	case ELFDATANONE:
		printf("none\n");
		break;
	case ELFDATA2LSB:
		printf("2's complement, little endian\n");
		break;
	case ELFDATA2MSB:
		printf("2's complement, big endian\n");
		break;
	default:
		printf("<unknown: %x>\n", data[EI_CLASS]);
	}
}
/**
 * print_version - Prints ELF version file.
 * @version: ELF file.
 * Return: none.
 */
void print_version(unsigned char *version)
{
	printf("  Version:                           %d",
	       version[EI_VERSION]);

	switch (version[EI_VERSION])
	{
	case EV_CURRENT:
		printf(" (current)\n");
		break;
	default:
		printf("\n");
		break;
	}
}
/**
 * print_os_abi - Prints ELF OS/ABI file.
 * @o_a: ELF file.
 * Return: none.
 */
void print_os_abi(unsigned char *o_a)
{
	printf("  OS/ABI:                            ");

	switch (o_a[EI_OSABI])
	{
	case ELFOSABI_NONE:
		printf("UNIX - System V\n");
		break;
	case ELFOSABI_HPUX:
		printf("UNIX - HP-UX\n");
		break;
	case ELFOSABI_NETBSD:
		printf("UNIX - NetBSD\n");
		break;
	case ELFOSABI_LINUX:
		printf("UNIX - Linux\n");
		break;
	case ELFOSABI_SOLARIS:
		printf("UNIX - Solaris\n");
		break;
	case ELFOSABI_IRIX:
		printf("UNIX - IRIX\n");
		break;
	case ELFOSABI_FREEBSD:
		printf("UNIX - FreeBSD\n");
		break;
	case ELFOSABI_TRU64:
		printf("UNIX - TRU64\n");
		break;
	case ELFOSABI_ARM:
		printf("ARM\n");
		break;
	case ELFOSABI_STANDALONE:
		printf("Standalone App\n");
		break;
	default:
		printf("<unknown: %x>\n", o_a[EI_OSABI]);
	}
}
/**
 * print_abi - Prinf ELF ABI version file.
 * @abi: ELF file.
 * Return: none.
 */
void print_abi(unsigned char *abi)
{
	printf("  ABI Version:   %d\n",
	       abi[EI_ABIVERSION]);
}
/**
 * print_type - Print ELF type file.
 * @type: ELF type.
 * @class: ELF Class
 * Return: none.
 */
void print_type(unsigned int type, unsigned char *class)
{
	if (class[EI_DATA] == ELFDATA2MSB)
		type >>= 8;

	printf("  Type:                              ");

	switch (type)
	{
	case ET_NONE:
		printf("NONE (None)\n");
		break;
	case ET_REL:
		printf("REL (Relocatable file)\n");
		break;
	case ET_EXEC:
		printf("EXEC (Executable file)\n");
		break;
	case ET_DYN:
		printf("DYN (Shared object file)\n");
		break;
	case ET_CORE:
		printf("CORE (Core file)\n");
		break;
	default:
		printf("<unknown: %x>\n", type);
	}
}
/**
 * print_entry - Print ELF entry.
 * @entry: ELF type.
 * @class: ELF Class
 * Return: none.
 */
void print_entry(unsigned long int entry, unsigned char *class)
{
	printf("  Entry point address:               ");

	if (class[EI_DATA] == ELFDATA2MSB)
	{
		entry = ((entry << 8) & 0xFF00FF00) |
			  ((entry >> 8) & 0xFF00FF);
		entry = (entry << 16) | (entry >> 16);
	}

	if (class[EI_CLASS] == ELFCLASS32)
		printf("%#x\n", (unsigned int)entry);

	else
		printf("%#lx\n", entry);
}
/**
 * main - Displays the information contained in the ELF header at the
 *        start of an ELF file.
 * @ac: Number of arguments passed into the program
 * @av: Array of arguments passed.
 * Return: 0 on success.
 */
int main(int q, char **t)
{
	Elf64_Ehdr *header;
	int openn, readd;

	if (q != 2 || t[1] == NULL)
		dprintf(STDERR_FILENO, "Usage: %s elf_filename\n",
			t[0]), exit(98);
	openn = open(t[1], O_RDONLY);
	if (openn == -1)
		dprintf(STDERR_FILENO, "Error: Cannot read file %s\n",
			t[1]), exit(98);
	header = malloc(sizeof(Elf64_Ehdr));
	if (!header)
	{
		dprintf(STDERR_FILENO, "Error: No memory allocated for %s\n",
			t[1]);
		closes_file(openn), exit(98);
	}
	readd = read(openn, header, sizeof(Elf64_Ehdr));
	if (readd == -1)
	{
		printf("Error: Cannot read file %s\n", t[1]);
		free(header), closes_file(openn), exit(98);
	}
	check_file(header->e_ident);
	print_magic(header->e_ident);
	print_class(header->e_ident);
	print_data(header->e_ident);
	print_version(header->e_ident);
	print_os_abi(header->e_ident);
	print_abi(header->e_ident);
	print_type(header->e_type, header->e_ident);
	print_entry(header->e_entry, header->e_ident);

	free(header);
	closes_file(openn);
	return (0);
}
