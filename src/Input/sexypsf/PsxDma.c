/*  Pcsx - Pc Psx Emulator
 *  Copyright (C) 1999-2002  Pcsx Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "PsxCommon.h"

void psxDma4(u32 madr, u32 bcr, u32 chcr) { // SPU
	switch (chcr) {
		case 0x01000201: //cpu to spu transfer
		{
		 bcr= (bcr>>16) * (bcr&0xffff) * 2;

		 //printf("%08x, %08x\n",madr,bcr);
		 SPUwriteDMAMem(madr, bcr);		
		}
		break;
		case 0x01000200: //spu to cpu transfer
		{
		 //printf("%08x\n",madr);
	  	 SPUreadDMAMem (madr, (bcr >> 16) * (bcr & 0xffff) * 2);
		}
		break;
	}
}

void psxDma6(u32 madr, u32 bcr, u32 chcr) {
	u32 *mem = (u32 *)PSXM(madr);

#ifdef PSXDMA_LOG
	PSXDMA_LOG("*** DMA 6 - OT *** %lx addr = %lx size = %lx\n", chcr, madr, bcr);
#endif

	if (chcr == 0x11000002) {
		while (bcr--) {
			*mem-- = (madr - 4) & 0xffffff;
			madr -= 4;
		}
		mem++; *mem = 0xffffff;
	} else {
		// Unknown option
#ifdef PSXDMA_LOG
		PSXDMA_LOG("*** DMA 6 - OT unknown *** %lx addr = %lx size = %lx\n", chcr, madr, bcr);
#endif
	}
}
