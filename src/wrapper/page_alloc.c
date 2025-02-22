/* SPDX-License-Identifier: (GPL-2.0-only or LGPL-2.1-only)
 * wrapper/page_alloc.c
 *
 * wrapper around get_pfnblock_flags_mask and Ubuntu
 * get_pageblock_flags_mask. Using KALLSYMS to get their address when
 * available, else we need to have a kernel that exports this function
 * to GPL modules.
 *
 * Copyright (C) 2015 Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 */

#ifdef CONFIG_KALLSYMS

#include <linux/kallsyms.h>
#include <linux/mm_types.h>
#include <linux/module.h>
#include <wrapper/kallsyms.h>
#include <wrapper/page_alloc.h>

static
unsigned long (*get_pfnblock_flags_mask_sym)(struct page *page,
		unsigned long pfn,
		unsigned long end_bitidx,
		unsigned long mask);

unsigned long wrapper_get_pfnblock_flags_mask(struct page *page,
		unsigned long pfn,
		unsigned long end_bitidx,
		unsigned long mask)
{
	WARN_ON_ONCE(!get_pfnblock_flags_mask_sym);
	if (get_pfnblock_flags_mask_sym) {
		return get_pfnblock_flags_mask_sym(page, pfn, end_bitidx, mask);
	} else {
		return -ENOSYS;
	}
}
EXPORT_SYMBOL_GPL(wrapper_get_pfnblock_flags_mask);

int wrapper_get_pfnblock_flags_mask_init(void)
{
	get_pfnblock_flags_mask_sym =
		(void *) kallsyms_lookup_funcptr("get_pfnblock_flags_mask");
	if (!get_pfnblock_flags_mask_sym)
		return -1;
	return 0;
}
EXPORT_SYMBOL_GPL(wrapper_get_pfnblock_flags_mask_init);

/*
 * Canary function to check for 'get_pfnblock_flags_mask()' at compile time.
 *
 * From 'include/linux/pageblock-flags.h':
 *
 *   unsigned long get_pfnblock_flags_mask(struct page *page,
 *                                         unsigned long pfn,
 *                                         unsigned long end_bitidx,
 *                                         unsigned long mask);
 */
__attribute__((unused)) static
unsigned long __canary__get_pfnblock_flags_mask(struct page *page,
						unsigned long pfn,
						unsigned long end_bitidx,
						unsigned long mask)
{
	return get_pfnblock_flags_mask(page, pfn, end_bitidx, mask);
}

#else

#include <linux/pageblock-flags.h>

#endif
