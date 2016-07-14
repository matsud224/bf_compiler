#include <stdint.h>

void movabs_r8_imm8(void *imm, FILE *fp);
void inc_r8(FILE *fp);
void dec_r8(FILE *fp);
void inc_r8id_byte(FILE *fp);
void dec_r8id_byte(FILE *fp);
void mov_rax_imm4(int32_t imm, FILE *fp);
void mov_rdi_imm4(int32_t imm, FILE *fp);
void mov_rdx_imm4(int32_t imm, FILE *fp);
void mov_rsi_r8(FILE *fp);
void cmp_r8id_0_byte(FILE *fp);
void ret(FILE *fp);
void syscall(FILE *fp);
int jz_dword(FILE *fp);
int jnz_dword(FILE *fp);
