About this Document:
	This document is goint to analyis ELF file output after compilation.We will use  following three commond :
		1. nm
		2. objdum
		3.readelf
	To analysis the object file.


Compiler Symbols Tables :
			Symbol table is an important data structure created and maintained by compilers in order to store information about the
			following :
				1->Occurrence of various entities{Like variable names} .
				2->The function names of programes
				3->The objects, classes, interfaces	  
			It stores identifier as well as it’s associated attributes like scope, type, line-number of occurrence, etc.The analysis and the synthesis parts
			of a compiler used the Symbol table.Symbol table can be implemented using various data structures like:
				1->LinkedList
				2->Hash Table
				3->Tree
			
			Scope Management:
				A compiler maintains mainly three types of symbol tables :
				1->Local Symbols Table
				2->Global Symbols Table
				3->Weak Symbols Table

Local Symbols Table :
		     The Local symbols are not visible outside the object file containing their definition. The Local symbols of the same name may exist in multiple files without
		     interfering with each other.
		     
Local Symbols Table :
		    The Global symbols are visible to all object files being combined. One file's definition of a global symbol will satisfy another file's undefined reference to the same
		    global symbol.
Weak Symbols Table  :
		    The Weak symbols resemble global symbols, but their definitions have lower precedence.
		     
		     
		     


For any kind of elf binarary objdump show all symbols table using follwing keyword:		 
		The symbol is a local (l), global (g), unique global (u), neither global nor local (a space) or both global and local (!).  A symbol can be neither local or global 
		for a variety of reasons,e.g., because it is used for debugging, but it is probably an indication of a bug if it is ever both local and global.	
		
		"w" The symbol is weak (w) or strong (a space).
           	"C" The symbol denotes a constructor (C) or an ordinary symbol (a space).
		"W" The symbol is a warning (W) or a normal symbol (a space).  A warning symbol's name is a message to be displayed if the symbol following the warning symbol is ever
		 referenced.
	       "I"
           	"i" The symbol is an indirect reference to another symbol (I), a function to be evaluated during reloc processing (i) or a normal symbol (a space).
               "d"
               "D" The symbol is a debugging symbol (d) or a dynamic symbol (D) or a normal symbol (a space).
               "F"
               "f"
               "O" The symbol is the name of a function (F) or a file (f) or an object (O) or just a normal symbol (a space).
		
		
		
		
		Case 01 : $ objdump -x code01 | grep l
		*****************************************
		0000000000000254 l    d  .note.ABI-tag	0000000000000000              .note.ABI-tag
		00000000000002b8 l    d  .dynsym	0000000000000000              .dynsym
		0000000000000360 l    d  .dynstr	0000000000000000              .dynstr
		0000000000000520 l    d  .plt.got	0000000000000000              .plt.got
		0000000000000530 l    d  .text		0000000000000000              .text
		00000000000006d4 l    d  .fini		0000000000000000              .fini
		00000000000006e0 l    d  .rodata	0000000000000000              .rodata
		0000000000000704 l    d  .eh_frame_hdr	0000000000000000              .eh_frame_hdr
		0000000000000740 l    d  .eh_frame	0000000000000000              .eh_frame
		0000000000200db8 l    d  .init_array	0000000000000000              .init_array
		0000000000200dc0 l    d  .fini_array	0000000000000000              .fini_array
		0000000000200dc8 l    d  .dynamic	0000000000000000              .dynamic
		
		Case 02 :$ objdump -x code01 | grep g
		objdump -x code01 | grep  "g "
  		 .note.ABI-tag 00000020  0000000000000254  0000000000000254  00000254  2**2
		00000000000006d0 g     F .text	0000000000000002              __libc_csu_fini
		0000000000201010 g       .data	0000000000000000              _edata
		00000000000006d4 g     F .fini	0000000000000000              _fini
		0000000000201000 g       .data	0000000000000000              __data_start
		0000000000201008 g     O .data	0000000000000000              .hidden __dso_handle
		00000000000006e0 g     O.rodata	0000000000000004              _IO_stdin_used
		0000000000000660 g     F .text	0000000000000065              __libc_csu_init
		0000000000201018 g       .bss	0000000000000000              _end
		0000000000000530 g     F .text	000000000000002b              _start
		0000000000201010 g       .bss	0000000000000000              __bss_start
		000000000000063a g     F .text	0000000000000017              main
		0000000000201010 g     O .data	0000000000000000              .hidden __TMC_END__
		00000000000004e8 g     F .init	0000000000000000              _init
		
		Case 03 :$ objdump -x code01 | grep  "w "
		0000000000000000  w      *UND*	0000000000000000              _ITM_deregisterTMCloneTable
		0000000000201000  w      .data	0000000000000000              data_start
		0000000000000000  w      *UND*	0000000000000000              __gmon_start__
		0000000000000000  w      *UND*	0000000000000000              _ITM_registerTMCloneTable
		0000000000000000  w    F *UND*	0000000000000000              __cxa_finalize@@GLIBC_2.2.5
		

Memory layout of a Process :
============================
		When we compiled a source file from the GNU tool-chain compiler then it may take single object code or multiple object code and linker link different
		object code as input in to single output file.During the linking the linker done many thing on input object file:
		
		1->ld combines a number of object and archive files and relocates their data and ties up symbol references. 
		2->ld take .text,.bss,.stack.data of many input object file and map it into single binary ELF formate that called address relocation.
		   In this three symbols table are relocated that are given bellow:
		   	1->Local Symbols Table
			2->Global Symbols Table
			3->Weak Symbols Table
		Each ELF file contain three fundamental object that are given bellow:
			1-> ELF Header
			2-> Program Header Table
			3-> Section Header Table
1-> ELF Header:
	      This header provide short description about the ELF file formate. Each ELF file is made from one ELF header,and this header contain the following:
	      1->File magic number(7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00)
	      2->Class:            (ELF64)
	      3->OS/ABI:            (UNIX - System V)
  	      4->ABI Version                       
              5->Type:               (REL (Relocatable file)/DYN (Shared object file)
              6->Machine:            (Advanced Micro Devices X86-64)
              7->Entry point address (0x0                          )

              8->Start of section headers    (  4576 bytes into file)
  
              9->Size of program headers:     (    0 bytes )
             10->Number of program headers:   (    0       )
             11->Size of section headers:     (    64 (bytes)
             12->Number of section headers:   (      21     )
  	     13->Section header string table index ( 20 )

	1.0->ELF Header structure :
	     The ELF header defines whether to use 32- or 64-bit addresses. The ELF header structure is 52 or 64 bytes long for 32-bit and 64-bit binaries respectively.
	     The ELF header defines following area of binaries:
	        1->This Structure define the magic number of elf binary using the e_ident field of strucutures.
	        2->This structure signify 32- or 64-bit format, respectively and  provides the little or big endianness of CPU.
	        3->Identifies the target operating system ABI.
	        4->It  specifies the ABI version. Its interpretation depends on the target ABI.
	        5->Specifies target instruction set architecture.
	        6->Specifies entry point to the memory address from where the process starts executing.
	        7->Points out the start of the program header table.
	        8->Points to the start of the section header table.
	        9->Contains the size of this header, normally 64 Bytes for 64-bit and 52 Bytes for 32-bit format.
	       11->Contains the size of a program header table entry.
	      
	      
2->Program header:
            The Program header table, describing zero or more memory segments.The program header table tells the system how to create a process image{final elf}.
            Program header structure following element that described given bellow:
            	2.1->p_type[0x00]Identifies the type of the segment.
            	    1.0->Program header table entry unused
            	    1.1->Loadable segment and Dynamic linking information.
            	    1.2->Interpreter Auxiliary information
            	    1.3->Segment containing program header table itself
           	2.2->p_flags[0x04/0x08] Identifies the Segment-dependent flags
           	2.3->p_offset:	Offset of the segment in the file image.
           	2.4->p_vaddr : Virtual address of the segment in memory.
           	2.5->p_paddr :	On systems where physical address is relevant, reserved for segment's physical address.
           	2.6->p_filesz:	Size in bytes of the segment in the file image. May be 0.
           	2.7->p_memsz :	Size in bytes of the segment in memory. May be 0.
           	2.8->p_flags :	Segment-dependent flags (position for 32-bit structure).
           
           The programe header shows the segments used at run time and this entities is zero for relocatble object file.

3->Section header:
           The section header  is used to define the set of section[code,data,bss] of individual binaries.At the linking stage these section is relocated to segment.
           This header contain the following abstraction :
           3.0->sh_name[0x00]:An offset to a string in the .shstrtab section that represents the name of this section
           3.1->sh_type[0x04]:	Identifies the type of this header.
           **********************************************************************************
           		0x0	SHT_NULL			Section header table entry unused
			0x1	SHT_PROGBITS			Program data
			0x2	SHT_SYMTAB			Symbol table
			0x3	SHT_STRTAB			String table
			0x4	SHT_RELA			Relocation entries with addends
			0x5	SHT_HASH			Symbol hash table
			0x6	SHT_DYNAMIC			Dynamic linking information
			0x7	SHT_NOTE			Notes
			0x8	SHT_NOBITS			Program space with no data (bss)
			0x9	SHT_REL				Relocation entries, no addends
			0x0A	SHT_SHLIB			Reserved
			0x0B	SHT_DYNSYM			Dynamic linker symbol table
			0x0E	SHT_INIT_ARRAY			Array of constructors
			0x0F	SHT_FINI_ARRAY			Array of destructors
			0x10	SHT_PREINIT_ARRAY		Array of pre-constructors
			0x11	SHT_GROUP			Section group
			0x12	SHT_SYMTAB_SHNDX		Extended section indices
			0x13	SHT_NUM				Number of defined types.
			0x60000000 SHT_LOOS			Start OS-specific.
	 ******************************************************************************************
4->Program memory :
	A computer program memory can be largely categorized into two sections: read-only and read-write.This distinction grew from early systems holding their main program in 
	read-only memory such as Mask ROM, PROM or EEPROM .
	
	As systems became more complex and programs were loaded from other media into RAM instead of executing from ROM and some portions of the program's memory should not be 
	modified was retained.These became the .text and .rodata segments of the program.Keep remember which could be written to divided into a number of other segments for specific
	tasks.So segment/Section of program's memory:
	
	
	4.0->Text segment/section:
	         The code/text segment is where a portion of an object file stored and which contains executable instructions.As a memory region, a text segment may be placed
	          below the heap or stack in order to prevent heaps and stack overflows from overwriting it.Usually,the text segment is sharable so that only a single copy needs
	          to be in memory for frequently executed programs.Also, the text segment is often read-only, to prevent a program from accidentally modifying its instructions.
	          $ objdump -D code01 ;This will producd the disassemble code and go .text section this contain the address of following:
	          
	          Disassembly of section .text:
	          		4.0.0-> 0000000000000530 <_start>
	          		4.0.1-> 0000000000000560 <deregister_tm_clones>
	          		4.0.2-> 00000000000005a0 <register_tm_clones>
	          		4.0.3-> 00000000000005f0 <__do_global_dtors_aux>
	          		4.0.4->0000000000000630 <frame_dummy>:
	          		4.0.5->000000000000063a <main>:
                                4.0.6->0000000000000660 <__libc_csu_init>:
                                4.0.7->00000000000006d0 <__libc_csu_fini>:
                  Or We can check from the comond line : $objdump -x code01 | grep text
 				13 .text         000001a2  0000000000000530  0000000000000530  00000530  2**4
				0000000000000530 l    d  .text	0000000000000000              .text
				0000000000000560 l     F .text	0000000000000000              deregister_tm_clones
				00000000000005a0 l     F .text	0000000000000000              register_tm_clones
				00000000000005f0 l     F .text	0000000000000000              __do_global_dtors_aux
				0000000000000630 l     F .text	0000000000000000              frame_dummy
				00000000000006d0 g     F .text	0000000000000002              __libc_csu_fini
				0000000000000660 g     F .text	0000000000000065              __libc_csu_init
				0000000000000530 g     F .text	000000000000002b              _start
				000000000000063a g     F .text	0000000000000017              main



	          
	4.1->Data segment/section:
		The .data segment contains any global or static variables which have a pre-defined value and can be modified. That is any variables that are not defined within 
		a function (and thus can be accessed from anywhere) or are defined in a function but are defined as static so they retain their address across subsequent calls.
		For any elf file we can check contain of data/rodata from "objdump -x code01 | grep .data" commond:
		
		
				15 .rodata       00000022  00000000000006e0  00000000000006e0  000006e0  2**2
 				22 .data         00000010  0000000000201000  0000000000201000  00001000  2**3
				00000000000006e0 l    d  .rodata		0000000000000000              .rodata
				0000000000201000 l    d  .data			0000000000000000              .data
				0000000000201000  w      .data			0000000000000000              data_start
				0000000000201010 g       .data			0000000000000000              _edata
				0000000000201000 g       .data			0000000000000000              __data_start
				0000000000201007 g     O .data			0000000000000000              .hidden __dso_handle
				00000000000006e0 g     O .rodata		0000000000000004              _IO_stdin_used
				0000000000201010 g     O .data			0000000000000000              .hidden __TMC_END__

		
	
	4.2->Bss segment/section:
		The BSS segment, also known as uninitialized data, is usually adjacent to the data segment. The BSS segment contains all global variables and static variables
		 that are initialized to zero or do not have explicit initialization in source code. For instance, a variable defined as static int i; would be contained in the
		 BSS segment.
		 
		 For any elf file we can check contain of data/rodata from objdump -x code01 | grep .bss commond:
				 23 .bss         	 00000007  0000000000201010  0000000000201010  00001010  2**0
				0000000000201010 l    d  .bss	0000000000000000              .bss
				0000000000201010 l     O .bss	0000000000000001              completed.7697
				0000000000201017 g       .bss	0000000000000000              _end
				0000000000201010 g       .bss	0000000000000000              __bss_start

	4.3->Heap segment/section:
		The heap area commonly begins at the end of the .bss and .data segments and grows to larger addresses from there. The heap area is managed by malloc, calloc, realloc,
		 and free, which may use the brk and sbrk system calls to adjust its size. The heap area is shared by all threads, shared libraries, and dynamically loaded modules 
		 in a process.
	4.4->Stack segment/section:
		The stack area contains the program stack, a LIFO structure, typically located in the higher parts of memory. A "stack pointer" register tracks the top of the stack;
		it is adjusted each time a value is "pushed" onto the stack. The set of values pushed for one function call is termed a "stack frame". A stack frame consists at minimum
		of a return address.The Automatic variables are also allocated on the stack.The stack area traditionally adjoined the heap area and they grew towards each other; when
		the stack pointer met the heap pointer, free memory was exhausted. 

	So using the external linker script we can modified or redefined the Program memory of the process .These are normal segment of the program memory.There are many that 
	given given bellow:
	
	Section to Segment mapping:
  		Segment Sections...
   		00     
  		01     .interp 
   		02     .interp .note.ABI-tag .note.gnu.build id .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt .init .plt .plt.got .text .fini .rodata 
   		       .eh_frame_hdr .eh_frame 
   		03     .init_array .fini_array .dynamic .got .data .bss 
   		04     .dynamic 
   		05     .note.ABI-tag .note.gnu.build-id 
   		06     .eh_frame_hdr      
   		07     .init_array .fini_array .dynamic .got 
   		

Real time Example :
===================	 	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	         
             
	     
 

	



			
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
