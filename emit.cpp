#include <string.h>
#include <stdint.h>
#include "emit.h"

void movabs_r8_tape(FILE *fp){

	return;
}

void inc_r8(FILE *fp){
	uint8_t code[] = { 0x49, 0xFF, 0xC0 };
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void dec_r8(FILE *fp){
	uint8_t code[] = { 0x49, 0xFF, 0xC8 };
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void inc_r8id_byte(FILE *fp){
	uint8_t code[] = { 0x41, 0xFE, 0x00 };
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void dec_r8id_byte(FILE *fp){
	uint8_t code[] = { 0x41, 0xFE, 0x08 };
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void mov_rax_imm4(int32_t imm, FILE *fp){
	uint8_t code[] = { 0x48, 0xC7, 0xC0, 0x01, 0x00, 0x00, 0x00 };
	memcpy(code+3, &imm, 4);
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void mov_rdi_imm4(int32_t imm, FILE *fp){
	uint8_t code[] = { 0x48, 0xC7, 0xC7, 0x01, 0x00, 0x00, 0x00 };
	memcpy(code+3, &imm, 4);
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void mov_rdx_imm4(int32_t imm, FILE *fp){
	uint8_t code[] = { 0x48, 0xC7, 0xC2, 0x01, 0x00, 0x00, 0x00 };
	memcpy(code+3, &imm, 4);
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void mov_rsi_r8(FILE *fp){
	uint8_t code[] = { 0x4C, 0x89, 0xC6 };
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void cmp_r8id_0_byte(FILE *fp){
	uint8_t code[] = { 0x41, 0x80, 0x38, 0x00 };
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void ret(FILE *fp){
	uint8_t code[] = { 0xC3 };
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

void syscall(FILE *fp){
	uint8_t code[] = { 0x0F, 0x05 };
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return;
}

int jz_dword(FILE *fp){
	int modify_index = *index + 2;
	uint8_t code[] = { 0x0F, 0x84, 0x00, 0x00, 0x00, 0x00 };
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return modify_index;
}

int jnz_dword(FILE *fp){
	int modify_index = *index + 2;
	uint8_t code[] = { 0x0F, 0x85, 0x00, 0x00, 0x00, 0x00 };
	memcpy(dest + *index, code, sizeof(code));
	*index += sizeof(code);
	return modify_index;
}
