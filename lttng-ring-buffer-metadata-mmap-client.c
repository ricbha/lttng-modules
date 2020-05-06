/* SPDX-License-Identifier: (GPL-2.0-only or LGPL-2.1-only)
 *
 * lttng-ring-buffer-metadata-client.c
 *
 * LTTng lib ring buffer metadta client.
 *
 * Copyright (C) 2010-2012 Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 */

#include <linux/module.h>
#include <lttng/tracer.h>

#define RING_BUFFER_MODE_TEMPLATE		RING_BUFFER_DISCARD
#define RING_BUFFER_MODE_TEMPLATE_STRING	"metadata-mmap"
#define RING_BUFFER_OUTPUT_TEMPLATE		RING_BUFFER_MMAP
#include "lttng-ring-buffer-metadata-client.h"
