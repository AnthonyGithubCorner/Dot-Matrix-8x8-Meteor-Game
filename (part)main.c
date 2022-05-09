//Was written for ECE 198, all code below was fully written by Anthony Lazar and ...
#ifdef MATRIX_GAME
    
    max_init(); //Initializes the MAX7219 Dot Matrix display.

    uint8_t display[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//Initializes all rows to have no meteors
   
    // for (int i=1;i<9;i++){

    //             write_max(i,display[0][i-1]); //Sends the data for A to functions which will relay the data to the display.
    //         }
    
    
    // while (true){
    //     for (int j=1; j<6;j++){
    //         int counter = 0;
    //         for (int i=1;i<9;i++){
    //             write_max(i,display[j-1][i-1]); //Sends the data for A to functions which will relay the data to the display.
    //             ++counter;
    //         }
    //         HAL_Delay(250);
    //     }
    // }
    
    uint8_t player = 0x08;
    int counter = 0;
    int color = 1;
    HAL_GPIO_WritePin(GPIOA, blue_pin, color & 0x01);  // blue  (hex 1 == 0001 binary)
    HAL_GPIO_WritePin(GPIOA, green_pin, color & 0x02);  // green (hex 2 == 0010 binary)
    HAL_GPIO_WritePin(GPIOA, red_pin, color & 0x04);  // red   (hex 4 == 0100 binary)'

    int speed = 75;
    while (1){
        //char mystr[10];

        // sprintf(mystr, "%d", player); 
        // SerialPuts(mystr);
        // SerialPuts("!\n");
        if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) && player < 0x80){
            player = player << 1;
            SerialPuts("    TO the left    !\n");
            HAL_Delay(30);
        }
        if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) && player > 0x01){
            player = player >> 1;
            SerialPuts("    TO the right   !\n");
            HAL_Delay(30);
        }
        //write_max(8,player);
        srand(HAL_GetTick());
        int spawn = rand() % 254; //random number between 0 and 0xFE where a 1 in the binary is meteor and 0 is hole for player to go through
        //SerialPuts(spawn);
        if ((counter % 2) == 0){
            spawn = 0x00;
        }
        SerialPuts("!\n");
        //display[8] = display[7];
        if ((counter % 5) == 0){
            display[7] = display[6];
            display[6] = display[5];
            display[5] = display[4];
            display[4] = display[3];
            display[3] = display[2];
            display[2] = display[1];
            display[1] = display[0];
            display[0] = spawn;
            
        }
        for (int i = 0; i<9; i++){
            if (i != 8){
                write_max(i, display[i-1]);
            }
            else{
                write_max(i, display[i-1] | player);
            }
        }
        if ((player & display[7]) > 0){
             SerialPuts("You Lose!");
             //HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
             break;
        }
        

        if (counter%100 == 0){
            // bottom three bits indicate which of the three LEDs should be on (eight possible combinations)
            HAL_GPIO_WritePin(GPIOA, blue_pin, color & 0x01);  // blue  (hex 1 == 0001 binary)
            HAL_GPIO_WritePin(GPIOA, green_pin, color & 0x02);  // green (hex 2 == 0010 binary)
            HAL_GPIO_WritePin(GPIOA, red_pin, color & 0x04);  // red   (hex 4 == 0100 binary)

           color++;

           if(color >= 8){
               color=7;
           }

           if(speed > 40){
                speed-=5;
           }
        }

        ++counter;
        HAL_Delay(speed);
        //SerialPuts(counter);
    
        // int counter = 0;
        // if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)){
        //     counter++;
        //     HAL_Delay(100);
        // }
        // else{
        //     for (int i=1; i<9; i++){
        //         write_max(i,display[counter][i-1]);
        //     }
        // }
        // if (counter > 4){
        //     counter = 0;
        // }
    }    
#endif
