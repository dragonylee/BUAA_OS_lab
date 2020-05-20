/*
 * operations on IDE disk.
 */

#include "fs.h"
#include "lib.h"
#include <mmu.h>

#define IDE_BEGIN_ADDR 0x13000000
#define IDE_OFFSET_ADDR IDE_BEGIN_ADDR + 0x0000
#define IDE_OFFSETHI_ADDR IDE_BEGIN_ADDR + 0x0008
#define IDE_ID_ADDR IDE_BEGIN_ADDR + 0x0010
#define IDE_OP_ADDR IDE_BEGIN_ADDR + 0x0020
#define IDE_STATUS_ADDR IDE_BEGIN_ADDR + 0x0030
#define IDE_BUFFER_ADDR IDE_BEGIN_ADDR + 0x4000
#define IDE_BUFFER_SIZE 0x0200

// Overview:
// 	read data from IDE disk. First issue a read request through
// 	disk register and then copy data from disk buffer
// 	(512 bytes, a sector) to destination array.
//
// Parameters:
//	diskno: disk number.
// 	secno: start sector number.
// 	dst: destination for data read from IDE disk.
// 	nsecs: the number of sectors to read.
//
// Post-Condition:
// 	If error occurred during read the IDE disk, panic.
//
// Hint: use syscalls to access device registers and buffers
void ide_read(u_int diskno, u_int secno, void *dst, u_int nsecs)
{
	// 0x200: the size of a sector: 512 bytes.
	int offset_begin = secno * IDE_BUFFER_SIZE;
	int offset_end = offset_begin + nsecs * IDE_BUFFER_SIZE;
	int offset = 0;
	u_int temp = 0;
	int ret = 0;

	while (offset_begin + offset < offset_end)
	{
		// Your code here
		// error occurred, then panic.
		ret = 0;
		temp = offset_begin + offset;
		syscall_write_dev((u_int)&diskno, IDE_ID_ADDR, sizeof(u_int));
		syscall_write_dev((u_int)&temp, IDE_BEGIN_ADDR, sizeof(u_int));
		syscall_write_dev((u_int)&ret, IDE_OP_ADDR, sizeof(u_int));
		syscall_read_dev((u_int)&ret, IDE_STATUS_ADDR, sizeof(u_int));
		if(!ret)
			user_panic("ide_read error\n");
		syscall_read_dev((u_int)(dst + offset), IDE_BUFFER_ADDR, IDE_BUFFER_SIZE);
		offset += IDE_BUFFER_SIZE;
	}
}

// Overview:
// 	write data to IDE disk.
//
// Parameters:
//	diskno: disk number.
//	secno: start sector number.
// 	src: the source data to write into IDE disk.
//	nsecs: the number of sectors to write.
//
// Post-Condition:
//	If error occurred during read the IDE disk, panic.
//
// Hint: use syscalls to access device registers and buffers
void ide_write(u_int diskno, u_int secno, void *src, u_int nsecs)
{
	// Your code here
	// int offset_begin = ;
	// int offset_end = ;
	// int offset = ;
	int offset_begin = secno * IDE_BUFFER_SIZE;
	int offset_end = offset_begin + nsecs * IDE_BUFFER_SIZE;
	int offset = 0;
	int temp = 0;
	int ret = 0;

	// DO NOT DELETE WRITEF !!!
	writef("diskno: %d\n", diskno);

	// while ( < ) {
	// copy data from source array to disk buffer.

	// if error occur, then panic.
	// }
	while (offset_begin + offset < offset_end)
	{
		ret = 1;
		temp = offset_begin + offset;
		syscall_write_dev((u_int)&diskno, IDE_ID_ADDR, sizeof(u_int));
		syscall_write_dev((u_int)&temp, IDE_BEGIN_ADDR, sizeof(u_int));
		syscall_write_dev((u_int)(src + offset), IDE_BUFFER_ADDR, IDE_BUFFER_SIZE);
		syscall_write_dev((u_int)&ret, IDE_OP_ADDR, sizeof(u_int));
		syscall_read_dev((u_int)&ret, IDE_STATUS_ADDR, sizeof(u_int));
		if(!ret)
			user_panic("ide_write error\n");
		offset+=IDE_BUFFER_SIZE;
	}
}

