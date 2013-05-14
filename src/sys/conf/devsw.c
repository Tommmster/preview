/*
 * MACHINE GENERATED: DO NOT EDIT
 *
 * devsw.c, from "MINIMAL"
 */

#include <sys/param.h>
#include <sys/conf.h>

#define	DEVSW_ARRAY_SIZE(x)	(sizeof((x))/sizeof((x)[0]))

/* device switch table for block device */
extern const struct bdevsw md_bdevsw;
extern const struct bdevsw swap_bdevsw;
extern const struct bdevsw dk_bdevsw;

const struct bdevsw *bdevsw0[] = {
	NULL,
	NULL,
	NULL,
	NULL,
	&swap_bdevsw,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&md_bdevsw,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&dk_bdevsw,
};

const struct bdevsw **bdevsw = bdevsw0;
const int sys_bdevsws = DEVSW_ARRAY_SIZE(bdevsw0);
int max_bdevsws = DEVSW_ARRAY_SIZE(bdevsw0);

/* device switch table for character device */
extern const struct cdevsw cons_cdevsw;
extern const struct cdevsw swap_cdevsw;
extern const struct cdevsw ctty_cdevsw;
extern const struct cdevsw mem_cdevsw;
extern const struct cdevsw log_cdevsw;
extern const struct cdevsw filedesc_cdevsw;
extern const struct cdevsw md_cdevsw;
extern const struct cdevsw dk_cdevsw;
extern const struct cdevsw cpuctl_cdevsw;
extern const struct cdevsw at32usart_cdevsw;

const struct cdevsw *cdevsw0[] = {
	&cons_cdevsw,
	&swap_cdevsw,
	&ctty_cdevsw,
	&mem_cdevsw,
	NULL,
	NULL,
	&log_cdevsw,
	&filedesc_cdevsw,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&at32usart_cdevsw,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&md_cdevsw,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&dk_cdevsw,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&cpuctl_cdevsw,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};

const struct cdevsw **cdevsw = cdevsw0;
const int sys_cdevsws = DEVSW_ARRAY_SIZE(cdevsw0);
int max_cdevsws = DEVSW_ARRAY_SIZE(cdevsw0);

/* device conversion table */
struct devsw_conv devsw_conv0[] = {
	{ "crypto", -1, 160 },
	{ "pf", -1, 161 },
	{ "fss", 163, 163 },
	{ "pps", -1, 164 },
	{ "ptm", -1, 165 },
	{ "atabus", -1, 166 },
	{ "drvctl", -1, 167 },
	{ "dk", 168, 168 },
	{ "tap", -1, 169 },
	{ "veriexec", -1, 170 },
	{ "fw", -1, 171 },
	{ "ucycom", -1, 172 },
	{ "gpio", -1, 173 },
	{ "utoppy", -1, 174 },
	{ "bthub", -1, 175 },
	{ "amr", -1, 176 },
	{ "lockstat", -1, 177 },
	{ "putter", -1, 178 },
	{ "srt", -1, 179 },
	{ "drm", -1, 180 },
	{ "bio", -1, 181 },
	{ "twa", -1, 187 },
	{ "cpuctl", -1, 188 },
	{ "pad", -1, 189 },
	{ "zfs", -1, 190 },
	{ "tprof", -1, 191 },
	{ "isv", -1, 192 },
	{ "video", -1, 193 },
	{ "hdaudio", -1, 195 },
	{ "cons", -1, 0 },
	{ "swap", 4, 1 },
	{ "ctty", -1, 2 },
	{ "mem", -1, 3 },
	{ "pts", -1, 4 },
	{ "ptc", -1, 5 },
	{ "log", -1, 6 },
	{ "filedesc", -1, 7 },
	{ "sd", 19, 9 },
	{ "vnd", 2, 11 },
	{ "bpf", -1, 12 },
	{ "dz", -1, 16 },
	{ "zstty", -1, 17 },
	{ "pts_ultrix", -1, 20 },
	{ "ptc_ultrix", -1, 21 },
	{ "mem_ultrix", -1, 43 },
	{ "st", 18, 46 },
	{ "cd", 25, 47 },
	{ "ss", -1, 53 },
	{ "ch", -1, 54 },
	{ "uk", -1, 55 },
	{ "rz", 21, 56 },
	{ "at32usart", -1, 77 },
	{ "ccd", 24, 87 },
	{ "wsdisplay", -1, 88 },
	{ "wskbd", -1, 89 },
	{ "wsmouse", -1, 90 },
	{ "ipl", -1, 91 },
	{ "rnd", -1, 92 },
	{ "tun", -1, 93 },
	{ "lkm", -1, 94 },
	{ "scsibus", -1, 95 },
	{ "raid", 32, 96 },
	{ "md", 17, 97 },
	{ "stic", -1, 98 },
	{ "audio", -1, 99 },
	{ "clockctl", -1, 100 },
	{ "wsmux", -1, 101 },
	{ "wsfont", -1, 102 },
	{ "cgd", 33, 104 },
	{ "ksyms", -1, 105 },
	{ "nsmb", -1, 106 },
};

struct devsw_conv *devsw_conv = devsw_conv0;
int max_devsw_convs = DEVSW_ARRAY_SIZE(devsw_conv0);

const dev_t swapdev = makedev(4, 0);
const dev_t zerodev = makedev(3, DEV_ZERO);

/* mem_no is only used in iskmemdev() */
const int mem_no = 3;