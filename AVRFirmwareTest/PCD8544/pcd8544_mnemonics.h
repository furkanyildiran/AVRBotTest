#ifndef __PCD8544_MNEMONICS_H__
#define __PCD8544_MNEMONICS_H__

#define CHIP_ACTIVE  0
#define CHIP_PWR_DWN 1
#define HORZNTL_ADDR 0
#define VERTICL_ADDR 1
#define BASIC_I_SET  0
#define EXTND_I_SET  1
#define DSPLY_BLANK  0
#define NORMAL_MODE  4
#define ALL_SEGMT_ON 1
#define INV_VID_MODE 5
#define TEMP_COEFF0  0
#define TEMP_COEFF1  1
#define TEMP_COEFF2  2
#define TEMP_COEFF3  3
#define BIAS7        0
#define BIAS6        1
#define BIAS5        2
#define BIAS4        3
#define BIAS3        4
#define BIAS2        5
#define BIAS1        6
#define BIAS0        7

#define PD_bit 2
#define V_bit  1
#define H_bit  0

#define func_set(power_down_ctrl, entry_mode, extnd_ins_set_mode)   (0x20 | (power_down_ctrl << PD_bit) | (entry_mode << V_bit) | (extnd_ins_set_mode << H_bit))
#define dsply_ctrl(mode)       (0x08 | mode)
#define set_y_addr(addr)       (0x40 | addr)
#define set_x_addr(addr)       (0x80 | addr)
#define temp_ctrl(coeff)       (0x04 | coeff)
#define bias_systm(bias)       (0x10 | bias)
#define set_Vop(Vop)           (0x80 | Vop)

#define INDIS_OFFSET  0x20
#define CHAR_WIDTH    0x05
#define CHAR_NUMBER   0x5B
#define LINE_0        0
#define LINE_1        1
#define LINE_2        2
#define LINE_3        3
#define LINE_4        4
#define LINE_5        5

#define res_low_pulse_width 5   //must be at least 100ns
#define MAX_CHAR_NUM_IN_LINE 16

#endif 