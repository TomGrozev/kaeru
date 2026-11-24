//
// SPDX-FileCopyrightText: 2026 LibreEcho contributors
// SPDX-License-Identifier: AGPL-3.0-or-later
//

#include <board_ops.h>

#define BOARD_NAME "Echo Plus 2nd Gen"

// Amazon gates every unlock decision (boot, fastboot handlers) on the return
// value of this predicate. It reads the `unlock_code` idme record and returns
// 1 when the record is non-empty, so forcing 1 gives unrestricted fastboot.
//
// The stock LK entry is 0x41E0196C: `push {r4, lr}; sub sp, #0x100`, then a
// memset, then an idme read of the literal that resolves to "unlock_code". The
// string-offset table before it ends exactly at this address. The Echo Plus 2
// unlock kit uses 0x41E01968, which is the last dword of that table, not an
// entry point.
#define UNLOCK_CHECK_FUNC_ADDR 0x41E0196C

void board_early_init(void) {
    printf("Entering early init for %s\n", BOARD_NAME);
    FORCE_RETURN(UNLOCK_CHECK_FUNC_ADDR, 1);
}

void board_late_init(void) {
    printf("Entering late init for %s\n", BOARD_NAME);
}
