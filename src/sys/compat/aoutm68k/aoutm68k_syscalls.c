/* $NetBSD: aoutm68k_syscalls.c,v 1.30 2008/06/21 19:59:09 he Exp $ */

/*
 * System call names.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * created from	NetBSD: syscalls.master,v 1.28 2008/06/21 19:58:27 he Exp
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD: aoutm68k_syscalls.c,v 1.30 2008/06/21 19:59:09 he Exp $");

#if defined(_KERNEL_OPT)
#if defined(_KERNEL_OPT)
#include "opt_ktrace.h"
#include "opt_nfsserver.h"
#include "opt_ntp.h"
#include "opt_compat_netbsd.h"
#include "opt_sysv.h"
#include "opt_compat_43.h"
#include "fs_lfs.h"
#include "fs_nfs.h"
#endif
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/signal.h>
#include <sys/mount.h>
#include <sys/sched.h>
#include <sys/syscallargs.h>
#include <compat/aoutm68k/aoutm68k_syscallargs.h>
#endif /* _KERNEL_OPT */

const char *const aoutm68k_syscallnames[] = {
	/*   0 */	"syscall",
	/*   1 */	"exit",
	/*   2 */	"fork",
	/*   3 */	"read",
	/*   4 */	"write",
	/*   5 */	"open",
	/*   6 */	"close",
	/*   7 */	"wait4",
#if defined(COMPAT_43) || !defined(_KERNEL)
	/*   8 */	"ocreat",
#else
	/*   8 */	"#8 (excluded compat_43_sys_creat)",
#endif
	/*   9 */	"link",
	/*  10 */	"unlink",
	/*  11 */	"#11 (obsolete execv)",
	/*  12 */	"chdir",
	/*  13 */	"fchdir",
	/*  14 */	"mknod",
	/*  15 */	"chmod",
	/*  16 */	"chown",
	/*  17 */	"break",
#if defined(COMPAT_20) || !defined(_KERNEL)
	/*  18 */	"getfsstat",
#else
	/*  18 */	"#18 (excluded compat_20_sys_getfsstat)",
#endif
#if defined(COMPAT_43) || !defined(_KERNEL)
	/*  19 */	"olseek",
#else
	/*  19 */	"#19 (excluded compat_43_sys_lseek)",
#endif
	/*  20 */	"getpid",
	/*  21 */	"mount",
	/*  22 */	"unmount",
	/*  23 */	"setuid",
	/*  24 */	"getuid",
	/*  25 */	"geteuid",
	/*  26 */	"ptrace",
	/*  27 */	"recvmsg",
	/*  28 */	"sendmsg",
	/*  29 */	"recvfrom",
	/*  30 */	"accept",
	/*  31 */	"getpeername",
	/*  32 */	"getsockname",
	/*  33 */	"access",
	/*  34 */	"chflags",
	/*  35 */	"fchflags",
	/*  36 */	"sync",
	/*  37 */	"kill",
#if defined(COMPAT_43) || !defined(_KERNEL)
	/*  38 */	"stat43",
#else
	/*  38 */	"#38 (excluded aoutm68k_compat_43_sys_stat)",
#endif
	/*  39 */	"getppid",
#if defined(COMPAT_43) || !defined(_KERNEL)
	/*  40 */	"lstat43",
#else
	/*  40 */	"#40 (excluded aoutm68k_compat_43_sys_lstat)",
#endif
	/*  41 */	"dup",
	/*  42 */	"pipe",
	/*  43 */	"getegid",
	/*  44 */	"profil",
#if defined(KTRACE) || !defined(_KERNEL)
	/*  45 */	"ktrace",
#else
	/*  45 */	"#45 (excluded ktrace)",
#endif
#if defined(COMPAT_13) || !defined(_KERNEL)
	/*  46 */	"sigaction13",
#else
	/*  46 */	"#46 (excluded compat_13_sys_sigaction)",
#endif
	/*  47 */	"getgid",
#if defined(COMPAT_13) || !defined(_KERNEL)
	/*  48 */	"sigprocmask13",
#else
	/*  48 */	"#48 (excluded compat_13_sys_sigprocmask)",
#endif
	/*  49 */	"__getlogin",
	/*  50 */	"__setlogin",
	/*  51 */	"acct",
#if defined(COMPAT_13) || !defined(_KERNEL)
	/*  52 */	"sigpending13",
	/*  53 */	"sigaltstack13",
#else
	/*  52 */	"#52 (excluded compat_13_sys_sigpending)",
	/*  53 */	"#53 (excluded compat_13_sys_sigaltstack)",
#endif
	/*  54 */	"ioctl",
#if defined(COMPAT_12) || !defined(_KERNEL)
	/*  55 */	"oreboot",
#else
	/*  55 */	"#55 (excluded compat_12_sys_reboot)",
#endif
	/*  56 */	"revoke",
	/*  57 */	"symlink",
	/*  58 */	"readlink",
	/*  59 */	"execve",
	/*  60 */	"umask",
	/*  61 */	"chroot",
#if defined(COMPAT_43) || !defined(_KERNEL)
	/*  62 */	"fstat43",
	/*  63 */	"ogetkerninfo",
	/*  64 */	"ogetpagesize",
#else
	/*  62 */	"#62 (excluded aoutm68k_compat_43_sys_fstat)",
	/*  63 */	"#63 (excluded compat_43_sys_getkerninfo)",
	/*  64 */	"#64 (excluded compat_43_sys_getpagesize)",
#endif
#if defined(COMPAT_12) || !defined(_KERNEL)
	/*  65 */	"msync",
#else
	/*  65 */	"#65 (excluded compat_12_sys_msync)",
#endif
	/*  66 */	"vfork",
	/*  67 */	"#67 (obsolete vread)",
	/*  68 */	"#68 (obsolete vwrite)",
	/*  69 */	"sbrk",
	/*  70 */	"sstk",
#if defined(COMPAT_43) || !defined(_KERNEL)
	/*  71 */	"ommap",
#else
	/*  71 */	"#71 (excluded compat_43_sys_mmap)",
#endif
	/*  72 */	"vadvise",
	/*  73 */	"munmap",
	/*  74 */	"mprotect",
	/*  75 */	"madvise",
	/*  76 */	"#76 (obsolete vhangup)",
	/*  77 */	"#77 (obsolete vlimit)",
	/*  78 */	"mincore",
	/*  79 */	"getgroups",
	/*  80 */	"setgroups",
	/*  81 */	"getpgrp",
	/*  82 */	"setpgid",
	/*  83 */	"setitimer",
#if defined(COMPAT_43) || !defined(_KERNEL)
	/*  84 */	"owait",
#else
	/*  84 */	"#84 (excluded compat_43_sys_wait)",
#endif
#if defined(COMPAT_12) || !defined(_KERNEL)
	/*  85 */	"oswapon",
#else
	/*  85 */	"#85 (excluded compat_12_sys_swapon)",
#endif
	/*  86 */	"getitimer",
#if defined(COMPAT_43) || !defined(_KERNEL)
	/*  87 */	"ogethostname",
	/*  88 */	"osethostname",
	/*  89 */	"ogetdtablesize",
#else
	/*  87 */	"#87 (excluded compat_43_sys_gethostname)",
	/*  88 */	"#88 (excluded compat_43_sys_sethostname)",
	/*  89 */	"#89 (excluded compat_43_sys_getdtablesize)",
#endif
	/*  90 */	"dup2",
	/*  91 */	"#91 (unimplemented getdopt)",
	/*  92 */	"fcntl",
	/*  93 */	"select",
	/*  94 */	"#94 (unimplemented setdopt)",
	/*  95 */	"fsync",
	/*  96 */	"setpriority",
	/*  97 */	"socket",
	/*  98 */	"connect",
#if defined(COMPAT_43) || !defined(_KERNEL)
	/*  99 */	"oaccept",
#else
	/*  99 */	"#99 (excluded compat_43_sys_accept)",
#endif
	/* 100 */	"getpriority",
#if defined(COMPAT_43) || !defined(_KERNEL)
	/* 101 */	"osend",
	/* 102 */	"orecv",
#else
	/* 101 */	"#101 (excluded compat_43_sys_send)",
	/* 102 */	"#102 (excluded compat_43_sys_recv)",
#endif
#if defined(COMPAT_13) || !defined(_KERNEL)
	/* 103 */	"sigreturn13",
#else
	/* 103 */	"#103 (excluded compat_13_sys_sigreturn)",
#endif
	/* 104 */	"bind",
	/* 105 */	"setsockopt",
	/* 106 */	"listen",
	/* 107 */	"#107 (obsolete vtimes)",
#if defined(COMPAT_43) || !defined(_KERNEL)
	/* 108 */	"osigvec",
	/* 109 */	"osigblock",
	/* 110 */	"osigsetmask",
#else
	/* 108 */	"#108 (excluded compat_43_sys_sigvec)",
	/* 109 */	"#109 (excluded compat_43_sys_sigblock)",
	/* 110 */	"#110 (excluded compat_43_sys_sigsetmask)",
#endif
#if defined(COMPAT_13) || !defined(_KERNEL)
	/* 111 */	"sigsuspend13",
#else
	/* 111 */	"#111 (excluded compat_13_sys_sigsuspend)",
#endif
#if defined(COMPAT_43) || !defined(_KERNEL)
	/* 112 */	"osigstack",
	/* 113 */	"orecvmsg",
	/* 114 */	"osendmsg",
#else
	/* 112 */	"#112 (excluded compat_43_sys_sigstack)",
	/* 113 */	"#113 (excluded compat_43_sys_recvmesg)",
	/* 114 */	"#114 (excluded compat_43_sys_sendmesg)",
#endif
	/* 115 */	"#115 (obsolete vtrace)",
	/* 116 */	"gettimeofday",
	/* 117 */	"getrusage",
	/* 118 */	"getsockopt",
	/* 119 */	"#119 (obsolete resuba)",
	/* 120 */	"readv",
	/* 121 */	"writev",
	/* 122 */	"settimeofday",
	/* 123 */	"fchown",
	/* 124 */	"fchmod",
#if defined(COMPAT_43) || !defined(_KERNEL)
	/* 125 */	"orecvfrom",
#else
	/* 125 */	"#125 (excluded compat_43_sys_recvfrom)",
#endif
	/* 126 */	"setreuid",
	/* 127 */	"setregid",
	/* 128 */	"rename",
#if defined(COMPAT_43) || !defined(_KERNEL)
	/* 129 */	"otruncate",
	/* 130 */	"oftruncate",
#else
	/* 129 */	"#129 (excluded compat_43_sys_truncate)",
	/* 130 */	"#130 (excluded compat_43_sys_ftruncate)",
#endif
	/* 131 */	"flock",
	/* 132 */	"mkfifo",
	/* 133 */	"sendto",
	/* 134 */	"shutdown",
	/* 135 */	"socketpair",
	/* 136 */	"mkdir",
	/* 137 */	"rmdir",
	/* 138 */	"utimes",
	/* 139 */	"#139 (obsolete 4.2 sigreturn)",
	/* 140 */	"adjtime",
#if defined(COMPAT_43) || !defined(_KERNEL)
	/* 141 */	"ogetpeername",
	/* 142 */	"ogethostid",
	/* 143 */	"osethostid",
	/* 144 */	"ogetrlimit",
	/* 145 */	"osetrlimit",
	/* 146 */	"okillpg",
#else
	/* 141 */	"#141 (excluded compat_43_sys_getpeername)",
	/* 142 */	"#142 (excluded compat_43_sys_gethostid)",
	/* 143 */	"#143 (excluded compat_43_sys_sethostid)",
	/* 144 */	"#144 (excluded compat_43_sys_getrlimit)",
	/* 145 */	"#145 (excluded compat_43_sys_setrlimit)",
	/* 146 */	"#146 (excluded compat_43_sys_killpg)",
#endif
	/* 147 */	"setsid",
	/* 148 */	"quotactl",
#if defined(COMPAT_43) || !defined(_KERNEL)
	/* 149 */	"oquota",
	/* 150 */	"ogetsockname",
#else
	/* 149 */	"#149 (excluded compat_43_sys_quota)",
	/* 150 */	"#150 (excluded compat_43_sys_getsockname)",
#endif
	/* 151 */	"#151 (unimplemented)",
	/* 152 */	"#152 (unimplemented)",
	/* 153 */	"#153 (unimplemented)",
	/* 154 */	"#154 (unimplemented)",
#if defined(NFS) || defined(NFSSERVER) || !defined(_KERNEL)
	/* 155 */	"nfssvc",
#else
	/* 155 */	"#155 (excluded nfssvc)",
#endif
#if defined(COMPAT_43) || !defined(_KERNEL)
	/* 156 */	"ogetdirentries",
#else
	/* 156 */	"#156 (excluded compat_43_sys_getdirentries)",
#endif
#if defined(COMPAT_20) || !defined(_KERNEL)
	/* 157 */	"statfs",
#else
	/* 157 */	"#157 (excluded compat_20_sys_statfs)",
#endif
#if defined(COMPAT_20) || !defined(_KERNEL)
	/* 158 */	"fstatfs",
#else
	/* 158 */	"#158 (excluded compat_20_sys_statfs)",
#endif
	/* 159 */	"#159 (unimplemented)",
	/* 160 */	"#160 (unimplemented)",
	/* 161 */	"getfh",
#if defined(COMPAT_09) || !defined(_KERNEL)
	/* 162 */	"ogetdomainname",
	/* 163 */	"osetdomainname",
	/* 164 */	"ouname",
#else
	/* 162 */	"#162 (excluded compat_09_sys_getdomainname)",
	/* 163 */	"#163 (excluded compat_09_sys_setdomainname)",
	/* 164 */	"#164 (excluded compat_09_sys_uname)",
#endif
	/* 165 */	"sysarch",
	/* 166 */	"#166 (unimplemented)",
	/* 167 */	"#167 (unimplemented)",
	/* 168 */	"#168 (unimplemented)",
#if (defined(SYSVSEM) || !defined(_KERNEL)) && !defined(_LP64) && defined(COMPAT_10)
	/* 169 */	"osemsys",
#else
	/* 169 */	"#169 (excluded 1.0 semsys)",
#endif
#if (defined(SYSVMSG) || !defined(_KERNEL)) && !defined(_LP64) && defined(COMPAT_10)
	/* 170 */	"omsgsys",
#else
	/* 170 */	"#170 (excluded 1.0 msgsys)",
#endif
#if (defined(SYSVSHM) || !defined(_KERNEL)) && !defined(_LP64) && defined(COMPAT_10)
	/* 171 */	"oshmsys",
#else
	/* 171 */	"#171 (excluded 1.0 shmsys)",
#endif
	/* 172 */	"#172 (unimplemented)",
	/* 173 */	"pread",
	/* 174 */	"pwrite",
	/* 175 */	"#175 (unimplemented { int sys_ntp_gettime ( struct ntptimeval * ntvp ) ; })",
#if defined(NTP) || !defined(_KERNEL)
	/* 176 */	"ntp_adjtime",
#else
	/* 176 */	"#176 (excluded ntp_adjtime)",
#endif
	/* 177 */	"#177 (unimplemented)",
	/* 178 */	"#178 (unimplemented)",
	/* 179 */	"#179 (unimplemented)",
	/* 180 */	"#180 (unimplemented)",
	/* 181 */	"setgid",
	/* 182 */	"setegid",
	/* 183 */	"seteuid",
#if defined(LFS) || !defined(_KERNEL)
	/* 184 */	"lfs_bmapv",
	/* 185 */	"lfs_markv",
	/* 186 */	"lfs_segclean",
	/* 187 */	"lfs_segwait",
#else
	/* 184 */	"#184 (excluded lfs_bmapv)",
	/* 185 */	"#185 (excluded lfs_markv)",
	/* 186 */	"#186 (excluded lfs_segclean)",
	/* 187 */	"#187 (excluded lfs_segwait)",
#endif
#if defined(COMPAT_12) || !defined(_KERNEL)
	/* 188 */	"stat12",
	/* 189 */	"fstat12",
	/* 190 */	"lstat12",
#else
	/* 188 */	"#188 (excluded aoutm68k_compat_12_sys_stat)",
	/* 189 */	"#189 (excluded aoutm68k_compat_12_sys_fstat)",
	/* 190 */	"#190 (excluded aoutm68k_compat_12_sys_lstat)",
#endif
	/* 191 */	"pathconf",
	/* 192 */	"fpathconf",
	/* 193 */	"#193 (unimplemented)",
	/* 194 */	"getrlimit",
	/* 195 */	"setrlimit",
#if defined(COMPAT_12) || !defined(_KERNEL)
	/* 196 */	"getdirentries",
#else
	/* 196 */	"#196 (excluded compat_12_sys_getdirentries)",
#endif
	/* 197 */	"mmap",
	/* 198 */	"__syscall",
	/* 199 */	"lseek",
	/* 200 */	"truncate",
	/* 201 */	"ftruncate",
	/* 202 */	"__sysctl",
	/* 203 */	"mlock",
	/* 204 */	"munlock",
	/* 205 */	"undelete",
	/* 206 */	"futimes",
	/* 207 */	"getpgid",
	/* 208 */	"reboot",
	/* 209 */	"poll",
#if defined(LKM) || !defined(_KERNEL)
	/* 210 */	"lkmnosys",
	/* 211 */	"lkmnosys",
	/* 212 */	"lkmnosys",
	/* 213 */	"lkmnosys",
	/* 214 */	"lkmnosys",
	/* 215 */	"lkmnosys",
	/* 216 */	"lkmnosys",
	/* 217 */	"lkmnosys",
	/* 218 */	"lkmnosys",
	/* 219 */	"lkmnosys",
#else	/* !LKM */
	/* 210 */	"#210 (excluded lkmnosys)",
	/* 211 */	"#211 (excluded lkmnosys)",
	/* 212 */	"#212 (excluded lkmnosys)",
	/* 213 */	"#213 (excluded lkmnosys)",
	/* 214 */	"#214 (excluded lkmnosys)",
	/* 215 */	"#215 (excluded lkmnosys)",
	/* 216 */	"#216 (excluded lkmnosys)",
	/* 217 */	"#217 (excluded lkmnosys)",
	/* 218 */	"#218 (excluded lkmnosys)",
	/* 219 */	"#219 (excluded lkmnosys)",
#endif	/* !LKM */
#if defined(SYSVSEM) || !defined(_KERNEL)
#if defined(COMPAT_14) || !defined(_KERNEL)
	/* 220 */	"__semctl",
#else
	/* 220 */	"#220 (excluded compat_14_semctl)",
#endif
	/* 221 */	"semget",
	/* 222 */	"semop",
	/* 223 */	"semconfig",
#else
	/* 220 */	"#220 (excluded compat_14_semctl)",
	/* 221 */	"#221 (excluded semget)",
	/* 222 */	"#222 (excluded semop)",
	/* 223 */	"#223 (excluded semconfig)",
#endif
#if defined(SYSVMSG) || !defined(_KERNEL)
#if defined(COMPAT_14) || !defined(_KERNEL)
	/* 224 */	"msgctl",
#else
	/* 224 */	"#224 (excluded compat_14_sys_msgctl)",
#endif
	/* 225 */	"msgget",
	/* 226 */	"msgsnd",
	/* 227 */	"msgrcv",
#else
	/* 224 */	"#224 (excluded compat_14_msgctl)",
	/* 225 */	"#225 (excluded msgget)",
	/* 226 */	"#226 (excluded msgsnd)",
	/* 227 */	"#227 (excluded msgrcv)",
#endif
#if defined(SYSVSHM) || !defined(_KERNEL)
	/* 228 */	"shmat",
#if defined(COMPAT_14) || !defined(_KERNEL)
	/* 229 */	"shmctl",
#else
	/* 229 */	"#229 (excluded compat_14_sys_shmctl)",
#endif
	/* 230 */	"shmdt",
	/* 231 */	"shmget",
#else
	/* 228 */	"#228 (excluded shmat)",
	/* 229 */	"#229 (excluded compat_14_shmctl)",
	/* 230 */	"#230 (excluded shmdt)",
	/* 231 */	"#231 (excluded shmget)",
#endif
	/* 232 */	"clock_gettime",
	/* 233 */	"clock_settime",
	/* 234 */	"clock_getres",
	/* 235 */	"#235 (unimplemented timer_create)",
	/* 236 */	"#236 (unimplemented timer_delete)",
	/* 237 */	"#237 (unimplemented timer_settime)",
	/* 238 */	"#238 (unimplemented timer_gettime)",
	/* 239 */	"#239 (unimplemented timer_getoverrun)",
	/* 240 */	"nanosleep",
	/* 241 */	"fdatasync",
	/* 242 */	"mlockall",
	/* 243 */	"munlockall",
	/* 244 */	"#244 (unimplemented)",
	/* 245 */	"#245 (unimplemented)",
	/* 246 */	"#246 (unimplemented)",
	/* 247 */	"#247 (unimplemented)",
	/* 248 */	"#248 (unimplemented)",
	/* 249 */	"#249 (unimplemented)",
	/* 250 */	"#250 (unimplemented)",
	/* 251 */	"#251 (unimplemented)",
	/* 252 */	"#252 (unimplemented)",
	/* 253 */	"#253 (unimplemented)",
	/* 254 */	"#254 (unimplemented)",
	/* 255 */	"#255 (unimplemented)",
	/* 256 */	"#256 (unimplemented)",
	/* 257 */	"#257 (unimplemented)",
	/* 258 */	"#258 (unimplemented)",
	/* 259 */	"#259 (unimplemented)",
	/* 260 */	"#260 (unimplemented)",
	/* 261 */	"#261 (unimplemented)",
	/* 262 */	"#262 (unimplemented)",
	/* 263 */	"#263 (unimplemented)",
	/* 264 */	"#264 (unimplemented)",
	/* 265 */	"#265 (unimplemented)",
	/* 266 */	"#266 (unimplemented)",
	/* 267 */	"#267 (unimplemented)",
	/* 268 */	"#268 (unimplemented)",
	/* 269 */	"#269 (unimplemented)",
	/* 270 */	"__posix_rename",
	/* 271 */	"swapctl",
#if defined(COMPAT_30) || !defined(_KERNEL)
	/* 272 */	"getdents",
#else
	/* 272 */	"#272 (excluded compat_30_sys_getdents)",
#endif
	/* 273 */	"minherit",
	/* 274 */	"lchmod",
	/* 275 */	"lchown",
	/* 276 */	"lutimes",
	/* 277 */	"__msync13",
	/* 278 */	"__stat13",
	/* 279 */	"__fstat13",
	/* 280 */	"__lstat13",
	/* 281 */	"__sigaltstack14",
	/* 282 */	"__vfork14",
	/* 283 */	"__posix_chown",
	/* 284 */	"__posix_fchown",
	/* 285 */	"__posix_lchown",
	/* 286 */	"getsid",
	/* 287 */	"#287 (unimplemented)",
#if defined(KTRACE) || !defined(_KERNEL)
	/* 288 */	"fktrace",
#else
	/* 288 */	"#288 (excluded ktrace)",
#endif
	/* 289 */	"preadv",
	/* 290 */	"pwritev",
#if defined(COMPAT_16) || !defined(_KERNEL)
	/* 291 */	"__sigaction14",
#else
	/* 291 */	"#291 (excluded compat_16_sys___sigaction14)",
#endif
	/* 292 */	"__sigpending14",
	/* 293 */	"__sigprocmask14",
	/* 294 */	"__sigsuspend14",
#if defined(COMPAT_16) || !defined(_KERNEL)
	/* 295 */	"__sigreturn14",
#else
	/* 295 */	"#295 (excluded compat_16_sys___sigreturn14)",
#endif
	/* 296 */	"__getcwd",
	/* 297 */	"fchroot",
	/* 298 */	"fhopen",
	/* 299 */	"fhstat",
#if defined(COMPAT_20) || !defined(_KERNEL)
	/* 300 */	"fhstatfs",
#else
	/* 300 */	"#300 (excluded compat_20_sys_fhstatfs)",
#endif
#if defined(SYSVSEM) || !defined(_KERNEL)
	/* 301 */	"____semctl13",
#else
	/* 301 */	"#301 (excluded ____semctl13)",
#endif
#if defined(SYSVMSG) || !defined(_KERNEL)
	/* 302 */	"__msgctl13",
#else
	/* 302 */	"#302 (excluded __msgctl13)",
#endif
#if defined(SYSVSHM) || !defined(_KERNEL)
	/* 303 */	"__shmctl13",
#else
	/* 303 */	"#303 (excluded __shmctl13)",
#endif
	/* 304 */	"lchflags",
	/* 305 */	"issetugid",
	/* 306 */	"getcontext",
	/* 307 */	"setcontext",
};