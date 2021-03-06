// Кодировка UTF-8 //

#include "cpu-init.h"

uint8_t TransitBuffer[DMA_BUFFER_SIZE]; // Транзитный буффер, для хранения временных данных, полученных с 
uint8_t UartBuffer[DMA_BUFFER_SIZE];

/////************************************************************************************************************************************/////

//Функция настройки портов контроллера
void gpio_init(void)
{	
	//Включаем тактирование портов
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

  //Создаём структуры для настройки портов
  GPIO_InitTypeDef gpio_porta_lcd;     //Создаём структуру для настройки порта "A" под LCD
	GPIO_InitTypeDef gpio_porta_usart1;  //Создаём структуру для настройки порта "A" для USART1 (GPS/Wi-Fi)
  GPIO_InitTypeDef gpio_portb_usart3;  //Создаём структуру для настройки порта "B" для USART3 (GSM)
  //GPIO_InitTypeDef gpio_portb_keys;    //Создаём структуру для настройки порта "B" под клавиатуру
	
  //Настраиваем ноги PA0 - РА4 для работы с LCD по программному SPI
  gpio_porta_lcd.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4); //Подключаем пины для работы с LCD
  gpio_porta_lcd.GPIO_Mode = GPIO_Mode_Out_PP;  //Задаём пинам порта ввода-вывода "А" режим работы с LCD
  gpio_porta_lcd.GPIO_Speed = GPIO_Speed_50MHz; //Задаём пинам порта ввода-вывода "А" скорость работы
  GPIO_Init(GPIOA, &gpio_porta_lcd);
	
	//Настраиваем ногу PA10 как вход USART1 (RxD)
  gpio_porta_usart1.GPIO_Pin   = GPIO_Pin_10;
  gpio_porta_usart1.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &gpio_porta_usart1);

  //Настраиваем ногу PA9 как выход USART1 (TxD)
  //Причем не просто выход, а выход с альтернативной функцией
  gpio_porta_usart1.GPIO_Pin   = GPIO_Pin_9;
  gpio_porta_usart1.GPIO_Speed = GPIO_Speed_50MHz;
  gpio_porta_usart1.GPIO_Mode  = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &gpio_porta_usart1);

  //Настраиваем ногу PB11 как вход USART3 (RxD)
  gpio_portb_usart3.GPIO_Pin   = GPIO_Pin_11;
  gpio_portb_usart3.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &gpio_portb_usart3);

  //Настраиваем ногу PB10 как выход USART3 (TxD)
  //Причем не просто выход, а выход с альтернативной функцией
  gpio_portb_usart3.GPIO_Pin   = GPIO_Pin_10;
  gpio_portb_usart3.GPIO_Speed = GPIO_Speed_50MHz;
  gpio_portb_usart3.GPIO_Mode  = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &gpio_portb_usart3);

  //Настраиваем ноги PB5 - РB9 для работы с клавиатурой (не по прерываниям)
//  gpio_portb_keys.GPIO_Pin = (GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9);
//  gpio_portb_keys.GPIO_Mode = GPIO_Mode_IPU;
//  gpio_portb_keys.GPIO_Speed = GPIO_Speed_10MHz;
//  GPIO_Init(GPIOB, &gpio_portb_keys);


}

/////************************************************************************************************************************************/////

//Функция настройки UART1
void uart1_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); // Включаем тактирование USART1
	
  //Заполняем структуру настройками 1-го UARTa
  USART_InitTypeDef uart1_struct;
  uart1_struct.USART_BaudRate            = 9600;
  uart1_struct.USART_WordLength          = USART_WordLength_8b;
  uart1_struct.USART_StopBits            = USART_StopBits_1;
  uart1_struct.USART_Parity              = USART_Parity_No ;
  uart1_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  uart1_struct.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;

  //Инициализируем UART
  USART_Init(USART1, &uart1_struct);
	
	//Активируем приём с последовательного порта по запросу DMA
  USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);

  //Включаем UART
  USART_Cmd(USART1, ENABLE);
}

/////************************************************************************************************************************************/////

//Функция настройки UART3
void uart3_init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);//НЕ ЗАБЫВАТЬ!!! USART3 тактируется от шины APB1
	
  //Заполняем структуру настройками 3-го UARTa
  USART_InitTypeDef uart3_struct;
  uart3_struct.USART_BaudRate            = 9600;
  uart3_struct.USART_WordLength          = USART_WordLength_8b;
  uart3_struct.USART_StopBits            = USART_StopBits_1;
  uart3_struct.USART_Parity              = USART_Parity_No ;
  uart3_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  uart3_struct.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;

  //Инициализируем UART
  USART_Init(USART3, &uart3_struct);
	
	//Активируем приём с последовательного порта по запросу DMA
  //USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);

  //Включаем UART
  USART_Cmd(USART3, ENABLE);
}

/////************************************************************************************************************************************/////

//Функция настройки DMA1
void dma1_init(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	// Включаем тактирование DMA1
	
  DMA_InitTypeDef dma;  //Создаём структуру для настройки DMA1
  //Заполняем структуру настройками DMA1
  DMA_StructInit(&dma);
  dma.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR);     // это адрес регистра данных USART3
  dma.DMA_MemoryBaseAddr = (uint32_t)&TransitBuffer[0];     // адрес нулевого элемента массива
  dma.DMA_DIR = DMA_DIR_PeripheralSRC;                      // принимаем данные с периферии
  dma.DMA_Mode = DMA_Mode_Circular;                         // Режим DMA - циклический
  dma.DMA_BufferSize = DMA_BUFFER_SIZE;                     // буфер – 16 байт (#define DMA_BUFFER_SIZE 16)
  dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        // перифериию не инкрементируем
  dma.DMA_MemoryInc = DMA_MemoryInc_Enable;                 // память инкрементируем
  dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // шлем байтами
  dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         // шлем байтами
	 
  //Инициализируем DMA1
  DMA_Init(DMA1_Channel5, &dma);	                          // Идем в таблицу с каналами – USART1_RX – 5 канал, все верно =)
	
  //Включаем прямой доступ к памяти DMA
  DMA_Cmd(DMA1_Channel5, ENABLE);	
}

void InitButton()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitTypeDefStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* GPIOB clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	/*Включили тактирование AFIO на шине APB2. Этот блок отвечает за внешние прерывания как AF*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	// Configure PB.5/6/7/8/9 as Input
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//Подключаем порт к прерыванию
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource6);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource7);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource8);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource9);

	EXTI_InitTypeDefStructure.EXTI_Line = EXTI_Line5 | EXTI_Line6 | EXTI_Line7 | EXTI_Line8 | EXTI_Line9;
	EXTI_InitTypeDefStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitTypeDefStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitTypeDefStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitTypeDefStructure);
	//EXTI_ClearITPendingBit(EXTI_Line5 | EXTI_Line6 | EXTI_Line7 | EXTI_Line8 | EXTI_Line9);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
};

void EXTI9_5_IRQHandler()
{
  if (EXTI_GetITStatus(EXTI_Line5) != RESET)      // Left Button
  {
		setPressedButton(LEFT);
		
	  EXTI_ClearITPendingBit(EXTI_Line5);
  }
	else if (EXTI_GetITStatus(EXTI_Line8) != RESET) // Up Button
  {
		setPressedButton(UP);
		
	  EXTI_ClearITPendingBit(EXTI_Line8);
  }
	  else if (EXTI_GetITStatus(EXTI_Line9) != RESET) // Right Button
  {
		setPressedButton(RIGHT);
		
	  EXTI_ClearITPendingBit(EXTI_Line9);
  }
  else if (EXTI_GetITStatus(EXTI_Line6) != RESET) // Down Button
  {
		setPressedButton(DOWN);
		
	  EXTI_ClearITPendingBit(EXTI_Line6);
  }
  else if (EXTI_GetITStatus(EXTI_Line7) != RESET) // Center Button
  {	
		setPressedButton(CENTER);
		
	  EXTI_ClearITPendingBit(EXTI_Line7);
  }
};

void clearBuffer(uint8_t* buf){
	
	for(int i = 0; i < DMA_BUFFER_SIZE; i++){
		buf[i] = 0;
	}
};

void copyFilterBuffer(uint8_t* bufIn, uint8_t* bufOut){
	
	int i, j, count = 0;
	
	while(bufIn[i++]!='$'){
		if(i==DMA_BUFFER_SIZE) i = 0;
	}
	clearBuffer(bufOut);
	
	while(count<DMA_BUFFER_SIZE){
		if(bufIn[i]=='\r' || bufIn[i]=='\n') return;
		bufOut[j++] = bufIn[i++];
		if(i==DMA_BUFFER_SIZE) i = 0;
		count++;
	}
};

void system_init(void)
{
	gpio_init();
	uart1_init();
	uart3_init();
	dma1_init();
	InitButton();
}
