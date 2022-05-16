#include<stdio.h>
#include<stdlib.h>

#define SIZE 8 


//data of the car
typedef struct 
{
  int id;
  int typeCar;
  int typeService; 
  float hours; 

}Car; 

//data of the queue
typedef struct 
{
	int head, end; 
	float hours;
	Car array[SIZE];
}Queue; 

//prototype of functions

Queue *new();  
int empty(Queue *q); 
int full(Queue *q); 
void enqueue(Queue *q, Car x); 
Car dequeue(Queue *q); 
void show(Queue *q); 
void waitInd(Queue *q1, Queue *q2, Queue *q3, Queue *q4); 
void waitForType(Queue *q); 


int main()
{
  	Car x;
	int cond, answer, answerRemove, answerShow, answerView; //get the answers

	//creation of queues for each type of service
	Queue *oilChange = new();
	Queue *alignment = new();
	Queue *balancing = new(); 
	Queue *tireChange = new();
	
	
	printf("\nDigite 0 para iniciar:\n");
	scanf("%d",&cond);
	while(cond == 0)
	{
		printf("\nO que você deseja fazer:\n1)Adicionar um carro\n2)Remover um carro da fila\n");
		printf("3)Imprimir uma fila de serviço\n4)Visualizar carros em espera INDEPENDENTE DO SERVIÇO\n");
		printf("5)Visualizar carros em espera POR TIPO DE SERVIÇO\n");
		scanf("%d",&answer);
		if (answer == 1) //chose add a car to queue 
		{
			printf("\nDigite o número da ordem do seu serviço:\n");
			scanf("%d",&x.id); 
			printf("\nDigite o tipo do seu carro:\n\n1)Passeio\n2)Utilitário\n");
			scanf("%d",&x.typeCar); 
			printf("\nDigite o tipo de serviço que você deseja fazer:\n\n1)Troca de Oléo\n");
			printf("2)Alinhamento\n3)Balanceamento\n4)Troca de Pneus\n");
			scanf("%d",&x.typeService); 
			if (x.typeService == 1)//chose oil change 
			{
        		x.hours = 1.0; 
				enqueue(oilChange, x);
			}
			if (x.typeService == 2)//chose alignment
			{
        		if(x.typeCar == 1)//passenger car
        		{
          			x.hours = 0.5; 
          			enqueue(alignment, x);
          		}
        		else //utility car
        		{
          			x.hours = 1.0; 
					enqueue(alignment, x);
				}
			}
			if (x.typeService == 3)//chose balancing
			{
        		if(x.typeCar == 1)//passenger car
        		{
          			x.hours = 0.5;
					enqueue(balancing,x); 
				}
        		else //utility car
				{ 
          			x.hours = 1.0;
					enqueue(balancing,x);
				}
			}
			if (x.typeService == 4)//chose tire change
			{
        		x.hours = 0.5; 
				enqueue(tireChange, x); 
			}
		}
		if (answer == 2)//chose remove a car to queue
		{
			printf("\nEscolha o serviço do qual você quer REMOVER um carro:\n1)Troca de Oléo\n");
			printf("2)Alinhamento\n3)Balanceamento\n4)Troca de Pneus\n");
			scanf("%d",&answerRemove);
			if (answerRemove == 1)//chose oil change 
				dequeue(oilChange);
			if (answerRemove == 2)//chose alignment
				dequeue(alignment);
			if (answerRemove == 3)//chose balancing
				dequeue(balancing);
			if (answerRemove == 4)//chose tire change
				dequeue(tireChange); 
		}
		if (answer == 3)//chose display a queue
		{
			printf("\nEscolha o serviço do qual você deseja IMPRIMIR:\n1)Troca de Oléo\n2)alignment\n3)balancing\n4)Troca de Pneus\n");
			scanf("%d",&answerShow);
			if (answerShow == 1)//chose oil change
				show(oilChange);
			if (answerShow == 2)//chose alignment
				show(alignment);
			if (answerShow == 3)//chose balancing
				show(balancing);
			if (answerShow == 4)//chose tire change
				show(tireChange);
		}
		if (answer == 4)//chose see the wait independent of type of service
			waitInd(oilChange, alignment, balancing, tireChange);

		if (answer == 5)//chose see the wait for type of service
		{
			printf("\nEscolha o serviço do qual você quer visualizar:\n1)Troca de Oléo\n");
			printf("2)Alinhamento\n3)Balanceamento\n4)Troca de Pneus\n");
			scanf("%d",&answerView);
			if (answerView == 1)//chose see the wait from oil change
				waitForType(oilChange);
			if (answerView == 2)//chose see the wait from alignment
				waitForType(alignment);
			if (answerView == 3)//chose see the wait from balancing
				waitForType(balancing);
			if (answerView == 4)//chose see the wait from tire change
				waitForType(tireChange);
		}
			
		printf("\nDigite 0 para continuar:\n"); 
		scanf("%d",&cond);
	}	
	return 0; 
}

Queue *new()//create a new queue
{
	Queue *q = (Queue *) malloc(sizeof(Queue)); 
	q->head = 0; 
	q->end = 0;                            
}

int empty(Queue *q)//check if the queue it's empty
{
	return q->head == q->end;
}


int full(Queue *q)//check if the queue it's full
{
	return q->end - q->head == SIZE;
}

void enqueue(Queue *q, Car x)//add a car to queue 
{
	int i; 
	float sum = 0.0; 
	if (full(q))
		printf("\nFila cheia! Sinto muito, volte depois.\n");
	else
	{
		q->array[q->end % SIZE] = x;  
		q->end++;  
		printf("\nCarro Adicionado à fila!\n");
		for (i=q->head; i<q->end; i++)
			sum += q->array[i%SIZE].hours; 
		printf("\nSeu tempo máximo factível para a execução do serviço é de: %.2f hora(s)\n",sum); 
	}
}


Car dequeue(Queue *q)//remove a car to queue 
{
	Car aux;
	if (empty(q))
	{
		printf("\nEssa fila de serviço já está vazia. Não há o que remover!\n");
	}
	else
	{
		printf("\nCarro removido com sucesso!\n");
		aux = q->array[q->head % SIZE];
		q->head++;
		return aux;
	}
}



void show(Queue *q)//display a queue
{
	int i;
	if (empty(q))
		printf("\nEsta fila está vazia!\n");
	else
		printf("\nFila: \n");
	for (i=q->head; i<q->end; i++)
		printf("\n Carro de número -->   [%2d] ",q->array[i%SIZE].id);
	printf("\n");
}    

void waitInd(Queue *q1, Queue *q2, Queue *q3, Queue *q4)//show wait INDEPENDENT the type of service
{
	int a, b, c, d, passengerCars = 0, utilityCars = 0;  
	for (a=q1->head; a<q1->end; a++)//q1 represent oil change's queue
	{
		if (q1->array[a%SIZE].typeCar == 1)//means that type of the car is passenger
			passengerCars++;
		else //means that type of car is utility
			utilityCars++;
	}
	for (b=q2->head; b<q2->end; b++)//q2 represent alignment's queue
	{
		if (q2->array[b%SIZE].typeCar == 1)
			passengerCars++;
		else
			utilityCars++;
	}
	for (c=q3->head; c<q3->end; c++)//q3 represent balancing's queue
	{
		if (q3->array[c%SIZE].typeCar == 1)
			passengerCars++;
		else
			utilityCars++;
	}
	for (d=q4->head; d<q4->end; d++)//q4 represent tire change's queue
	{
		if (q4->array[d%SIZE].typeCar == 1)
			passengerCars++;
		else
			utilityCars++;
	}
	printf("\nHá %d carro(s) de passeio e %d carro(s) utilitários em espera independente do serviço\n",passengerCars,utilityCars); 
}

void waitForType(Queue *q)//show wait FOR type of service
{
	int i, passengerCars = 0, utilityCars = 0;    
	for (i=q->head; i<q->end; i++)//q represent the chosen queue
	{
		if (q->array[i%SIZE].typeCar == 1)//means that type of the car is passenger
			passengerCars++;
		else //means that type of the car is utility
			utilityCars++;
	}
	printf("\nHá %d carro(s) de passeio e %d carro(s) utilitários em espera nesta fila!\n",passengerCars,utilityCars);
}