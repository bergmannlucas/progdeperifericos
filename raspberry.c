#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>

#define DIRECTION_MAX 35
#define VALUE_MAX 30
#define BUFFER_MAX 3

#define IN  0
#define OUT 1

#define LOW  0
#define HIGH 1

#define QUANTIDADE_PADROES qtdPadroes
#define PADRAO_INICIAL 'A'

int qtdPadroes = 2;

char padrao_atual = PADRAO_INICIAL;
int contador = 0;
int vezes_padroes[16];

int config_serial(char * device, unsigned int baudrate) {
	struct termios options;
	int fd;

	fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY );
	if (fd < 0) {
		//Could not open the port.
		perror("config_serial: Não pode abrir a serial - ");
		return -1;
	}

	fcntl(fd, F_SETFL, 0);

	//Get the current options for the port...
	tcgetattr(fd, &options);

	//Sets the terminal to something like the "raw" mode
	cfmakeraw(&options);

	//Set the baudrate...
	cfsetispeed(&options, baudrate);
	cfsetospeed(&options, baudrate);

	//Enable the receiver and set local mode...
	options.c_cflag |= (CLOCAL | CREAD);

	//No parit, 1 stop bit, size 8
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;

	//Clear old settings
	options.c_cflag &= ~CRTSCTS;
	options.c_iflag &= ~(IXON | IXOFF | IXANY);

	//non-caninical mode
	options.c_lflag &= ~ICANON; 

	//Set the new options for the port...
	tcsetattr(fd, TCSANOW, &options);

	//configura a tty para escritas e leituras não bloqueantes
	//fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);

	return fd;
}

static int GPIOExport(int pin) {

	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;

	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open export for writing!\n");
		return(-1);
	}

	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
}

static int GPIOUnexport(int pin) {
	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;

	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open unexport for writing!\n");
		return(-1);
	}

	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
}

static int GPIODirection(int pin, int dir) {
	static const char s_directions_str[]  = "in\0out";

	char path[DIRECTION_MAX];
	int fd;

	snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio direction for writing!\n");
		return(-1);
	}

	if (-1 == write(fd, &s_directions_str[IN == dir ? 0 : 3], IN == dir ? 2 : 3)) {
		fprintf(stderr, "Failed to set direction!\n");
		return(-1);
	}

	close(fd);
	return(0);
}

static int GPIORead(int pin) {
	char path[VALUE_MAX];
	char value_str[3];
	int fd;

	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_RDONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio value for reading!\n");
		return(-1);
	}

	if (-1 == read(fd, value_str, 3)) {
		fprintf(stderr, "Failed to read value!\n");
		return(-1);
	}

	close(fd);

	return(atoi(value_str));
}

static int GPIOWrite(int pin, int value) {
	static const char s_values_str[] = "01";

	char path[VALUE_MAX];
	int fd;

	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio value for writing!\n");
		return(-1);
	}

	if (1 != write(fd, &s_values_str[LOW == value ? 0 : 1], 1)) {
		fprintf(stderr, "Failed to write value!\n");
		return(-1);
	}

	close(fd);
	return(0);
}

void escrever_padrao() {
	int fd;

	fd = config_serial((char*) "/dev/ttyAMA0", B9600);

	if(fd < 0) {
		printf("ERRO AO TENTAR ESCREVER NO SERIAL!!!\n");

		return;
	}

	//printf("PADRAO ATUAL = %c\n", padrao_atual);

	write(fd, &padrao_atual, 1);
}

void escrever_padrao_comparametro(char padrao) {
	int fd;

	fd = config_serial((char*) "/dev/ttyAMA0", B9600);

	if(fd < 0) {
		printf("ERRO AO TENTAR ESCREVER NO SERIAL!!!\n");

		return;
	}

	//printf("PADRAO ATUAL = %c\n", padrao);

	write(fd, &padrao, 1);
}

void proximo_padrao() {
	if(contador < (QUANTIDADE_PADROES - 1)) {
		padrao_atual++;
		contador++;
	} else { 
		padrao_atual = PADRAO_INICIAL;
		contador = 0;
	}

	printf("PADRAO ATUAL = %c\n", padrao_atual);
	//printf("Aperte S3 para confirmar!\n");
}

void padrao_anterior() {
	if(contador > 0) {
		padrao_atual--;
		contador--;
	} else {
		padrao_atual = PADRAO_INICIAL + QUANTIDADE_PADROES - 1;
		contador = QUANTIDADE_PADROES - 1;
	}

	printf("PADRAO ATUAL = %c\n", padrao_atual);
	//printf("Aperte S3 para confirmar!\n");
}

void escreve_padrao_comnumero(int padrao){
	if(padrao == 2) {
		escrever_padrao_comparametro('C');
	} else if(padrao == 3) {
		escrever_padrao_comparametro('D');
	}
	else if(padrao == 4) {
		escrever_padrao_comparametro('E');
	}
	else if(padrao == 5) {
		escrever_padrao_comparametro('F');
	}
	else if(padrao == 6) {
		escrever_padrao_comparametro('G');
	}
	else if(padrao == 7) {
		escrever_padrao_comparametro('H');
	}
	else if(padrao == 8) {
		escrever_padrao_comparametro('I');
	}
	else if(padrao == 9) {
		escrever_padrao_comparametro('J');
	}
	else if(padrao == 10) {
		escrever_padrao_comparametro('K');
	}
	else if(padrao == 11) {
		escrever_padrao_comparametro('L');
	}
	else if(padrao == 12) {
		escrever_padrao_comparametro('M');
	}
	else if(padrao == 13) {
		escrever_padrao_comparametro('N');
	}
	else if(padrao == 14) {
		escrever_padrao_comparametro('O');
	}
	else if(padrao == 15) {
		escrever_padrao_comparametro('P');
	}
}

void ler_mudancas_de_cada_padrao() {
	int fd;
	int i;

	fd = config_serial((char*) "/dev/ttyAMA0", B9600);

	if(fd < 0) {
		printf("ERRO AO TENTAR LER DO SERIAL!!!\n");

		return;
	}

	char valor = '0';

	write(fd, &valor, 1);	

	char padrao_aux = PADRAO_INICIAL;

	printf("MUDANCAS DE CADA PADRAO -> [");
	for(i=0; i<QUANTIDADE_PADROES; i++) {
		read(fd, &valor, 1);

		printf(" %c=%d ", padrao_aux, valor);
		padrao_aux++;
	}
	read(fd, &valor, 1);
	printf(" TOTAL=%d ", valor);
	printf("]\n");
}

int debounce(int btn){
	int val=0;
	do{
	  GPIODirection(btn, OUT);
	  GPIOWrite(btn, 1);
	  GPIODirection(btn, IN);
	  val=GPIORead(btn);
	}while(val==0);
}

void incrementa_index_array(char padrao){
	if(padrao == 'A') {
		vezes_padroes[0] += 1;
	} else if(padrao == 'B') {
		vezes_padroes[1] += 1;
	}
	else if(padrao == 'C') {
		vezes_padroes[2] += 1;
	}
	else if(padrao == 'D') {
		vezes_padroes[3] += 1;
	}
	else if(padrao == 'E') {
		vezes_padroes[4] += 1;
	}
	else if(padrao == 'F') {
		vezes_padroes[5] += 1;
	}
	else if(padrao == 'G') {
		vezes_padroes[6] += 1;
	}
	else if(padrao == 'H') {
		vezes_padroes[7] += 1;
	}
	else if(padrao == 'I') {
		vezes_padroes[8] += 1;
	}
	else if(padrao == 'J') {
		vezes_padroes[9] += 1;
	}
	else if(padrao == 'K') {
		vezes_padroes[10] += 1;
	}
	else if(padrao == 'L') {
		vezes_padroes[11] += 1;
	}
	else if(padrao == 'M') {
		vezes_padroes[12] += 1;
	}
	else if(padrao == 'N') {
		vezes_padroes[13] += 1;
	}
	else if(padrao == 'O') {
		vezes_padroes[14] += 1;
	}
	else if(padrao == 'P') {
		vezes_padroes[15] += 1;
	}
	else if(padrao == 'Q') {
		vezes_padroes[16] += 1;
	}
}

void printa_vezes_padroes() {
	int i;
	char padrao_atual2 = 'A';
	for(i=0; i < qtdPadroes; i++) {
		//vezes_padroes[i] = 0;
		printf("Padrão %c: %d\n", padrao_atual2, vezes_padroes[i]);		
		padrao_atual2++;
	}
}

void inicializa_array_vezes_padroes() {
	int i;
	for(i=0; i < qtdPadroes; i++) {
		vezes_padroes[i] = 0;
		//printf("Posição %d do array: %d\n", i, vezes_padroes[i]);
	}
}

int main(int argc, char *argv[]) 
{
	//S3
	int pushbutton25 = 25;
	//S2
	int pushbutton24 = 24;
	//S1
	int pushbutton23 = 23;

	bool apertous3 = false;

	//Enable GPIO pins
	GPIOExport(pushbutton25);
	GPIOExport(pushbutton24);
	GPIOExport(pushbutton23);

	while(1) {
		//Set GPIO directions
		if (-1 == GPIODirection(pushbutton25, OUT)) {
			return(2);
		}

		//Write GPIO value
		if (-1 == GPIOWrite(pushbutton25, 1)) {
			return(3);
		}

		//Set GPIO directions
		if (-1 == GPIODirection(pushbutton25, IN)) {
			return(2);
		}

		//23
		if (-1 == GPIODirection(pushbutton23, OUT)) {
			return(2);
		}
		if (-1 == GPIOWrite(pushbutton23, 1)) {
			return(3);
		}
		if (-1 == GPIODirection(pushbutton23, IN)) {
			return(2);
		}

		//24
		if (-1 == GPIODirection(pushbutton24, OUT)) {
			return(2);
		}
		if (-1 == GPIOWrite(pushbutton24, 1)) {
			return(3);
		}
		if (-1 == GPIODirection(pushbutton24, IN)) {
			return(2);
		}

		if(GPIORead(pushbutton23) == 0 && apertous3) {	
			printf("Saiu do modo de configuração!\n");
			debounce(pushbutton23);
			break;
		} else if(GPIORead(pushbutton23) == 0){
			//printf("passo 1 - 23\n");		
			printf("Aperte S3 novamente para confirmar a configuração!\n");	
			debounce(pushbutton23);
			apertous3 = true;
			escreve_padrao_comnumero(qtdPadroes);
		} else {
		 	if (GPIORead(pushbutton25) == 0) {
				//printf("passo 2 - 25\n");			
				debounce(pushbutton25);
				apertous3 = false;
				if (qtdPadroes < 16) {
					//printf("passo 3 - 25 / <16\n");			
					qtdPadroes++;
					//escreve_padrao_comnumero(qtdPadroes);
					printf("Quantidade de padrões: %d\n", qtdPadroes);
				}
			} else if (GPIORead(pushbutton24) == 0) {
				debounce(pushbutton24);
				//printf("passo 4 - 24\n");			
				apertous3 = false;
				if (qtdPadroes > 2) {
					qtdPadroes--;
					//escreve_padrao_comnumero(qtdPadroes);
					printf("Quantidade de padrões: %d\n", qtdPadroes);
				}
			}
			//usleep(500 * 1000);
		}
	}

	apertous3 = false;
	//printf("Entrando no proximo while\n")
	inicializa_array_vezes_padroes();
	printa_vezes_padroes();
	
	while(1) {
		//Set GPIO directions
		if (-1 == GPIODirection(pushbutton25, OUT)) {
			return(2);
		}

		//Write GPIO value
		if (-1 == GPIOWrite(pushbutton25, 1)) {
			return(3);
		}

		//Set GPIO directions
		if (-1 == GPIODirection(pushbutton25, IN)) {
			return(2);
		}

		//23
		if (-1 == GPIODirection(pushbutton23, OUT)) {
			return(2);
		}

		if (-1 == GPIOWrite(pushbutton23, 1)) {
			return(3);
		}
		if (-1 == GPIODirection(pushbutton23, IN)) {
			return(2);
		}

		//24
		if (-1 == GPIODirection(pushbutton24, OUT)) {
			return(2);
		}
		if (-1 == GPIOWrite(pushbutton24, 1)) {
			return(3);
		}
		if (-1 == GPIODirection(pushbutton24, IN)) {
			return(2);
		}

		//CHAMADA DE FUNCAO QUANDO UM BOTAO E PRESSIONADO
		/*
		if (GPIORead(pushbutton25) == 0)
		{
			printf("25\n");
			debounce(pushbutton25);
			proximo_padrao();
			apertous3 = false;
		}
		else if (GPIORead(pushbutton24) == 0)
		{
			printf("24\n");
			debounce(pushbutton24);
			padrao_anterior();
			apertous3 = false;
		}
		else if (GPIORead(pushbutton23) == 0 && apertous3) //confirmacao
		{	
			printf("23\n");
			debounce(pushbutton23);
			escrever_padrao();
			apertous3 = false;
		} else if(GPIORead(pushbutton23) == 0) {
			debounce(pushbutton23);
			apertous3 = true;
			ler_mudancas_de_cada_padrao();
		}
		*/

		if(GPIORead(pushbutton23) == 0 && apertous3) {	
			printf("Confirmou padrão\n");
			debounce(pushbutton23);
			incrementa_index_array(padrao_atual);
			printa_vezes_padroes();
			escrever_padrao();
			apertous3 = false;
		} else if(GPIORead(pushbutton23) == 0){
			printf("Aperte S3 novamente para confirmar o padrão!\n");			
			debounce(pushbutton23);
			apertous3 = true;
		} else {
		 	if (GPIORead(pushbutton25) == 0) {
				//printf("25\n");
				debounce(pushbutton25);
				proximo_padrao();
				apertous3 = false;
			} else if (GPIORead(pushbutton24) == 0) {
				//printf("24\n");
				debounce(pushbutton24);
				padrao_anterior();
				apertous3 = false;
			}
			//usleep(500 * 1000);
		}

		//Read GPIO value
		//usleep(500 * 1000);
	}
	

	//Disable GPIO pins
	if (-1 == GPIOUnexport(pushbutton25)) {
		return(4);
	}
	if (-1 == GPIOUnexport(pushbutton24)) {
		return(4);
	}
	if (-1 == GPIOUnexport(pushbutton23)) {
		return(4);
	}

	return(0);
}
