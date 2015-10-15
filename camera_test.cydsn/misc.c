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
        
        if (!isRotating() && !isDriving()){
            switch( state) {
                case S_READ_INSTRUCTIONS:
                    RED_Write(1);
                    BLUE_Write(0);
                    set_gain_exposure(1);
                    //capture_thresh_image();
                    //CyDelay(500);
                    //capture_thresh_image();
                    ///color_looking_for = nth_blob_colour(0);
                    color_looking_for = puck_plan[num_pucks];
                    if (color_looking_for == RED){
                        LCD_PosPrintString(0,0,"RED!!!");
                    } else if (color_looking_for == BLUE){
                        LCD_PosPrintString(0,0,"BLUE!!!");
                    } else if (color_looking_for == GREEN){
                        LCD_PosPrintString(0,0,"GREEN!!!");
                    }  else {
                        LCD_PosPrintString(0,0,"NOTHING");
                    }
                    CyDelay(500);
                    state = S_LEAVE_BASE;
                    break;
                case S_LEAVE_BASE:
                    go_backward(600, 255);
                    //setReverse(MBOTH);
                    //setSpeed(MBOTH, 255);
                    //CyDelay(600);
                    //setCoast(MBOTH);
                    state = S_FACE_CORRECT_DIR;
                    break;
                case S_FACE_CORRECT_DIR:
                    set_heading(180);
                    rotate_degrees(0);
                    state = S_GET_PUCK;
                    start_finding_time = time;
                    break;
                case S_GET_PUCK:
                    if (start_finding_time - time > 400000){
                        //sprintf(outString, "%lu", time);
                        //LCD_PosPrintString(0,0,outString);
                        //sprintf(outString, "%lu", start_finding_time - time);
                        //LCD_PosPrintString(1,0,outString);
                        //CyDelay(5000);
                        state = S_GO_HOME_WITHOUT_PUCK_ROTATE;
                        break;
                    }
                    CyDelay(500);
                    capture_thresh_image();
                    puck_heading = to_nearest_blob(color_looking_for, 30, 12);
                    if (puck_heading < -3){
                        rotate_degrees(10);
                    } else if (puck_heading > 3){
                        rotate_degrees(-10);
                    } else if (puck_heading == -1) {
                        if (cant_see_puck_forward++ < 3){
                            go_forward(500, 150)
                        } else if (cant_see_puck_left != 1){
                            rotate_degrees(-10);
                            cant_see_puck_left = 1;
                        } else if (cant_see_puck_right != 1){
                            rotate_degrees(10);
                            cant_see_puck_right = 1;
                        } else if (cant_see_puck_right == 1){
                            cant_see_puck_forward = 0;
                            cant_see_puck_left = 0;
                            cant_see_puck_right = 0;
                        }
                    } else {
                        go_forward(600, 150);
                        CyDelay(500);
                        if (ultra_distance < 18){
                            go_forward(800, 150);
                            CyDelay(300);
                            pickup_puck();
                            CyDelay(500);
                            state = S_FACE_HOME;
                            arm_set_level(1);
                            CyDelay(500);
                        }
                    }
                     break;
                case S_GO_HOME_WITHOUT_PUCK_ROTATE:
                    go_backward(1500, 150);
                    set_heading(0);
                    rotate_degrees(0);
                    state = S_GO_HOME_WITHOUT_PUCK;
                    rotate_begin_time = time;
                    break;
                case S_GO_HOME_WITHOUT_PUCK:
                    if (time - rotate_begin_time > 20000){
                        while (ultra_distance_2 > 20){
                    //TODO: the closer we get to home the slower we should drive and for less time
                     
                            go_forward(1000, 150); 
                        }
                        state = S_LEAVE_BASE; 
                    }
                    break;
                case S_FACE_HOME:
                    set_heading(0);
                
                    state = S_GO_HOME;
                    rotate_begin_time = time;
                    break;
                case S_GO_HOME:
                    if (time - rotate_begin_time > 50000){
                        while (ultra_distance_2 > 24){
                            setForward(MBOTH);
                            setSpeed(MBOTH, 100);
                            CyDelay(1000);
                            //setReverse(MBOTH);
                            //CyDelay(50);
                            setCoast(MBOTH);
                            CyDelay(200);
                            int k;
                            for (k = 0; k < 10; k++){
                                compass_read();
                                update_position();
                                control_motors();
                                CyDelay(100);
                            }
                        }
                        state = S_GOT_HOME;    
                    } else if (time - rotate_begin_time > 30000){
                        go_forward(1000, 100);
                    } else if ((time - rotate_begin_time) >= 25000){
                        capture_thresh_image();
                        puck_heading = to_nearest_blob(color_looking_for, 400, 12);
                        if (puck_heading != 0){
                            go_forward(1000, 100);
                            state = S_FACE_CORRECT_DIR;
                            drop_puck();
                        }
                    }
                    break;
                case S_GOT_HOME:
                    arm_set_level(0);
                    set_heading(90);
                    rotate_degrees(0);
                    got_home_time = time;
                    state = S_DROP_OFF_IN_WORKSPACE;
                    break;
                case S_DROP_OFF_IN_WORKSPACE:
                    if (time - got_home_time > 10000){
                        go_forward(1500, 100);
                        drop_puck();
                        num_pucks += 1;
                        if (num_pucks < 2){
                            go_backward(600, 100);
                            set_heading(0);
                            rotate_degrees(0);
                            CyDelay(600);
                            state = S_LEAVE_BASE;
                        } else {
                            state = S_HOLDING_PATTERN;
                        }
                    }
                    break;
                case S_HOLDING_PATTERN:
                    set_heading(90);
                    rotate_degrees(0);
                    go_backward(3000, 80);
                    CyDelay(15000);
                    while (1){
                        go_backward(3000, 80);
                        CyDelay(15000);
                        go_forward(3000, 80);
                        CyDelay(15000);
                    }
                    break;
            }
        }
        
        //Handle buttons
        if (but1_b){
            but1_b = 0;
            state = S_READ_INSTRUCTIONS;
            drop_puck();
            
        } else if (but0_b){
            but0_b = 0;
            
        }
        
        //image_stuff4();
        sprintf(outString, "P%d c%d hu%d", puck_heading, color_looking_for, ultra_distance_2);
        LCD_ClearDisplay();
        LCD_PosPrintString(0,0, outString);
        sprintf(outString, "u%d S%d", ultra_distance, state);
        LCD_PosPrintString(1,0, outString);
//        //Print some info to the screen
        if ((time % 10000) == 0){
        
            LCD_ClearDisplay();
            sprintf(outString, "%lu", time/10000);
        
            //sprintf(outString, "c%d d%ld y%ld", compass_heading, desired_distance, delta_y_distance);
            //LCD_PosPrintString(1,0,outString);
        }
    }*/

/* [] END OF FILE */
