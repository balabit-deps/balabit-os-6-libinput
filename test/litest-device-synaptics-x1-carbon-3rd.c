/*
 * Copyright © 2015 Red Hat, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "config.h"

#include "litest.h"
#include "litest-int.h"

static void
litest_synaptics_carbon3rd_setup(void)
{
	struct litest_device *d = litest_create_device(LITEST_SYNAPTICS_TRACKPOINT_BUTTONS);
	litest_set_current_device(d);
}

static struct input_event down[] = {
	{ .type = EV_ABS, .code = ABS_X, .value = LITEST_AUTO_ASSIGN  },
	{ .type = EV_ABS, .code = ABS_Y, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_PRESSURE, .value = LITEST_AUTO_ASSIGN  },
	{ .type = EV_ABS, .code = ABS_MT_SLOT, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_MT_TRACKING_ID, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_MT_POSITION_X, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_MT_POSITION_Y, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_MT_PRESSURE, .value = LITEST_AUTO_ASSIGN  },
	{ .type = EV_SYN, .code = SYN_REPORT, .value = 0 },
	{ .type = -1, .code = -1 },
};

static struct input_event move[] = {
	{ .type = EV_ABS, .code = ABS_MT_SLOT, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_X, .value = LITEST_AUTO_ASSIGN  },
	{ .type = EV_ABS, .code = ABS_Y, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_PRESSURE, .value = LITEST_AUTO_ASSIGN  },
	{ .type = EV_ABS, .code = ABS_MT_POSITION_X, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_MT_POSITION_Y, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_MT_PRESSURE, .value = LITEST_AUTO_ASSIGN  },
	{ .type = EV_SYN, .code = SYN_REPORT, .value = 0 },
	{ .type = -1, .code = -1 },
};

static int
get_axis_default(struct litest_device *d, unsigned int evcode, int32_t *value)
{
	switch (evcode) {
	case ABS_PRESSURE:
	case ABS_MT_PRESSURE:
		*value = 30;
		return 0;
	}
	return 1;
}

static struct litest_device_interface interface = {
	.touch_down_events = down,
	.touch_move_events = move,

	.get_axis_default = get_axis_default,
};

static struct input_id input_id = {
	.bustype = 0x11,
	.vendor = 0x2,
	.product = 0x7,
};

static int events[] = {
	EV_KEY, BTN_LEFT,
	EV_KEY, BTN_TOOL_FINGER,
	EV_KEY, BTN_TOOL_QUINTTAP,
	EV_KEY, BTN_TOUCH,
	EV_KEY, BTN_TOOL_DOUBLETAP,
	EV_KEY, BTN_TOOL_TRIPLETAP,
	EV_KEY, BTN_TOOL_QUADTAP,
	EV_KEY, BTN_0,
	EV_KEY, BTN_1,
	EV_KEY, BTN_2,
	INPUT_PROP_MAX, INPUT_PROP_POINTER,
	INPUT_PROP_MAX, INPUT_PROP_BUTTONPAD,
	-1, -1,
};

static struct input_absinfo absinfo[] = {
	{ ABS_X, 1266, 5676, 0, 0, 45 },
	{ ABS_Y, 1096, 4758, 0, 0, 68 },
	{ ABS_PRESSURE, 0, 255, 0, 0, 0 },
	{ ABS_TOOL_WIDTH, 0, 15, 0, 0, 0 },
	{ ABS_MT_SLOT, 0, 1, 0, 0, 0 },
	{ ABS_MT_POSITION_X, 1266, 5676, 0, 0, 45 },
	{ ABS_MT_POSITION_Y, 1096, 4758, 0, 0, 68 },
	{ ABS_MT_TRACKING_ID, 0, 65535, 0, 0, 0 },
	{ ABS_MT_PRESSURE, 0, 255, 0, 0, 0 },
	{ .value = -1 }
};

static const char udev_rule[] =
"ACTION==\"remove\", GOTO=\"touchpad_end\"\n"
"KERNEL!=\"event*\", GOTO=\"touchpad_end\"\n"
"ENV{ID_INPUT_TOUCHPAD}==\"\", GOTO=\"touchpad_end\"\n"
"\n"
"ATTRS{name}==\"litest SynPS/2 Synaptics TouchPad X1C3rd\","
"    ENV{LIBINPUT_MODEL_LENOVO_T450_TOUCHPAD}=\"1\"\n"
"\n"
"LABEL=\"touchpad_end\"";

struct litest_test_device litest_synaptics_carbon3rd_device = {
	.type = LITEST_SYNAPTICS_TRACKPOINT_BUTTONS,
	.features = LITEST_TOUCHPAD | LITEST_CLICKPAD | LITEST_BUTTON,
	.shortname = "synaptics carbon3rd",
	.setup = litest_synaptics_carbon3rd_setup,
	.interface = &interface,

	.name = "SynPS/2 Synaptics TouchPad X1C3rd",
	.id = &input_id,
	.events = events,
	.absinfo = absinfo,
	.udev_rule = udev_rule,
};
