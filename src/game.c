#include "game.h"
#include "io.h"

int health = 1;

//menu display
void show_menu() {
    uart_puts("\r\nWelcome to Wonderland OS!\r\n");
    uart_puts("Commands:\r\n");
    uart_puts(" - play: Start the game\r\n");
    uart_puts(" - about: About this OS\r\n");
    uart_puts(" - credits: See who made this\r\n");
}

//handles commands
void handle_command(char **commands_arr) {
    if (commands_arr[0] == 0 || strcmp(commands_arr[0], "quit") == 0 || strcmp(commands_arr[0], "Quit")==0) return;

    if (strcmp(commands_arr[0], "play") == 0) {
        clear_screen();
        game_loop();
        clear_screen();
        show_menu();
    } else if (strcmp(commands_arr[0], "about") == 0) {
        uart_puts_slow("\r\nWonderland OS was created for an Operating Systems class at Smith College.\r\n");
    } else if (strcmp(commands_arr[0], "credits") == 0) {
        uart_puts_slow("\r\nCreated by Lily Garner and Liberty Lehr.\r\n");
    } else if(strcmp(commands_arr[0], "drink") == 0){
        if(strcmp(commands_arr[1], "tea") == 0){
            uart_puts_slow("\r\nMmmm, tea. (+1 Health)");
            health++;
        } else if(strcmp(commands_arr[1], "milk") == 0){
            uart_puts_slow("\r\nI can see your bones getting stronger! (+5 Health)");
            health = health+5;
        } else{
            uart_puts_slow("\r\nDrink what?");
        }
    } else if(strcmp(commands_arr[0], "eat") == 0){
        if(strcmp(commands_arr[1], "scone") == 0){
            uart_puts_slow("\r\nYummy, scone. (+10 Health)");
            health = health+10;
        } else{
            uart_puts_slow("\r\nEat what?");
        }
    } else if(strcmp(commands_arr[0], "check") == 0){
        if(strcmp(commands_arr[1], "health") == 0){
            uart_puts_slow("\r\nHealth: ");
            uart_puts_slow(int_to_string(health));
        } else{
            uart_puts_slow("\r\nCheck what?");
        }
    } else if(strcmp(commands_arr[0], "help") == 0){
        uart_puts("\r\nHello Alice...\r\n");
        uart_puts("Some commands to try:\r\n");
        uart_puts(" - drink\r\n");
        uart_puts(" - eat\r\n");
        uart_puts(" - check health\r\n");
        uart_puts("\r\nRemember to be specific!\r\n");
    } else {
        uart_puts_slow("\r\nUnknown command. Please try again.\r\n");
    }
}

//main game loop 
void game_loop() {
    uart_puts_slow("To quit the game type 'quit' at any point.\r\n");
    uart_puts_slow("Hi Alice. Would you like to follow the rabbit?\r\nType 'y' or 'n':\r\n> ");

    char buff[BUFSIZE];
    uart_gets(buff, sizeof(buff));

    if (strcmp(buff, "y") == 0 || strcmp(buff, "Y") == 0) {
        uart_puts_slow("\r\nLet's go!\r\n");
        uart_puts_slow("In an effort to avoid the plague of daily life you decide to take a walk by the pond. To your surprise you see a white rabbit reach into his waist coat pocket and pull out a pocket watch.");
        uart_puts_slow("\r\n    \"Excuse me Mr. Rabbit, may I ask...\", you call in confusion.");
        uart_puts_slow("\r\n    \"Can you not see I'm late!\", the rabbit proclaims as he hops away. A rabbit who talks, bizarre, you must go after him!");
        uart_puts_slow("\r\n    \"Wait for me Mr. Rabbit\", you call out as you chase him through the woods. As you round a bend you see the tip of his white tail disappear into a hole beneath some gnarly tree roots. Consumed by curiosity you go after him head first down the rabbit hole.");
        uart_puts_slow("\r\nThe tunnel goes straight down towards the center of the earth. At first you fall quickly, but soon physics wanes and you slow to a downward float.");
        uart_puts_slow("\r\nAs you fall a table floats by. You peer over to see a gingham table cloth set with tea, milk and a plate of scones. A small knife sticks out of a pot of jam.");
        delay(10000000);
        uart_puts_slow("\r\n\r\nOh no, you got injured falling down the hole!\r\n\r\n");
        uart_puts_slow("HEALTH: 1 \r\n\r\n");
        delay(10000000);
        uart_puts_slow("Try a simple command to interact with your surroundings. EX: 'drink tea', or 'help'\r\n");
        
        while (1) {
            uart_puts("\r\n> ");
            uart_gets(buff, BUFSIZE);
            char** commands_arr = read_args(buff);
            handle_command(commands_arr);
            if (strcmp(buff, "quit") == 0) {
                uart_puts_slow("\r\nQuitting...\r\n");
                break;
            }
        }

        uart_puts_slow("\r\nGame ended. Going to main menu, please wait...\r\n");
        delay(1000000000);

    } else if (strcmp(buff, "n") == 0 || strcmp(buff, "N") == 0) {
        uart_puts_slow("\r\nWell that's boring...Bye!\r\n");
        delay(1000000000);

    } else {
        uart_puts_slow("\r\nInvalid choice.\r\n");
    }
}