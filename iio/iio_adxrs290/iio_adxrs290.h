/***************************************************************************//**
 *   @file   iio_adxrs290.h
 *   @brief  Implementation of ADXRS290 iio.
 *   @author Kister Genesis Jimenez (kister.jimenez@analog.com)
********************************************************************************
 * Copyright 2020(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *  - The use of this software may or may not infringe the patent rights
 *    of one or more patent holders.  This license does not release you
 *    from the requirement that you obtain separate licenses from these
 *    patent holders to use this software.
 *  - Use of the software either in source or binary form, must be run
 *    on or directly connected to an Analog Devices Inc. component.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#ifndef IIO_ADXRS290_H
#define IIO_ADXRS290_H

#include "iio_types.h"

ssize_t get_adxrs290_iio_reg(void *device, char *buf, size_t len,
			     const struct iio_ch_info *channel);
ssize_t set_adxrs290_iio_reg(void *device, char *buf, size_t len,
			     const struct iio_ch_info *channel);
ssize_t get_adxrs290_iio_ch_raw(void *device, char *buf, size_t len,
				const struct iio_ch_info *channel);
ssize_t get_adxrs290_iio_ch_scale(void *device, char *buf, size_t len,
				  const struct iio_ch_info *channel);
ssize_t set_adxrs290_iio_ch_hpf(void *device, char *buf, size_t len,
				const struct iio_ch_info *channel);
ssize_t get_adxrs290_iio_ch_hpf(void *device, char *buf, size_t len,
				const struct iio_ch_info *channel);
ssize_t set_adxrs290_iio_ch_lpf(void *device, char *buf, size_t len,
				const struct iio_ch_info *channel);
ssize_t get_adxrs290_iio_ch_lpf(void *device, char *buf, size_t len,
				const struct iio_ch_info *channel);

static struct iio_attribute adxrs290_iio_ch_attr_3db_hpf_freq_val = {
	.name = "filter_high_pass_3db_frequency",
	.show = get_adxrs290_iio_ch_hpf,
	.store = set_adxrs290_iio_ch_hpf
};

static struct iio_attribute adxrs290_iio_ch_attr_3db_lpf_freq_val = {
	.name = "filter_low_pass_3db_frequency",
	.show = get_adxrs290_iio_ch_lpf,
	.store = set_adxrs290_iio_ch_lpf
};

static struct iio_attribute adxrs290_iio_ch_attr_raw = {
	.name = "raw",
	.show = get_adxrs290_iio_ch_raw,
	.store = NULL
};

static struct iio_attribute adxrs290_iio_ch_attr_scale = {
	.name = "scale",
	.show = get_adxrs290_iio_ch_scale,
	.store = NULL
};

static struct iio_attribute *adxrs290_iio_vel_attrs[] = {
	&adxrs290_iio_ch_attr_3db_hpf_freq_val,
	&adxrs290_iio_ch_attr_3db_lpf_freq_val,
	&adxrs290_iio_ch_attr_raw,
	&adxrs290_iio_ch_attr_scale,
	NULL,
};

static struct iio_attribute *adxrs290_iio_temp_attrs[] = {
	&adxrs290_iio_ch_attr_raw,
	&adxrs290_iio_ch_attr_scale,
	NULL,
};

static struct iio_channel adxrs290_iio_channel_x = {
	.ch_type = IIO_ANGL_VEL,
	.modified=1,
	.channel2=IIO_MOD_X,
	.scan_index = 0,
	.scan_type = NULL,
	.attributes = adxrs290_iio_vel_attrs,
	.ch_out = false,
};

static struct iio_channel adxrs290_iio_channel_y = {
	.ch_type = IIO_ANGL_VEL,
	.modified=1,
	.channel2=IIO_MOD_Y,
	.scan_index = 1,
	.scan_type = NULL,
	.attributes = adxrs290_iio_vel_attrs,
	.ch_out = false,
};

static struct iio_channel adxrs290_iio_channel_temp = {
	.ch_type = IIO_TEMP,
	.scan_index = 2,
	.scan_type = NULL,
	.attributes = adxrs290_iio_temp_attrs,
	.ch_out = false,
};

static struct iio_channel *adxrs290_iio_channels[] = {
	&adxrs290_iio_channel_x,
	&adxrs290_iio_channel_y,
	&adxrs290_iio_channel_temp,
	NULL,
};

//extern struct iio_device adxrs290_iio_descriptor ;
struct iio_device adxrs290_iio_descriptor = {
	.num_ch = 3,
	.channels = adxrs290_iio_channels,
	.attributes = NULL,
	.debug_attributes = NULL,
	.buffer_attributes = NULL,
	.transfer_dev_to_mem = NULL,
	.transfer_mem_to_dev = NULL,
	.read_data = NULL,
	.write_data = NULL,
	.debug_reg_read = (int32_t (*)())adxrs290_reg_read,
	.debug_reg_write = (int32_t (*)())adxrs290_reg_write,
};

#endif
