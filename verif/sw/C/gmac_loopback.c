/*
 * Copyright (c) 1999-2001 Tony Givargis.  Permission to copy is granted
 * provided that this header remains intact.  This software is provided
 * with no warranties.
 *
 * Version : 2.9
 */

/*---------------------------------------------------------------------------*/

#include <8051.h>

char cErrCnt;
/*---------------------------------------------------------------------------*/

__xdata __at (0xA030) unsigned int read_data;
__xdata unsigned int *rx_des_base;
__xdata unsigned int *tx_des_base;

void main() {
    
    unsigned int cFrameCnt = 0;
    unsigned int desc_ptr   =0;

    while(1) {
       if((read_data & 0xF) != 0) { // Check the Rx Q Counter
          // Read the Receive Descriptor
          // tb_top.cpu_read('h4,{desc_rx_qbase,desc_ptr},read_data); 
          // Write the Tx Descriptor
          rx_des_base = (__xdata unsigned int *) 0x7000;
          tx_des_base = (__xdata unsigned int *) 0x7040;
          //rx_des_base = (__xdata unsigned int *) (0x7000+desc_ptr);
          //tx_des_base = (__xdata unsigned int *) (0x7040+desc_ptr);
          //__xdata (int *) (0x7040+desc_ptr) = __xdata (int *)(0x7000+desc_ptr);
          // tb_top.cpu_write('h4,{desc_tx_qbase,desc_ptr},read_data); 
          *tx_des_base = *rx_des_base;
          desc_ptr = desc_ptr+4;
          cFrameCnt  = cFrameCnt+1;
         }
    }
}