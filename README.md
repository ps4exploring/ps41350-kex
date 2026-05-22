# ps41350-kex
#### no, you cant inject it without userland jailbreak.
#### btw there's a UAF exploit in CSS. so ig we gonna have a userland soon
trying to recreate zero-day exploit.

if u dont wanna read this: the vulnerability is a race condition between a socket write operation and a custom syscall that doesnt properly synchronize access to shared kernel memory, allowing an attacker to redirect kernel execution to a userland rop chain.



## loader.c (stage1):
* bypass kaslr
* finding rop gadgets in kernel memory
* using a race condition via rfork to spray a rop chain into the kernel
* copying a ps4-hen **(NOT GOLDHEN!)** payload from userland into kernel memory
* executing the payload by disabling the wp (aka write protection) bit in CR0

## the vulnerability: race condition in socket + custom syscall
the code doesnt exploit a classic buffer overflow or use-after-free. instead, it exploits a race condition - a lack of proper synchronization between two different system calls in the kernel.
**the exploit creates two threads using rfork(RFPROC | RFMEM):**
| thread | role   | action |
|--------|--------|--------|
| child   | attacker| spams SONY_FSC2H_CTRL with 0x20005 in an infinite loop |
| parent  | victim  | 	sprays ROP chain via sendto() (syscall 34) + triggers SONY_FSC2H_CTRL with 0x10001 |

## whats the race window?

somewhere in the kernel, theres a shared data structure (likely a socket object or a file descriptor context) that is accessed by both:

```sendto()``` on a socket - writes user-controlled data into kernel memory (the rop chain)

```SONY_FSC2H_CTRL``` - a custom sony syscall that probably:

puts the calling thread to sleep (waiting for an event)

or copies data between kernel/userland without proper locking

the bug is that **these two paths don't use proper locking** (mutex, spinlock, etc.). so when the child is inside the kernel waiting, the parent can race in and modify the same kernel object.

visualising the race:
```
time →
────────────────────────────────────────────────────────────────────

child:  [syscall][inside kernel][sleep/wait][wake up][syscall exit]
                                  ↑
parent:  [syscall][write ROP][trigger][syscall]
                     ↑              ↑
                     │              └─ causes wakeup/interrupt
                     └─ writes to same object child is waiting on
```
> if the parent writes the rop chain just as the child is in a vulnerable state (e.g., kernel has released a lock but hasnt validated data), the child thread will return from ```SONY_FSC2H_CTRL``` with kernel rip pointing to user-controlled data.

## why 200 spray attempts?
```C
for(int k = 0; k < 200; k++) {
    sys_call(34, s, (long)rop, 0);  // spray via sendto
    sys_call(SONY_FSC2H_CTRL, 0x10001, 0x1337, 0); // trigger
}
```

**the exploit tries 200 times because:**

* race windows are tiny - measured in microseconds

* not every attempt wins the race

* spraying increases probability of hitting the exact timing

## what makes this a vulnerability?
the core bug is that the kernel assumes exclusive access to a resource but doesnt enforce it. two threads can enter different syscall handlers operating on the same kernel object at the same time - and one of them ends up executing user-controlled data as code.
