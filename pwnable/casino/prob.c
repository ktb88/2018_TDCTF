#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

struct Passport{
    unsigned int PassportNo;
    char nationality[0x10];
    char name[0xE4];
}typedef Passport;


struct Temp{
	int BetDice;	
	char buf[0x10];
	int bet;
	int dice1;
	int dice2;
}typedef Temp;

void init();
void banner();
void make_passport();
int read_str(char* buf, unsigned int size);
unsigned read_number(char* buf, unsigned int size);
void print_passport();
void menu();
void menu2();
void visit_cashier();
void buy_item();
void sell_item();
void change_item();
void insert_iteminfo(char **buf, int size);

Passport* MyPassport;
long Money;
long DiceSeed;
char* ItemType[0x3];
char** ItemSlot[0x10];

void banner(){
    puts("*******************************************************************************");
	puts(R"EOF(  _______         _____        _ _               _____          _             
 |__   __|       |  __ \      | | |             / ____|        (_)            
    | | ___ _ __ | |  | | ___ | | | __ _ _ __  | |     __ _ ___ _ _ __   ___  
    | |/ _ \ '_ \| |  | |/ _ \| | |/ _` | '__| | |    / _` / __| | '_ \ / _ \ 
    | |  __/ | | | |__| | (_) | | | (_| | |    | |___| (_| \__ \ | | | | (_) |
    |_|\___|_| |_|_____/ \___/|_|_|\__,_|_|     \_____\__,_|___/_|_| |_|\___/ 
                                                                              
                                                                              )EOF");
    puts("*******************************************************************************");	
};

void init(){
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    srand(time(NULL));
	int fd = open("/dev/random", O_RDONLY);
	read(fd, (char *)&DiceSeed, sizeof(int));
	close(fd);
	Money = 10;
	MyPassport = NULL;
	ItemType[0] = "Gold";
	ItemType[1] = "Silver";
	ItemType[2] = "Bronze";
	//alarm(10);
}

void make_passport(){
	if(MyPassport == NULL){
		puts("[!] You don't have Passport!");
		puts("I will make you a new passport. Enter your information.");
		MyPassport = (Passport *)malloc(sizeof(Passport));
	    MyPassport->PassportNo = (unsigned int)rand()^0xffffffff;
 
	}
    printf("What is your name?\n>> ");
    read_str(MyPassport->name, 0xE4);
    printf("Input your nationality. (ex. KR)\n>> ");
    read_str(MyPassport->nationality, 0x10);
    print_passport();
    puts("Ok! Here is your passport. Enjoy casino!\n");
    puts("");
}

void print_passport(){
    puts("");
    puts("------------------------------");
    printf("| *PASSPORT*      $%9u |\n", Money);
    puts("|                            |"); 
    printf("| Name : %19s |\n", MyPassport->name);
    puts("|                            |");
    printf("| Contry : %17s |\n", MyPassport->nationality);
    puts("|                            |");
    puts("| Passport No :   ********** |");
    puts("------------------------------");
}

int read_str(char* buf, unsigned int size){
    int i;
    for(i=0; i<size; i++){
        if( read(0, buf + i, 1) == -1){
            break;
        }
        if(buf[i] == '\n'){
            buf[i] = 0x00;
            break;
        }
    }
    *(buf+i) = 0x00;
}


unsigned int read_number(char* buf, unsigned int size){
    if(read(0, buf, size) == -1)
        exit(0);

    return atoi(buf);
}

void check_passport(){
    char buf[0x10] = {'\x00',};
    puts("[!] Wait! You look so young. May I see your passport?");
    if(MyPassport == NULL){
        make_passport();
        return ;
    }

    //print_passport();
    puts("Hmm.. Let me ask you a few questions.");
    printf("What is your passport number?\n>> ");
    if(MyPassport->PassportNo != read_number(buf, 0x10))
        exit(0);
}

void menu(){
    puts("===================");
	puts("   Casino Menu");
	puts("===================");
	puts("1. Play Blackjack");
    puts("2. Play Craps");
    puts("3. Visit Shop");
    puts("4. Change Passport");
    puts("5. Exit");
	printf(">> ");
}

void play_blackjack(){
	puts("\n\n+++++++++++++++++++");
	puts("  ♠♡ Blackjack ♣◇");
	puts("+++++++++++++++++++");
		

	char deal[0x10] = {0,};
	int bet;
	check_passport();
	printf("Money : $%d\n", Money);
	puts("How much do you want to bet?(1~10)\n>> ");
	bet = read_number(deal, 10);
	if(bet < 0 || bet > Money){
		puts("Invalid betting");
		return;
	}
	puts("Dealer : ♣J ♠A (Blackjack)");
	puts("You : ♠8 ♠7 (15)");
	puts("You lose..");
	Money -= bet;
}

void play_craps(){
	
	puts("\n\n+++++++++++++++++++");
	puts("  □ Craps □");
	puts("+++++++++++++++++++");
		
	Temp var;
	check_passport();
	
	printf("Money : $%d\n", Money);
	printf("How much do you want to bet?(1~10)\n>> ");
	var.bet = read_number(var.buf, 10);
	memset(var.buf, 0x00, 0x10);
	if(var.bet < 0 || var.bet > Money){
		puts("Invalid betting");
		return;
	}
	
	srand(DiceSeed);
	var.dice1 = rand();
	DiceSeed = var.dice1;
	var.dice1 = var.dice1 % 6 +1;
	var.dice2 = rand() % 6 +1;
	
	printf("Which number do you want to bet on?(2~12 not 7)\n>> ");	
	var.BetDice = read_number(var.buf, 0x20);

	if(var.BetDice< 0 || var.BetDice > 12 || var.BetDice == 7){
		puts("Invalid number");
		return;
	}

	printf("Dice : %d/%d (%d)\n",var.dice1, var.dice2, var.dice1 + var.dice2);

	if(var.dice1 + var.dice2 == 7){
		puts("You lose!..");
		Money -= var.bet;
		return;
	}else{
		if(var.dice1 + var.dice2 == var.BetDice){
			puts("You win!");
			Money += var.bet;
		}else{
			puts("Draw.. :-(");
		}
		return;
	}
	
	if(Money > 1000){
		puts("Dice : 3/4 (7)");
		puts("You lose!..");
		Money -= var.bet;
		return;
	}

}

void menu2(){
	puts("===================");
	puts("    Shop Menu");
	puts("===================");
	puts("1. Buy Item");
    puts("2. Chagne Item information");
    puts("3. Sell Item");
    puts("4. Back");
    printf(">> ");
}

void visit_cashier(){
    char choice[0x10] = {0,};
	while(1){
        menu2();
        switch(read_number(choice, 3)){
            case 1: buy_item(); break;
            case 2: change_item(); break;
            case 3: sell_item(); break;
            case 4: return;
            default : break;
        }
    }
}

void buy_item(){
	char buf[0x10];
	int size;
	printf("Money : $%d\n", Money);
	printf("How much will you pay?($30~$700)\n>> ");
	size = read_number(buf, 10);
	if(size < 30 || size > 700){
		puts("Invaild money");
		exit(0);
	}
	
	if(size > Money){
		puts("Not enough money");
		exit(0);
	}
	int idx;
	for(int i=0; i<0x10; i++){
		if(ItemSlot[i] == NULL){
			idx = i;
			break;
		}
		if(ItemSlot[0xF] != NULL){
			puts("Slot is full!");
			return;
		}
	}
	
	ItemSlot[idx] = (char **)malloc(size + 0x10);
	*(long **)ItemSlot[idx] = (long)ItemType[0]; 
	*(long **)(ItemSlot[idx] + 1) = (long)size;

	insert_iteminfo(ItemSlot[idx] + 0x2, size);
	printf("%s\n", *ItemSlot[idx]);
	return;
	Money -= size;
}

void insert_iteminfo(char **buf, int size){

	printf("Enter inforamtion of item\n>> ");
	read_str((char *)buf, size-1);

}

void list_itemslot(){

	for(int i=0; i<0x10; i++){
		if(ItemSlot[i] != NULL)
			printf("[%2d/16] %s %30s\n", i+1, *ItemSlot[i], ItemSlot[i] + 0x2);
		else
			printf("[%2d/16] Empty\n", i+1);
	}
}

void change_item(){

	char buf[0x10];
	list_itemslot();
	printf("Which item do you want to modify?\n>> ");
	int choice = read_number(buf, 10);
	if(choice < 1 || choice > 16){
		puts("Invaild Index");
		return;
	}
	if(ItemSlot[choice-1] == NULL){
		puts("Invaild Index");
		return;
	}

	insert_iteminfo(ItemSlot[choice-1] + 0x2, (int)(ItemSlot[choice-1] + 0x1));
	
	return;
}

void sell_item(){
	list_itemslot();
	char buf[0x10];
	printf("Which item do you want to sell?\n>> ");
	int choice = read_number(buf, 10);
	if(choice < 1 || choice > 16){
		puts("Invaild Index");
		return;
	}
	if(ItemSlot[choice-1] == NULL){
		puts("Invaild Slot");
		return;
	}
	
	free(ItemSlot[choice-1]);
	ItemSlot[choice-1] = NULL;

	return;
}

int main(){
    char choice[0x10] = {0,};
    
    init();
    banner();
    make_passport();
    while(1){
        menu();
        switch(read_number(choice, 3)){
            case 1: play_blackjack(); break;
            case 2: play_craps(); break;
            case 3: visit_cashier(); break;
            case 4: make_passport(); break;
			case 5: puts("Bye!"); exit(0); break;
	        default : break;
        }
    }
        
}
