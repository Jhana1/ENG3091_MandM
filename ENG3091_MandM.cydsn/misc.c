/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
/*

    int record = 0;
    int N = 50;
    int32 posxa[N];
    int32 posya[N];
    int32 posxb[N];
    int32 posyb[N];
    int idx = 0;
    extern volatile int32 loc_x_a;
    extern volatile int32 loc_y_a;
    extern volatile int32 loc_x_b;
    extern volatile int32 loc_y_b;
    extern volatile uint8 data_ready_a;
 
        if (record && (data_ready_a > 2)){
            if (idx < N){
                posxa[idx] = loc_x_a;
                posya[idx] = loc_y_a;
                posxb[idx] = loc_x_b;
                posyb[idx] = loc_y_b;
                loc_x_a = 0;
                loc_y_a = 0;
                loc_x_b = 0;
                loc_y_b = 0;
                data_ready_a = 0;
                idx++;
            } else {
                setCoast(0x3);
                stop_mice();
                USB_Start(0,USB_DWR_VDDD_OPERATION);
                LCD_PosPrintString(0,0,"READY!!!!");
                CyDelay(5000);
                LCD_PosPrintString(0,0,"SENDING...");
                print("START\n");
                
                for (idx = 0; idx < N; idx++){
                    print("%ld %ld %ld %ld\n", posxa[idx],posya[idx + 1],posxb[idx+2], posyb[idx+3]);
                }
                print("STOP\n");
                LCD_PosPrintString(0,0,"SENT!\n");
                record = 0;
            }
        }
       */

/* [] END OF FILE */
