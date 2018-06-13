// Lucas Bergmann e Ludgero Mascarenhas

int led3 = 9 ; //PB01 
int led4 = 10; //PB02
int led5 = 11; //PB03
int led6 = 12; //PB04
int led7 = 13; //PB05

char padrao_atual = 'A';
int quantidade_padroes = 16;
int mudancas_de_cada_padrao[16];
int mudancas_de_padrao = 0;
int valor_recebido = 0;

void setup() 
{     
    
	Serial.begin(9600);  
	pinMode(led3, OUTPUT);
	pinMode(led4, OUTPUT);     
	pinMode(led5, OUTPUT);     
	pinMode(led6, OUTPUT);     
	pinMode(led7, OUTPUT);     
	

	int i;
	for (i = 0; i < quantidade_padroes; i = i + 1) 
	{
		mudancas_de_cada_padrao[i] = 0;
	}
}

void padrao_a() // 0
{
	
	digitalWrite(led3, LOW);
	digitalWrite(led4, LOW);
	digitalWrite(led5, LOW);
	digitalWrite(led6, LOW);
	digitalWrite(led7, LOW);
	delay(1000);
	
}

void padraoInverso_a()
{
	digitalWrite(led3, HIGH);
	digitalWrite(led4, HIGH);
	digitalWrite(led5, HIGH);
	digitalWrite(led6, HIGH);
	digitalWrite(led7, HIGH);
	delay(1000);
}

void padrao_b() //1
{
	digitalWrite(led3, LOW);
	digitalWrite(led4, LOW);
	digitalWrite(led5, LOW);
	digitalWrite(led6, LOW);
	digitalWrite(led7, HIGH);
	delay(1000);
}

void padraoInverso_b()
{
	digitalWrite(led3, HIGH);
	digitalWrite(led4, HIGH);
	digitalWrite(led5, HIGH);
	digitalWrite(led6, HIGH);
	digitalWrite(led7, LOW);
	delay(1000);
}

void padrao_c() //2
{
	digitalWrite(led3, LOW);
	digitalWrite(led4, LOW);
	digitalWrite(led5, LOW);
	digitalWrite(led6, HIGH);
	digitalWrite(led7, LOW);
	delay(1000);
}

void padraoInverso_c()
{
	digitalWrite(led3, HIGH);
	digitalWrite(led4, HIGH);
	digitalWrite(led5, HIGH);
	digitalWrite(led6, LOW);
	digitalWrite(led7, HIGH);
	delay(1000);
}

void padrao_d() //3
{
	digitalWrite(led3, LOW);
	digitalWrite(led4, LOW);
	digitalWrite(led5, LOW);
	digitalWrite(led6, HIGH);
	digitalWrite(led7, HIGH);
	delay(1000);
}

void padraoInverso_d()
{
	digitalWrite(led3, HIGH);
	digitalWrite(led4, HIGH);
	digitalWrite(led5, HIGH);
	digitalWrite(led6, LOW);
	digitalWrite(led7, LOW);
	delay(1000);
}

void padrao_e() //4
{
	digitalWrite(led3, LOW);
	digitalWrite(led4, LOW);
	digitalWrite(led5, HIGH);
	digitalWrite(led6, LOW);
	digitalWrite(led7, LOW);
	delay(1000);
}

void padraoInverso_e()
{
	digitalWrite(led3, HIGH);
	digitalWrite(led4, HIGH);
	digitalWrite(led5, LOW);
	digitalWrite(led6, HIGH);
	digitalWrite(led7, HIGH);
	delay(1000);
}

void padrao_f() //5
{
	digitalWrite(led3, LOW);
	digitalWrite(led4, LOW);
	digitalWrite(led5, HIGH);
	digitalWrite(led6, LOW);
	digitalWrite(led7, HIGH);
	delay(1000);
}

void padraoInverso_f()
{
	digitalWrite(led3, HIGH);
	digitalWrite(led4, HIGH);
	digitalWrite(led5, LOW);
	digitalWrite(led6, HIGH);
	digitalWrite(led7, LOW);
	delay(1000);
}

void padrao_g() //6
{
	digitalWrite(led3, LOW);
	digitalWrite(led4, LOW);
	digitalWrite(led5, HIGH);
	digitalWrite(led6, HIGH);
	digitalWrite(led7, LOW);
	delay(1000);
}

void padraoInverso_g()
{
	digitalWrite(led3, HIGH);
	digitalWrite(led4, HIGH);
	digitalWrite(led5, LOW);
	digitalWrite(led6, LOW);
	digitalWrite(led7, HIGH);
	delay(1000);
}

void padrao_h() //7
{
	digitalWrite(led3, LOW);
	digitalWrite(led4, LOW);
	digitalWrite(led5, HIGH);
	digitalWrite(led6, HIGH);
	digitalWrite(led7, HIGH);
	delay(1000);
}

void padraoInverso_h()
{
	digitalWrite(led3, HIGH);
	digitalWrite(led4, HIGH);
	digitalWrite(led5, LOW);
	digitalWrite(led6, LOW);
	digitalWrite(led7, LOW);
	delay(1000);
}

void padrao_i() //8
{
	digitalWrite(led3, LOW);
	digitalWrite(led4, HIGH);
	digitalWrite(led5, LOW);
	digitalWrite(led6, LOW);
	digitalWrite(led7, LOW);
	delay(1000);
}

void padraoInverso_i()
{
	digitalWrite(led3, HIGH);
	digitalWrite(led4, LOW);
	digitalWrite(led5, HIGH);
	digitalWrite(led6, HIGH);
	digitalWrite(led7, HIGH);
	delay(1000);
}

void padrao_j() // 9
{
	digitalWrite(led3, LOW); 
	digitalWrite(led4, HIGH); //8
	digitalWrite(led5, LOW); //4
	digitalWrite(led6, LOW); //2
	digitalWrite(led7, HIGH); // 1
	delay(1000);
}

void padraoInverso_j()
{
	digitalWrite(led3, HIGH); 
	digitalWrite(led4, LOW); //8
	digitalWrite(led5, HIGH); //4
	digitalWrite(led6, HIGH); //2
	digitalWrite(led7, LOW); // 1
	delay(1000);
}

void padrao_k() // 10
{
	digitalWrite(led3, LOW); 
	digitalWrite(led4, HIGH); //8
	digitalWrite(led5, LOW); //4
	digitalWrite(led6, HIGH); //2
	digitalWrite(led7, LOW); // 1
	delay(1000);
}

void padraoInverso_k()
{
	digitalWrite(led3, HIGH); 
	digitalWrite(led4, LOW); //8
	digitalWrite(led5, HIGH); //4
	digitalWrite(led6, LOW); //2
	digitalWrite(led7, HIGH); // 1
	delay(1000);
}

void padrao_l() //11
{
	digitalWrite(led3, LOW); 
	digitalWrite(led4, HIGH); //8
	digitalWrite(led5, LOW); //4
	digitalWrite(led6, HIGH); //2
	digitalWrite(led7, HIGH); // 1
	delay(1000);
}

void padraoInverso_l()
{
	digitalWrite(led3, HIGH); 
	digitalWrite(led4, LOW); //8
	digitalWrite(led5, HIGH); //4
	digitalWrite(led6, LOW); //2
	digitalWrite(led7, LOW); // 1
	delay(1000);
}

void padrao_m()//12
{
	digitalWrite(led3, LOW); 
	digitalWrite(led4, HIGH); //8
	digitalWrite(led5, HIGH); //4
	digitalWrite(led6, LOW); //2
	digitalWrite(led7, LOW); // 1
	delay(1000);
}

void padraoInverso_m()
{
	digitalWrite(led3, HIGH); 
	digitalWrite(led4, LOW); //8
	digitalWrite(led5, LOW); //4
	digitalWrite(led6, HIGH); //2
	digitalWrite(led7, HIGH); // 1
	delay(1000);
}

void padrao_n()//13
{
	digitalWrite(led3, LOW); 
	digitalWrite(led4, HIGH); //8
	digitalWrite(led5, HIGH); //4
	digitalWrite(led6, LOW); //2
	digitalWrite(led7, HIGH); // 1
	delay(1000);
}

void padraoInverso_n()
{
	digitalWrite(led3, HIGH); 
	digitalWrite(led4, LOW); //8
	digitalWrite(led5, LOW); //4
	digitalWrite(led6, HIGH); //2
	digitalWrite(led7, LOW); // 1
	delay(1000);
}

void padrao_o()//14
{
	digitalWrite(led3, LOW); 
	digitalWrite(led4, HIGH); //8
	digitalWrite(led5, HIGH); //4
	digitalWrite(led6, HIGH); //2
	digitalWrite(led7, LOW); // 1
	delay(1000);
}

void padraoInverso_o()
{
	digitalWrite(led3, HIGH); 
	digitalWrite(led4, LOW); //8
	digitalWrite(led5, LOW); //4
	digitalWrite(led6, HIGH); //2
	digitalWrite(led7, LOW); // 1
	delay(1000);
}

void padrao_p()//15
{
	digitalWrite(led3, LOW); 
	digitalWrite(led4, HIGH); //8
	digitalWrite(led5, HIGH); //4
	digitalWrite(led6, HIGH); //2
	digitalWrite(led7, HIGH); // 1
	delay(1000);
}

void padraoInverso_p()
{
	digitalWrite(led3, HIGH); 
	digitalWrite(led4, LOW); //8
	digitalWrite(led5, LOW); //4
	digitalWrite(led6, LOW); //2
	digitalWrite(led7, LOW); // 1
	delay(1000);
}

void piscar_leds()
{
	if(padrao_atual == 'A')
	{
		padrao_a();
		padraoInverso_a();
	}
	else if(padrao_atual == 'B')
	{
		padrao_b();
		padraoInverso_b();
	}
	else if(padrao_atual == 'C')
	{
		padrao_c();
		padraoInverso_c();
	}
	else if(padrao_atual == 'D')
	{
		padrao_d();
		padraoInverso_d();
	}
	else if(padrao_atual == 'E')
	{
		padrao_e();
		padraoInverso_e();
	}
	else if(padrao_atual == 'F')
	{
		padrao_f();
		padraoInverso_f();
	}
	else if(padrao_atual == 'G')
	{
		padrao_g();
		padraoInverso_g();
	}
	else if(padrao_atual == 'H')
	{
		padrao_h();
		padraoInverso_h();
	}
	else if(padrao_atual == 'I')
	{
		padrao_i();
		padraoInverso_i();
	}
	else if(padrao_atual == 'J')
	{
		padrao_j();
		padraoInverso_j();
	}
	else if(padrao_atual == 'K')
	{
		padrao_k();
		padraoInverso_k();
	}
	else if(padrao_atual == 'L')
	{
		padrao_l();
		padraoInverso_l();
	}
	else if(padrao_atual == 'M')
	{
		padrao_m();
		padraoInverso_m();
	}
	else if(padrao_atual == 'N')
	{
		padrao_n();
		padraoInverso_n();
	}
	else if(padrao_atual == 'O')
	{
		padrao_o();
		padraoInverso_o();
	}
	else if(padrao_atual == 'P')
	{
		padrao_p();
		padraoInverso_p();
	}
}

void escrever_mudancas_de_cada_padrao()
{
	int i;
	for (i = 0; i < quantidade_padroes; i = i + 1) 
	{
		Serial.write(mudancas_de_cada_padrao[i]);
	} 

	Serial.write(mudancas_de_padrao);  
}

void loop() 
{
	if (Serial.available()) 
	{
		valor_recebido = Serial.read();

		if (valor_recebido > -1) 
		{
			if(valor_recebido == 'A')
			{
				padrao_atual = 'A';
				mudancas_de_cada_padrao[0] = mudancas_de_cada_padrao[0] + 1;
				mudancas_de_padrao = mudancas_de_padrao + 1;
			}	
			else if(valor_recebido == 'B')
			{
				padrao_atual = 'B';
				mudancas_de_cada_padrao[1] = mudancas_de_cada_padrao[1] + 1;
				mudancas_de_padrao = mudancas_de_padrao + 1;
			}
			else if(valor_recebido == 'C')
			{
				padrao_atual = 'C';
				mudancas_de_cada_padrao[2] = mudancas_de_cada_padrao[2] + 1;
				mudancas_de_padrao = mudancas_de_padrao + 1;
			}	
			else if(valor_recebido == 'D')
			{
				padrao_atual = 'D';
				mudancas_de_cada_padrao[3] = mudancas_de_cada_padrao[3] + 1;
				mudancas_de_padrao = mudancas_de_padrao + 1;
			}
			else if(valor_recebido == 'E')
			{
				padrao_atual = 'E';
				mudancas_de_cada_padrao[4] = mudancas_de_cada_padrao[4] + 1;
				mudancas_de_padrao = mudancas_de_padrao + 1;
			}
			else if(valor_recebido == 'F')
			{
				padrao_atual = 'F';
				mudancas_de_cada_padrao[5] = mudancas_de_cada_padrao[5] + 1;
				mudancas_de_padrao = mudancas_de_padrao + 1;
			}
			else if(valor_recebido == 'G')
			{
				padrao_atual = 'G';
				mudancas_de_cada_padrao[6] = mudancas_de_cada_padrao[6] + 1;
				mudancas_de_padrao = mudancas_de_padrao + 1;
			}
			else if(valor_recebido == 'H')
			{
				padrao_atual = 'H';
				mudancas_de_cada_padrao[7] = mudancas_de_cada_padrao[7] + 1;
				mudancas_de_padrao = mudancas_de_padrao + 1;
			}
			else if(valor_recebido == 'I')
			{
				padrao_atual = 'I';
				mudancas_de_cada_padrao[8] = mudancas_de_cada_padrao[8] + 1;
				mudancas_de_padrao = mudancas_de_padrao + 1;
			}
			else if(valor_recebido == 'J')
			{
				padrao_atual = 'J';
				mudancas_de_cada_padrao[9] = mudancas_de_cada_padrao[9] + 1;
				mudancas_de_padrao = mudancas_de_padrao + 1;
			}
			else if(valor_recebido == 'K')
			{
				padrao_atual = 'K';
				mudancas_de_cada_padrao[10] = mudancas_de_cada_padrao[10] + 1;
				mudancas_de_padrao = mudancas_de_padrao + 1;
			}
			else if(valor_recebido == 'L')
			{
				padrao_atual = 'L';
				mudancas_de_cada_padrao[11] = mudancas_de_cada_padrao[11] + 1;
				mudancas_de_padrao = mudancas_de_padrao + 1;
			}
			else if(valor_recebido == 'M')
			{
				padrao_atual = 'M';
				mudancas_de_cada_padrao[12] = mudancas_de_cada_padrao[12] + 1;
				mudancas_de_padrao = mudancas_de_padrao + 1;
			}
			else if(valor_recebido == 'N')
			{
				padrao_atual = 'N';
				mudancas_de_cada_padrao[13] = mudancas_de_cada_padrao[13] + 1;
				mudancas_de_padrao = mudancas_de_padrao + 1;
			}
			else if(valor_recebido == 'O')
			{
				padrao_atual = 'O';
				mudancas_de_cada_padrao[14] = mudancas_de_cada_padrao[14] + 1;
				mudancas_de_padrao = mudancas_de_padrao + 1;
			}
			else if(valor_recebido == 'P')
			{
				padrao_atual = 'P';
				mudancas_de_cada_padrao[15] = mudancas_de_cada_padrao[15] + 1;
				mudancas_de_padrao = mudancas_de_padrao + 1;
			}
			else if(valor_recebido == '0')
			{
				escrever_mudancas_de_cada_padrao();
			}
		}
	}
	else
	{
		piscar_leds();
	}
}
